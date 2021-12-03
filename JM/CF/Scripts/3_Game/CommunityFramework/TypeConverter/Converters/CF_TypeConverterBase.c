/**
 * @brief Super implementation to handle all possible conversions. 
 */
class CF_TypeConverterBase : Managed
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

	override string GetDebugName()
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
		auto trace = CF_Trace_1(this, "Read").Add(instance).Add(variable);
		#endif

		CF_Log.Error("" + ClassName() + "::Read not implemented");
	}

	bool Read(Class instance, int index)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Read").Add(instance).Add(index);
		#endif

		CF_Log.Error("" + ClassName() + "::Read not implemented");

		return false;
	}

	void Write(Class instance, string variable)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Write").Add(instance).Add(variable);
		#endif

		CF_Log.Error("" + ClassName() + "::Write not implemented");
	}
};
