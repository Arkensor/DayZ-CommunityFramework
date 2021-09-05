/**
 * Base class for widget properties
 */

class CF_Widget : CF_ViewModel
{
	reference string Name;				// [R/W]
	reference string Visible;			// [R/W]
	reference string Enabled;			// [R/W]
	reference string Flags;				// [R/W]
	reference string Sort;				// [R/W]
	reference string Position;			// [R/W]
	reference string PositionX;			// [R/W]
	reference string PositionY;			// [R/W]
	reference string Size;				// [R/W]
	reference string Width;				// [R/W]
	reference string Height;			// [R/W]
	reference string ScreenPositionX;	// [R/W]
	reference string ScreenPositionY;	// [R/W]
	reference string ScreenWidth;		// [R]
	reference string ScreenHeight;		// [R]
	reference string Color;				// [R/W]
	reference string Roll;				// [R/W]
	reference string Pitch;				// [R/W]
	reference string Yaw;				// [R/W]
	reference string Alpha;				// [R/W]

	protected Widget _Widget;
	protected CF_MVVM_PropertyBase _Name = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Visible = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Enabled = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Flags = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Sort = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Position = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _PositionX = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _PositionY = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Size = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Width = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Height = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _ScreenPositionX = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _ScreenPositionY = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _ScreenWidth = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _ScreenHeight = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Color = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Roll = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Pitch = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Yaw = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Alpha = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetProperties");
		#endif

		super.GetProperties();
		
		AddProperty(Name, "Name");
		AddProperty(Visible, "Visible");
		AddProperty(Enabled, "Enabled");
		AddProperty(Flags, "Flags");
		AddProperty(Sort, "Sort");
		AddProperty(PositionX, "PositionX");
		AddProperty(PositionY, "PositionY");
		AddProperty(Width, "Width");
		AddProperty(Height, "Height");
		AddProperty(ScreenPositionX, "ScreenPositionX");
		AddProperty(ScreenPositionY, "ScreenPositionY");
		AddProperty(ScreenWidth, "ScreenWidth");
		AddProperty(ScreenHeight, "ScreenHeight");
		AddProperty(Color, "Color");
		AddProperty(Roll, "Roll");
		AddProperty(Pitch, "Pitch");
		AddProperty(Yaw, "Yaw");
		AddProperty(Alpha, "Alpha");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_Widget, w);
	}

	void OnView_Name(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Name").Add(sender).Add(args.GetDebugName());
		#endif

		_Name.SetString(_Widget.GetName());
	}

	void OnModel_Name(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Name").Add(sender).Add(args.GetDebugName());
		#endif

		_Widget.SetName(_Name.GetString());
	}

	void OnView_Visible(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Visible").Add(sender).Add(args.GetDebugName());
		#endif

		_Visible.SetBool(_Widget.IsVisible());
	}

	void OnModel_Visible(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Visible").Add(sender).Add(args.GetDebugName());
		#endif

		_Widget.Show(_Visible.GetBool());
	}

	void OnView_Enabled(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Enabled").Add(sender).Add(args.GetDebugName());
		#endif

		OnView_Enabled(sender, args);
	}

	void OnModel_Enabled(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Enabled").Add(sender).Add(args.GetDebugName());
		#endif
		
		_Widget.Enable(_Enabled.GetBool());
	}

	void OnView_Flags(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Flags").Add(sender).Add(args.GetDebugName());
		#endif

		_Flags.SetInt(_Widget.GetFlags());
	}

	void OnModel_Flags(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Flags").Add(sender).Add(args.GetDebugName());
		#endif
		
		_Widget.ClearFlags(_Widget.GetFlags(), false);
		_Widget.SetFlags(_Flags.GetInt());
	}

	void OnView_Sort(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Sort").Add(sender).Add(args.GetDebugName());
		#endif

		_Sort.SetInt(_Widget.GetSort());
	}

	void OnModel_Sort(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Sort").Add(sender).Add(args.GetDebugName());
		#endif
		
		_Widget.SetSort(_Sort.GetInt());
	}

	void OnView_Position(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Position").Add(sender).Add(args.GetDebugName());
		#endif
		
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);

		_Position.SetVector(Vector(_positionX, _positionY, 0));
	}

	void OnModel_Position(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Position").Add(sender).Add(args.GetDebugName());
		#endif
				
		vector position = _Position.GetVector();

		_Widget.SetPos(position[0], position[1]);
		
		NotifyPropertyChanged(PositionX, "PositionX");
		NotifyPropertyChanged(PositionY, "PositionY");
	}

	void OnView_PositionX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_PositionX").Add(sender).Add(args.GetDebugName());
		#endif

		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);

		_PositionX.SetFloat(_positionX);
	}

	void OnModel_PositionX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_PositionX").Add(sender).Add(args.GetDebugName());
		#endif
		
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);

		_Widget.SetPos(_PositionX.GetFloat(), _positionY);
	}

	void OnView_PositionY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_PositionY").Add(sender).Add(args.GetDebugName());
		#endif
		
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);

		_PositionY.SetFloat(_positionY);
	}

	void OnModel_PositionY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_PositionY").Add(sender).Add(args.GetDebugName());
		#endif
				
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);

		_Widget.SetPos(_positionX, _PositionY.GetFloat());
	}

	void OnView_Size(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Size").Add(sender).Add(args.GetDebugName());
		#endif
		
		float _width;
		float _height;
		_Widget.GetSize(_width, _height);

		_Size.SetVector(Vector(_width, _height, 0));
	}

	void OnModel_Size(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Size").Add(sender).Add(args.GetDebugName());
		#endif
				
		vector size = _Size.GetVector();

		_Widget.SetSize(size[0], size[1]);
		
		NotifyPropertyChanged(Width, "Width");
		NotifyPropertyChanged(Height, "Height");
	}

	void OnView_Width(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Width").Add(sender).Add(args.GetDebugName());
		#endif
		
		float _width;
		float _height;
		_Widget.GetSize(_width, _height);

		_Width.SetFloat(_width);
	}

	void OnModel_Width(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Width").Add(sender).Add(args.GetDebugName());
		#endif
				
		float _width;
		float _height;
		_Widget.GetSize(_width, _height);

		_Widget.SetSize(_Width.GetFloat(), _height);
	}

	void OnView_Height(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Height").Add(sender).Add(args.GetDebugName());
		#endif

		float _width;
		float _height;
		_Widget.GetSize(_width, _height);

		_Height.SetFloat(_height);
	}

	void OnModel_Height(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Height").Add(sender).Add(args.GetDebugName());
		#endif
		
		float _width;
		float _height;
		_Widget.GetSize(_width, _height);

		_Widget.SetSize(_width, _Height.GetFloat());
	}
	
	void OnView_ScreenPositionX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_ScreenPositionX").Add(sender).Add(args.GetDebugName());
		#endif
		
		float _positionX;
		float _positionY;
		_Widget.GetScreenPos(_positionX, _positionY);

		_ScreenPositionX.SetFloat(_positionX);
	}

	void OnModel_ScreenPositionX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_ScreenPositionX").Add(sender).Add(args.GetDebugName());
		#endif
		
		float _positionX;
		float _positionY;
		_Widget.GetScreenPos(_positionX, _positionY);
		_positionX = _PositionX.GetFloat();

		if ((_Widget.GetFlags() & WidgetFlags.HEXACTPOS) != 0)
		{
			float temp;

			float posAdd = 0;
			float posMul = 0;
			Widget parent = _Widget.GetParent();
			if (parent)
			{
				_Widget.GetScreenPos(posAdd, temp);
				_Widget.GetScreenSize(posMul, temp);

			}
			_positionX = posAdd + (posMul * _positionX);
		}

		_Widget.SetPos(_positionX, _positionY);
	}

	void OnView_ScreenPositionY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_ScreenPositionY").Add(sender).Add(args.GetDebugName());
		#endif

		float _positionX;
		float _positionY;
		_Widget.GetScreenPos(_positionX, _positionY);

		_ScreenPositionY.SetFloat(_positionY);
	}

	void OnModel_ScreenPositionY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_ScreenPositionY").Add(sender).Add(args.GetDebugName());
		#endif

		float _positionX;
		float _positionY;
		_Widget.GetScreenPos(_positionX, _positionY);
		_positionY = _PositionY.GetFloat();

		if ((_Widget.GetFlags() & WidgetFlags.VEXACTPOS) != 0)
		{
			float temp;

			float posAdd = 0;
			float posMul = 0;
			Widget parent = _Widget.GetParent();
			if (parent)
			{
				_Widget.GetScreenPos(temp, posAdd);
				_Widget.GetScreenSize(temp, posMul);

			}
			_positionY = posAdd + (posMul * _positionY);
		}

		_Widget.SetPos(_positionX, _positionY);
	}

	void OnView_ScreenWidth(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_ScreenWidth").Add(sender).Add(args.GetDebugName());
		#endif

		float _width;
		float _height;
		_Widget.GetScreenSize(_width, _height);

		_ScreenWidth.SetFloat(_width);
	}

	void OnModel_ScreenWidth(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_ScreenWidth").Add(sender).Add(args.GetDebugName());
		#endif
				
		OnView_ScreenWidth(m_Model, args);
	}

	void OnView_ScreenHeight(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_ScreenHeight").Add(sender).Add(args.GetDebugName());
		#endif

		float _width;
		float _height;
		_Widget.GetScreenSize(_width, _height);

		_ScreenHeight.SetFloat(_height);
	}

	void OnModel_ScreenHeight(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_ScreenHeight").Add(sender).Add(args.GetDebugName());
		#endif
				
		OnView_ScreenHeight(m_Model, args);
	}

	void OnView_Color(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Color").Add(sender).Add(args.GetDebugName());
		#endif

		_Color.SetInt(_Widget.GetColor());
	}

	void OnModel_Color(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Color").Add(sender).Add(args.GetDebugName());
		#endif
		
		_Widget.SetColor(_Color.GetInt());
	}

	void OnView_Roll(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Roll").Add(sender).Add(args.GetDebugName());
		#endif

		OnModel_Roll(sender, args);
	}

	void OnModel_Roll(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Roll").Add(sender).Add(args.GetDebugName());
		#endif
		
		_Widget.SetRotation(_Roll.GetFloat(), _Pitch.GetFloat(), _Yaw.GetFloat());
	}

	void OnView_Pitch(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Pitch").Add(sender).Add(args.GetDebugName());
		#endif

		OnModel_Pitch(sender, args);
	}

	void OnModel_Pitch(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Pitch").Add(sender).Add(args.GetDebugName());
		#endif
		
		_Widget.SetRotation(_Roll.GetFloat(), _Pitch.GetFloat(), _Yaw.GetFloat());
	}

	void OnView_Yaw(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Yaw").Add(sender).Add(args.GetDebugName());
		#endif

		OnModel_Yaw(sender, args);
	}

	void OnModel_Yaw(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Yaw").Add(sender).Add(args.GetDebugName());
		#endif
		
		_Widget.SetRotation(_Roll.GetFloat(), _Pitch.GetFloat(), _Yaw.GetFloat());
	}
	
	void OnView_Alpha(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Alpha").Add(sender).Add(args.GetDebugName());
		#endif

		_Alpha.SetInt(_Widget.GetAlpha());
	}

	void OnModel_Alpha(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Alpha").Add(sender).Add(args.GetDebugName());
		#endif
		
		_Widget.SetAlpha(_Alpha.GetInt());
	}

	override bool OnResize(CF_ModelBase sender, CF_ResizeEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnResize").Add(sender).Add(args.GetDebugName());
		#endif
		
		//NotifyPropertyChanged(Size, "Size");
		
		//NotifyPropertyChanged(Width, "Width");
		//NotifyPropertyChanged(Height, "Height");

		//NotifyPropertyChanged(ScreenWidth, "ScreenWidth");
		//NotifyPropertyChanged(ScreenHeight, "ScreenHeight");

		return super.OnResize(sender, args);
	}

	override bool OnUpdate(CF_ModelBase sender, CF_ViewEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnUpdate").Add(sender).Add(args.GetDebugName());
		#endif
		
		//NotifyPropertyChanged(Position, "Position");
		//NotifyPropertyChanged(PositionX, "PositionX");
		//NotifyPropertyChanged(PositionY, "PositionY");
		
		//NotifyPropertyChanged(ScreenPositionX, "ScreenPositionX");
		//NotifyPropertyChanged(ScreenPositionY, "ScreenPositionY");

		bool visible = _Widget.IsVisible();
		if (!_Visible.IsDefault() && _Visible.GetBool() != visible)
		{
			_Visible.SetBool(visible);
			
			if (visible) OnShow(m_Widget);
			else OnHide(m_Widget);
		}

		return super.OnUpdate(sender, args);
	}
};
