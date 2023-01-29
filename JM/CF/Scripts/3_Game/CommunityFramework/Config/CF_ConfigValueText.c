typedef CF_ConfigValueText ConfigValueText;

class CF_ConfigValueText : CF_ConfigValue
{
	private string _value;

	override string GetType()
	{
		return "TEXT";
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
