class CF_ItemPreviewWidget : CF_Widget
{
	reference string Item;
	reference string View;
	reference string Orientation;
	reference string Position;
	reference string ForceFlipEnable;
	reference string ForceFlip;

	protected ItemPreviewWidget _ItemPreviewWidget;
	protected CF_TypeConverter _Item;
	protected CF_TypeConverter _View;
	protected CF_TypeConverter _Orientation;
	protected CF_TypeConverter _Position;
	protected CF_TypeConverter _ForceFlipEnable;
	protected CF_TypeConverter _ForceFlip;

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

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
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_ItemPreviewWidget, w);
	}

	void OnView_Item(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Item", "" + model, evt.String());
		
		_Item.SetClass(_ItemPreviewWidget.GetItem());
		_Item.ToVariable(model, Item);
	}

	void OnModel_Item(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Item", "" + model, evt.String());
		
		_Item.FromVariable(model, Item);
		_ItemPreviewWidget.SetItem(EntityAI.Cast(_Item.GetClass()));
	}

	void OnView_View(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_View", "" + model, evt.String());
		
		_View.SetInt(_ItemPreviewWidget.GetView());
		_View.ToVariable(model, View);
	}

	void OnModel_View(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_View", "" + model, evt.String());
		
		_View.FromVariable(model, View);
		_ItemPreviewWidget.SetView(_View.GetInt());
	}

	void OnView_Orientation(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Orientation", "" + model, evt.String());
		
		_Orientation.SetVector(_ItemPreviewWidget.GetModelOrientation());
		_Orientation.ToVariable(model, Orientation);
	}

	void OnModel_Orientation(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Orientation", "" + model, evt.String());
		
		_Orientation.FromVariable(model, Orientation);
		_ItemPreviewWidget.SetModelOrientation(_Orientation.GetVector());
	}

	void OnView_Position(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Position", "" + model, evt.String());
		
		_Position.SetVector(_ItemPreviewWidget.GetModelPosition());
		_Position.ToVariable(model, Position);
	}

	void OnModel_Position(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Position", "" + model, evt.String());
		
		_Position.FromVariable(model, Position);
		_ItemPreviewWidget.SetModelPosition(_Position.GetVector());
	}

	void OnView_ForceFlipEnable(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_ForceFlipEnable", "" + model, evt.String());
		
	}

	void OnModel_ForceFlipEnable(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_ForceFlipEnable", "" + model, evt.String());
		
		_ForceFlipEnable.FromVariable(model, ForceFlipEnable);
		_ItemPreviewWidget.SetForceFlipEnable(_ForceFlipEnable.GetBool());
	}

	void OnView_ForceFlip(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_ForceFlip", "" + model, evt.String());
		
	}

	void OnModel_ForceFlip(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_ForceFlip", "" + model, evt.String());
		
		_ForceFlip.FromVariable(model, ForceFlip);
		_ItemPreviewWidget.SetForceFlip(_ForceFlip.GetBool());
	}

};
