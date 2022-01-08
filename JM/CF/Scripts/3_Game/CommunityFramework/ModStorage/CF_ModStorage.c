/**
 * Do not mod this class. Modding this class defeats the purpose of this being in Community Framework.
 * You will break persistence if you mod it. Make a pull request here https://github.com/Jacob-Mango/DayZ-Community-Framework/pulls
 */
class CF_ModStorage
{
	static const int VERSION = 3;

	protected ModStructure m_Mod;

	protected int m_Version;
	protected ref CF_ModStorageStream m_Stream;

	void CF_ModStorage(ModStructure mod)
	{
		m_Mod = mod;
		m_Version = m_Mod.GetStorageVersion();
		m_Stream = new CF_ModStorageStream(null);
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
		string token;
		int result;

		result = m_Stream.Eat(token);
		value = token == "1";

		return true;
	}

	bool Read(out int value)
	{
		string token;
		int result;

		result = m_Stream.Eat(token);
		value = token.ToInt();

		return true;
	}

	bool Read(out float value)
	{
		string token;
		int result;

		result = m_Stream.Eat(token);
		value = token.ToFloat();

		return true;
	}

	bool Read(out vector value)
	{
		string token;
		int result;

		result = m_Stream.Eat(token);
		value = token.ToVector();

		return true;
	}

	bool Read(out string value)
	{
		int result;

		result = m_Stream.Eat(value);

		return true;
	}

	void Write(bool value)
	{
		if (value)
		{
			m_Stream.m_Data += " 1";
		}
		else
		{
			m_Stream.m_Data += " 0";
		}
	}

	void Write(int value)
	{
		m_Stream.m_Data += " " + value.ToString();
	}

	void Write(float value)
	{
		m_Stream.m_Data += " " + value.ToString();
	}

	void Write(vector value)
	{
		m_Stream.m_Data += " \"" + value.ToString(false) + "\"";
	}

	void Write(string value)
	{
		m_Stream.m_Data += " \"" + value + "\"";
	}
	
	CF_ModStorageStream GetStream()
	{
		return m_Stream;
	}

	void _CopyStreamTo(Serializer ctx)
	{
		m_Stream.WriteToStream(ctx);

		_ResetStream();
	}

	void _ResetStream()
	{
		m_Stream.Reset();
		m_Version = m_Mod.GetStorageVersion();
	}
	
	override string GetDebugName()
	{
		string str = super.GetDebugName();
		
		if (m_Stream) str += ", Stream=" + m_Stream.GetDebugName();
		else str += ", Stream=null";
		
		return str;
	}
};
