class CF_SpacerBaseWidget : CF_UIWidget
{
	protected SpacerBaseWidget _SpacerBaseWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_SpacerBaseWidget, w);
	}

	override void OnModel_Children_InsertAt(CF_ObservableCollection sender, CF_CollectionInsertAtEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Children_InsertAt", "" + sender, args.ToStr());
		#endif

		CF_TypeConverter conv = sender.GetConverter(args.Index);
		if (!conv) return;

		CF_ModelBase model = conv.GetManaged();

		string layout;
		g_Script.CallFunction(model, "GetLayout", layout, null);
		
		CF_MVVM.Create(model, layout);
		if (args.Index == sender.Count()) return;

		Widget widget = CF_MVVM.GetPropertyCollection(model).GetWidget();
		if (!widget) return;
		
		Widget append = GetChildWidgetAt(args.Index);
		_SpacerBaseWidget.AddChildAfter(widget, append);
	}

	override void OnModel_Children_Set(CF_ObservableCollection sender, CF_CollectionSetEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Children_Set", "" + sender, args.ToStr());
		#endif

		CF_TypeConverter conv = sender.GetConverter(args.Index);
		if (!conv) return;

		CF_ModelBase model = conv.GetManaged();

		string layout;
		g_Script.CallFunction(model, "GetLayout", layout, null);
		
		CF_MVVM.Create(model, layout);

		Widget widget = CF_MVVM.GetPropertyCollection(model).GetWidget();
		if (!widget) return;

		Widget append = GetChildWidgetAt(args.Index);
		_SpacerBaseWidget.AddChildAfter(widget, append);
		_SpacerBaseWidget.RemoveChild(append);
	}
	
	override void OnModel_Children_Swap(CF_ObservableCollection sender, CF_CollectionSwapEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Children_Swap", "" + sender, args.ToStr());
		#endif

		if (args.IndexA == args.IndexB) return;
		
		Widget widgetA = GetChildWidgetAt(args.IndexA);
		Widget widgetB = GetChildWidgetAt(args.IndexB);

		Widget widgetA_B = GetChildWidgetAt(args.IndexA - 1);
		Widget widgetB_B = GetChildWidgetAt(args.IndexB - 1);

		_SpacerBaseWidget.RemoveChild(widgetA);
		_SpacerBaseWidget.RemoveChild(widgetB);

		_SpacerBaseWidget.AddChildAfter(widgetB, widgetA_B);
		_SpacerBaseWidget.AddChildAfter(widgetA, widgetB_B);
	}
};
