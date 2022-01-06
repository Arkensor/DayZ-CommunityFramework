# Modules

## Base Classes

Depending on which `ScriptModule` you desire the module to be in, you change the inheritance to allow for more events. All the possible events in the modules are documented within the the respective classes.

| Script Module | CF Module        |
| ------------- | ---------------- |
| 1_Core        | `CF_ModuleCore`  |
| 2_GameScript  | `CF_ModuleCore`  |
| 3_Game        | `CF_ModuleGame`  |
| 4_World       | `CF_ModuleWorld` |
| 5_Mission     | `CF_ModuleWorld` |

## Events

All events within the modules are by default disabled. Once enabled the event can't be disabled. To enable an event you call the corresponding method starting with 'Enable'. 

| Event Method                              | Enable Method                 | When Fired?                                        | 
| ----------------------------------------- | ----------------------------- | -------------------------------------------------- |
| `CF_ModuleCore::OnMissionStart`           | `EnableMissionStart`          | Called when `MissionBase::OnMissionStart` is ran   |
| `CF_ModuleCore::OnMissionFinish`          | `EnableMissionFinish`         | Called when `MissionBase::OnMissionFinish` is ran  |
| `CF_ModuleCore::OnMissionLoaded`          | `EnableMissionLoaded`         | Called when `MissionBase::OnMissionLoaded` is ran  |
| `CF_ModuleCore::OnUpdate`                 | `EnableUpdate`                | Called when `MissionBase::OnUpdate` is ran         |
| `CF_ModuleCore::OnWorldCleanup`           | `EnableWorldCleanup`          | See: WorldCleaupEventTypeID                        |
| `CF_ModuleCore::OnMPSessionStart`         | `EnableMPSessionStart`        | See: MPSessionStartEventTypeID                     |
| `CF_ModuleCore::OnMPSessionPlayerReady`   | `EnableMPSessionPlayerReady`  | See: MPSessionPlayerReadyEventTypeID               |
| `CF_ModuleCore::OnMPSessionFail`          | `EnableMPSessionFail`         | See: MPSessionFailEventTypeID                      |
| `CF_ModuleCore::OnMPSessionEnd`           | `EnableMPSessionEnd`          | See: MPSessionEndEventTypeID                       |
| `CF_ModuleCore::OnMPConnectAbort`         | `EnableMPConnectAbort`        | See: ConnectingAbortEventTypeID                    |
| `CF_ModuleCore::OnMPConnectionLost`       | `EnableMPConnectionLost`      | See: MPConnectionLostEventTypeID                   |
| `CF_ModuleCore::OnRespawn`                | `EnableRespawn`               | See: RespawnEventTypeID                            |
| `CF_ModuleCore::OnLoginTime`              | `EnableLoginTime`             | See: LoginTimeEventTypeID                          |
| `CF_ModuleCore::OnLoginStatus`            | `EnableLoginStatus`           | See: LoginStatusEventTypeID                        |
| `CF_ModuleCore::OnLogout`                 | `EnableLogout`                | See: LogoutEventTypeID                             |
| `CF_ModuleCore::OnChat`                   | `EnableChat`                  | See: ChatMessageEventTypeID                        |
| `CF_ModuleGame::OnRPC`                    | `EnableRPC`                   | Called when `DayZGame::OnRPC` is ran               |
| `CF_ModuleWorld::OnInvokeConnect`         | `EnableInvokeConnect`         | See: MissionServer::InvokeOnConnect                |
| `CF_ModuleWorld::OnInvokeDisconnect`      | `EnableInvokeDisconnect`      | See: MissionServer::InvokeOnDisconnect             |
| `CF_ModuleWorld::OnClientNew`             | `EnableClientNew`             | See: ClientNewEventTypeID                          |
| `CF_ModuleWorld::OnClientRespawn`         | `EnableClientRespawn`         | See: ClientRespawnEventTypeID                      |
| `CF_ModuleWorld::OnClientReady`           | `EnableClientReady`           | See: ClientReadyEventTypeID                        |
| `CF_ModuleWorld::OnClientPrepare`         | `EnableClientPrepare`         | See: ClientPrepareEventTypeID                      |
| `CF_ModuleWorld::OnClientReconnect`       | `EnableClientReconnect`       | See: ClientReconnectEventTypeID                    |
| `CF_ModuleWorld::OnClientLogout`          | `EnableClientLogout`          | See: ClientDisconnectedEventTypeID                 |
| `CF_ModuleWorld::OnClientDisconnect`      | `EnableClientDisconnect`      | See: MissionServer::PlayerDisconnected             |
| `CF_ModuleWorld::OnClientLogoutCancelled` | `EnableClientLogoutCancelled` | See: LogoutCancelEventTypeID                       |

## Example Module

Below is an example module which will send a message to the player 5 seconds after they log into the server.

```csharp
[CF_RegisterModule(SomeModule)]
class SomeModule : CF_ModuleWorld
{
	override void OnInit()
	{
		super.OnInit();

		// Enable the 'OnInvokeConnect' event
		EnableInvokeConnect();
	}

	override void OnInvokeConnect(Class sender, CF_EventArgs args)
	{
		super.OnInvokeConnect(sender, args);

		auto player = CF_EventPlayerArgs.Cast(args).Player;

		// Send the messsage 5 seconds later, this event can fire before the HUD is loaded and so the message won't be seen
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.SendMessage, 5000, false, player, "Welcome to the server!");
	}

	void SendMessage(PlayerBase player, string message)
	{
		// Send a message by firing the RPC to the player
		GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string>(message), true, player.GetIdentity());
	}
};
```
