class CF_TypeConverterConstructor
{
	void Insert(typename type, typename converter)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Insert").Add(type).Add(converter);
		#endif
		
		g_CF_TypeConverter.Insert(type, converter);
	}

	void Register()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "Register");
		#endif

		Insert(bool, CF_TypeConverterBool);
		Insert(int, CF_TypeConverterInt);
		Insert(float, CF_TypeConverterFloat);
		Insert(vector, CF_TypeConverterVector);
		Insert(string, CF_TypeConverterString);
		Insert(Class, CF_TypeConverterClass);
		Insert(Managed, CF_TypeConverterManaged);
		Insert(EntityAI, CF_TypeConverterManaged);
		Insert(CF_Expression, CF_TypeConverterExpression);
		Insert(CF_Date, CF_TypeConverterDate);
		Insert(CF_Localiser, CF_TypeConverterLocaliser);
	}
};
