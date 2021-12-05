[CF_RegisterTypeConverter(CF_TypeConverterExpression)]
class CF_TypeConverterExpression : CF_TypeConverterClass
{
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
		return expr.Evaluate(new array<float>);
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
		expr.Compile(new array<string>);
	}

	override typename GetType()
	{
		typename type = CF_Expression;
		return type;
	}
	
	CF_Expression GetExpression()
	{
		return CF_Expression.Cast(m_Value);
	}
};
