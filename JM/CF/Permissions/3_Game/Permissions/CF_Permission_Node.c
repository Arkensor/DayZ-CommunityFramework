typedef CF_Permission_Node JMPermission;

class CF_Permission_Node : Managed
{
	CF_Permission_Node Parent;

	ref array<ref CF_Permission_Node> Children;

	string Name;

	private	string m_SerializedFullName;

	CF_Permission_Type Type;

	Widget View;

	int Depth;

	void CF_Permission_Node(string name, ref CF_Permission_Node parent = NULL)
	{
		Name = name;
		Parent = parent;

		Type = CF_Permission_Type.INHERIT;

		if (Parent == NULL)
		{
			Type = CF_Permission_Type.DISALLOW;
		}

		Children = new array<ref CF_Permission_Node>;

		UpdateFullName();
	}

	void ~CF_Permission_Node()
	{
		Clear();

		delete Children;
	}

	void UpdateFullName()
	{
		m_SerializedFullName = Name;

		CF_Permission_Node parent = Parent;
		while (parent != NULL)
		{
			if (parent.Parent == NULL)
			{
				return;
			}

			m_SerializedFullName = parent.Name + "." + m_SerializedFullName;
			parent = parent.Parent;
		}
	}

	string GetFullName()
	{
		return m_SerializedFullName;
	}

	void AddPermission(string inp, CF_Permission_Type permType = CF_Permission_Type.INHERIT)
	{
		array<string> tokens = new array<string>;

		array<string> spaces = new array<string>;
		inp.Split(" ", spaces);

		CF_Permission_Type type;

		if (permType == CF_Permission_Type.INHERIT && spaces.Count() == 2)
		{
			if (spaces[1].Contains("2"))
			{
				type = CF_Permission_Type.ALLOW;
			}
			else if (spaces[1].Contains("1"))
			{
				type = CF_Permission_Type.DISALLOW;
			}
			else
			{
				type = CF_Permission_Type.INHERIT;
			}

			spaces[0].Split(".", tokens);
		}
		else if (spaces.Count() < 2)
		{
			type = permType;

			inp.Split(".", tokens);
		}
		else
		{
			Error("Warning, permission line improperly formatted! Read as \"" + inp + "\" but meant to be in format \"Perm.Perm {n}\".");
			return;
		}

		int depth = tokens.Find(Name);

		if (depth > -1)
		{
			AddPermissionInternal(tokens, depth + 1, type);
		}
		else
		{
			AddPermissionInternal(tokens, 0, type);
		}
	}

	private	void AddPermissionInternal(array<string> tokens, int depth, CF_Permission_Type value)
	{
		if (depth < tokens.Count())
		{
			string name = tokens[depth];

			ref CF_Permission_Node nChild = VerifyAddPermission(name);

			nChild.AddPermissionInternal(tokens, depth + 1, value);
		}
		else
		{
			Type = value;
		}
	}

	private	ref CF_Permission_Node VerifyAddPermission(string name)
	{
		ref CF_Permission_Node nChild = NULL;

		for (int i = 0; i < Children.Count(); i++)
		{
			if (name == Children[i].Name)
			{
				nChild = Children[i];
				break;
			}
		}

		if (nChild == NULL)
		{
			nChild = new CF_Permission_Node(name, this);
			nChild.Type = CF_Permission_Type.INHERIT;

			Children.Insert(nChild);
		}

		return nChild;
	}

	ref CF_Permission_Node GetPermission(string inp)
	{
		array<string> tokens = new array<string>;
		inp.Split(".", tokens);

		int depth = tokens.Find(Name);

		if (depth > -1)
		{
			return Get(tokens, depth + 1);
		}
		else
		{
			return Get(tokens, 0);
		}
	}

	private	ref CF_Permission_Node Get(array<string> tokens, int depth)
	{
		if (depth < tokens.Count())
		{
			ref CF_Permission_Node nChild = NULL;

			for (int i = 0; i < Children.Count(); i++)
			{
				if (Children[i].Name == tokens[depth])
				{
					nChild = Children[i];
				}
			}

			if (nChild)
			{
				return nChild.Get(tokens, depth + 1);
			}
		}

		return this;
	}

	bool HasPermission(string inp, out CF_Permission_Type permType)
	{
		array<string> tokens = new array<string>;
		inp.Split(".", tokens);

		if (tokens.Count() == 0)
			return false;

		int depth = tokens.Find(Name);

		bool parentDisallowed = false;

		if (Type == CF_Permission_Type.DISALLOW)
		{
			parentDisallowed = true;
		}
		else if (Type == CF_Permission_Type.INHERIT)
		{
			CF_Permission_Node parent = Parent;
			while (parent != NULL)
			{
				if (parent.Type != CF_Permission_Type.INHERIT)
				{
					if (parent.Type == CF_Permission_Type.DISALLOW)
					{
						parentDisallowed = true;
					}

					break;
				}

				parent = parent.Parent;
			}
		}

		if (depth > -1)
		{
			return Check(tokens, depth + 1, parentDisallowed, permType);
		}
		else
		{
			return Check(tokens, 0, parentDisallowed, permType);
		}
	}

	bool Check(array<string> tokens, int depth, bool parentDisallowed, out CF_Permission_Type permType)
	{
		bool ifReturnAs = false;

		if (Type == CF_Permission_Type.ALLOW)
		{
			ifReturnAs = true;
		}

		if (Type == CF_Permission_Type.INHERIT && parentDisallowed == false)
		{
			ifReturnAs = true;
		}

		if (Type == CF_Permission_Type.DISALLOW)
		{
			parentDisallowed = true;
		}

		if (Type == CF_Permission_Type.ALLOW)
		{
			parentDisallowed = false;
		}

		if (depth < tokens.Count())
		{
			ref CF_Permission_Node nChild = NULL;

			for (int i = 0; i < Children.Count(); i++)
			{
				if (Children[i].Name == tokens[depth])
				{
					nChild = Children[i];
				}
			}

			if (nChild)
			{
				return nChild.Check(tokens, depth + 1, parentDisallowed, permType);
			}
		}

		permType = Type;

		return ifReturnAs;
	}

	void Clear()
	{
		/*
		for ( int i = 0; i < Children.Count(); ++i )
		{
			delete Children[i];
		}
		*/

		Children.Clear();
	}

	void Serialize(ref array<string> output, string prepend = "")
	{
		for (int i = 0; i < Children.Count(); i++)
		{
			string serialize = prepend + Children[i].Name;

			output.Insert(serialize + " " + Children[i].Type);

			if (Children[i].Children.Count() > 0)
			{
				Children[i].Serialize(output, serialize + ".");
			}
		}
	}

	void Deserialize(ref array<string> input)
	{
		Clear();

		for (int i = 0; i < input.Count(); i++)
			AddPermission(input[i], CF_Permission_Type.INHERIT);
	}

	void DebugPrint(int depth = 0)
	{
		string message = this.Name;

		for (int j = 0; j < depth; j++)
		{
			message = "  " + message;
		}

		string append = "";

		switch (Type)
		{
		case CF_Permission_Type.ALLOW:
		{
			append = " ALLOW";
			break;
		}
		case CF_Permission_Type.DISALLOW:
		{
			append = " DISALLOW";
			break;
		}
		default:
		case CF_Permission_Type.INHERIT:
		{
			append = " INHERIT";
			break;
		}
		}

		// Print( message + append );

		for (int i = 0; i < Children.Count(); i++)
		{
			Children[i].DebugPrint(depth + 1);
		}
	}
};