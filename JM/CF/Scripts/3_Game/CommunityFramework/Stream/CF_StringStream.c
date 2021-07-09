class CF_StringStream : CF_Stream
{
	private ref array<string> m_Data = new array<string>();
	private int m_Position = 0;

	override bool ReadFile(string path)
	{
		FileHandle fileHandle = OpenFile(path, FileMode.READ);
		if (fileHandle == 0) return false;
		
		string lineContent;
		while (FGets(fileHandle, lineContent) >= 0)
		{
			for (int i = 0; i < lineContent.Length(); i++)
			{
				m_Data.Insert(lineContent[i]);
			}
		}

		CloseFile(fileHandle);
		return true;
	}

	override bool WriteFile(string path)
	{
		FileHandle fileHandle = OpenFile(path, FileMode.WRITE);
		if (fileHandle == 0) return false;

		for (int i = 0; i < m_Data.Count(); i++)
		{
			FPrint(fileHandle, m_Data[i]);
		}

		CloseFile(fileHandle);
		return true;
	}

	override void Write(int value)
	{
		m_Data.InsertAt(_cf_characters[value - 32], m_Position);
	}

	override void WriteChar(string value)
	{
		m_Data.InsertAt(value, m_Position);
	}

	override int Read()
	{
		return m_Data[m_Position++].Hash();
	}

	override string ReadChar()
	{
		return m_Data[m_Position++];
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
		for (int i = 0; i < m_Data.Count(); i++)
		{
			arr.Insert(m_Data[i].Hash());
		}
		return arr;
	}
};