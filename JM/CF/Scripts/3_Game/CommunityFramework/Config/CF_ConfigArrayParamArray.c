typedef CF_ConfigArrayParamArray ConfigArrayParamArray;

class CF_ConfigArrayParamArray : CF_ConfigArrayParam
{
	private ref CF_ConfigArray _value = new CF_ConfigArray();

	void ~CF_ConfigArrayParamArray()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "~CF_ConfigArrayParamArray");
#endif
	}

	override string GetType()
	{
		return "ARRAY_PARAM";
	}

	override CF_ConfigArray GetArray()
	{
		return _value;
	}

	override bool IsArray()
	{
		return true;
	}
};
