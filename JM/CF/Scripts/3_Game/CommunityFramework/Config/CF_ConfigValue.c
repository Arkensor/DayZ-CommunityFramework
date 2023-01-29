typedef CF_ConfigValue ConfigValue;

class CF_ConfigValue : ConfigEntry
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
