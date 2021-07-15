class CF_BinaryStream : CF_Stream
{
	private ref array<int> m_Data = new array<int>();
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
				m_Data.Clear();

				int lastZero = 0;

				bool readData[1];
				while (ReadFile(fileHandle, readData, 1) > 0)
				{
					m_Data.Insert(readData[0] & 0x000000FF);

					// Add if currently only less than maximum required
					if (m_NonZeroes.Count() < 4)
					{
						// Isn't the value we are trying to ignore
						if (m_Data[index] != 0)
						{
							// The value is at the start of a block of 4 bytes
							if (((index - lastZero) % 4) == 0)
							{
								m_NonZeroes.Insert(index);
								lastZero = index + 1;
							}
						}
					}
					
					index++;
				}

				// Don't need all non-zero variables
				m_NonZeroes.Resize(m_Data.Count() % 4);
				m_NonZeroesDirty = false;

				CloseFile(fileHandle);
				
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

	override void Write(int value)
	{
		m_Data.InsertAt(value, m_Position++);
		
		m_NonZeroesDirty = true;
	}

	override void WriteChar(string value)
	{
		Write(value.Hash());
	}

	override void WriteBool(bool value)
	{
		if (value) Write(0x00000001);
		else Write(0x00000000);
	}

	override void WriteInt(int value)
	{
		Write((value >> 24) & 0x000000FF);
		Write((value >> 16) & 0x000000FF);
		Write((value >> 8 ) & 0x000000FF);
		Write((value	  ) & 0x000000FF);
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
			Write(value[i].Hash());
		}
	}

	override void WriteCString(string value)
	{
		for (int i = 0; i < value.Length(); i++)
		{
			Write(value[i].Hash());
		}
		Write(0);
	}

	override int ReadByte()
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
				m_Position = Length() - num;
				return;
		}
	}

	override void SetBytes(array<int> bytes)
	{
		m_Data.Clear();
		m_Data.Copy(bytes);
		
		m_NonZeroesDirty = true;
	}

	override array<int> GetBytes()
	{
		array<int> arr();
		arr.Copy(m_Data);
		return arr;
	}
};
