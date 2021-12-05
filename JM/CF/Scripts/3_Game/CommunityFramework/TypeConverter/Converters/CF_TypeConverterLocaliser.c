[CF_RegisterTypeConverter(CF_TypeConverterLocaliser)]
class CF_TypeConverterLocaliser : CF_TypeConverterClass
{
	override string GetString()
	{
		CF_Localiser localiser = GetLocaliser();
		if (!localiser)
		{
			return "";
		}
		
		return localiser.Format();
	}

	override void SetString(string value)
	{
	}

	override typename GetType()
	{
		typename type = CF_Localiser;
		return type;
	}
	
	CF_Localiser GetLocaliser()
	{
		return CF_Localiser.Cast(m_Value);
	}
};
