class ConfigArrayParamInt : ConfigArrayParam
{
	private int _value;

	override string GetType()
	{
		return "INT_PARAM";
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