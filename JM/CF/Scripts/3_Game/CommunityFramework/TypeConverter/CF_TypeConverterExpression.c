class CF_TypeConverterExpression : CF_TypeConverterClass
{
	private ref CF_Map<string, float> m_Variables = new CF_Map<string, float>();

	override void SetBool(bool value)
	{
	}

	override bool GetBool()
	{
		return GetFloat() != 0.0;		
	}

	override void SetInt(int value)
	{
	}

	override int GetInt()
	{
		return GetFloat();		
	}

	override void SetFloat(float value)
	{
	}

	override float GetFloat()
	{
		CF_Expression expr = GetExpression();
		if (!expr) return 0;
		return expr.Evaluate(m_Variables.GetValueArray());
	}

	override string GetString()
	{
		CF_Expression expr = GetExpression();
		if (!expr) return "";

		return expr.GetSource();
	}

	override void SetString(string value)
	{
		CF_Expression expr = GetExpression();
		if (!expr) return;

		expr.SetSource(value);
		expr.Compile(m_Variables.GetKeyArray());
	}
	
	CF_Expression GetExpression()
	{
		return CF_Expression.Cast(m_Value);
	}
};
