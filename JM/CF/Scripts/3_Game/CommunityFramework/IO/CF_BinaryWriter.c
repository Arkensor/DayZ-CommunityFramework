class CF_BinaryWriter : CF_File
{
	private ref array<CF_Byte> m_Data = new array<CF_Byte>();
	private int m_Position = 0;

	private bool m_NonZeroesDirty = true;
	private ref array<int> m_NonZeroes = new array<int>();

	override bool File(string path, FileMode mode)
	{		
		FileHandle fileHandle = OpenFile(path, mode);
		if (fileHandle == 0) return false;

		int index;

		switch (mode)
		{
			case FileMode.READ:
			{
				CloseFile(fileHandle);
				Error("Invalid file mode");
				return false;
				break;
			}
			case FileMode.APPEND:
			case FileMode.WRITE:
			{
				UpdateNonZeroFields();
				
				CloseFile(fileHandle);
				
				FileSerializer fs = new FileSerializer();
				fs.Open(path, FileMode.APPEND);

				int ivalue;

				int zeroCheck = 0;
				while (index < m_Data.Count())
				{
					if (zeroCheck < 4 && m_NonZeroes[zeroCheck] == index)
					{
						fs.Close();
						fileHandle = OpenFile(path, FileMode.APPEND);
						
						ivalue = m_Data[index++];
						FPrint(fileHandle, ivalue.AsciiToString());
						zeroCheck++;
						
						CloseFile(fileHandle);
						fs.Open(path, FileMode.APPEND);
						continue;
					}

					int b0 = m_Data[index++];
					int b1 = m_Data[index++];
					int b2 = m_Data[index++];
					int b3 = m_Data[index++];

					ivalue = ((b3) << 24) + ((b2) << 16) + ((b1) << 8) + (b0);
					fs.Write(ivalue);
				}
				
				fs.Close();

				break;
			}
		}
		return true;
	}
	
	void UpdateNonZeroFields()
	{
		if (!m_NonZeroesDirty) return;
		
		m_NonZeroes.Clear();
		
		int needed = m_Data.Count() % 4;
		int lastZero = 0;
		
		for (int index = 0; index < m_Data.Count(); index++)
		{
			if (m_NonZeroes.Count() >= needed) break;

			if (m_Data[index] == 0) continue;

			// The value is at the start of a block of 4 bytes
			if (((index - lastZero) % 4) == 0)
			{
				m_NonZeroes.Insert(index);
				lastZero = index + 1;
			}
		}

		m_NonZeroesDirty = false;
	}

	override void WriteByte(CF_Byte value)
	{
		m_Data.InsertAt(value.Clamp(), m_Position++);
		
		m_NonZeroesDirty = true;
	}

	override void WriteChar(string value)
	{
		WriteByte(value.Hash());
	}

	override void WriteBool(bool value)
	{
		if (value) WriteByte(0x00000001);
		else WriteByte(0x00000000);
	}

	override void WriteInt(int value)
	{
		WriteByte((value >> 24) & 0x000000FF);
		WriteByte((value >> 16) & 0x000000FF);
		WriteByte((value >> 8 ) & 0x000000FF);
		WriteByte((value	  ) & 0x000000FF);
	}

	override void WriteFloat(float value)
	{
		WriteInt(CF_Cast<float, int>.Reinterpret(value));
	}

	override void WriteVector(vector value)
	{
		WriteFloat(value[0]);
		WriteFloat(value[1]);
		WriteFloat(value[2]);
	}

	override void WriteString(string value)
	{
		WriteInt(value.Length());
		for (int i = 0; i < value.Length(); i++)
		{
			WriteByte(value[i].Hash());
		}
	}

	override void WriteCString(string value)
	{
		for (int i = 0; i < value.Length(); i++)
		{
			WriteByte(value[i].Hash());
		}
		WriteByte(0);
	}

	override bool EOF()
	{
		return m_Position >= m_Data.Count();
	}

	override int Position()
	{
		return m_Position;
	}

	override int Length()
	{
		return m_Data.Count();
	}

	override void Seek(int num, CF_SeekOrigin origin = CF_SeekOrigin.CURRENT)
	{
		switch (origin)
		{
			case CF_SeekOrigin.SET:
				m_Position = num;
				return;
			case CF_SeekOrigin.CURRENT:
				m_Position += num;
				return;
			case CF_SeekOrigin.END:
				m_Position = Length() - num - 1;
				return;
		}
	}

	override void SetBytes(array<CF_Byte> bytes)
	{
		m_Data.Clear();
		m_Data.Copy(bytes);
		
		m_NonZeroesDirty = true;
	}
};
