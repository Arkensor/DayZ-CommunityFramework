static autoptr CF_TypeConverter g_CF_TypeConverter = null;
	
class CF_TypeConverter
{
	private static ref map<typename, typename> m_TypeConvertersMap;
	private static ref array<typename> m_TypeConverters;

	private void CF_TypeConverter()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "CF_TypeConverter");
		#endif

		CF_TypeConverterConstructor constructor = new CF_TypeConverterConstructor();
		constructor.Register();
	}

	void Insert(typename type, typename converter)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Register").Add(type).Add(converter);
		#endif
		
		m_TypeConvertersMap.Insert(type, converter);
		m_TypeConverters.Insert(type);
	}
		
	[CF_EventSubscriber(CF_TypeConverter._Init, CF_LifecycleEvents.OnGameCreate)]
	static void _Init()
	{
		if (g_CF_TypeConverter) return;

		m_TypeConvertersMap = new map<typename, typename>();
		m_TypeConverters = new array<typename>();
		
		g_CF_TypeConverter = new CF_TypeConverter();
	}

	[CF_EventSubscriber(CF_TypeConverter._Cleanup, CF_LifecycleEvents.OnGameDestroy)]
	static void _Cleanup()
	{
		g_CF_TypeConverter = null;

		m_TypeConverters = null;
		m_TypeConvertersMap = null;
	}

	static CF_TypeConverterBase Create(typename type)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Create").Add(type);
		#endif
				
		typename baseType = type;
		typename convType;
		if (!m_TypeConvertersMap.Find(baseType, convType))
		{
			int idx = -1;
			for (int i = m_TypeConverters.Count() - 1; i >= 0; i--)
			{
				if (baseType.IsInherited(m_TypeConverters[i]))
				{
					idx = i;
					break;
				}
			}

			baseType = m_TypeConverters[idx];
			m_TypeConvertersMap.Find(baseType, convType);
		}
		
		CF_TypeConverterBase res = CF_TypeConverterBase.Cast(convType.Spawn());		
		
		return res;
	}
};
