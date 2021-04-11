class CF_ModStorage_Data_Class : CF_ModStorage_Data
{
	protected Class m_Value;

	protected string m_Type = "";
	protected bool m_IsNull = false;
	protected autoptr array<ref CF_ModStorage_Data> m_Data = new ref array<ref CF_ModStorage_Data>();

	void CF_ModStorage_Data_Class(Class value)
	{
		m_Value = value;
		m_IsNull = m_Value == null;
	}

	override void OnSet()
	{
		m_IsNull = m_Value == null;
		if (m_IsNull)
			return;

		typename type = m_Value.Type();

		m_Type = type.ToString();

		for (int i = 0; i < type.GetVariableCount(); i++)
		{
			typename variableType = type.GetVariableType(i);
			string variableName = type.GetVariableName(i);

			ref CF_ModStorage_Data data = CF_ModStorage_Converter.Create(variableType.ToString());
			if (data)
			{
				data.m_VariableName = variableName;

				data.SetFrom(m_Value, data.m_VariableName);

				data.OnSet();

				m_Data.Insert(data);
			}
			else
			{
				Error("Invalid data passsed into ModStorage class '" + variableName + "' '" + variableType.ToString() + "'");
			}
		}
	}

	override bool IsNull()
	{
		return m_IsNull;
	}

	override typename GetType()
	{
		return Class;
	}

	override void Write(ParamsWriteContext ctx)
	{
		ctx.Write(m_VariableName);
		ctx.Write(m_IsNull);
		ctx.Write(m_Type);

		int count = m_Data.Count();
		ctx.Write(count);

		for (int i = 0; i < count; i++)
		{
			ctx.Write(m_Data[i].GetType().ToString());
			m_Data[i].Write(ctx);
		}
	}

	override void Read(ParamsReadContext ctx)
	{
		ctx.Read(m_VariableName);
		ctx.Read(m_IsNull);
		ctx.Read(m_Type);
		
		int count;
		ctx.Read(count);

		for (int i = 0; i < count; i++)
		{
			m_Data.Insert(CF_ModStorage_Converter.Read(ctx));
		}
	}

	override void SetFrom(Class cls, string name, int idx = 0)
	{
		EnScript.GetClassVar(cls, name, idx, m_Value);
	}

	override void SetTo(Class cls, string name, int idx = 0)
	{
		if (IsNull())
			return;

		EnScript.GetClassVar(cls, name, idx, m_Value);
		if (!Get(m_Value))
			return;

		EnScript.SetClassVar(cls, name, idx, m_Value);
	}

	override bool Get(inout Class cls)
	{
		if (m_IsNull)
			return true;

		if (!cls)
		{
			if (m_Type == "")
				return false;

			cls = m_Type.ToType().Spawn();

			if (cls == null)
				return false;
		}

		for (int i = 0; i < m_Data.Count(); i++)
		{
			m_Data[i].SetTo(cls, m_Data[i].m_VariableName, 0);
		}

		return true;
	}
};