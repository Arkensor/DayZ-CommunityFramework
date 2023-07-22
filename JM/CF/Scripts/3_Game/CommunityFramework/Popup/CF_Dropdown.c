class CF_DropdownBase : CF_Model
{
	override string GetLayoutFile()
	{
		return "";
	}

	string GetPopupLayoutFile()
	{
		return "";
	}

	string GetElementLayoutFile()
	{
		return "";
	}
};

class CF_Dropdown<Class T> : CF_DropdownBase
{
	ref CF_ObservableArray<ref T> m_Elements;

	ref CF_DropdownElement<T> m_Selected;

	autoptr CF_DropdownPopup<T> m_Popup;

	void CF_Dropdown(CF_ObservableArray<ref T> elements = null)
	{
		m_Elements = elements;
		if (!m_Elements)
		{
			m_Elements = new CF_ObservableArray<ref T>();
		}

		m_Selected = new CF_DropdownElement<T>();
		m_Selected.Init(null, this, GetElementLayoutFile());
	}

	void Insert(T item)
	{
		m_Elements.Insert(item);
	}

	void SetSelected(T selected)
	{
		m_Selected.m_Data = selected;

		if (m_Popup) m_Popup.SetSelected(m_Selected);
	}

	T GetSelected()
	{
		return m_Selected.m_Data;
	}
	
	void OnToggle(CF_ModelBase sender, CF_EventArgs args)
	{
		if (m_Popup) Close();
		else Open();
	}

	void Open()
	{
		if (m_Popup) return;

		m_Popup = new CF_DropdownPopup<T>();
		m_Popup.Init(this, GetPopupLayoutFile(), GetElementLayoutFile());
		m_Popup.OnDestroy.AddSubscriber(OnClose);
		NotifyPropertyChanged("m_Popup");
	}

	void Close()
	{
		if (!m_Popup) return;

		delete m_Popup;
	}

	void OnClose(Class sender, CF_EventArgs args)
	{
		m_Popup = null;
		NotifyPropertyChanged("m_Popup");
	}
};

class CF_DropdownElementBase : CF_Model
{
	void Init(Class data, CF_DropdownBase dropdown, string layoutFile);
		
	void SetSelected(bool selected);
};

class CF_DropdownElement<Class T> : CF_DropdownElementBase
{
	T m_Data;
	bool m_Selected;

	CF_Dropdown<T> m_Dropdown;

	string m_LayoutFile;

	override void Init(Class data, CF_DropdownBase dropdown, string layoutFile)
	{
		Class.CastTo(m_Dropdown, dropdown);
		Class.CastTo(m_Data, data);

		m_LayoutFile = layoutFile;
	}

	override string GetLayoutFile()
	{
		return m_LayoutFile;
	}

	void OnClick(CF_ModelBase sender, CF_EventArgs args)
	{
		m_Dropdown.SetSelected(m_Data);
	}

	override void SetSelected(bool selected)
	{
		m_Selected = selected;
		NotifyPropertyChanged("m_Selected");
	}
};

class CF_DropdownPopupBase : CF_Popup
{
	void Init(CF_DropdownBase dropdown, string popupLayoutFile, string elementLayoutFile);
	
	void SetSelected(Class selected);
};

class CF_DropdownPopup<Class T> : CF_DropdownPopupBase
{
	ref CF_ObservableMap<T, ref CF_DropdownElementBase> m_Elements;

	CF_Dropdown<T> m_Dropdown;

	string m_LayoutFile;

	override void Init(CF_DropdownBase dropdown, string popupLayoutFile, string elementLayoutFile)
	{
		Class.CastTo(m_Dropdown, dropdown);

		m_LayoutFile = popupLayoutFile;

		m_Elements = new CF_ObservableMap<T, ref CF_DropdownElementBase>();

		int count = m_Dropdown.m_Elements.Count();
		for (int i = 0; i < count; i++)
		{
			T item = m_Dropdown.m_Elements[i];
			auto element = new CF_DropdownElement<T>();
			element.Init(item, m_Dropdown, elementLayoutFile);
			m_Elements.Insert(item, element);
		}
	}

	override string GetLayoutFile()
	{
		return m_LayoutFile;
	}

	override void SetSelected(Class selected)
	{
		for (int i = 0; i < m_Elements.Count(); i++)
		{
			auto element = CF_DropdownElement<T>.Cast(m_Elements.GetElement(i));

			if (element.m_Data == selected)
			{
				element.SetSelected(true);
				continue;
			}

			element.SetSelected(false);
		}
	}
};
