class ConfigValue : ConfigEntry
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