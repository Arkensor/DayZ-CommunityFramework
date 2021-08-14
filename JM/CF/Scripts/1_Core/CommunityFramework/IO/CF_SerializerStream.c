class CF_SerializerStream : CF_Stream
{
	Serializer m_Serializer;

	void CF_SerializerStream(Serializer serializer)
	{
		m_Serializer = serializer;
	}

	override bool IsValid()
	{
		return m_Serializer != null;
	}
};

class CF_SerializerReadStream : CF_SerializerStream
{
	void CF_SerializerReadStream(Serializer serializer)
	{
		m_Serializer.Read(m_Size);
		
		if (m_Size > 0)
		{
			m_Head = new CF_PackedByte();
			m_Tail = m_Head;
			
			m_Position = 0;
			m_Current = m_Head;
			
			while (m_Position < m_Size)
			{
				m_Current = m_Current.SerializerRead(m_Serializer, m_Size, m_Position);
			}
			
			m_Tail = m_Current;
		}
		
		m_Position = 0;
		m_Current = m_Head;
	}
};

class CF_SerializerWriteStream : CF_SerializerStream
{
	bool m_Flushed;
	
	override void Flush()
	{		
		if (m_Flushed) return;
		m_Flushed = true;
		
		m_Serializer.Write(m_Size);
		
		int oldPosition = m_Position;
		CF_PackedByte oldCurrent = m_Current;

		m_Position = 0;
		m_Current = m_Head;
		
		while (m_Position < m_Size)
		{
			m_Current = m_Current.SerializerWrite(m_Serializer, m_Size, m_Position);
		}
		
		m_Position = oldPosition;
		m_Current = oldCurrent;
	}
};
