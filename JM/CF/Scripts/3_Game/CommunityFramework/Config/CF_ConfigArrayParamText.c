typedef CF_ConfigArrayParamText ConfigArrayParamText;

class CF_ConfigArrayParamText : CF_ConfigArrayParam
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

	override void SetText(string value)
	{
		_value = value;
	}
};
