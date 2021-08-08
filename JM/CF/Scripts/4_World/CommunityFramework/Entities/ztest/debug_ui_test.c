// This is only temporary testing code. Due to a script compile error the folder name is weird :)

modded class ZombieBase
{
	void ZombieBase()
	{
		CF_DebugUI.Create(this);
	}

	void ~ZombieBase()
	{
		CF_DebugUI.Destroy(this);
	}

	/**
	 * @note When overriding and adding to the instance, you must return true.
	 */
	override bool CF_OnDebugUpdate(CF_DebugUI_Instance instance, CF_DebugUI_Type type)
	{
		DayZInfectedInputController dzip = GetInputController();

		instance.Add("Movement Speed", dzip.GetMovementSpeed());
		instance.Add("Alert Level", dzip.GetAlertLevel());
		instance.Add("Vault", dzip.IsVault());
		instance.Add("Vault Height", dzip.GetVaultHeight());
		instance.Add("Mind State", dzip.GetMindState());
		instance.Add("Target Entity", dzip.GetTargetEntity());
		instance.Add("Look At Enabled", dzip.IsLookAtEnabled());
		instance.Add("Look At DirectionWS", dzip.GetLookAtDirectionWS());

		return true;
	}
};

modded class CarScript
{
	void CarScript()
	{
		CF_DebugUI.Create(this);
	}

	void ~CarScript()
	{
		CF_DebugUI.Destroy(this);
	}

	/**
	 * @note When overriding and adding to the instance, you must return true.
	 */
	override bool CF_OnDebugUpdate(CF_DebugUI_Instance instance, CF_DebugUI_Type type)
	{
		super.CF_OnDebugUpdate(instance, type);

		CarController cc = GetController();

		instance.Add("Velocity", GetVelocity(this));
		instance.Add("Speedometer", GetSpeedometer());
		instance.Add("Fluid Capacity FUEL", GetFluidCapacity(CarFluid.FUEL));
		instance.Add("Fluid Fraction FUEL", GetFluidFraction(CarFluid.FUEL));
		instance.Add("Fluid Capacity OIL", GetFluidCapacity(CarFluid.OIL));
		instance.Add("Fluid Fraction OIL", GetFluidFraction(CarFluid.OIL));
		instance.Add("Fluid Capacity BRAKE", GetFluidCapacity(CarFluid.BRAKE));
		instance.Add("Fluid Fraction BRAKE", GetFluidFraction(CarFluid.BRAKE));
		instance.Add("Fluid Capacity COOLANT", GetFluidCapacity(CarFluid.COOLANT));
		instance.Add("Fluid Fraction COOLANT", GetFluidFraction(CarFluid.COOLANT));
		instance.Add("Engine On", EngineIsOn());
		instance.Add("Engine RPM", EngineGetRPM());
		instance.Add("Engine RPM Max", EngineGetRPMMax());
		instance.Add("Engine RPM Redline", EngineGetRPMRedline());
		instance.Add("Steering", cc.GetSteering());
		instance.Add("Thrust", cc.GetThrust());
		instance.Add("Thrust Turbo", cc.GetThrustTurbo());
		instance.Add("Thrust Gentle", cc.GetThrustGentle());
		instance.Add("Brake", cc.GetBrake());
		instance.Add("Gear", cc.GetGear());
		instance.Add("Gear Count", GetGearsCount());

		return true;
	}
};
