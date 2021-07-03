class CF_Window : CF_Model
{
	private float m_PositionX;
	private float m_PositionY;
 
	private float m_Width;
	private float m_Height;
 
	private ref CF_ModelBase m_Model;

	private int m_ID;

	override string GetLayout()
	{
		return "JM/CF/GUI/layouts/windows/window.layout";
	}
};