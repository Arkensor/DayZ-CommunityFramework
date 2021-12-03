class CF_EventArgs
{
    static const CF_EventArgs Empty = NULL;
    
	override string GetDebugName()
	{
		return "[" + ClassName() + "]";
	}
};
