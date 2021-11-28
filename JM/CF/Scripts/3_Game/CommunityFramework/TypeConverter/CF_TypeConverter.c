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

	string GetDebugName()
	{
		return "[" + this + "] " + GetString();
	}

	void ToIO(CF_IO io)
	{

	}

	void FromIO(CF_IO io)
	{
		
	}

	void Read(Class instance, string variable)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Read", "" + instance, variable);
		#endif

		CF_Log.Error("" + ClassName() + "::Read not implemented");
	}

	bool Read(Class instance, int index)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Read", "" + instance, "" + index);
		#endif

		CF_Log.Error("" + ClassName() + "::Read not implemented");

		return false;
	}

	void Write(Class instance, string variable)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Write", "" + instance, variable);
		#endif

		CF_Log.Error("" + ClassName() + "::Write not implemented");
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

	override void Read(Class instance, string variable)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Read", "" + instance, variable);
		#endif

		EnScript.GetClassVar(instance, variable, 0, m_Value);
	}

	override bool Read(Class instance, int index)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Read", "" + instance, "" + index);
		#endif

		typename type = instance.Type();

		typename variableType = type.GetVariableType(index);
		string variableName = type.GetVariableName(index);

		// Unfortunately 'Class' type variables results in a hard crash with no discernible pattern to lock them out
		if (variableType.IsInherited(Class)) return false;

		type.GetVariableValue(instance, index, m_Value);

		return true;
	}

	override void Write(Class instance, string variable)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Write", "" + instance, variable);
		#endif

		EnScript.SetClassVar(instance, variable, 0, m_Value);
	}
};
