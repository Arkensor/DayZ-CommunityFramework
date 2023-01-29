class CF_Location : Class
{
	CF_Lexer m_Lexer;

	int m_Position;

	int m_Row;
	int m_Column;

	CF_Location Copy()
	{
		CF_Location location = new CF_Location();

		location.m_Lexer = m_Lexer;
		location.m_Position = m_Position;

		location.m_Row = m_Row;
		location.m_Column = m_Column;

		return location;
	}
	
	override string GetDebugName()
	{
		string str = super.GetDebugName();
		
		str += " Position=" + m_Position + "";
		str += " " + m_Row + ":" + m_Column + "";
		
		return str;
	}
};
