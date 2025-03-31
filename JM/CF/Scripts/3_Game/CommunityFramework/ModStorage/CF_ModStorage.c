/**
 * @class	CF_ModStorage
 *
 * @note	Do not mod this class. Modding this class defeats the purpose of this being in Community Framework.
 * 			You will break persistence if you mod it. Make a pull request here https://github.com/Jacob-Mango/DayZ-Community-Framework/pulls
 */
class CF_ModStorage
{
	static const int VERSION = 5;
	
	static const int GAME_VERSION_FIRST_INSTALL = 116;
	static const int GAME_VERSION_WIPE_FILE = 141;  //! DayZ 1.27 GAME_STORAGE_VERSION

	static const int MODSTORAGE_INITIAL_IMPLEMENTATION = 2;

	int m_CF_Version;

	ModStructure m_Mod;

	int m_Version;

	int m_HashA;
	int m_HashB;

	// v4
	string m_Data;
	string m_Value;

	// v5
	ref array<ref CF_ModStorageDataBase> m_Entries;
	int m_Idx;
	int m_MaxIdx;

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

	string GetModName()
	{
		if (m_Mod)
		{
			return m_Mod.GetName();
		}

		return "unknown<" + m_HashA + "," + m_HashB + ">";
	}

	bool Read(out bool value)
	{
		if (m_CF_Version < VERSION)
		{
			m_Data.ParseStringEx(m_Value);

			value = m_Value == "1";
		}
		else
		{
			if (m_Idx > m_MaxIdx || m_Entries[m_Idx].ValueType() != bool)
				return false;

			value = CF_ModStorageData<bool>.Cast(m_Entries[m_Idx++]).Get();
		}

		return true;
	}

	bool Read(out int value)
	{
		if (m_CF_Version < VERSION)
		{
			m_Data.ParseStringEx(m_Value);

			value = m_Value.ToInt();
		}
		else
		{
			if (m_Idx > m_MaxIdx || m_Entries[m_Idx].ValueType() != int)
				return false;

			value = CF_ModStorageData<int>.Cast(m_Entries[m_Idx++]).Get();
		}

		return true;
	}

	bool Read(out float value)
	{
		if (m_CF_Version < VERSION)
		{
			m_Data.ParseStringEx(m_Value);

			value = m_Value.ToFloat();
		}
		else
		{
			if (m_Idx > m_MaxIdx || m_Entries[m_Idx].ValueType() != float)
				return false;

			value = CF_ModStorageData<float>.Cast(m_Entries[m_Idx++]).Get();
		}

		return true;
	}

	bool Read(out vector value)
	{
		if (m_CF_Version < VERSION)
		{
			m_Data.ParseStringEx(m_Value);

			value = m_Value.ToVector();
		}
		else
		{
			if (m_Idx > m_MaxIdx || m_Entries[m_Idx].ValueType() != vector)
				return false;

			value = CF_ModStorageData<vector>.Cast(m_Entries[m_Idx++]).Get();
		}

		return true;
	}

	bool Read(out string value)
	{
		if (m_CF_Version < VERSION)
		{
			m_Data.ParseStringEx(m_Value);

			value = m_Value;
		}
		else
		{
			if (m_Idx > m_MaxIdx || m_Entries[m_Idx].ValueType() != string)
				return false;

			value = CF_ModStorageData<string>.Cast(m_Entries[m_Idx++]).Get();
		}

		return true;
	}

	void Write(bool value)
	{
		_Insert(value);
	}

	void Write(int value)
	{
		_Insert(value);
	}

	void Write(float value)
	{
		_Insert(value);
	}

	void Write(vector value)
	{
		_Insert(value);
	}

	void Write(string value)
	{
		_Insert(value);
	}

	void _CopyStreamTo(Serializer ctx)
	{
		int cf_version = m_CF_Version;
		string data;

		if (cf_version < VERSION)
		{
			if (m_Data.Length() > 0)
			{
				data = m_Data.Substring(1, m_Data.Length() - 1);
			}
		}

		auto tmp = m_Entries;

		// force resetting early so we can write the latest version
		_ResetStream();

		ctx.Write(m_HashA);
		ctx.Write(m_HashB);
		
		ctx.Write(m_Version);

		if (cf_version < VERSION)
		{
			ctx.Write(data);
			return;
		}

		ctx.Write(tmp.Count());
		foreach (auto entry: tmp)
		{
			switch (entry.ValueType())
			{
				case bool:
					CF_ModStorageData<bool> entryBool = CF_ModStorageData<bool>.Cast(entry);
					ctx.Write(CF_ModStorageDataType.BOOL);
					ctx.Write(entryBool.Get());
					break;
				case int:
					CF_ModStorageData<int> entryInt = CF_ModStorageData<int>.Cast(entry);
					ctx.Write(CF_ModStorageDataType.INT);
					ctx.Write(entryInt.Get());
					break;
				case float:
					CF_ModStorageData<float> entryFloat = CF_ModStorageData<float>.Cast(entry);
					ctx.Write(CF_ModStorageDataType.FLOAT);
					ctx.Write(entryFloat.Get());
					break;
				case vector:
					CF_ModStorageData<vector> entryVector = CF_ModStorageData<vector>.Cast(entry);
					ctx.Write(CF_ModStorageDataType.VECTOR);
					vector v = entryVector.Get();
					ctx.Write(v[0]);
					ctx.Write(v[1]);
					ctx.Write(v[2]);
					break;
				case string:
					CF_ModStorageData<string> entryString = CF_ModStorageData<string>.Cast(entry);
					ctx.Write(CF_ModStorageDataType.STRING);
					ctx.Write(entryString.Get());
					break;
				default:
					CF_Log.Error("Failed to write unknown data type %1 for mod %2", entry.Type().ToString(), GetModName());
			}
		}
	}

	// Read and Write functions can't be called, so we can't reset the stream
	void _ResetStream()
	{
		m_Idx = 0;

		if (!m_Mod)
		{
			if (!m_Entries)
			{
				m_Entries = new array<ref CF_ModStorageDataBase>();
				m_MaxIdx = -1;
			}
			return;
		}

		m_CF_Version = VERSION;

		m_Entries = new array<ref CF_ModStorageDataBase>();
		m_MaxIdx = -1;

		m_Data = string.Empty;

		m_HashA = m_Mod.m_CF_HashA;
		m_HashB = m_Mod.m_CF_HashB;

		m_Version = m_Mod.GetStorageVersion();
	}

	void _Insert(bool b)
	{
		m_Entries.Insert(new CF_ModStorageData<bool>(b));
		m_MaxIdx++;
	}

	void _Insert(int i)
	{
		m_Entries.Insert(new CF_ModStorageData<int>(i));
		m_MaxIdx++;
	}

	void _Insert(float f)
	{
		m_Entries.Insert(new CF_ModStorageData<float>(f));
		m_MaxIdx++;
	}

	void _Insert(vector v)
	{
		m_Entries.Insert(new CF_ModStorageData<vector>(v));
		m_MaxIdx++;
	}

	void _Insert(string s)
	{
		m_Entries.Insert(new CF_ModStorageData<string>(s));
		m_MaxIdx++;
	}
};
