class CF_EventSubscriber
{
    protected static ref map<string, ScriptCaller> m_mSingletons = new map<string, ScriptCaller>();

    /**
     * @brief ATTRIBUTE Register a function as subscriber of up to 9 CF_EventHandler instances.
     *                  If you need more than 9, please use the CF_MultiEventSubscriber attribute instead.
     *
     * @code
     * [CF_EventSubscriber(ScriptCaller.Create(HandlerFunction), Event1, Event2, Event3 ... Event9)]
     * void HandlerFunction(Class sender, CF_EventArgs args) {}
     * @endcode
     *
     * @param subscriber    Function to register as subscriber.
     * @param evt1...9      CF_EventHandler instances to subscribe to.
     * @return void.
     */
    void CF_EventSubscriber(ScriptCaller subscriber,
        CF_EventHandlerBase evt1 = NULL,
        CF_EventHandlerBase evt2 = NULL,
        CF_EventHandlerBase evt3 = NULL,
        CF_EventHandlerBase evt4 = NULL,
        CF_EventHandlerBase evt5 = NULL,
        CF_EventHandlerBase evt6 = NULL,
        CF_EventHandlerBase evt7 = NULL,
        CF_EventHandlerBase evt8 = NULL,
        CF_EventHandlerBase evt9 = NULL)
    {
        UpdateSubscriptions(subscriber, {evt1, evt2, evt3, evt4, evt5, evt6, evt7, evt8, evt9});
    }

    static void UpdateSubscriptions(ScriptCaller subscriber, array<CF_EventHandlerBase> events)
    {
        string stackDump;
        DumpStackString(stackDump);
        int popInternalCallsIdx = stackDump.IndexOfFrom(stackDump.IndexOf("\n") + 1, "\n");
        stackDump = stackDump.Substring(popInternalCallsIdx + 1, stackDump.Length() - (popInternalCallsIdx + 2));

        ScriptCaller existingCaller = m_mSingletons.Get(stackDump);
        if (existingCaller)
        {
            return; // Do not add it twice. Currently we keep the one script caller instance alive via a strong ref.
            
            //foreach(auto removeEvent : events)
            //{
            //    removeEvent.RemoveSubscriber(existingCaller);
            //}
        }

        m_mSingletons.Set(stackDump, subscriber);

        foreach(auto addEvent : events)
        {
            if (addEvent)
                addEvent.AddSubscriber(subscriber);
        }
    }
};
