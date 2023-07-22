class CF_Collection : Managed
{
	protected CF_TypeConverterBase m_Converter;
	protected int m_Count;

	void CF_Collection()
	{
	}

	override string GetDebugName()
	{
		return "[" + this + "]";
	}

	/*
	 * @note Returns the same instance of Converter for every index, 
	 * when called in sucession, the value is overwritten
	 */
	CF_TypeConverterBase GetConverter(int index)
	{
		return m_Converter;
	}

	CF_TypeConverterBase GetConverter()
	{
		return m_Converter;
	}

	void OverrideConverter(CF_TypeConverterBase converter = null)
	{
		m_Converter = converter;
	}

	int Count()
	{
		return m_Count;
	}
};