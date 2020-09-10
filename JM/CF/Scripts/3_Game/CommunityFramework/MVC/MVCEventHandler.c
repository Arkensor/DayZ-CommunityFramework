


class MVCWidgetHandler: ScriptedWidgetEventHandler
{
	protected Widget m_LayoutRoot;
	Widget GetLayoutRoot()
		return m_LayoutRoot;
	
	void OnWidgetScriptInit(Widget w)
	{
		m_LayoutRoot = w;
		m_LayoutRoot.SetHandler(this);
	}	
}

