class CF_BinaryStream : CF_Stream
{
	private ref array<byte> m_Data = new array<byte>();
	private int m_Position = 0;
	private int m_Offset = 8;

	override bool File(string path, FileMode mode)
	{
		FileHandle fileHandle = OpenFile(path, mode);
		if (fileHandle == 0) return false;

		switch (mode)
		{
			case FileMode.READ:
			{
				bool varr[1];
				while (ReadFile(fileHandle, varr, 1) > 0)
				{
					m_Data.Insert(varr[0] & 0x000000FF);
				}
				break;
			}
			case FileMode.APPEND:
			case FileMode.WRITE:
			{
				FileSerializer fs = new FileSerializer();
				if (!fs.Open(path, FileMode.APPEND)) return false;

				int ivalue = 0;

				int index = 0;
				while (index < (m_Data.Count() - m_Offset))
				{
					byte b0 = m_Data[index++];
					byte b1 = m_Data[index++];
					byte b2 = m_Data[index++];
					byte b3 = m_Data[index++];

					ivalue = ((b3) << 24) + ((b2) << 16) + ((b1) << 8) + (b0);

					fs.Write(ivalue);
				}

				while (index < m_Data.Count() - m_Offset)
				{
					ivalue = m_Data[index++];
					FPrint(fileHandle, ivalue.AsciiToString());
				}
				break;
			}
		}

		CloseFile(fileHandle);
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
		int b = m_Data[m_Position++];
		return b.AsciiToString();
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
