class CF_Debugger_Block: ScriptViewTemplate<CF_Debugger_Block_Controller>
{
	private string m_Name;

	private Object m_Target;
	//! Boolean to determine if the block has a target, so we can auto destroy if the target becomes null without affecting non-targets
	private bool m_HasTarget;

	private int m_Count;

	void CF_Debugger_Block(string name, Object target = null)
	{
		m_Name = name;

		m_Target = target;
		m_HasTarget = m_Target != null;
	}

	void Set(string key, int text)
	{
		SetValue(key, "" + text);
	}

	void Set(string key, bool text)
	{
		SetValue(key, "" + text);
	}

	void Set(string key, float text)
	{
		SetValue(key, "" + text);
	}

	void Set(string key, vector text)
	{
		SetValue(key, "" + text);
	}

	void Set(string key, Class text)
	{
		SetValue(key, "" + text);
	}

	void Set(string key, string text)
	{
		SetValue(key, text);
	}
	
	void Remove(string key)
	{
		GetTemplateController().DebuggerBlockData.Remove(key);
	}

	void Clear()
	{
		GetTemplateController().DebuggerBlockData.Clear();
	}

	void Cleanup()
	{
		//m_Count = 0;
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
		CF_Debugger_Entry entry = GetTemplateController().DebuggerBlockData.Get(key);
		if (!entry)
		{
			entry = new CF_Debugger_Entry(key);
			entry.Index = GetTemplateController().DebuggerBlockData.Insert(key, entry);
		}
		
		entry.SetValue(value);
		
		entry.Index = GetTemplateController().DebuggerBlockData.MoveIndex(entry.Index, m_Count - entry.Index);
		m_Count = entry.Index + 1;
	}

	override string GetLayoutFile()
	{
		return "JM/CF/Debugger/layouts/Debugger_Block.layout";
	}
};