class CF_ModStorage_Converter
{
	private static bool m_Constructed = false;
	private static autoptr map<typename, typename> m_Types = new map<typename, typename>();

	static void Construct()
	{
		if (m_Constructed)
			return;
		
		m_Constructed = true;
		
		//TODO: test why this still worked with all 'types' set to bool
		AddType(bool, CF_ModStorage_Data_Bool);
		AddType(int, CF_ModStorage_Data_Int);
		AddType(float, CF_ModStorage_Data_Float);
		AddType(vector, CF_ModStorage_Data_Vector);
		AddType(string, CF_ModStorage_Data_String);
	}

	private static void AddType(typename type, typename modStorage)
	{
		m_Types.Insert(type, modStorage);
	}

	static ref CF_ModStorage_Data Read(ParamsReadContext ctx)
	{
		Construct();
		
		typename type;
		ctx.Read(type);

		typename modStorageType = m_Types.Get(type);
		ref CF_ModStorage_Data data = CF_ModStorage_Data.Cast(modStorageType.Spawn());

		if (data)
			data.Read(ctx);

		return data;
	}
};