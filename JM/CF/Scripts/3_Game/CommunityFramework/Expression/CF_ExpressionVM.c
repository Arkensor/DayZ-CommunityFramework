//! Significant performance improvement as global variables.
static ref CF_ExpressionFunction CF_ExpressionVM_Lookup[256];
static CF_ExpressionInstruction CF_ExpressionVM_Instruction;
static float CF_ExpressionVM_Stack[16];
static ref CF_ExpressionStackDebug CF_ExpressionVM_StackDebugger = new CF_ExpressionStackDebug();
static int CF_ExpressionVM_StackPointer;
static array<float> CF_ExpressionVM_Variables;
	
class CF_ExpressionVM
{
	private	static ref map<string, ref CF_ExpressionFunction> s_Functions;
	private	static int s_Count;

	[CF_EventSubscriber(CF_ExpressionVM.Destroy, CF_LifecycleEvents.OnGameDestroy)]
	static void Destroy()
	{
		s_Functions = null;
	}

	static void _MoveFunctionTo(CF_ExpressionFunction function, int index)
	{
		//! Check if the index is not the right function
		if (CF_ExpressionVM_Lookup[index] != function)
		{
			//! Perform swap
			CF_ExpressionVM_Lookup[function.index] = CF_ExpressionVM_Lookup[index];
			CF_ExpressionVM_Lookup[function.index].index = function.index;
			CF_ExpressionVM_Lookup[index] = function;
			CF_ExpressionVM_Lookup[index].index = index;
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
		CF_ExpressionVM_Lookup[function.index] = function;

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
		return CF_ExpressionVM_Lookup[index];
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