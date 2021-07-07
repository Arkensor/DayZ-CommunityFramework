/**
 * Base class for widget properties
 */

class CF_Widget : CF_MVVM_View
{
	reference string Event_Click;
	reference string Event_ModalResult;
	reference string Event_DoubleClick;
	reference string Event_Select;
	reference string Event_ItemSelected;
	reference string Event_Focus;
	reference string Event_FocusLost;
	reference string Event_MouseEnter;
	reference string Event_MouseLeave;
	reference string Event_MouseWheel;
	reference string Event_MouseButtonDown;
	reference string Event_MouseButtonUp;
	reference string Event_Controller;
	reference string Event_KeyDown;
	reference string Event_KeyUp;
	reference string Event_KeyPress;
	reference string Event_Change;
	reference string Event_Drag;
	reference string Event_Dragging;
	reference string Event_DraggingOver;
	reference string Event_Drop;
	reference string Event_DropReceived;
	reference string Event_Resize;
	reference string Event_ChildAdd;
	reference string Event_ChildRemove;
	reference string Event_Update;
	reference string Event_Show;
	reference string Event_Hide;
	reference string Event_Destroyed;

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

	void OnView_Name(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Name", "" + model, evt.String());

		string _name = _Widget.GetName();
		EnScript.SetClassVar(model, Name, 0, _name);
	}

	void OnModel_Name(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Name", "" + model, evt.String());

		string _name;
		EnScript.GetClassVar(model, Name, 0, _name);
		_Widget.SetName(_name);
	}

	void OnView_Visible(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Visible", "" + model, evt.String());

		bool _visible = _Widget.IsVisible();
		EnScript.SetClassVar(model, Visible, 0, _visible);
	}

	void OnModel_Visible(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Visible", "" + model, evt.String());

		bool _visible;
		EnScript.GetClassVar(model, Visible, 0, _visible);
		_Widget.Show(_visible);
	}

	void OnView_Enabled(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Enabled", "" + model, evt.String());
		
		EnScript.SetClassVar(model, Enabled, 0, _Enabled);
	}

	void OnModel_Enabled(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Enabled", "" + model, evt.String());
		
		EnScript.GetClassVar(model, Enabled, 0, _Enabled);
		_Widget.Enable(_Enabled);
	}

	void OnView_Flags(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Flags", "" + model, evt.String());
		
		int _flags = _Widget.GetFlags();
		EnScript.SetClassVar(model, Flags, 0, _flags);
	}

	void OnModel_Flags(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Flags", "" + model, evt.String());
		
		int _flags;
		EnScript.GetClassVar(model, Flags, 0, _flags);
		_Widget.ClearFlags(_Widget.GetFlags(), false);
		_Widget.SetFlags(_flags);
	}

	void OnView_Sort(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Sort", "" + model, evt.String());
		
		int _sort = _Widget.GetSort();
		EnScript.SetClassVar(model, Sort, 0, _sort);
	}

	void OnModel_Sort(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Sort", "" + model, evt.String());
		
		int _sort;
		EnScript.GetClassVar(model, Sort, 0, _sort);
		_Widget.SetSort(_sort);
	}

	void OnView_PositionX(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_PositionX", "" + model, evt.String());
		
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);
		EnScript.SetClassVar(model, PositionX, 0, _positionX);
	}

	void OnModel_PositionX(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_PositionX", "" + model, evt.String());
		
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);
		EnScript.GetClassVar(model, PositionX, 0, _positionX);
		_Widget.SetPos(_positionX, _positionY);
	}

	void OnView_PositionY(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_PositionY", "" + model, evt.String());
		
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);
		EnScript.SetClassVar(model, PositionY, 0, _positionY);
	}

	void OnModel_PositionY(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_PositionY", "" + model, evt.String());
		
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);
		EnScript.GetClassVar(model, PositionY, 0, _positionY);
		_Widget.SetPos(_positionX, _positionY);
	}

	void OnView_Width(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Width", "" + model, evt.String());
		
		float _width;
		float _height;
		_Widget.GetSize(_width, _height);
		EnScript.SetClassVar(model, Width, 0, _width);
	}

	void OnModel_Width(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Width", "" + model, evt.String());
		
		float _width;
		float _height;
		_Widget.GetSize(_width, _height);
		EnScript.GetClassVar(model, Width, 0, _width);
		_Widget.SetSize(_width, _height);
	}

	void OnView_Height(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Height", "" + model, evt.String());
		
		float _width;
		float _height;
		_Widget.GetSize(_width, _height);
		EnScript.SetClassVar(model, Height, 0, _height);
	}

	void OnModel_Height(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Height", "" + model, evt.String());
		
		float _width;
		float _height;
		_Widget.GetSize(_width, _height);
		EnScript.GetClassVar(model, Height, 0, _height);
		_Widget.SetSize(_width, _height);
	}
	
	void OnView_ScreenPositionX(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_ScreenPositionX", "" + model, evt.String());
		
		float _positionX;
		float _positionY;
		_Widget.GetScreenPos(_positionX, _positionY);
		EnScript.SetClassVar(model, ScreenPositionX, 0, _positionX);
	}

	void OnModel_ScreenPositionX(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_ScreenPositionX", "" + model, evt.String());
		
		float _positionX;
		float _positionY;
		_Widget.GetScreenPos(_positionX, _positionY);
		EnScript.GetClassVar(model, PositionX, 0, _positionX);

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

	void OnView_ScreenPositionY(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_ScreenPositionY", "" + model, evt.String());
		
		float _positionX;
		float _positionY;
		_Widget.GetScreenPos(_positionX, _positionY);
		EnScript.SetClassVar(model, ScreenPositionY, 0, _positionY);
	}

	void OnModel_ScreenPositionY(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_ScreenPositionY", "" + model, evt.String());
		
		float _positionX;
		float _positionY;
		_Widget.GetScreenPos(_positionX, _positionY);
		EnScript.GetClassVar(model, PositionY, 0, _positionY);

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

	void OnView_ScreenWidth(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_ScreenWidth", "" + model, evt.String());
		
		float _width;
		float _height;
		_Widget.GetScreenSize(_width, _height);
		EnScript.SetClassVar(model, ScreenWidth, 0, _width);
	}

	void OnModel_ScreenWidth(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_ScreenWidth", "" + model, evt.String());
		
		OnView_ScreenWidth(model, evt);
	}

	void OnView_ScreenHeight(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_ScreenHeight", "" + model, evt.String());
		
		float _width;
		float _height;
		_Widget.GetScreenSize(_width, _height);
		EnScript.SetClassVar(model, ScreenHeight, 0, _height);
	}

	void OnModel_ScreenHeight(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_ScreenHeight", "" + model, evt.String());
		
		OnView_ScreenHeight(model, evt);
	}

	void OnView_Color(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Color", "" + model, evt.String());
		
		int _color = _Widget.GetColor();
		EnScript.SetClassVar(model, Color, 0, _color);
	}

	void OnModel_Color(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Color", "" + model, evt.String());
		
		int _color;
		EnScript.GetClassVar(model, Color, 0, _color);
		_Widget.SetColor(_color);
	}

	void OnView_Roll(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Roll", "" + model, evt.String());
		
		EnScript.SetClassVar(model, Roll, 0, _Roll);
	}

	void OnModel_Roll(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Roll", "" + model, evt.String());
		
		EnScript.GetClassVar(model, Roll, 0, _Roll);
		_Widget.SetRotation(_Roll, _Pitch, _Yaw);
	}

	void OnView_Pitch(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Pitch", "" + model, evt.String());
		
		EnScript.SetClassVar(model, Pitch, 0, _Pitch);
	}

	void OnModel_Pitch(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Pitch", "" + model, evt.String());
		
		EnScript.GetClassVar(model, Pitch, 0, _Pitch);
		_Widget.SetRotation(_Roll, _Pitch, _Yaw);
	}

	void OnView_Yaw(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Yaw", "" + model, evt.String());
		
		EnScript.SetClassVar(model, Yaw, 0, _Yaw);
	}

	void OnModel_Yaw(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Yaw", "" + model, evt.String());
		
		EnScript.GetClassVar(model, Yaw, 0, _Yaw);
		_Widget.SetRotation(_Roll, _Pitch, _Yaw);
	}
	
	void OnView_Alpha(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Alpha", "" + model, evt.String());
		
		int _alpha = _Widget.GetAlpha();
		EnScript.SetClassVar(model, Alpha, 0, _alpha);
	}

	void OnModel_Alpha(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Alpha", "" + model, evt.String());
		
		int _alpha;
		EnScript.GetClassVar(model, Alpha, 0, _alpha);
		_Widget.SetAlpha(_alpha);
	}

	override bool OnResize(CF_ResizeEventArgs evt)
	{
		CF_Trace trace(this, "OnResize", evt.String());
		
		NotifyPropertyChanged("Width");
		NotifyPropertyChanged("Height");

		NotifyPropertyChanged("ScreenWidth");
		NotifyPropertyChanged("ScreenHeight");

		return super.OnResize(evt);
	}

	override bool OnUpdate(CF_ViewEventArgs evt)
	{
		CF_Trace trace(this, "OnUpdate", evt.String());
		
		NotifyPropertyChanged("PositionX");
		NotifyPropertyChanged("PositionY");
		
		NotifyPropertyChanged("ScreenPositionX");
		NotifyPropertyChanged("ScreenPositionY");

		if (_Visible != _Widget.IsVisible())
		{
			_Visible = _Widget.IsVisible();
			
			if (_Visible) m_ViewModel.OnShow(m_Widget);
			else m_ViewModel.OnHide(m_Widget);
		}

		return super.OnUpdate(evt);
	}
};
