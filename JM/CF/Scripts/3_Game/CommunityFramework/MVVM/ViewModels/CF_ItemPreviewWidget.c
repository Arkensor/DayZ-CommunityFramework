class CF_ItemPreviewWidget : CF_Widget
{
	reference string Item;
	reference string View;
	reference string Orientation;
	reference string Position;
	reference string ForceFlipEnable;
	reference string ForceFlip;

	protected ItemPreviewWidget _ItemPreviewWidget;
	protected CF_MVVM_PropertyBase _Item = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _View = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Orientation = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Position = CF_MVVM_GetDefaultProperty();
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
		AddProperty(Orientation, "Orientation");
		AddProperty(Position, "Position");
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
		_Item.ToVariable(m_Model, Item);
	}

	void OnModel_Item(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Item", "" + sender, args.ToStr());
		#endif
		
		_Item.FromVariable(m_Model, Item);
		_ItemPreviewWidget.SetItem(EntityAI.Cast(_Item.GetClass()));
	}

	void OnView_View(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_View", "" + sender, args.ToStr());
		#endif
		
		_View.SetInt(_ItemPreviewWidget.GetView());
		_View.ToVariable(m_Model, View);
	}

	void OnModel_View(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_View", "" + sender, args.ToStr());
		#endif
		
		_View.FromVariable(m_Model, View);
		_ItemPreviewWidget.SetView(_View.GetInt());
	}

	void OnView_Orientation(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Orientation", "" + sender, args.ToStr());
		#endif
		
		_Orientation.SetVector(_ItemPreviewWidget.GetModelOrientation());
		_Orientation.ToVariable(m_Model, Orientation);
	}

	void OnModel_Orientation(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Orientation", "" + sender, args.ToStr());
		#endif
		
		_Orientation.FromVariable(m_Model, Orientation);
		_ItemPreviewWidget.SetModelOrientation(_Orientation.GetVector());
	}

	void OnView_Position(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Position", "" + sender, args.ToStr());
		#endif
		
		_Position.SetVector(_ItemPreviewWidget.GetModelPosition());
		_Position.ToVariable(m_Model, Position);
	}

	void OnModel_Position(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Position", "" + sender, args.ToStr());
		#endif
		
		_Position.FromVariable(m_Model, Position);
		_ItemPreviewWidget.SetModelPosition(_Position.GetVector());
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
		
		_ForceFlipEnable.FromVariable(m_Model, ForceFlipEnable);
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
		
		_ForceFlip.FromVariable(m_Model, ForceFlip);
		_ItemPreviewWidget.SetForceFlip(_ForceFlip.GetBool());
	}

};
