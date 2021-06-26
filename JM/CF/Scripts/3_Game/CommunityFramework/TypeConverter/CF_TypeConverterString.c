class CF_TypeConverterString : CF_TypeConverterT<string>
{
	override void SetInt(int value)
	{
		m_Value = "" + value;
	}

	override int GetInt()
	{
		return m_Value.ToInt();		
	}

	override void SetBool(bool value)
	{
		m_Value = "" + value;
	}

	override bool GetBool()
	{
		return CF.StringToBool(m_Value);
	}

	override void SetFloat(float value)
	{
		m_Value = "" + value;
	}

	override float GetFloat()
	{
		return m_Value.ToFloat();
	}

	override void SetVector(vector value)
	{
		m_Value = "" + value;
	}

	override vector GetVector()
	{
		return m_Value.ToVector();
	}

	override void SetString(string value)
	{
		m_Value = value;
	}

	override string GetString()
	{
		return m_Value;
	}
};