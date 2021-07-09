class CF_BinaryStream : CF_Stream
{
	private ref array<int> m_Data = new array<int>();
	private int m_Position = 0;

	override bool ReadFile(string path)
	{
		FileSerializer fileHandle();
		if (!fileHandle.Open(path, FileMode.READ)) return false;
		
		int value;
		while (fileHandle.Read(value))
		{
			int b0 = (value >> 24) & 0x000000FF;
			int b1 = (value >> 16) & 0x000000FF;
			int b2 = (value >> 8) & 0x000000FF;
			int b3 = (value) & 0x000000FF;

			m_Data.Insert(b0);
			m_Data.Insert(b1);
			m_Data.Insert(b2);
			m_Data.Insert(b3);
		}

		fileHandle.Close();
		return true;
	}

	override bool WriteFile(string path)
	{
		FileSerializer fileHandle();
		if (!fileHandle.Open(path, FileMode.WRITE)) return false;
		
		int index = 0;
		while (index < m_Data.Count())
		{
			int b0;
			int b1;
			int b2;
			int b3;

			if (index < m_Data.Count()) b0 = m_Data[index];
			index++;
			if (index < m_Data.Count()) b1 = m_Data[index];
			index++;
			if (index < m_Data.Count()) b2 = m_Data[index];
			index++;
			if (index < m_Data.Count()) b3 = m_Data[index];
			index++;

			int value = (b0 << 24) + (b1 << 16) + (b2 << 8) + (b3);
			
			fileHandle.Write(value);
		}

		fileHandle.Close();
		return true;
	}

	override void Write(int value)
	{
		m_Data.InsertAt(value, m_Position);
	}

	override void WriteChar(string value)
	{
		m_Data.InsertAt(value.Hash(), m_Position);
	}

	override int Read()
	{
		return m_Data[m_Position++];
	}

	override string ReadChar()
	{
		int byte = m_Data[m_Position++];
		return _cf_characters[byte - 32];
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

	override array<int> GetByteArray()
	{
		array<int> arr();
		arr.Copy(m_Data);
		return arr;
	}
};