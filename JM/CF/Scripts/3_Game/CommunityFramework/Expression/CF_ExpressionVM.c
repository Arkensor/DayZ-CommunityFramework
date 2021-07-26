static ref CF_ExpressionFunction g_CF_ExpressionVM_Lookup[256];

class CF_ExpressionVM
{
	private	static ref map<string, ref CF_ExpressionFunction> s_Functions;
	private	static int s_Count;

	[CF_EventSubscriber(CF_ExpressionVM.Init, CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		MoveFunctionTo(AddFunction("#INTERNAL_0", new CF_ExpressionFunctionValue()), 0);
		MoveFunctionTo(AddFunction("#INTERNAL_1", new CF_ExpressionFunctionVariable()), 1);
		
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

	private static void MoveFunctionTo(CF_ExpressionFunction function, int index)
	{
		//! Check if the index is not the right function
		if (g_CF_ExpressionVM_Lookup[index] != function)
		{
			//! Perform swap
			g_CF_ExpressionVM_Lookup[function.index] = g_CF_ExpressionVM_Lookup[index];
			g_CF_ExpressionVM_Lookup[function.index].index = function.index;
			g_CF_ExpressionVM_Lookup[index] = function;
			g_CF_ExpressionVM_Lookup[index].index = index;
		}
	}

	static CF_ExpressionFunction AddFunction(string name, notnull CF_ExpressionFunction function)
	{
		//! Init map
		if (s_Functions == null)
		{
			s_Functions = new map<string, ref CF_ExpressionFunction>();
			s_Count = 0;
		}

		int index = s_Count;
		s_Count++;

		//! Handling edge case if function was registered twice
		CF_ExpressionFunction old_function;
		if (s_Functions.Find(name, old_function))
		{
			index = old_function.index;
			s_Count--;
		}

		//! Add the function
		s_Functions[name] = function;
		function.index = index;
		g_CF_ExpressionVM_Lookup[function.index] = function;

		return function;
	}

	static CF_Expression Create(string src)
	{
		return Create(src, CF_MathExpression);
	}

	static CF_Expression Create(string src, typename type)
	{
		CF_Expression expr = CF_Expression.Cast(type.Spawn());
		if (expr) expr.SetSource(src);
		return expr;
	}

	static CF_Expression Compile(string src)
	{
		return Compile(src, new array<string>(), CF_MathExpression);
	}

	static CF_Expression Compile(string src, array<string> variables)
	{
		return Compile(src, variables, CF_MathExpression);
	}

	static CF_Expression Compile(string src, typename type)
	{
		return Compile(src, new array<string>(), type);
	}

	static CF_Expression Compile(string src, array<string> variables, typename type)
	{
		CF_Expression expr = Create(src, type);
		expr.Compile(variables);
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