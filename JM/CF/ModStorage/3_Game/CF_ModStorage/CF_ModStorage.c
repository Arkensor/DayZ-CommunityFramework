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
	
	void Clear()
	{
		m_Index = 0;
		m_Data.Clear();
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
			string type = m_Data[i].GetType().ToString();
			ctx.Write(type);
			m_Data[i].Write( ctx );
		}
	}

	/**
	 * @note Mod name is read in the entity OnStoreLoad method
	 */
	bool Load( EntityAI entity, ParamsReadContext ctx, int version )
	{
		Clear();
		
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

	ref CF_ModStorage_Data ReadRaw()
	{
		if ( m_Index >= m_Data.Count() )
			return null;

		return m_Data[m_Index++];
	}

	void WriteRaw( ref CF_ModStorage_Data data )
	{
		data.OnSet();
		m_Data.Insert( data );
	}

	bool Skip()
	{
		return ReadRaw() != null;
	}

	bool Read( out bool value )
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if ( !data )
			return false;

		value = Param1<bool>.Cast(data.Get()).param1;

		return true;
	}

	bool Read( out int value )
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if ( !data )
			return false;

		value = Param1<int>.Cast(data.Get()).param1;

		return true;
	}

	bool Read( out float value )
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if ( !data )
			return false;

		value = Param1<float>.Cast(data.Get()).param1;

		return true;
	}

	bool Read( out vector value )
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if ( !data )
			return false;

		value = Param1<vector>.Cast(data.Get()).param1;

		return true;
	}

	bool Read( out string value )
	{
		ref CF_ModStorage_Data data = ReadRaw();
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
		ref CF_ModStorage_Data data = ReadRaw();
		if ( !data )
			return false;
		
		if ( !value )
			return data.IsNull();

		return data.Get( value );
	}

	bool ReadArray( ref TBoolArray value )
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if ( !data )
			return false;

		Class cls = Class.Cast(value);
		bool ret = data.Get( cls );
		value = cls;
		
		return ret;
	}

	bool ReadArray( ref TIntArray value )
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if ( !data )
			return false;

		Class cls = Class.Cast(value);
		bool ret = data.Get( cls );
		value = cls;
		
		return ret;
	}

	bool ReadArray( ref TFloatArray value )
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if ( !data )
			return false;

		Class cls = Class.Cast(value);
		bool ret = data.Get( cls );
		value = cls;
		
		return ret;
	}

	bool ReadArray( ref TVectorArray value )
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if ( !data )
			return false;

		Class cls = Class.Cast(value);
		bool ret = data.Get( cls );
		value = cls;
		
		return ret;
	}

	bool ReadArray( ref TStringArray value )
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if ( !data )
			return false;
		
		Class cls = Class.Cast(value);
		bool ret = data.Get( cls );
		value = cls;
		
		return ret;
	}
	
	bool ReadArray( ref Class value )
	{
		ref CF_ModStorage_Data data = ReadRaw();
		if ( !data )
			return false;
		
		if ( !value )
			return data.IsNull();

		return data.Get( value );
	}

	void Write( bool value )
	{
		WriteRaw( new CF_ModStorage_Data_Primitive<bool>( value ) );
	}

	void Write( int value )
	{
		WriteRaw( new CF_ModStorage_Data_Primitive<int>( value ) );
	}

	void Write( float value )
	{
		WriteRaw( new CF_ModStorage_Data_Primitive<float>( value ) );
	}

	void Write( vector value )
	{
		WriteRaw( new CF_ModStorage_Data_Primitive<vector>( value ) );
	}

	void Write( string value )
	{
		WriteRaw( new CF_ModStorage_Data_Primitive<string>( value ) );
	}

	void Write( Class value )
	{
		WriteRaw( new CF_ModStorage_Data_Class( value ) );
	}

	void WriteArray( TBoolArray value )
	{
		WriteRaw( new CF_ModStorage_Data_Array<bool>( value ) );
	}

	void WriteArray( TIntArray value )
	{
		WriteRaw( new CF_ModStorage_Data_Array<int>( value ) );
	}

	void WriteArray( TFloatArray value )
	{
		WriteRaw( new CF_ModStorage_Data_Array<float>( value ) );
	}

	void WriteArray( TVectorArray value )
	{
		WriteRaw( new CF_ModStorage_Data_Array<vector>( value ) );
	}

	void WriteArray( TStringArray value )
	{
		WriteRaw( new CF_ModStorage_Data_Array<string>( value ) );
	}

	void WriteArray( Class value )
	{
		WriteRaw( new CF_ModStorage_Data_Array<Class>( value ) );
	}
};