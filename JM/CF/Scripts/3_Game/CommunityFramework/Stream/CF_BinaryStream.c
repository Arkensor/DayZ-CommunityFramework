class CF_BinaryStream : CF_Stream
{
	private ref array<byte> m_Data = new array<byte>();
	private int m_Position = 0;

	override bool _ReadFile(string path)
	{
		FileHandle fileHandle = OpenFile(path, FileMode.READ);
		if (fileHandle == 0) return false;
		
		bool varr[1];
		while (ReadFile(fileHandle, varr, 1) > 0)
		{
			byte value = varr[0] & 0x000000FF;
			m_Data.Insert(value);
		}

		CloseFile(fileHandle);
		return true;
	}

	override bool _WriteFile(string path)
	{
		FileSerializer fileHandle();
		if (!fileHandle.Open(path, FileMode.WRITE)) return false;
		
		int index = 0;

		byte b0;
		byte b1;
		byte b2;
		byte b3;

		while (index < m_Data.Count())
		{
			b0 = 0;
			b1 = 0;
			b2 = 0;
			b3 = 0;

			if (index < m_Data.Count()) b0 = m_Data[index];
			index++;
			if (index < m_Data.Count()) b1 = m_Data[index];
			index++;
			if (index < m_Data.Count()) b2 = m_Data[index];
			index++;
			if (index < m_Data.Count()) b3 = m_Data[index];
			index++;
			
			int value = ((b3) << 24) + ((b2) << 16) + ((b1) << 8) + (b0);
			
			fileHandle.Write(value);
		}

		fileHandle.Close();
		return true;
	}

	override void Write(byte value)
	{
		m_Data.InsertAt(value, m_Position);
	}

	override void WriteChar(string value)
	{
		m_Data.InsertAt(value.Hash(), m_Position);
	}

	override byte Read()
	{
		return m_Data[m_Position++];
	}

	override string ReadChar()
	{
		byte b = m_Data[m_Position++];
		return _cf_characters[b - 32];
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

	override void GoTo(int position)
	{
		m_Position = position;
	}

	override void Seek(int offset)
	{
		m_Position += offset;
	}

	override void SetBytes(array<byte> bytes)
	{
		m_Data.Clear();
		m_Data.Copy(bytes);
	}

	override array<byte> GetBytes()
	{
		array<byte> arr();
		arr.Copy(m_Data);
		return arr;
	}
};
