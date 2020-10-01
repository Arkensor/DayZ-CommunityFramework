
// Base class for all Observable Types (ObservableCollection, ObservableSet, ObservableDictionary)
class Observable
{
	protected string m_VariableName;
	protected Controller m_Controller;
	
	void Observable(string variable_name, Controller controller) {
		m_VariableName = variable_name; m_Controller = controller;
	}
	
	protected void CollectionChanged(CollectionChangedEventArgs args) {
		m_Controller.NotifyCollectionChanged(m_VariableName, args);
	}
	
	string GetVariableName() {
		return m_VariableName;
	}
	
	// Abstract
	typename GetType();
	int Count();
}