
// Base class for all Observable Types (ObservableCollection, ObservableSet, ObservableDictionary)
class Observable
{
	// Assigned by GetTypeFromValue on Insert
	private typename m_Type;
	
	protected string m_VariableName;
	protected Controller m_Controller;
	
	void Observable(string variable_name, Controller controller) {
		m_VariableName = variable_name; 
		m_Controller = controller;
	}
	
	protected void CollectionChanged(CollectionChangedEventArgs args) {
		m_Controller.NotifyCollectionChanged(m_VariableName, args);
	}
	
	string GetVariableName() {
		return m_VariableName;
	}
	
	typename GetType() {
		return m_Type;
	}
	
	TypeConverter GetTypeConverter() {
		return MVC.GetTypeConversion(m_Type);
	}
	
	// Abstract	
	int Count();
}