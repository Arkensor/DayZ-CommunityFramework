class ConfigValueLong : ConfigValue
{
	private int _value;

	override string GetType()
	{
		return "LONG";
	}

	override bool IsLong()
	{
		return true;
	}

	override int GetLong()
	{
		return _value;
	}

	override void SetLong( int value )
	{
		_value = value;
	}
};