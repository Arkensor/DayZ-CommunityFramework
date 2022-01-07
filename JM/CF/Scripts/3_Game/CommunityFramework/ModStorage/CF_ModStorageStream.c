class CF_ModStorageStream : CF_SerializerStream
{
	string m_Name;
	int m_Version;

	void Reset()
	{
		m_Head = null;
		m_Tail = null;
		m_Current = null;
		m_Size = 0;
		m_Position = 0;
	}

	void ReadFromStream(Serializer serializer)
	{
		m_Serializer = serializer;
		
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

	void WriteToStream(Serializer serializer)
	{
		m_Serializer = serializer;

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

	override bool IsValid()
	{
		return true;
	}
};
