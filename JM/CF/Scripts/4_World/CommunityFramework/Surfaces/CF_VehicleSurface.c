class CF_VehicleSurface
{
	protected static ref map<string, ref CF_VehicleSurface> s_VehicleSurfaces = new map<string, ref CF_VehicleSurface>();

	string Name;

	float NoiseSteer;
	float NoiseFrequency;
	float Roughness;
	float FrictionOffroad;
	float FrictionSlick;
	float RollResistance;
	float RollDrag;

	void CF_VehicleSurface(string name)
	{
		Name = name;

		s_VehicleSurfaces[Name] = this;

		string path;
		string rootPath = "CfgVehicleSurfaces " + Name + " ";

		path = rootPath + "noiseSteer";
		if (GetGame().ConfigIsExisting(path)) NoiseSteer = GetGame().ConfigGetFloat(path);

		path = rootPath + "noiseFrequency";
		if (GetGame().ConfigIsExisting(path)) NoiseFrequency = GetGame().ConfigGetFloat(path);

		path = rootPath + "roughness";
		if (GetGame().ConfigIsExisting(path)) Roughness = GetGame().ConfigGetFloat(path);

		path = rootPath + "frictionOffroad";
		if (GetGame().ConfigIsExisting(path)) FrictionOffroad = GetGame().ConfigGetFloat(path);

		path = rootPath + "frictionSlick";
		if (GetGame().ConfigIsExisting(path)) FrictionSlick = GetGame().ConfigGetFloat(path);

		path = rootPath + "rollResistance";
		if (GetGame().ConfigIsExisting(path)) RollResistance = GetGame().ConfigGetFloat(path);

		path = rootPath + "rollDrag";
		if (GetGame().ConfigIsExisting(path)) RollDrag = GetGame().ConfigGetFloat(path);
	}

	/**
	 * @brief Get the vehicle surface by the name. From 'CfgVehicleSurfaces'
	 * 
	 * @param name The class name of the surface
	 * 
	 * @return Instance of the vehicle surface class, creates a new one if it doesn't exist
	 */
	static CF_VehicleSurface Get(string name)
	{
		auto surf = s_VehicleSurfaces[name];
		if (!surf)
		{
			return new CF_VehicleSurface(name);
		}

		return surf;
	}

	/**
	 * @brief Get the vehicle surface at the position in the world
	 * 
	 * @param position The position of the surface within the world
	 * 
	 * @return Global instance of the vehicle surface class
	 */
	static CF_VehicleSurface At(vector position)
	{
		return CF_Surface.At(position).VehicleSurface;
	}

	/**
	 * @brief Get the vehicle surface at the position in the world at it's maximum height
	 * 
	 * @param x The x position of the surface within the world
	 * @param z The z position of the surface within the world
	 * 
	 * @return Global instance of the vehicle surface class
	 */
	static CF_VehicleSurface At(float x, float z)
	{
		return CF_Surface.At(x, z).VehicleSurface;
	}

#ifdef CF_DebugUI
	bool CF_OnDebugUpdate(CF_Debug instance, CF_DebugUI_Type type)
	{
		instance.Add("Name", Name);
		instance.Add("Noise Steer", NoiseSteer);
		instance.Add("Noise Frequency", NoiseFrequency);
		instance.Add("Roughness", Roughness);
		instance.Add("Friction Offroad", FrictionOffroad);
		instance.Add("Friction Slick", FrictionSlick);
		instance.Add("Roll Resistance", RollResistance);
		instance.Add("Roll Drag", RollDrag);

		return true;
	}
#endif
};
