class CF_Stream
{
	ref CF_PackedByte m_Head;
	CF_PackedByte m_Tail;

	CF_PackedByte m_Current;
	
	int m_Size;
	int m_Position;

	bool IsValid()
	{
		return true;
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

		if (size < m_Size)
		{
			for (i = size; i < m_Size; i++)
			{
				AppendCurrent();
			}
		}
		else
		{
			byte.m_Next = null;
			m_Tail = byte;
		}

		m_Size = size;
	}

	void Write(Serializer ctx)
	{
		ctx.Write(m_Size);

		m_Position = 0;
		while (m_Position < m_Size)
		{
			WriteSingle(ctx);
		}
	}

	void Read(Serializer ctx)
	{
		ctx.Read(m_Size);

		m_Position = 0;
		while (m_Position < m_Size)
		{
			ReadSingle(ctx);
		}
	}

	void WriteSingle(Serializer ctx)
	{
		if (!m_Current) return;

		m_Current = m_Current.SerializerWrite(ctx, m_Size, m_Position);
	}

	void ReadSingle(Serializer ctx)
	{
		if (!m_Tail) Append();

		if (!m_Current) m_Current = m_Tail;

		m_Current = m_Current.SerializerRead(ctx, m_Size, m_Position);

		if (!m_Current.m_Next) m_Tail = m_Current;
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

	void Set(int index, CF_Byte value, CF_SeekOrigin origin)
	{
		Seek(index, origin);
		
		m_Current.m_Value = value;
	}

	void Set(int index, CF_Byte value)
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
		dest.m_Head = null;

		CF_PackedByte byte = m_Head;
		while (!byte)
		{
			dest.Append(byte.m_Value);
			byte = byte.m_Next;
		}
	}

	void Flush()
	{

	}
	
	void Close()
	{
		
	}
};
