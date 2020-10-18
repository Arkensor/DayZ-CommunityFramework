class ExpressionVM
{
	private ref map< string, ref ExpressionFunction > _functions;
	private ref set< ExpressionFunction > _fastLookup;

	private static ref ExpressionVM _instance = new ExpressionVM();

	static ref ExpressionVM Get()
	{
		return _instance;
	}

	static void Destroy()
	{
		delete _instance;
	}

	private void ExpressionVM()
	{
		_functions = new map< string, ref ExpressionFunction >();
		_quickLookUp = new set< ExpressionFunction >();

		SetFunctions();
	}

	void ~ExpressionVM()
	{
		while ( _functions.Count() > 0 )
		{
			string key = _functions.GetKey( 0 );
			delete _functions[key];
			_functions.Remove( key );
		}
		
		delete _functions;

		delete _fastLookup;
	}

	void AddFunction( string name, ref ExpressionFunction function )
	{
		_functions[name] = function;
		function.index = _quickLookUp.Insert( function );
	}

	/*
	 * /brief Override this to add functions
	 */
	void SetFunctions()
	{
		AddFunction( "^", new ExpressionFunctionPow() );
		AddFunction( "*", new ExpressionFunctionMul() );
		AddFunction( "/", new ExpressionFunctionDiv() );
		AddFunction( "+", new ExpressionFunctionAdd() );
		AddFunction( "-", new ExpressionFunctionSub() );
		AddFunction( "factor", new ExpressionFunctionFactor() );
		AddFunction( "cos", new ExpressionFunctionCos() );
		AddFunction( "sin", new ExpressionFunctionSin() );
		AddFunction( "min", new ExpressionFunctionMin() );
		AddFunction( "max", new ExpressionFunctionMax() );
	}

	int GetIndex( string name )
	{
		return _functions[name].index;
	}

	ref ExpressionFunction Get( int index )
	{
		return _quickLookUp[ index ];
	}

	bool Find( string name, ExpressionFunction function )
	{
		return _functions.Find( name, function );
	}

	bool Contains( string name )
	{
		return _functions.Contains( name );
	}
};