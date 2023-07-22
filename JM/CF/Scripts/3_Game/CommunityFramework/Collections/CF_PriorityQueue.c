class CF_PriorityQueue<Class T, Class Comparable> : CF_Collection
{
	protected ref Param2<T, Comparable> m_Data[256];

	void CF_PriorityQueue()
	{
		typename t = T;
		m_Converter = CF_TypeConverter.Get(t);
	}

	override string GetDebugName()
	{
		string str = super.GetDebugName();
		str += "Count: " + m_Count;
		for (int i = 0; i < m_Count; i++)
		{
			str += " " + m_Data[i];
		}
		return str;
	}

	override CF_TypeConverterBase GetConverter(int index)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "GetConverter").Add(index);
		#endif

		g_Script.CallFunction(m_Converter, "Set", null, m_Data[index]);
		return m_Converter;
	}

	void Enqueue(T item, Comparable priority)
	{
		m_Data[m_Count] = new Param2<ref T, Comparable>(item, priority);
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

		m_Count--;

		m_Data[bestIndex] = m_Data[m_Count];
		m_Data[m_Count] = null;

		return bestItem;
	}
}