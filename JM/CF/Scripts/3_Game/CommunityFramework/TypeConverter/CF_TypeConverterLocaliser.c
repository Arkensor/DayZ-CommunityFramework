class CF_TypeConverterLocaliser : CF_TypeConverterClass
{
	override string GetString()
	{
		CF_Localiser localiser = GetLocaliser();
		if (!localiser) return "";

		return localiser.ToStr();
	}

	override void SetString(string value)
	{
	}
	
	CF_Localiser GetLocaliser()
	{
		return CF_Localiser.Cast(m_Value);
	}
};
