/*
 * Private class
 */
class CF_ExpressionCompileToken
{
	string token;
	ref array< float > parameters;
	
	void CF_ExpressionCompileToken( string _token )
	{
		token = _token;
		parameters = new array< float >();
	}

	CF_ExpressionInstruction ToOperation( int func_idx = -1 )
	{
		return new CF_ExpressionInstruction( token, parameters, func_idx, -1 );
	}
};
