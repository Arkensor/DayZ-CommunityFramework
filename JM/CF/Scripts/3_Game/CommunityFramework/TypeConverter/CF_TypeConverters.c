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
		CF_Trace trace(CF.TypeConverters, "RegisterTypes", "" + type, "" + converter);
		
		m_TypeConvertersMap.Insert(type, converter);
		m_TypeConverters.Insert(type);
	}
	
	protected void RegisterTypes()
	{
		CF_Trace trace(CF.TypeConverters, "RegisterTypes");
		
		RegisterType(bool, CF_TypeConverterBool);
		RegisterType(int, CF_TypeConverterInt);
		RegisterType(float, CF_TypeConverterFloat);
		RegisterType(vector, CF_TypeConverterVector);
		RegisterType(string, CF_TypeConverterString);
		RegisterType(Class, CF_TypeConverterClass);
		RegisterType(Managed, CF_TypeConverterManaged);
	}
	
	static CF_TypeConverters _Init()
	{
		m_TypeConvertersMap = new map<typename, typename>();
		m_TypeConverters = new array<typename>();

		return new CF_TypeConverters();
	}

	static void _Cleanup()
	{
		m_TypeConverters = null;
		m_TypeConvertersMap = null;
	}

	static CF_TypeConverter Create(typename type)
	{
		CF_Trace trace(CF.TypeConverters, "Create", "" + type);
				
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
		
		CF.Log.Info("Type=%1", "" + type);
		CF.Log.Info("BaseType=%1", "" + baseType);
		CF.Log.Info("Conv=%1", "" + res);
		
		return res;
	}
};