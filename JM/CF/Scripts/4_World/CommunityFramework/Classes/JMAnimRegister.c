class JMAnimRegister
{
	private void JMAnimRegister()
	{

	}

	static JMAnimRegister Register( DayZPlayerType pType )
	{
		JMAnimRegister animReg = new JMAnimRegister;

		DayzPlayerItemBehaviorCfg behaviour;

		behaviour = new DayzPlayerItemBehaviorCfg;
		behaviour.SetEmptyHanded();
		animReg.OnRegisterEmptyHanded( pType, behaviour );
		
		behaviour = new DayzPlayerItemBehaviorCfg;
		behaviour.SetTwoHanded();
		animReg.OnRegisterTwoHanded( pType, behaviour );
		
		behaviour = new DayzPlayerItemBehaviorCfg;
		behaviour.SetToolsOneHanded();
		animReg.OnRegisterOneHanded( pType, behaviour );
		
		behaviour = new DayzPlayerItemBehaviorCfg;
		behaviour.SetRestrained();
		animReg.OnRegisterRestrained( pType, behaviour );
		
		behaviour = new DayzPlayerItemBehaviorCfg;
		behaviour.SetSurrender();
		animReg.OnRegisterSurrender( pType, behaviour );
		
		behaviour = new DayzPlayerItemBehaviorCfg;
		behaviour.SetHeavyItems();
		animReg.OnRegisterHeavy( pType, behaviour );

		behaviour = new DayzPlayerItemBehaviorCfg;
		behaviour.SetPistols();
		animReg.OnRegisterPistol( pType, behaviour );
		
		behaviour = new DayzPlayerItemBehaviorCfg;
		behaviour.SetFirearms();
		animReg.OnRegisterFireArms( pType, behaviour );

		behaviour = new DayzPlayerItemBehaviorCfg;
		animReg.OnRegisterArcheryItem( pType, behaviour );

		behaviour = new DayzPlayerItemBehaviorCfg;
		animReg.OnRegisterLauncher( pType, behaviour );

		animReg.OnBoneRemapping( pType );

		return animReg;
	}

	void OnRegisterEmptyHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterTwoHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterOneHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterRestrained( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterSurrender( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterHeavy( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterPistol( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterFireArms( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterArcheryItem( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnRegisterLauncher( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior );

	void OnBoneRemapping( DayZPlayerType pType );
};