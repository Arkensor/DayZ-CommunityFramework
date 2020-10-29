modded class ItemBase
{
	override void OnStoreSave( ParamsWriteContext ctx )
	{
		super.OnStoreSave( ctx );
	
		array< ref ModStructure > mods = ModLoader.GetMods();

		int count = mods.Count();

		ctx.Write( count );

		for ( int i = 0; i < count; i++ )
		{
			ModStorage store = new ModStorage( mods[ i ] );

			OnModStoreSave( store, mods[ i ].GetName() );

			store.Save( this, ctx );
		}
	}

	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;

		// If the persistence file is before 1.10, cf data doesn't exist
		if ( version < 116 )
			return true;

		int count;
		if ( !ctx.Read( count ) )
			return false;

		for ( int i = 0; i < count; i++ )
		{
			string modName;
			if ( !ctx.Read( modName ) )
				return false;

			ModStorage store = new ModStorage( ModLoader.Get( modName ) );

			if ( !store.Load( this, ctx, version ) )
			{
				Error( "Failed reading " + GetType() + " for mod '" + modName + "'!" );
				return false;
			}

			if ( store.GetMod() && store.GetVersion() > 0 && !OnModStoreLoad( store, modName ) )
			{
				Error( "Failed loading " + GetType() + " for mod '" + modName + "'!" );
				return false;
			}
		}

		return true;
	}

	/**
	 * @param storage	Where the data is written to, only use public methods 'void Write...(value)`
	 * @param modName	The name of the mod from CfgMods class to check against
	 * 
	 * @code
	modded class KitBase // extends from ItemBase
	{
		override void OnModStoreSave( ModStorage storage, string modName )
		{
			//! Always call super at the start.
			super.OnModStoreSave( storage, modName );

			if ( modName != "JM_CommunityFramework" )
				return; //! Early exit

			storage.WriteVector( GetOrientation() );
			storage.WriteInt( 6 );

			//! The version of the mod is set in 'ModStructure::OnLoad', using 'SetStorageVersion'
			if ( storage.GetVersion() > 1 ) //! this check is redudant
			{
				storage.WriteString( "ThisVariableIsAddedWithVersion2" );
			}
		}
	}
	 */
	void OnModStoreSave( ModStorage storage, string modName )
	{

	}

	/**
	 * @param storage	Where the data is read from, only use public methods 'bool Read...(out value)`
	 * @param modName	The name of the mod from CfgMods class to check against
	 * 
	 * @code
	modded class KitBase // extends from ItemBase
	{
		override bool OnModStoreLoad( ModStorage storage, string modName )
		{
			if ( !super.OnModStoreLoad( storage, modName ) )
				return false;

			if ( modName != "JM_CommunityFramework" )
				return true; //! Early exit

			vector orientation;
			if ( !storage.ReadVector( orientation ) )
				return false;

			string intVar;
			if ( !storage.ReadInt( intVar ) )
				return false;

			//! The version of the mod is set in 'ModStructure::OnLoad', using 'SetStorageVersion'
			if ( storage.GetVersion() > 1 )
			{
				string strVar;
				if ( !storage.ReadString( strVar ) )
					return false;
			}

			return true;
		}
	}
	 */
	bool OnModStoreLoad( ModStorage storage, string modName )
	{
		return true;
	}
};