class CF_ExpressionVM
{
	static CF_ExpressionInstruction CurrentInstruction;
	static float Stack[16];
	static ref CF_ExpressionStackDebug StackDebugger = new CF_ExpressionStackDebug();
	static int StackPointer;
	static array<float> Variables;

	private	static autoptr map<string, autoptr CF_ExpressionFunctionDef> s_Functions;

	[CF_EventSubscriber(ScriptCaller.Create(CF_ExpressionVM.Destroy), CF_LifecycleEvents.OnGameDestroy)]
	static void Destroy()
	{
		s_Functions = null;
	}

	static void AddFunction(string name, notnull CF_ExpressionFunctionDef function)
	{
		//! Init map
		if (s_Functions == null)
		{
			s_Functions = new map<string, autoptr CF_ExpressionFunctionDef>();
		}

		//! Add the function
		s_Functions[name] = function;
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

	static bool Find(string name, inout CF_ExpressionFunctionDef function)
	{
		return s_Functions.Find(name, function);
	}

	static bool Contains(string name)
	{
		return s_Functions.Contains(name);
	}
};
