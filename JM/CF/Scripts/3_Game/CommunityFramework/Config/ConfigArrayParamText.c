class ConfigArrayParamText : ConfigArrayParam
{
	private string _value;

	override string GetType()
	{
		return "TEXT_PARAM";
	}

	override bool IsText()
	{
		return true;
	}

	override string GetText()
	{
		return _value;
	}

	override void SetText( string value )
	{
		_value = value;
	}
};