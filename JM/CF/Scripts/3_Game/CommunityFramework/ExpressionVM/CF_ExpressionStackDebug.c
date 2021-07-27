class CF_ExpressionStackDebug
{
	float Get(int index)
	{
		Print("[" + index + "]: " + CF_ExpressionVM.Stack[index] + "");
		return CF_ExpressionVM.Stack[index];
	}
	
	void Set(int index, float value)
	{
		Print("[" + index + "]: " + CF_ExpressionVM.Stack[index] + " -> " + value + "");
		CF_ExpressionVM.Stack[index] = value;
	}
};
