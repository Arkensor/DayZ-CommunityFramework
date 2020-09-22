


// Abstract Class
class RoutedUICommand
{
	private bool m_CanExecute = true;
	
	protected ViewBinding m_ViewBinding;
	void SetViewBinding(ViewBinding view_binding) {
		m_ViewBinding = view_binding;
	}
	
	// returns bool defining whether or not the Execute can be called
	bool CanExecute() {
		return m_CanExecute;
	}
	
	// sets whether or not RoutedUICommand can be executed
	// depreciate if BI ever adds property Getters and Setters
	void SetCanExecute(bool state) {
		m_CanExecute = state;
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(CanExecuteChanged, m_CanExecute);
	}
	
	
	/* Abstract Methods */
	
	// called when type is Clicked, Selected, or Changed
	void Execute(RoutedUICommandArgs args);
	
	// Abstract function called when execution ability is changed
	void CanExecuteChanged(bool state);
}
