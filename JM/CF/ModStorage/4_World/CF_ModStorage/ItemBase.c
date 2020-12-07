modded class ItemBase
{
	autoptr CF_ModStorage_Object<ItemBase> m_CF_ModStorage = new CF_ModStorage_Object<ItemBase>(this);

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		m_CF_ModStorage.OnStoreSave(ctx);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if ( !super.OnStoreLoad(ctx, version)) return false;

		return m_CF_ModStorage.OnStoreLoad(ctx, version);
	}

	/**
	 * @param storage	Where the data is written to, only use public methods 'void Write...(value)`
	 * @param modName	The name of the mod from CfgMods class to check against
	 * 
	 * @code
	modded class KitBase // extends from ItemBase
	{
		override void CF_OnStoreSave( CF_ModStorage storage, string modName )
		{
			//! Always call super at the start.
			super.CF_OnStoreSave( storage, modName );

			if ( modName != "JM_CommunityFramework" )
				return; //! Early exit, we aren't writing our mod

			storage.Write( GetOrientation() );
			storage.Write( 6 );

			//! The version of the mod is set in 'ModStructure::OnLoad', using 'SetStorageVersion'
			if ( storage.GetVersion() > 1 ) //! this check is redudant for writing since it is assumed you are always writing the latest version
			{
				storage.Write( "ThisVariableIsAddedWithVersion2" );
			}

			array<ref CF_ModStorage_Test_Class_B> arrayOfClassesExample = new array<ref CF_ModStorage_Test_Class_B>();
			arrayOfClassesExample.Insert(new CF_ModStorage_Test_Class_B("arkensor", new CF_ModStorage_Test_Class_A(1768)));
			arrayOfClassesExample.Insert(new CF_ModStorage_Test_Class_B("tyler", new CF_ModStorage_Test_Class_A(1278)));
			arrayOfClassesExample.Insert(new CF_ModStorage_Test_Class_B("paul", new CF_ModStorage_Test_Class_A(278)));

			CF_ModStorage_Data_Array_Class<CF_ModStorage_Test_Class_B>.Write(storage, arrayOfClassesExample);
		}
	}
	 */
	void CF_OnStoreSave( CF_ModStorage storage, string modName )
	{

	}

	/**
	 * @param storage	Where the data is read from, only use public methods 'bool Read...(out value)`
	 * @param modName	The name of the mod from CfgMods class to check against
	 * 
	 * @code
	modded class KitBase // extends from ItemBase
	{
		override bool CF_OnStoreLoad( CF_ModStorage storage, string modName )
		{
			if ( !super.CF_OnStoreLoad( storage, modName ) )
				return false;

			if ( modName != "JM_CommunityFramework" )
				return true; //! Early exit, we aren't loading our mod

			vector orientation;
			if ( !storage.Read( orientation ) )
				return false;

			string intVar;
			if ( !storage.Read( intVar ) )
				return false;

			//! The version of the mod is set in 'ModStructure::OnLoad', using 'SetStorageVersion'
			if ( storage.GetVersion() > 1 )
			{
				string strVar;
				if ( !storage.Read( strVar ) )
					return false;
			}

			array<ref CF_ModStorage_Test_Class_B> arrayOfClassesExample = new array<ref CF_ModStorage_Test_Class_B>();
			CF_ModStorage_Data_Array_Class<CF_ModStorage_Test_Class_B>.Read(storage, arrayOfClassesExample);

			return true;
		}
	}
	 */
	bool CF_OnStoreLoad( CF_ModStorage storage, string modName )
	{
		return true;
	}
};