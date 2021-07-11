class CF_BinaryStream : CF_Stream
{
	private ref array<byte> m_Data = new array<byte>();
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
				int lastZero = 0;

				bool varr[1];
				while (ReadFile(fileHandle, varr, 1) > 0)
				{
					m_Data.Insert(varr[0] & 0x000000FF);

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

					byte b0 = m_Data[index++];
					byte b1 = m_Data[index++];
					byte b2 = m_Data[index++];
					byte b3 = m_Data[index++];

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

	override void Write(byte value)
	{
		m_Data.InsertAt(value, m_Position);
		
		m_NonZeroesDirty = true;
	}

	override void WriteChar(string value)
	{
		m_Data.InsertAt(value.Hash(), m_Position);
		
		m_NonZeroesDirty = true;
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
		
		m_NonZeroesDirty = true;
	}

	override array<byte> GetBytes()
	{
		array<byte> arr();
		arr.Copy(m_Data);
		return arr;
	}
};
