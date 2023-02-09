class CF_ObjectManager_ObjectLink extends OLinkT
{
    int flags;
    int eventMask;
}

class CF_ObjectManager
{
    //!Single static instance. Do not create with new or spawn - use CF.ObjectManager for access instead.
    protected void CF_ObjectManager()
    {
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif
    }

    protected void ~CF_ObjectManager()
    {
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif
    }

    protected static const int HIDE_OBJECT_AXIS_OFFSET = 10000;

    protected static const ref map<Object, ref CF_ObjectManager_ObjectLink> m_HiddenObjects = new map<Object, ref CF_ObjectManager_ObjectLink>();

    protected static const ref array<ref CF_ObjectManager_ObjectLink> m_HiddenObjectsArray = new array<ref CF_ObjectManager_ObjectLink>();

    /**
     * @brief Hides a static map object (Houses, Vegetation, etc.) visually and physically.
     * @code
     * Object hidden = CF.ObjectManager.HideMapObject(object);
     * @endcode
     *
     * @param object            Object to be hidden
     * @param updatePathGraph   Performs a path graph update after the object has been hidden. Enabled by default.
     * @return Object           instance of the object that was hidden, NULL in case of failure or invalid params.
     */
    static Object HideMapObject(Object object, bool updatePathGraph = true)
    {
        if (!IsMapObject(object)) return NULL; //Object is not a map object

        if (IsMapObjectHidden(object)) return NULL; //Object already hidden

        //Remember the original position for path graph updates
        auto originalPosition = object.GetPosition();

        //Register object in it's current state
        auto link = new CF_ObjectManager_ObjectLink(object);
        link.flags = object.GetFlags();
        link.eventMask = object.GetEventMask();

        object.ClearFlags(link.flags, true);
        object.ClearEventMask(link.eventMask);

        m_HiddenObjects.Set(object, link);
        m_HiddenObjectsArray.Insert(link);

        vector tm[4];
        object.GetTransform(tm);
        tm[3] = tm[3] - Vector(HIDE_OBJECT_AXIS_OFFSET, HIDE_OBJECT_AXIS_OFFSET, HIDE_OBJECT_AXIS_OFFSET);
        object.SetTransform(tm);
        object.Update();

        if (updatePathGraph && object.CanAffectPathgraph())
        {
            vector minMax[2];
            auto objectRadius = object.ClippingInfo(minMax);
            auto radiusVector = Vector(objectRadius, objectRadius, objectRadius);
            g_Game.UpdatePathgraphRegion(originalPosition - radiusVector, originalPosition + radiusVector);
        }

        return object;
    }

    /**
     * @brief Unhides an array of map objects
     * @code
     * array<Object> hidden = CF.ObjectManager.HideMapObjects(objects);
     * @endcode
     *
     * @param objects           Objects to be hidden
     * @param updatePathGraph   Performs a path graph update after the objects were hidden. Enabled by default.
     * @return array<Object>    Array of objects that were hidden.
     */
    static array<Object> HideMapObjects(array<Object> objects, bool updatePathGraph = true)
    {
        array<Object> hidden();

        foreach (auto object: objects)
        {
            /*
                Todo potential improvement:
                Determine if a single path graph update over the whole area is more effective that many small ones.
                Possible metrics:
                    - Object count to area ratio
                    - Max distance between objects
                    - Fixed radius lookup table
            */
            if (HideMapObject(object, updatePathGraph))
            {
                hidden.Insert(object);
            }
        }

        return hidden;
    }

    /**
     * @brief Hides static map objects at certain position and within a given radius
     * @code
     * array<Object> hidden = CF.ObjectManager.HideMapObjectsInRadius(position, 1000);
     * @endcode
     *
     * @param centerPosition    center coordinates for the hide area.
     * @param radius            radius of the hide area.
     * @param limitHeight       y-axis limit for the hide area (Sphere). Disabled by default.
     * @param updatePathGraph   Performs a path graph update after the objects were hidden. Enabled by default.
     * @return array<Object>    Array of objects that were hidden.
     */
    static array<Object> HideMapObjectsInRadius(vector centerPosition, float radius, bool limitHeight = false, bool updatePathGraph = true)
    {
        array<Object> objects();

        if (limitHeight)
        {
            GetGame().GetObjectsAtPosition3D(centerPosition, radius, objects, NULL);
        }
        else
        {
            GetGame().GetObjectsAtPosition(centerPosition, radius, objects, NULL);
        }

        array<Object> hidden();

        foreach (auto object: objects)
        {
            //Todo potential improvement -> s. HideMapObjects
            if (HideMapObject(object, updatePathGraph))
            {
                hidden.Insert(object);
            }
        }

        return hidden;
    }

    /**
     * @brief Unhides a hidden static map object (Houses, Vegetation, etc.).
     * @code
     * Object unhidden = CF.ObjectManager.UnhideMapObject(hiddenObject);
     * @endcode
     *
     * @param object            Object to be unhidden
     * @param updatePathGraph   Performs a path graph update after the object has been unhidden. Enabled by default.
     * @return Object           instance of the object that was unhidden, NULL in case of failure or invalid params.
     */
    static Object UnhideMapObject(Object object, bool updatePathGraph = true)
    {
        //Remove object from hidden collection
        auto link = m_HiddenObjects[object];

        if (!link) return NULL; //Object not known as hidden

        m_HiddenObjects.Remove(object);
        
        auto arrayIdx = m_HiddenObjectsArray.Find(link);
        if(arrayIdx >= 0) m_HiddenObjectsArray.Remove(arrayIdx);

        vector tm[4];
        object.GetTransform(tm);
        tm[3] = tm[3] + Vector(HIDE_OBJECT_AXIS_OFFSET, HIDE_OBJECT_AXIS_OFFSET, HIDE_OBJECT_AXIS_OFFSET);
        object.SetTransform(tm);

        object.SetFlags(link.flags, true);
        object.SetEventMask(link.eventMask);

        object.Update();

        if (updatePathGraph && object.CanAffectPathgraph())
        {
            vector minMax[2];
            auto objectPosition = object.GetPosition();
            auto objectRadius = object.ClippingInfo(minMax);
            auto radiusVector = Vector(objectRadius, objectRadius, objectRadius);
            g_Game.UpdatePathgraphRegion(objectPosition - radiusVector, objectPosition + radiusVector);
        }

        return object;
    }

    /**
     * @brief Unhides an array of map objects
     * @code
     * array<Object> unhidden = CF.ObjectManager.UnhideMapObjects(hiddenObjects);
     * @endcode
     *
     * @param objects           Objects to be unhidden
     * @param updatePathGraph   Performs a path graph update after the objects were unhidden. Enabled by default.
     * @return array<Object>    Array of objects that were unhidden.
     */
    static array<Object> UnhideMapObjects(array<Object> objects, bool updatePathGraph = true)
    {
        array<Object> unhidden();

        foreach (auto object: objects)
        {
            //Todo potential improvement -> s. HideMapObjects
            if (UnhideMapObject(object, updatePathGraph))
            {
                unhidden.Insert(object);
            }
        }

        return unhidden;
    }

    /**
     * @brief Unhides static map objects at certain position and within a given radius
     * @code
     * array<Object> unhidden = CF.ObjectManager.UnhideMapObjectsInRadius(position, 1000);
     * @endcode
     *
     * @param centerPosition    center coordinates for the unhide area.
     * @param radius            radius of the unhide area.
     * @param limitHeight       y-axis limit for the unhide area (Sphere). Disabled by default.
     * @param updatePathGraph   Performs a path graph update after the objects were unhidden. Enabled by default.
     * @return array<Object>    Array of objects that were unhidden.
     */
    static array<Object> UnhideMapObjectsInRadius(vector centerPosition, float radius, bool limitHeight = false, bool updatePathGraph = true)
    {
        array<Object> objects();

        if (limitHeight)
        {
            GetGame().GetObjectsAtPosition3D(centerPosition, radius, objects, NULL);
        }
        else
        {
            GetGame().GetObjectsAtPosition(centerPosition, radius, objects, NULL);
        }

        return UnhideMapObjects(objects, updatePathGraph);
    }

    /**
     * @brief Unhides all hidden map objects
     * @code
     * array<Object> unhidden = CF.ObjectManager.UnhideAllMapObjects();
     * @endcode
     *
     * @param updatePathGraph   Performs a path graph update after the objects were unhidden. Enabled by default.
     * @return array<Object>    Array of objects that were unhidden.
     */
	static array<Object> UnhideAllMapObjects(bool updatePathGraph = true)
	{
	    //Expected result would be all the hidden objects
	    auto unhidden = GetHiddenMapObjects();

        for(int nObject = 0; nObject < unhidden.Count(); nObject++)
        {
            //Todo potential improvement -> s. HideMapObjects
            if (!UnhideMapObject(unhidden[nObject], updatePathGraph))
            {
                //If - for what ever reason - the object was not unhidden, remove it from the result collection.
                unhidden.RemoveOrdered(nObject--);
            }
        }

        return unhidden;
	}

    /**
     * @brief Returns all map objects that are currently hidden
     * @code
     * array<Object> objects = CF.ObjectManager.GetHiddenMapObjects();
     * @endcode
     *
     * @return array<Object> Array of hidden objects.
     */
	static array<Object> GetHiddenMapObjects()
	{
        array<Object> objects();
        
        foreach(auto link : m_HiddenObjectsArray)
        {
            objects.Insert(link.Ptr());
        }
        
        return objects;
	}

    /**
     * @brief Checks if a map object is currently hidden.
     * @code
     * bool isHiddenObject = CF.ObjectManager.IsMapObjectHidden(object);
     * @endcode
     *
     * @param object Object to check
     * @return bool true if currently hidden, false otherwise.
     */
    static bool IsMapObjectHidden(Object object)
    {
        return m_HiddenObjects.Contains(object);
    }

    /**
     * @brief Checks if the given object is part of the baked map objects.
     * @code
     * bool isMapObject = CF.ObjectManager.IsMapObject(object);
     * @endcode
     *
     * @param object Object pointer
     * @return bool    true if it is a map object, false otherwise.
     */
    static bool IsMapObject(Object object)
    {
        if (!object) return false; //Null

        // Added via p3d in TB with no config.
        // Inherits from House in Cfg class -> Building, House, Wreck, Well, Tree, Bush, etc.
        return ((object.GetType() == string.Empty) && (object.Type() == Object)) || object.IsKindOf("House") || object.IsTree() || object.IsBush() || object.IsRock() || object.IsInherited(Static);
    }

    /**
     * @brief [Internal] CommunityFramework cleanup
     *
     * @return void
     */
    static void _Cleanup()
    {
        //Cleanup hidden object allocation
        m_HiddenObjects.Clear();
        delete m_HiddenObjects;
        
        m_HiddenObjectsArray.Clear();
        delete m_HiddenObjectsArray;
    }
}
