class CF_DoublyLinkedNode<Class T>
{
	ref CF_DoublyLinkedNode<T> m_Next;
	ref CF_DoublyLinkedNode<T> m_Prev;

	ref T m_Value;

	void CF_DoublyLinkedNode(T value)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(true, this).Add("" + value);
#endif

		m_Value = value;
	}

	void ~CF_DoublyLinkedNode()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(true, this);
#endif

		if (!g_Game)
			return;

		Unlink();
	}

	/**
	 * @brief Link two nodes
	 */
	void Link(CF_DoublyLinkedNode<T> next, CF_DoublyLinkedNode<T> prev)
	{
		if (next == this || prev == this || (next != null && next == prev))
		{
			Error(string.Format("Trying to create circular reference (next=%1, prev=%2)", next, prev));
			return;
		}

		m_Next = next;
		m_Prev = prev;

		if (next)
			next.m_Prev = this;

		if (prev)
			prev.m_Next = this;
	}

	/**
	 * @brief Unlink this node from adjacent nodes
	 */
	void Unlink()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(true, this);
#endif

		T value;
		m_Value = value;

		if (m_Next)
		{
#ifdef CF_TRACE_ENABLED
			trace.Debug("Assigning %1 as prev node to next node %2", "" + m_Prev, "" + m_Next);
#endif
			m_Next.m_Prev = m_Prev;
		}

		if (m_Prev)
		{
#ifdef CF_TRACE_ENABLED
			trace.Debug("Assigning %1 as next node to prev node %2", "" + m_Next, "" + m_Prev);
#endif
			m_Prev.m_Next = m_Next;
		}

		m_Next = null;
		m_Prev = null;
	}
}
