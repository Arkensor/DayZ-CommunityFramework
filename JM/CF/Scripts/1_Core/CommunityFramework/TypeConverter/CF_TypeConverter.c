class CF_TypeConverter
{
	private static autoptr array<string> m_TypeConverterNames = new array<string>();

	private static autoptr map<typename, CF_TypeConverterBase> m_TypeConvertersMap = new map<typename, CF_TypeConverterBase>();
	private static autoptr array<autoptr CF_TypeConverterBase> m_TypeConverters = new array<autoptr CF_TypeConverterBase>();

	private static bool m_IsCreated;

	private void CF_TypeConverter()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "CF_TypeConverter");
#endif
	}

	void ~CF_TypeConverter()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "~CF_TypeConverter");
#endif
	}

	static void _OnCreate()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0("CF_TypeConverter", "_OnCreate");
#endif


		_OnDestroy();

		m_IsCreated = true;

		for (int i = 0; i < m_TypeConverterNames.Count(); i++)
		{
			_Create(m_TypeConverterNames[i]);
		}
	}

	static void _OnDestroy()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0("CF_TypeConverter", "_OnDestroy");
#endif

		m_TypeConvertersMap.Clear();
		m_TypeConverters.Clear();

		m_IsCreated = false;
	}

	/**
	 * @brief Inserts the typeconverter typename into the list of typeconverters to create, creates if already instantiated
	 */
	static void _Insert(typename type)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1("Insert").Add(type);
#endif

		string className = type.ToString();
		m_TypeConverterNames.Insert(className);

		if (m_IsCreated)
		{
			_Create(className);
		}
	}

	/**
	 * @brief Creates the typeconverter from the name of the class
	 */
	static void _Create(string className)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1("Create").Add(className);
#endif

		CF_TypeConverterBase converter;
		if (!Class.CastTo(converter, className.ToType().Spawn()))
		{
			return;
		}

		if (m_TypeConvertersMap.Contains(converter.GetType()))
		{
			return;
		}

		m_TypeConvertersMap.Insert(converter.GetType(), converter);
		m_TypeConverters.Insert(converter);
	}

	static CF_TypeConverterBase Get(typename type)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1("Get").Add(type);
#endif

		CF_TypeConverterBase converter;
		if (!m_TypeConvertersMap.Find(type, converter))
		{
			// if the type converter wasn't found, iterate over the list to find the inherited type and add it

			typename inputType = type;
			for (int i = m_TypeConverters.Count() - 1; i >= 0; i--)
			{
				if (type.IsInherited(m_TypeConverters[i].GetType()))
				{
					type = m_TypeConverters[i].GetType();
					break;
				}
			}

			if (type == inputType)
			{
				CF_Log.Error("Type Converter not found for type=" + type);
				return null;
			}

			m_TypeConvertersMap.Find(type, converter);
		}

		return converter;
	}

	static CF_TypeConverterBase Get(Class instance, string variableName)
	{
		if (!instance)
		{
			return null;
		}

		typename instanceType = instance.Type();
		int count = instanceType.GetVariableCount();
		for (int index = 0; index < count; index++)
		{
			if (CF_String.EqualsIgnoreCase(variableName, instanceType.GetVariableName(index)))
			{
				typename variableType = instanceType.GetVariableType(index);
				return Get(variableType);
			}
		}

		return null;
	}
};
