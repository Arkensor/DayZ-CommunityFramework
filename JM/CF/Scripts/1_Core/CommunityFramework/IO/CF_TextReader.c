class CF_TextReader : CF_IO
{
	override bool IsRead()
	{
		return true;
	}

	override bool IsWrite()
	{
		return false;
	}

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
		Param2<CF_PackedByte, int> position;
		m_Stream.GetCurrent(position);

		string str = ReadWord();
		if (str == "true")
			return true;

		if (str == "false")
			return false;

		m_Stream.SetCurrent(position);
		return false;
	}

	override int ReadInt()
	{
		string str;

		int byte = ReadByte();
		while (!CF_Encoding.IsWhitespace(byte) && CF_Encoding.IsNumeric(byte) && !EOF())
		{
			str += byte.AsciiToString();
			byte = ReadByte();
		}

		return str.ToInt();
	}

	override float ReadFloat()
	{
		string str;

		int byte = ReadByte();
		bool decimal = false;
		while (!CF_Encoding.IsWhitespace(byte) && (CF_Encoding.IsNumeric(byte) || (!decimal && byte == 46)) && !EOF())
		{
			str += byte.AsciiToString();
			byte = ReadByte();
		}

		return str.ToFloat();
	}

	override vector ReadVector()
	{
		Param2<CF_PackedByte, int> position;
		m_Stream.GetCurrent(position);

		vector vec;

		vec[0] = ReadFloat();
		
		if (ReadByte() != 44)
		{
			m_Stream.SetCurrent(position);
			return vector.Zero;
		}

		ReadWhitespace();
		vec[1] = ReadFloat();

		if (ReadByte() != 44)
		{
			m_Stream.SetCurrent(position);
			return vector.Zero;
		}

		ReadWhitespace();
		vec[2] = ReadFloat();

		return vec;
	}

	override string ReadLine()
	{
		string str;

		int byte = ReadByte();
		while (!CF_Encoding.IsLine(byte) && !EOF())
		{
			str += byte.AsciiToString();
			byte = ReadByte();
		}

		return str;
	}

	string ReadWord()
	{
		string str;

		int byte = m_Stream.Next();
		while (!CF_Encoding.IsWhitespace(byte) && CF_Encoding.IsAlphanumeric(byte) && !EOF())
		{
			str += byte.AsciiToString();
			byte = m_Stream.Next();
		}

		m_Stream.Previous();

		return str;
	}

	string ReadWhitespace()
	{
		string str;

		int byte = ReadByte();
		while (CF_Encoding.IsWhitespace(byte) && !EOF())
		{
			str += byte.AsciiToString();
			byte = ReadByte();
		}

		m_Stream.Previous();

		return str;
	}
};
