class CF_SpacerBaseWidget : CF_UIWidget
{
	protected SpacerBaseWidget _SpacerBaseWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_SpacerBaseWidget, w);
	}

	override void OnModel_Children_InsertAt(CF_ObservableCollection collection, CF_CollectionInsertAtEventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Children_InsertAt", "" + collection, evt.String());

		CF_ModelBase model = collection.GetConverter(evt.Index).GetManaged();

		string layout;
		g_Script.CallFunction(model, "GetLayout", layout, null);
		
		CF_ViewModel vm = CF.MVVM.Create(model, layout, _SpacerBaseWidget);
		if (evt.Index == collection.Count()) return;

		Widget widget = vm.GetView().GetWidget();
		Widget append = GetChildWidgetAt(evt.Index);
		_SpacerBaseWidget.AddChildAfter(widget, append);
	}

	override void OnModel_Children_Set(CF_ObservableCollection collection, CF_CollectionSetEventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Children_Set", "" + collection, evt.String());

		CF_ModelBase model = collection.GetConverter(evt.Index).GetManaged();

		string layout;
		g_Script.CallFunction(model, "GetLayout", layout, null);
		
		CF_ViewModel vm = CF.MVVM.Create(model, layout, _SpacerBaseWidget);

		Widget widget = vm.GetView().GetWidget();
		Widget append = GetChildWidgetAt(evt.Index);
		_SpacerBaseWidget.AddChildAfter(widget, append);
		_SpacerBaseWidget.RemoveChild(append);
	}
	
	override void OnModel_Children_Swap(CF_ObservableCollection collection, CF_CollectionSwapEventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Children_Swap", "" + collection, evt.String());

		if (evt.IndexA == evt.IndexB) return;
		
		Widget widgetA = GetChildWidgetAt(evt.IndexA);
		Widget widgetB = GetChildWidgetAt(evt.IndexB);

		Widget widgetA_B = GetChildWidgetAt(evt.IndexA - 1);
		Widget widgetB_B = GetChildWidgetAt(evt.IndexB - 1);

		_SpacerBaseWidget.RemoveChild(widgetA);
		_SpacerBaseWidget.RemoveChild(widgetB);

		_SpacerBaseWidget.AddChildAfter(widgetB, widgetA_B);
		_SpacerBaseWidget.AddChildAfter(widgetA, widgetB_B);
	}
};
