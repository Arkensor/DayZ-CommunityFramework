class CF_TypeConverterManaged : CF_TypeConverterClass
{
	override string GetString()
	{
		return "" + m_Value;
	}
	
	override void SetManaged(Managed value)
	{
		m_Value = value;
	}
	
	override Managed GetManaged()
	{
		return Managed.Cast(m_Value);
	}
};