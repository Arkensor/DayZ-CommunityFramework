class CF_Trace
{
	static string s_TraceDepth;

	protected string m_InstanceName;
	protected string m_StackName;
	
	protected int m_Ticks;

	protected int m_Count;

	protected int m_Index;
	protected string m_Strings[10];
	protected bool m_Flushed;

	static string Depth()
	{
		return s_TraceDepth;
	}

	static string FormatInstance(Class instance)
	{
		if (!instance) return "null";

		Object obj;
		if (Class.CastTo(obj, instance)) return "(" + Object.GetDebugName(obj) + ")";

		return "" + instance;
	}

	void CF_Trace(string instanceName, string stackName, int count)
	{
		m_InstanceName = instanceName;
		m_StackName = stackName;

		m_Count = count;

		if (m_Count == 0) Output();
	}

	void ~CF_Trace()
	{
		s_TraceDepth = s_TraceDepth.Substring(0, s_TraceDepth.Length() - 1);

		m_Ticks = TickCount(m_Ticks);

		CF_Log.Trace("%1-%2::%3 Time: %4ms", Depth(), m_InstanceName, m_StackName, (m_Ticks / 10000.0).ToString());
	}

	CF_Trace Output()
	{
		if (m_Flushed) return this;
		m_Flushed = true;

		string params;
		for (int i = 0; i < m_Count - 1; i++)
		{
			params += m_Strings[i] + ", ";
		}

		if (m_Count > 0) params += m_Strings[m_Count - 1];

		CF_Log.Trace("%1+%2::%3 (%4)", Depth(), m_InstanceName, m_StackName, params);

		s_TraceDepth += " ";
		
		m_Ticks = TickCount(0);

		return this;
	}

	CF_Trace Add(bool value)
	{
		m_Strings[m_Index] = value.ToString();
		m_Index++;

		if (m_Index < m_Count || m_Count == -1) return this;

		Output();

		return this;
	}

	CF_Trace Add(int value)
	{
		m_Strings[m_Index] = value.ToString();
		m_Index++;

		if (m_Index < m_Count || m_Count == -1) return this;

		Output();
		
		return this;
	}

	CF_Trace Add(float value)
	{
		m_Strings[m_Index] = value.ToString();
		m_Index++;

		if (m_Index < m_Count || m_Count == -1) return this;

		Output();
		
		return this;
	}

	CF_Trace Add(vector value)
	{
		m_Strings[m_Index] = value.ToString();
		m_Index++;

		if (m_Index < m_Count || m_Count == -1) return this;

		Output();
		
		return this;
	}

	CF_Trace Add(string value)
	{
		m_Strings[m_Index] = "\"" + value + "\"";
		m_Index++;

		if (m_Index < m_Count || m_Count == -1) return this;

		Output();
		
		return this;
	}

	CF_Trace Add(Class value)
	{
		string val = "" + value;

		if (value)
		{
			string toStr;
			g_Script.CallFunction(value, "ToStr", toStr, null);
			if (toStr != string.Empty) val = "\"" + toStr + "\"";
		}

		m_Strings[m_Index] = val;
		m_Index++;

		if (m_Index < m_Count || m_Count == -1) return this;

		Output();
		
		return this;
	}
};

static CF_Trace CF_Trace(Class instance, string stackName)
{
	return new CF_Trace(CF_Trace.FormatInstance(instance), stackName, -1);
}

static CF_Trace CF_Trace_0(Class instance, string stackName)
{
	return new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 0);
}

static CF_Trace CF_Trace_1(Class instance, string stackName)
{
	return new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 1);
}

static CF_Trace CF_Trace_2(Class instance, string stackName)
{
	return new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 2);
}

static CF_Trace CF_Trace_3(Class instance, string stackName)
{
	return new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 3);
}

static CF_Trace CF_Trace_4(Class instance, string stackName)
{
	return new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 4);
}

static CF_Trace CF_Trace_5(Class instance, string stackName)
{
	return new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 5);
}

static CF_Trace CF_Trace_6(Class instance, string stackName)
{
	return new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 6);
}

static CF_Trace CF_Trace_7(Class instance, string stackName)
{
	return new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 7);
}

static CF_Trace CF_Trace_8(Class instance, string stackName)
{
	return new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 8);
}

static CF_Trace CF_Trace_9(Class instance, string stackName)
{
	return new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 9);
}

static CF_Trace CF_Trace(string instance, string stackName)
{
	return new CF_Trace(instance, stackName, -1);
}

static CF_Trace CF_Trace_0(string instance, string stackName)
{
	return new CF_Trace(instance, stackName, 0);
}

static CF_Trace CF_Trace_1(string instance, string stackName)
{
	return new CF_Trace(instance, stackName, 1);
}

static CF_Trace CF_Trace_2(string instance, string stackName)
{
	return new CF_Trace(instance, stackName, 2);
}

static CF_Trace CF_Trace_3(string instance, string stackName)
{
	return new CF_Trace(instance, stackName, 3);
}

static CF_Trace CF_Trace_4(string instance, string stackName)
{
	return new CF_Trace(instance, stackName, 4);
}

static CF_Trace CF_Trace_5(string instance, string stackName)
{
	return new CF_Trace(instance, stackName, 5);
}

static CF_Trace CF_Trace_6(string instance, string stackName)
{
	return new CF_Trace(instance, stackName, 6);
}

static CF_Trace CF_Trace_7(string instance, string stackName)
{
	return new CF_Trace(instance, stackName, 7);
}

static CF_Trace CF_Trace_8(string instance, string stackName)
{
	return new CF_Trace(instance, stackName, 8);
}

static CF_Trace CF_Trace_9(string instance, string stackName)
{
	return new CF_Trace(instance, stackName, 9);
}

static CF_Trace CF_Trace(string stackName)
{
	return new CF_Trace("", stackName, -1);
}

static CF_Trace CF_Trace_0(string stackName)
{
	return new CF_Trace("", stackName, 0);
}

static CF_Trace CF_Trace_1(string stackName)
{
	return new CF_Trace("", stackName, 1);
}

static CF_Trace CF_Trace_2(string stackName)
{
	return new CF_Trace("", stackName, 2);
}

static CF_Trace CF_Trace_3(string stackName)
{
	return new CF_Trace("", stackName, 3);
}

static CF_Trace CF_Trace_4(string stackName)
{
	return new CF_Trace("", stackName, 4);
}

static CF_Trace CF_Trace_5(string stackName)
{
	return new CF_Trace("", stackName, 5);
}

static CF_Trace CF_Trace_6(string stackName)
{
	return new CF_Trace("", stackName, 6);
}

static CF_Trace CF_Trace_7(string stackName)
{
	return new CF_Trace("", stackName, 7);
}

static CF_Trace CF_Trace_8(string stackName)
{
	return new CF_Trace("", stackName, 8);
}

static CF_Trace CF_Trace_9(string stackName)
{
	return new CF_Trace("", stackName, 9);
}
