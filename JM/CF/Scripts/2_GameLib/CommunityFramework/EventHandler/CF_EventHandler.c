class CF_EventHandlerBase //Base class to be able to accept both CF_EventHandler and CF_EventHandlerT as function parameter
{
    protected autoptr ScriptInvoker m_Invoker = new ScriptInvoker();

    void AddSubscriber(func subscriber)
    {
        m_Invoker.Insert(subscriber);
    }

    void RemoveSubscriber(func subscriber)
    {
        m_Invoker.Remove(subscriber);
    }
};

class CF_EventHandlerT<Class TEventArgs> extends CF_EventHandlerBase
{
    void Invoke(Class sender = NULL, TEventArgs args = NULL)
    {
        m_Invoker.Invoke(sender, args);
    }
};

class CF_EventHandler extends CF_EventHandlerT<CF_EventArgs> {};
