class CF_StringStream : CF_Stream
{
	private ref array<char> m_Data = new array<char>();
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

	override void Write(byte value)
	{
		m_Data.InsertAt(_cf_characters[value - 32], m_Position);
	}

	override void WriteChar(string value)
	{
		m_Data.InsertAt(value, m_Position);
	}

	override byte Read()
	{
		string s = m_Data[m_Position++];
		return s.Hash();
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

	override void SetBytes(array<byte> bytes)
	{
		/*CF.Log.*/Error("Not implemented.");
	}

	override array<byte> GetBytes()
	{
		array<byte> arr();
		for (int i = 0; i < m_Data.Count(); i++)
		{
			string s = m_Data[i];
			arr.Insert(s.Hash());
		}
		return arr;
	}
};
