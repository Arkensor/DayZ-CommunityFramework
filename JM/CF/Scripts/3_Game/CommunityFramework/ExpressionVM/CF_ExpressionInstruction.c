/*
 * Private class
 */
class CF_ExpressionInstruction
{
	string token;
	float value;

	int variableIndex;

	ref CF_ExpressionInstruction next;
	
	float param1;
	float param2;
	float param3;
	float param4;

	void SetFields(string _token, array< float > _parameters, int _variableIndex)
	{
		token = _token;
		if (_variableIndex == -2) value = _token.ToFloat();
		variableIndex = _variableIndex;
		
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

	void Call();

	override string GetDebugName()
	{
		return ToString();
	}
};
