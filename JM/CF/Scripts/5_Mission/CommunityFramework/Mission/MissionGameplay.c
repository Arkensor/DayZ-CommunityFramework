modded class MissionGameplay
{
	protected bool m_bLoaded;

	void MissionGameplay()
	{
		m_bLoaded = false;
		
		GetRPCManager().AddRPC( "CF", "LoadDebugging", this, SingeplayerExecutionType.Client );
	}

	void ~MissionGameplay()
	{
	}

	override void OnInit()
	{
		super.OnInit();
	}

	override void OnMissionStart()
	{
		super.OnMissionStart();
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();
	}

	void OnMissionLoaded()
	{
	}

	override void OnUpdate( float timeslice )
	{
		if( !m_bLoaded && !GetDayZGame().IsLoading() )
		{
			m_bLoaded = true;
			OnMissionLoaded();
		} else {
			super.OnUpdate( timeslice );
		}
	}
	
	void LoadDebugging( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
		Print("test");
		Param1< ref Debugging > data;
		Print(data);
		Print(type);
		if ( type == CallType.Client && ctx.Read( data ) ) 
		{
			Print(data.param1);
			g_Debugging = data.param1;
			Print(g_Debugging);
		}
	}
}
