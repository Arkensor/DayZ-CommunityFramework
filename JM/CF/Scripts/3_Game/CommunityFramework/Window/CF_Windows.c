typedef int CF_WindowHandle;

static string CF_WindowHandleToString(CF_WindowHandle handle)
{
	//int h = handle;
	return "";// + h;
}

static autoptr CF_Windows g_CF_Windows = null;

class CF_Windows
{
	private static ref map<CF_WindowHandle, ref CF_Window> s_Windows;

	private static Widget s_Container;

	private static ref array<CF_WindowHandle> s_Z;
	private static CF_WindowHandle s_HandleTicker;

	private void CF_Windows()
	{

	}

	[CF_EventSubscriber(CF_Windows._Init, CF_LifecycleEvents.OnGameCreate)]
	static void _Init()
	{
		if (g_CF_Windows) return;

		s_Windows = new map<CF_WindowHandle, ref CF_Window>();
		s_Z = new array<CF_WindowHandle>();
		s_HandleTicker = 1;

		g_CF_Windows = new CF_Windows();
	}

	[CF_EventSubscriber(CF_Windows._Cleanup, CF_LifecycleEvents.OnGameDestroy)]
	static void _Cleanup()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(g_CF_Windows, "_Cleanup");
		#endif
		
		s_Windows = null;
		s_Z = null;
		s_HandleTicker = 1;
		
		g_CF_Windows = null;
	}

	[CF_EventSubscriber(CF_Windows._MissionInit, CF_LifecycleEvents.OnMissionCreate)]
	static void _MissionInit()
	{
		s_Container = GetGame().GetWorkspace().CreateWidgets( "JM/CF/GUI/layouts/windows/container.layout", NULL );
	}

	[CF_EventSubscriber(CF_Windows._MissionCleanup, CF_LifecycleEvents.OnMissionDestroy)]
	static void _MissionCleanup()
	{
		s_Container.Unlink();
	}

	static Widget _GetContainer()
	{
		return s_Container;
	}

	/**
	 * @brief Generates a handle ID for the window if input not valid
	 */
	static void Handle(inout CF_WindowHandle handle)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(g_CF_Windows, "Handle", CF_WindowHandleToString(handle));
		#endif
		
		if (handle != 0) return;

		handle = s_HandleTicker;
		s_HandleTicker++;
	}

	/**
	 * @brief Retrieves the Window for the specified handle, if the window doesn't exist, creates it.
	 * 
	 * @return True if the window was created, false if it already exists
	 */
	static bool Retrieve(CF_WindowHandle handle)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(g_CF_Windows, "Retrieve", CF_WindowHandleToString(handle));
		#endif
		
		if (s_Windows.Contains(handle)) return false;

		CF_Window window = new CF_Window(handle);
		s_Windows.Insert(handle, window);
		s_Z.InsertAt(handle, 0);

		CF_MVVM.Create(window, window.GetLayout(), s_Container);

		return true;
	}

	/**
	 * @brief Retrieves the Window for the specified handle, if the window doesn't exist, creates it.
	 * @return True if the window was created, false if it already exists
	 */
	static bool Retrieve(CF_WindowHandle handle, out CF_Window window)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(g_CF_Windows, "Retrieve", CF_WindowHandleToString(handle));
		#endif
		
		if (s_Windows.Find(handle, window)) return false;

		window = new CF_Window(handle);
		s_Windows.Insert(handle, window);
		s_Z.InsertAt(handle, 0);

		CF_MVVM.Create(window, window.GetLayout());

		return true;
	}

	/**
	 * Destroys the window for the specified handle
	 */
	static void Destroy(CF_WindowHandle handle)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(g_CF_Windows, "Destroy", CF_WindowHandleToString(handle));
		#endif
		
		CF_Window window;
		if (!s_Windows.Find(handle, window)) return;

		s_Windows.Remove(handle);
		s_Z.RemoveItem(handle);

		CF_MVVM.Destroy(window);
	}

	/**
	 * Brings the window to foremost buffer
	 */
	static void Focus(CF_WindowHandle handle)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(g_CF_Windows, "Focus", CF_WindowHandleToString(handle));
		#endif
		
		int z = s_Z.Find(handle);
		if (z <= 0) return;

		s_Z.RemoveOrdered(z);
		s_Z.InsertAt(handle, 0);
	}

	/**
	 * Gets the z-index for the window handle
	 */
	static int ZIndex(CF_WindowHandle handle)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(g_CF_Windows, "ZIndex", CF_WindowHandleToString(handle));
		#endif
		
		return s_Z.Find(handle);
	}
};