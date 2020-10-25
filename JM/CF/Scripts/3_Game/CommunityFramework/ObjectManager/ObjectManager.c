class CF__ObjectManager 
{
	private static ref const map<Object, ref OLinkT> REGISTERED_OBJECTS = new map<Object, ref OLinkT>;
	
	private void CF__ObjectManager();
	private void ~CF__ObjectManager();
	
	/**
	 * @brief Registers obj to be exempt of being affected by the network bubble and the view distance.
	 *
	 * @param obj	Object pointer.
	 * @return bool	true of the object registered, false otherwise.
	 */
	static bool Register( Object obj )
	{
		if ( !obj || IsObjectRegistered( obj ) )
			return false;
		
		REGISTERED_OBJECTS.Insert( obj, new OLinkT( obj ) );
		return true;
	}
	
	/**
	 * @brief Registers objects to be exempt of being affected by the network bubble and the view distance.
	 *
	 * @param objects	array<Object> array of objects to register.
	 */
	static void Register( array<Object> objects )
	{
		foreach ( Object obj: objects )
			Register( obj );
	}
	
	/**
	 * @brief Unregisters obj so that it can be affected by the network bubble and the view distance.
	 *
	 * @param obj	Object pointer.
	 * @return bool	true of the object unregistered, false otherwise.
	 */
	static bool Unregister( Object obj )
	{
		if ( !obj )
			return false;
		
		OLinkT objectLink = REGISTERED_OBJECTS.Get( obj );
		
		if ( !objectLink )
			return false;
		
		REGISTERED_OBJECTS.Remove( obj );
		
		if ( !objectLink.IsNull() )
			objectLink.Release();
		
		return true;
	}
	
	/**
	 * @brief Unregisters objects so that it can be affected by the network bubble and the view distance.
	 *
	 * @param objects	array<Object> array of objects to unregister.
	 */
	static void Unregister( array<Object> objects )
	{
		foreach ( Object obj: objects )
			Unregister( obj );
	}
	
	/**
	 * @brief Checks if obj is registered.
	 *
	 * @param obj	Object pointer
	 * @return bool	true of the object registered, false otherwise.
	 */
	static bool IsObjectRegistered( Object obj )
	{
		if ( !obj )
			return false;
		
		return REGISTERED_OBJECTS.Contains( obj );
	}
	
	/**
	 * @brief Checks if obj is a map object.
	 *
	 * @param obj	Object pointer
	 * @return bool	true of the object is a map object, false otherwise.
	 */
	static bool IsMapObject( Object obj )
	{
		if ( !obj )
			return false;
		
		// Added via p3d in TB with no config.
		bool isStatic = (obj.GetType() == string.Empty) && (obj.Type() == Object);
		// Inherits from House in Cfg class.
		// Building, House, Wreck, Well, Tree, Bush, etc.
		bool isHouse = obj.IsKindOf("House");
		bool isVegetation = obj.IsTree() || obj.IsBush();
		
		return isStatic || isHouse || isVegetation;
	}
	
	/**
	 * @brief Removes static object from the map.
	 *
	 * @param obj	Object pointer
	 */
	static void RemoveObject( Object obj )
	{
		if ( !obj || !IsMapObject( obj ) )
			return;
		
		Register( obj );
		EntityFlags entityFlags = obj.GetFlags();
		EntityEvent entityEvents = obj.GetEventMask();
		obj.ClearFlags( entityFlags, true );
		obj.ClearEventMask( entityEvents );
		obj.SetEventMask( EntityEvent.NOTVISIBLE );
		obj.SetScale( 0.0 );
		dBodyDestroy( obj ); //! Needed for disabling some extra collisions.
	}
	
	/**
	 * @brief Removes static objects at certain position and radius from the map (No height).
	 *
	 * @param position	vector coordinates of the center.
	 * @param radius	float radius of the query.
	 */
	static void RemoveObjectsInRadius2D( vector position, float radius )
	{
		array<Object> objects = new array<Object>();
		array<CargoBase> proxyCargos = new array<CargoBase>();
				
		GetGame().GetObjectsAtPosition( position, radius, objects, proxyCargos );
		foreach ( Object obj: objects )
			RemoveObject( obj );
	}
	
	/**
	 * @brief Removes static objects at certain position and radius from the map.
	 *
	 * @param position	vector coordinates of the center.
	 * @param radius	float radius of the query.
	 */
	static void RemoveObjectsInRadius3D( vector position, float radius )
	{
		array<Object> objects = new array<Object>();
		array<CargoBase> proxyCargos = new array<CargoBase>();
				
		GetGame().GetObjectsAtPosition3D( position, radius, objects, proxyCargos );
		foreach ( Object obj: objects )
			RemoveObject( obj );
	}
	
	/**
	 * @brief Get all current registered objects.
	 *
	 * @return array<Object>	array of current registered objects.
	 */
	static array<Object> GetRegisteredObjects()
	{
		return REGISTERED_OBJECTS.GetKeyArray();
	}
}