class CF_MultiEventSubscriber
{
    /**
     * @brief ATTRIBUTE Register a function as subscriber of multiple CF_EventHandler instances.
     *                  If you only need to subscribe to 9 or less instances, use the regular CF_EventSubscriber attribute instead.
     *
     * @code
     * [CF_MultiEventSubscriber(ScriptCaller.Create(HandlerFunction), {Event1, Event2, Event3 ... EventN})]
     * void HandlerFunction(Class sender, CF_EventArgs args) {}
     * @endcode
     *
     * @param subscriber    Function to register as subscriber.
     * @param events        Array of CF_EventHandler instances to subscribe to. Use the static array initializer syntax: {<data here>}.
     * @return void.
     */
    void CF_MultiEventSubscriber(ScriptCaller subscriber, array<CF_EventHandlerBase> events)
    {
        CF_EventSubscriber.UpdateSubscriptions(subscriber, events);
    }
};
