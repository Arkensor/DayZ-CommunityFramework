class CF_SplineDebug : Managed
{
	private ref array<Shape> m_Shapes = new array<Shape>();

	private ref CF_Spline m_Spline;

	void CF_SplineDebug(CF_Spline spline)
	{
		SetSpline(spline);
	}

	void ~CF_SplineDebug()
	{
		Clear();
		
		SetSpline(null);
	}

	void SetSpline(CF_Spline spline)
	{
		if (m_Spline == spline) return;

		if (m_Spline)
		{
			m_Spline.Update.Remove(Draw);
		}

		m_Spline = spline;

		if (m_Spline)
		{
			m_Spline.Update.Insert(Draw);
		}
	}

	CF_Spline GetSpline()
	{
		return m_Spline;
	}
	
	void Clear()
	{
		for ( int i = 0; i < m_Shapes.Count(); i++ )
		{
			if (!m_Shapes[i]) continue;
			m_Shapes[i].Destroy();
		}
		
		m_Shapes.Clear();
	}

	void Draw()
	{
		Clear();

		if (!m_Spline) return;

		float originalTime = m_Spline.GetTime();

		float maxTime = m_Spline.GetMaxTime();
		m_Spline.SetTime(0);
		m_Spline.Tick(0.0);

		vector p0 = m_Spline.GetPosition();
		vector o0 = m_Spline.GetOrientation();
		
		vector p1;
		vector o1;
		
		CF_SplinePoint current = m_Spline.GetCurrent();
		DrawSphere(current.GetPosition());
		
		while (m_Spline.GetTime() <= maxTime)
		{
			m_Spline.Tick(0.5);

			p1 = m_Spline.GetPosition();
			o1 = m_Spline.GetOrientation();

			DrawLine(p0, p1);
			
			p0 = p1;
			o0 = o1;
			
			CF_SplinePoint next = m_Spline.GetCurrent();
			if (next != current)
			{
				DrawSphere(next.GetPosition());
				
				current = next;
			}
		}

		m_Spline.SetTime(originalTime);
		m_Spline.Tick(0);
	}

	protected void DrawLine(vector start, vector end)
	{
		vector pts[2];
		pts[0] = start;
		pts[1] = end;
		Shape shape = Shape.CreateLines(0xFFFF00FF, ShapeFlags.TRANSP, pts, 2);
		m_Shapes.Insert(shape);
	}
	
	protected void DrawSphere(vector pos)
	{
		int flags = ShapeFlags.TRANSP | ShapeFlags.WIREFRAME;
		Shape shape = Shape.CreateSphere(ARGB(20, 255, 255, 0), flags, pos, 0.5);
		m_Shapes.Insert(shape);
	}
};
