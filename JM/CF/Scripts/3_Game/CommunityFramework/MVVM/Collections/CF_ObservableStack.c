class CF_ObservableStack<Class T> : CF_ObservableCollection
{
	private	T m_Data[256];
	private int m_Count;

	void CF_ObservableStack()
	{
		typename t = T;
		m_Converter = CF.TypeConverters.Create(t);
	}

	override string String()
	{
		string str = super.String();
		str += "Count: " + m_Count;
		for (int i = 0; i < m_Count; i++)
		{
			str += " " + m_Data[i];
		}
		return str;
	}

	override CF_TypeConverter GetConverter(int index)
	{
		CF_Trace trace(this, "GetConverter", "" + index);

		g_Script.CallFunction(m_Converter, "Set", null, m_Data[index]);
		return m_Converter;
	}

	T Pop()
	{
		T value;

		if (m_Count <= 0)
		{
			m_Count = 0;
		}
		else
		{
			value = m_Data[m_Count - 1];

			NotifyCollectionChanged(new CF_CollectionRemoveEventArgs(m_Count - 1));

			m_Count--;
		}

		return value;
	}

	T Peek()
	{
		return m_Data[m_Count - 1];
	}

	T Push(T value)
	{
		m_Data[m_Count] = value;

		NotifyCollectionChanged(new CF_CollectionInsertEventArgs(m_Count));

		m_Count++;

		return value;
	}

	array<T> ToArray()
	{
		array<T> arr = new array<T>();
		for (int i = 0; i < m_Count; i++)
			arr.Insert(m_Data[i]);
		return arr;
	}

	void Clear()
	{
		m_Count = 0;

		NotifyCollectionChanged(new CF_CollectionClearEventArgs());
	}

	T Get(int index)
	{
		return m_Data[index];
	}

	void Set(int index, T value)
	{
		m_Data[index] = value;

		NotifyCollectionChanged(new CF_CollectionSetEventArgs(index));
	}

	override int Count()
	{
		return m_Count;
	}
};