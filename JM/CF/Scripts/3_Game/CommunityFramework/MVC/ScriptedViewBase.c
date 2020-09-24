

class ScriptedViewBase: ScriptedWidgetEventHandler
{
	
	// Enable verbose logging
	reference bool Debug_Logging;
	
	bool Trace_Logs = true;
	
	void ScriptedViewBase()
	{
		Trace(Type().ToString());
	}
	
	void ~ScriptedViewBase()
	{	
		Trace("~" + Type().ToString());
	}
	
	void Trace(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (Debug_Logging && Trace_Logs)
			PrintFormat("[Trace] %1 - %2 ", Type(), string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}
	
	void Log(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (Debug_Logging)
			PrintFormat("[Log] %1 - %2", Type(), string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}
	
	
	void Error(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		string msg = string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9);
		//PrintFormat("MVCLog::Error %1", msg);
		string header = string.Format("[Error] %1", Type());
		Error2(header, msg);
		
#ifdef COMPONENT_SYSTEM
		Workbench.Dialog(header, msg);
#endif
	}
	
	// Source Widget
	protected Widget m_LayoutRoot;
	Widget GetLayoutRoot() {
		return m_LayoutRoot;
	}
	
	// Parent (should be overridden)
	ScriptedViewBase GetParent();
	
	
	void OnWidgetScriptInit(Widget w)
	{
		Trace("OnWidgetScriptInit %1", w.GetName());
		m_LayoutRoot = w;
		m_LayoutRoot.SetHandler(this);
	}
	
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		Trace("OnClick: %1", w.GetName());
		return false;
	}

	override bool OnModalResult(Widget w, int x, int y, int code, int result)
	{
		Trace("OnModalResult: %1", w.GetName());
		return false;
	}
	
	override bool OnDoubleClick(Widget w, int x, int y, int button) 
	{
		Trace("OnDoubleClick: %1", w.GetName());		
		return false;
	}
	
	override bool OnSelect(Widget w, int x, int y) 
	{
		Trace("OnSelect: %1", w.GetName());		
		return false;
	}
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int column, int oldRow, int oldColumn)
	{
		Trace("OnItemSelected: %1", w.GetName());		
		return false;
	}
	
	override bool OnFocus(Widget w, int x, int y)
	{
		Trace("OnFocus: %1", w.GetName());		
		return false;
	}
	
	override bool OnFocusLost(Widget w, int x, int y)
	{
		Trace("OnFocusLost: %1", w.GetName());		
		return false;
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		Trace("OnMouseEnter: %1", w.GetName());		
		return false;
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		Trace("OnMouseLeave: %1", w.GetName());		
		return false;
	}
	
	override bool OnMouseWheel(Widget w, int x, int y, int wheel)
	{
		Trace("OnMouseWheel: %1", w.GetName());		
		return false;
	}
	
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		Trace("OnMouseButtonDown: %1", w.GetName());		
		return false;
	}
	
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		Trace("OnMouseButtonUp: %1", w.GetName());		
		return false;
	}

	override bool OnController(Widget w, int control, int value)
	{
		Trace("OnController: %1", w.GetName());
		return false;
	}
	
	override bool OnKeyDown(Widget w, int x, int y, int key)
	{
		Trace("OnKeyDown: %1", w.GetName());		
		return false;
	}
	
	override bool OnKeyUp(Widget w, int x, int y, int key)
	{
		Trace("OnKeyUp: %1", w.GetName());		
		return false;
	}
	
	override bool OnKeyPress(Widget w, int x, int y, int key)
	{
		Trace("OnKeyPress: %1", w.GetName());		
		return false;
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		Trace("OnChange: %1", w.GetName());		
		return false;
	}
	
	override bool OnDrag(Widget w, int x, int y)
	{
		Trace("OnDrag: %1", w.GetName());		
		return false;
	}
	
	override bool OnDragging(Widget w, int x, int y, Widget reciever)
	{
		Trace("OnDragging: %1", w.GetName());		
		return false;
	}
	
	override bool OnDraggingOver(Widget w, int x, int y, Widget reciever)
	{
		Trace("OnDraggingOver: %1", w.GetName());		
		return false;
	}
	
	override bool OnDrop(Widget w, int x, int y, Widget reciever)
	{
		Trace("OnDrop: %1", w.GetName());		
		return false;
	}
	
	override bool OnDropReceived(Widget w, int x, int y, Widget reciever)
	{
		Trace("OnDropReceived: %1", w.GetName());		
		return false;
	}
	
	override bool OnResize(Widget w, int x, int y)
	{
		Trace("OnResize: %1", w.GetName());		
		return false;
	}
	
	override bool OnChildAdd(Widget w, Widget child)
	{
		Trace("OnChildAdd: %1", w.GetName());		
		return false;
	}
	
	override bool OnChildRemove(Widget w, Widget child)
	{
		Trace("OnChildRemove: %1", w.GetName());		
		return false;
	}
	
}