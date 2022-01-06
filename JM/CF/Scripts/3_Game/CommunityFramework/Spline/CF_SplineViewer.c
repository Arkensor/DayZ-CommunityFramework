#ifdef CF_SPLINE_TEST
ref CF_SplineDebug g_CF_SplineDebug;
ref CF_Spline g_CF_Spline;

float g_CF_SplineTension = 0.5;
float g_CF_SplineSpeed = 20.0;

int g_CF_SplineAddKeyCode = KeyCode.KC_J;
int g_CF_SplineCameraKeyCode = KeyCode.KC_I;
bool g_CF_SplinePressed = false;

bool g_CF_SplineCamera = false;
bool g_CF_SplineCameraPressed = false;

void CF_Spline_Create()
{
	if (g_CF_SplineDebug && g_CF_Spline) return;

	g_CF_Spline = new CF_Spline();
	g_CF_SplineDebug = new CF_SplineDebug(g_CF_Spline);

	g_CF_Spline.SetTension(g_CF_SplineTension, false);
}

void CF_Spline_AddCamera()
{	
	CF_Spline_Create();
	
	vector pos = GetGame().GetCurrentCameraPosition();
	vector ori = GetGame().GetCurrentCameraDirection().VectorToAngles();

	CF_SplinePoint point = new CF_SplinePoint();

	point.SetType(CF_SplinePointType.CUBIC);
	point.SetPosition(pos);
	//point.SetOrientation(ori); 
	
	g_CF_Spline.Insert(point);
}

void CF_Spline_CameraUpdate(float pDt)
{
	if (!g_CF_Spline) return;
	
	Camera camera = Camera.GetCurrentCamera();
	if (g_CF_SplineCamera && camera)
	{
		g_CF_Spline.Tick(pDt * g_CF_SplineSpeed);
		if (g_CF_Spline.Completed()) g_CF_Spline.SetTime(0);

		camera.SetPosition(g_CF_Spline.GetPosition());
		camera.SetOrientation(g_CF_Spline.GetOrientation());
	}
}

void CF_Spline_OnKeyPress(int key)
{
	if ( key == g_CF_SplineAddKeyCode ) 
	{
		if (!g_CF_SplinePressed)
		{
			CF_Spline_AddCamera();
		}

		g_CF_SplinePressed = true;
	}
	
	if ( key == g_CF_SplineCameraKeyCode ) 
	{
		if (!g_CF_SplineCameraPressed)
			g_CF_SplineCamera = !g_CF_SplineCamera;

		g_CF_SplineCameraPressed = true;
	}
	
	if ( key == KeyCode.KC_K ) 
	{
		g_CF_SplineDebug = null;
		g_CF_Spline = null;
	}
	
	if ( key == KeyCode.KC_O && g_CF_SplineDebug ) 
	{
		g_CF_SplineTension -= 0.05;
		g_CF_Spline.SetTension(g_CF_SplineTension);
	}
	
	if ( key == KeyCode.KC_P && g_CF_SplineDebug ) 
	{
		g_CF_SplineTension += 0.05;
		g_CF_Spline.SetTension(g_CF_SplineTension);
	}
	
	if (g_CF_Spline) g_CF_SplineTension = g_CF_Spline.GetTension();
}

void CF_Spline_OnKeyRelease(int key)
{
	if ( key == g_CF_SplineAddKeyCode ) 
	{
		g_CF_SplinePressed = false;
	}

	if ( key == g_CF_SplineCameraKeyCode ) 
	{
		g_CF_SplineCameraPressed = false;
	}
}

modded class DayZGame
{
	override void OnUpdate(bool doSim, float timeslice)
	{
		super.OnUpdate(doSim, timeslice);

		if (doSim)
		{
			CF_Spline_CameraUpdate(timeslice);
		}
	}

	override void OnKeyPress(int key)
	{
		CF_Spline_OnKeyPress(key);

		super.OnKeyPress(key);
	}
	
	override void OnKeyRelease(int key)
	{
		CF_Spline_OnKeyRelease(key);

		super.OnKeyRelease(key);
	}
};
#endif
