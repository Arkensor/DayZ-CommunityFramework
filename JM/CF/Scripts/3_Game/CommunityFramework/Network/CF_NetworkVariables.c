class CF_NetworkVariable
{
	ref CF_NetworkVariable m_Next;

	string m_Name;
	int m_Count; // max 4
	int m_AccessorIndices[4];
	typename m_AccessorTypes[4];
	CF_TypeConverter m_Converter;
};

class CF_NetworkVariables
{
	static int MAX_COUNT = 256;

	int m_Count;

	ref CF_NetworkVariable m_Head;
	CF_NetworkVariable m_Tail;

	Class m_Instance;

	void CF_NetworkVariables(Class instance)
	{
		m_Instance = instance;
	}

	string ErrorPrefix()
	{
		return "ERROR: (" + m_Instance + ") " + this + "::";
	}

	bool Register(string name)
	{
		// hard limit, no point attempting to sync more variables
		if (m_Count >= MAX_COUNT)
		{
			Error(ErrorPrefix() + "Register('" + name + "') -> More than " + MAX_COUNT + " variables registered, got '" + m_Count + "'");
			return false;
		}

		CF_NetworkVariable variable = new CF_NetworkVariable();

		typename type = m_Instance.Type();
		array<string> tokens();
		name.Split(".", tokens);

		variable.m_Name = name;

		if (tokens.Count() != 0)
		{
			// Maximum of 3 tokens (max - 1)
			if (tokens.Count() >= 3)
			{
				Error(ErrorPrefix() + "RegisterNetSyncVariable('" + name + "') -> Variable depth more than 3, got '" + tokens.Count() + "'");
				return false;
			}

			variable.m_Name = tokens[tokens.Count() - 1];

			int i, j;

			// iterate over all tokens to get the sub class for the variable
			for (i = 0; i < tokens.Count() - 1; i++)
			{
				bool success = false;
				for (j = 0; j < type.GetVariableCount(); j++)
				{
					if (type.GetVariableName(j) == tokens[i])
					{
						type = type.GetVariableType(j);

						variable.m_AccessorIndices[variable.m_Count] = j;
						variable.m_AccessorTypes[variable.m_Count] = type;
						variable.m_Count++;

						success = true;

						break;
					}
				}

				// couldn't find sub variable
				if (!success)
				{
					Error(ErrorPrefix() + "RegisterNetSyncVariable('" + name + "') -> Couldn't find sub variable '" + tokens[i] + "'");
					return false;
				}
			}
		}

		for (j = 0; j < type.GetVariableCount(); j++)
		{
			if (type.GetVariableName(j) == variable.m_Name)
			{
				type = type.GetVariableType(j);

				variable.m_AccessorIndices[variable.m_Count] = j;
				variable.m_AccessorTypes[variable.m_Count] = type;
				variable.m_Count++;

				variable.m_Converter = CF_TypeConverters.Create(type);

				if (!variable.m_Converter)
				{
					Error(ErrorPrefix() + "RegisterNetSyncVariable('" + name + "') -> TypeConverter not found for type '" + type + "'");
					return false;
				}

				if (!m_Tail)
				{
					m_Head = variable;
					m_Tail = variable;
				}
				else
				{
					m_Tail.m_Next = variable;
					m_Tail = variable;
				}

				m_Count++;

				return true;
			}
		}

		Error(ErrorPrefix() + "RegisterNetSyncVariable('" + name + "') -> Couldn't find variable '" + variable.m_Name + "'");
		return false;
	}

	void Write(ParamsWriteContext ctx)
	{
		CF_BinaryWriter writer = new CF_BinaryWriter(new CF_SerializerWriteStream(ctx));

		CF_NetworkVariable variable = m_Head;
		while (variable)
		{
			Class instance = m_Instance;

			int index = variable.m_Count - 1;
			
			for (int j = 0; j < index; j++)
			{
				if (!instance) break;
				
				variable.m_AccessorTypes[j].GetVariableValue(instance, variable.m_AccessorIndices[j], instance);
			}

			if (instance)
			{
				variable.m_Converter.FromTypename(instance, variable.m_AccessorIndices[index]);
			}

			variable.m_Converter.ToIO(writer);

			variable = variable.m_Next;
		}

		writer.Close();
	}

	void Read(ParamsReadContext ctx)
	{
		CF_BinaryReader reader = new CF_BinaryReader(new CF_SerializerReadStream(ctx));

		CF_NetworkVariable variable = m_Head;
		while (variable)
		{
			Class instance = m_Instance;
			
			for (int j = 0; j < variable.m_Count - 1; j++)
			{
				if (!instance) break;

				variable.m_AccessorTypes[j].GetVariableValue(instance, variable.m_AccessorIndices[j], instance);
			}

			variable.m_Converter.FromIO(reader);

			if (instance)
			{
				variable.m_Converter.ToVariable(instance, variable.m_Name);
			}

			variable = variable.m_Next;
		}

		reader.Close();
	}
};
