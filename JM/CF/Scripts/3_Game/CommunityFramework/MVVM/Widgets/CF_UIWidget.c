class CF_UIWidget : CF_Widget
{
	reference string TextColor;
	reference string TextOutlineSize;
	reference string TextOutlineColor;
	reference string TextShadowSize;
	reference string TextShadowColor;
	reference string TextShadowOpacity;
	reference string TextShadowOffsetX;
	reference string TextShadowOffsetY;
	reference string TextItalic;
	reference string TextBold;
	
	private UIWidget _UIWidget;
	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_UIWidget, w);
	}
};
