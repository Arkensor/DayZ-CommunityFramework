class CF_ExpressionFunction : CF_ExpressionInstruction
{
};

class CF_ExpressionFunctionDef
{
	int params = 0;
	int precedence = 1;
	bool associative = true;
	typename type = CF_ExpressionFunction;

	void CF_ExpressionFunctionDef(typename _type, int _params = 0, int _precedence = 1, bool _associative = true)
	{
		params = _params;
		precedence = _precedence;
		associative = _associative;
		type = _type;
	}

	CF_ExpressionFunction SpawnFunction()
	{
		return CF_ExpressionFunction.Cast(type.Spawn());
	}
};

class CF_ExpressionFunctionValue : CF_ExpressionFunction
{
	static string CF_NAME = "#INTERNAL_0";

	[CF_EventSubscriber(ScriptCaller.Create(CF_ExpressionFunctionValue.Init), CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction(CF_NAME, new CF_ExpressionFunctionDef(CF_ExpressionFunctionValue, -1));
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[++CF_ExpressionVM.StackPointer] = value;
	}

	override string GetDebugName()
	{
		return "" + value;
	}
};

class CF_ExpressionFunctionVariable : CF_ExpressionFunction
{
	static string CF_NAME = "#INTERNAL_1";

	[CF_EventSubscriber(ScriptCaller.Create(CF_ExpressionFunctionVariable.Init), CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction(CF_NAME, new CF_ExpressionFunctionDef(CF_ExpressionFunctionVariable, -1));
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[++CF_ExpressionVM.StackPointer] = CF_ExpressionVM.Variables[variableIndex];
	}

	override string GetDebugName()
	{
		return token;
	}
};

class CF_ExpressionFunctionPow : CF_ExpressionFunction
{
	static string CF_NAME = "^";

	[CF_EventSubscriber(ScriptCaller.Create(CF_ExpressionFunctionPow.Init), CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction(CF_NAME, new CF_ExpressionFunctionDef(CF_ExpressionFunctionPow, 0, 4, false));
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = Math.Pow(CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer--], CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer]);
	}

	override string GetDebugName()
	{
		return CF_NAME;
	}
};

class CF_ExpressionFunctionMul : CF_ExpressionFunction
{
	static string CF_NAME = "*";

	[CF_EventSubscriber(ScriptCaller.Create(CF_ExpressionFunctionMul.Init), CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction(CF_NAME, new CF_ExpressionFunctionDef(CF_ExpressionFunctionMul, 0, 3, true));
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer--] * CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer];
	}

	override string GetDebugName()
	{
		return CF_NAME;
	}
};

class CF_ExpressionFunctionDiv : CF_ExpressionFunction
{
	static string CF_NAME = "/";
	
	[CF_EventSubscriber(ScriptCaller.Create(CF_ExpressionFunctionDiv.Init), CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction(CF_NAME, new CF_ExpressionFunctionDef(CF_ExpressionFunctionDiv, 0, 3, true));
	}

	override void Call()
	{
		CF_ExpressionVM.StackPointer--;
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] / CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer + 1];
	}

	override string GetDebugName()
	{
		return CF_NAME;
	}
};

class CF_ExpressionFunctionAdd : CF_ExpressionFunction
{
	static string CF_NAME = "+";
	
	[CF_EventSubscriber(ScriptCaller.Create(CF_ExpressionFunctionAdd.Init), CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction(CF_NAME, new CF_ExpressionFunctionDef(CF_ExpressionFunctionAdd, 0, 2, true));
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer--] + CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer];
	}

	override string GetDebugName()
	{
		return CF_NAME;
	}
};

class CF_ExpressionFunctionSub : CF_ExpressionFunction
{
	static string CF_NAME = "-";
	
	[CF_EventSubscriber(ScriptCaller.Create(CF_ExpressionFunctionSub.Init), CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction(CF_NAME, new CF_ExpressionFunctionDef(CF_ExpressionFunctionSub, 0, 2, true));
	}

	override void Call()
	{
		CF_ExpressionVM.StackPointer--;
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] - CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer + 1];
	}

	override string GetDebugName()
	{
		return CF_NAME;
	}
};

class CF_ExpressionFunctionFactor : CF_ExpressionFunction
{
	static string CF_NAME = "factor";
	
	[CF_EventSubscriber(ScriptCaller.Create(CF_ExpressionFunctionFactor.Init), CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction(CF_NAME, new CF_ExpressionFunctionDef(CF_ExpressionFunctionFactor, 2));
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = (Math.Clamp(CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer], param1, param2) - param1) / (param2 - param1);
	}

	override string GetDebugName()
	{
		return CF_NAME;
	}
};

class CF_ExpressionFunctionReverseFactor : CF_ExpressionFunction
{
	static string CF_NAME = "#factor_reverse";
	
	[CF_EventSubscriber(ScriptCaller.Create(CF_ExpressionFunctionReverseFactor.Init), CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction(CF_NAME, new CF_ExpressionFunctionDef(CF_ExpressionFunctionReverseFactor, 2));
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = 1.0 - (Math.Clamp(CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer], param2, param1) - param2) / (param1 - param2);
	}

	override string GetDebugName()
	{
		return CF_NAME;
	}
};

class CF_ExpressionFunctionCos : CF_ExpressionFunction
{
	static string CF_NAME = "cos";
	
	[CF_EventSubscriber(ScriptCaller.Create(CF_ExpressionFunctionCos.Init), CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction(CF_NAME, new CF_ExpressionFunctionDef(CF_ExpressionFunctionCos));
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = Math.Cos(CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer]);
	}

	override string GetDebugName()
	{
		return CF_NAME;
	}
};

class CF_ExpressionFunctionSin : CF_ExpressionFunction
{
	static string CF_NAME = "sin";
	
	[CF_EventSubscriber(ScriptCaller.Create(CF_ExpressionFunctionSin.Init), CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction(CF_NAME, new CF_ExpressionFunctionDef(CF_ExpressionFunctionSin));
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = Math.Sin(CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer]);
	}

	override string GetDebugName()
	{
		return CF_NAME;
	}
};

class CF_ExpressionFunctionMin : CF_ExpressionFunction
{
	static string CF_NAME = "min";
	
	[CF_EventSubscriber(ScriptCaller.Create(CF_ExpressionFunctionMin.Init), CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction(CF_NAME, new CF_ExpressionFunctionDef(CF_ExpressionFunctionMin));
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = Math.Min(CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer--], CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer]);
	}

	override string GetDebugName()
	{
		return CF_NAME;
	}
};

class CF_ExpressionFunctionMax : CF_ExpressionFunction
{
	static string CF_NAME = "max";
	
	[CF_EventSubscriber(ScriptCaller.Create(CF_ExpressionFunctionMax.Init), CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction(CF_NAME, new CF_ExpressionFunctionDef(CF_ExpressionFunctionMax));
	}

	override void Call()
	{
		CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer] = Math.Max(CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer--], CF_ExpressionVM.Stack[CF_ExpressionVM.StackPointer]);
	}

	override string GetDebugName()
	{
		return CF_NAME;
	}
};
