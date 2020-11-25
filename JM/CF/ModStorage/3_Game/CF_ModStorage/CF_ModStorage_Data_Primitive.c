typedef CF_ModStorage_Data_Primitive<bool> CF_ModStorage_Data_Bool;
typedef CF_ModStorage_Data_Primitive<int> CF_ModStorage_Data_Int;
typedef CF_ModStorage_Data_Primitive<float> CF_ModStorage_Data_Float;
typedef CF_ModStorage_Data_Primitive<vector> CF_ModStorage_Data_Vector;
typedef CF_ModStorage_Data_Primitive<string> CF_ModStorage_Data_String;

class CF_ModStorage_Data_Primitive<Class T> : CF_ModStorage_Data
{
	protected T m_Value;

	void CF_ModStorage_Data_Primitive(T value)
	{
		m_Value = value;
	}

	override typename GetType()
	{
		return TemplateType<T>.GetType();
	}

	override void Write(ParamsWriteContext ctx)
	{
		ctx.Write(m_VariableName);
		ctx.Write(m_Value);
	}

	override void Read(ParamsReadContext ctx)
	{
		ctx.Read(m_VariableName);
		ctx.Read(m_Value);
	}

	override void SetFrom(Class cls, string name, int idx = 0)
	{
		EnScript.GetClassVar(cls, name, idx, m_Value);
	}

	override void SetTo(Class cls, string name, int idx = 0)
	{
		EnScript.SetClassVar(cls, name, idx, m_Value);
	}

	override Param Get()
	{
		return new Param1<T>(m_Value);
	}
};