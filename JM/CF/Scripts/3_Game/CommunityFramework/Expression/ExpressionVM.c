static ref CF_ExpressionFunction g_CF_ExpressionVM_Lookup[256];

class CF_ExpressionVM
{
	private	static ref map<string, ref CF_ExpressionFunction> s_Functions;
	private	static int s_Count;

	[CF_EventSubscriber(CF_ExpressionVM.Init, CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		s_Functions = new map<string, ref CF_ExpressionFunction>();
		s_Count = 0;

		AddFunction("#INTERNAL_1", new CF_ExpressionFunctionValue());
		AddFunction("#INTERNAL_2", new CF_ExpressionFunctionVariable());
		
		AddFunction("^", new CF_ExpressionFunctionPow());
		AddFunction("*", new CF_ExpressionFunctionMul());
		AddFunction("/", new CF_ExpressionFunctionDiv());
		AddFunction("+", new CF_ExpressionFunctionAdd());
		AddFunction("-", new CF_ExpressionFunctionSub());
		AddFunction("factor", new CF_ExpressionFunctionFactor());
		AddFunction("cos", new CF_ExpressionFunctionCos());
		AddFunction("sin", new CF_ExpressionFunctionSin());
		AddFunction("min", new CF_ExpressionFunctionMin());
		AddFunction("max", new CF_ExpressionFunctionMax());
	}

	[CF_EventSubscriber(CF_ExpressionVM.Destroy, CF_LifecycleEvents.OnGameDestroy)]
	static void Destroy()
	{
		s_Functions = null;
	}

	static void AddFunction(string name, CF_ExpressionFunction function)
	{
		s_Functions[name] = function;
		function.index = s_Count;
		g_CF_ExpressionVM_Lookup[function.index] = function;
		s_Count++;
	}

	static CF_Expression Create(string expression, typename type)
	{
		CF_Expression expr = CF_Expression.Cast(type.Spawn());
		expr.value = expression;
		return expr;
	}

	static int GetIndex(string name)
	{
		return s_Functions[name].index;
	}

	static CF_ExpressionFunction Get(int index)
	{
		return g_CF_ExpressionVM_Lookup[index];
	}

	static bool Find(string name, inout CF_ExpressionFunction function)
	{
		return s_Functions.Find(name, function);
	}

	static bool Contains(string name)
	{
		return s_Functions.Contains(name);
	}
};