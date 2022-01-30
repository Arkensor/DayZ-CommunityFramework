class CF_SQFExpression : CF_Expression
{
	protected override int _Compile(array<string> variables)
	{
		array<ref CF_ExpressionCompileToken> dataStackStore();
		__Stack<CF_ExpressionCompileToken> stack();

		ClearInstructions();

		CF_ExpressionFunctionDef funcDef;
		CF_ExpressionCompileToken compileToken;

		while (!EOF())
		{
			string token = GetToken();

			token = token.Trim();

			if (token == "]" || token == ",")
				break;

			CF_ExpressionFunctionDef op1;
			CF_ExpressionFunctionDef op2;

			if (CF_ExpressionVM.Find(token, op1))
			{
				while (stack.Count() > 0)
				{
					string tok = stack.Peek().token;
					if (!CF_ExpressionVM.Find(tok, op2))
						break;

					int c = op1.precedence - op2.precedence;

					if (c < 0 || (!op1.associative && c <= 0))
						AddInstruction(stack.Pop().ToOperation(op2));
					else
						break;
				}

				compileToken = stack.Push(new CF_ExpressionCompileToken(token));
				dataStackStore.Insert(compileToken);

				int startPosition = m_Position;

				token = SkipWhitespace();
				if (token == "[")
				{
					token = SkipWhitespace();
					m_Position--;
					while (token != "]")
					{
						CF_Expression parameter = new CF_SQFExpression();

						parameter.m_Source = m_Source + "";
						parameter.m_Position = m_Position + 0;

						//! there should be no variables/functions inside a parameter for a function call
						int nPos = parameter._Compile(variables);
						float nVal = parameter._Evaluate(new array<float>());

						compileToken.parameters.Insert(nVal);

						m_Position = nPos - 1;
						token = SkipWhitespace();
					}

					//! factor function optimization
					if (compileToken.token == CF_ExpressionFunctionFactor.CF_NAME)
					{
						if (compileToken.parameters[1] < compileToken.parameters[0])
						{
							compileToken.token = CF_ExpressionFunctionReverseFactor.CF_NAME;
						}
					}
				}
				else
				{
					m_Position = startPosition;
				}
			}
			else if (token == "(")
			{
				dataStackStore.Insert(stack.Push(new CF_ExpressionCompileToken(token)));
			}
			else if (token == ")")
			{
				string topToken = "";
				while (stack.Count() > 0)
				{
					compileToken = stack.Pop();
					topToken = compileToken.token;
					if (compileToken.token == "(")
						break;

					if (CF_ExpressionVM.Find(topToken, funcDef))
						AddInstruction(compileToken.ToOperation(funcDef));
				}

				if (topToken != "(")
					CF_Log.Error("No matching left parenthesis");
			}
			else
			{
				if (IsNumber(token))
				{
					compileToken = new CF_ExpressionCompileToken(token);
					if (CF_ExpressionVM.Find(CF_ExpressionFunctionValue.CF_NAME, funcDef))
					{
						AddInstruction(compileToken.ToOperation(funcDef, -2));
					}
				}
				else
				{
					compileToken = new CF_ExpressionCompileToken(token);
					if (CF_ExpressionVM.Find(CF_ExpressionFunctionVariable.CF_NAME, funcDef))
					{
						AddInstruction(compileToken.ToOperation(funcDef, variables.Find(token)));
					}
				}
			}
		}

		while (stack.Count() > 0)
		{
			compileToken = stack.Pop();
			if (!CF_ExpressionVM.Contains(compileToken.token))
				CF_Log.Error("No matching right parenthesis");

			if (CF_ExpressionVM.Find(compileToken.token, funcDef))
			{
				AddInstruction(compileToken.ToOperation(funcDef));
			}
		}

		while (dataStackStore.Count() > 0)
		{
			dataStackStore.Remove(0);
		}

		return m_Position;
	}
};

/**
 * Backwards compatibility
 */
class Expression : CF_SQFExpression
{
	// DEPRECATED
	string value;

	void Expression(string val = "")
	{
		SetSource(val);
	}
};
