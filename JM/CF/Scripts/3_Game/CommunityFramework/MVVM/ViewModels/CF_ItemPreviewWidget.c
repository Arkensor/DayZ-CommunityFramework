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
		CF_Trace trace(this, "GetProperties");
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
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_ItemPreviewWidget, w);
	}

	void OnView_Item(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Item", "" + sender, args.ToStr());
		#endif
		
		_Item.SetClass(_ItemPreviewWidget.GetItem());
	}

	void OnModel_Item(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Item", "" + sender, args.ToStr());
		#endif
		
		_ItemPreviewWidget.SetItem(EntityAI.Cast(_Item.GetClass()));
	}

	void OnView_View(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_View", "" + sender, args.ToStr());
		#endif
		
		_View.SetInt(_ItemPreviewWidget.GetView());
	}

	void OnModel_View(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_View", "" + sender, args.ToStr());
		#endif
		
		_ItemPreviewWidget.SetView(_View.GetInt());
	}

	void OnView_ModelOrientation(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnViewModel_Orientation", "" + sender, args.ToStr());
		#endif
		
		_ModelOrientation.SetVector(_ItemPreviewWidget.GetModelOrientation());
	}

	void OnModel_ModelOrientation(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_ModelOrientation", "" + sender, args.ToStr());
		#endif
		
		_ItemPreviewWidget.SetModelOrientation(_ModelOrientation.GetVector());
	}

	void OnView_ModelPosition(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_ModelPosition", "" + sender, args.ToStr());
		#endif
		
		_ModelPosition.SetVector(_ItemPreviewWidget.GetModelPosition());
	}

	void OnModel_ModelPosition(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_ModelPosition", "" + sender, args.ToStr());
		#endif
		
		_ItemPreviewWidget.SetModelPosition(_ModelPosition.GetVector());
	}

	void OnView_ForceFlipEnable(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_ForceFlipEnable", "" + sender, args.ToStr());
		#endif
		
	}

	void OnModel_ForceFlipEnable(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_ForceFlipEnable", "" + sender, args.ToStr());
		#endif
		
		_ItemPreviewWidget.SetForceFlipEnable(_ForceFlipEnable.GetBool());
	}

	void OnView_ForceFlip(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_ForceFlip", "" + sender, args.ToStr());
		#endif
		
	}

	void OnModel_ForceFlip(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_ForceFlip", "" + sender, args.ToStr());
		#endif
		
		_ItemPreviewWidget.SetForceFlip(_ForceFlip.GetBool());
	}

};
