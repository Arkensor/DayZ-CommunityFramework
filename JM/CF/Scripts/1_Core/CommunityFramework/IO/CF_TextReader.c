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

		while (!EOF())
		{
			int byte = ReadByte();
			if (CF_Encoding.IsWhitespace(byte) || !CF_Encoding.IsNumeric(byte)) {
				break;
			}
			str += byte.AsciiToString();
		}

		return str.ToInt();
	}

	override float ReadFloat()
	{
		string str;

		bool decimal = false;
		while (!EOF())
		{
			int byte = ReadByte();

			if (byte == 46) {
				if (decimal)
					break;
				decimal = true;
			} else if ( CF_Encoding.IsWhitespace(byte) || (!CF_Encoding.IsNumeric(byte) ) ) {
				break;
			}
			str += byte.AsciiToString();
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

		int byte;
		while (!EOF())
		{
			byte = ReadByte();
			if (CF_Encoding.IsLine(byte)) {
				break;
			}
			str += byte.AsciiToString();
		}

		return str;
	}

	string ReadWord()
	{
		string str;

		while (!EOF())
		{
			int byte = m_Stream.Next();			
			if (CF_Encoding.IsWhitespace(byte) || !CF_Encoding.IsAlphanumeric(byte)) {
				break;
			}
			str += byte.AsciiToString();
		}

		m_Stream.Previous();

		return str;
	}

	string ReadWhitespace()
	{
		string str;

		while (!EOF())
		{
			int byte = ReadByte();
			if (!CF_Encoding.IsWhitespace(byte)) {
				break;
			}
			str += byte.AsciiToString();
		}

		m_Stream.Previous();

		return str;
	}
};
