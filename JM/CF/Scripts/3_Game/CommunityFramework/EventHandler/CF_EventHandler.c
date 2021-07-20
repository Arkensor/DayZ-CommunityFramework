class CF_EventHandler<Class TEventArgs>
{
    protected autoptr ScriptInvoker m_Invoker = new ScriptInvoker();

    void Subscribe(func callback)
    {
        m_Invoker.Insert(callback);
    }

    void Invoke(Class sender, TEventArgs args)
    {
        m_Invoker.Invoke(sender, args);
    }
};
