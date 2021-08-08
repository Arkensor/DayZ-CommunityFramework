modded class BuildingBase
{
	protected autoptr CF_DebugUI m_CF_DebugUI;

	CF_DebugUI CF_CreateDebugUI()
	{
		if (m_CF_DebugUI) return m_CF_DebugUI;
		m_CF_DebugUI = CF_DebugUI.Create(this);
		return m_CF_DebugUI;
	}

	/**
	 * @note When overriding and adding to the instance, you must return true.
	 */
	bool CF_OnDebugUpdate(CF_DebugUI_Instance instance, CF_DebugUI_Type type)
	{
		return false;
	}
};

modded class AnimalBase
{
	protected autoptr CF_DebugUI m_CF_DebugUI;

	CF_DebugUI CF_CreateDebugUI()
	{
		if (m_CF_DebugUI) return m_CF_DebugUI;
		m_CF_DebugUI = CF_DebugUI.Create(this);
		return m_CF_DebugUI;
	}

	/**
	 * @note When overriding and adding to the instance, you must return true.
	 */
	bool CF_OnDebugUpdate(CF_DebugUI_Instance instance, CF_DebugUI_Type type)
	{
		return false;
	}
};

modded class ZombieBase
{
	protected autoptr CF_DebugUI m_CF_DebugUI;

	CF_DebugUI CF_CreateDebugUI()
	{
		if (m_CF_DebugUI) return m_CF_DebugUI;
		m_CF_DebugUI = CF_DebugUI.Create(this);
		return m_CF_DebugUI;
	}

	/**
	 * @note When overriding and adding to the instance, you must return true.
	 */
	bool CF_OnDebugUpdate(CF_DebugUI_Instance instance, CF_DebugUI_Type type)
	{
		return false;
	}
};

modded class ItemBase
{
	protected autoptr CF_DebugUI m_CF_DebugUI;

	CF_DebugUI CF_CreateDebugUI()
	{
		if (m_CF_DebugUI) return m_CF_DebugUI;
		m_CF_DebugUI = CF_DebugUI.Create(this);
		return m_CF_DebugUI;
	}

	/**
	 * @note When overriding and adding to the instance, you must return true.
	 */
	bool CF_OnDebugUpdate(CF_DebugUI_Instance instance, CF_DebugUI_Type type)
	{
		return false;
	}
};

modded class DayZPlayerImplement
{
	protected autoptr CF_DebugUI m_CF_DebugUI;

	CF_DebugUI CF_CreateDebugUI()
	{
		if (m_CF_DebugUI) return m_CF_DebugUI;
		m_CF_DebugUI = CF_DebugUI.Create(this);
		return m_CF_DebugUI;
	}

	/**
	 * @note When overriding and adding to the instance, you must return true.
	 */
	bool CF_OnDebugUpdate(CF_DebugUI_Instance instance, CF_DebugUI_Type type)
	{
		return false;
	}
};

modded class CarScript
{
	protected autoptr CF_DebugUI m_CF_DebugUI;

	CF_DebugUI CF_CreateDebugUI()
	{
		if (m_CF_DebugUI) return m_CF_DebugUI;
		m_CF_DebugUI = CF_DebugUI.Create(this);
		return m_CF_DebugUI;
	}

	/**
	 * @note When overriding and adding to the instance, you must return true.
	 */
	bool CF_OnDebugUpdate(CF_DebugUI_Instance instance, CF_DebugUI_Type type)
	{
		return false;
	}
};

modded class HelicopterScript
{
	protected autoptr CF_DebugUI m_CF_DebugUI;

	CF_DebugUI CF_CreateDebugUI()
	{
		if (m_CF_DebugUI) return m_CF_DebugUI;
		m_CF_DebugUI = CF_DebugUI.Create(this);
		return m_CF_DebugUI;
	}

	/**
	 * @note When overriding and adding to the instance, you must return true.
	 */
	bool CF_OnDebugUpdate(CF_DebugUI_Instance instance, CF_DebugUI_Type type)
	{
		return false;
	}
};

modded class AdvancedCommunication
{
	protected autoptr CF_DebugUI m_CF_DebugUI;

	CF_DebugUI CF_CreateDebugUI()
	{
		if (m_CF_DebugUI) return m_CF_DebugUI;
		m_CF_DebugUI = CF_DebugUI.Create(this);
		return m_CF_DebugUI;
	}

	/**
	 * @note When overriding and adding to the instance, you must return true.
	 */
	bool CF_OnDebugUpdate(CF_DebugUI_Instance instance, CF_DebugUI_Type type)
	{
		return false;
	}
};
