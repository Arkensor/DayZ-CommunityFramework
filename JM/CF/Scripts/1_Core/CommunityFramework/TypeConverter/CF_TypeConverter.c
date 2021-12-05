class CF_TypeConverter
{
	private static ref array<string> m_TypeConverterNames = new array<string>();

	private static ref map<typename, CF_TypeConverterBase> m_TypeConvertersMap = new map<typename, CF_TypeConverterBase>();
	private static ref array<ref CF_TypeConverterBase> m_TypeConverters = new array<ref CF_TypeConverterBase>();

	private static bool m_IsCreated;

	private void CF_TypeConverter()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "CF_TypeConverter");
		#endif
	}

	static void OnCreate()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0("Create");
		#endif

		OnDestroy();

		m_IsCreated = true;

		for (int i = 0; i < m_TypeConverterNames.Count(); i++)
		{
			Create(m_TypeConverterNames[i]);
		}
	}

	static void OnDestroy()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0("Create");
		#endif

		m_TypeConvertersMap.Clear();
		m_TypeConverters.Clear();

		m_IsCreated = false;
	}

	static void Insert(typename type)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1("Insert").Add(type);
		#endif

		string className = type.ToString();
		m_TypeConverterNames.Insert(className);

		if (m_IsCreated)
		{
			Create(className);
		}
	}

	static void Create(string className)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1("Create").Add(type);
		#endif

		CF_TypeConverterBase converter;
		if (!Class.CastTo(converter, className.ToType().Spawn()))
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
				
		typename baseType = type;
		CF_TypeConverterBase converter;
		if (!m_TypeConvertersMap.Find(baseType, converter))
		{
			// if the type converter wasn't found, iterate over the list to find the inherited type and add it
			int idx = -1;
			for (int i = m_TypeConverters.Count() - 1; i >= 0; i--)
			{
				if (baseType.IsInherited(m_TypeConverters[i].Type()))
				{
					idx = i;
					break;
				}
			}

			baseType = m_TypeConverters[idx].Type();
			m_TypeConvertersMap.Find(baseType, converter);
		}
		
		return converter;
	}
};
