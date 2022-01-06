class CF_SplinePoint : Managed
{
	private CF_Spline m_Spline;
	private ref CF_SplinePoint m_Next;
	private CF_SplinePoint m_Prev;

	protected vector m_Position;
	protected vector m_Orientation;
	protected CF_SplinePointType m_Type;

	protected float m_SpeedCoef;
	protected bool m_DerivedRotation;
	
	protected float m_Start;
	protected float m_Length;

	protected float m_Rotation[4];
	protected vector m_Tangent;
	
	void CF_SplinePoint(vector position = vector.Zero)
	{
		SetPosition(position);

		SetSpeedCoef(1.0);
		SetRotationDerived(true);
	}
	
	void ~CF_SplinePoint()
	{
	}

	void SetSpline(CF_Spline spline)
	{
		m_Spline = spline;
	}

	CF_Spline GetSpline()
	{
		return m_Spline;
	}
	
	void SetPosition(vector position, bool imd = true)
	{
		m_Position = position;

		if (imd && m_Spline) m_Spline._Update();
	}
	
	vector GetPosition()
	{
		return m_Position;
	}

	void CalculateTangent(bool imd = true)
	{
		float diff = GetEnd();
		if (m_Prev) diff = GetEnd() - m_Prev.GetStart();
		
		vector pv = vector.Zero;
		vector nv = vector.Zero;

		if (m_Next) nv = vector.Direction(m_Next.GetPosition(), m_Position);
		if (m_Prev) pv = vector.Direction(m_Position, m_Prev.GetPosition());
		
		if (!m_Next && m_Prev) nv = vector.Direction(m_Prev.GetPosition(), m_Position);
		if (!m_Prev && m_Next) pv = vector.Direction(m_Position, m_Next.GetPosition());

		m_Tangent = (pv + nv) * -(1.0 - m_Spline.GetTension()) * (1.0 / Math.Max(0.0001, diff));

		if (imd && m_Spline) m_Spline._Update();
	}

	void SetTangent(vector tangent, bool imd = true)
	{
		m_Tangent = tangent;
		m_Type = CF_SplinePointType.CUBIC_USER;

		if (imd && m_Spline) m_Spline._Update();
	}
	
	vector GetTangent()
	{
		return m_Tangent;
	}
	
	void SetDirection(vector direction, vector up = "0 1 0")
	{
		vector mat[4];
		Math3D.DirectionAndUpMatrix(direction, up, mat);
		m_Orientation = Math3D.MatrixToAngles(mat);
		Math3D.MatrixToQuat(mat, m_Rotation);

		SetRotationDerived(false);
	}
	
	void SetOrientation(vector orientation)
	{
		m_Orientation = orientation;
		
		vector mat[3];
		m_Orientation.RotationMatrixFromAngles(mat);
		Math3D.MatrixToQuat(mat, m_Rotation);

		SetRotationDerived(false);
	}
	
	vector GetOrientation()
	{
		return m_Orientation;
	}

	void SetType(CF_SplinePointType type, bool imd = true)
	{
		m_Type = type;

		if (imd && m_Spline) m_Spline._Update();
	}

	CF_SplinePointType GetType()
	{
		return m_Type;
	}

	void SetRotationDerived(bool derived)
	{
		m_DerivedRotation = derived;
	}

	bool IsRotationDerived()
	{
		return m_DerivedRotation;
	}

	void SetSpeedCoef(float speedCoef)
	{
		m_SpeedCoef = speedCoef;
		if (m_SpeedCoef <= 0.0) m_SpeedCoef = 1.0;
	}

	float GetSpeedCoef()
	{
		return m_SpeedCoef;
	}

	float GetLength()
	{
		return m_Length;
	}

	float GetStart()
	{
		return m_Start;
	}

	float GetEnd()
	{
		return m_Start + m_Length;
	}

	void Get(float delta, out vector position, out vector orientation)
	{
		position = m_Position;
		orientation = m_Orientation;
		
		switch (m_Next.m_Type)
		{
			case CF_SplinePointType.LINEAR:
				LinInterp(delta, position, orientation);
				break;
			case CF_SplinePointType.CUBIC:
			case CF_SplinePointType.CUBIC_USER:
				CubicInterp(delta, position, orientation);
				break;
		}
	}

	void LinInterp(float delta, out vector position, out vector orientation)
	{
		if (!m_Next) return;
		
		position = vector.Lerp(m_Position, m_Next.m_Position, delta);

		float rot[4];
		Math3D.QuatLerp(rot, m_Rotation, m_Next.m_Rotation, delta);
		orientation = Math3D.QuatToAngles(rot);
	}

	void CubicInterp(float delta, out vector position, out vector orientation)
	{	
		if (!m_Next) return;
		
		float diff = GetLength();
		if (m_Prev) diff = GetStart() - m_Prev.GetStart();
		
		position = CF_Math.CubicInterp(m_Position, m_Next.m_Position, m_Tangent * diff, m_Next.m_Tangent * diff, delta);

		float rotation[4];
		Math3D.QuatLerp(rotation, m_Rotation, m_Next.m_Rotation, delta);
		orientation = Math3D.QuatToAngles(rotation);
	}

	void Update()
	{
		m_Length = 0;
		if (m_Next) m_Length = vector.Distance(m_Position, m_Next.GetPosition());
		
		m_Start = 0;
		if (m_Prev) m_Start = m_Prev.GetEnd();

		CalculateTangent(false);

		if (m_DerivedRotation && m_Next)
		{
			float diff = GetStart();
			if (m_Prev) diff = GetStart() - m_Prev.GetStart();

			vector startPosition = CF_Math.CubicInterp(m_Position, m_Next.m_Position, m_Tangent * diff, m_Next.m_Tangent * diff, 0);
			vector endPosition = CF_Math.CubicInterp(m_Position, m_Next.m_Position, m_Tangent * diff, m_Next.m_Tangent * diff, 1.0 / m_Length);

			vector mat[3];
			vector direction = vector.Direction(startPosition, endPosition).Normalized();
			Math3D.DirectionAndUpMatrix(direction, "0 1 0", mat);
			Math3D.MatrixToQuat(mat, m_Rotation);
		}
	}
	
	CF_SplinePoint GetNext()
	{
		return m_Next;
	}

	void SetNext(CF_SplinePoint point)
	{
		m_Next = point;
	}
	
	CF_SplinePoint GetPrevious()
	{
		return m_Prev;
	}

	void SetPrevious(CF_SplinePoint point)
	{
		m_Prev = point;
	}
};
