class CF_Stream : Managed
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
			m_Position = 0;
		}
		else
		{
			pByte.m_Prev = m_Tail;
			m_Tail.m_Next = pByte;
			m_Tail = pByte;
			m_Position++;
		}
		
		m_Size++;

		m_Current = pByte;
	}

	void AppendCurrent(CF_Byte byte = 0)
	{
		CF_PackedByte pByte = new CF_PackedByte();
		pByte.m_Value = byte;

		if (!m_Tail)
		{
			m_Head = pByte;
			m_Tail = pByte;
			m_Position = 0;
		}
		else if (m_Tail == m_Head)
		{
			
		}
		else
		{
			if (!m_Current)
			{
				m_Current = m_Tail;
			}
			
			if (m_Current != m_Head)
			{
				if (!m_Current.m_Prev)
				{
					pByte.m_Prev = null;
					pByte.m_Next = m_Head;
					m_Head.m_Prev = pByte;
					m_Head = pByte;
				}
				else if (!m_Current.m_Prev.m_Next)
				{
					pByte.m_Next = null;
					pByte.m_Prev = m_Tail;
					m_Tail.m_Next = pByte;
					m_Tail = pByte;
				}
				else
				{
					pByte.m_Prev = m_Current.m_Prev;
					pByte.m_Next = pByte.m_Prev.m_Next;
					pByte.m_Next.m_Prev = pByte;
					pByte.m_Prev.m_Next = pByte;
				}
			}
			else
			{
				pByte.m_Prev = m_Current.m_Prev;
				pByte.m_Next = pByte.m_Prev.m_Next;
				pByte.m_Next.m_Prev = pByte;
				pByte.m_Prev.m_Next = pByte;
			}

			m_Position++;
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

	CF_Byte Get(int index)
	{
		Seek(index, CF_SeekOrigin.SET);
		if (!m_Current) return 0;
		return m_Current.m_Value;
	}

	void Set(int index, CF_Byte value)
	{
		Seek(index, CF_SeekOrigin.SET);
		if (!m_Current) return;
		m_Current.m_Value = value;
	}

	CF_Byte Next()
	{
		CF_Byte value;
		if (m_Current)
		{
			value = m_Current.m_Value;
			m_Current = m_Current.m_Next;
			m_Position++;
		}

		return value;
	}

	CF_Byte Previous()
	{
		CF_Byte value;
		if (m_Current)
		{
			value = m_Current.m_Value;
			m_Current = m_Current.m_Prev;
			m_Position--;
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

	void SetPosition(int newPosition)
	{
		if (newPosition == m_Position) return;

		if (newPosition <= 0)
		{
			m_Current = m_Head;
			m_Position = 0;
			return;
		}

		if (newPosition >= m_Size - 1)
		{
			m_Current = m_Tail;
			m_Position = m_Size - 1;
			return;
		}

		int diff = newPosition - m_Position;

		int aDiff = diff;
		if (aDiff < 0) aDiff = -aDiff;

		if (aDiff > m_Size / 2)
		{
			if (diff < 0)
			{
				Seek(newPosition, CF_SeekOrigin.SET);
			}
			else
			{
				Seek(newPosition - m_Size, CF_SeekOrigin.END);
			}

			return;
		}

		int i;

		m_Position = newPosition;
		if (diff > 0) for (i = 0; i < diff; i++) m_Current = m_Current.m_Next;
		else if (diff < 0) for (i = 0; i < diff; i++) m_Current = m_Current.m_Prev;
	}

	void Seek(int num, CF_SeekOrigin origin = CF_SeekOrigin.CURRENT)
	{
		int i;
		switch (origin)
		{
			case CF_SeekOrigin.SET:
				m_Position = num;
				m_Current = m_Head;
				for (i = 0; i < num; i++) m_Current = m_Current.m_Next;
				return;
			case CF_SeekOrigin.CURRENT:
				m_Position = m_Position + num;
				if (num > 0) for (i = 0; i < num; i++) m_Current = m_Current.m_Next;
				else if (num < 0) for (i = 0; i < num; i++) m_Current = m_Current.m_Prev;
				return;
			case CF_SeekOrigin.END:
				m_Position = m_Size - num - 1;
				m_Current = m_Tail;
				for (i = 0; i < num; i++) m_Current = m_Current.m_Prev;
				return;
		}
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
};
