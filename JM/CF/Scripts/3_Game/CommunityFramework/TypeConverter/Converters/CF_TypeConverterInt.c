[CF_RegisterTypeConverter(CF_TypeConverterInt)]
class CF_TypeConverterInt : CF_TypeConverterT<int>
{
	override void SetInt(int value)
	{
		m_Value = value;
	}

	override int GetInt()
	{
		return m_Value;		
	}

	override void SetBool(bool value)
	{
		m_Value = value;
	}

	override bool GetBool()
	{
		return m_Value != 0;
	}

	override void SetFloat(float value)
	{
		m_Value = value;
	}

	override float GetFloat()
	{
		return m_Value;
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
		m_Value = value.ToInt();
	}

	override string GetString()
	{
		return "" + m_Value;
	}

	override bool IsIOSupported()
	{
		return true;
	}

	override bool Read(CF_IO io)
	{
		m_Value = io.ReadInt();

		return true;
	}

	override bool Write(CF_IO io)
	{
		io.WriteInt(m_Value);

		return true;
	}
};
