static autoptr CF_MVVM g_CF_MVVM = null;

class CF_MVVM
{
	//! Do not directly use this variable, interface with the functions..
	/*private*/ static ref map<CF_ModelBase, ref CF_MVVM_Linker> s_ModelMap;

	static const int MVVM_UI_MENU_ID = 10042;

	static ref array<ref CF_MVVM_Linker> s_Destroying;

#ifdef COMPONENT_SYSTEM
	static bool WB_NEXT_IN_SCRIPT = false;
#endif

	private void CF_MVVM()
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_0(this, "CF_MVVM");
#endif
	}

	[CF_EventSubscriber(CF_MVVM._Init, CF_LifecycleEvents.OnGameCreate)]
	static void _Init()
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_0(g_CF_MVVM, "_Init");
#endif

		if (g_CF_MVVM)
			return;

		s_ModelMap = new map<CF_ModelBase, ref CF_MVVM_Linker>();
		s_Destroying = new array<ref CF_MVVM_Linker>();

#ifdef COMPONENT_SYSTEM
		CF_Log.Level = CF_LogLevel.TRACE;
#endif

		g_CF_MVVM = new CF_MVVM();
	}

	[CF_EventSubscriber(CF_Windows._Cleanup, CF_LifecycleEvents.OnGameDestroy)]
	static void _Cleanup()
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_0(g_CF_MVVM, "_Cleanup");
#endif

		s_ModelMap = null;
		s_Destroying = null;

		g_CF_MVVM = null;
	}

	static CF_MVVM_Linker GetPropertyCollection(CF_ModelBase model)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(g_CF_MVVM, "GetPropertyCollection").Add(model);
#endif

		return s_ModelMap[model];
	}

	/**
	 * @brief Creates a new View for the model. Returns existing view if it already exists for the model
	 */
	static CF_MVVM_Linker Create(CF_ModelBase model, string layout)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(g_CF_MVVM, "Create").Add(model).Add(layout);
#endif

#ifdef COMPONENT_SYSTEM
		if (s_ModelMap == null)
		{
			CF._GameInit();
		}
#endif

		CF_MVVM_Linker link;
		if (!s_ModelMap.Find(model, link))
		{
			link = new CF_MVVM_Linker();
			s_ModelMap.Insert(model, link);
		}
		else if (link.IsValid())
		{
			link.Relink();
			return link;
		}
		else
		{
			link.Unlink();
		}

#ifdef COMPONENT_SYSTEM
		CF_MVVM.WB_NEXT_IN_SCRIPT = true;
#endif

		Widget widget = GetGame().GetWorkspace().CreateWidgets(layout, null);

		if (!widget)
			return null;

		CF_ViewModel view;
		widget.GetScript(view);

		link.Link(view, model);

#ifdef COMPONENT_SYSTEM
		CF_MVVM.WB_NEXT_IN_SCRIPT = false;
#endif

		return link;
	}

	/**
	 * @brief Creates a new View for the model. Returns existing view if it already exists for the model. Updates the parent widget
	 */
	static CF_MVVM_Linker Create(CF_ModelBase model, string layout, Widget parent)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_3(g_CF_MVVM, "Create").Add(model).Add(layout).Add(parent);
#endif

#ifdef COMPONENT_SYSTEM
		if (s_ModelMap == null)
		{
			CF._GameInit();
		}
#endif

		CF_MVVM_Linker link;
		if (!s_ModelMap.Find(model, link))
		{
			link = new CF_MVVM_Linker();
			s_ModelMap.Insert(model, link);
		}
		else if (link.ChangeParent(parent))
		{
			link.Relink();
			return link;
		}
		else
		{
			link.Unlink();
		}

		WorkspaceWidget wSpace = GetGame().GetWorkspace();
		// A mess to fix an issue in Workbench, can also substitute for loading screen support
		if (wSpace == null)
		{
			wSpace = GetGame().GetLoadingWorkspace();
			if (!wSpace)
				wSpace = CF.Game().GetWorkspace();
			if (!wSpace)
				wSpace = CF.Game().GetLoadingWorkspace();

			if (!wSpace)
				return null;
		}

#ifdef COMPONENT_SYSTEM
		CF_MVVM.WB_NEXT_IN_SCRIPT = true;
#endif

		Widget widget = wSpace.CreateWidgets(layout, parent);
		if (!widget)
			return null;

		CF_ViewModel view;
		widget.GetScript(view);

		link.Link(view, model);

#ifdef COMPONENT_SYSTEM
		CF_MVVM.WB_NEXT_IN_SCRIPT = false;
#endif

		return link;
	}

	static CF_MVVM_Linker Connect(CF_ModelBase model, Widget widget)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(g_CF_MVVM, "Connect").Add(model).Add(widget);
#endif

#ifdef COMPONENT_SYSTEM
		if (s_ModelMap == null)
		{
			CF._GameInit();
		}
#endif

		CF_MVVM_Linker link;
		if (!s_ModelMap.Find(model, link))
		{
			link = new CF_MVVM_Linker();
			s_ModelMap.Insert(model, link);
		}

#ifdef COMPONENT_SYSTEM //! Workbench editing
		if (!CF_MVVM.WB_NEXT_IN_SCRIPT)
		{
#endif

			link.Unlink();

#ifdef COMPONENT_SYSTEM //! Workbench editing
		}
#endif

		if (!widget)
			return null;

		CF_ViewModel view;
		widget.GetScript(view);

		link.Link(view, model);

		return link;
	}

	static CF_MVVM_Linker Connect(CF_ModelBase model, CF_ViewModel view)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(g_CF_MVVM, "Connect").Add(model).Add(view);
#endif

#ifdef COMPONENT_SYSTEM
		if (s_ModelMap == null)
		{
			CF._GameInit();
		}
#endif

		CF_MVVM_Linker link;
		if (!s_ModelMap.Find(model, link))
		{
			link = new CF_MVVM_Linker();
			s_ModelMap.Insert(model, link);
		}

#ifdef COMPONENT_SYSTEM //! Workbench editing
		if (!CF_MVVM.WB_NEXT_IN_SCRIPT)
		{
#endif

			link.Unlink();

#ifdef COMPONENT_SYSTEM //! Workbench editing
		}
#endif

		link.Link(view, model);

		return link;
	}

	static CF_ModelBase OpenMenu(string modelName)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(g_CF_MVVM, "OpenMenu").Add(modelName);
#endif

		CF_ModelBase model = CF_ModelBase.Cast(modelName.ToType().Spawn());
		if (!model)
			return null;

		return OpenMenu(model);
	}

	static CF_ModelBase OpenMenu(typename modelType)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(g_CF_MVVM, "OpenMenu").Add(modelType);
#endif

		CF_ModelBase model = CF_ModelBase.Cast(modelType.Spawn());
		if (!model)
			return null;

		return OpenMenu(model);
	}

	static CF_ModelBase OpenMenu(CF_ModelBase model)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(g_CF_MVVM, "OpenMenu").Add(model);
#endif

		if (!model)
			return null;

		string layoutFile;
		g_Script.CallFunction(model, "GetLayoutFile", layoutFile, null);
		if (layoutFile == string.Empty)
			return null;

		return OpenMenu(model, layoutFile);
	}

	static CF_ModelBase OpenMenu(CF_ModelBase model, string layoutFile)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(g_CF_MVVM, "OpenMenu").Add(model).Add(layoutFile);
#endif

		if (!GetGame() || !model)
			return null;

		CF_MVVM_Menu menu;
		if (!Class.CastTo(menu, GetGame().GetUIManager().EnterScriptedMenu(CF_MVVM.MVVM_UI_MENU_ID, null)))
			return null;

		menu.SetModel(model, layoutFile);

		return model;
	}

	static void Destroy(CF_ModelBase model)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(g_CF_MVVM, "Destroy").Add(model);
#endif

#ifdef COMPONENT_SYSTEM
		if (s_ModelMap == null)
		{
			CF._GameInit();
		}
#endif

		CF_MVVM_Linker link;
		if (!s_ModelMap.Find(model, link))
			return;

		link.Unlink();
	}

	/**
	 * @note Make sure to call '_UnlockForDestroy' in return Linker
	 */
	static CF_MVVM_Linker _LockForDestroy(CF_ModelBase model)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(g_CF_MVVM, "Destroy").Add(model);
#endif

#ifdef COMPONENT_SYSTEM
		if (s_ModelMap == null)
		{
			CF._GameInit();
		}
#endif

		CF_MVVM_Linker link;
		if (!s_ModelMap.Find(model, link))
			return null;

		link._LockForDestroy();

		return link;
	}

/**
	 * @brief	Fixes issue when script is recompiled while the layout file is opened.
	 * 
	 * @note	To only be using during Workbench editing of layout files.
	 */
#ifdef COMPONENT_SYSTEM
	static void _CheckInit()
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_0(g_CF_MVVM, "_CheckInit");
#endif

		if (s_ModelMap == null)
		{
			CF._GameInit();
		}
	}
#endif

	static void NotifyPropertyChanged(CF_ModelBase model, string propertyName, CF_EventArgs args = null)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(g_CF_MVVM, "NotifyPropertyChanged").Add(model).Add(propertyName).Add(args);
#endif

#ifdef COMPONENT_SYSTEM
		if (s_ModelMap == null)
		{
			CF._GameInit();
		}
#endif

		CF_MVVM_Linker pc;
		if (!s_ModelMap.Find(model, pc))
			return;

		if (args == null)
			args = new CF_EventArgs();

		pc.NotifyPropertyChanged(propertyName, args);
	}

	static void NotifyPropertyChanged(CF_ModelBase model)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(g_CF_MVVM, "NotifyPropertyChanged").Add(model);
#endif

#ifdef COMPONENT_SYSTEM
		if (s_ModelMap == null)
		{
			CF._GameInit();
		}
#endif

		CF_MVVM_Linker pc;
		if (!s_ModelMap.Find(model, pc))
			return;

		pc.NotifyPropertyChanged(new CF_EventArgs());
	}
};
