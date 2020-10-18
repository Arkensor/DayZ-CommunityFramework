class JMPermission : Managed
{
	JMPermission Parent;

	ref array< ref JMPermission > Children;

	string Name;

	private string m_SerializedFullName;

	JMPermissionType Type;

	Widget View;

	int Depth;

	void JMPermission( string name, ref JMPermission parent = NULL )
	{
		Name = name;
		Parent = parent;

		Type = JMPermissionType.INHERIT;

		if ( Parent == NULL )
		{
			Type = JMPermissionType.DISALLOW;
		}

		Children = new array< ref JMPermission >;

		UpdateFullName();
	}

	void ~JMPermission()
	{
		Clear();

		delete Children;
	}

	void UpdateFullName()
	{
		m_SerializedFullName = Name;

		JMPermission parent = Parent;
		while ( parent != NULL )
		{
			if ( parent.Parent == NULL ) 
			{
				return;
			}
			
			m_SerializedFullName = parent.Name + "." +  m_SerializedFullName;
			parent = parent.Parent;
		}
	}

	string GetFullName()
	{
		return m_SerializedFullName;
	}

	void AddPermission( string inp, JMPermissionType permType = JMPermissionType.INHERIT )
	{
		array<string> tokens = new array<string>;

		array<string> spaces = new array<string>;
		inp.Split( " ", spaces );

		JMPermissionType type;

		if ( permType == JMPermissionType.INHERIT && spaces.Count() == 2 )
		{
			if ( spaces[1].Contains( "2" ) )
			{
				type = JMPermissionType.ALLOW;
			} else if ( spaces[1].Contains( "1" ) )
			{
				type = JMPermissionType.DISALLOW;
			} else 
			{
				type = JMPermissionType.INHERIT;
			}

			spaces[0].Split( ".", tokens );
		} else if ( spaces.Count() < 2 )
		{
			type = permType;

			inp.Split( ".", tokens );
		} else {
			Error( "Warning, permission line improperly formatted! Read as \"" + inp + "\" but meant to be in format \"Perm.Perm {n}\"." );
			return;
		}
		
		int depth = tokens.Find( Name );

		if ( depth > -1 )
		{
			AddPermissionInternal( tokens, depth + 1, type );
		} else 
		{
			AddPermissionInternal( tokens, 0, type );
		}
	}

	private void AddPermissionInternal( array<string> tokens, int depth, JMPermissionType value )
	{
		if ( depth < tokens.Count() )
		{
			string name = tokens[depth];

			ref JMPermission nChild = VerifyAddPermission( name );

			nChild.AddPermissionInternal( tokens, depth + 1, value );
		} else {
			Type = value;
		}
	}

	private ref JMPermission VerifyAddPermission( string name )
	{
		ref JMPermission nChild = NULL;

		for ( int i = 0; i < Children.Count(); i++ )
		{
			if ( name == Children[i].Name )
			{
				nChild = Children[i];
				break;
			}
		}
			
		if ( nChild == NULL )
		{
			nChild = new JMPermission( name, this );
			nChild.Type = JMPermissionType.INHERIT;

			Children.Insert( nChild );
		}

		return nChild;
	}

	ref JMPermission GetPermission( string inp )
	{
		array<string> tokens = new array<string>;
		inp.Split( ".", tokens );
		
		int depth = tokens.Find(Name);

		if ( depth > -1 )
		{
			return Get( tokens, depth + 1 );
		} else 
		{
			return Get( tokens, 0 );
		}
	}

	private ref JMPermission Get( array<string> tokens, int depth )
	{
		if ( depth < tokens.Count() )
		{
			ref JMPermission nChild = NULL;

			for ( int i = 0; i < Children.Count(); i++ )
			{
				if ( Children[i].Name == tokens[depth] )
				{
					nChild = Children[i]; 
				}
			}

			if ( nChild )
			{
				return nChild.Get( tokens, depth + 1 );
			}
		}

		return this;
	}

	bool HasPermission( string inp, out JMPermissionType permType )
	{
		array<string> tokens = new array<string>;
		inp.Split( ".", tokens );

		if ( tokens.Count() == 0 )
			return false;
		
		int depth = tokens.Find( Name );

		bool parentDisallowed = false;

		if ( Type == JMPermissionType.DISALLOW )
		{
			parentDisallowed = true;
		} else if ( Type == JMPermissionType.INHERIT )
		{
			JMPermission parent = Parent;
			while ( parent != NULL )
			{
				if ( parent.Type != JMPermissionType.INHERIT )
				{
					if ( parent.Type == JMPermissionType.DISALLOW )
					{
						parentDisallowed = true;
					}

					break;
				}
				
				parent = parent.Parent;
			}
		}
		
		if ( depth > -1 )
		{
			return Check( tokens, depth + 1, parentDisallowed, permType );
		} else 
		{
			return Check( tokens, 0, parentDisallowed, permType );
		}
	}

	bool Check( array<string> tokens, int depth, bool parentDisallowed, out JMPermissionType permType )
	{
		bool ifReturnAs = false;

		if ( Type == JMPermissionType.ALLOW )
		{
			ifReturnAs = true;
		}

		if ( Type == JMPermissionType.INHERIT && parentDisallowed == false )
		{
			ifReturnAs = true;
		}

		if ( Type == JMPermissionType.DISALLOW )
		{
			parentDisallowed = true;
		}

		if ( Type == JMPermissionType.ALLOW )
		{
			parentDisallowed = false;
		}

		if ( depth < tokens.Count() )
		{
			ref JMPermission nChild = NULL;

			for ( int i = 0; i < Children.Count(); i++ )
			{
				if ( Children[i].Name == tokens[depth] )
				{
					nChild = Children[i]; 
				}
			}

			if ( nChild )
			{
				return nChild.Check( tokens, depth + 1, parentDisallowed, permType );
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

	void Serialize( ref array< string > output, string prepend = "" )
	{
		for ( int i = 0; i < Children.Count(); i++ )
		{
			string serialize = prepend + Children[i].Name;
				
			output.Insert( serialize + " " + Children[i].Type );

			if ( Children[i].Children.Count() > 0 ) 
			{
				Children[i].Serialize( output, serialize + "." );
			}
		}
	}

	void Deserialize( ref array< string > input )
	{
		Clear();

		for ( int i = 0; i < input.Count(); i++ )
			AddPermission( input[i], JMPermissionType.INHERIT );
	}

	void DebugPrint( int depth = 0 )
	{
		string message = this.Name;

		for ( int j = 0; j < depth; j++ )
		{
			message = "  " + message;
		}

		string append = "";

		switch ( Type )
		{
			case JMPermissionType.ALLOW:
			{
				append = " ALLOW";
				break;
			}
			case JMPermissionType.DISALLOW:
			{
				append = " DISALLOW";
				break;
			}
			default:
			case JMPermissionType.INHERIT:
			{
				append = " INHERIT";
				break;
			}
		}

		// Print( message + append );

		for ( int i = 0; i < Children.Count(); i++ )
		{
			Children[i].DebugPrint( depth + 1 );
		}
	}
}