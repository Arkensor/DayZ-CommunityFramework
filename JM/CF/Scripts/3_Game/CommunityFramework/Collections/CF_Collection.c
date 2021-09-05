class CF_Collection : Managed
{
	protected ref CF_TypeConverter m_Converter;
	protected int m_Count;

	void CF_Collection()
	{
	}

	string GetDebugName()
	{
		return "[" + this + "]";
	}

	/*
	 * @note Returns the same instance of Converter for every index, 
	 * when called in sucession, the value is overwritten
	 */
	CF_TypeConverter GetConverter(int index)
	{
		return m_Converter;
	}

	CF_TypeConverter GetConverter()
	{
		return m_Converter;
	}

	void OverrideConverter(CF_TypeConverter converter = null)
	{
		m_Converter = converter;
	}

	int Count()
	{
		return m_Count;
	}
};