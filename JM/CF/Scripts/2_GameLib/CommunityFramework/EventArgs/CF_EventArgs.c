class CF_EventArgs
{
    static const CF_EventArgs Empty = NULL;
    
	string GetDebugName()
	{
		return "[" + ClassName() + "]";
	}
};
