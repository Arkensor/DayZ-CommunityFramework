
/**
 * @brief Inheriting from 'CF_Model' is not a requirement, must re-implement the 'GetLayoutFile' method.
 */
class CF_TestModel : CF_Model
{
	int Index;

	string TextInput = "Input?";
	bool BlockInput = false;

	string ButtonText = "Press??";
	
	//ref CF_Dropdown<ref CF_TestColour> Dropdown = new CF_Dropdown<ref CF_TestColour>();

	ref CF_ObservableArray<CF_TestItemModel> Test = new CF_ObservableArray<CF_TestItemModel>();
	
	void CF_TestModel()
	{
		//Dropdown.Insert(new CF_TestColour(0xFFFF0000, "Red"));
		//Dropdown.Insert(new CF_TestColour(0xFF00FF00, "Green"));
		//Dropdown.Insert(new CF_TestColour(0xFF0000FF, "Blue"));
	}

	void OpenWindow()
	{
	}

	void CloseWindow()
	{
	}

	void OnCheckboxChange(CF_ModelBase sender, CF_ChangeEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnCheckboxChange").Add(sender).Add(evt.ToStr());
		#endif

		evt.Continue = true;
	}

	void OnChange(CF_ModelBase sender, CF_ChangeEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnChange").Add(sender).Add(evt.ToStr());
		#endif
		
		evt.Continue = BlockInput;

		ButtonText = TextInput;
		NotifyPropertyChanged("ButtonText");
	}

	void OnClick(CF_ModelBase sender, CF_MouseEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnClick").Add(sender).Add(evt.ToStr());
		#endif

		Index++;

		ButtonText = "Pressed " + Index + " times!";
		NotifyPropertyChanged("ButtonText");

		// Dropdown.GetSelected()
		CF_TestItemModel item = new CF_TestItemModel(this, null, Index);
		Test.Insert(item);
	}

	override string GetLayoutFile()
	{
		return "JM/CF/GUI/layouts/mvvm/test.layout";
	}
};

class CF_TestColour : CF_Model
{
	int Hex;

	string Name;

	void CF_TestColour(int _hex, string _name)
	{
		Hex = _hex;
		Name = _name;
	}

	override string ToStr()
	{
		return Name;
	}
};

class CF_TestItemModel : CF_Model
{
	string ButtonText = "NOT SET!";

	ref CF_TestColour Colour;

	private CF_TestModel m_Parent;

	void CF_TestItemModel(CF_TestModel parent, CF_TestColour colour, int index)
	{
		m_Parent = parent;

		Colour = colour;

		ButtonText = "Press To Remove (" + index + ")";
	}

	void Remove(CF_ModelBase sender, CF_MouseEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Remove").Add(sender).Add(evt.ToStr());
		#endif

		int index = m_Parent.Test.Find(this);
		m_Parent.Test.RemoveOrdered(index);
	}

	override string GetLayoutFile()
	{
		return "JM/CF/GUI/layouts/mvvm/testitem.layout";
	}
};

class CF_TestModelTester
{
	static ref CF_TestModelTester s_Tester;

	static void _Init()
	{
		s_Tester = new CF_TestModelTester();
	}

	private UAInput m_ToggleInput;

	void CF_TestModelTester()
	{
		m_ToggleInput = GetUApi().GetInputByName("UACFTEST");

		CF_Timer.Create(this, "Update");
	}

	void Update(CF_TimerBase timer, float dt)
	{
		if (GetGame().GetUIManager().GetMenu())
		{

		}
	}	
};
