class CF_EventHandlerBase //Common baseclass for all templated versions
{
    protected autoptr ScriptInvoker m_Invoker = new ScriptInvoker();

    void Subscribe(func callback)
    {
        m_Invoker.Insert(callback);
    }
};

class CF_EventHandler<Class TEventArgs> extends CF_EventHandlerBase
{
    void Invoke(Class sender, TEventArgs args)
    {
        m_Invoker.Invoke(sender, args);
    }
};
