class CF_ExpressionFunction
{
	int index;

	int params;

	int precedence;
	bool associative;

	void CF_ExpressionFunction()
	{
		params = 0;

		precedence = 1;
		associative = true;
	}

	void Call();
};

class CF_ExpressionFunctionValue : CF_ExpressionFunction
{
	void CF_ExpressionFunctionVariable()
	{
	}

	override void Call()
	{
		CF_ExpressionVM_Stack[++CF_ExpressionVM_StackPointer] = CF_ExpressionVM_Instruction.token_f;
	}
};

class CF_ExpressionFunctionVariable : CF_ExpressionFunction
{
	void CF_ExpressionFunctionVariable()
	{
	}

	override void Call()
	{
		CF_ExpressionVM_Stack[++CF_ExpressionVM_StackPointer] = CF_ExpressionVM_Variables[CF_ExpressionVM_Instruction.var_idx];
	}
};

class CF_ExpressionFunctionPow : CF_ExpressionFunction
{
	void CF_ExpressionFunctionPow()
	{
		precedence = 4;
		associative = false;
	}

	override void Call()
	{
		float numA = CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer--];
		float numB = CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer];
		CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer] = Math.Pow(numA, numB);
	}
};

class CF_ExpressionFunctionMul : CF_ExpressionFunction
{
	void CF_ExpressionFunctionMul()
	{
		precedence = 3;
		associative = true;
	}

	override void Call()
	{
		float numA = CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer--];
		float numB = CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer];
		CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer] = numA * numB;
	}
};

class CF_ExpressionFunctionDiv : CF_ExpressionFunction
{
	void CF_ExpressionFunctionDiv()
	{
		precedence = 3;
		associative = true;
	}

	override void Call()
	{
		float numA = CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer--];
		float numB = CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer];
		CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer] = numB / numA;
	}
};

class CF_ExpressionFunctionAdd : CF_ExpressionFunction
{
	void CF_ExpressionFunctionAdd()
	{
		precedence = 2;
		associative = true;
	}

	override void Call()
	{
		float numA = CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer--];
		float numB = CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer];
		CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer] = numA + numB;
	}
};

class CF_ExpressionFunctionSub : CF_ExpressionFunction
{
	void CF_ExpressionFunctionSub()
	{
		precedence = 2;
		associative = true;
	}

	override void Call()
	{
		float numA = CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer--];
		float numB = CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer];
		CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer] = numB - numA;
	}
};

class CF_ExpressionFunctionFactor : CF_ExpressionFunction
{
	void CF_ExpressionFunctionFactor()
	{
		params = 2;
	}

	override void Call()
	{
		CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer] = Math.Interpolate(CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer], CF_ExpressionVM_Instruction.param1, CF_ExpressionVM_Instruction.param2, 0.0, 1.0);
	}
};

class CF_ExpressionFunctionCos : CF_ExpressionFunction
{
	override void Call()
	{
		CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer] = Math.Cos(CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer]);
	}
};

class CF_ExpressionFunctionSin : CF_ExpressionFunction
{
	override void Call()
	{
		CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer] = Math.Sin(CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer]);
	}
};

class CF_ExpressionFunctionMin : CF_ExpressionFunction
{
	override void Call()
	{
		float numA = CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer--];
		float numB = CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer];
		CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer] = Math.Min(numA, numB);
	}
};

class CF_ExpressionFunctionMax : CF_ExpressionFunction
{
	override void Call()
	{
		float numA = CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer--];
		float numB = CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer];
		CF_ExpressionVM_Stack[CF_ExpressionVM_StackPointer] = Math.Max(numA, numB);
	}
};