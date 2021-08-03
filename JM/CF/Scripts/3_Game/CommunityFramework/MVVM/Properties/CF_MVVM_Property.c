class CF_MVVM_Property : CF_MVVM_PropertyBase
{
	protected CF_ModelBase m_Model;
	protected CF_ViewModel m_ViewModel;

	protected CF_ObservableCollection m_Collection;
	protected bool m_IsCollection;

	protected string m_Name;
	protected string m_VariableName;

	protected string m_TypeConverterType;
	protected ref CF_TypeConverter m_TypeConverter;

	void CF_MVVM_Property(CF_ViewModel handler, string name)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "CF_MVVM_Property", "" + handler, name);
		#endif

		m_ViewModel = handler;
		m_Name = name;
	}

	string SetVariableName(string variableName)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "SetVariableName", "" + variableName);
		#endif

		int colonSeperator = variableName.IndexOf(":");
		if (colonSeperator == -1)
		{
			m_VariableName = variableName;
			return m_VariableName;
		}

		m_VariableName = variableName.Substring(0, colonSeperator);
		m_TypeConverterType = variableName.Substring(colonSeperator + 1, variableName.Length() - colonSeperator - 1);

		return m_VariableName;
	}

	string GetVariableName()
	{
		return m_VariableName;
	}

	string GetName()
	{
		return m_Name;
	}

	override string ToStr()
	{
		string str = "[" + ClassName() + "] ";
		str += "Name=" + m_Name;
		str += ", ";
		str += "VariableName=" + m_VariableName;
		str += ", ";
		str += "IsCollection=" + m_IsCollection;
		str += ", ";
		str += "Collection=" + m_Collection;
		str += ", ";
		str += "Model=" + m_Model;
		str += ", ";
		str += "ViewModel=" + m_ViewModel;
		str += ", ";
		str += "TypeConverterType=" + m_TypeConverterType;
		return str;
	}

	void Link(CF_ModelBase model, typename variableType, CF_TypeConverter typeConverter)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Assign", "" + model);
		#endif

		m_Model = model;

		m_IsCollection = variableType.IsInherited(CF_ObservableCollection);
		if (m_IsCollection)
		{
			OnModel(new CF_EventArgs());

			return;
		}

		m_TypeConverter = typeConverter;

		CF_TypeConverter typeConverterOverride;
		if (m_TypeConverterType != string.Empty && Class.CastTo(typeConverterOverride, m_TypeConverterType.ToType().Spawn()))
		{
			if (typeConverterOverride.IsInherited(m_TypeConverter.Type()))
			{
				m_TypeConverter = typeConverterOverride;
			}
			else
			{
				CF_Log.Warn("Overriding type converter '%1' doesn't inherit from '%2'. Using '%2'.", typeConverterOverride.ToStr(), m_TypeConverter.ToStr());
			}
		}

		EnScript.SetClassVar(m_ViewModel, "_" + m_Name, 0, this);

		OnModel(new CF_EventArgs());
	}
	
	void OnView(/*notnull*/ CF_EventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView", evt.ToStr());
		#endif

		Param param = new Param2<CF_ModelBase, CF_EventArgs>(m_Model, evt);
		g_Script.CallFunctionParams(m_ViewModel, "OnView_" + m_Name, null, param);
	}

	void OnModel(/*notnull*/ CF_EventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel", evt.ToStr());
		#endif

		CF_EventArgs eventOverride = evt;

		if (m_IsCollection)
		{
			CF_ObservableCollection _collection;
			EnScript.GetClassVar(m_Model, m_VariableName, 0, _collection);
			EnScript.SetClassVar(m_ViewModel, "_" + m_Name, 0, _collection);

			if (!evt.Type().IsInherited(CF_CollectionEventArgs))
			{
				if (_collection == m_Collection) return;

				// the previous instance may still be alive, if so, make sure it doesn't notify from now on
				if (m_Collection)
				{
					m_Collection.Init(null);
				}

				if (_collection)
				{
					_collection.Init(m_Model, m_VariableName);

					CF_TypeConverter typeConverter = _collection.GetConverter();
					if (!typeConverter)
					{
						CF_Log.Error("Collection '%1.%2' has no assigned type converter!", "" + m_Model, m_VariableName);
						return;
					}

					CF_TypeConverter replacingTypeConverter;
					if (m_TypeConverterType != string.Empty && Class.CastTo(replacingTypeConverter, m_TypeConverterType.ToType().Spawn()))
					{
						if (replacingTypeConverter.IsInherited(typeConverter.Type()))
						{
							_collection.OverrideConverter(replacingTypeConverter);
						}
						else
						{
							CF_Log.Warn("Overriding type converter '%1' doesn't inherit from '%2'. Using '%2'.", replacingTypeConverter.ToStr(), typeConverter.ToStr());
						}
					}
				}

				// The variable is no longer set to an instance, override event to reset UI
				if (!_collection) eventOverride = new CF_CollectionClearEventArgs();
			}

			m_Collection = _collection;
		}

		Param param = new Param2<CF_ModelBase, CF_EventArgs>(m_Model, eventOverride);
		g_Script.CallFunctionParams(m_ViewModel, "OnModel_" + m_Name, null, param);
	}

	override bool IsDefault()
	{
		return false;
	}

	override void SetInt(int value)
	{
		m_TypeConverter.SetInt(value);
		m_TypeConverter.ToVariable(m_Model, m_VariableName);
	}

	override int GetInt()
	{
		m_TypeConverter.FromVariable(m_Model, m_VariableName);
		return m_TypeConverter.GetInt();
	}

	override void SetBool(bool value)
	{
		m_TypeConverter.SetBool(value);
		m_TypeConverter.ToVariable(m_Model, m_VariableName);
	}

	override bool GetBool()
	{
		m_TypeConverter.FromVariable(m_Model, m_VariableName);
		return m_TypeConverter.GetBool();
	}

	override void SetFloat(float value)
	{
		m_TypeConverter.SetFloat(value);
		m_TypeConverter.ToVariable(m_Model, m_VariableName);
	}

	override float GetFloat()
	{
		m_TypeConverter.FromVariable(m_Model, m_VariableName);
		return m_TypeConverter.GetFloat();
	}

	override void SetVector(vector value)
	{
		m_TypeConverter.SetVector(value);
		m_TypeConverter.ToVariable(m_Model, m_VariableName);
	}

	override vector GetVector()
	{
		m_TypeConverter.FromVariable(m_Model, m_VariableName);
		return m_TypeConverter.GetVector();
	}
	
	override void SetString(string value)
	{
		m_TypeConverter.SetString(value);
		m_TypeConverter.ToVariable(m_Model, m_VariableName);
	}

	override string GetString()
	{
		m_TypeConverter.FromVariable(m_Model, m_VariableName);
		return m_TypeConverter.GetString();
	}

	override void SetClass(Class value)
	{
		m_TypeConverter.SetClass(value);
		m_TypeConverter.ToVariable(m_Model, m_VariableName);
	}

	override Class GetClass()
	{
		m_TypeConverter.FromVariable(m_Model, m_VariableName);
		return m_TypeConverter.GetClass();
	}

	override void SetManaged(Managed value)
	{
		m_TypeConverter.SetManaged(value);
		m_TypeConverter.ToVariable(m_Model, m_VariableName);
	}

	override Managed GetManaged()
	{
		m_TypeConverter.FromVariable(m_Model, m_VariableName);
		return m_TypeConverter.GetManaged();
	}
};
