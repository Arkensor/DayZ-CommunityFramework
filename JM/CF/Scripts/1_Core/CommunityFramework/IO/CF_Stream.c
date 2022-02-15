class CF_Stream
{
	ref CF_PackedByte m_Head;
	CF_PackedByte m_Tail;

	CF_PackedByte m_Current;
	
	int m_Size;
	int m_Position;

	bool m_IsOpen;
	
	void ~CF_Stream()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "~CF_Stream");
#endif

		Close();
	}

	bool IsValid()
	{
		return m_IsOpen;
	}

	void Append(CF_Byte byte = 0)
	{
		CF_PackedByte pByte = new CF_PackedByte();
		pByte.m_Value = byte;

		if (!m_Tail)
		{
			m_Head = pByte;
			m_Tail = pByte;
			m_Size = 1;
		}
		else
		{
			pByte.m_Prev = m_Tail;
			m_Tail.m_Next = pByte;
			m_Tail = pByte;
			m_Size++;
		}
		
		m_Position = m_Size - 1;

		m_Current = pByte;
	}

	void AppendCurrent(CF_Byte byte = 0)
	{
		if (!m_Tail || m_Tail == m_Head || (m_Tail && m_Tail == m_Current))
		{
			Append(byte);
			return;
		}

		CF_PackedByte pByte = new CF_PackedByte();
		pByte.m_Value = byte;

		if (m_Current)
		{
			pByte.m_Next = m_Current.m_Next;
			m_Current.m_Next = pByte;
 
			pByte.m_Prev = m_Current;
 
			if (pByte.m_Next != null) pByte.m_Next.m_Prev = pByte;
			
			m_Position++;
		}
		else
		{
			pByte.m_Next = m_Head;
			m_Head.m_Prev = pByte;
			m_Head = pByte;

			m_Position = 0;
		}

		m_Size++;

		m_Current = pByte;
	}

	void Resize(int size)
	{
		if (m_Size == size) return;

		CF_PackedByte byte = m_Head;
		for (int i = 0; i < size; i++)
		{
			byte = byte.m_Next;
		}

		if (m_Size < size)
		{
			for (i = m_Size; i < size; i++)
			{
				Append();
			}
		}
		else
		{			
			byte.m_Next = null;
			m_Tail = byte;
			
			if (m_Position >= size - 1)
			{
				m_Current = m_Tail;
				m_Position = size - 1;
			}
		}

		m_Size = size;
	}

	int Length()
	{
		return m_Size;
	}

	CF_Byte Get(int index, CF_SeekOrigin origin)
	{
		Seek(index, origin);
		if (!m_Current) return 0;
		return m_Current.m_Value;
	}

	CF_Byte Get(int index)
	{
		Seek(index, CF_SeekOrigin.SET);
		if (!m_Current) return 0;
		return m_Current.m_Value;
	}

	void SetOrigin(int index, int value, CF_SeekOrigin origin)
	{
		Seek(index, origin);
		
		m_Current.m_Value = value;
	}

	void Set(int index, int value)
	{
		Seek(index, CF_SeekOrigin.SET);
		
		m_Current.m_Value = value;
	}

	CF_Byte Next()
	{
		if (!m_Current)
		{
			m_Position = 0;
			m_Current = m_Head;
			
			return 0;
		}
				
		CF_Byte value = m_Current.m_Value;
			
		m_Current = m_Current.m_Next;
		m_Position++;
		
		if (!m_Current)
		{
			m_Position = m_Size;
			m_Current = null;
		}

		return value;
	}

	CF_Byte Previous()
	{
		if (!m_Current)
		{
			m_Position = m_Size - 1;
			m_Current = m_Tail;
			
			return 0;
		}
		
		CF_Byte value = m_Current.m_Value;
			
		m_Current = m_Current.m_Prev;
		m_Position--;
		
		if (!m_Current)
		{
			m_Position = 0;
			m_Current = m_Head;
		}
		
		return value;
	}

	void Next(CF_Byte value)
	{
		AppendCurrent(value);
	}

	Param2<CF_PackedByte, int> GetCurrent()
	{
		return new Param2<CF_PackedByte, int>(m_Current, m_Position);
	}

	void GetCurrent(inout Param2<CF_PackedByte, int> tuple)
	{
		tuple = new Param2<CF_PackedByte, int>(m_Current, m_Position);
	}

	void SetCurrent(Param2<CF_PackedByte, int> tuple)
	{
		m_Current = tuple.param1;
		m_Position = tuple.param2;
	}

	void SetPositionAtStart()
	{
		m_Current = null;
		m_Position = -1;
	}

	void SetPositionAtEnd()
	{
		m_Current = m_Tail;
		m_Position = m_Size - 1;
	}

	void Seek(int num, CF_SeekOrigin origin = CF_SeekOrigin.CURRENT)
	{
		int newPosition;
		
		switch (origin)
		{
			case CF_SeekOrigin.SET:
				newPosition = num;
			
				m_Position = 0;
				m_Current = m_Head;
				break;
			case CF_SeekOrigin.CURRENT:
				newPosition = m_Position + num;
				break;
			case CF_SeekOrigin.END:
				newPosition = m_Size - num;
			
				m_Position = m_Size - 1;
				m_Current = m_Tail;
				break;
		}
		
		if (newPosition < 0)
		{
			m_Position = -1;
			m_Current = null;
			return;
		}
		else if (newPosition >= m_Size)
		{
			m_Position = m_Size - 1;
			m_Current = m_Tail;
			return;
		}
		
		int i;
		if (newPosition > m_Position)
		{
			i = m_Position;
			while (i < newPosition)
			{
				m_Current = m_Current.m_Next;
				i++;
			}
		}
		else if (newPosition < m_Position)
		{
			i = m_Position;
			while (i > newPosition)
			{
				m_Current = m_Current.m_Prev;
				i--;
			}
		}
		
		m_Position = newPosition;
	}

	void CopyTo(CF_Stream dest)
	{
		CF_PackedByte byte = m_Head;
		while (byte)
		{
			dest.Append(byte.m_Value);
			byte = byte.m_Next;
		}
	}

	void CopyTo(CF_Stream dest, int size)
	{
		CF_PackedByte byte = m_Head;

		int index = 0;
		while (byte && index < size)
		{
			dest.Append(byte.m_Value);
			byte = byte.m_Next;
			index++;
		}
	}

	void CopyCurrentTo(CF_Stream dest)
	{
		CF_PackedByte byte = m_Current;

		while (byte)
		{
			dest.Append(byte.m_Value);
			byte = byte.m_Next;
		}
	}

	void CopyCurrentTo(CF_Stream dest, int size)
	{
		CF_PackedByte byte = m_Current;

		int index = 0;
		while (byte && index < size)
		{
			dest.Append(byte.m_Value);
			byte = byte.m_Next;
			index++;
		}
	}

	void Flush()
	{

	}
	
	void Close()
	{
		if (!m_IsOpen)
			return;

		Flush();

		m_IsOpen = true;
	}
	
	override string GetDebugName()
	{
		string str = "[" + m_Size + "] 0x";
		
		int oldPosition = m_Position;
		CF_PackedByte oldCurrent = m_Current;

		m_Position = 0;
		m_Current = m_Head;

		while (m_Current)
		{
			str += m_Current.m_Value.ToHex();

			m_Current = m_Current.m_Next;
		}

		m_Position = oldPosition;
		m_Current = oldCurrent;
		
		return str;
	}
};
