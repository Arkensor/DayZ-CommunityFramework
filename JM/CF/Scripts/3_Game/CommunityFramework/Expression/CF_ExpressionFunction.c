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
	[CF_EventSubscriber(CF_ExpressionFunctionValue.Init, CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM._MoveFunctionTo(CF_ExpressionVM.AddFunction("#INTERNAL_0", new CF_ExpressionFunctionValue()), 0);
	}

	void CF_ExpressionFunctionVariable()
	{
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[++CF_ExpressionVM.StackPointer] = CF_ExpressionVM.Instruction.token_f;
	}
};

class CF_ExpressionFunctionVariable : CF_ExpressionFunction
{
	[CF_EventSubscriber(CF_ExpressionFunctionVariable.Init, CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM._MoveFunctionTo(CF_ExpressionVM.AddFunction("#INTERNAL_1", new CF_ExpressionFunctionVariable()), 1);
	}

	void CF_ExpressionFunctionVariable()
	{
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[++CF_ExpressionVM.StackPointer] = CF_ExpressionVM.Variables[CF_ExpressionVM.Instruction.var_idx];
	}
};

class CF_ExpressionFunctionPow : CF_ExpressionFunction
{
	[CF_EventSubscriber(CF_ExpressionFunctionPow.Init, CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction("^", new CF_ExpressionFunctionPow());
	}

	void CF_ExpressionFunctionPow()
	{
		precedence = 4;
		associative = false;
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = Math.Pow(CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer--], CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer]);
	}
};

class CF_ExpressionFunctionMul : CF_ExpressionFunction
{
	[CF_EventSubscriber(CF_ExpressionFunctionMul.Init, CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction("*", new CF_ExpressionFunctionMul());
	}

	void CF_ExpressionFunctionMul()
	{
		precedence = 3;
		associative = true;
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer--] * CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer];
	}
};

class CF_ExpressionFunctionDiv : CF_ExpressionFunction
{
	[CF_EventSubscriber(CF_ExpressionFunctionDiv.Init, CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction("/", new CF_ExpressionFunctionDiv());
	}

	void CF_ExpressionFunctionDiv()
	{
		precedence = 3;
		associative = true;
	}

	override void Call()
	{
		CF_ExpressionVM.StackPointer--;
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] / CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer + 1];
	}
};

class CF_ExpressionFunctionAdd : CF_ExpressionFunction
{
	[CF_EventSubscriber(CF_ExpressionFunctionAdd.Init, CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction("+", new CF_ExpressionFunctionAdd());
	}

	void CF_ExpressionFunctionAdd()
	{
		precedence = 2;
		associative = true;
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer--] + CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer];
	}
};

class CF_ExpressionFunctionSub : CF_ExpressionFunction
{
	[CF_EventSubscriber(CF_ExpressionFunctionSub.Init, CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction("-", new CF_ExpressionFunctionSub());
	}

	void CF_ExpressionFunctionSub()
	{
		precedence = 2;
		associative = true;
	}

	override void Call()
	{
		CF_ExpressionVM.StackPointer--;
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] - CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer + 1];
	}
};

class CF_ExpressionFunctionFactor : CF_ExpressionFunction
{
	[CF_EventSubscriber(CF_ExpressionFunctionFactor.Init, CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction("factor", new CF_ExpressionFunctionFactor());
	}

	void CF_ExpressionFunctionFactor()
	{
		params = 2;
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = Math.Interpolate(CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer], CF_ExpressionVM.Instruction.param1, CF_ExpressionVM.Instruction.param2, 0.0, 1.0);
	}
};

class CF_ExpressionFunctionCos : CF_ExpressionFunction
{
	[CF_EventSubscriber(CF_ExpressionFunctionCos.Init, CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction("cos", new CF_ExpressionFunctionCos());
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = Math.Cos(CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer]);
	}
};

class CF_ExpressionFunctionSin : CF_ExpressionFunction
{
	[CF_EventSubscriber(CF_ExpressionFunctionSin.Init, CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction("sin", new CF_ExpressionFunctionSin());
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = Math.Sin(CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer]);
	}
};

class CF_ExpressionFunctionMin : CF_ExpressionFunction
{
	[CF_EventSubscriber(CF_ExpressionFunctionMin.Init, CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction("min", new CF_ExpressionFunctionMin());
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = Math.Min(CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer--], CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer]);
	}
};

class CF_ExpressionFunctionMax : CF_ExpressionFunction
{
	[CF_EventSubscriber(CF_ExpressionFunctionMax.Init, CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction("max", new CF_ExpressionFunctionMax());
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = Math.Max(CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer--], CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer]);
	}
};
