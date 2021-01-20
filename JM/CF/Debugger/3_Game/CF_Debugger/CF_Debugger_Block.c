class CF_Debugger_Block
{
	private string m_Name;

	private Object m_Target;
	//! Boolean to determine if the block has a target, so we can auto destroy if the target becomes null without affecting non-targets
	private bool m_HasTarget;

	private autoptr map<string, string> m_Text;

	void CF_Debugger_Block(string name, Object target = null)
	{
		m_Name = name;

		m_Target = target;
		m_HasTarget = m_Target != null;

		m_Text = new map<string, string>();
	}

	void Add(string key, int text)
	{
		m_Text[key] = "" + text;
	}

	void Add(string key, bool text)
	{
		m_Text[key] = "" + text;
	}

	void Add(string key, float text)
	{
		m_Text[key] = "" + text;
	}

	void Add(string key, vector text)
	{
		m_Text[key] = "" + text;
	}

	void Add(string key, string text)
	{
		m_Text[key] = text;
	}

	void Clear()
	{
		m_Text.Clear();
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
};