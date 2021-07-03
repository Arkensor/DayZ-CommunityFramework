class CF_Collection : Managed
{
	protected ref CF_TypeConverter m_Converter;

	void CF_Collection()
	{
	}

	string String()
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

	int Count()
	{
		return 0;
	}
};