
// Base type for all primary view Types (ScriptView, Controller, ViewBinding)
class ScriptedViewBase : Managed
{
	// Enable verbose logging
	[NonSerialized()]
	reference bool Debug_Logging;

	// Source Widget
	[NonSerialized()]
	protected Widget m_LayoutRoot;
	Widget GetLayoutRoot()
	{
		return m_LayoutRoot;
	}

	// Source Widget Controller
	[NonSerialized()]
	protected autoptr WidgetController m_WidgetController;
	WidgetController GetWidgetController()
	{
		return m_WidgetController;
	}

	// ScriptedViewBase Type Converter
	[NonSerialized()]
	protected autoptr TypeConverter m_TypeConverter;
	TypeConverter GetTypeConversion()
	{
		return m_TypeConverter;
	}

	// ScriptedViewBase parent
	[NonSerialized()]
	protected ScriptedViewBase m_ParentScriptedViewBase;
	ScriptedViewBase GetParent()
	{
		if (!m_ParentScriptedViewBase && m_LayoutRoot) 
		{
			// Experimental update for trying to recursively find a root... causes Stackoverflow
			//m_ParentScriptedViewBase = GetParentScriptView(m_LayoutRoot);
		}
		
		return m_ParentScriptedViewBase;
	}

	[NonSerialized()]
	protected autoptr ScriptedViewBaseHandler m_ScriptedViewBaseHandler;
	ScriptedViewBaseHandler GetHandler()
	{
		return m_ScriptedViewBaseHandler;
	}

	void SetParent(ScriptedViewBase parent)
	{
		m_ParentScriptedViewBase = parent;

		// Propagates debug logging even if disabled locally
		Debug_Logging = Debug_Logging || m_ParentScriptedViewBase.Debug_Logging;
	}

	void ScriptedViewBase()
	{
		if (Debug_Logging)
			PrintFormat("[Log] %1", this);

		m_TypeConverter = LayoutBindingManager.GetTypeConversion(Type());
		if (!m_TypeConverter)
		{
			Error("Could not generate TypeConverter on %1", Type().ToString());
			return;
		}

		m_ScriptedViewBaseHandler = new ScriptedViewBaseHandler(this);
		m_TypeConverter.Set(this);
	}

	void ~ScriptedViewBase()
	{
		if (Debug_Logging)
			PrintFormat("[Log] ~%1", this);
	}

	void OnWidgetScriptInit(Widget w)
	{
		Trace("OnWidgetScriptInit %1", w.ToString());
		m_LayoutRoot = w;
		m_LayoutRoot.SetHandler(m_ScriptedViewBaseHandler);

		m_WidgetController = LayoutBindingManager.GetWidgetController(m_LayoutRoot);
		if (!m_WidgetController)
		{
			Error("Could not find WidgetController for type %1\n\nOverride LayoutBindingManager.RegisterWidgetControllers to register custom WidgetControllers", m_LayoutRoot.GetTypeName());
			return;
		}
	}

	ScriptedViewBase GetScriptedRoot()
	{
		ScriptedViewBase viewBase = this;
		FindScriptedRoot(viewBase);
		return viewBase;
	}

	static void FindScriptedRoot(out ScriptedViewBase viewBase)
	{
		if (viewBase && viewBase.GetParent())
		{
			viewBase = viewBase.GetParent();
			FindScriptedRoot(viewBase);
		}
	}
	
	// recursive function searches up the tree for the first available script view
	private static ScriptedViewBase GetParentScriptView(Widget widget)
	{		
		if (!widget)
		{
			return null;
		}
		
		ScriptedViewBase scripted_view;
		widget.GetScript(scripted_view);
		
		if (scripted_view) 
		{
			return scripted_view;
		}
		
		widget = widget.GetParent();
		return GetParentScriptView(widget);
	}

	void Trace(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		//#ifdef COMPONENT_SYSTEM
		if (Debug_Logging) // || LBMLogLevel >= LogLevel.TRACE
			PrintFormat("[Trace] %1 - %2 ", Type(), string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
		//#endif
	}

	void Log(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		//#ifdef COMPONENT_SYSTEM
		if (Debug_Logging) // || LBMLogLevel >= LogLevel.INFO
			PrintFormat("[Log] %1 - %2", Type(), string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
		//#endif
	}

	void Error(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		string msg = string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9);
		string header = string.Format("[Error] %1", Type());
		Error2(header, msg);

#ifdef COMPONENT_SYSTEM
		Workbench.Dialog(header, msg);
#endif
	}

	bool OnClick(Widget w, int x, int y, int button)
	{
		Trace("OnClick: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnClick(w, x, y, button);
		}

		return false;
	}

	bool OnModalResult(Widget w, int x, int y, int code, int result)
	{
		Trace("OnModalResult: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnModalResult(w, x, y, code, result);
		}

		return false;
	}

	bool OnDoubleClick(Widget w, int x, int y, int button)
	{
		Trace("OnDoubleClick: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnDoubleClick(w, x, y, button);
		}

		return false;
	}

	bool OnSelect(Widget w, int x, int y)
	{
		Trace("OnSelect: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnSelect(w, x, y);
		}

		return false;
	}

	bool OnItemSelected(Widget w, int x, int y, int row, int column, int oldRow, int oldColumn)
	{
		Trace("OnItemSelected: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnItemSelected(w, x, y, row, column, oldRow, oldColumn);
		}

		return false;
	}

	bool OnFocus(Widget w, int x, int y)
	{
		Trace("OnFocus: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnFocus(w, x, y);
		}

		return false;
	}

	bool OnFocusLost(Widget w, int x, int y)
	{
		Trace("OnFocusLost: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnFocusLost(w, x, y);
		}

		return false;
	}

	bool OnMouseEnter(Widget w, int x, int y)
	{
		Trace("OnMouseEnter: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnMouseEnter(w, x, y);
		}

		return false;
	}

	bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		Trace("OnMouseLeave: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnMouseLeave(w, enterW, x, y);
		}

		return false;
	}

	bool OnMouseWheel(Widget w, int x, int y, int wheel)
	{
		Trace("OnMouseWheel: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnMouseWheel(w, x, y, wheel);
		}

		return false;
	}

	bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		Trace("OnMouseButtonDown: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnMouseButtonDown(w, x, y, button);
		}

		return false;
	}

	bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		Trace("OnMouseButtonUp: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnMouseButtonUp(w, x, y, button);
		}

		return false;
	}

	bool OnController(Widget w, int control, int value)
	{
		Trace("OnController: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnController(w, control, value);
		}

		return false;
	}

	bool OnKeyDown(Widget w, int x, int y, int key)
	{
		Trace("OnKeyDown: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnKeyDown(w, x, y, key);
		}

		return false;
	}

	bool OnKeyUp(Widget w, int x, int y, int key)
	{
		Trace("OnKeyUp: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnKeyUp(w, x, y, key);
		}

		return false;
	}

	bool OnKeyPress(Widget w, int x, int y, int key)
	{
		Trace("OnKeyPress: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnKeyPress(w, x, y, key);
		}

		return false;
	}

	bool OnChange(Widget w, int x, int y, bool finished)
	{
		Trace("OnChange: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnChange(w, x, y, finished);
		}

		return false;
	}

	bool OnDrag(Widget w, int x, int y)
	{
		Trace("OnDrag: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnDrag(w, x, y);
		}

		return false;
	}

	bool OnDragging(Widget w, int x, int y, Widget reciever)
	{
		// Disabled bc it wont stfu
		//Trace("OnDragging: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnDragging(w, x, y, reciever);
		}

		return false;
	}

	bool OnDraggingOver(Widget w, int x, int y, Widget reciever)
	{
		// Disabled bc it wont stfu
		//Trace("OnDraggingOver: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnDraggingOver(w, x, y, reciever);
		}

		return false;
	}

	bool OnDrop(Widget w, int x, int y, Widget reciever)
	{
		Trace("OnDrop: %1 - Reciever: %2", w.GetName(), reciever.ToString());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnDrop(w, x, y, reciever);
		}

		return false;
	}

	bool OnDropReceived(Widget w, int x, int y, Widget reciever)
	{
		Trace("OnDropReceived: %1 - Reciever: %2", w.GetName(), reciever.ToString());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnDropReceived(w, x, y, reciever);
		}

		return false;
	}

	bool OnResize(Widget w, int x, int y)
	{
		// Disabled bc it wont stfu
		//Trace("OnResize: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnResize(w, x, y);
		}

		return false;
	}

	bool OnChildAdd(Widget w, Widget child)
	{
		Trace("OnChildAdd: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnChildAdd(w, child);
		}

		return false;
	}

	bool OnChildRemove(Widget w, Widget child)
	{
		Trace("OnChildRemove: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnChildRemove(w, child);
		}

		return false;
	}

	bool OnUpdate(Widget w)
	{
		// Disabled bc it wont stfu
		//Trace("OnUpdate: %1", w.GetName());
		if (m_ParentScriptedViewBase)
		{
			return m_ParentScriptedViewBase.OnUpdate(w);
		}

		return false;
	}
};