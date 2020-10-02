
// Essentially the same as ScriptView except GetControllerType is now a Template
class ScriptViewTemplate<Class T>: ScriptViewBase
{
	protected T m_Controller;
	T GetController() {
		return m_Controller;
	}
	
	void ScriptViewTemplate(Widget parent = null)
	{
		EnScript.GetClassVar(this, "m_ControllerInstance", 0, m_Controller);
	}
	
	override void SetController(Controller controller)
	{
		super.SetController(controller);
		EnScript.GetClassVar(this, "m_ControllerInstance", 0, m_Controller);
	}
	
	protected override typename GetControllerType() {
		return T;
	}
}