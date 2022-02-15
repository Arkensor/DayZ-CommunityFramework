class CF_FileStream : CF_Stream
{
	string m_Path;
	FileMode m_Mode;

	FileHandle m_FileHandle;

	protected bool m_Dirty;
	protected int m_NonZeroCount;
	protected int m_NonZeroes[4];

	void CF_FileStream(string path, FileMode mode)
	{
		m_Path = path;
		m_Mode = mode;

		m_FileHandle = OpenFile(m_Path, m_Mode);

		m_IsOpen = m_FileHandle != 0;

		ReadData(false);
	}

	void MarkDirty()
	{
		m_Dirty = true;
	}

	override void Append(CF_Byte byte = 0)
	{
		super.Append(byte);

		m_Dirty = true;
	}

	override void AppendCurrent(CF_Byte byte = 0)
	{
		super.AppendCurrent(byte);
		
		m_Dirty = true;
	}
	
	override void SetOrigin(int index, int value, CF_SeekOrigin origin)
	{
		super.SetOrigin(index, value, origin);

		m_Dirty = true;
	}
	
	override void Set(int index, int value)
	{
		super.Set(index, value);

		m_Dirty = true;
	}

	override void Resize(int size)
	{
		super.Resize(size);
		
		m_Dirty = true;
	}

	override bool IsValid()
	{
		return m_FileHandle != 0;
	}

	void ReadData(bool reopen = true)
	{
		if (reopen)
		{
			if (m_FileHandle != 0) CloseFile(m_FileHandle);

			m_FileHandle = OpenFile(m_Path, m_Mode);
		}

		if (m_FileHandle == 0) return;

		if (m_Mode != FileMode.READ) return;
		
		Resize(0);

		bool readData[1];
		while (ReadFile(m_FileHandle, readData, 1) > 0)
		{
			Append(readData[0] & 0x000000FF);
		}
		
		Seek(0, CF_SeekOrigin.SET);
	}

	override void Flush()
	{
		if (m_Mode == FileMode.READ) return;
		
		UpdateDirty();
				
		FileSerializer serializer = new FileSerializer();
		
		if (m_FileHandle != 0)
		{
			CloseFile(m_FileHandle);
		}
		
		if (!serializer.Open(m_Path, FileMode.APPEND)) return;
		
		int oldPosition = m_Position;
		CF_PackedByte oldCurrent = m_Current;

		m_Position = 0;
		m_Current = m_Head;

		int zero = 0;
		while (m_Current)
		{
			if (zero < m_NonZeroCount && m_NonZeroes[zero] == m_Position)
			{
				zero++;

				serializer.Close();
				m_FileHandle = OpenFile(m_Path, FileMode.APPEND);
				
				FPrint(m_FileHandle, Next_AsInt().AsciiToString());
				
				CloseFile(m_FileHandle);
				serializer.Open(m_Path, FileMode.APPEND);

				continue;
			}

			m_Current = m_Current.SerializerWrite(serializer, m_Size, m_Position);
		}
		
		serializer.Close();
		m_FileHandle = OpenFile(m_Path, FileMode.APPEND);

		m_Position = oldPosition;
		m_Current = oldCurrent;
	}
	
	override void Close()
	{
		super.Close();

		if (!IsValid())
			return;
			
		CloseFile(m_FileHandle);
	}

	protected int Next_AsInt()
	{
		int value;
		if (m_Current)
		{
			value = m_Current.m_Value;
			m_Current = m_Current.m_Next;
			m_Position++;
		}

		return value;
	}

	protected void UpdateDirty()
	{
		if (!m_Dirty) return;

		int oldPosition = m_Position;
		CF_PackedByte oldCurrent = m_Current;

		m_Position = 0;
		m_Current = m_Head;
		
		int needed = m_Size % 4;
		int lastZero = 0;

		m_NonZeroCount = 0;
		
		for (int index = 0; index < m_Size; index++)
		{
			if (m_NonZeroCount >= needed) break;

			if (Next() == 0) continue;

			// The value is at the start of a block of 4 bytes
			if (((index - lastZero) % 4) == 0)
			{
				m_NonZeroes[m_NonZeroCount] = index;
				m_NonZeroCount++;

				lastZero = index + 1;
			}
		}

		m_Position = oldPosition;
		m_Current = oldCurrent;

		m_Dirty = false;
	}
};
