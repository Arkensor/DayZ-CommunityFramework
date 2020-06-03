modded class ModItemRegisterCallbacks
{
	ref JMAnimRegister m_AnimRegister;

	void ModItemRegisterCallbacks()
	{
		m_AnimRegister = new JMAnimRegister();
	}

	void ~ModItemRegisterCallbacks()
	{
		delete m_AnimRegister;
	}

	override void RegisterEmptyHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterEmptyHanded( pType, pBehavior );

		m_AnimRegister.OnRegisterEmptyHanded( pType, pBehavior );
	}

    override void RegisterOneHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterOneHanded( pType, pBehavior );

		m_AnimRegister.OnRegisterOneHanded( pType, pBehavior );
	}

    override void RegisterTwoHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterTwoHanded( pType, pBehavior );

		m_AnimRegister.OnRegisterTwoHanded( pType, pBehavior );
	}

    override void RegisterRestrained( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterRestrained( pType, pBehavior );

		m_AnimRegister.OnRegisterRestrained( pType, pBehavior );
	}

    override void RegisterSurrender( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterSurrender( pType, pBehavior );

		m_AnimRegister.OnRegisterSurrender( pType, pBehavior );
	}

    override void RegisterHeavy( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterHeavy( pType, pBehavior );

		m_AnimRegister.OnRegisterHeavy( pType, pBehavior );
	}

    override void RegisterPistol( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterPistol( pType, pBehavior );

		m_AnimRegister.OnRegisterPistol( pType, pBehavior );
	}

    override void RegisterFireArms( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterFireArms( pType, pBehavior );

		m_AnimRegister.OnRegisterFireArms( pType, pBehavior );
	}

    override void RegisterArcheryItem( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterArcheryItem( pType, pBehavior );

		m_AnimRegister.OnRegisterArcheryItem( pType, pBehavior );
	}

    override void RegisterLauncher( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.RegisterLauncher( pType, pBehavior );

		m_AnimRegister.OnRegisterLauncher( pType, pBehavior );
	}

	override void RegisterCustom( DayZPlayerType pType )
	{
		super.RegisterCustom( pType );
	}

	override void CustomBoneRemapping( DayZPlayerType pType )
	{
		super.CustomBoneRemapping( pType );

		m_AnimRegister.OnBoneRemapping( pType );
	}
};

// 107 compatibility
class JMAnimRegister
{
	void OnRegisterEmptyHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterOneHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterTwoHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterRestrained( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterSurrender( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterHeavy( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterPistol( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterFireArms( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterArcheryItem( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterLauncher( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnBoneRemapping( DayZPlayerType pType );
};