typedef CF_ConfigValue ConfigValue;

class CF_ConfigValue : CF_ConfigEntry
{
	override string GetType()
	{
		return "VALUE";
	}

	override bool IsValue()
	{
		return true;
	}
}
