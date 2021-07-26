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

	ExpressionInstruction ToOperation( int type, int token_i = -1 )
	{
		return new ExpressionInstruction( token, type, parameters, token_i );
	}
};