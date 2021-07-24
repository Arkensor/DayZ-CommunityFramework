/**
 * Super implementation to handle all possible conversions. 
 */
class CF_TypeConverter : Managed
{
	void SetInt(int value)
	{
		
	}

	int GetInt()
	{
		return 0;		
	}

	void SetBool(bool value)
	{
		
	}

	bool GetBool()
	{
		return false;
	}

	void SetFloat(float value)
	{
		
	}

	float GetFloat()
	{
		return 0;
	}

	void SetVector(vector value)
	{
		
	}

	vector GetVector()
	{
		return "0 0 0";
	}
	
	void SetString(string value)
	{

	}

	string GetString()
	{
		return "";
	}

	void SetClass(Class value)
	{
		
	}

	Class GetClass()
	{
		return null;
	}

	void SetManaged(Managed value)
	{
		
	}

	Managed GetManaged()
	{
		return null;
	}

	string ToStr()
	{
		return "" + this;
	}

	void FromVariable(Class instance, string variable)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "FromVariable", "" + instance, variable);
		#endif
		CF_Log.Error("Override FromVariable!");
	}

	bool FromTypename(Class instance, int index)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "FromVariable", "" + instance, "" + index);
		#endif
		CF_Log.Error("Override FromVariable!");
		return false;
	}

	void ToVariable(Class instance, string variable)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "ToVariable", "" + instance, variable);
		#endif
		CF_Log.Error("Override ToVariable!");
	}
};

class CF_TypeConverterT<Class T> : CF_TypeConverter
{
	protected T m_Value;
	
	void Set(T value)
	{
		m_Value = value;
	}
	
	T Get()
	{
		return m_Value;
	}

	override void FromVariable(Class instance, string variable)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "FromVariable", "" + instance, variable);
		#endif
		EnScript.GetClassVar(instance, variable, 0, m_Value);
	}

	override bool FromTypename(Class instance, int index)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "FromVariable", "" + instance, "" + index);
		#endif

		typename type = instance.Type();

		typename variableType = type.GetVariableType(index);
		string variableName = type.GetVariableName(index);

		if (variableType.IsInherited(Class))
		{
			//string variableTypeStr = variableType.ToString();
			//int idx = variableTypeStr.IndexOf("<");
			//if (idx != -1) return false;
			return false;
		}
		else
		{
			type.GetVariableValue(instance, index, m_Value);
		}

		return true;
	}

	override void ToVariable(Class instance, string variable)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "ToVariable", "" + instance, variable);
		#endif
		EnScript.SetClassVar(instance, variable, 0, m_Value);
	}
};