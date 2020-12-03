modded class AttachmentCategoriesContainer
{
    override void LoadAttachmentCategoriesIcon(SlotsContainer items_cont, string icon_name, int slot_number)
    {
        SlotsIcon icon = items_cont.GetSlotIcon(slot_number);
        ImageWidget image_widget = icon.GetGhostSlot();
        image_widget.Show(true);

        string path = "CfgSlots" + " Slot_" + InventorySlots.GetSlotName(icon.GetSlotID());

		if ( GetGame().ConfigIsExisting( path + " modGhostIcon" ) && GetGame().ConfigGetText( path + " modGhostIcon", icon_name ) && icon_name != "" )
        {
            image_widget.LoadImageFile(0, icon_name);

            if (m_Body.Count() > (slot_number + 2))
            {
                ClosableContainer c = ClosableContainer.Cast(m_Body.Get(slot_number + 2));
                icon.GetRadialIconPanel().Show(true);
                if (c && c.IsOpened())
                {
                    icon.GetRadialIconClosed().Show(false);
                    icon.GetRadialIcon().Show(true);
                }
                else
                {
                    icon.GetRadialIcon().Show(false);
                    icon.GetRadialIconClosed().Show(true);
                }
            }
        } else
        {
            super.LoadAttachmentCategoriesIcon(items_cont, icon_name, slot_number);
        }
    }
};