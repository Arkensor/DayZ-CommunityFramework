class CF_StringStream : CF_Stream
{
	void CF_StringStream(string source = "")
	{
		for (int i = 0; i < source.Length(); i++)
		{
			Append(source[i].Hash());
		}
	}

	override void Append(CF_Byte byte = 0)
	{
		if (byte == 0)
		{
			Error("Attempted writing null byte in CF_StringStream.");
			return;
		}

		super.Append(byte);
	}

	override void AppendCurrent(CF_Byte byte = 0)
	{
		if (byte == 0)
		{
			Error("Attempted writing null byte in CF_StringStream.");
			return;
		}
		
		super.AppendCurrent(byte);
	}

	string ToStr()
	{
		string str = "";

		int oldPosition = m_Position;
		CF_PackedByte oldCurrent = m_Current;

		m_Position = 0;
		m_Current = m_Head;

		while (m_Current)
		{
			int byte = m_Current.m_Value;
			str += byte.AsciiToString();

			m_Current = m_Current.m_Next;
		}

		m_Position = oldPosition;
		m_Current = oldCurrent;

		return str;
	}
};
