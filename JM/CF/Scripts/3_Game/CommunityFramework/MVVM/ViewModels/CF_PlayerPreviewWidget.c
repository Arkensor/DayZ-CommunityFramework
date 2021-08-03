class CF_PlayerPreviewWidget : CF_Widget
{
	reference string Player;
	reference string HandItem;
	reference string Orientation;
	reference string Position;

	protected PlayerPreviewWidget _PlayerPreviewWidget;
	protected ref CF_TypeConverter _Player = CF_GetDefaultTC();
	protected ref CF_TypeConverter _HandItem = CF_GetDefaultTC();
	protected ref CF_TypeConverter _Orientation = CF_GetDefaultTC();
	protected ref CF_TypeConverter _Position = CF_GetDefaultTC();

	override void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "GetProperties");
		#endif

		super.GetProperties();
		
		AddProperty(Player, "Player");
		AddProperty(HandItem, "HandItem");
		AddProperty(Orientation, "Orientation");
		AddProperty(Position, "Position");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_PlayerPreviewWidget, w);
	}

	void OnView_Player(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Player", "" + sender, args.ToStr());
		#endif

		_Player.SetClass(_PlayerPreviewWidget.GetDummyPlayer());
		_Player.ToVariable(m_Model, Player);
	}

	void OnModel_Player(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Player", "" + sender, args.ToStr());
		#endif

		_Player.FromVariable(m_Model, Player);
		_PlayerPreviewWidget.SetPlayer(DayZPlayer.Cast(_Player.GetClass()));
	}

	void OnView_HandItem(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_HandItem", "" + sender, args.ToStr());
		#endif

	}

	void OnModel_HandItem(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_HandItem", "" + sender, args.ToStr());
		#endif

		_HandItem.FromVariable(m_Model, HandItem);
		_PlayerPreviewWidget.UpdateItemInHands(EntityAI.Cast(_HandItem.GetClass()));
	}

	void OnView_Orientation(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Orientation", "" + sender, args.ToStr());
		#endif
		
		_Orientation.SetVector(_PlayerPreviewWidget.GetModelOrientation());
		_Orientation.ToVariable(m_Model, Orientation);
	}

	void OnModel_Orientation(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Orientation", "" + sender, args.ToStr());
		#endif
		
		_Orientation.FromVariable(m_Model, Orientation);
		_PlayerPreviewWidget.SetModelOrientation(_Orientation.GetVector());
	}

	void OnView_Position(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Position", "" + sender, args.ToStr());
		#endif
		
		_Position.SetVector(_PlayerPreviewWidget.GetModelPosition());
		_Position.ToVariable(m_Model, Position);
	}

	void OnModel_Position(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Position", "" + sender, args.ToStr());
		#endif
		
		_Position.FromVariable(m_Model, Position);
		_PlayerPreviewWidget.SetModelPosition(_Position.GetVector());
	}
};
