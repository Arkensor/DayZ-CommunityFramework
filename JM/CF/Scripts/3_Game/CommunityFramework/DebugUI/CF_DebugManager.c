class CF_DebugManager : CF_Model
{
	private autoptr CF_Map<Class, CF_Debug> m_Instances;
	private bool m_Allowed;

	void CF_DebugManager()
	{
		m_Instances = new CF_Map<Class, CF_Debug>();
	}

	override string GetLayoutFile()
	{
		return "JM/CF/GUI/layouts/debug/panel.layout";
	}

	bool IsAllowed()
	{
		return m_Allowed;
	}

	void SetAllowed(bool newState)
	{
		m_Allowed = newState;
	}

	void Create(Class instance, string title = "##")
	{
		if (!m_Allowed || !instance) return;

		title = ConvertTitle(instance, title);

		CF_Debug cf_debug;
		if (m_Instances.Find(instance, cf_debug))
		{
			cf_debug.SetName(title);
			return;
		}

		cf_debug = new CF_Debug(instance, title);
		m_Instances.Insert(instance, cf_debug);
	}

	void Destroy(Class instance)
	{
		m_Instances.Remove(instance);
	}

	string ConvertTitle(Class instance, string title)
	{
		if (title != "##") return title;

		string hex = "" + instance;
		int previousIndex = hex.IndexOf("<");
		int index = -1;
		while (previousIndex != -1)
		{
			index = previousIndex;
			hex = hex.Substring(index + 1, hex.Length() - index - 1);
			previousIndex = hex.IndexOf("<");
		}
		hex = hex.Substring(0, hex.Length() - 1);

		title = instance.ClassName();
	
		Object object;
		if (Class.CastTo(object, instance))
		{
			title = object.GetDisplayName();

			if (GetGame().IsMultiplayer())
			{
				title += " (" + object.GetNetworkIDString() + ")";
			}
		}

		title += " (" + hex + ")";

		return title;
	}
};
