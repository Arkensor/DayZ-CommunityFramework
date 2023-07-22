class CF_TypeConverter_BoolInvert : CF_TypeConverterInt
{
	override void SetInt(int value)
	{
		m_Value = value == 0;
	}

	override int GetInt()
	{
		if (m_Value != 0)
			return 0;
		return 1;
	}

	override void SetBool(bool value)
	{
		m_Value = value == 0;
	}

	override bool GetBool()
	{
		return m_Value == 0;
	}

	override void SetFloat(float value)
	{
		m_Value = value == 0.0;
	}

	override float GetFloat()
	{
		return GetInt();
	}

	override void SetVector(vector value)
	{
	}

	override vector GetVector()
	{
		return vector.Zero;
	}

	override void SetString(string value)
	{
		m_Value = CF.StringToBool(value) == false;
	}

	override string GetString()
	{
		return "" + (!m_Value);
	}
};
