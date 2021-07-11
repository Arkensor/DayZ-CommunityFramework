class CF_StringStream : CF_Stream
{
	private ref array<string> m_Data = new array<string>();
	private int m_Position = 0;

	override bool File(string path, FileMode mode)
	{
		FileHandle fileHandle = OpenFile(path, mode);
		if (fileHandle == 0) return false;

		int index;

		switch (mode)
		{
			case FileMode.READ:
			{
				string lineContent;
				while (FGets(fileHandle, lineContent) >= 0)
				{
					for (index = 0; index < lineContent.Length(); index++)
					{
						m_Data.Insert(lineContent[index]);
					}
				}
				break;
			}
			case FileMode.APPEND:
			case FileMode.WRITE:
			{
				for (index = 0; index < m_Data.Count(); index++)
				{
					FPrint(fileHandle, m_Data[index]);
				}
				break;
			}
		}

		CloseFile(fileHandle);
		return true;
	}

	override void Write(int value)
	{
		m_Data.InsertAt(value.AsciiToString(), m_Position++);
	}

	override void WriteChar(string value)
	{
		m_Data.InsertAt(value, m_Position++);
	}

	override void WriteString(string value)
	{
		for (int i = 0; i < value.Length(); i++)
		{
			m_Data.InsertAt(value[i], m_Position++);
		}
	}

	override int Read()
	{
		string s = m_Data[m_Position++];
		return s.Hash();
	}

	override string ReadChar()
	{
		return m_Data[m_Position++];
	}

	override string ReadString()
	{
		string str;

		string c = ReadChar();
		while (c != "" && m_Position < m_Data.Count())
		{
			str += c;
			c = ReadChar();
		}

		return str;
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

	override void SetBytes(array<int> bytes)
	{
		m_Data.Clear();
		for (int i = 0; i < bytes.Count(); i++)
		{
			m_Data.Insert(bytes[i].AsciiToString());
		}
	}

	override array<int> GetBytes()
	{
		array<int> arr();
		for (int i = 0; i < m_Data.Count(); i++)
		{
			string s = m_Data[i];
			arr.Insert(s.Hash());
		}
		return arr;
	}
};
