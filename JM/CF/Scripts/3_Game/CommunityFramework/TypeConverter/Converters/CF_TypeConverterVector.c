[CF_RegisterTypeConverter(CF_TypeConverterVector)]
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

	override bool IsIOSupported()
	{
		return true;
	}

	override void Write(CF_IO io)
	{
		io.WriteVector(m_Value);
	}

	override void Read(CF_IO io)
	{
		m_Value = io.ReadVector();
	}
};
