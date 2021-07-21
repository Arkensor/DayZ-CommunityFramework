class CF_EventHandlerBase //Base class to be able to accept both CF_EventHandler and CF_EventHandlerT as function parameter
{
    protected autoptr ScriptInvoker m_Invoker = new ScriptInvoker();

    void Subscribe(func callback)
    {
        m_Invoker.Insert(callback);
    }
};

class CF_EventHandlerT<Class TEventArgs> extends CF_EventHandlerBase
{
    void Invoke(Class sender, TEventArgs args)
    {
        m_Invoker.Invoke(sender, args);
    }
};

class CF_EventHandler extends CF_EventHandlerT<CF_EventArgs> {};
