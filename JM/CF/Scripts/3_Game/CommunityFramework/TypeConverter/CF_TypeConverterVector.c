class CF_TypeConverterVector : CF_TypeConverterT<vector>
{
	override void SetVector(vector value)
	{
		m_Value = value;
	}

	override vector GetVector()
	{
		return m_Value;
	}

	override void SetString(string value)
	{
		m_Value = value.ToVector();
	}

	override string GetString()
	{
		return "" + m_Value;
	}
};