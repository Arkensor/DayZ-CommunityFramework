class ConfigArrayParamArray : ConfigArrayParam
{
	private ref ConfigArray _value = new ConfigArray();

	void ~ConfigArrayParamArray()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif

	}

	override string GetType()
	{
		return "ARRAY_PARAM";
	}

	override ConfigArray GetArray()
	{
		return _value;
	}

	override bool IsArray()
	{
		return true;
	}
};