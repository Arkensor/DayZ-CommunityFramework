class CF_Spline : Managed /*CF_ObservableCollection*/
{
	autoptr ScriptInvoker Update = new ScriptInvoker();
	
	private ref CF_SplinePoint m_Head;
	private ref CF_SplinePoint m_Tail;

	private CF_SplinePoint m_Current;
	private float m_Time;
	private float m_MaxTime;

	private vector m_Position;
	private vector m_Orientation;

	private float m_Tension;
	
	void CF_Spline()
	{
		SetTension(0.0);
	}

	void Tick(float dt)
	{
		SetTime(m_Time);

		if (!m_Current) return;

		m_Time += dt * m_Current.GetSpeedCoef();

		float delta = m_Time - m_Current.GetStart();
		float length = m_Current.GetLength();
		if (length <= 0.0) return;

		m_Current.Get(delta / length, m_Position, m_Orientation);

		if (m_Time > m_MaxTime) m_Time = m_MaxTime;
	}

	vector GetPosition()
	{
		return m_Position;
	}

	vector GetOrientation()
	{
		return m_Orientation;
	}

	CF_SplinePoint GetCurrent()
	{
		return m_Current;
	}

	void SetCurrent(CF_SplinePoint current)
	{
		if (current.GetSpline() != this) return;

		m_Current = current;
	}

	void SetTime(float time)
	{
		m_Time = time;

		if (m_MaxTime <= 0.0)
		{
			m_Time = 0.0;
			m_Current = null;
			return;
		}

		if (!m_Current || m_Current.GetStart() > m_Time) m_Current = m_Head;

		CF_SplinePoint next = m_Current.GetNext();
		while (next != null)
		{
			if (next.GetStart() > m_Time) return;

			m_Current = next;
			next = next.GetNext();
		}

		m_Current = m_Tail;
	}

	float GetTime()
	{
		return m_Time;
	}

	float GetMaxTime()
	{
		return m_MaxTime;
	}

	bool Completed()
	{
		return m_Time >= m_MaxTime;
	}

	/**
	 * Updates the tension of the spline
	 */
	void SetTension(float tension, bool imd = true)
	{
		m_Tension = tension;

		if (m_Tension < 0.0) m_Tension = 0.0;
		if (m_Tension > 1.0) m_Tension = 1.0;

		if (imd) _Update();
	}

	float GetTension()
	{
		return m_Tension;
	}

	/**
	 * Internal update function
	 */
	void _Update()
	{		
		CF_SplinePoint next = m_Head;
		while (next != null)
		{
			next.Update();
			next = next.GetNext();
		}

		m_MaxTime = 0;
		if (m_Tail) m_MaxTime = m_Tail.GetEnd();

		Update.Invoke();
	}

	/**
	 * Get the head of the spline
	 */
	CF_SplinePoint GetHead()
	{
		return m_Head;
	}

	/**
	 * Get the tail end of the spline
	 */
	CF_SplinePoint GetTail()
	{
		return m_Tail;
	}

	/**
	 * Inserts a point at the end of the spline
	 * 
	 * @param imd Updates the spline immediately
	 */
	CF_SplinePoint Insert(CF_SplinePoint _this, bool imd = true)
	{
		_this.SetSpline(this);
		
		if (!m_Tail)
		{
			m_Head = _this;
			m_Tail = _this;
		}
		else
		{
			_this.SetNext(null);
			_this.SetPrevious(m_Tail);
			
			m_Tail.SetNext(_this);
			m_Tail = _this;
		}

		if (imd) _Update();

		return _this;
	}

	/**
	 * Inserts a point on to the spline at the index
	 * 
	 * @param imd Updates the spline immediately
	 */
	CF_SplinePoint InsertAt(CF_SplinePoint _this, int index, bool imd = true)
	{
		_this.SetSpline(this);

		CF_SplinePoint previous = m_Head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous.GetNext();
		}

		if (!previous)
		{
			_this.SetPrevious(null);
			_this.SetNext(m_Head);
			m_Head.SetPrevious(_this);
			m_Head = _this;
		}
		else if (!previous.GetNext())
		{
			_this.SetNext(null);
			_this.SetPrevious(m_Tail);
			m_Tail.SetNext(_this);
			m_Tail = _this;
		}
		else
		{
			_this.SetPrevious(previous);
			_this.SetNext(previous.GetNext());
			_this.GetNext().SetPrevious(_this);
			_this.GetPrevious().SetNext(_this);
		}

		if (imd) _Update();

		return _this;
	}

	/**
	 * Remove a point from the spline, by index
	 * 
	 * @param imd Updates the spline immediately
	 */
	CF_SplinePoint Remove(int index, bool imd = true)
	{
		CF_SplinePoint _this = m_Head;
		for (int i = 0; i < index; i++)
		{
			_this = _this.GetNext();
		}

		CF_SplinePoint next = _this.GetNext();
		CF_SplinePoint prev = _this.GetPrevious();
		
		if (next)
		{
			next.SetPrevious(prev);
		}
		else
		{
			m_Tail = prev;
		}

		if (prev)
		{
			prev.SetNext(next);
		}
		else
		{
			m_Head = next;
		}

		_this.SetPrevious(null);
		_this.SetNext(null);

		if (imd) _Update();

		return _this;
	}
};
