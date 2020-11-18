/**
 * Do not mod this class.
 */
class ModStorage
{
	static const int VERSION = 1;

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
		if (m_Mod)
			ctx.Write(m_Mod.GetName());
		else
			ctx.Write("");

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
		if (entity == null)
		{
			string tempModName;
			ctx.Read(tempModName);
		}
		
		int currVersion = m_Version;
		ctx.Read( m_Version );

		if ( currVersion != -1 && entity && m_Mod )
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

	bool Read( out bool value )
	{
		ref ModStorageData data = Read();
		if ( !data )
			return false;

		value = data.GetBool();

		return true;
	}

	bool Read( out int value )
	{
		ref ModStorageData data = Read();
		if ( !data )
			return false;

		value = data.GetInt();

		return true;
	}

	bool Read( out float value )
	{
		ref ModStorageData data = Read();
		if ( !data )
			return false;

		value = data.GetFloat();

		return true;
	}

	bool Read( out vector value )
	{
		ref ModStorageData data = Read();
		if ( !data )
			return false;

		value = data.GetVector();

		return true;
	}

	bool Read( out string value )
	{
		ref ModStorageData data = Read();
		if ( !data )
			return false;

		value = data.GetString();

		return true;
	}

	/**
	 * @param value		Class variable for read data to be assigned to
	 *
	 * @note value can't be null and can't be marked out/inout
	 */
	bool Read( ref Class value )
	{
		ref ModStorageData data = Read();
		if ( !data )
			return false;
		
		if ( !value )
			return data.IsNull();

		return data.GetClass( value );
	}

	void Write( bool value )
	{
		m_Data.Insert( new ModStorageDataBool( value ) );
	}

	void Write( int value )
	{
		m_Data.Insert( new ModStorageDataInt( value ) );
	}

	void Write( float value )
	{
		m_Data.Insert( new ModStorageDataFloat( value ) );
	}

	void Write( vector value )
	{
		m_Data.Insert( new ModStorageDataVector( value ) );
	}

	void Write( string value )
	{
		m_Data.Insert( new ModStorageDataString( value ) );
	}

	void Write( Class value )
	{
		typename variableType = value.Type();
		
		//! vanilla doesn't support this due to funky persistence id accessing, maybe we shouldn't either
		if (variableType.IsInherited(Object))
		{
			//m_Data.Insert( new ModStorageDataObject( 0 ) );
			return;
		}
		
		if (variableType.IsInherited(array))
		{
			//m_Data.Insert( new ModStorageDataArray( value ) );
			return;
		}
		
		if (variableType.IsInherited(map))
		{
			//m_Data.Insert( new ModStorageDataMap( value ) );
			return;
		}
		
		//! these types of classes shouldn't be serialized at all, someone is going to try it and have a bad day :)
		if (variableType.IsInherited(IEntity) || variableType.IsInherited(Widget))
		{
			return;
		}
		
		m_Data.Insert( new ModStorageDataClass( value ) );
	}
};