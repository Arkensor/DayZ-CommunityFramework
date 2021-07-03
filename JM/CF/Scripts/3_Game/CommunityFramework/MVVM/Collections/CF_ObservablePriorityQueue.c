class CF_ObservablePriorityQueue<Class T> : CF_ObservableCollection
{
	private	ref Param2<ref T, float> m_Data[256];
	private int m_Count;

	void CF_ObservablePriorityQueue()
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

	override int Count()
	{
		return elements.Count();
	}

	void Enqueue(T item, float priority)
	{
		m_Data[m_Count] = new Param2<ref T, float>(item, priority);
		
		NotifyCollectionChanged(new CF_CollectionInsertEventArgs(m_Count));

		m_Count++;
	}

	T Dequeue()
	{
		int bestIndex = 0;
		
		for (int i = 0; i < m_Count; i++)
		{
			if (m_Data[i].param2 < m_Data[bestIndex].param2)
			{
				bestIndex = i;
			}
		}

		T bestItem = m_Data[bestIndex].param1;

		NotifyCollectionChanged(new CF_CollectionRemoveEventArgs(bestIndex));

		m_Count--;

		//NotifyCollectionChanged(new CF_CollectionRemoveEventArgs(m_Count));

		m_Data[bestIndex] = m_Data[m_Count];
		m_Data[m_Count] = null;

		if (bestIndex < m_Count && m_Count > 0)
		{
			NotifyCollectionChanged(new CF_CollectionSetEventArgs(bestIndex));
		}

		return bestItem;
	}
}