class CF_Debugger_Block_UI: ScriptViewTemplate<CF_Debugger_Block_Controller>
{
	protected ref map<string, ref CF_Debugger_Entry> m_DebugEntries = new map<string, ref CF_Debugger_Entry>();
	
	void SetEntryValue(string key, string value)
	{
		if (!m_DebugEntries[key]) {
			m_DebugEntries[key] = new CF_Debugger_Entry(key);
			GetTemplateController().DebuggerBlockData.Insert(m_DebugEntries[key]);
		}
		
		m_DebugEntries[key].SetValue(value);
	}
		
	override string GetLayoutFile()
	{
		return "JM/CF/Debugger/layouts/Debugger_Block.layout";
	}
}


static ref CF_Debugger_Block_UI Test_CF_Debugger_Block_UI;