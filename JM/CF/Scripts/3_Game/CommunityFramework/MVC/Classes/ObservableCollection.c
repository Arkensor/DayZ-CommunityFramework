enum NotifyCollectionChangedAction {
	Add,
	Remove,
	Set,
	Move,
	Clear
};

// Base class for Observable Types
// The design behind them is you wont need to use NotifyPropertyChanged() upon setting a variable
// They are current used to support Collections (array, map)
class Observable
{
	protected string m_VariableName;
	protected Controller m_Controller;
	
	void Observable(string variable_name, Controller parent_controller)	{
		m_VariableName = variable_name; m_Controller = parent_controller;
	}
	
	typename GetType();
}

class ObservableCollection<Class TValue>: Observable
{
	private autoptr ref array<ref TValue> _data = new array<ref TValue>();
	
	int Insert(TValue value)
	{
		int index = _data.Insert(value);
		if (index != -1) {
			m_Controller.NotifyCollectionChanged(m_VariableName, new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Add, index, new Param1<TValue>(value)));
		}
		
		return index;
	}
	
	int InsertAt(TValue value, int index)
	{
		int new_index = _data.InsertAt(value, index);
		m_Controller.NotifyCollectionChanged(m_VariableName, new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Set, index, new Param1<TValue>(value)));
		return new_index;
	}
	
	
	void Remove(int index)
	{
		m_Controller.NotifyCollectionChanged(m_VariableName, new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Remove, index, new Param1<TValue>(_data.Get(index))));	
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
		m_Controller.NotifyCollectionChanged(m_VariableName, new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Set, index, new Param1<TValue>(value)));
		_data.Set(index, value);
	}
	
	int Move(int index, int moveindex)
	{
		int new_index = _data.MoveIndex(index, moveindex);
		m_Controller.NotifyCollectionChanged(m_VariableName, new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Move, index, new Param1<int>(new_index)));
		return new_index;
	}
	
	void Clear()
	{
		_data.Clear();
		m_Controller.NotifyCollectionChanged(m_VariableName, new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Clear, -1, null));
	}
	
	TValue Get(int index)
	{
		TValue v = _data.Get(index);
		if (!v) {
			MVC.Error(string.Format("ObservableCollection.Get returned null! Index: %1 Name: %2", index, m_VariableName));
		}
		
		return v;
	}
	
	int Count() { 
		return _data.Count(); 
	}
	
	int Find(TValue value) { 
		return _data.Find(value); 
	}
	
	override typename GetType() {
		return TValue;
	}
}

class ObservableSet<Class TValue>: Observable
{
	private autoptr ref set<ref TValue> _data = new set<ref TValue>();	
	
	int Insert(TValue value)
	{
		int index = _data.Insert(value);
		if (index != -1) {
			m_Controller.NotifyCollectionChanged(m_VariableName, new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Add, index, new Param1<TValue>(value)));
		}
		
		return index;
	}
	
	int InsertAt(TValue value, int index)
	{
		int new_index = _data.InsertAt(value, index);
		m_Controller.NotifyCollectionChanged(m_VariableName, new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Set, index, new Param1<TValue>(value)));
		return new_index;
	}
	
	
	void Remove(int index)
	{
		m_Controller.NotifyCollectionChanged(m_VariableName, new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Remove, index, new Param1<TValue>(_data.Get(index))));	
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
		m_Controller.NotifyCollectionChanged(m_VariableName, new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Set, index, new Param1<TValue>(value)));
		_data.Set(index, value);
	}
	
	int Move(int index, int moveindex)
	{
		int new_index = _data.MoveIndex(index, moveindex);
		m_Controller.NotifyCollectionChanged(m_VariableName, new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Move, index, new Param1<int>(new_index)));
		return new_index;
	}
	
	void Clear()
	{
		_data.Clear();
		m_Controller.NotifyCollectionChanged(m_VariableName, new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Clear, -1, null));
	}
	
	TValue Get(int index)
	{
		TValue v = _data.Get(index);
		if (!v) {
			MVC.Error(string.Format("ObservableCollection.Get returned null! Index: %1 Name: %2", index, m_VariableName));
		}
		
		return v;
	}
	
	int Count() { 
		return _data.Count(); 
	}
	
	int Find(TValue value) { 
		return _data.Find(value); 
	}
	
	override typename GetType() {
		return TValue;
	}
}

class ObservableDictionary<Class TKey, Class TValue>: Observable
{
	private autoptr ref map<TKey, TValue> _data = new map<TKey, TValue>();
		
	bool Insert(TKey key, TValue value)
	{
		if (_data.Insert(key, value)) {
			m_Controller.NotifyCollectionChanged(m_VariableName, new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Add, new Param2<TKey, TValue>(key, value)));
			return true;
		}
		
		return false;
	}

	void Remove(TKey key)
	{
		if (_data.Contains(key)) {
			TValue value = _data.Get(key);
			_data.Remove(key);
			m_Controller.NotifyCollectionChanged(m_VariableName, new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Remove, new Param2<TKey, TValue>(key, value)));
		}
	}
	
	void Clear()
	{
		_data.Clear();
		m_Controller.NotifyCollectionChanged(m_VariableName, new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Clear, null));
	}
	
	void Set(TKey key, TValue value)
	{
		_data.Set(key, value);
		m_Controller.NotifyCollectionChanged(m_VariableName, new CollectionChangedEventArgs(this, NotifyCollectionChangedAction.Set, new Param2<TKey, TValue>(key, value)));
	}
	

	
	TValue Get(TKey key)
	{
		return _data.Get(key);
	}
		
	TKey GetKey(int index)
	{
		return _data.GetKey(index);
	}
	
	int Count() { 
		return _data.Count(); 
	}
	
	override typename GetType() {
		return TValue;
	}
}




