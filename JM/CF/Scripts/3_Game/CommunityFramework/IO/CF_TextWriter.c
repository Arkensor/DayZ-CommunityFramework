class CF_TextWriter : CF_File
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
				CloseFile(fileHandle);
				Error("Invalid file mode");
				return false;
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

	override void WriteByte(CF_Byte value)
	{
		m_Data.InsertAt(value.AsciiToString(), m_Position++);
	}

	override void WriteChar(string value)
	{
		m_Data.InsertAt(value, m_Position++);
	}

	override void WriteLine(string value)
	{
		for (int i = 0; i < value.Length(); i++)
		{
			WriteChar(value);
		}
		WriteChar("\n");
	}

	override void WriteString(string value)
	{
		for (int i = 0; i < value.Length(); i++)
		{
			WriteChar(value);
		}
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
