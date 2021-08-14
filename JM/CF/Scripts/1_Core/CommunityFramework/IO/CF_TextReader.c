class CF_TextReader : CF_IO
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

	override string ReadLine()
	{
		string str;

		string c = ReadChar();
		while (c != "\n" && !EOF())
		{
			str += c;
			c = ReadChar();
		}

		return str;
	}
};
