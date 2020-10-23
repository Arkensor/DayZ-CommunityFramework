modded class AttachmentCategoriesRow
{
	override void Init( int attachments_categories_count, int i, string attachment_category, string config_path_attachment_categories, EntityAI entity, int parent_m_Body_count )
	{
		super.Init( attachments_categories_count, i, attachment_category, config_path_attachment_categories, entity, parent_m_Body_count );

		ref array<string> player_ghosts_slots2 = new array<string>;
		GetGame().ConfigGetTextArray( m_RowConfigPath, player_ghosts_slots2 );
		int count = player_ghosts_slots2.Count();

		for ( int j = 0; j < count; ++j )
		{
			int id = j % ITEMS_IN_ROW;
			SlotsContainer ic2 = SlotsContainer.Cast( Get( ( j / ITEMS_IN_ROW + 1 ) ) );
			SlotsIcon icon2 = ic2.GetSlotIcon( id );

			string slot_name = player_ghosts_slots2.Get ( j );
			string path = "CfgSlots" + " Slot_" + slot_name;

			string icon_name = "";
			if ( GetGame().ConfigGetText( path + " modGhostIcons", icon_name ) && icon_name != "" )
				icon2.GetGhostSlot().LoadImageFile( 0, icon_name );
		}
	}
};