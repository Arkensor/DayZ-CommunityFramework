class ConfigArrayParamFloat : ConfigArrayParam
{
	private float _value;

	override string GetType()
	{
		return "FLOAT_PARAM";
	}

	override bool IsFloat()
	{
		return true;
	}

	override float GetFloat()
	{
		return _value;
	}

	override void SetFloat( float value )
	{
		_value = value;
	}
};