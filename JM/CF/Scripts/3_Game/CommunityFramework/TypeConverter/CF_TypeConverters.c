static autoptr CF_TypeConverters g_CF_TypeConverters = null;
	
class CF_TypeConverters
{
	private static ref map<typename, typename> m_TypeConvertersMap;
	private static ref array<typename> m_TypeConverters;

	private void CF_TypeConverters()
	{
		RegisterTypes();
	}

	protected void RegisterType(typename type, typename converter)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(g_CF_TypeConverters, "RegisterTypes").Add("" + type).Add("" + converter);
		#endif
		
		m_TypeConvertersMap.Insert(type, converter);
		m_TypeConverters.Insert(type);
	}
	
	protected void RegisterTypes()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(g_CF_TypeConverters, "RegisterTypes");
		#endif
		
		RegisterType(bool, CF_TypeConverterBool);
		RegisterType(int, CF_TypeConverterInt);
		RegisterType(float, CF_TypeConverterFloat);
		RegisterType(vector, CF_TypeConverterVector);
		RegisterType(string, CF_TypeConverterString);
		RegisterType(Class, CF_TypeConverterClass);
		RegisterType(Managed, CF_TypeConverterManaged);
		RegisterType(EntityAI, CF_TypeConverterManaged);
		RegisterType(CF_Expression, CF_TypeConverterExpression);
		RegisterType(CF_Date, CF_TypeConverterDate);
		RegisterType(CF_Localiser, CF_TypeConverterLocaliser);
	}
	
	[CF_EventSubscriber(CF_TypeConverters._Init, CF_LifecycleEvents.OnGameCreate)]
	static void _Init()
	{
		if (g_CF_TypeConverters) return;

		m_TypeConvertersMap = new map<typename, typename>();
		m_TypeConverters = new array<typename>();
		
		g_CF_TypeConverters = new CF_TypeConverters();
	}

	[CF_EventSubscriber(CF_TypeConverters._Cleanup, CF_LifecycleEvents.OnGameDestroy)]
	static void _Cleanup()
	{
		g_CF_TypeConverters = null;

		m_TypeConverters = null;
		m_TypeConvertersMap = null;
	}

	static CF_TypeConverter Create(typename type)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(g_CF_TypeConverters, "Create").Add("" + type);
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
		
		CF_TypeConverter res = CF_TypeConverter.Cast(convType.Spawn());		
		
		return res;
	}
};
