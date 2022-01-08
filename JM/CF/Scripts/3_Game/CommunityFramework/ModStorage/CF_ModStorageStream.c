class CF_ModStorageStream
{
	string m_Name;
	int m_Version;

	string m_Data;
	
	string m_Value;

	void CF_ModStorageStream(Serializer serializer)
	{

	}
	
	int Eat(out string value)
	{
		int result = m_Data.ParseStringEx(m_Value);
		
		value = m_Value;
		
		return result;
	}

	void Reset()
	{
		m_Data = string.Empty;
	}

	void ReadFromStream(Serializer serializer)
	{
		serializer.Read(m_Data);
	}

	void WriteToStream(Serializer serializer)
	{
		if (m_Data.Length() > 0)
		{
			m_Data = m_Data.Substring(1, m_Data.Length() - 1);
		}
		
		serializer.Write(m_Data);
	}

	//override bool IsValid()
	//{
	//	return true;
	//}
};
