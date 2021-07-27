class CF_MathExpression : CF_Expression
{
	//! I want this to be protected or private but a compile error happens
	int __Compile(array<string> variables)
	{
		array<ref CF_ExpressionCompileToken> dataStackStore();
		__Stack<CF_ExpressionCompileToken> stack();

		while (!EOF())
		{
			string token = GetToken();

			token = token.Trim();

			if (token == ",")
				break;

			CF_ExpressionFunction op1;
			CF_ExpressionFunction op2;

			if (CF_ExpressionVM.Find(token, op1))
			{
				CF_ExpressionCompileToken ct = new CF_ExpressionCompileToken(token);
				dataStackStore.Insert(ct);

				int startPosition = m_Position;

				token = SkipWhitespace();
				if (token == "(")
				{
					token = SkipWhitespace();
					int paramidx = 0;
					int nPos;

					m_Position--;
					while (token != ")")
					{
						//! First param can be a variabled expression, i.e. behaves as if this was brackets
						if (paramidx == 0)
						{
							nPos = __Compile(variables);
							m_Position = nPos - 1;
							token = SkipWhitespace();
						}
						else
						{
							CF_Expression parameter = new CF_MathExpression();

							parameter.m_Source = m_Source + "";
							parameter.m_Position = m_Position + 0;

							//! there should be no variables/functions inside a parameter for a function call
							nPos = parameter._Compile(variables);
							float nVal = parameter._Evaluate(new array<float>());

							ct.parameters.Insert(nVal);

							m_Position = nPos - 1;
							token = SkipWhitespace();
						}
						paramidx++;
					}
				}
				else
				{
					m_Position = startPosition;
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

				while (stack.Count() > 0)
				{
					string tok = stack.Peek().token;
					if (!CF_ExpressionVM.Find(tok, op2))
						break;

					int c = op1.precedence - op2.precedence;

					if (op1.precedence != 1 && (c < 0 || (!op1.associative && c <= 0)))
						AddInstruction(stack.Pop().ToOperation(CF_ExpressionVM.GetIndex(tok)));
					else
						break;
				}

				stack.Push(ct);
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
					CF_ExpressionCompileToken top = stack.Pop();
					topToken = top.token;
					if (top.token == "(")
						break;

					AddInstruction(top.ToOperation(CF_ExpressionVM.GetIndex(topToken)));
				}

				if (topToken != "(")
					break;
			}
			else
			{
				if (IsNumber(token))
				{
					AddInstruction(new CF_ExpressionInstruction(token, null, 0, -1));
				}
				else
				{
					AddInstruction(new CF_ExpressionInstruction(token, null, 1, variables.Find(token)));
				}
			}
		}

		while (stack.Count() > 0)
		{
			CF_ExpressionCompileToken o = stack.Pop();
			if (!CF_ExpressionVM.Contains(o.token))
				Error("No matching right parenthesis");

			AddInstruction(o.ToOperation(CF_ExpressionVM.GetIndex(o.token)));
		}

		while (dataStackStore.Count() > 0)
		{
			dataStackStore.Remove(0);
		}

		return m_Position;
	}

	protected override int _Compile(array<string> variables)
	{
		ClearInstructions();

		return __Compile(variables);
	}
};
