class CF_BinaryWriter : CF_IO
{
	override bool IsRead()
	{
		return false;
	}

	override bool IsWrite()
	{
		return true;
	}

	override void WriteByte(CF_Byte value)
	{
		m_Stream.AppendCurrent(value);
	}

	override void WriteBytes(array<CF_Byte> bytes)
	{
		for (int i = 0; i < bytes.Count(); i++)
		{
			WriteByte(bytes[i]);
		}
	}

	override void WriteChar(string value)
	{
		m_Stream.AppendCurrent(value.ToAscii());
	}

	override void WriteBool(bool value)
	{
		m_Stream.AppendCurrent(value != 0);
	}

	override void WriteShort(int value)
	{
		m_Stream.AppendCurrent((value      ) & 0x000000FF);
		m_Stream.AppendCurrent((value >> 8 ) & 0x000000FF);
	}

	override void WriteInt(int value)
	{
		m_Stream.AppendCurrent((value      ) & 0x000000FF);
		m_Stream.AppendCurrent((value >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((value >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((value >> 24) & 0x000000FF);
	}

	override void WriteFloat(float value)
	{
		float src[1] = { value };
		int dst[1];
		copyarray(dst, src);
		
		m_Stream.AppendCurrent((dst[0]      ) & 0x000000FF);
		m_Stream.AppendCurrent((dst[0] >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((dst[0] >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((dst[0] >> 24) & 0x000000FF);
	}

	override void WriteVector(vector value)
	{
		int dst[3];
		copyarray(dst, value);

		int a = dst[0];
		int b = dst[1];
		int c = dst[2];
		
		m_Stream.AppendCurrent((a      ) & 0x000000FF);
		m_Stream.AppendCurrent((a >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((a >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((a >> 24) & 0x000000FF);
		
		m_Stream.AppendCurrent((b      ) & 0x000000FF);
		m_Stream.AppendCurrent((b >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((b >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((b >> 24) & 0x000000FF);
		
		m_Stream.AppendCurrent((c      ) & 0x000000FF);
		m_Stream.AppendCurrent((c >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((c >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((c >> 24) & 0x000000FF);
	}

	override void WriteString(string value)
	{
		int length = value.Length();
		m_Stream.AppendCurrent((length      ) & 0x000000FF);
		m_Stream.AppendCurrent((length >> 8 ) & 0x000000FF);
		m_Stream.AppendCurrent((length >> 16) & 0x000000FF);
		m_Stream.AppendCurrent((length >> 24) & 0x000000FF);
		
		for (int i = 0; i < value.Length(); i++)
		{
			m_Stream.AppendCurrent(value.Get(i).ToAscii());
		}
	}

	override void WriteCString(string value)
	{
		for (int i = 0; i < value.Length(); i++)
		{
			m_Stream.AppendCurrent(value.Get(i).ToAscii());
		}
		
		m_Stream.AppendCurrent(0);
	}
};
