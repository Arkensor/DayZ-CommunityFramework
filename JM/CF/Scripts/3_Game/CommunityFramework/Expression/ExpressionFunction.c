ExpressionInstruction g_CF_Expression_instruction;
float g_CF_Expression_stack[16];
int g_CF_Expression_stackPointer;
array<float> g_CF_Expression_variables;

class ExpressionFunction
{
	int index;

	int params;

	int precedence;
	bool associative;

	void ExpressionFunction()
	{
		params = 0;

		precedence = 1;
		associative = false;
	}

	void Call();
};

class ExpressionFunctionValue : ExpressionFunction
{
	void ExpressionFunctionVariable()
	{
	}

	override void Call()
	{
		g_CF_Expression_stack[++g_CF_Expression_stackPointer] = g_CF_Expression_instruction.token_f;
	}
};

class ExpressionFunctionVariable : ExpressionFunction
{
	void ExpressionFunctionVariable()
	{
	}

	override void Call()
	{
		g_CF_Expression_stack[++g_CF_Expression_stackPointer] = g_CF_Expression_variables[g_CF_Expression_instruction.var_idx];
	}
};

class ExpressionFunctionPow : ExpressionFunction
{
	void ExpressionFunctionPow()
	{
		precedence = 4;
		associative = false;
	}

	override void Call()
	{
		float numA = g_CF_Expression_stack[g_CF_Expression_stackPointer--];
		float numB = g_CF_Expression_stack[g_CF_Expression_stackPointer];
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = Math.Pow(numA, numB);
	}
};

class ExpressionFunctionMul : ExpressionFunction
{
	void ExpressionFunctionMul()
	{
		precedence = 3;
		associative = true;
	}

	override void Call()
	{
		float numA = g_CF_Expression_stack[g_CF_Expression_stackPointer--];
		float numB = g_CF_Expression_stack[g_CF_Expression_stackPointer];
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = numA * numB;
	}
};

class ExpressionFunctionDiv : ExpressionFunction
{
	void ExpressionFunctionDiv()
	{
		precedence = 3;
		associative = true;
	}

	override void Call()
	{
		float numA = g_CF_Expression_stack[g_CF_Expression_stackPointer--];
		float numB = g_CF_Expression_stack[g_CF_Expression_stackPointer];
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = numB / numA;
	}
};

class ExpressionFunctionAdd : ExpressionFunction
{
	void ExpressionFunctionAdd()
	{
		precedence = 2;
		associative = true;
	}

	override void Call()
	{
		float numA = g_CF_Expression_stack[g_CF_Expression_stackPointer--];
		float numB = g_CF_Expression_stack[g_CF_Expression_stackPointer];
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = numA + numB;
	}
};

class ExpressionFunctionSub : ExpressionFunction
{
	void ExpressionFunctionSub()
	{
		precedence = 2;
		associative = true;
	}

	override void Call()
	{
		float numA = g_CF_Expression_stack[g_CF_Expression_stackPointer--];
		float numB = g_CF_Expression_stack[g_CF_Expression_stackPointer];
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = numB - numA;
	}
};

class ExpressionFunctionFactor : ExpressionFunction
{
	void ExpressionFunctionFactor()
	{
		params = 2;
	}

	override void Call()
	{
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = Math.Interpolate(g_CF_Expression_stack[g_CF_Expression_stackPointer], g_CF_Expression_instruction.param1, g_CF_Expression_instruction.param2, 0.0, 1.0);
	}
};

class ExpressionFunctionCos : ExpressionFunction
{
	override void Call()
	{
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = Math.Cos(g_CF_Expression_stack[g_CF_Expression_stackPointer]);
	}
};

class ExpressionFunctionSin : ExpressionFunction
{
	override void Call()
	{
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = Math.Sin(g_CF_Expression_stack[g_CF_Expression_stackPointer]);
	}
};

class ExpressionFunctionMin : ExpressionFunction
{
	override void Call()
	{
		float numA = g_CF_Expression_stack[g_CF_Expression_stackPointer--];
		float numB = g_CF_Expression_stack[g_CF_Expression_stackPointer];
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = Math.Min(numA, numB);
	}
};

class ExpressionFunctionMax : ExpressionFunction
{
	override void Call()
	{
		float numA = g_CF_Expression_stack[g_CF_Expression_stackPointer--];
		float numB = g_CF_Expression_stack[g_CF_Expression_stackPointer];
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = Math.Max(numA, numB);
	}
};