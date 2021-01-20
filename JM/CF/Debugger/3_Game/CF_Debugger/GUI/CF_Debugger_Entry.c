class CF_Debugger_Entry: ScriptViewTemplate<CF_Debugger_Entry_Controller>
{	
	void CF_Debugger_Entry(string key)
	{
		GetTemplateController().EntryKey = key;
		GetTemplateController().NotifyPropertyChanged("EntryKey");
	}
	
	void SetValue(string value)
	{
		GetTemplateController().EntryValue = value;
		GetTemplateController().NotifyPropertyChanged("EntryValue");
	}
	
	string GetKey()
	{
		return GetTemplateController().EntryKey;
	}
	
	string GetValue()
	{
		return GetTemplateController().EntryValue;
	}
	
	override string GetLayoutFile()
	{
		return "JM/CF/Debugger/layouts/Debugger_Entry.layout";
	}
};