class CF_Debugger_Block_Controller: Controller
{
	ref ObservableDictionary<string, CF_Debugger_Entry> DebuggerBlockData = new ObservableDictionary<string, CF_Debugger_Entry>(this);
};