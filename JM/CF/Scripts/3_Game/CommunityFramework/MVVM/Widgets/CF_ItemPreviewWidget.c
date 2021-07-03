class CF_ItemPreviewWidget : CF_Widget
{
	reference string Item;
	reference string View;
	reference string Orientation;
	reference string Position;
	reference string ForceFlipEnable;
	reference string ForceFlip;

	protected ItemPreviewWidget _ItemPreviewWidget;
	protected bool _ForceFlipEnable;
	protected bool _ForceFlip;

	override void GetProperties()
	{
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
		super.OnWidgetScriptInit(w);
		Class.CastTo(_ItemPreviewWidget, w);
	}

	void OnView_Item(CF_ModelBase model, CF_EventArgs evt)
	{
		EntityAI _value = _ItemPreviewWidget.GetItem();
		EnScript.SetClassVar(model, Item, 0, _value);
	}

	void OnModel_Item(CF_ModelBase model, CF_EventArgs evt)
	{
		EntityAI _value;
		EnScript.GetClassVar(model, Item, 0, _value);
		_ItemPreviewWidget.SetItem(_value);
	}

	void OnView_View(CF_ModelBase model, CF_EventArgs evt)
	{
		int _value = _ItemPreviewWidget.GetView();
		EnScript.SetClassVar(model, View, 0, _value);
	}

	void OnModel_View(CF_ModelBase model, CF_EventArgs evt)
	{
		int _value;
		EnScript.GetClassVar(model, View, 0, _value);
		_ItemPreviewWidget.SetView(_value);
	}

	void OnView_Orientation(CF_ModelBase model, CF_EventArgs evt)
	{
		vector _value = _ItemPreviewWidget.GetModelOrientation();
		EnScript.SetClassVar(model, Orientation, 0, _value);
	}

	void OnModel_Orientation(CF_ModelBase model, CF_EventArgs evt)
	{
		vector _value;
		EnScript.GetClassVar(model, Orientation, 0, _value);
		_ItemPreviewWidget.SetModelOrientation(_value);
	}

	void OnView_Position(CF_ModelBase model, CF_EventArgs evt)
	{
		vector _value = _ItemPreviewWidget.GetModelPosition();
		EnScript.SetClassVar(model, Position, 0, _value);
	}

	void OnModel_Position(CF_ModelBase model, CF_EventArgs evt)
	{
		vector _value;
		EnScript.GetClassVar(model, Position, 0, _value);
		_ItemPreviewWidget.SetModelPosition(_value);
	}

	void OnView_ForceFlipEnable(CF_ModelBase model, CF_EventArgs evt)
	{
		EnScript.SetClassVar(model, ForceFlipEnable, 0, _ForceFlipEnable);
	}

	void OnModel_ForceFlipEnable(CF_ModelBase model, CF_EventArgs evt)
	{
		EnScript.GetClassVar(model, ForceFlipEnable, 0, _ForceFlipEnable);
		_ItemPreviewWidget.SetForceFlipEnable(_ForceFlipEnable);
	}

	void OnView_ForceFlip(CF_ModelBase model, CF_EventArgs evt)
	{
		EnScript.SetClassVar(model, ForceFlip, 0, _ForceFlip);
	}

	void OnModel_ForceFlip(CF_ModelBase model, CF_EventArgs evt)
	{
		EnScript.GetClassVar(model, ForceFlip, 0, _ForceFlip);
		_ItemPreviewWidget.SetForceFlip(_ForceFlip);
	}

};
