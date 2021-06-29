/**
 * Do not mod this class. Modding this class defeats the purpose of this being in Community Framework.
 * You will break persistence if you mod it. Make a pull request here https://github.com/Jacob-Mango/DayZ-Community-Framework/pulls
 */
class CF_ModStorage
{
	static const int VERSION = 4;

	protected int m_Version;

	protected ModStructure m_Mod;
	protected ref CF_ModHash m_Hash;

	private autoptr array<ref CF_ModStorage_Data> m_Data = new array<ref CF_ModStorage_Data>();
	private int m_Index;

	void CF_ModStorage(ref ModStructure mod, ref CF_ModHash hashOverride = NULL)
	{
		m_Version = -1;
		m_Mod = mod;
		if (m_Mod)
		{
			m_Version = m_Mod.GetStorageVersion();
			m_Hash = m_Mod.GetHash();
		}
		else
		{
			m_Hash = hashOverride;
		}
	}

	int GetVersion()
	{
		return m_Version;
	}

	ModStructure GetMod()
	{
		return m_Mod;
	}

	void Clear()
	{
		m_Index = 0;
		m_Data.Clear();
	}

	/**
	 * @note Mod name is written here to the context
	 * @note Make sure to write CF_ModStorage.VERSION before calling ::Save(...)
	 * 
	 * @param ctx The context which is being written to
	 */
	void Save(ParamsWriteContext ctx)
	{
		m_Hash.Save(ctx);

		ctx.Write(m_Version);

		int count = m_Data.Count();
		ctx.Write(count);

		for (int i = 0; i < count; i++)
		{
			string type = m_Data[i].GetType().ToString();
			ctx.Write(type);
			m_Data[i].Write(ctx);
		}
	}

	/**
	 * @note Mod name is read in the entity OnStoreLoad method.
	 * @note Make sure to read the version variable before calling ::Load(..., modStorageVersion)
	 * 
	 * @param ctx The context which is being read
	 * @param modStorageVersion Version of ModStorage being loaded
	 */
	bool Load(ParamsReadContext ctx, int modStorageVersion)
	{
		Clear();

		int currVersion = m_Version;
		ctx.Read(m_Version);

		int count;
		ctx.Read(count);

		for (int i = 0; i < count; i++)
		{
			m_Data.Insert(CF_ModStorage_Converter.Read(ctx));
		}

		return true;
	}

	ref CF_ModStorage_Data ReadRaw()
	{
		if (m_Index >= m_Data.Count()) return null;

		return m_Data[m_Index++];
	}

	void WriteRaw(ref CF_ModStorage_Data data)
	{
		data.OnSet();
		m_Data.Insert(data);
	}

	bool Skip(int skip = 1)
	{
		m_Index += --skip; //! decrement here because ReadRaw increments automatically by 1
		return ReadRaw() != null;
	}

	bool Read(out bool value)
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if (!data) return false;

		value = Param1<bool>.Cast(data.Get()).param1;

		return true;
	}

	bool Read(out int value)
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if (!data) return false;

		value = Param1<int>.Cast(data.Get()).param1;

		return true;
	}

	bool Read(out float value)
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if (!data) return false;

		value = Param1<float>.Cast(data.Get()).param1;

		return true;
	}

	bool Read(out vector value)
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if (!data) return false;

		value = Param1<vector>.Cast(data.Get()).param1;

		return true;
	}

	bool Read(out string value)
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if (!data) return false;

		value = Param1<string>.Cast(data.Get()).param1;

		return true;
	}

	/**
	 * @param value		Class variable for read data to be assigned to
	 *
	 * @note value can't be null and can't be marked out/inout
	 */
	bool Read(ref Class value)
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if (!data) return false;

		if (!value) return data.IsNull();

		return data.Get(value);
	}

	bool Read(ref TBoolArray value)
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if (!data) return false;

		Class cls = value;
		if (!data.Get(cls)) return false;
		
		value = TBoolArray.Cast(cls);
		return true;
	}

	bool Read(ref TIntArray value)
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if (!data) return false;

		Class cls = value;
		if (!data.Get(cls)) return false;

		value = TIntArray.Cast(cls);
		return true;
	}

	bool Read(ref TFloatArray value)
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if (!data) return false;

		Class cls = value;
		if (!data.Get(cls)) return false;

		value = TFloatArray.Cast(cls);
		return true;
	}

	bool Read(ref TVectorArray value)
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if (!data) return false;

		Class cls = value;
		if (!data.Get(cls)) return false;

		value = TVectorArray.Cast(cls);
		return true;
	}

	bool Read(ref TStringArray value)
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if (!data) return false;

		Class cls = value;
		if (!data.Get(cls)) return false;

		value = TStringArray.Cast(cls);
		return true;
	}

	void Write(bool value)
	{
		WriteRaw(new CF_ModStorage_Data_Primitive<bool>(value));
	}

	void Write(int value)
	{
		WriteRaw(new CF_ModStorage_Data_Primitive<int>(value));
	}

	void Write(float value)
	{
		WriteRaw(new CF_ModStorage_Data_Primitive<float>(value));
	}

	void Write(vector value)
	{
		WriteRaw(new CF_ModStorage_Data_Primitive<vector>(value));
	}

	void Write(string value)
	{
		WriteRaw(new CF_ModStorage_Data_Primitive<string>(value));
	}

	void Write(TBoolArray value)
	{
		WriteRaw(new CF_ModStorage_Data_Array<bool>(value));
	}

	void Write(TIntArray value)
	{
		WriteRaw(new CF_ModStorage_Data_Array<int>(value));
	}

	void Write(TFloatArray value)
	{
		WriteRaw(new CF_ModStorage_Data_Array<float>(value));
	}

	void Write(TVectorArray value)
	{
		WriteRaw(new CF_ModStorage_Data_Array<vector>(value));
	}

	void Write(TStringArray value)
	{
		WriteRaw(new CF_ModStorage_Data_Array<string>(value));
	}

	void Write(Class value)
	{
		WriteRaw(new CF_ModStorage_Data_Class(value));
	}
};