class CF_ModStorageWriter : CF_ModStorage
{
	ref CF_Stream m_Stream;

	void CF_ModStorageWriter(ModStructure mod, CF_Stream stream)
	{
		m_Stream = stream;
	}

	void WriteHeader()
	{
		m_Stream.m_Current = m_Stream.m_Head;
		m_Stream.m_Position = 0;

		Write(m_Stream.m_Size + m_ModName.Length() + 4);
		Write(m_ModName);

		m_Stream.m_Current = m_Stream.m_Tail;
		m_Stream.m_Position = m_Stream.m_Size - 1;
	}

	override void Write(bool value)
	{
		m_Stream.AppendCurrent(value != 0);
	}

	override void Write(int value)
	{
		m_Stream.AppendCurrent((value >> 24) & 0x000000FF);
		m_Stream.AppendCurrent((value >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((value >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((value      ) & 0x000000FF);
	}

	override void Write(float value)
	{
		float src[1] = { value };
		int dst[1];
		copyarray(dst, src);
		
		m_Stream.AppendCurrent((dst[0] >> 24) & 0x000000FF);
		m_Stream.AppendCurrent((dst[0] >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((dst[0] >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((dst[0]      ) & 0x000000FF);
	}

	override void Write(vector value)
	{
		int dst[3];
		copyarray(dst, value);

		int a = dst[0];
		int b = dst[1];
		int c = dst[2];
		
		m_Stream.AppendCurrent((a >> 24) & 0x000000FF);
		m_Stream.AppendCurrent((a >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((a >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((a      ) & 0x000000FF);
		
		m_Stream.AppendCurrent((b >> 24) & 0x000000FF);
		m_Stream.AppendCurrent((b >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((b >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((b      ) & 0x000000FF);
		
		m_Stream.AppendCurrent((c >> 24) & 0x000000FF);
		m_Stream.AppendCurrent((c >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((c >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((c      ) & 0x000000FF);
	}

	override void Write(string value)
	{
		int length = value.Length();
		m_Stream.AppendCurrent((length >> 24) & 0x000000FF);
		m_Stream.AppendCurrent((length >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((length >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((length      ) & 0x000000FF);
		
		for (int i = 0; i < length; i++)
		{
			m_Stream.AppendCurrent(value.Substring(i, 1).Hash());
		}
	}
};
