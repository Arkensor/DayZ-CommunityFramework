class ConfigValueInt : ConfigValue
{
	private int _value;

	override string GetType()
	{
		return "INT";
	}

	override bool IsInt()
	{
		return true;
	}

	override int GetInt()
	{
		return _value;
	}

	override void SetInt( int value )
	{
		_value = value;
	}
};