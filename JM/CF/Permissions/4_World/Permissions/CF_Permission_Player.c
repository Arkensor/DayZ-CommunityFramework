class CF_Permission_Player : CF_Permission_PlayerBase
{
	PlayerBase PBObject;

	override bool OnUpdateData()
	{
		return Class.CastTo(PBObject, PlayerObject);
	}
};