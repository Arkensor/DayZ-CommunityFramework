class CF_PlayerPreviewWidget : CF_Widget
{
	reference string Player;
	reference string HandItem;
	reference string Orientation;
	reference string Position;

	protected PlayerPreviewWidget _PlayerPreviewWidget;
	protected CF_TypeConverter _Player;
	protected CF_TypeConverter _HandItem;
	protected CF_TypeConverter _Orientation;
	protected CF_TypeConverter _Position;

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(Player, "Player");
		AddProperty(HandItem, "HandItem");
		AddProperty(Orientation, "Orientation");
		AddProperty(Position, "Position");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_PlayerPreviewWidget, w);
	}

	void OnView_Player(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Player", "" + model, evt.String());

		_Player.SetClass(_PlayerPreviewWidget.GetDummyPlayer());
		_Player.ToVariable(model, Player);
	}

	void OnModel_Player(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Player", "" + model, evt.String());

		_Player.FromVariable(model, Player);
		_PlayerPreviewWidget.SetPlayer(DayZPlayer.Cast(_Player.GetClass()));
	}

	void OnView_HandItem(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_HandItem", "" + model, evt.String());

	}

	void OnModel_HandItem(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_HandItem", "" + model, evt.String());

		_HandItem.FromVariable(model, HandItem);
		_PlayerPreviewWidget.UpdateItemInHands(EntityAI.Cast(_HandItem.GetClass()));
	}

	void OnView_Orientation(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Orientation", "" + model, evt.String());
		
		_Orientation.SetVector(_PlayerPreviewWidget.GetModelOrientation());
		_Orientation.ToVariable(model, Orientation);
	}

	void OnModel_Orientation(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Orientation", "" + model, evt.String());
		
		_Orientation.FromVariable(model, Orientation);
		_PlayerPreviewWidget.SetModelOrientation(_Orientation.GetVector());
	}

	void OnView_Position(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Position", "" + model, evt.String());
		
		_Position.SetVector(_PlayerPreviewWidget.GetModelPosition());
		_Position.ToVariable(model, Position);
	}

	void OnModel_Position(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Position", "" + model, evt.String());
		
		_Position.FromVariable(model, Position);
		_PlayerPreviewWidget.SetModelPosition(_Position.GetVector());
	}
};
