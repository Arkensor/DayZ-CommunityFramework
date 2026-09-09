modded class ModItemRegisterCallbacks
{
	ref JMAnimRegister m_JMAnimRegister = new JMAnimRegister();

	override void RegisterEmptyHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterEmptyHanded( pType, pBehavior );

		m_JMAnimRegister.OnRegisterEmptyHanded( pType, pBehavior );
		m_JMAnimRegister.RegisterEmptyHanded( pType, pBehavior );
	}

    override void RegisterOneHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterOneHanded( pType, pBehavior );

		m_JMAnimRegister.OnRegisterOneHanded( pType, pBehavior );
		m_JMAnimRegister.RegisterOneHanded( pType, pBehavior );
	}

    override void RegisterTwoHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterTwoHanded( pType, pBehavior );

		m_JMAnimRegister.OnRegisterTwoHanded( pType, pBehavior );
		m_JMAnimRegister.RegisterTwoHanded( pType, pBehavior );
	}

    override void RegisterRestrained( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterRestrained( pType, pBehavior );

		m_JMAnimRegister.OnRegisterRestrained( pType, pBehavior );
		m_JMAnimRegister.RegisterRestrained( pType, pBehavior );
	}

    override void RegisterSurrender( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterSurrender( pType, pBehavior );

		m_JMAnimRegister.OnRegisterSurrender( pType, pBehavior );
		m_JMAnimRegister.RegisterSurrender( pType, pBehavior );
	}

    override void RegisterHeavy( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterHeavy( pType, pBehavior );

		m_JMAnimRegister.OnRegisterHeavy( pType, pBehavior );
		m_JMAnimRegister.RegisterHeavy( pType, pBehavior );
	}

    override void RegisterPistol( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterPistol( pType, pBehavior );

		m_JMAnimRegister.OnRegisterPistol( pType, pBehavior );
		m_JMAnimRegister.RegisterPistol( pType, pBehavior );
	}

    override void RegisterFireArms( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterFireArms( pType, pBehavior );

		m_JMAnimRegister.OnRegisterFireArms( pType, pBehavior );
		m_JMAnimRegister.RegisterFireArms( pType, pBehavior );
	}

    override void RegisterArcheryItem( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterArcheryItem( pType, pBehavior );

		m_JMAnimRegister.OnRegisterArcheryItem( pType, pBehavior );
		m_JMAnimRegister.RegisterArcheryItem( pType, pBehavior );
	}

    override void RegisterLauncher( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterLauncher( pType, pBehavior );

		m_JMAnimRegister.OnRegisterLauncher( pType, pBehavior );
		m_JMAnimRegister.RegisterLauncher( pType, pBehavior );
	}

	override void RegisterCustom( DayZPlayerType pType )
	{
		super.RegisterCustom( pType );

		m_JMAnimRegister.OnRegisterCustom( pType );
		m_JMAnimRegister.RegisterCustom( pType );
	}

	override void CustomBoneRemapping( DayZPlayerType pType )
	{
		super.CustomBoneRemapping( pType );

		m_JMAnimRegister.OnBoneRemapping( pType );
		m_JMAnimRegister.BoneRemapping( pType );
	}
};

// 107 compatibility - DEPRECATED, should no longer be used
class JMAnimRegister
{
	static JMAnimRegister Register( DayZPlayerType pType );
	void RegisterEmptyHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void OnRegisterEmptyHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void RegisterOneHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void OnRegisterOneHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void RegisterTwoHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void OnRegisterTwoHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void RegisterRestrained( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void OnRegisterRestrained( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void RegisterSurrender( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void OnRegisterSurrender( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void RegisterHeavy( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void OnRegisterHeavy( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void RegisterPistol( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void OnRegisterPistol( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void RegisterFireArms( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void OnRegisterFireArms( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void RegisterArcheryItem( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void OnRegisterArcheryItem( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void RegisterLauncher( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void OnRegisterLauncher( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );
	void RegisterCustom( DayZPlayerType pType );
	void OnRegisterCustom( DayZPlayerType pType );
	void BoneRemapping( DayZPlayerType pType );
	void OnBoneRemapping( DayZPlayerType pType );
};
