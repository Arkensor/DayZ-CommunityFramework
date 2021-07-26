class ExpressionVM
{
	private	static ref map<string, ref ExpressionFunction> s_Functions;
	private	static int s_Count;

	static ref ExpressionFunction Lookup[256];

	[CF_EventSubscriber(ExpressionVM.Init, CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		s_Functions = new map<string, ref ExpressionFunction>();
		s_Count = 0;

		AddFunction("#INTERNAL_1", new ExpressionFunctionValue());
		AddFunction("#INTERNAL_2", new ExpressionFunctionVariable());
		
		AddFunction("^", new ExpressionFunctionPow());
		AddFunction("*", new ExpressionFunctionMul());
		AddFunction("/", new ExpressionFunctionDiv());
		AddFunction("+", new ExpressionFunctionAdd());
		AddFunction("-", new ExpressionFunctionSub());
		AddFunction("factor", new ExpressionFunctionFactor());
		AddFunction("cos", new ExpressionFunctionCos());
		AddFunction("sin", new ExpressionFunctionSin());
		AddFunction("min", new ExpressionFunctionMin());
		AddFunction("max", new ExpressionFunctionMax());
	}

	[CF_EventSubscriber(ExpressionVM.Destroy, CF_LifecycleEvents.OnGameDestroy)]
	static void Destroy()
	{
		s_Functions = null;
	}

	static void AddFunction(string name, ExpressionFunction function)
	{
		s_Functions[name] = function;
		function.index = s_Count;
		Lookup[function.index] = function;
		s_Count++;
	}

	static Expression Create(string expression, typename type)
	{
		Expression expr = Expression.Cast(type.Spawn());
		expr.value = expression;
		return expr;
	}

	static int GetIndex(string name)
	{
		return s_Functions[name].index;
	}

	static ExpressionFunction Get(int index)
	{
		return Lookup[index];
	}

	static bool Find(string name, inout ExpressionFunction function)
	{
		return s_Functions.Find(name, function);
	}

	static bool Contains(string name)
	{
		return s_Functions.Contains(name);
	}
};