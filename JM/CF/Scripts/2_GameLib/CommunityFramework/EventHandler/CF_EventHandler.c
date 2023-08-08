// DO NOT REMOVE!!! For some reason without this there is a compile error cf_eventhandler.c(39): Too many parameters for 'Get' method ...
typedef array<ref ScriptCaller> CF_ScriptInvoker;

class CF_EventHandlerBase //Base class to be able to accept both CF_EventHandler and CF_EventHandlerT as function parameter
{
	protected autoptr CF_ScriptInvoker m_aCallers = {};

	void AddSubscriber(ScriptCaller caller)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "AddSubscriber");
#endif

		// Make sure we do not add the same caller twice
		foreach (ScriptCaller existingCaller : m_aCallers)
		{
			if (existingCaller.IsValid() && existingCaller.Equals(caller))
				return;
		}

		m_aCallers.Insert(caller);
	}

	void RemoveSubscriber(ScriptCaller caller)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "RemoveSubscriber");
#endif

		m_aCallers.RemoveItem(caller);
	}

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
}

class CF_EventHandlerT<Class TEventArgs> extends CF_EventHandlerBase
{
	void Invoke(Class sender = NULL, TEventArgs args = NULL)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Invoke").Add(sender).Add(args);
#endif

		foreach (auto caller : m_aCallers)
		{
			if (caller && caller.IsValid())
				caller.Invoke(sender, args);
		}
	}
}

class CF_EventHandler extends CF_EventHandlerT<CF_EventArgs> 
{
}
