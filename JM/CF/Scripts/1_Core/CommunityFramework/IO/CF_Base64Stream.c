class CF_Base64Stream : CF_Stream
{
	static const string s_Padding[3] = { "", "=", "==" };
	
	protected string m_String;

	protected bool m_Dirty;

	void CF_Base64Stream(string str = "")
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

			int padding = 0;
			int i = 0;

			while (i < m_String.Length())
			{
				int value;
				
				for (int j = 0; j < 4; j++)
				{
					int n = CF_Encoding.Find(CF_Encoding.BASE_64, 64, m_String.Substring(i, 1));
					i++;
					if (n == -1)
					{
						padding++;
						continue;
					}
					
					value += n << ((18 - j * 6));
				}

				Append((value >> 16	) & 255);
				Append((value >> 8	) & 255);
				Append((value		) & 255);
			}
			
			Resize(m_Size - padding);
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
			CF_Uint value = 0;
			
			value = value.Add(m_Current.m_Value << 16);
			m_Current = m_Current.m_Next;
			
			if (m_Current)
			{
				value = value.Add(m_Current.m_Value << 8);
				m_Current = m_Current.m_Next;
			}
			
			if (m_Current)
			{
				value = value.Add(m_Current.m_Value);
				m_Current = m_Current.m_Next;
			}

			m_String += CF_Encoding.BASE_64[value.ShiftRight(18) & 63];
			m_String += CF_Encoding.BASE_64[value.ShiftRight(12) & 63];
			m_String += CF_Encoding.BASE_64[value.ShiftRight(6) & 63];
			m_String += CF_Encoding.BASE_64[value & 63];
		}
		
		int pad = 3 - (m_Size % 3);
		m_String = m_String.Substring(0, m_String.Length() - pad) + s_Padding[pad];

		m_Position = oldPosition;
		m_Current = oldCurrent;

		m_Dirty = false;
	}
};
