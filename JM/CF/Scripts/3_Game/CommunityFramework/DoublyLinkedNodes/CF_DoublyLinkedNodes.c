/**
 * @brief a collection of doubly linked nodes (doubly linked list)
 * 
 * @code
 *  class Example
 *  {
 *      static ref CF_DoublyLinkedNodes<Example> s_All = new CF_DoublyLinkedNodes<Example>();
 * 
 *      ref CF_DoublyLinkedNode<Example> m_Node;
 *  
 *      void Example()
 *      {
 *          m_Node = s_All.Add(this);
 *      }
 *  
 *      void ~Example()
 *      {
 *          if (s_All)
 *              s_All.Remove(m_Node);
 *      }
 *  }
 * @endcode
*/
class CF_DoublyLinkedNodes<Class T>
{
	ref CF_DoublyLinkedNode<T> m_Head;
	CF_DoublyLinkedNode<T> m_Current;

	int m_Count;

	ref ScriptInvoker m_OnRemove = new ScriptInvoker;

	void ~CF_DoublyLinkedNodes()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(true, this);
#endif

		if (!g_Game)
			return;

		m_Head = null;
	}

	/**
	 * @brief Add value to collection, automatically creating a wrapping node
	 */
	CF_DoublyLinkedNode<T> Add(T value)
	{
		auto node = new CF_DoublyLinkedNode<T>(value);

		Add(node);

		return node;
	}

	/**
	 * @brief Add node to collection
	 */
	void Add(CF_DoublyLinkedNode<T> node)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(true, this).Add("" + node);
#endif

		node.Link(m_Head, null);

		m_Head = node;

		m_Count++;

#ifdef CF_TRACE_ENABLED
		trace.Debug("Count: %1", "" + m_Count);
#endif
	}

	/**
	 * @brief Remove node from collection
	 */
	void Remove(CF_DoublyLinkedNode<T> node)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(true, this).Add("" + node);
#endif

		if (!node)
			return;

		bool isHead = m_Head == node;

		if (!isHead && node.m_Next == null && node.m_Prev == null)
			return;

		bool isCurrent = m_Current == node;

		auto next = node.m_Next;

		m_OnRemove.Invoke(node);

		delete node;

		if (isHead)
		{
#ifdef CF_TRACE_ENABLED
			trace.Debug("Assigning %1 as head node", "" + next);
#endif
			m_Head = next;
		}

		if (isCurrent)
		{
#ifdef CF_TRACE_ENABLED
			trace.Debug("Assigning %1 as current node", "" + next);
#endif
			m_Current = next;
		}

		m_Count--;

#ifdef CF_TRACE_ENABLED
		trace.Debug("Count: %1", "" + m_Count);
#endif
	}

	/**
	 * @brief processes elements in the linked list.
	 * 
	 * if `limit` is set to a nonzero value, only `n` elements are processed each call.
	 * The value of each node is passed to the callback.
	 * Returns the number of processed elements.
	 */
	int Each(ScriptCaller callback, int limit = 0)
	{
		if (!m_Current)
			m_Current = m_Head;

		//! @note: Enforce garbage collects references to function arguments inside loops after the first iteration,
		//! so we have to assign a local variable and use that instead to avoid premature garbage collection
		ScriptCaller localCallback = callback;

		int count;
		while (m_Current)
		{
			localCallback.Invoke(m_Current.m_Value);
			m_Current = m_Current.m_Next;
			count++;
			if (limit > 0 && count == limit)
				break;
		}

		return count;
	}
}
