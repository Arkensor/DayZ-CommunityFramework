class CF_PlayerPreviewWidget : CF_Widget
{
	reference string Player;
	reference string HandItem;
	reference string Orientation;
	reference string Position;

	protected PlayerPreviewWidget _PlayerPreviewWidget;
	protected CF_TypeConverter _Player = CF_GetDefaultTC();
	protected CF_TypeConverter _HandItem = CF_GetDefaultTC();
	protected CF_TypeConverter _Orientation = CF_GetDefaultTC();
	protected CF_TypeConverter _Position = CF_GetDefaultTC();

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

	void OnView_Player(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Player", "" + sender, args.ToStr());

		_Player.SetClass(_PlayerPreviewWidget.GetDummyPlayer());
		_Player.ToVariable(m_Model, Player);
	}

	void OnModel_Player(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Player", "" + sender, args.ToStr());

		_Player.FromVariable(m_Model, Player);
		_PlayerPreviewWidget.SetPlayer(DayZPlayer.Cast(_Player.GetClass()));
	}

	void OnView_HandItem(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_HandItem", "" + sender, args.ToStr());

	}

	void OnModel_HandItem(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_HandItem", "" + sender, args.ToStr());

		_HandItem.FromVariable(m_Model, HandItem);
		_PlayerPreviewWidget.UpdateItemInHands(EntityAI.Cast(_HandItem.GetClass()));
	}

	void OnView_Orientation(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Orientation", "" + sender, args.ToStr());
		
		_Orientation.SetVector(_PlayerPreviewWidget.GetModelOrientation());
		_Orientation.ToVariable(m_Model, Orientation);
	}

	void OnModel_Orientation(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Orientation", "" + sender, args.ToStr());
		
		_Orientation.FromVariable(m_Model, Orientation);
		_PlayerPreviewWidget.SetModelOrientation(_Orientation.GetVector());
	}

	void OnView_Position(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Position", "" + sender, args.ToStr());
		
		_Position.SetVector(_PlayerPreviewWidget.GetModelPosition());
		_Position.ToVariable(m_Model, Position);
	}

	void OnModel_Position(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Position", "" + sender, args.ToStr());
		
		_Position.FromVariable(m_Model, Position);
		_PlayerPreviewWidget.SetModelPosition(_Position.GetVector());
	}
};
