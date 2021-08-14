class CF_PackedByte
{
	autoptr CF_PackedByte m_Next;

	CF_Byte m_Value;
	
	private void CF_PackedByte()
	{
		// Do not allow anyone to instiate outside of 'CF_PackedByte'
		// Must use 'CF_PackedByteHeader' with 'Resize' or 'AppendNext'/'RemoveNext'
	}

	/**
	 * Creates new byte between current next and this
	 */
	CF_Byte AppendNext(CF_Byte byte = 0)
	{
		CF_PackedByte newByte();
		newByte.m_Value = byte;
		newByte.m_Value.Clamp();
		newByte.m_Next = m_Next;
		m_Next = newByte;

		return m_Next;
	}

	/**
	 * Overrites next byte with value, creates next byte if it doesn't exist
	 */
	CF_Byte OverriteNext(CF_Byte byte = 0)
	{
		if (m_Next)
		{
			m_Next.m_Value = byte;
			m_Next.m_Value.Clamp();
			return m_Next;
		}

		CF_PackedByte newByte();
		newByte.m_Value = byte;
		newByte.m_Value.Clamp();
		newByte.m_Next = m_Next;
		m_Next = newByte;

		return m_Next;
	}

	/**
	 * Removes next byte, replacing with byte after
	 */
	void RemoveNext()
	{
		if (!m_Next) return;

		m_Next = m_Next.m_Next;
	}

	/**
	 * Removes all next bytes
	 */
	void DestroyNext()
	{
		m_Next = null;
	}

	CF_PackedByte WriteNext(Serializer ctx)
	{
		CF_PackedByte byte = m_Next;

		int b0;
		int b1;
		int b2;
		int b3;

		if (byte)
		{
			b0 = byte.m_Value;
			byte = byte.m_Next;
		}

		if (byte)
		{
			b1 = byte.m_Value;
			byte = byte.m_Next;
		}

		if (byte)
		{
			b2 = byte.m_Value;
			byte = byte.m_Next;
		}

		if (byte)
		{
			b3 = byte.m_Value;
			byte = byte.m_Next;
		}

		ctx.Write(((b3 & 0x000000FF) << 24) + ((b2 & 0x000000FF) << 16) + ((b1 & 0x000000FF) << 8) + (b0));

		return byte;
	}

	CF_PackedByte ReadNext(Serializer ctx, int length, inout int index)
	{
		CF_PackedByte byte = this;

		int value;

		ctx.Read(value);

		int b0 = (value >> 24) & 0x000000FF;
		int b1 = (value >> 16) & 0x000000FF;
		int b2 = (value >> 8 ) & 0x000000FF;
		int b3 = (value		 ) & 0x000000FF;

		if (index < m_Length)
		{
			byte = byte.OverriteNext(b0);

			index++;
		}

		if (index < m_Length)
		{
			byte = byte.OverriteNext(b1);
			
			index++;
		}

		if (index < m_Length)
		{
			byte = byte.OverriteNext(b2);
			
			index++;
		}

		if (index < m_Length)
		{
			byte = byte.OverriteNext(b3);
			
			index++;
		}

		return byte;
	}
};

void CF_PackedByteHeader : CF_PackedByte
{
	int m_Size;

	void Resize(int size)
	{
		if (m_Size == size) return;

		CF_PackedByte byte = this;
		for (int i = 0; i < size; i++)
		{
			byte = byte.m_Next;
		}

		if (size < m_Size)
		{
			for (i = size; i < m_Size; i++)
			{
				byte = byte.AppendNext();
			}
		}
		else
		{
			byte.DestroyNext();
		}

		m_Size = size;
	}

	void Write(Serializer ctx)
	{
		ctx.Write(m_Size);

		CF_PackedByte byte = this;
		while (!byte)
		{
			byte = byte.WriteNext(ctx);
		}
	}

	void Read(Serializer ctx)
	{
		ctx.Read(m_Size);

		int index;

		CF_PackedByte byte = this;
		while (index < m_Size)
		{
			byte = byte.ReadNext(ctx, m_Size, index);
		}
	}
};
