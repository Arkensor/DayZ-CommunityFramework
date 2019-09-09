class JMModuleManagerBase
{
	void JMModuleManagerBase()
	{
		GetLogger().Log( "JMModuleManagerBase::JMModuleManagerBase()", "JM_COT_ModuleFramework" );
	}

	void ~JMModuleManagerBase()
	{
		GetLogger().Log( "JMModuleManagerBase::~JMModuleManagerBase()", "JM_COT_ModuleFramework" );
	}

	void RegisterModules()
	{
		GetLogger().Log( "JMModuleManagerBase::RegisterModules()", "JM_COT_ModuleFramework" );
	}

	void ReloadSettings()
	{
		GetLogger().Log( "JMModuleManagerBase::ReloadSettings()", "JM_COT_ModuleFramework" );
	}

	void OnInit()
	{
		GetLogger().Log( "JMModuleManagerBase::OnInit()", "JM_COT_ModuleFramework" );
	}

	void OnMissionStart()
	{
		GetLogger().Log( "JMModuleManagerBase::OnMissionStart()", "JM_COT_ModuleFramework" );
	}

	void OnMissionFinish()
	{
		GetLogger().Log( "JMModuleManagerBase::OnMissionFinish()", "JM_COT_ModuleFramework" );
	}

	void OnMissionLoaded()
	{
		GetLogger().Log( "JMModuleManagerBase::OnMissionLoaded()", "JM_COT_ModuleFramework" );
	}
    
	void OnUpdate( float timeslice )
	{
		GetLogger().Log( "JMModuleManagerBase::OnUpdate()", "JM_COT_ModuleFramework" );
	}
}

ref JMModuleManagerBase g_cot_ModuleManager;