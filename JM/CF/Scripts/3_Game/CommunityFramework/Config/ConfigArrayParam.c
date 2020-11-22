class ConfigArrayParam : ConfigEntry
{
	override string GetType()
	{
		return "ARRAY_PARAM_BASE";
	}

	override bool IsArrayParam()
	{
		return true;
	}
};