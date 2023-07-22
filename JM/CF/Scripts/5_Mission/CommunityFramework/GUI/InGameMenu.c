modded class InGameMenu
{
	void ~InGameMenu()
	{
		CF_Debug.CloseManager();
	}

	override Widget Init()
	{
		super.Init();

		if (!CF_Debug.IsAllowed()) return layoutRoot;

		Widget wLeft = layoutRoot.FindAnyWidget("dayz_logo");
		Widget wRight = layoutRoot.FindAnyWidget("play_panel_root");

		float x;
		float y;

		float h;
		float w;

		wLeft.GetScreenPos(x, y);
		wLeft.GetScreenSize(w, h);

		x = x + w;

		wRight.GetScreenPos(w, h);

		w = w - x;

		Widget debugManager = CF_Debug.ShowManager(layoutRoot);

		float d_x;
		float d_y;
		float d_w;
		float d_h;

		debugManager.GetScreenPos(d_x, d_y);
		debugManager.GetScreenSize(d_w, d_h);

		int marginX = 0;
		int marginY = 0;

		d_y = d_y / d_h;
		d_h = d_h / d_h;
		marginY = marginY / d_h;

		debugManager.SetPos(x + marginX, d_y + marginY);
		debugManager.SetSize(w - (marginX * 2), d_h - (marginY * 2));

		return layoutRoot;
	}
};