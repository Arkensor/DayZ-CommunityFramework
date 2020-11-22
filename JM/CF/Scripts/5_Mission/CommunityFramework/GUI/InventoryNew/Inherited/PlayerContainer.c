modded class PlayerContainer
{
	void PlayerContainer( LayoutHolder parent, int sort = -1 )
	{
		int row, column;
		SlotsIcon icon;

		string config_path_ghosts_slots = "CfgVehicles SurvivorBase InventoryEquipment playerSlots";
		ref array<string> player_ghosts_slots = new array<string>;
		GetGame().ConfigGetTextArray( config_path_ghosts_slots, player_ghosts_slots );
		
		for ( int i = 0; i < player_ghosts_slots.Count(); i++ )
		{
			string slot_name = player_ghosts_slots.Get ( i );
			string path = "CfgSlots" + " " + slot_name;
			string ghostIconPath = "CfgSlots" + " " + slot_name + " modGhostIcon";

			if ( GetGame().ConfigIsExisting( path ) && GetGame().ConfigIsExisting( ghostIconPath ) )
			{
				string expansionGhost;
				GetGame().ConfigGetText( ghostIconPath, expansionGhost );

				icon = GetSlotsIcon( row, column );
				icon.GetGhostSlot().LoadImageFile( 0, expansionGhost );
			}
		}
	}
};