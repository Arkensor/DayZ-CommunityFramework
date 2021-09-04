class CF_Map<Class TKey, Class TValue> : CF_Collection
{
	private ref map<autoptr TKey, int> m_DataMap = new map<autoptr TKey, int>();
	private ref array<autoptr TKey> m_Keys = new array<autoptr TKey>();
	private ref array<autoptr TValue> m_Values = new array<autoptr TValue>();
	private TValue m_NullValue;

	void CF_Map()
	{
		#ifdef COMPONENT_SYSTEM
		CF_MVVM._CheckInit();
		#endif

		typename t = TValue;
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, string.Format("CF_Map<%1>", t));
		#endif

		m_Converter = CF_TypeConverters.Create(t);

		CF_Log.Info("m_Converter=%1", "" + m_Converter);
	}

	override string ToStr()
	{
		string str = super.ToStr();
		str += "Count: " + Count();
		for (int i = 0; i < Count(); i++)
		{
			str += " " + m_Keys[i] + ":";
			str += " " + m_Values[i];
		}
		return str;
	}

	override CF_TypeConverter GetConverter(int index)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "GetConverter").Add(index);
		#endif

		g_Script.CallFunction(m_Converter, "Set", null, m_Values[index]);
		return m_Converter;
	}

	override int Count()
	{
		return m_Values.Count();
	}

	TValue Get(TKey key)
	{
		int index = m_DataMap[key];
		if (!m_DataMap.Find(key, index)) return m_NullValue;
		return m_Values[index];
	}

	bool Find(TKey key, out TValue val)
	{
		int idx;
		if (m_DataMap.Find(key, idx))
		{
			val = m_Values[idx];
			return true;
		}

		return false;
	}

	TValue GetElement(int index)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "GetElement").Add(index);
		#endif
		return m_Values[index];
	}

	TKey GetKey(int i)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "GetKey").Add(i);
		#endif
		return m_Keys[i];
	}

	void Set(TKey key, TValue value)
	{
		if (Contains(key))
		{
			m_Values[m_DataMap[key]] = value;
		}
		else
		{
			int idx = m_Values.Count();
			m_Keys.Insert(key);
			m_Values.Insert(value);
			m_DataMap.Insert(key, idx);
		}
	}

	void Remove(TKey key)
	{
		int index = m_DataMap[key];
		
		TKey replaced = m_Keys[m_Keys.Count() - 1];

		m_Keys.Remove(index);
		m_Values.Remove(index);
		
		m_DataMap.Remove(key);

		if (m_Keys.Count() > 0 && index < m_Keys.Count())
		{
			m_DataMap[replaced] = index;
		}
	}

	void RemoveElement(int index)
	{
		Remove(GetKey(index));
	}

	bool Contains(TKey key)
	{
		return m_DataMap.Contains(key);
	}

	void Insert(TKey key, TValue value)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Insert").Add(key).Add(value);
		#endif
		
		Set(key, value);
	}

	void Clear()
	{
		m_Values.Clear();
		m_Keys.Clear();
		m_DataMap.Clear();
	}

	array<TKey> GetKeyArray()
	{
		array<TKey> result();
		result.Resize(m_Keys.Count());
		for (int i = 0; i < m_Keys.Count(); i++)
		{
			result[i] = m_Keys[i];
		}
		return result;
	}

	array<TValue> GetValueArray()
	{
		array<TValue> result();
		result.Resize(m_Values.Count());
		for (int i = 0; i < m_Values.Count(); i++)
		{
			result[i] = m_Values[i];
		}
		return result;
	}
};