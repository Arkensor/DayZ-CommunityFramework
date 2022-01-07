modded class ItemBase
{
	autoptr CF_ModStorage_Base m_CF_ModStorage;

	void ItemBase()
	{
		m_CF_ModStorage = new CF_ModStorage_Object<ItemBase>(this);
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		m_CF_ModStorage.OnStoreSave(ctx);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		return m_CF_ModStorage.OnStoreLoad(ctx, version);
	}

	/**
	 * @param storage	Map of 'CF_ModStorage' classes
	 * 
	 * @code
	 *	modded class KitBase // extends from ItemBase
	 *	{
	 *		override void CF_OnStoreSave(map<string, CF_ModStorage> storage)
	 *		{
	 *			//! Always call super at the start.
	 *			super.CF_OnStoreSave(storage);
	 *	
	 *			auto ctx = storage["JM_CommunityFramework"];
	 *			
	 *			ctx.Write(GetOrientation());
	 *			ctx.Write(6);
	 *	
	 *			//! The version of the mod is set in config 'storageVersion' for 'CfgMods' class
	 *	
	 *			//! redundant check for checking if the writing version matches
	 *			if (ctx.GetVersion() > 1)
	 *			{
	 *				ctx.Write("ThisVariableIsAddedWithVersion2");
	 *			}
	 *		}
	 *	}
	 */
	void CF_OnStoreSave(map<string, CF_ModStorage> storage)
	{
	}

	/**
	 * @param storage	Map of 'CF_ModStorage' classes
	 * 
	 * @return True if loading was successful
	 * 
	 * @code
	 * 	modded class KitBase // extends from ItemBase
	 * 	{
	 * 		override bool CF_OnStoreLoad(map<string, CF_ModStorage> storage)
	 * 		{
	 * 			if (!super.CF_OnStoreLoad(storage))
	 * 				return false;
	 * 	
	 *			auto ctx = storage["JM_CommunityFramework"];
	 * 	
	 * 			vector orientation;
	 * 			if (!ctx.Read(orientation)) return false;
	 * 	
	 * 			string intVar;
	 * 			if (!ctx.Read(intVar)) return false;
	 * 	
	 *			//! The version of the mod is set in config 'storageVersion' for 'CfgMods' class
	 * 
	 * 			string strVar;
	 * 			if (ctx.GetVersion() > 1)
	 * 			{
	 * 				if (!ctx.Read(strVar)) return false;
	 * 			}
	 * 			else
	 * 			{
	 * 				strVar = "Default Value";
	 * 			}
	 * 			
	 * 			return true;
	 * 		}
	 * 	}
	 * @endcode
	 */
	bool CF_OnStoreLoad(map<string, CF_ModStorage> storage)
	{
		return true;
	}
};