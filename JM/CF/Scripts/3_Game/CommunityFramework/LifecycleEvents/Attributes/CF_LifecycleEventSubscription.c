class CF_LifecycleEventSubscription
{
    void CF_LifecycleEventSubscription(CF_EventHandler<CF_EventArgs> lifecycleEvent, func callback)
    {
        lifecycleEvent.Subscribe(callback);
    }
};
