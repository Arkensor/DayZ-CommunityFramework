class CF_TextWriter : CF_IO
{
	override void WriteByte(CF_Byte value)
	{
		m_Stream.AppendCurrent(value);
	}

	override void WriteChar(string value)
	{
		WriteByte(value.Hash());
	}

	override void WriteLine(string value)
	{
		for (int i = 0; i < value.Length(); i++)
		{
			WriteChar(value);
		}
		WriteChar("\n");
	}

	override void WriteString(string value)
	{
		for (int i = 0; i < value.Length(); i++)
		{
			WriteChar(value);
		}
	}
};
