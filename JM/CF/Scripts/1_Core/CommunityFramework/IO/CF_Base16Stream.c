typedef CF_Base16Stream CF_HexStream;

class CF_Base16Stream : CF_Stream
{
	protected string m_String;

	protected bool m_Dirty;

	void CF_Base16Stream(string str = "")
	{
		Decode(str);
	}

	override void Append(CF_Byte byte = 0)
	{
		super.Append(byte);

		m_Dirty = true;
	}

	override void AppendCurrent(CF_Byte byte = 0)
	{		
		super.AppendCurrent(byte);

		m_Dirty = true;
	}
	
	override void SetOrigin(int index, int value, CF_SeekOrigin origin)
	{
		super.SetOrigin(index, value, origin);

		m_Dirty = true;
	}
	
	override void Set(int index, int value)
	{
		super.Set(index, value);

		m_Dirty = true;
	}

	override void Resize(int size)
	{
		super.Resize(size);
		
		m_Dirty = true;
	}

	void Decode(string str)
	{
		if (m_String != str)
		{
			m_String = str;

			for (int i = 0; i < m_String.Length() / 2; i++)
			{
				int n0 = CF_Encoding.Find(CF_Encoding.BASE_16, 16, m_String[i * 2 + 0]) * 16;
				int n1 = CF_Encoding.Find(CF_Encoding.BASE_16, 16, m_String[i * 2 + 1]) * 16;

				if (n0 < 0 || n1 < 0)
				{
					Error("Invalid character, expect valid base-16, got \"" + m_String[i * 2 + 0] + m_String[i * 2 + 1] + "\"");
					return;
				}

				Append(n0 + n1);
			}
		}
		
		Seek(0, CF_SeekOrigin.SET);
	}

	string Encode()
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
			m_String += m_Current.m_Value.ToHex();

			m_Current = m_Current.m_Next;
		}

		m_Position = oldPosition;
		m_Current = oldCurrent;

		m_Dirty = false;
	}
};
