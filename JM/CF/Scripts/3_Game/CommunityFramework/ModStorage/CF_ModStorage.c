/**
 * @class	CF_ModStorage
 *
 * @note	Do not mod this class. Modding this class defeats the purpose of this being in Community Framework.
 * 			You will break persistence if you mod it. Make a pull request here https://github.com/Jacob-Mango/DayZ-Community-Framework/pulls
 */
class CF_ModStorage
{
	static const int VERSION = 4;
	
	static const int GAME_VERSION_FIRST_INSTALL = 116;
	static const int GAME_VERSION_WIPE_FILE = 127;

	static const int MODSTORAGE_INITIAL_IMPLEMENTATION = 2;

	ModStructure m_Mod;

	int m_Version;

	int m_HashA;
	int m_HashB;

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
		string data;
		if (m_Data.Length() > 0)
		{
			data = m_Data.Substring(1, m_Data.Length() - 1);
		}

		// force resetting early so we can write the latest version
		_ResetStream();

		ctx.Write(m_HashA);
		ctx.Write(m_HashB);
		
		ctx.Write(m_Version);

		ctx.Write(data);
	}

	// Read and Write functions can't be called, so we can't reset the stream
	void _ResetStream()
	{
		if (!m_Mod)
		{
			return;
		}

		m_Data = string.Empty;

		m_HashA = m_Mod.m_CF_HashA;
		m_HashB = m_Mod.m_CF_HashB;

		m_Version = m_Mod.GetStorageVersion();
	}
};
