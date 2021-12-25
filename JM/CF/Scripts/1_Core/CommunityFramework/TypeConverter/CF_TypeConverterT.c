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

	override typename GetType()
	{
		typename type = T;
		return type;
	}

	override bool Read(Serializer ctx)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Read").Add(ctx);
		#endif

		return ctx.Read(m_Value);
	}

	override bool Write(Serializer ctx)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Write").Add(ctx);
		#endif

		return ctx.Write(m_Value);
	}

	override bool Read(Class instance, string variableName)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Read").Add(instance).Add(variableName);
		#endif

		EnScript.GetClassVar(instance, variableName, 0, m_Value);

		return true;
	}

	override bool Write(Class instance, string variableName)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Write").Add(instance).Add(variableName);
		#endif

		EnScript.SetClassVar(instance, variableName, 0, m_Value);

		return true;
	}

	override bool Read(Class instance, int variableIndex)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Read").Add(instance).Add(variableIndex);
		#endif

		typename instanceType = instance.Type();

		typename variableType = instanceType.GetVariableType(variableIndex);
		string variableName = instanceType.GetVariableName(variableIndex);

		// Unfortunately 'Class' type variables results in a hard crash with no discernible pattern to lock them out
		if (variableType.IsInherited(Class)) return false;

		instanceType.GetVariableValue(instance, variableIndex, m_Value);

		return true;
	}
};
