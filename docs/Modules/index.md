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

| Event Method                              | Enable Method                 | When Fired?                                        | Executing Platform | Expected Arguments                                                      | 
| ----------------------------------------- | ----------------------------- | -------------------------------------------------- | ------------------ | ----------------------------------------------------------------------- |
| `CF_ModuleCore::OnMissionStart`           | `EnableMissionStart`          | Called when `MissionBase::OnMissionStart` is ran   | ALL                | `CF_EventArgs`                                                          |
| `CF_ModuleCore::OnMissionFinish`          | `EnableMissionFinish`         | Called when `MissionBase::OnMissionFinish` is ran  | ALL                | `CF_EventArgs`                                                          |
| `CF_ModuleCore::OnMissionLoaded`          | `EnableMissionLoaded`         | Called when `MissionBase::OnMissionLoaded` is ran  | ALL                | `CF_EventArgs`                                                          |
| `CF_ModuleCore::OnUpdate`                 | `EnableUpdate`                | Called when `MissionBase::OnUpdate` is ran         | ALL                | `CF_EventArgs`, `CF_EventUpdateArgs`                                    |
| `CF_ModuleCore::OnWorldCleanup`           | `EnableWorldCleanup`          | See: WorldCleaupEventTypeID                        | ALL                | `CF_EventArgs`                                                          |
| `CF_ModuleCore::OnMPSessionStart`         | `EnableMPSessionStart`        | See: MPSessionStartEventTypeID                     | Client             | `CF_EventArgs`                                                          |
| `CF_ModuleCore::OnMPSessionPlayerReady`   | `EnableMPSessionPlayerReady`  | See: MPSessionPlayerReadyEventTypeID               | Client             | `CF_EventArgs`                                                          |
| `CF_ModuleCore::OnMPSessionFail`          | `EnableMPSessionFail`         | See: MPSessionFailEventTypeID                      | Client             | `CF_EventArgs`                                                          |
| `CF_ModuleCore::OnMPSessionEnd`           | `EnableMPSessionEnd`          | See: MPSessionEndEventTypeID                       | Client             | `CF_EventArgs`                                                          |
| `CF_ModuleCore::OnMPConnectAbort`         | `EnableMPConnectAbort`        | See: ConnectingAbortEventTypeID                    | Client             | `CF_EventArgs`                                                          |
| `CF_ModuleCore::OnMPConnectionLost`       | `EnableMPConnectionLost`      | See: MPConnectionLostEventTypeID                   | Client             | `CF_EventArgs`, `CF_EventTimeArgs`                                      |
| `CF_ModuleCore::OnRespawn`                | `EnableRespawn`               | See: RespawnEventTypeID                            | Client             | `CF_EventArgs`, `CF_EventTimeArgs`                                      |
| `CF_ModuleCore::OnLoginTime`              | `EnableLoginTime`             | See: LoginTimeEventTypeID                          | Client             | `CF_EventArgs`, `CF_EventTimeArgs`                                      |
| `CF_ModuleCore::OnLoginStatus`            | `EnableLoginStatus`           | See: LoginStatusEventTypeID                        | Client             | `CF_EventArgs`, `CF_EventLoginArgs`                                     |
| `CF_ModuleCore::OnLogout`                 | `EnableLogout`                | See: LogoutEventTypeID                             | Client             | `CF_EventArgs`, `CF_EventTimeArgs`                                      |
| `CF_ModuleCore::OnChat`                   | `EnableChat`                  | See: ChatMessageEventTypeID                        | Client             | `CF_EventArgs`, `CF_EventChatArgs`                                      |
| `CF_ModuleGame::OnRPC`                    | `EnableRPC`                   | Called when `DayZGame::OnRPC` is ran               | ALL                | `CF_EventArgs`, `CF_EventRPCArgs`                                       |
| `CF_ModuleWorld::OnInvokeConnect`         | `EnableInvokeConnect`         | Called from `MissionServer::InvokeOnConnect`       | Server             | `CF_EventArgs`, `CF_EventPlayerArgs`                                    |
| `CF_ModuleWorld::OnInvokeDisconnect`      | `EnableInvokeDisconnect`      | Called from `MissionServer::InvokeOnDisconnect`    | Server             | `CF_EventArgs`, `CF_EventPlayerArgs`                                    |
| `CF_ModuleWorld::OnClientNew`             | `EnableClientNew`             | See: ClientNewEventTypeID                          | Server             | `CF_EventArgs`, `CF_EventPlayerArgs`, `CF_EventNewPlayerArgs`           |
| `CF_ModuleWorld::OnClientRespawn`         | `EnableClientRespawn`         | See: ClientRespawnEventTypeID                      | Server             | `CF_EventArgs`, `CF_EventPlayerArgs`                                    |
| `CF_ModuleWorld::OnClientReady`           | `EnableClientReady`           | See: ClientReadyEventTypeID                        | Server             | `CF_EventArgs`, `CF_EventPlayerArgs`                                    |
| `CF_ModuleWorld::OnClientPrepare`         | `EnableClientPrepare`         | See: ClientPrepareEventTypeID                      | Server             | `CF_EventArgs`, `CF_EventPlayerPrepareArgs`                             |
| `CF_ModuleWorld::OnClientReconnect`       | `EnableClientReconnect`       | See: ClientReconnectEventTypeID                    | Server             | `CF_EventArgs`, `CF_EventPlayerArgs`                                    |
| `CF_ModuleWorld::OnClientLogout`          | `EnableClientLogout`          | See: ClientDisconnectedEventTypeID                 | Server             | `CF_EventArgs`, `CF_EventPlayerArgs`, `CF_EventPlayerDisconnectedArgs`  |
| `CF_ModuleWorld::OnClientDisconnect`      | `EnableClientDisconnect`      | Called from `MissionServer::PlayerDisconnected`    | Server             | `CF_EventArgs`, `CF_EventPlayerArgs`, `CF_EventPlayerDisconnectedArgs`  |
| `CF_ModuleWorld::OnClientLogoutCancelled` | `EnableClientLogoutCancelled` | See: LogoutCancelEventTypeID                       | Server             | `CF_EventArgs`, `CF_EventPlayerArgs`                                    |

`See: X` refer to all events originating from `DayZGame::OnEvent`

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

## Variables

Similiar to what is found in [EntityAI](https://github.com/Thurston00/DayZSAEnfScript/blob/8b13d29719fb597de74057ecd4de80ef69e1dfb5/scripts/3_Game/Entities/EntityAI.c#L1747), modules can contain variables that can be synchronized over the network from the server to every client.

A basic implementation for the modules is below. For more advanced examples checkout [Networked Variables](../NetworkedVariables/index.md).

```csharp
[CF_RegisterModule(SomeModule)]
class SomeModule : CF_ModuleWorld
{
	private float m_ModuleTime;
	private float m_ModuleTimeSynch;

	override void OnInit()
	{
		super.OnInit();

		RegisterNetSyncVariable("m_ModuleTimeSynch");

		EnableUpdate();
	}

	override void OnVariablesSynchronized(Class sender, CF_EventArgs args)
	{
		super.OnVariablesSynchronized(sender, args);
		
		Print("The client module is at " + m_ModuleTime);
		Print("The server module is at " + m_ModuleTimeSynch);
	}

	override void OnUpdate(Class sender, CF_EventArgs args)
	{
		auto update = CF_EventUpdateArgs.Cast(args);

		m_ModuleTime += update.DeltaTime;

		if (GetGame().IsServer())
		{
			m_ModuleTimeSynch += update.DeltaTime;
			SetSynchDirty();
		}
	}
};
```
