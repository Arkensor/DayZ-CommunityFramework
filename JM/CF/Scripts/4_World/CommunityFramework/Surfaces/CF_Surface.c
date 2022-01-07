class CF_Surface
{
	protected static ref map<string, ref CF_Surface> s_Surfaces = new map<string, ref CF_Surface>();

	string Name;

	float Interior;
	float Deflection;
	float Friction;
	float Restitution;

	string SoundEnvironent;
	string SoundHit;
	string Character;

	float FootDamage;
	float Audibility;

	string Impact;

	bool IsDigable;
	bool IsFertile;

	float ChanceForCatch;
	float WindModifier;

	CF_VehicleSurface VehicleSurface;

	private void CF_Surface(string name)
	{
		Name = name;

		s_Surfaces[Name] = this;

		string path;
		string rootPath = "CfgSurfaces " + Name + " ";

		path = rootPath + "interior";
		if (GetGame().ConfigIsExisting(path)) Interior = GetGame().ConfigGetFloat(path);

		path = rootPath + "deflection";
		if (GetGame().ConfigIsExisting(path)) Deflection = GetGame().ConfigGetFloat(path);

		path = rootPath + "friction";
		if (GetGame().ConfigIsExisting(path)) Friction = GetGame().ConfigGetFloat(path);

		path = rootPath + "restitution";
		if (GetGame().ConfigIsExisting(path)) Restitution = GetGame().ConfigGetFloat(path);

		path = rootPath + "soundEnviron";
		if (GetGame().ConfigIsExisting(path)) SoundEnvironent = GetGame().ConfigGetTextOut(path);

		path = rootPath + "soundHit";
		if (GetGame().ConfigIsExisting(path)) SoundHit = GetGame().ConfigGetTextOut(path);

		path = rootPath + "character";
		if (GetGame().ConfigIsExisting(path)) Character = GetGame().ConfigGetTextOut(path);

		path = rootPath + "footDamage";
		if (GetGame().ConfigIsExisting(path)) FootDamage = GetGame().ConfigGetFloat(path);

		path = rootPath + "audibility";
		if (GetGame().ConfigIsExisting(path)) Audibility = GetGame().ConfigGetFloat(path);

		path = rootPath + "impact";
		if (GetGame().ConfigIsExisting(path)) Impact = GetGame().ConfigGetTextOut(path);

		path = rootPath + "isDigable";
		if (GetGame().ConfigIsExisting(path)) IsDigable = GetGame().ConfigGetInt(path);

		path = rootPath + "isFertile";
		if (GetGame().ConfigIsExisting(path)) IsFertile = GetGame().ConfigGetInt(path);

		path = rootPath + "chanceForCatch";
		if (GetGame().ConfigIsExisting(path)) ChanceForCatch = GetGame().ConfigGetFloat(path);

		path = rootPath + "windModifier";
		if (GetGame().ConfigIsExisting(path)) WindModifier = GetGame().ConfigGetFloat(path);

		path = rootPath + "vpSurface";
		if (GetGame().ConfigIsExisting(path)) VehicleSurface = CF_VehicleSurface.Get(GetGame().ConfigGetTextOut(path));
	}
	
	/**
	 * @brief Private constructor to prevent from marking as ref
	 */
	private void ~CF_Surface()
	{
	}

	/**
	 * @brief Get the surface by the name. From 'CfgSurfaces'
	 * 
	 * @param name The class name of the surface
	 * 
	 * @return Instance of the surface class, creates a new one if it doesn't exist
	 */
	static CF_Surface Get(string name)
	{
		auto surf = s_Surfaces[name];
		if (!surf)
		{
			return new CF_Surface(name);
		}

		return surf;
	}

	/**
	 * @brief Get the surface at the position in the world
	 * 
	 * @param position The position of the surface within the world
	 * 
	 * @return Global instance of the surface class
	 */
	static CF_Surface At(vector position)
	{
		string name;
		GetGame().SurfaceGetType3D(position[0], position[1], position[2], name);
		return CF_Surface.Get(name);
	}

	/**
	 * @brief Get the surface at the position in the world at it's maximum height
	 * 
	 * @param x The x position of the surface within the world
	 * @param z The z position of the surface within the world
	 * 
	 * @return Global instance of the surface class
	 */
	static CF_Surface At(float x, float z)
	{
		string name;
		GetGame().SurfaceGetType(x, z, name);
		return CF_Surface.Get(name);
	}

#ifdef CF_DebugUI
	bool CF_OnDebugUpdate(CF_Debug instance, CF_DebugUI_Type type)
	{
		instance.Add("Name", Name);
		instance.Add("Interior", Interior);
		instance.Add("Deflection", Deflection);
		instance.Add("Friction", Friction);
		instance.Add("Restitution", Restitution);
		instance.Add("Sound Environent", SoundEnvironent);
		instance.Add("Sound Hit", SoundHit);
		instance.Add("Character", Character);
		instance.Add("Foot Damage", FootDamage);
		instance.Add("Audibility", Audibility);
		instance.Add("Impact", Impact);
		instance.Add("Is Digable", IsDigable);
		instance.Add("Is Fertile", IsFertile);
		instance.Add("Chance For Catch", ChanceForCatch);
		instance.Add("Wind Modifier", WindModifier);
		instance.Add(VehicleSurface);

		return true;
	}
#endif
};
