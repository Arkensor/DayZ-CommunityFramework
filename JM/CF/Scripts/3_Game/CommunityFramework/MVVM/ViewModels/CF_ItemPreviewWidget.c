class CF_ItemPreviewWidget : CF_Widget
{
	reference string Item;
	reference string View;
	reference string ModelOrientation;
	reference string ModelPosition;
	reference string ForceFlipEnable;
	reference string ForceFlip;

	protected ItemPreviewWidget _ItemPreviewWidget;
	protected CF_MVVM_PropertyBase _Item = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _View = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _ModelOrientation = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _ModelPosition = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _ForceFlipEnable = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _ForceFlip = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetProperties");
		#endif

		super.GetProperties();
		
		AddProperty(Item, "Item");
		AddProperty(View, "View");
		AddProperty(ModelOrientation, "ModelOrientation");
		AddProperty(ModelPosition, "ModelPosition");
		AddProperty(ForceFlipEnable, "ForceFlipEnable");
		AddProperty(ForceFlip, "ForceFlip");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_ItemPreviewWidget, w);
	}

	void OnView_Item(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Item").Add(sender).Add(args.GetDebugName());
		#endif
		
		_Item.SetClass(_ItemPreviewWidget.GetItem());
	}

	void OnModel_Item(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Item").Add(sender).Add(args.GetDebugName());
		#endif
		
		_ItemPreviewWidget.SetItem(EntityAI.Cast(_Item.GetClass()));
	}

	void OnView_View(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_View").Add(sender).Add(args.GetDebugName());
		#endif
		
		_View.SetInt(_ItemPreviewWidget.GetView());
	}

	void OnModel_View(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_View").Add(sender).Add(args.GetDebugName());
		#endif
		
		_ItemPreviewWidget.SetView(_View.GetInt());
	}

	void OnView_ModelOrientation(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnViewModel_Orientation").Add(sender).Add(args.GetDebugName());
		#endif
		
		_ModelOrientation.SetVector(_ItemPreviewWidget.GetModelOrientation());
	}

	void OnModel_ModelOrientation(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_ModelOrientation").Add(sender).Add(args.GetDebugName());
		#endif
		
		_ItemPreviewWidget.SetModelOrientation(_ModelOrientation.GetVector());
	}

	void OnView_ModelPosition(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_ModelPosition").Add(sender).Add(args.GetDebugName());
		#endif
		
		_ModelPosition.SetVector(_ItemPreviewWidget.GetModelPosition());
	}

	void OnModel_ModelPosition(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_ModelPosition").Add(sender).Add(args.GetDebugName());
		#endif
		
		_ItemPreviewWidget.SetModelPosition(_ModelPosition.GetVector());
	}

	void OnView_ForceFlipEnable(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_ForceFlipEnable").Add(sender).Add(args.GetDebugName());
		#endif
		
	}

	void OnModel_ForceFlipEnable(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_ForceFlipEnable").Add(sender).Add(args.GetDebugName());
		#endif
		
		_ItemPreviewWidget.SetForceFlipEnable(_ForceFlipEnable.GetBool());
	}

	void OnView_ForceFlip(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_ForceFlip").Add(sender).Add(args.GetDebugName());
		#endif
		
	}

	void OnModel_ForceFlip(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_ForceFlip").Add(sender).Add(args.GetDebugName());
		#endif
		
		_ItemPreviewWidget.SetForceFlip(_ForceFlip.GetBool());
	}

};
