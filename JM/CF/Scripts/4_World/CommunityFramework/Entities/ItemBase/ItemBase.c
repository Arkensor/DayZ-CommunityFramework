modded class ItemBase
{
	/**
	 * @note When overriding and adding to the instance, you must return true.
	 */
	bool CF_OnDebugUpdate(CF_Debug instance, CF_DebugUI_Type type)
	{
		return false;
	}
};
