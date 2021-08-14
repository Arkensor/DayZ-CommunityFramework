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

	CF_ExpressionInstruction ToOperation(CF_ExpressionFunctionDef funcDef, int variableIdx = -1)
	{
		CF_ExpressionInstruction instruction;
		if (funcDef)
		{
			instruction = funcDef.SpawnFunction();
		}
		else
		{
			instruction = new CF_ExpressionInstruction();
		}

		instruction.SetFields(token, parameters, variableIdx);

		return instruction;
	}
};
