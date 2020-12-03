modded class Attachments
{
    override void InitAttachmentGrid(int att_row_index)
    {
        super.InitAttachmentGrid(att_row_index);

        for (int i = 0; i < m_AttachmentSlotNames.Count(); i++)
        {
            SlotsIcon icon2 = SlotsContainer.Cast(m_AttachmentsContainer.Get((i / ITEMS_IN_ROW))).GetSlotIcon(i % ITEMS_IN_ROW);
            WidgetEventHandler.GetInstance().RegisterOnDoubleClick(icon2.GetPanelWidget(), m_Parent, "DoubleClick");

            string path = "CfgSlots" + " Slot_" + m_AttachmentSlotNames[i];

            //Show different magazine icon for firearms and pistols
            if (m_AttachmentSlotNames[i] == "magazine")
            {
                if (!m_Entity.IsInherited(Pistol_Base))
                    path = "CfgSlots" + " Slot_" + "magazine2";
            }

            string icon_name = "";
            if (GetGame().ConfigIsExisting(path + " modGhostIcon") && GetGame().ConfigGetText(path + " modGhostIcon", icon_name) && icon_name != "")
            {
                icon2.GetGhostSlot().LoadImageFile(0, icon_name);

                int slot_id = InventorySlots.GetSlotIdFromString(m_AttachmentSlotNames[i]);
                m_AttachmentSlots.Insert(slot_id, icon2);
                icon2.SetSlotID(slot_id);

                EntityAI item = m_Entity.GetInventory().FindAttachment(slot_id);
                if (item)
                    AttachmentAdded(item, m_AttachmentSlotNames[i], m_Entity);
                else
                    icon2.Clear();
            }
        }
    }
};