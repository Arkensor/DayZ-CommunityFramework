class CF_NotificationHandler: ScriptedWidgetEventHandler
{
	NotificationUI m_NotificationUI;
	NotificationRuntimeData m_Data;
	Widget m_Notification;

	void CF_NotificationHandler(NotificationUI notificationUI, NotificationRuntimeData data, Widget notification)
	{
		m_NotificationUI = notificationUI;
		m_Data = data;
		m_Notification = notification;
		m_Notification.SetHandler(this);
	}
	
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		if (w == m_Notification)
		{
			m_NotificationUI.CF_DiscardNotification(this);
			return true;
		}

		return false;
	}
}
