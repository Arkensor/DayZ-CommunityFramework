/*
 * Private class
 */
class ExpressionCompileToken
{
	string token;
	ref array< float > parameters;
	
	void ExpressionCompileToken( string _token )
	{
		token = _token;
		parameters = new array< float >();
	}

	ExpressionInstruction ToOperation( int func_idx = -1 )
	{
		return new ExpressionInstruction( token, parameters, func_idx, -1 );
	}
};