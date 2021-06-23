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
		CF_Model_Base model = m_Collection.GetRaw(Index);
		string layout;
		g_Script.CallFunction(model, "GetLayout", layout, null);
		CF.MVVM.Create(model, layout, m_Widget);
	}
};