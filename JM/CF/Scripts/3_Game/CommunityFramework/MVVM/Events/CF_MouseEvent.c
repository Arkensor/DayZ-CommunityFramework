class CF_MouseEvent : CF_PositionEvent
{
	/**
	 * @brief OnClick, OnDoubleClick, OnMouseButtonDown, OnMouseButtonUp
	 */
	int Button;

	/**
	 * @brief OnMouseLeave
	 */
	Widget Enter;

	/**
	 * @brief OnMouseWheel
	 */
	int Wheel;

	override string String()
	{
		string str = super.String();
		str += " Button=" + Button;
		str += " Enter=" + Enter;
		str += " Wheel=" + Wheel;
		return str;
	}
};
