class CF_ObservableMap<Class TKey, Class TValue> : CF_ObservableCollection
{
	private ref map<autoptr TKey, int> m_DataMap = new map<autoptr TKey, int>();
	private ref array<autoptr TKey> m_Keys = new array<autoptr TKey>();
	private ref array<autoptr TValue> m_Values = new array<autoptr TValue>();

	void CF_ObservableMap()
	{
		#ifdef COMPONENT_SYSTEM
		CF_MVVM._CheckInit();
		#endif

		typename t = TValue;
		CF_Trace trace(this, string.Format("CF_ObservableMap<%1>", "" + t));

		m_Converter = CF.TypeConverters.Create(t);

		CF.Log.Info("m_Converter=%1", "" + m_Converter);
	}

	override string String()
	{
		string str = super.String();
		str += "Count: " + m_Count;
		for (int i = 0; i < m_Count; i++)
		{
			str += " " + m_Keys[i] + ":";
			str += " " + m_Values[i];
		}
		return str;
	}

	override CF_TypeConverter GetConverter(int index)
	{
		CF_Trace trace(this, "GetConverter", "" + index);

		g_Script.CallFunction(m_Converter, "Set", null, m_Values[index]);
		return m_Converter;
	}

	override int Count()
	{
		return m_Values.Count();
	}

	TValue Get(TKey key)
	{
		return m_Values[m_DataMap[key]];
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
		return m_Values[index];
	}

	TKey GetKey(int i)
	{
		return m_Keys[i];
	}

	void Set(TKey key, TValue value)
	{
		if (Contains(key))
		{
			m_Values[m_DataMap[key]] = value;
			NotifyCollectionChanged(new CF_CollectionSetEventArgs(m_DataMap[key]));
		}
		else
		{
			int idx = m_Values.Count();
			m_Keys.Insert(key);
			m_Values.Insert(value);
			m_DataMap.Insert(key, idx);
			NotifyCollectionChanged(new CF_CollectionInsertEventArgs(m_DataMap[key]));
		}
	}

	void Remove(TKey key)
	{
		int index = m_DataMap[key];

		if (m_Keys.Count() <= 1) NotifyCollectionChanged(new CF_CollectionRemoveEventArgs(index));
		
		TKey replaced = m_Keys[m_Keys.Count() - 1];

		m_Keys.Remove(index);
		m_Values.Remove(index);
		
		m_DataMap.Remove(key);

		if (m_Keys.Count() > 0 && index < m_Data.Count())
		{
			m_DataMap[replaced] = index;
			NotifyCollectionChanged(new CF_CollectionSetEventArgs(index));
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
		Set(key, value);
	}

	void Clear()
	{
		NotifyCollectionChanged(new CF_CollectionClearEventArgs());

		m_Values.Clear();
		m_Keys.Clear();
		m_DataMap.Clear();
	}
};