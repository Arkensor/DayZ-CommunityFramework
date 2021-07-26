
class CF_Expression
{
	protected string m_Source;
	protected int m_Position = -1;
	
	protected ref CF_ExpressionInstruction m_Instructions[1024];
	protected int m_InstructionCount;

	void SetSource(string source)
	{
		m_Source = source;
	}

	string GetSource()
	{
		return m_Source;
	}

	protected string BackChar()
	{
		m_Position--;
		
		if ( m_Position < 0 )
			m_Position = 0;
		
		string c = m_Source.Substring( m_Position, 1 );
		
		return c;
	}

	protected string GetChar()
	{
		m_Position++;
		
		if ( m_Position >= m_Source.Length() )
			m_Position = m_Source.Length();
		
		string c = m_Source.Substring( m_Position, 1 );
		
		return c;
	}

	protected bool EOF()
	{
		return m_Position >= m_Source.Length() - 1;
	}

	protected bool IsWhitespace( string c )
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

	protected bool IsAlphanumeric( string c )
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

	protected bool IsLetterOrDigit( string c )
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

	protected string SkipWhitespace()
	{
		if ( EOF() )
			return "\0";
		
		string c = GetChar();
		while ( IsWhitespace( c ) && !EOF() )
			c = GetChar();

		return c;
	}

	protected string GetToken()
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

		m_Position--;

		return word;
	}

	protected bool IsNumber( string word )
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
		m_Position = -1;
		
		return _Evaluate( variables );
	}

	float Evaluate()
	{
		//! Make sure the evaluation position is set at the start
		m_Position = -1;
		
		return _Evaluate(new array<float>());
	}

	float EvaluateTest( array< float > variables, bool test )
	{
		int start = TickCount( 0 );

		m_Position = -1;
		float num = _Evaluate( variables );
		
		int time = TickCount( start );
		if ( test )
			Print( "CF_Expression::Evaluate took " + time + " ticks to execute." ); 
		
		return num;
	}

	protected float _Evaluate( array< float > variables )
	{
		g_CF_Expression_stackPointer = 0;
		g_CF_Expression_variables = variables;
		
		for ( int i = 0; i < m_InstructionCount; i++ )
		{
			g_CF_Expression_instruction = m_Instructions[i];
			g_CF_ExpressionVM_Lookup[g_CF_Expression_instruction.func_idx].Call();
		}
		
		return g_CF_Expression_stack[g_CF_Expression_stackPointer];
	}

	protected void ClearInstructions()
	{
		m_InstructionCount = 0;
	}
	
	protected void AddInstruction(CF_ExpressionInstruction instruction)
	{
		m_Instructions[m_InstructionCount] = instruction;
		m_InstructionCount++;
	}
	
	protected int _Compile( array< string > variables )
	{
		return 0;
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
		
		if (m_InstructionCount == 0 )
			return "0"; //! edge case because I managed to accidentally optimize this out

		for ( int i = 0; i < m_InstructionCount; i++ )
		{
			if ( i > 0 )
				rpn = rpn + " ";

			rpn = rpn + m_Instructions[i].token;
			
			if ( m_Instructions[i].func_idx >= 2 )
			{
	           	CF_ExpressionFunction function = CF_ExpressionVM.Get(m_Instructions[i].func_idx);
				
				//! instruction doesn't store parameters in an array for memory reasons
				if ( function.params != 0 )
				{
					rpn = rpn + " [";
					
					if ( function.params >= 4 )
					{
						rpn = rpn + m_Instructions[i].param1;
						rpn = rpn + ", ";
						rpn = rpn + m_Instructions[i].param2;
						rpn = rpn + ", ";
						rpn = rpn + m_Instructions[i].param3;
						rpn = rpn + ", ";
						rpn = rpn + m_Instructions[i].param4;
					} else if ( function.params >= 3 )
					{
						rpn = rpn + m_Instructions[i].param1;
						rpn = rpn + ", ";
						rpn = rpn + m_Instructions[i].param2;
						rpn = rpn + ", ";
						rpn = rpn + m_Instructions[i].param3;
					} else if ( function.params >= 2 )
					{
						rpn = rpn + m_Instructions[i].param1;
						rpn = rpn + ", ";
						rpn = rpn + m_Instructions[i].param2;
					} else if ( function.params >= 1 )
					{
						rpn = rpn + m_Instructions[i].param1;
					}
					
					rpn = rpn + "]";
				}
			}
		}

		return rpn;
	}
};