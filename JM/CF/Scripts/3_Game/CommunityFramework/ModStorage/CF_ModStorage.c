/**
 * Do not mod this class. Modding this class defeats the purpose of this being in Community Framework.
 * You will break persistence if you mod it. Make a pull request here https://github.com/Jacob-Mango/DayZ-Community-Framework/pulls
 */
class CF_ModStorage
{
	static const int VERSION = 3;

	protected ModStructure m_Mod;

	protected string m_ModName;
	protected int m_Version;

	void CF_ModStorage(ModStructure mod)
	{
		m_Mod = mod;
		m_Version = m_Mod.GetStorageVersion();
		m_ModName = m_Mod.GetName();
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
		return false;
	}

	bool Read(out int value)
	{
		return false;
	}

	bool Read(out float value)
	{
		return false;
	}

	bool Read(out vector value)
	{
		return false;
	}

	bool Read(out string value)
	{
		return false;
	}

	void Write(bool value)
	{
	}

	void Write(int value)
	{
	}

	void Write(float value)
	{
	}

	void Write(vector value)
	{
	}

	void Write(string value)
	{
	}
};