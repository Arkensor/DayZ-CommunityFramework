#ifdef DAYZ_1_19
typedef ScriptInvoker CF_ScriptInvoker;
#else
typedef array<ref ScriptCaller> CF_ScriptInvoker;
#endif

class CF_EventHandlerBase //Base class to be able to accept both CF_EventHandler and CF_EventHandlerT as function parameter
{
	protected autoptr CF_ScriptInvoker m_Invoker = new CF_ScriptInvoker();

	void CF_EventHandlerBase()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "CF_EventHandlerBase");
#endif

	}

	void ~CF_EventHandlerBase()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "~CF_EventHandlerBase");
#endif

	}
	
#ifdef DAYZ_1_19
	void AddSubscriber(func subscriber)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "AddSubscriber");
#endif

		m_Invoker.Insert(subscriber);
	}

	void RemoveSubscriber(func subscriber)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "RemoveSubscriber");
#endif

		m_Invoker.Remove(subscriber);
	}
#else
	void AddSubscriber(ScriptCaller caller)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "AddSubscriber");
#endif

		m_Invoker.Insert(caller);
	}

	void RemoveSubscriber(ScriptCaller caller)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "RemoveSubscriber");
#endif

		m_Invoker.RemoveItem(caller);
	}
#endif
};

class CF_EventHandlerT<Class TEventArgs> extends CF_EventHandlerBase
{
	void Invoke(Class sender = NULL, TEventArgs args = NULL)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Invoke").Add(sender).Add(args);
#endif

#ifdef DAYZ_1_19
        m_Invoker.Invoke(sender, args);
#else
		foreach (auto invoker : m_Invoker)
		{
			invoker.Invoke(sender, args);
		}
#endif
	}
};

class CF_EventHandler extends CF_EventHandlerT<CF_EventArgs> {};
