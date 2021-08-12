class CF_Dropdown<Class T> : CF_Model
{
	ref CF_ObservableArray<T> m_Elements;

	T m_Selected;

	autoptr CF_DropdownPopup<T> m_Popup;

	void CF_Dropdown(CF_ObservableArray<T> elements)
	{
		m_Elements = elements;
		if (!m_Elements)
		{
			m_Elements = new CF_ObservableArray<T>();
		}
	}

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

	void SetSelected(T selected)
	{
		if (m_Selected == selected) return;

		m_Selected = selected;

		if (m_Popup) m_Popup.SetSelected(m_Selected);
	}

	void Open()
	{
		if (m_Popup) return;

		m_Popup = new CF_DropdownPopup<T>(this, GetPopupLayoutFile(), GetElementLayoutFile());
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

class CF_DropdownElement<Class T> : CF_Model
{
	T m_Data;
	bool m_Selected;

	CF_Dropdown<T> m_Dropdown;

	string m_LayoutFile;

	void CF_DropdownElement(T data, CF_Dropdown<T> dropdown, string layoutFile)
	{
		m_Data = data;
		m_Dropdown = dropdown;

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

	void SetSelected(bool selected)
	{
		m_Selected = selected;
		NotifyPropertyChanged("m_Selected");
	}
};

class CF_DropdownPopup<Class T> : CF_Popup
{
	ref CF_ObservableMap<T, ref CF_DropdownElement<T>> m_Elements;

	CF_Dropdown<T> m_Dropdown;

	string m_LayoutFile;

	void CF_DropdownPopup(CF_Dropdown<T> dropdown, string popupLayoutFile, string elementLayoutFile)
	{
		m_Dropdown = dropdown;

		m_LayoutFile = popupLayoutFile;

		m_Elements = new CF_ObservableMap<T, ref CF_DropdownElement<T>>();

		int count = m_Dropdown.m_Elements.Count();
		for (int i = 0; i < count; i++)
		{
			T item = m_Dropdown.m_Elements[i];
			m_Elements.Insert(item, new CF_DropdownElement<T>(item, m_Dropdown, elementLayoutFile));
		}
	}

	override string GetLayoutFile()
	{
		return m_LayoutFile;
	}

	void SetSelected(T selected)
	{
		for (int i = 0; i < m_Elements.Count(); i++)
		{
			if (m_Elements[i].m_Data == selected)
			{
				m_Elements[i].SetSelected(true);
				continue;
			}

			m_Elements[i].SetSelected(false);
		}
	}
};
