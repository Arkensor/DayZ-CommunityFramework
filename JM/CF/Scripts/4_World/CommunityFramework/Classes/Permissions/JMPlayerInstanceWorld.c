class JMPlayerInstanceWorld: JMPlayerInstance
{
	PlayerBase PBObject;

	override void OnUpdateData()
	{
		Class.CastTo( PBObject, PlayerObject );
	}
};