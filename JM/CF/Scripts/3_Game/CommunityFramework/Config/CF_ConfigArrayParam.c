typedef CF_ConfigArrayParam ConfigArrayParam;

class CF_ConfigArrayParam : CF_ConfigEntry
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
