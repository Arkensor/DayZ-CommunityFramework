/**
 * Do not mod this class.
 */
class ModStorage
{
	private int m_Version;

	private ModStructure m_Mod;

	private ref array< ref ModStorageData > m_Data = new ref array< ref ModStorageData >();
	private int m_Index;

	void ModStorage( ref ModStructure mod )
	{
		m_Mod = mod;

		m_Data = new array< ref ModStorageData >();

		if ( m_Mod )
			m_Version = m_Mod.GetStorageVersion();
		m_Version = -1;
	}

	void ~ModStorage()
	{
		for ( int i = 0; i < m_Data.Count(); i++ )
			delete m_Data[i];

		delete m_Data;
	}

	int GetVersion()
	{
		return m_Version;
	}

	ModStructure GetMod()
	{
		return m_Mod;
	}

	void Save( EntityAI entity, ParamsWriteContext ctx )
	{
		ctx.Write( m_Mod.GetName() );

		ctx.Write( m_Version );

		int count = m_Data.Count();
		ctx.Write( count );

		for ( int i = 0; i < count; i++ )
		{
			int type = m_Data[i].GetType();
			ctx.Write( type );
			m_Data[i].Write( ctx );
		}
	}

	/**
	 * @note Mod name is read in the entity OnStoreLoad method
	 */
	bool Load( EntityAI entity, ParamsReadContext ctx, int version )
	{
		int currVersion = m_Version;
		ctx.Read( m_Version );

		if ( currVersion != -1 )
		{
			if ( currVersion != m_Version )
			{
				Print( "Updating " + entity.GetType() + " for mod '" + m_Mod.GetName() + "' from " + m_Version + " to " + currVersion );
			}
		}

		int count;
		ctx.Read( count );

		for ( int i = 0; i < count; i++ )
		{
			m_Data.Insert( ModStorageData.ReadCreate( ctx ) );
		}

		return true;
	}

	private ref ModStorageData Read()
	{
		if ( m_Index >= m_Data.Count() )
			return null;

		return m_Data[m_Index++];
	}

	bool Skip()
	{
		return Read() != null;
	}

	bool ReadBool( out bool value )
	{
		ref ModStorageData data = Read();
		if ( !data )
			return false;

		value = data.GetBool();

		return true;
	}

	bool ReadInt( out int value )
	{
		ref ModStorageData data = Read();
		if ( !data )
			return false;

		value = data.GetInt();

		return true;
	}

	bool ReadFloat( out float value )
	{
		ref ModStorageData data = Read();
		if ( !data )
			return false;

		value = data.GetFloat();

		return true;
	}

	bool ReadVector( out vector value )
	{
		ref ModStorageData data = Read();
		if ( !data )
			return false;

		value = data.GetVector();

		return true;
	}

	bool ReadString( out string value )
	{
		ref ModStorageData data = Read();
		if ( !data )
			return false;

		value = data.GetString();

		return true;
	}

	void WriteBool( bool value )
	{
		m_Data.Insert( new ModStorageDataBool( value ) );
	}

	void WriteInt( int value )
	{
		m_Data.Insert( new ModStorageDataInt( value ) );
	}

	void WriteFloat( float value )
	{
		m_Data.Insert( new ModStorageDataFloat( value ) );
	}

	void WriteVector( vector value )
	{
		m_Data.Insert( new ModStorageDataVector( value ) );
	}

	void WriteString( string value )
	{
		m_Data.Insert( new ModStorageDataString( value ) );
	}
};