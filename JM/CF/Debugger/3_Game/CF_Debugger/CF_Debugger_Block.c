class CF_Debugger_Block: ScriptViewTemplate<CF_Debugger_Block_Controller>
{
	private string m_Name;

	private Object m_Target;
	//! Boolean to determine if the block has a target, so we can auto destroy if the target becomes null without affecting non-targets
	private bool m_HasTarget;

	private autoptr map<string, ref CF_Debugger_Entry> m_Text;

	void CF_Debugger_Block(string name, Object target = null)
	{
		m_Name = name;

		m_Target = target;
		m_HasTarget = m_Target != null;

		m_Text = new map<string, ref CF_Debugger_Entry>();
	}

	void Add(string key, int text)
	{
		SetValue(key, "" + text);
	}

	void Add(string key, bool text)
	{
		SetValue(key, "" + text);
	}

	void Add(string key, float text)
	{
		SetValue(key, "" + text);
	}

	void Add(string key, vector text)
	{
		SetValue(key, "" + text);
	}

	void Add(string key, string text)
	{
		SetValue(key, text);
	}

	void Clear()
	{
		m_Text.Clear();

		GetTemplateController().DebuggerBlockData.Clear();
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
	
	private void SetValue(string key, string value)
	{
		if (!m_Text[key])
		{
			m_Text[key] = new CF_Debugger_Entry(key);

			GetTemplateController().DebuggerBlockData.Insert(m_Text[key]);
		}
		
		m_Text[key].SetValue(value);
	}

	override string GetLayoutFile()
	{
		return "JM/CF/Debugger/layouts/Debugger_Block.layout";
	}
};