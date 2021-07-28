class CF_BinaryReader : CF_File
{
	private ref array<CF_Byte> m_Data = new array<CF_Byte>();
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
				m_Data.Clear();

				bool readData[1];
				while (ReadFile(fileHandle, readData, 1) > 0)
				{
					m_Data.Insert(readData[0] & 0x000000FF);
				}

				CloseFile(fileHandle);
				
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
		return true;
	}

	override CF_Byte ReadByte()
	{
		return m_Data[m_Position++];
	}

	override string ReadChar()
	{
		int b = m_Data[m_Position++];
		return b.AsciiToString();
	}

	override bool ReadBool()
	{
		return ReadByte() != 0;
	}

	override int ReadInt()
	{
		int b3 = ReadByte();
		int b2 = ReadByte();
		int b1 = ReadByte();
		int b0 = ReadByte();

		return ((b3 & 0x000000FF) << 24) + ((b2 & 0x000000FF) << 16) + ((b1 & 0x000000FF) << 8) + (b0);
	}

	override float ReadFloat()
	{
		return CF_Cast<int, float>.Reinterpret(ReadInt());
	}

	override vector ReadVector()
	{
		vector v;
		v[0] = ReadFloat();
		v[1] = ReadFloat();
		v[2] = ReadFloat();
		return v;
	}

	override string ReadString()
	{
		string str;

		for (int index = 0; index < ReadInt(); index++)
		{
			str += ReadByte().AsciiToString();
		}

		return str;
	}

	override string ReadCString()
	{
		string str;

		int c = ReadByte();
		while (c != 0)
		{
			str += c.AsciiToString();
			c = ReadByte();
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
		m_Data.Copy(bytes);
	}

	override array<CF_Byte> GetBytes()
	{
		array<CF_Byte> arr();
		arr.Copy(m_Data);
		return arr;
	}
};
