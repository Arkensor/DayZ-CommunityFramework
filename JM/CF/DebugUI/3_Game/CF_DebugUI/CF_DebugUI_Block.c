class CF_DebugUI_Block: ScriptViewTemplate<CF_DebugUI_Block_Controller>
{
	private string m_Name;

	private Object m_Target;
	private bool m_HasTarget;

	private bool m_Buffered;
	private bool m_SwapClears;

	private int m_Count;

	private autoptr map<string, int> m_EntryMap;
	private autoptr array<ref CF_DebugUI_Entry> m_Entries;

	void CF_DebugUI_Block(string name, Object target = null)
	{
		m_Name = name;

		m_Buffered = false;
		m_SwapClears = false;

		m_Target = target;
		m_HasTarget = m_Target != null;

		m_Entries = new array<ref CF_DebugUI_Entry>();
		m_EntryMap = new map<string, int>();
	}

	void Set(string key, int text)
	{
		Set(key, "" + text);
	}

	void Set(string key, bool text)
	{
		Set(key, "" + text);
	}

	void Set(string key, float text)
	{
		Set(key, "" + text);
	}

	void Set(string key, vector text)
	{
		Set(key, "" + text);
	}

	void Set(string key, Class text)
	{
		Set(key, "" + text);
	}

	void Set(string key, string text)
	{
		int index = -1;
		if (!m_EntryMap.Find(key, index))
		{
			index = m_Entries.Insert(new CF_DebugUI_Entry());
			m_EntryMap.Insert(key, index);
		}

		m_Entries[index].Key = key;
		m_Entries[index].Value = text;

		if (!m_Buffered) SwapBuffer();
	}

	void Remove(string key)
	{
		int index = m_EntryMap[key];
		m_EntryMap.Remove(key);
		m_Entries.RemoveOrdered(index);

		if (!m_Buffered) SwapBuffer();
	}

	void Clear()
	{
		m_EntryMap.Clear();
		m_Entries.Clear();
	}

	void SwapBuffer()
	{
		GetTemplateController().TextField = "";

		for (int i = 0; i < m_Entries.Count(); i++)
		{
			if (m_Entries[i].Key == "") m_Entries[i].Key = " ";
			GetTemplateController().TextField = GetTemplateController().TextField + m_Entries[i].Key;

			if (m_Entries[i].Value != "") GetTemplateController().TextField = GetTemplateController().TextField + ": " + m_Entries[i].Value + "\n";
		}

		GetTemplateController().NotifyPropertyChanged("TextField");

		if (m_SwapClears) Clear();		
	}

	string GetName()
	{
		return m_Name;
	}

	Object GetTarget()
	{
		return m_Target;
	}
	
	bool HasTarget()
	{
		if (m_HasTarget) return m_Target != null;

		return true;
	}

	bool IsTarget(notnull Object target)
	{
		if (!m_HasTarget) return false;

		return target == m_Target;
	}

	void SetBuffered(bool buffered, bool swapClears = false)
	{
		m_Buffered = buffered;
		m_SwapClears = swapClears;
	}

	override string GetLayoutFile()
	{
		return "JM/CF/DebugUI/layouts/DebugUI_Block.layout";
	}
};