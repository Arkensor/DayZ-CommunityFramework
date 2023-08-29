class CF_TextWriter : CF_IO
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

	override void WriteChar(string value)
	{
		WriteByte(value.ToAscii());
	}
	
	override void WriteBool(bool value)
	{
		WriteString(value.ToString());
	}

	override void WriteInt(int value)
	{
		WriteString(value.ToString());
	}

	override void WriteFloat(float value)
	{
		WriteString(value.ToString());
	}

	override void WriteVector(vector value)
	{
		WriteString(value.ToString());
	}

	override void WriteLine(string value)
	{
		for (int i = 0; i < value.Length(); i++)
		{
			WriteChar(value[i]);
		}
		WriteChar("\n");
	}

	override void WriteString(string value)
	{
		for (int i = 0; i < value.Length(); i++)
		{
			WriteChar(value[i]);
		}
	}
};
