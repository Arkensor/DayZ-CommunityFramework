class CF_CollectionEvent : CF_Event
{
	CF_MVVM_View m_View;
	CF_ObservableCollection m_Collection;

	Widget m_Widget;

	override string String()
	{
		string str = super.String();
		str += " View=" + m_View;
		str += " Collection=" + m_Collection;
		str += " Widget=" + m_Widget;
		return str;
	}

	void Process()
	{

	}
};