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
	reference string PositionX;			// [R/W]
	reference string PositionY;			// [R/W]
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
	protected ref CF_TypeConverter _Name = CF_GetDefaultTC();
	protected ref CF_TypeConverter _Visible = CF_GetDefaultTC();
	protected ref CF_TypeConverter _Enabled = CF_GetDefaultTC();
	protected ref CF_TypeConverter _Flags = CF_GetDefaultTC();
	protected ref CF_TypeConverter _Sort = CF_GetDefaultTC();
	protected ref CF_TypeConverter _PositionX = CF_GetDefaultTC();
	protected ref CF_TypeConverter _PositionY = CF_GetDefaultTC();
	protected ref CF_TypeConverter _Width = CF_GetDefaultTC();
	protected ref CF_TypeConverter _Height = CF_GetDefaultTC();
	protected ref CF_TypeConverter _ScreenPositionX = CF_GetDefaultTC();
	protected ref CF_TypeConverter _ScreenPositionY = CF_GetDefaultTC();
	protected ref CF_TypeConverter _ScreenWidth = CF_GetDefaultTC();
	protected ref CF_TypeConverter _ScreenHeight = CF_GetDefaultTC();
	protected ref CF_TypeConverter _Color = CF_GetDefaultTC();
	protected ref CF_TypeConverter _Roll = CF_GetDefaultTC();
	protected ref CF_TypeConverter _Pitch = CF_GetDefaultTC();
	protected ref CF_TypeConverter _Yaw = CF_GetDefaultTC();
	protected ref CF_TypeConverter _Alpha = CF_GetDefaultTC();

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

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
		AddProperty(PositionX, "ScreenPositionX");
		AddProperty(PositionY, "ScreenPositionY");
		AddProperty(Width, "ScreenWidth");
		AddProperty(Height, "ScreenHeight");
		AddProperty(Color, "Color");
		AddProperty(Roll, "Roll");
		AddProperty(Pitch, "Pitch");
		AddProperty(Yaw, "Yaw");
		AddProperty(Alpha, "Alpha");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_Widget, w);
	}

	void OnView_Name(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Name", "" + sender, args.ToStr());

		_Name.SetString(_Widget.GetName());
		_Name.ToVariable(m_Model, Name);
	}

	void OnModel_Name(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Name", "" + sender, args.ToStr());

		_Name.FromVariable(m_Model, Name);
		_Widget.SetName(_Name.GetString());
	}

	void OnView_Visible(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Visible", "" + sender, args.ToStr());

		_Visible.SetBool(_Widget.IsVisible());
		_Visible.ToVariable(m_Model, Visible);
	}

	void OnModel_Visible(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Visible", "" + sender, args.ToStr());

		_Visible.FromVariable(m_Model, Visible);
		_Widget.Show(_Visible.GetBool());
	}

	void OnView_Enabled(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Enabled", "" + sender, args.ToStr());

		OnView_Enabled(sender, args);
	}

	void OnModel_Enabled(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Enabled", "" + sender, args.ToStr());
		
		_Enabled.FromVariable(m_Model, Enabled);
		_Widget.Enable(_Enabled.GetBool());
	}

	void OnView_Flags(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Flags", "" + sender, args.ToStr());

		_Flags.SetInt(_Widget.GetFlags());
		_Flags.ToVariable(m_Model, Flags);
	}

	void OnModel_Flags(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Flags", "" + sender, args.ToStr());
		
		_Flags.FromVariable(m_Model, Name);
		_Widget.ClearFlags(_Widget.GetFlags(), false);
		_Widget.SetFlags(_Flags.GetInt());
	}

	void OnView_Sort(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Sort", "" + sender, args.ToStr());

		_Sort.SetInt(_Widget.GetSort());
		_Sort.ToVariable(m_Model, Sort);
	}

	void OnModel_Sort(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Sort", "" + sender, args.ToStr());
		
		_Sort.FromVariable(m_Model, Sort);
		_Widget.SetSort(_Sort.GetInt());
	}

	void OnView_PositionX(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_PositionX", "" + sender, args.ToStr());

		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);

		_PositionX.SetFloat(_positionX);
		_PositionX.ToVariable(m_Model, PositionX);
	}

	void OnModel_PositionX(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_PositionX", "" + sender, args.ToStr());
		
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);

		_PositionX.FromVariable(m_Model, PositionX);
		_Widget.SetPos(_PositionX.GetFloat(), _positionY);
	}

	void OnView_PositionY(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_PositionY", "" + sender, args.ToStr());
		
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);

		_PositionY.SetFloat(_positionY);
		_PositionY.ToVariable(m_Model, PositionY);
	}

	void OnModel_PositionY(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_PositionY", "" + sender, args.ToStr());
				
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);

		_PositionY.FromVariable(m_Model, PositionY);
		_Widget.SetPos(_positionX, _PositionY.GetFloat());
	}

	void OnView_Width(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Width", "" + sender, args.ToStr());
		
		float _width;
		float _height;
		_Widget.GetSize(_width, _height);

		_Width.SetFloat(_width);
		_Width.ToVariable(m_Model, Width);
	}

	void OnModel_Width(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Width", "" + sender, args.ToStr());
				
		float _width;
		float _height;
		_Widget.GetSize(_width, _height);

		_Width.FromVariable(m_Model, Width);
		_Widget.SetSize(_Width.GetFloat(), _height);
	}

	void OnView_Height(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Height", "" + sender, args.ToStr());

		float _width;
		float _height;
		_Widget.GetSize(_width, _height);

		_Height.SetFloat(_height);
		_Height.ToVariable(m_Model, Height);
	}

	void OnModel_Height(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Height", "" + sender, args.ToStr());
		
		float _width;
		float _height;
		_Widget.GetSize(_width, _height);

		_Height.FromVariable(m_Model, Height);
		_Widget.SetSize(_width, _Height.GetFloat());
	}
	
	void OnView_ScreenPositionX(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_ScreenPositionX", "" + sender, args.ToStr());
		
		float _positionX;
		float _positionY;
		_Widget.GetScreenPos(_positionX, _positionY);

		_ScreenPositionX.SetFloat(_positionX);
		_ScreenPositionX.ToVariable(m_Model, ScreenPositionX);
	}

	void OnModel_ScreenPositionX(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_ScreenPositionX", "" + sender, args.ToStr());
		
		float _positionX;
		float _positionY;
		_Widget.GetScreenPos(_positionX, _positionY);
		_PositionX.FromVariable(m_Model, PositionX);
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
		CF_Trace trace(this, "OnView_ScreenPositionY", "" + sender, args.ToStr());

		float _positionX;
		float _positionY;
		_Widget.GetScreenPos(_positionX, _positionY);

		_ScreenPositionY.SetFloat(_positionY);
		_ScreenPositionY.ToVariable(m_Model, ScreenPositionY);
	}

	void OnModel_ScreenPositionY(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_ScreenPositionY", "" + sender, args.ToStr());

		float _positionX;
		float _positionY;
		_Widget.GetScreenPos(_positionX, _positionY);
		_PositionY.FromVariable(m_Model, PositionY);
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
		CF_Trace trace(this, "OnView_ScreenWidth", "" + sender, args.ToStr());

		float _width;
		float _height;
		_Widget.GetScreenSize(_width, _height);

		_ScreenWidth.SetFloat(_width);
		_ScreenWidth.ToVariable(m_Model, ScreenWidth);
	}

	void OnModel_ScreenWidth(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_ScreenWidth", "" + sender, args.ToStr());
				
		OnView_ScreenWidth(m_Model, args);
	}

	void OnView_ScreenHeight(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_ScreenHeight", "" + sender, args.ToStr());

		float _width;
		float _height;
		_Widget.GetScreenSize(_width, _height);

		_ScreenHeight.SetFloat(_height);
		_ScreenHeight.ToVariable(m_Model, ScreenHeight);
	}

	void OnModel_ScreenHeight(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_ScreenHeight", "" + sender, args.ToStr());
				
		OnView_ScreenHeight(m_Model, args);
	}

	void OnView_Color(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Color", "" + sender, args.ToStr());

		_Color.SetInt(_Widget.GetColor());
		_Color.ToVariable(m_Model, Color);
	}

	void OnModel_Color(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Color", "" + sender, args.ToStr());
		
		_Color.FromVariable(m_Model, Color);
		_Widget.SetColor(_Color.GetInt());
	}

	void OnView_Roll(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Roll", "" + sender, args.ToStr());

		OnModel_Roll(sender, args);
	}

	void OnModel_Roll(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Roll", "" + sender, args.ToStr());
		
		_Roll.FromVariable(m_Model, Roll);
		_Widget.SetRotation(_Roll.GetFloat(), _Pitch.GetFloat(), _Yaw.GetFloat());
	}

	void OnView_Pitch(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Pitch", "" + sender, args.ToStr());

		OnModel_Pitch(sender, args);
	}

	void OnModel_Pitch(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Pitch", "" + sender, args.ToStr());
		
		_Pitch.FromVariable(m_Model, Pitch);
		_Widget.SetRotation(_Roll.GetFloat(), _Pitch.GetFloat(), _Yaw.GetFloat());
	}

	void OnView_Yaw(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Yaw", "" + sender, args.ToStr());

		OnModel_Yaw(sender, args);
	}

	void OnModel_Yaw(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Yaw", "" + sender, args.ToStr());
		
		_Yaw.FromVariable(m_Model, Yaw);
		_Widget.SetRotation(_Roll.GetFloat(), _Pitch.GetFloat(), _Yaw.GetFloat());
	}
	
	void OnView_Alpha(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Alpha", "" + sender, args.ToStr());

		_Alpha.SetInt(_Widget.GetAlpha());
		_Alpha.ToVariable(m_Model, Alpha);
	}

	void OnModel_Alpha(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Alpha", "" + sender, args.ToStr());
		
		_Alpha.FromVariable(m_Model, Alpha);
		_Widget.SetAlpha(_Alpha.GetInt());
	}

	override bool OnResize(CF_ModelBase sender, CF_ResizeEventArgs args)
	{
		CF_Trace trace(this, "OnResize", args.ToStr());
		
		NotifyPropertyChanged(Width, "Width");
		NotifyPropertyChanged(Height, "Height");

		NotifyPropertyChanged(ScreenWidth, "ScreenWidth");
		NotifyPropertyChanged(ScreenHeight, "ScreenHeight");

		return super.OnResize(sender, args);
	}

	override bool OnUpdate(CF_ModelBase sender, CF_ViewEventArgs args)
	{
		CF_Trace trace(this, "OnUpdate", args.ToStr());
		
		NotifyPropertyChanged(PositionX, "PositionX");
		NotifyPropertyChanged(PositionY, "PositionY");
		
		NotifyPropertyChanged(ScreenPositionX, "ScreenPositionX");
		NotifyPropertyChanged(ScreenPositionY, "ScreenPositionY");

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
