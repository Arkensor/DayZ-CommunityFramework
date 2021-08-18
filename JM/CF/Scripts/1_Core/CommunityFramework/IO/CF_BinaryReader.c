class CF_BinaryReader : CF_IO
{
	override CF_Byte ReadByte()
	{
		return m_Stream.Next();
	}

	override string ReadChar()
	{
		int byte = m_Stream.Next();
		return byte.AsciiToString();
	}

	override bool ReadBool()
	{
		return m_Stream.Next() != 0;
	}

	override int ReadShort()
	{
		int b1 = m_Stream.Next();
		int b0 = m_Stream.Next();
		
		return ((b1 & 0x000000FF) << 8) + (b0);
	}

	override int ReadInt()
	{
		int b3 = m_Stream.Next();
		int b2 = m_Stream.Next();
		int b1 = m_Stream.Next();
		int b0 = m_Stream.Next();
		
		return ((b3 & 0x000000FF) << 24) + ((b2 & 0x000000FF) << 16) + ((b1 & 0x000000FF) << 8) + (b0);
	}

	override float ReadFloat()
	{
		int b3 = m_Stream.Next();
		int b2 = m_Stream.Next();
		int b1 = m_Stream.Next();
		int b0 = m_Stream.Next();

		int src[1];
		src[0] = ((b3 & 0x000000FF) << 24) + ((b2 & 0x000000FF) << 16) + ((b1 & 0x000000FF) << 8) + (b0);
		float dst[1];
		
		copyarray(dst, src);
		
		return dst[0];
	}

	override vector ReadVector()
	{
		int b3;
		int b2;
		int b1;
		int b0;

		int src[3];
		vector dst;
		
		b3 = m_Stream.Next();
		b2 = m_Stream.Next();
		b1 = m_Stream.Next();
		b0 = m_Stream.Next();
		src[0] = ((b3 & 0x000000FF) << 24) + ((b2 & 0x000000FF) << 16) + ((b1 & 0x000000FF) << 8) + (b0);
		
		b3 = m_Stream.Next();
		b2 = m_Stream.Next();
		b1 = m_Stream.Next();
		b0 = m_Stream.Next();
		src[1] = ((b3 & 0x000000FF) << 24) + ((b2 & 0x000000FF) << 16) + ((b1 & 0x000000FF) << 8) + (b0);
		
		b3 = m_Stream.Next();
		b2 = m_Stream.Next();
		b1 = m_Stream.Next();
		b0 = m_Stream.Next();
		src[2] = ((b3 & 0x000000FF) << 24) + ((b2 & 0x000000FF) << 16) + ((b1 & 0x000000FF) << 8) + (b0);
		
		copyarray(dst, src);
		
		return dst;
	}

	override string ReadString()
	{
		int b3 = m_Stream.Next();
		int b2 = m_Stream.Next();
		int b1 = m_Stream.Next();
		int b0 = m_Stream.Next();

		int length = ((b3 & 0x000000FF) << 24) + ((b2 & 0x000000FF) << 16) + ((b1 & 0x000000FF) << 8) + (b0);
		
		string str;

		for (int index = 0; index < length; index++)
		{
			str += m_Stream.Next().AsciiToString();
		}

		return str;
	}

	override string ReadCString()
	{
		string str;

		int c = m_Stream.Next();
		while (c != 0)
		{
			str += c.AsciiToString();
			c = m_Stream.Next();
		}

		return str;
	}
};
