

class ScriptedViewBase: ScriptedWidgetEventHandler
{
	// Source Widget
	protected Widget m_LayoutRoot;
	Widget GetLayoutRoot() {
		return m_LayoutRoot;
	}
	
	// Parent (should be overridden)
	ScriptedViewBase GetParent();
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (GetParent()) {
			return GetParent().OnClick(w, x, y, button);
		}
		
		return false;
	}

	override bool OnModalResult(Widget w, int x, int y, int code, int result)
	{
		if (GetParent()) {
			return GetParent().OnModalResult(w, x, y, code, result);
		}
		
		return false;
	}
	
	override bool OnDoubleClick(Widget w, int x, int y, int button) 
	{
		if (GetParent()) {
			return GetParent().OnDoubleClick(w, x, y, button);
		}
		
		return false;
	}
	
	override bool OnSelect(Widget w, int x, int y) 
	{
		if (GetParent()) {
			return GetParent().OnSelect(w, x, y);
		}
		
		return false;
	}
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int column, int oldRow, int oldColumn)
	{
		if (GetParent()) {
			return GetParent().OnItemSelected(w, x, y, row, column, oldRow, oldColumn);
		}
		
		return false;
	}
	
	override bool OnFocus(Widget w, int x, int y)
	{
		if (GetParent()) {
			return GetParent().OnFocus(w, x, y);
		}
		
		return false;
	}
	
	override bool OnFocusLost(Widget w, int x, int y)
	{
		if (GetParent()) {
			return GetParent().OnFocusLost(w, x, y);
		}
		
		return false;
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		if (GetParent()) {
			return GetParent().OnMouseEnter(w, x, y);
		}
		
		return false;
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		if (GetParent()) {
			return GetParent().OnMouseLeave(w, enterW, x, y);
		}
		
		return false;
	}
	
	override bool OnMouseWheel(Widget w, int x, int y, int wheel)
	{
		if (GetParent()) {
			return GetParent().OnMouseWheel(w, x, y, wheel);
		}
		
		return false;
	}
	
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		if (GetParent()) {
			return GetParent().OnMouseButtonDown(w, x, y, button);
		}
		
		return false;
	}
	
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		if (GetParent()) {
			return GetParent().OnMouseButtonUp(w, x, y, button);
		}
		
		return false;
	}

	override bool OnController(Widget w, int control, int value)
	{
		if (GetParent()) {
			return GetParent().OnController(w, control, value);
		}
		
		return false;
	}
	
	override bool OnKeyDown(Widget w, int x, int y, int key)
	{
		if (GetParent()) {
			return GetParent().OnKeyDown(w, x, y, key);
		}
		
		return false;
	}
	
	override bool OnKeyUp(Widget w, int x, int y, int key)
	{
		if (GetParent()) {
			return GetParent().OnKeyUp(w, x, y, key);
		}
		
		return false;
	}
	
	override bool OnKeyPress(Widget w, int x, int y, int key)
	{
		if (GetParent()) {
			return GetParent().OnKeyPress(w, x, y, key);
		}
		
		return false;
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		if (GetParent()) {
			return GetParent().OnChange(w, x, y, finished);
		}
		
		return false;
	}
	
	override bool OnDrag(Widget w, int x, int y)
	{
		if (GetParent()) {
			return GetParent().OnDrag(w, x, y);
		}
		
		return false;
	}
	
	override bool OnDragging(Widget w, int x, int y, Widget reciever)
	{
		if (GetParent()) {
			return GetParent().OnDragging(w, x, y, reciever);
		}
		
		return false;
	}
	
	override bool OnDraggingOver(Widget w, int x, int y, Widget reciever)
	{
		if (GetParent()) {
			return GetParent().OnDraggingOver(w, x, y, reciever);
		}
		
		return false;
	}
	
	override bool OnDrop(Widget w, int x, int y, Widget reciever)
	{
		if (GetParent()) {
			return GetParent().OnDrop(w, x, y, reciever);
		}
		
		return false;
	}
	
	override bool OnDropReceived(Widget w, int x, int y, Widget reciever)
	{
		if (GetParent()) {
			return GetParent().OnDropReceived(w, x, y, reciever);
		}
		
		return false;
	}
	
	override bool OnResize(Widget w, int x, int y)
	{
		if (GetParent()) {
			return GetParent().OnResize(w, x, y);
		}
		
		return false;
	}
	
	override bool OnChildAdd(Widget w, Widget child)
	{
		if (GetParent()) {
			return GetParent().OnChildAdd(w, child);
		}
		
		return false;
	}
	
	override bool OnChildRemove(Widget w, Widget child)
	{
		if (GetParent()) {
			return GetParent().OnChildRemove(w, child);
		}
		
		return false;
	}
	
}