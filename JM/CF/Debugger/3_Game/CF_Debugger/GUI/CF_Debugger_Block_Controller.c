class CF_Debugger_Block_Controller: Controller
{
	ref ObservableCollection<CF_Debugger_Entry> DebuggerBlockData = new ObservableCollection<CF_Debugger_Entry>(this);
}

class CF_Debugger_Entry_Controller: Controller
{
	string EntryKey = "Test2";
	string EntryValue;
}