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

	typename GetType()
	{
		typename type;
		return type;
	}

	override string GetDebugName()
	{
		return "[" + this + "] " + GetString();
	}

	bool IsIOSupported()
	{
		return false;
	}

	bool Read(Serializer ctx)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Read").Add(ctx);
		#endif

		CF_Log.Error("" + ClassName() + "::Read(Serializer) not implemented");

		return false;
	}

	bool Write(Serializer ctx)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Write").Add(ctx);
		#endif

		CF_Log.Error("" + ClassName() + "::Write(Serializer) not implemented");

		return false;
	}

	bool Read(CF_IO io)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Read").Add(io);
		#endif

		CF_Log.Error("" + ClassName() + "::Read(CF_IO) not implemented");

		return false;
	}

	bool Write(CF_IO io)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Write").Add(io);
		#endif

		CF_Log.Error("" + ClassName() + "::Write(CF_IO) not implemented");

		return false;
	}

	bool Read(Class instance, string variableName)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Read").Add(instance).Add(variableName);
		#endif

		CF_Log.Error("" + ClassName() + "::Read(Class, string) not implemented");

		return false;
	}

	bool Write(Class instance, string variableName)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Write").Add(instance).Add(variableName);
		#endif

		CF_Log.Error("" + ClassName() + "::Write(Class, string) not implemented");

		return false;
	}

	bool Read(Class instance, int variableIndex)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Read").Add(instance).Add(variableIndex);
		#endif

		CF_Log.Error("" + ClassName() + "::Read(Class, int) not implemented");

		return false;
	}
};
