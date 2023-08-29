class CF_StringStream : CF_Stream
{
	protected string m_String;

	protected bool m_Dirty;

	void CF_StringStream(string str = "")
	{
		m_String = str;
		for (int i = 0; i < str.Length(); i++)
		{
			Append(str.Get(i).ToAscii());
		}
		
		Seek(0, CF_SeekOrigin.SET);
	}

	override void Append(CF_Byte byte = 0)
	{
		if (byte == 0)
		{
			CF_Log.Error("Attempted writing null byte in CF_StringStream.");
			return;
		}

		super.Append(byte);

		m_Dirty = true;
	}

	override void AppendCurrent(CF_Byte byte = 0)
	{
		if (byte == 0)
		{
			CF_Log.Error("Attempted writing null byte in CF_StringStream.");
			return;
		}
		
		super.AppendCurrent(byte);

		m_Dirty = true;
	}
	
	override void SetOrigin(int index, int value, CF_SeekOrigin origin)
	{
		if (value == 0)
		{
			CF_Log.Error("Attempted writing null byte in CF_StringStream.");
			return;
		}
		
		super.SetOrigin(index, value, origin);

		m_Dirty = true;
	}
	
	override void Set(int index, int value)
	{
		if (value == 0)
		{
			CF_Log.Error("Attempted writing null byte in CF_StringStream.");
			return;
		}
		
		super.Set(index, value);

		m_Dirty = true;
	}

	override void Resize(int size)
	{
		super.Resize(size);
		
		m_Dirty = true;
	}

	override string GetDebugName()
	{
		UpdateDirty();

		return m_String;
	}

	protected void UpdateDirty()
	{
		if (!m_Dirty) return;

		m_String = "";

		int oldPosition = m_Position;
		CF_PackedByte oldCurrent = m_Current;

		m_Position = 0;
		m_Current = m_Head;

		while (m_Current)
		{
			int byte = m_Current.m_Value;
			m_String += byte.AsciiToString();

			m_Current = m_Current.m_Next;
		}

		m_Position = oldPosition;
		m_Current = oldCurrent;

		m_Dirty = false;
	}
};
