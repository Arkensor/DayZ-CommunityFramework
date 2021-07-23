/**
 * Base class for widget properties
 */

class CF_Widget : CF_ViewModel
{
	reference string Name;
	reference string Visible;
	reference string Enabled;
	reference string Flags;
	reference string Sort;
	reference string PositionX;
	reference string PositionY;
	reference string Width;
	reference string Height;
	reference string ScreenPositionX;
	reference string ScreenPositionY;
	reference string ScreenWidth;
	reference string ScreenHeight;
	reference string Color;
	reference string Roll;
	reference string Pitch;
	reference string Yaw;
	reference string Alpha;

	protected Widget _Widget;
	protected CF_TypeConverter _Name;
	protected CF_TypeConverter _Visible;
	protected CF_TypeConverter _Enabled;
	protected CF_TypeConverter _Flags;
	protected CF_TypeConverter _Sort;
	protected CF_TypeConverter _PositionX;
	protected CF_TypeConverter _PositionY;
	protected CF_TypeConverter _Width;
	protected CF_TypeConverter _Height;
	protected CF_TypeConverter _ScreenPositionX;
	protected CF_TypeConverter _ScreenPositionY;
	protected CF_TypeConverter _ScreenWidth;
	protected CF_TypeConverter _ScreenHeight;
	protected CF_TypeConverter _Color;
	protected CF_TypeConverter _Roll;
	protected CF_TypeConverter _Pitch;
	protected CF_TypeConverter _Yaw;
	protected CF_TypeConverter _Alpha;

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

	void OnView_Name(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Name", "" + sender, args.ToStr());

		string _name = _Widget.GetName();
		EnScript.SetClassVar(m_Model, Name, 0, _name);
	}

	void OnModel_Name(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Name", "" + sender, args.ToStr());

		string _name;
		EnScript.GetClassVar(m_Model, Name, 0, _name);
		_Widget.SetName(_name);
	}

	void OnView_Visible(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Visible", "" + sender, args.ToStr());

		bool _visible = _Widget.IsVisible();
		EnScript.SetClassVar(m_Model, Visible, 0, _visible);
	}

	void OnModel_Visible(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Visible", "" + sender, args.ToStr());

		bool _visible;
		EnScript.GetClassVar(m_Model, Visible, 0, _visible);
		_Widget.Show(_visible);
	}

	void OnView_Enabled(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Enabled", "" + sender, args.ToStr());
		
		EnScript.SetClassVar(m_Model, Enabled, 0, _Enabled);
	}

	void OnModel_Enabled(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Enabled", "" + sender, args.ToStr());
		
		EnScript.GetClassVar(m_Model, Enabled, 0, _Enabled);
	//	_Widget.Enable(_Enabled);
	}

	void OnView_Flags(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Flags", "" + sender, args.ToStr());
		
		int _flags = _Widget.GetFlags();
		EnScript.SetClassVar(m_Model, Flags, 0, _flags);
	}

	void OnModel_Flags(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Flags", "" + sender, args.ToStr());
		
		int _flags;
		EnScript.GetClassVar(m_Model, Flags, 0, _flags);
		_Widget.ClearFlags(_Widget.GetFlags(), false);
		_Widget.SetFlags(_flags);
	}

	void OnView_Sort(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Sort", "" + sender, args.ToStr());
		
		int _sort = _Widget.GetSort();
		EnScript.SetClassVar(m_Model, Sort, 0, _sort);
	}

	void OnModel_Sort(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Sort", "" + sender, args.ToStr());
		
		int _sort;
		EnScript.GetClassVar(m_Model, Sort, 0, _sort);
		_Widget.SetSort(_sort);
	}

	void OnView_PositionX(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_PositionX", "" + sender, args.ToStr());
		
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);
		EnScript.SetClassVar(m_Model, PositionX, 0, _positionX);
	}

	void OnModel_PositionX(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_PositionX", "" + sender, args.ToStr());
		
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);
		EnScript.GetClassVar(m_Model, PositionX, 0, _positionX);
		_Widget.SetPos(_positionX, _positionY);
	}

	void OnView_PositionY(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_PositionY", "" + sender, args.ToStr());
		
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);
		EnScript.SetClassVar(m_Model, PositionY, 0, _positionY);
	}

	void OnModel_PositionY(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_PositionY", "" + sender, args.ToStr());
		
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);
		EnScript.GetClassVar(m_Model, PositionY, 0, _positionY);
		_Widget.SetPos(_positionX, _positionY);
	}

	void OnView_Width(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Width", "" + sender, args.ToStr());
		
		float _width;
		float _height;
		_Widget.GetSize(_width, _height);
		EnScript.SetClassVar(m_Model, Width, 0, _width);
	}

	void OnModel_Width(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Width", "" + sender, args.ToStr());
		
		float _width;
		float _height;
		_Widget.GetSize(_width, _height);
		EnScript.GetClassVar(m_Model, Width, 0, _width);
		_Widget.SetSize(_width, _height);
	}

	void OnView_Height(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Height", "" + sender, args.ToStr());
		
		float _width;
		float _height;
		_Widget.GetSize(_width, _height);
		EnScript.SetClassVar(m_Model, Height, 0, _height);
	}

	void OnModel_Height(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Height", "" + sender, args.ToStr());
		
		float _width;
		float _height;
		_Widget.GetSize(_width, _height);
		EnScript.GetClassVar(m_Model, Height, 0, _height);
		_Widget.SetSize(_width, _height);
	}
	
	void OnView_ScreenPositionX(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_ScreenPositionX", "" + sender, args.ToStr());
		
		float _positionX;
		float _positionY;
		_Widget.GetScreenPos(_positionX, _positionY);
		EnScript.SetClassVar(m_Model, ScreenPositionX, 0, _positionX);
	}

	void OnModel_ScreenPositionX(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_ScreenPositionX", "" + sender, args.ToStr());
		
		float _positionX;
		float _positionY;
		_Widget.GetScreenPos(_positionX, _positionY);
		EnScript.GetClassVar(m_Model, PositionX, 0, _positionX);

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

	void OnView_ScreenPositionY(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_ScreenPositionY", "" + sender, args.ToStr());
		
		float _positionX;
		float _positionY;
		_Widget.GetScreenPos(_positionX, _positionY);
		EnScript.SetClassVar(m_Model, ScreenPositionY, 0, _positionY);
	}

	void OnModel_ScreenPositionY(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_ScreenPositionY", "" + sender, args.ToStr());
		
		float _positionX;
		float _positionY;
		_Widget.GetScreenPos(_positionX, _positionY);
		EnScript.GetClassVar(m_Model, PositionY, 0, _positionY);

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

	void OnView_ScreenWidth(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_ScreenWidth", "" + sender, args.ToStr());
		
		float _width;
		float _height;
		_Widget.GetScreenSize(_width, _height);
		EnScript.SetClassVar(m_Model, ScreenWidth, 0, _width);
	}

	void OnModel_ScreenWidth(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_ScreenWidth", "" + sender, args.ToStr());
		
		OnView_ScreenWidth(m_Model, args);
	}

	void OnView_ScreenHeight(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_ScreenHeight", "" + sender, args.ToStr());
		
		float _width;
		float _height;
		_Widget.GetScreenSize(_width, _height);
		EnScript.SetClassVar(m_Model, ScreenHeight, 0, _height);
	}

	void OnModel_ScreenHeight(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_ScreenHeight", "" + sender, args.ToStr());
		
		OnView_ScreenHeight(m_Model, args);
	}

	void OnView_Color(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Color", "" + sender, args.ToStr());
		
		int _color = _Widget.GetColor();
		EnScript.SetClassVar(m_Model, Color, 0, _color);
	}

	void OnModel_Color(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Color", "" + sender, args.ToStr());
		
		int _color;
		EnScript.GetClassVar(m_Model, Color, 0, _color);
		_Widget.SetColor(_color);
	}

	void OnView_Roll(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Roll", "" + sender, args.ToStr());
		
		EnScript.SetClassVar(m_Model, Roll, 0, _Roll);
	}

	void OnModel_Roll(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Roll", "" + sender, args.ToStr());
		
		EnScript.GetClassVar(m_Model, Roll, 0, _Roll);
		//_Widget.SetRotation(_Roll, _Pitch, _Yaw);
	}

	void OnView_Pitch(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Pitch", "" + sender, args.ToStr());
		
		EnScript.SetClassVar(m_Model, Pitch, 0, _Pitch);
	}

	void OnModel_Pitch(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Pitch", "" + sender, args.ToStr());
		
		EnScript.GetClassVar(m_Model, Pitch, 0, _Pitch);
		//_Widget.SetRotation(_Roll, _Pitch, _Yaw);
	}

	void OnView_Yaw(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Yaw", "" + sender, args.ToStr());
		
		EnScript.SetClassVar(m_Model, Yaw, 0, _Yaw);
	}

	void OnModel_Yaw(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Yaw", "" + sender, args.ToStr());
		
		EnScript.GetClassVar(m_Model, Yaw, 0, _Yaw);
		//_Widget.SetRotation(_Roll, _Pitch, _Yaw);
	}
	
	void OnView_Alpha(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Alpha", "" + sender, args.ToStr());
		
		int _alpha = _Widget.GetAlpha();
		EnScript.SetClassVar(m_Model, Alpha, 0, _alpha);
	}

	void OnModel_Alpha(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Alpha", "" + sender, args.ToStr());
		
		int _alpha;
		EnScript.GetClassVar(m_Model, Alpha, 0, _alpha);
		_Widget.SetAlpha(_alpha);
	}

	override bool OnResize(Class sender, CF_ResizeEventArgs args)
	{
		CF_Trace trace(this, "OnResize", args.ToStr());
		
		NotifyPropertyChanged("Width");
		NotifyPropertyChanged("Height");

		NotifyPropertyChanged("ScreenWidth");
		NotifyPropertyChanged("ScreenHeight");

		return super.OnResize(sender, args);
	}

	override bool OnUpdate(Class sender, CF_ViewEventArgs args)
	{
		CF_Trace trace(this, "OnUpdate", args.ToStr());
		
		NotifyPropertyChanged("PositionX");
		NotifyPropertyChanged("PositionY");
		
		NotifyPropertyChanged("ScreenPositionX");
		NotifyPropertyChanged("ScreenPositionY");

		if (_Visible != _Widget.IsVisible())
		{
			//_Visible = _Widget.IsVisible();
			
			//if (_Visible) m_ViewModel.OnShow(m_Widget);
			//else m_ViewModel.OnHide(m_Widget);
		}

		//return super.OnUpdate(sender, args);
		return true;
	}
};
