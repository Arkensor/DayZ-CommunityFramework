/*
 * Private class
 */
class ExpressionInstruction
{
	string token;
	float token_f;
	int token_i;
	int type;
	
	float param1;
	float param2;
	float param3;
	float param4;

	void ExpressionInstruction( string _token, int _type, ref array< float > _parameters, int _token_i )
	{
		token = _token;
		type = _type;
		
		if ( type == 0 )
			token_f = token.ToFloat();
		
		token_i = _token_i;
		
		//! Setting the variables
		//! This looks bad but the code runs a couple of CPU ticks faster with it like this
		//! For code that is expected to run 1000 times a frame this is important
		if ( _parameters )
		{
			if ( _parameters.Count() >= 4 )
			{
				param1 = _parameters[0];
				param2 = _parameters[1];
				param3 = _parameters[2];
				param4 = _parameters[3];
			} else if ( _parameters.Count() >= 3 )
			{
				param1 = _parameters[0];
				param2 = _parameters[1];
				param3 = _parameters[2];
			} else if ( _parameters.Count() >= 2 )
			{
				param1 = _parameters[0];
				param2 = _parameters[1];
			} else if ( _parameters.Count() >= 1 )
			{
				param1 = _parameters[0];
			}
		}
	}
};