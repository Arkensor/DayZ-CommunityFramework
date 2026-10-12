/**
 * Fix for vanilla notifications that stay on screen forever after a quick burst,
 * and for the notification root intercepting mouse clicks (instead, a click now immediately discards the notification)
 * 
 * Vanilla NotificationUI.RemoveNotification moves an expired notification into m_WidgetTimers (the fade-out map)
 * under the key  m_WidgetTimers.Count().ToString() + data.GetTime().ToString().  That key is not unique: with two
 * notifications of the same show time fading ("03", "13"), the first one finishing drops the count to 1 and the
 * next expiry builds "13" again ("1" + "13" and "11" + "3" collide the same way). The insert then drops or replaces
 * a widget, which is no longer in m_Notifications either, so Update never fades or deletes it: it stays forever.
 * 
 * This override only frees the key vanilla is about to use: a widget already fading under it is moved to a key that
 * cannot collide (it keeps fading from where it was). Then super runs unchanged, so the base game and every other
 * mod's override behave exactly as before, and NotificationSystem is not touched.
 */
modded class NotificationUI
{
	protected static int s_CF_UniqueFadeSerial;

	protected ref set<ref CF_NotificationHandler> m_CF_NotificationHandlers = new set<ref CF_NotificationHandler>;

	override void AddNotification(NotificationRuntimeData data)
	{
		super.AddNotification(data);

		Widget notification;
		if (m_Notifications.Find(data, notification))
		{
			m_CF_NotificationHandlers.Insert(new CF_NotificationHandler(this, data, notification));
		}
	}

	override void RemoveNotification(NotificationRuntimeData data)
	{
		if (m_Notifications.Contains(data))
		{
			int fadingCount = m_WidgetTimers.Count();
			float showTime = data.GetTime();
			string vanillaKey = fadingCount.ToString() + showTime.ToString();

			Widget fading;
			if (m_WidgetTimers.Find(vanillaKey, fading))
			{
				m_WidgetTimers.Remove(vanillaKey);
				m_WidgetTimers.Insert(CF_GetUniqueFadeKey(), fading);
			}
		}

		super.RemoveNotification(data);
	}

	//! Unfortunately this is the only signal when a notification gets deleted after fading
	override void UpdateTargetHeight()
	{
		super.UpdateTargetHeight();

		foreach (int i, CF_NotificationHandler handler: m_CF_NotificationHandlers)
		{
			if (!handler.m_Notification)
			{
				m_CF_NotificationHandlers.Remove(i);
				break;
			}
		} 
	}

	//! A fade-out key no vanilla key ("<count><time>") or voice key (a player id) can be.
	protected string CF_GetUniqueFadeKey()
	{
		string key = string.Format("CF_Fade_%1", s_CF_UniqueFadeSerial);

		while (m_WidgetTimers.Contains(key))
		{
			++s_CF_UniqueFadeSerial;
			key = string.Format("CF_Fade_%1", s_CF_UniqueFadeSerial);
		}

		++s_CF_UniqueFadeSerial;

		return key;
	}

	//! Immediately discard notification, no fading
	void CF_DiscardNotification(CF_NotificationHandler handler)
	{
		if (m_Notifications.Contains(handler.m_Data))
		{
			m_Notifications.Remove(handler.m_Data);
		}
		else
		{
			foreach (string key, Widget w: m_WidgetTimers)
			{
				if (w == handler.m_Notification)
				{
					m_WidgetTimers.Remove(key);
					break;
				}
			}
		}

		handler.m_Notification.Unlink();
		m_CF_NotificationHandlers.RemoveItem(handler);
		UpdateTargetHeight();
	}
}
