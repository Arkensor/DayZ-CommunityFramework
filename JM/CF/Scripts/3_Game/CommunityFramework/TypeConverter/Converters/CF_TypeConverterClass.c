[CF_RegisterTypeConverter(CF_TypeConverterClass)]
class CF_TypeConverterClass : CF_TypeConverterT<Class>
{
	override int GetInt()
	{
		return (int) m_Value;		
	}

	override bool GetBool()
	{
		return m_Value != null;
	}

	override float GetFloat()
	{
		return GetInt();
	}

	override string GetString()
	{
		if (!m_Value) return "NULL";
		return m_Value.GetDebugName();
	}
	
	override void SetClass(Class value)
	{
		m_Value = value;
	}
	
	override Class GetClass()
	{
		return m_Value;
	}
};
