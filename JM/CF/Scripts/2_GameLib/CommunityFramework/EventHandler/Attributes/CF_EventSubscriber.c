class CF_EventSubscriber
{
    /**
     * @brief ATTRIBUTE Register a function as subscriber of up to 9 CF_EventHandler instances.
     *                  If you need more than 9, please use the CF_MultiEventSubscriber attribute instead.
     *
     * @code
     * [CF_EventSubscriber(HandlerFunction, Event1, Event2, Event3 ... Event9)]
     * void HandlerFunction(Class sender, CF_EventArgs args) {}
     * @endcode
     *
     * @param subscriber    Function to register as subscriber.
     * @param evt1...9      CF_EventHandler instances to subscribe to.
     * @return void.
     */
    void CF_EventSubscriber(func subscriber,
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
        //Always remove first, to make sure we do not have the same function subscribed twice
        if (evt1){ evt1.RemoveSubscriber(subscriber); evt1.AddSubscriber(subscriber); }
        if (evt2){ evt2.RemoveSubscriber(subscriber); evt2.AddSubscriber(subscriber); }
        if (evt3){ evt3.RemoveSubscriber(subscriber); evt3.AddSubscriber(subscriber); }
        if (evt4){ evt4.RemoveSubscriber(subscriber); evt4.AddSubscriber(subscriber); }
        if (evt5){ evt5.RemoveSubscriber(subscriber); evt5.AddSubscriber(subscriber); }
        if (evt6){ evt6.RemoveSubscriber(subscriber); evt6.AddSubscriber(subscriber); }
        if (evt7){ evt7.RemoveSubscriber(subscriber); evt7.AddSubscriber(subscriber); }
        if (evt8){ evt8.RemoveSubscriber(subscriber); evt8.AddSubscriber(subscriber); }
        if (evt9){ evt9.RemoveSubscriber(subscriber); evt9.AddSubscriber(subscriber); }
    }
};
