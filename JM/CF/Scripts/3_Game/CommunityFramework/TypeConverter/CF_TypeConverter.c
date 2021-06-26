/**
 * Super implementation to handle all possible conversions. 
 */
class CF_TypeConverter
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

	void FromVariable(Class instance, string variable)
	{
		CF_Trace trace(this, "FromVariable", "" + instance, variable);
		CF.Log.Error("Override FromVariable!");
	}

	void ToVariable(Class instance, string variable)
	{
		CF_Trace trace(this, "ToVariable", "" + instance, variable);
		CF.Log.Error("Override ToVariable!");
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
		CF_Trace trace(this, "FromVariable", "" + instance, variable);
		EnScript.GetClassVar(instance, variable, 0, m_Value);
	}

	override void ToVariable(Class instance, string variable)
	{
		CF_Trace trace(this, "ToVariable", "" + instance, variable);
		EnScript.SetClassVar(instance, variable, 0, m_Value);
	}
};