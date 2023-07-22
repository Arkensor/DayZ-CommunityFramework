# LifecycleEvents
The static `CF_LifecycleEvents` class offers different [CF_EventHandler](../EventHandler/index.md) instances that can be subscribed to with custom logic. This provides an easy way to, for example, reset a global cache every time the player switches servers (aka the mission instance is locally recreated).

## Event types
| Module  | Event type       | Event source              | Description                                                      |
| ------- | ---------------- | ------------------------- | ---------------------------------------------------------------- |
| Game    | OnGameCreate     | `DayZGame` constructor    | Once per game launch                                             |
| Game    | OnGameDestroy    | `DayZGame` destructor     | Once when closing the game                                       |
| Mission | OnMissionCreate  | `MissionBase` constructor | Every time a local mission is started or during server join      |
| Mission | OnMissionDestroy | `MissionBase` destructor  | Every time a local mission ends or during disconnect from server |

## Demo
```csharp
class LifecycleInstanceDemo
{
    void LifecycleInstanceDemo()
    {
        CF_LifecycleEvents.OnGameCreate.AddSubscriber(ScriptCaller.Create(this.HandleGameCreate));
    }
    
    void HandleGameCreate()
    {
        Print("LifecycleInstanceDemo::HandleGameCreate");
    }
};
```

```csharp
class LifecycleStaticDemo
{
    [CF_EventSubscriber(ScriptCaller.Create(LifecycleStaticDemo.GameCreate), CF_LifecycleEvents.OnGameCreate)]
    static void GameCreate()
    {
        Print("LifecycleStaticDemo::GameCreate");
    }

    [CF_EventSubscriber(ScriptCaller.Create(LifecycleStaticDemo.GameDestroy), CF_LifecycleEvents.OnGameDestroy)]
    static void GameDestroy()
    {
        Print("LifecycleStaticDemo::GameDestroy");
    }

    [CF_EventSubscriber(ScriptCaller.Create(LifecycleStaticDemo.MissionCreate), CF_LifecycleEvents.OnMissionCreate)]
    static void MissionCreate()
    {
        Print("LifecycleStaticDemo::MissionCreate");
    }

    [CF_EventSubscriber(ScriptCaller.Create(LifecycleStaticDemo.MissionDestroy), CF_LifecycleEvents.OnMissionDestroy)]
    static void MissionDestroy()
    {
        Print("LifecycleStaticDemo::MissionDestroy");
    }

    [CF_EventSubscriber(ScriptCaller.Create(LifecycleStaticDemo.OnePrintToRuleThemAll),
        CF_LifecycleEvents.OnGameCreate,
        CF_LifecycleEvents.OnGameDestroy,
        CF_LifecycleEvents.OnMissionCreate,
        CF_LifecycleEvents.OnMissionDestroy)]
    static void OnePrintToRuleThemAll()
    {
        Print("OnePrintToRuleThemAll");
    }
};
```
