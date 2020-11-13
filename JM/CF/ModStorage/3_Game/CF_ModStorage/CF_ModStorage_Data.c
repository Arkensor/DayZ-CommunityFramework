enum ModStorageDataType
{
	UNKNOWN = 0,
	BOOL,
	INT,
	FLOAT,
	VECTOR,
	STRING
};

class ModStorageData
{
	static ref ModStorageData ReadCreate( ParamsReadContext ctx )
	{
		ref ModStorageData data = null;

		int type;
		ctx.Read( type );

		switch ( type )
		{
		case ModStorageDataType.BOOL:
			data = new ModStorageDataBool();
			break;
		case ModStorageDataType.INT:
			data = new ModStorageDataInt();
			break;
		case ModStorageDataType.FLOAT:
			data = new ModStorageDataFloat();
			break;
		case ModStorageDataType.VECTOR:
			data = new ModStorageDataVector();
			break;
		case ModStorageDataType.STRING:
			data = new ModStorageDataString();
			break;
		}

		if ( data )
			data.Read( ctx );

		return data;
	}

	void Write( ParamsWriteContext ctx )
	{
	}

	void Read( ParamsReadContext ctx )
	{
	}

	ModStorageDataType GetType()
	{
		return ModStorageDataType.UNKNOWN;
	}

	bool GetBool();
	int GetInt();
	float GetFloat();
	vector GetVector();
	string GetString();
};

class ModStorageDataBool: ModStorageData
{
	private bool m_Value;

	void ModStorageDataBool( bool value = false )
	{
		m_Value = value;
	}

	override void Write( ParamsWriteContext ctx )
	{
		ctx.Write( m_Value );
	}

	override void Read( ParamsReadContext ctx )
	{
		ctx.Read( m_Value );
	}

	override ModStorageDataType GetType()
	{
		return ModStorageDataType.BOOL;
	}

	override bool GetBool()
	{
		return m_Value;
	}
};

class ModStorageDataInt: ModStorageData
{
	private int m_Value;

	void ModStorageDataInt( int value = 0 )
	{
		m_Value = value;
	}

	override void Write( ParamsWriteContext ctx )
	{
		ctx.Write( m_Value );
	}

	override void Read( ParamsReadContext ctx )
	{
		ctx.Read( m_Value );
	}

	override ModStorageDataType GetType()
	{
		return ModStorageDataType.INT;
	}

	override int GetInt()
	{
		return m_Value;
	}
};

class ModStorageDataFloat: ModStorageData
{
	private float m_Value;

	void ModStorageDataFloat( float value = 0 )
	{
		m_Value = value;
	}

	override void Write( ParamsWriteContext ctx )
	{
		ctx.Write( m_Value );
	}

	override void Read( ParamsReadContext ctx )
	{
		ctx.Read( m_Value );
	}

	override ModStorageDataType GetType()
	{
		return ModStorageDataType.FLOAT;
	}

	override float GetFloat()
	{
		return m_Value;
	}
};

class ModStorageDataVector: ModStorageData
{
	private vector m_Value;

	void ModStorageDataVector( vector value = "0 0 0" )
	{
		m_Value = value;
	}

	override void Write( ParamsWriteContext ctx )
	{
		ctx.Write( m_Value );
	}

	override void Read( ParamsReadContext ctx )
	{
		ctx.Read( m_Value );
	}

	override ModStorageDataType GetType()
	{
		return ModStorageDataType.VECTOR;
	}

	override vector GetVector()
	{
		return m_Value;
	}
};

class ModStorageDataString: ModStorageData
{
	private string m_Value;

	void ModStorageDataString( string value = "" )
	{
		m_Value = value;
	}

	override void Write( ParamsWriteContext ctx )
	{
		ctx.Write( m_Value );
	}

	override void Read( ParamsReadContext ctx )
	{
		ctx.Read( m_Value );
	}

	override ModStorageDataType GetType()
	{
		return ModStorageDataType.STRING;
	}

	override string GetString()
	{
		return m_Value;
	}
};