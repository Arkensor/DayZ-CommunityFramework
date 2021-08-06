modded class CarScript
{
	void CarScript()
	{
		CF_DebugUI.Show(this);
	}

	void ~CarScript()
	{
		CF_DebugUI.Hide(this);
	}
};

modded class DayZPlayerImplement
{
	void DayZPlayerImplement()
	{
		CF_DebugUI.Show(this);
	}

	void ~DayZPlayerImplement()
	{
		CF_DebugUI.Hide(this);
	}
};
