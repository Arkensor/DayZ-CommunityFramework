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
};
