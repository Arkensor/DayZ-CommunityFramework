class CF_TextReader : CF_IO
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
					m_Data.Insert("\n");
				}
				break;
			}
			case FileMode.APPEND:
			case FileMode.WRITE:
			{
				CloseFile(fileHandle);
				Error("Invalid file mode");
				return false;
				break;
			}
		}

		CloseFile(fileHandle);
		return true;
	}

	override CF_Byte ReadByte()
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

	override string ReadLine()
	{
		string str;

		string c = ReadChar();
		while (c != "\n" && m_Position < m_Data.Count())
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
		for (int i = 0; i < bytes.Count(); i++)
		{
			m_Data.Insert(bytes[i].AsciiToString());
		}
	}

	override array<CF_Byte> GetBytes()
	{
		array<CF_Byte> arr();
		for (int i = 0; i < m_Data.Count(); i++)
		{
			string s = m_Data[i];
			arr.Insert(s.Hash());
		}
		return arr;
	}
};
