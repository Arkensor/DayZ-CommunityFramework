class CF_EventSubscription
{
    void CF_EventSubscription(CF_EventHandlerBase eventHandler, func callback)
    {
        eventHandler.Subscribe(callback);
    }
};
