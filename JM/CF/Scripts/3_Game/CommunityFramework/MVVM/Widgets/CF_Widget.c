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

	reference string Name;
	reference string Visible;
	reference string Enabled;
	reference string Flags;
	reference string Sort;
	reference string PositionX;
	reference string PositionY;
	reference string Width;
	reference string Height;
	reference string Color;
	reference string Roll;
	reference string Pitch;
	reference string Yaw;
	reference string Alpha;

	private Widget _Widget;
	private bool _Enabled;
	private float _Roll;
	private float _Pitch;
	private float _Yaw;

	override void GetProperties()
	{
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
		AddProperty(Color, "Color");
		AddProperty(Roll, "Roll");
		AddProperty(Pitch, "Pitch");
		AddProperty(Yaw, "Yaw");
		AddProperty(Alpha, "Alpha");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_Widget, w);
	}

	void OnView_Name(Class model)
	{
		string _name = _Widget.GetName();
		EnScript.SetClassVar(model, Name, 0, _name);
	}

	void OnModel_Name(Class model)
	{
		string _name;
		EnScript.GetClassVar(model, Name, 0, _name);
		_Widget.SetName(_name);
	}

	void OnView_Visible(Class model)
	{
		bool _visible = _Widget.IsVisible();
		EnScript.SetClassVar(model, Visible, 0, _visible);
	}

	void OnModel_Visible(Class model)
	{
		bool _visible;
		EnScript.GetClassVar(model, Visible, 0, _visible);
		_Widget.Show(_visible);
	}

	void OnView_Enabled(Class model)
	{
		EnScript.SetClassVar(model, Enabled, 0, _Enabled);
	}

	void OnModel_Enabled(Class model)
	{
		EnScript.GetClassVar(model, Enabled, 0, _Enabled);
		_Widget.Enable(_Enabled);
	}

	void OnView_Flags(Class model)
	{
		int _flags = _Widget.GetFlags();
		EnScript.SetClassVar(model, Flags, 0, _flags);
	}

	void OnModel_Flags(Class model)
	{
		int _flags;
		EnScript.GetClassVar(model, Flags, 0, _flags);
		_Widget.SetFlags(_flags);
	}

	void OnView_Sort(Class model)
	{
		int _sort = _Widget.GetSort();
		EnScript.SetClassVar(model, Sort, 0, _sort);
	}

	void OnModel_Sort(Class model)
	{
		int _sort;
		EnScript.GetClassVar(model, Sort, 0, _sort);
		_Widget.SetSort(_sort);
	}

	void OnView_PositionX(Class model)
	{
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);
		EnScript.SetClassVar(model, PositionX, 0, _positionX);
	}

	void OnModel_PositionX(Class model)
	{
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);
		EnScript.GetClassVar(model, PositionX, 0, _positionX);
		_Widget.SetPos(_positionX, _positionY);
	}

	void OnView_PositionY(Class model)
	{
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);
		EnScript.SetClassVar(model, PositionY, 0, _positionY);
	}

	void OnModel_PositionY(Class model)
	{
		float _positionX;
		float _positionY;
		_Widget.GetPos(_positionX, _positionY);
		EnScript.GetClassVar(model, PositionY, 0, _positionY);
		_Widget.SetPos(_positionX, _positionY);
	}

	void OnView_Width(Class model)
	{
		float _width;
		float _height;
		_Widget.GetPos(_width, _height);
		EnScript.SetClassVar(model, Width, 0, _width);
	}

	void OnModel_Width(Class model)
	{
		float _width;
		float _height;
		_Widget.GetPos(_width, _height);
		EnScript.GetClassVar(model, Width, 0, _width);
		_Widget.SetPos(_width, _height);
	}

	void OnView_Height(Class model)
	{
		float _width;
		float _height;
		_Widget.GetPos(_width, _height);
		EnScript.SetClassVar(model, Height, 0, _height);
	}

	void OnModel_Height(Class model)
	{
		float _width;
		float _height;
		_Widget.GetPos(_width, _height);
		EnScript.GetClassVar(model, Height, 0, _height);
		_Widget.SetPos(_width, _height);
	}

	void OnView_Color(Class model)
	{
		int _color = _Widget.GetColor();
		EnScript.SetClassVar(model, Color, 0, _color);
	}

	void OnModel_Color(Class model)
	{
		int _color;
		EnScript.GetClassVar(model, Color, 0, _color);
		_Widget.SetColor(_color);
	}

	void OnView_Roll(Class model)
	{
		EnScript.SetClassVar(model, Roll, 0, _Roll);
	}

	void OnModel_Roll(Class model)
	{
		EnScript.GetClassVar(model, Roll, 0, _Roll);
		_Widget.SetRotation(_Roll, _Pitch, _Yaw);
	}

	void OnView_Pitch(Class model)
	{
		EnScript.SetClassVar(model, Pitch, 0, _Pitch);
	}

	void OnModel_Pitch(Class model)
	{
		EnScript.GetClassVar(model, Pitch, 0, _Pitch);
		_Widget.SetRotation(_Roll, _Pitch, _Yaw);
	}

	void OnView_Yaw(Class model)
	{
		EnScript.SetClassVar(model, Yaw, 0, _Yaw);
	}

	void OnModel_Yaw(Class model)
	{
		EnScript.GetClassVar(model, Yaw, 0, _Yaw);
		_Widget.SetRotation(_Roll, _Pitch, _Yaw);
	}
	
	void OnView_Alpha(Class model)
	{
		int _alpha = _Widget.GetAlpha();
		EnScript.SetClassVar(model, Alpha, 0, _alpha);
	}

	void OnModel_Alpha(Class model)
	{
		int _alpha;
		EnScript.GetClassVar(model, Alpha, 0, _alpha);
		_Widget.SetAlpha(_alpha);
	}
};
