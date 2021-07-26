typedef CF_Expression Expression;
class CF_Expression
{
	string value;

	private int _position = -1;
	
	private ref CF_ExpressionInstruction _compiled[1024];
	private int _compileCount;

	private string BackChar()
	{
		_position--;
		
		if ( _position < 0 )
			_position = 0;
		
		string c = value.Substring( _position, 1 );
		
		return c;
	}

	private string GetChar()
	{
		_position++;
		
		if ( _position >= value.Length() )
			_position = value.Length();
		
		string c = value.Substring( _position, 1 );
		
		return c;
	}

	private bool EOF()
	{
		return _position >= value.Length() - 1;
	}

	private bool IsWhitespace( string c )
	{
		if ( c == " " )
			return true;
		if ( c == "\t" )
			return true;
		if ( c == "\n" )
			return true;
		if ( c == "\r" )
			return true;

		//if ( c == "" )
		//	Error( "Unexpected end of string" );

		return false;
	}

	private bool IsAlphanumeric( string c )
	{
		int i = c.Hash();
			
		if ( i >= 48 && i <= 57 )
			return true;
		
		if ( i == 46 )
			return true;
		
		if ( i == 42 )
			return true;
		
		if ( i == 43 )
			return true;

		if ( i == 44 )
			return true;
		
		if ( i == 45 )
			return true;
		
		if ( i == 47 )
			return true;

		if ( i > 90 )
			i -= 32;

		if ( i >= 65 && i <= 90 )
			return true;

		return false;
	}

	private bool IsLetterOrDigit( string c )
	{
		int i = c.Hash();
			
		if ( i >= 48 && i <= 57 )
			return true;
		
		if ( i == 46 )
			return true;

		if ( i > 90 )
			i -= 32;

		if ( i >= 65 && i <= 90 )
			return true;

		return false;
	}

	private string SkipWhitespace()
	{
		if ( EOF() )
			return "\0";
		
		string c = GetChar();
		while ( IsWhitespace( c ) && !EOF() )
			c = GetChar();

		return c;
	}

	private string GetToken()
	{
		string word = "";
		
		string c = SkipWhitespace();
		
		if ( c == "[" || c == "]" || c == "(" || c == ")" )
			return c;
		
		if ( IsAlphanumeric( c ) && !IsLetterOrDigit( c ) )
			return c;
		
		while ( IsLetterOrDigit( c ) )
		{
			word = word + c;
			if ( EOF() )
				return word;
			
			c = GetChar();
			
			if ( c == "[" || c == "]" || c == "(" || c == ")" || word == "/" || word == "*" )
				break;
		}

		_position--;

		return word;
	}

	private bool IsNumber( string word )
	{
		bool decimal = false;

		for ( int i = 0; i < word.Length(); i++ )
		{
			int c = word[i].Hash();
			if ( c == 46 )
			{
				if ( decimal )
					return false;
				
				decimal = true;
			} else if ( !( c >= 48 && c <= 57 ) )
			{
				return false;
			}
		}

		return true;
	}

	float CompileEvaluate( map< string, float > variables )
	{
		if ( Compile( variables.GetKeyArray() ) )
			return Evaluate( variables.GetValueArray() );
		
		return 0;
	}

	float CompileEvaluateTest( map< string, float > variables, bool test )
	{
		if ( CompileTest( variables.GetKeyArray(), test ) )
			return EvaluateTest( variables.GetValueArray(), test );
		
		return 0;
	}
	
	bool Compile( array< string > variables )
	{
		_Compile( variables );
		
		return true;
	}
	
	bool CompileTest( array< string > variables, bool test )
	{
		int start = TickCount( 0 );
		
		bool success = Compile( variables );
		
		int time = TickCount( start );
		if ( test )
			Print( "CF_Expression::Compile took " + time + " ticks to execute." ); 
		
		return success;
	}

	float Evaluate( array< float > variables )
	{
		//! Make sure the evaluation position is set at the start
		_position = -1;
		
		return _Evaluate( variables );
	}

	float EvaluateTest( array< float > variables, bool test )
	{
		int start = TickCount( 0 );

		_position = -1;
		float num = _Evaluate( variables );
		
		int time = TickCount( start );
		if ( test )
			Print( "CF_Expression::Evaluate took " + time + " ticks to execute." ); 
		
		return num;
	}

	private float _Evaluate( array< float > variables )
	{
		g_CF_Expression_stackPointer = 0;
		g_CF_Expression_variables = variables;
		
		for ( int i = 0; i < _compileCount; i++ )
		{
			g_CF_Expression_instruction = _compiled[i];
			g_CF_ExpressionVM_Lookup[g_CF_Expression_instruction.func_idx].Call();
		}
		
		return g_CF_Expression_stack[g_CF_Expression_stackPointer];
	}
	
	private void AddInstruction(CF_ExpressionInstruction instruction)
	{
		_compiled[_compileCount] = instruction;
		_compileCount++;
	}
	
	private int _Compile( array< string > variables )
	{
		array< ref CF_ExpressionCompileToken > dataStackStore();
		__Stack< CF_ExpressionCompileToken > stack();
		
		_compileCount = 0;
		
		while ( !EOF() )
		{
			string token = GetToken();
			
			token = token.Trim();
			
			if ( token == "]" || token == "," )
				break;
						
			CF_ExpressionFunction op1;
			CF_ExpressionFunction op2;
			
			if ( CF_ExpressionVM.Find( token, op1 ) )
			{
				while ( stack.Count() > 0 )
				{
					string tok = stack.Peek().token;
					if ( !CF_ExpressionVM.Find( tok, op2 ) )
						break;
						
					int c = op1.precedence - op2.precedence;
										
					if ( c < 0 || ( !op1.associative && c <= 0 ) )
						AddInstruction( stack.Pop().ToOperation( CF_ExpressionVM.GetIndex( tok ) ) );
					else
						break;
				}
				
				CF_ExpressionCompileToken ct = stack.Push( new CF_ExpressionCompileToken( token ) );
				dataStackStore.Insert( ct );
				
				int startPosition = _position;
								
				token = SkipWhitespace();
				if ( token == "[" )
				{
					token = SkipWhitespace();
					_position--;
					while ( token != "]" )
					{
						CF_Expression parameter = new CF_Expression();
						
						parameter.value = value + "";
						parameter._position = _position + 0;

						//! there should be no variables/functions inside a parameter for a function call
						int nPos = parameter._Compile( variables );
						float nVal = parameter._Evaluate( new array<float>() );
						
						ct.parameters.Insert( nVal );

						_position = nPos - 1;
						token = SkipWhitespace();
					}
					
					//! factor function optimization
					if ( ct.token == "factor" )
					{
						if ( ct.parameters[1] < ct.parameters[0] )
						{
							float temp = ct.parameters[1];
							ct.parameters[1] = ct.parameters[0];
							ct.parameters[0] = temp;
						}
					}
				} else
				{
					_position = startPosition;
				}
			} else if ( token == "(" )
			{
				dataStackStore.Insert( stack.Push( new CF_ExpressionCompileToken( token ) ) );
			} else if ( token == ")" )
			{
				string topToken = "";
                while ( stack.Count() > 0 )
				{
					CF_ExpressionCompileToken top = stack.Pop();
					topToken = top.token;
					if ( top.token == "(" )
						break;
					
                    AddInstruction( top.ToOperation( CF_ExpressionVM.GetIndex( topToken ) ) );
                }
				
				if ( topToken != "(" )
					Error( "No matching left parenthesis" );
			} else
			{
				if ( IsNumber( token ) )
				{
					AddInstruction( new CF_ExpressionInstruction( token, null, 0, -1 ) );
				} else
				{
					AddInstruction( new CF_ExpressionInstruction( token, null, 1, variables.Find( token ) ) );
				}
			}
		}
		
		while ( stack.Count() > 0 )
		{
			CF_ExpressionCompileToken o = stack.Pop();
            if ( !CF_ExpressionVM.Contains( o.token ) )
				Error( "No matching right parenthesis" );
			
            AddInstruction( o.ToOperation( CF_ExpressionVM.GetIndex( o.token ) ) );
        }
		
		while ( dataStackStore.Count() > 0 )
		{
			delete dataStackStore[0];
			dataStackStore.Remove( 0 );
		}

		return _position;
	}
	
	string ToRPN()
	{
		return _ToRPN();
	}
	
	string ToRPN( bool test )
	{
		int start = TickCount( 0 );

		string rpn = _ToRPN();
		
		int time = TickCount( start );
		Print( "CF_Expression::ToRPN took " + time + " ticks to execute." ); 
		
		return rpn;
	}
	
	/**
	 *  @brief	Converts the compiled expression into Reverse Polish Notation 
	 *
	 * 	@return string
	 */
	private string _ToRPN()
	{
		string rpn = string.Empty;
		
		if (_compileCount == 0 )
			return "0"; //! edge case because I managed to accidentally optimize this out

		for ( int i = 0; i < _compileCount; i++ )
		{
			if ( i > 0 )
				rpn = rpn + " ";

			rpn = rpn + _compiled[i].token;
			
			if ( _compiled[i].func_idx >= 2 )
			{
	           	CF_ExpressionFunction function = CF_ExpressionVM.Get(_compiled[i].func_idx);
				
				//! instruction doesn't store parameters in an array for memory reasons
				if ( function.params != 0 )
				{
					rpn = rpn + " [";
					
					if ( function.params >= 4 )
					{
						rpn = rpn + _compiled[i].param1;
						rpn = rpn + ", ";
						rpn = rpn + _compiled[i].param2;
						rpn = rpn + ", ";
						rpn = rpn + _compiled[i].param3;
						rpn = rpn + ", ";
						rpn = rpn + _compiled[i].param4;
					} else if ( function.params >= 3 )
					{
						rpn = rpn + _compiled[i].param1;
						rpn = rpn + ", ";
						rpn = rpn + _compiled[i].param2;
						rpn = rpn + ", ";
						rpn = rpn + _compiled[i].param3;
					} else if ( function.params >= 2 )
					{
						rpn = rpn + _compiled[i].param1;
						rpn = rpn + ", ";
						rpn = rpn + _compiled[i].param2;
					} else if ( function.params >= 1 )
					{
						rpn = rpn + _compiled[i].param1;
					}
					
					rpn = rpn + "]";
				}
			}
		}

		return rpn;
	}
};