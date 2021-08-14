class CF_BinaryWriter : CF_IO
{
	override void WriteByte(CF_Byte value)
	{
		m_Stream.AppendCurrent(value);
	}

	override void WriteChar(string value)
	{
		WriteByte(value.Hash());
	}

	override void WriteBool(bool value)
	{
		if (value) WriteByte(0x00000001);
		else WriteByte(0x00000000);
	}

	override void WriteInt(int value)
	{
		WriteByte((value >> 24) & 0x000000FF);
		WriteByte((value >> 16) & 0x000000FF);
		WriteByte((value >> 8 ) & 0x000000FF);
		WriteByte((value	  ) & 0x000000FF);
	}

	override void WriteFloat(float value)
	{
		WriteInt(CF_Cast<float, int>.Reinterpret(value));
	}

	override void WriteVector(vector value)
	{
		WriteFloat(value[0]);
		WriteFloat(value[1]);
		WriteFloat(value[2]);
	}

	override void WriteString(string value)
	{
		WriteInt(value.Length());
		for (int i = 0; i < value.Length(); i++)
		{
			WriteByte(value[i].Hash());
		}
	}

	override void WriteCString(string value)
	{
		for (int i = 0; i < value.Length(); i++)
		{
			WriteByte(value[i].Hash());
		}
		WriteByte(0);
	}
};
