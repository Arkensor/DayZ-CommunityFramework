/**
 * Do not mod this class. Modding this class defeats the purpose of this being in Community Framework.
 * You will break persistence if you mod it. Make a pull request here https://github.com/Jacob-Mango/DayZ-Community-Framework/pulls
 */
class CF_ModStorage
{
	static const int VERSION = 3;

	ModStructure m_Mod;

	int m_Version;
	string m_Name;

	string m_Data;
	string m_Value;

	void CF_ModStorage(ModStructure mod)
	{
		m_Mod = mod;
		
		_ResetStream();
	}

	int GetVersion()
	{
		return m_Version;
	}

	ModStructure GetMod()
	{
		return m_Mod;
	}

	bool Read(out bool value)
	{
		m_Data.ParseStringEx(m_Value);

		value = m_Value == "1";

		return true;
	}

	bool Read(out int value)
	{
		m_Data.ParseStringEx(m_Value);

		value = m_Value.ToInt();

		return true;
	}

	bool Read(out float value)
	{
		m_Data.ParseStringEx(m_Value);

		value = m_Value.ToFloat();

		return true;
	}

	bool Read(out vector value)
	{
		m_Data.ParseStringEx(m_Value);

		value = m_Value.ToVector();

		return true;
	}

	bool Read(out string value)
	{
		m_Data.ParseStringEx(m_Value);

		value = m_Value;

		return true;
	}

	void Write(bool value)
	{
		if (value)
		{
			m_Data += " 1";
		}
		else
		{
			m_Data += " 0";
		}
	}

	void Write(int value)
	{
		m_Data += " " + value.ToString();
	}

	void Write(float value)
	{
		m_Data += " " + value.ToString();
	}

	void Write(vector value)
	{
		m_Data += " \"" + value.ToString(false) + "\"";
	}

	void Write(string value)
	{
		m_Data += " \"" + value + "\"";
	}

	void _CopyStreamTo(Serializer ctx)
	{
		if (m_Data.Length() > 0)
		{
			m_Data = m_Data.Substring(1, m_Data.Length() - 1);
		}
		
		ctx.Write(m_Data);

		_ResetStream();
	}

	// Read and Write functions can't be called, so we can't reset the stream
	void _ResetStream()
	{
		if (!m_Mod)
		{
			return;
		}

		m_Data = string.Empty;
		m_Version = m_Mod.GetStorageVersion();
	}
};
