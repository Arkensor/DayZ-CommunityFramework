class CF_EventHandlerBase //Base class to be able to accept both CF_EventHandler and CF_EventHandlerT as function parameter
{
    protected autoptr ScriptInvoker m_Invoker = new ScriptInvoker();

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
};

class CF_EventHandlerT<Class TEventArgs> extends CF_EventHandlerBase
{
    void Invoke(Class sender = NULL, TEventArgs args = NULL)
    {
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Invoke").Add(sender).Add(args);
#endif

        m_Invoker.Invoke(sender, args);
    }
};

class CF_EventHandler extends CF_EventHandlerT<CF_EventArgs> {};
