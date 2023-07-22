class CF_PlayerPreviewWidget : CF_Widget
{
	reference string Player;
	reference string HandItem;
	reference string ModelOrientation;
	reference string ModelPosition;

	protected PlayerPreviewWidget _PlayerPreviewWidget;
	protected CF_MVVM_PropertyBase _Player = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _HandItem = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _ModelOrientation = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _ModelPosition = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_0(this, "GetProperties");
#endif

		super.GetProperties();

		AddProperty(Player, "Player");
		AddProperty(HandItem, "HandItem");
		AddProperty(ModelOrientation, "ModelOrientation");
		AddProperty(ModelPosition, "ModelPosition");
	}

	override void OnWidgetScriptInit(Widget w)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_PlayerPreviewWidget, w);
	}

	void OnView_Player(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_Player").Add(sender).Add(args);
#endif

		_Player.SetClass(_PlayerPreviewWidget.GetDummyPlayer());
	}

	void OnModel_Player(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_Player").Add(sender).Add(args);
#endif

		_PlayerPreviewWidget.SetPlayer(DayZPlayer.Cast(_Player.GetClass()));
	}

	void OnView_HandItem(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_HandItem").Add(sender).Add(args);
#endif
	}

	void OnModel_HandItem(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_HandItem").Add(sender).Add(args);
#endif

		_PlayerPreviewWidget.UpdateItemInHands(EntityAI.Cast(_HandItem.GetClass()));
	}

	void OnView_ModelOrientation(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_ModelOrientation").Add(sender).Add(args);
#endif

		_ModelOrientation.SetVector(_PlayerPreviewWidget.GetModelOrientation());
	}

	void OnModel_ModelOrientation(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_ModelOrientation").Add(sender).Add(args);
#endif

		_PlayerPreviewWidget.SetModelOrientation(_ModelOrientation.GetVector());
	}

	void OnView_ModelPosition(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_ModelPosition").Add(sender).Add(args);
#endif

		_ModelPosition.SetVector(_PlayerPreviewWidget.GetModelPosition());
	}

	void OnModel_ModelPosition(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_ModelPosition").Add(sender).Add(args);
#endif

		_PlayerPreviewWidget.SetModelPosition(_ModelPosition.GetVector());
	}
};
