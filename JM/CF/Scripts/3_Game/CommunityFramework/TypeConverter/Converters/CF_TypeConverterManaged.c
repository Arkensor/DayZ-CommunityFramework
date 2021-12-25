[CF_RegisterTypeConverter(CF_TypeConverterManaged)]
class CF_TypeConverterManaged : CF_TypeConverterT<Managed>
{
	override string GetString()
	{
		if (!m_Value) return "NULL";
		return m_Value.GetDebugName();
	}
	
	override void SetClass(Class value)
	{
		Class.CastTo(m_Value, value);
	}
	
	override Class GetClass()
	{
		return m_Value;
	}
	
	override void SetManaged(Managed value)
	{
		m_Value = value;
	}
	
	override Managed GetManaged()
	{
		return m_Value;
	}
};
