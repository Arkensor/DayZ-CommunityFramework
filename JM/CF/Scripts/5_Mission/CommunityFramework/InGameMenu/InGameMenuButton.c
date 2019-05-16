class InGameMenuButton
{
	protected string m_Text;
	protected string m_Function;
	protected int m_DisableWhen; // 0 - Never, 1 - Dead, 2 - Alive

	void InGameMenuButton( string text, string function, int disable = 0 )
	{
		m_Function = function;
		m_Text = text;
		m_DisableWhen = disable;
	}

	string GetText()
	{
		return m_Text;
	}

	string GetFunction()
	{
		return m_Function;
	}

	int DisableWhen()
	{
		return m_DisableWhen;
	}

}