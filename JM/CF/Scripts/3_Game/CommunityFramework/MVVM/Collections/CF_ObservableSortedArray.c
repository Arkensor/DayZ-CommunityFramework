class CF_ObservableSortedArray<Class T> : CF_ObservableCollection
{
	private ref array<autoptr T> m_Data = new array<autoptr T>();
	private ref array<int> m_Sort = new array<int>();

	void CF_ObservableSortedArray()
	{
#ifdef COMPONENT_SYSTEM
		CF_MVVM._CheckInit();
#endif

		typename t = T;
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_0(this, string.Format("CF_ObservableArray<%1>", t));
#endif

		OverrideConverter();
	}

	override string GetDebugName()
	{
		string str = super.GetDebugName();
		str += "Count: " + m_Data.Count();
		for (int i = 0; i < m_Data.Count(); i++)
		{
			str += " " + m_Sort[i] + "=" + m_Data[i];
		}
		return str;
	}

	override CF_TypeConverterBase GetConverter(int index)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(this, "GetConverter").Add(index);
#endif

		g_Script.CallFunction(m_Converter, "Set", null, m_Data[index]);
		return m_Converter;
	}

	override void OverrideConverter(CF_TypeConverterBase converter = null)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(this, "OverrideConverter").Add(converter);
#endif

		if (!converter)
		{
			typename t = T;
			m_Converter = CF_TypeConverter.Get(t);
			return;
		}

		m_Converter = converter;
	}

	override int Count()
	{
		return m_Data.Count();
	}

	override void Clear()
	{
		m_Data.Clear();

		NotifyCollectionChanged(new CF_CollectionClearEventArgs());
	}

	void Insert(T value, int sort)
	{
		int index = 0;
		while (index < m_Count)
		{
			if (sort >= m_Sort[index])
			{
				break;
			}

			index++;
		}

		if (index >= m_Count)
		{
			index = m_Data.Insert(value);
			if (index != m_Sort.Insert(sort))
			{
				CF_Log.Error("Count mismatch");
			}

			NotifyCollectionChanged(new CF_CollectionInsertEventArgs(index));
		}
		else
		{
			m_Count = m_Data.InsertAt(value, index);
			if (m_Count != m_Sort.InsertAt(sort, index))
			{
				CF_Log.Error("Count mismatch");
			}

			NotifyCollectionChanged(new CF_CollectionInsertAtEventArgs(index));
		}

		m_Count = m_Data.Count();
	}

	void Remove(int index)
	{
		if (m_Data.Count() <= 1)
		{
			NotifyCollectionChanged(new CF_CollectionRemoveEventArgs(index));
		}

		m_Data.RemoveOrdered(index);
		m_Sort.RemoveOrdered(index);

		if (m_Data.Count() > 0 && index < m_Data.Count())
		{
			NotifyCollectionChanged(new CF_CollectionSetEventArgs(index));
		}

		m_Count = m_Data.Count();
	}

	void Resize(int newSize)
	{
		m_Data.Resize(newSize);
		m_Sort.Resize(newSize);
	}
};
