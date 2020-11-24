/**
 * Do not mod this class.
 */
class CF_ModStorage
{
	static const int VERSION = 1;

	private int m_Version;

	private ModStructure m_Mod;

	private ref array< ref CF_ModStorage_Data > m_Data = new ref array< ref CF_ModStorage_Data >();
	private int m_Index;

	void CF_ModStorage( ref ModStructure mod )
	{
		m_Mod = mod;

		m_Data = new array< ref CF_ModStorage_Data >();

		m_Version = -1;

		if ( m_Mod )
			m_Version = m_Mod.GetStorageVersion();
	}

	void ~CF_ModStorage()
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
			ctx.Write( m_Data[i].GetType() );
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
			m_Data.Insert( CF_ModStorage_Converter.Read( ctx ) );
		}

		return true;
	}

	private ref CF_ModStorage_Data Read()
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
		ref CF_ModStorage_Data data = Read();
		if ( !data )
			return false;

		value = Param1<bool>.Cast(data.Get()).param1;

		return true;
	}

	bool Read( out int value )
	{
		ref CF_ModStorage_Data data = Read();
		if ( !data )
			return false;

		value = Param1<int>.Cast(data.Get()).param1;

		return true;
	}

	bool Read( out float value )
	{
		ref CF_ModStorage_Data data = Read();
		if ( !data )
			return false;

		value = Param1<float>.Cast(data.Get()).param1;

		return true;
	}

	bool Read( out vector value )
	{
		ref CF_ModStorage_Data data = Read();
		if ( !data )
			return false;

		value = Param1<vector>.Cast(data.Get()).param1;

		return true;
	}

	bool Read( out string value )
	{
		ref CF_ModStorage_Data data = Read();
		if ( !data )
			return false;

		value = Param1<string>.Cast(data.Get()).param1;

		return true;
	}

	/**
	 * @param value		Class variable for read data to be assigned to
	 *
	 * @note value can't be null and can't be marked out/inout
	 */
	bool Read( ref Class value )
	{
		ref CF_ModStorage_Data data = Read();
		if ( !data )
			return false;
		
		if ( !value )
			return data.IsNull();

		return data.Get( value );
	}

	void Write( bool value )
	{
		m_Data.Insert( new CF_ModStorage_Data_Primitive<bool>( value ) );
	}

	void Write( int value )
	{
		m_Data.Insert( new CF_ModStorage_Data_Primitive<int>( value ) );
	}

	void Write( float value )
	{
		m_Data.Insert( new CF_ModStorage_Data_Primitive<float>( value ) );
	}

	void Write( vector value )
	{
		m_Data.Insert( new CF_ModStorage_Data_Primitive<vector>( value ) );
	}

	void Write( string value )
	{
		m_Data.Insert( new CF_ModStorage_Data_Primitive<string>( value ) );
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
		
		//m_Data.Insert( new ModStorageDataClass( value ) );
	}
};