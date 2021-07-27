class CF_ExpressionStackDebug
{
	float Get(int index)
	{
		Print("[" + index + "]: " + CF_ExpressionVM_Stack[index] + "");
		return CF_ExpressionVM_Stack[index];
	}
	
	void Set(int index, float value)
	{
		Print("[" + index + "]: " + CF_ExpressionVM_Stack[index] + " -> " + value + "");
		CF_ExpressionVM_Stack[index] = value;
	}
};