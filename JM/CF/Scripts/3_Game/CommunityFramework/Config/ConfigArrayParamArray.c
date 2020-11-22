class ConfigArrayParamArray : ConfigArrayParam
{
	private ref ConfigArray _value;

	void ConfigArrayParamArray()
	{
		_value = new ConfigArray();
	}

	void ~ConfigArrayParamArray()
	{
		delete _value;
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