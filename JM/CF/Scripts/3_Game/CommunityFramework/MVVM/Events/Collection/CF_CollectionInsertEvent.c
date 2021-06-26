class CF_CollectionInsertEvent : CF_CollectionEvent
{
	int Index;

	void CF_CollectionInsertEvent(int index)
	{
		Index = index;
	}

	override string String()
	{
		string str = super.String();
		str += " Index=" + Index;
		return str;
	}

	override void Process()
	{
		CF_Trace trace(this, "Process");

		CF_ModelBase model = m_Collection.GetConverter(Index).GetManaged();
		
		string layout;
		g_Script.CallFunction(model, "GetLayout", layout, null);
		CF.MVVM.Create(model, layout, m_Widget);
	}
};