class CF_MVVM_Property : CF_MVVM_PropertyBase
{
	protected CF_ModelBase m_Model;
	protected CF_ViewModel m_ViewModel;

	protected CF_ObservableCollection m_Collection;
	protected bool m_IsCollection;

	protected string m_Name;
	protected string m_VariableName;
	protected string m_ActualVariableName;
	// Going 1 deep is more than enough.

	protected int m_VariableIndices[4];
	protected int m_IndexCount;

	protected string m_TypeConverterType;
	protected ref CF_TypeConverter m_TypeConverter;

	void CF_MVVM_Property(CF_ViewModel handler, string name)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "CF_MVVM_Property").Add(handler).Add(name);
		#endif

		m_ViewModel = handler;
		m_Name = name;
	}

	string SetVariableName(string variableName)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "SetVariableName").Add(variableName);
		#endif

		m_IndexCount = -1;
		m_VariableName = variableName;

		int colonSeperator = m_VariableName.IndexOf(":");
		if (colonSeperator != -1)
		{
			m_VariableName = variableName.Substring(0, colonSeperator);
			m_TypeConverterType = variableName.Substring(colonSeperator + 1, variableName.Length() - colonSeperator - 1);
		}

		m_ActualVariableName = m_VariableName;

		if (m_VariableName.IndexOf(".") == -1)
		{
			m_IndexCount = 0;
		}

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

	override string GetDebugName()
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
		auto trace = CF_Trace_1(this, "Assign").Add(model);
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
				CF_Log.Warn("Overriding type converter '%1' doesn't inherit from '%2'. Using '%2'.", typeConverterOverride.GetDebugName(), m_TypeConverter.GetDebugName());
			}
		}

		EnScript.SetClassVar(m_ViewModel, "_" + m_Name, 0, this);

		OnModel(new CF_EventArgs());
	}
	
	void OnView(/*notnull*/ CF_EventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnView").Add(evt.GetDebugName());
		#endif

		if (m_IndexCount == -1) AcquireIndices();

		Param param = new Param2<CF_ModelBase, CF_EventArgs>(m_Model, evt);
		g_Script.CallFunctionParams(m_ViewModel, "OnView_" + m_Name, null, param);
	}

	void OnModel(/*notnull*/ CF_EventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnModel").Add(evt.GetDebugName());
		#endif

		if (m_IndexCount == -1) AcquireIndices();

		CF_EventArgs eventOverride = evt;

		if (m_IsCollection)
		{
			CF_ObservableCollection _collection = CF_ObservableCollection.Cast(GetClass());

			EnScript.SetClassVar(m_ViewModel, "_" + m_Name, 0, _collection);

			if (!evt.Type().IsInherited(CF_CollectionEventArgs))
			{
				if (_collection == m_Collection) return;

				//UPDATE: will continue to notify, even if unlinked
				// the previous instance may still be alive, if so, make sure it doesn't notify from now on
				//if (m_Collection)
				//{
				//	m_Collection.Init(null);
				//}

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
							CF_Log.Warn("Overriding type converter '%1' doesn't inherit from '%2'. Using '%2'.", replacingTypeConverter.GetDebugName(), typeConverter.GetDebugName());
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

	void AcquireIndices()
	{
		array<string> tokens();
		m_VariableName.Split(".", tokens);

		typename type = m_Model.Type();

		m_IndexCount = tokens.Count() - 1;

		for (int i = 0; i < m_IndexCount; i++)
		{
			bool success = false;
			for (int j = 0; j < type.GetVariableCount(); j++)
			{
				if (type.GetVariableName(j) == tokens[i])
				{
					m_VariableIndices[i] = j;

					type = type.GetVariableType(j);

					success = true;

					break; // break bad
				}
			}

			// couldn't find sub variable
			if (!success) return;
		}

		m_ActualVariableName = tokens[m_IndexCount];
	}

	void Write()
	{
		typename type = m_Model.Type();
		Class cls = m_Model;

		for (int i = 0; i < m_IndexCount; i++)
		{
			int idx = m_VariableIndices[i];
			type.GetVariableValue(cls, idx, cls);
			type = type.GetVariableType(idx);
		}

		m_TypeConverter.Write(cls, m_ActualVariableName);
	}

	void Read()
	{
		typename type = m_Model.Type();
		Class cls = m_Model;

		for (int i = 0; i < m_IndexCount; i++)
		{
			int idx = m_VariableIndices[i];
			type.GetVariableValue(cls, idx, cls);
			type = type.GetVariableType(idx);
		}

		m_TypeConverter.Read(cls, m_ActualVariableName);
	}

	override void SetInt(int value)
	{
		m_TypeConverter.SetInt(value);
		Write();
	}

	override int GetInt()
	{
		Read();
		return m_TypeConverter.GetInt();
	}

	override void SetBool(bool value)
	{
		m_TypeConverter.SetBool(value);
		Write();
	}

	override bool GetBool()
	{
		Read();
		return m_TypeConverter.GetBool();
	}

	override void SetFloat(float value)
	{
		m_TypeConverter.SetFloat(value);
		Write();
	}

	override float GetFloat()
	{
		Read();
		return m_TypeConverter.GetFloat();
	}

	override void SetVector(vector value)
	{
		m_TypeConverter.SetVector(value);
		Write();
	}

	override vector GetVector()
	{
		Read();
		return m_TypeConverter.GetVector();
	}
	
	override void SetString(string value)
	{
		m_TypeConverter.SetString(value);
		Write();
	}

	override string GetString()
	{
		Read();
		return m_TypeConverter.GetString();
	}

	override void SetClass(Class value)
	{
		m_TypeConverter.SetClass(value);
		Write();
	}

	override Class GetClass()
	{
		Read();
		return m_TypeConverter.GetClass();
	}

	override void SetManaged(Managed value)
	{
		m_TypeConverter.SetManaged(value);
		Write();
	}

	override Managed GetManaged()
	{
		Read();
		return m_TypeConverter.GetManaged();
	}
};
