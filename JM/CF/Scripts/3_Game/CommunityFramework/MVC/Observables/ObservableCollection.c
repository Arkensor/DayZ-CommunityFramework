
/*

 Base class for Observable Types
 The design behind them is you wont need to use NotifyPropertyChanged() upon setting a variable
 They are current used to support Collections (array, set, map)

Example: 


class TestController: Controller
{
	// "LeftList" goes into Binding_Name
	ref ObservableCollection<string> LeftList; 	
	
	// "LeftListSelection" goes into Selected_Item
	string LeftListSelection; 		
	
	void TestController()
	{
		LeftList = new ObservableCollection<string>("LeftList", this);
		LeftList.Insert("Line1");
	}

	override void PropertyChanged(string property_name)
	{
		switch (property_name) {
			case "LeftListSelection": {
				Print("LeftList selection changed: " + LeftListSelection);
				break;
			}
		}
	}
}

*/

class ObservableTest<Class TValue>
{
	private ref Param1<TValue> _type;
	
	void ObservableTest()
	{	
		Print(_type);
		_type = _type.Type().Spawn();
		Print(_type);
		
		_type = Param1<TValue>.Cast(new Param());
		Print(_type);
		
		_type = new Param();
		Print(_type);
		
		
	}
}


class ObservableCollection<Class TValue>: Observable
{	
	private ref array<ref TValue> _data = {};
	
	// Incredibly Scuffed way of acquiring typename from Value, since forward declaration
	// is totally borked :)
	// Error that inflicts this pain upon me
	// Can't get typename from forward declaration 'Class'. Use Type("name") instead....
	// Go ahead, try and Print(TValue). YOU CANT FIX IT >:(
	private typename GetTypeFromValue(TValue value)
	{
		typename param_type = (new Param1<TValue>(value)).Type();
		for (int i = 0; i < param_type.GetVariableCount(); i++) {
			if (param_type.GetVariableName(i) == "param1") {
				return param_type.GetVariableType(i);
			}
		}
		
		typename t;
		return t;
	}
	
	int Insert(TValue value)
	{
		if (!m_Type) {
			m_Type = GetTypeFromValue(value);
		}
		
		int index = _data.Insert(value);
		if (index != -1) {
			CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Insert, index, new Param1<TValue>(value)));
		}
		
		return index;
	}
	
	int InsertAt(TValue value, int index)
	{
		if (!m_Type) {
			m_Type = GetTypeFromValue(value);
		}
		
		int new_index = _data.InsertAt(value, index);
		CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.InsertAt, index, new Param1<TValue>(value)));
		return new_index;
	}
	
	
	// 0: TValue value
	// 1: int index
	int InsertAtEx(TypeConverter type_converter, int index)
	{
		TValue value; // scoofed
		g_Script.CallFunction(type_converter, "GetData", value, null);
		Print(value);
		int new_index = _data.InsertAt(value, index);
		CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.InsertAt, index, new Param1<TValue>(value)));
		return new_index;
	}
	
	void Remove(int index)
	{
		CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Remove, index, new Param1<TValue>(_data.Get(index))));	
		_data.Remove(index);	
	}
	
	void Remove(TValue value)
	{
		int index = _data.Find(value);
		if (index != -1)
			Remove(index);
	}
	
	void Set(int index, TValue value)
	{
		CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Replace, index, new Param1<TValue>(value)));
		_data.Set(index, value);
	}
	
	int MoveIndex(int index, int move_index)
	{
		TValue value = _data.Get(index);
		int new_index = _data.MoveIndex(index, move_index);
		CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Move, new_index, new Param1<TValue>(value)));
		return new_index;
	}
	
	void SwapItems(int item_1, int item_2)
	{
		_data.SwapItems(item_1, item_2);
		CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Swap, -1, new CollectionSwapArgs(item_1, item_2)));
	}
	
	void Clear()
	{
		_data.Clear();
		CollectionChanged(new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Clear, -1, null));
	}
	
	TValue Get(int index) {		
		return _data.Get(index);
	}
	
	override int Count() { 
		return _data.Count(); 
	}
	
	int Find(TValue value) {
		Print(value);
		return _data.Find(value); 
	}
}