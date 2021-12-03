/**
 * @brief Template
 */
class CF_TypeConverterT<Class T> : CF_TypeConverterBase
{
	protected T m_Value;
	
	void Set(T value)
	{
		m_Value = value;
	}
	
	T Get()
	{
		return m_Value;
	}

	override void Read(Class instance, string variable)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Read").Add(instance).Add(variable);
		#endif

		EnScript.GetClassVar(instance, variable, 0, m_Value);
	}

	override bool Read(Class instance, int index)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Read").Add(instance).Add(index);
		#endif

		typename type = instance.Type();

		typename variableType = type.GetVariableType(index);
		string variableName = type.GetVariableName(index);

		// Unfortunately 'Class' type variables results in a hard crash with no discernible pattern to lock them out
		if (variableType.IsInherited(Class)) return false;

		type.GetVariableValue(instance, index, m_Value);

		return true;
	}

	override void Write(Class instance, string variable)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Write").Add(instance).Add(variable);
		#endif

		EnScript.SetClassVar(instance, variable, 0, m_Value);
	}
};
