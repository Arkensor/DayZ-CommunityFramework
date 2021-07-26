//! Significant performance improvement as global variables.
CF_ExpressionInstruction g_CF_Expression_instruction;
float g_CF_Expression_stack[16];
int g_CF_Expression_stackPointer;
array<float> g_CF_Expression_variables;

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
		associative = false;
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
		g_CF_Expression_stack[++g_CF_Expression_stackPointer] = g_CF_Expression_instruction.token_f;
	}
};

class CF_ExpressionFunctionVariable : CF_ExpressionFunction
{
	void CF_ExpressionFunctionVariable()
	{
	}

	override void Call()
	{
		g_CF_Expression_stack[++g_CF_Expression_stackPointer] = g_CF_Expression_variables[g_CF_Expression_instruction.var_idx];
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
		float numA = g_CF_Expression_stack[g_CF_Expression_stackPointer--];
		float numB = g_CF_Expression_stack[g_CF_Expression_stackPointer];
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = Math.Pow(numA, numB);
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
		float numA = g_CF_Expression_stack[g_CF_Expression_stackPointer--];
		float numB = g_CF_Expression_stack[g_CF_Expression_stackPointer];
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = numA * numB;
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
		float numA = g_CF_Expression_stack[g_CF_Expression_stackPointer--];
		float numB = g_CF_Expression_stack[g_CF_Expression_stackPointer];
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = numB / numA;
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
		float numA = g_CF_Expression_stack[g_CF_Expression_stackPointer--];
		float numB = g_CF_Expression_stack[g_CF_Expression_stackPointer];
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = numA + numB;
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
		float numA = g_CF_Expression_stack[g_CF_Expression_stackPointer--];
		float numB = g_CF_Expression_stack[g_CF_Expression_stackPointer];
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = numB - numA;
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
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = Math.Interpolate(g_CF_Expression_stack[g_CF_Expression_stackPointer], g_CF_Expression_instruction.param1, g_CF_Expression_instruction.param2, 0.0, 1.0);
	}
};

class CF_ExpressionFunctionCos : CF_ExpressionFunction
{
	override void Call()
	{
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = Math.Cos(g_CF_Expression_stack[g_CF_Expression_stackPointer]);
	}
};

class CF_ExpressionFunctionSin : CF_ExpressionFunction
{
	override void Call()
	{
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = Math.Sin(g_CF_Expression_stack[g_CF_Expression_stackPointer]);
	}
};

class CF_ExpressionFunctionMin : CF_ExpressionFunction
{
	override void Call()
	{
		float numA = g_CF_Expression_stack[g_CF_Expression_stackPointer--];
		float numB = g_CF_Expression_stack[g_CF_Expression_stackPointer];
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = Math.Min(numA, numB);
	}
};

class CF_ExpressionFunctionMax : CF_ExpressionFunction
{
	override void Call()
	{
		float numA = g_CF_Expression_stack[g_CF_Expression_stackPointer--];
		float numB = g_CF_Expression_stack[g_CF_Expression_stackPointer];
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = Math.Max(numA, numB);
	}
};