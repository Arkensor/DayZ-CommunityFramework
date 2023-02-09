class CF_Trace : Managed
{
	// Global counter for the trace depth
	static string s_TraceDepth;

	protected string m_InstanceName;
	protected string m_StackName;
	
	protected int m_Ticks;

	protected int m_Count;

	protected int m_Index;
	protected string m_Strings[10];
	protected bool m_Flushed;
	protected bool m_DoLog;

	static string Depth()
	{
		return s_TraceDepth;
	}

	static string FormatInstance(Class instance)
	{
		if (!instance)
		{
			return "null";
		}
		
		string instanceName;
		//g_Script.CallFunction(instance, "GetDebugNameNative", instanceName, null);
		//if (instanceName == string.Empty)
		//{
			instanceName = "" + instance;
		//}

		return instanceName;
	}

	static string FormatStack(string instance, string stack)
	{
		string res;
		res = instance;
		if (stack != string.Empty) res = instance + "::" + stack;
		return res;
	}

	void CF_Trace(string instanceName, string stackName, int count, bool doLog)
	{
		m_DoLog = doLog;

		m_InstanceName = instanceName;

		string dump = "";
		DumpStackString(dump);
		array<string> outputs = new array<string>();
		dump.Split("\n", outputs);
		m_StackName = outputs[2];
		m_StackName = m_StackName.Substring(0, m_StackName.IndexOf("("));

		if (stackName != string.Empty)
		{
			m_StackName = m_StackName + "_" + stackName;
		}

		m_Count = count;

		if (m_Count == 0) Output();
	}

	void ~CF_Trace()
	{
		if (!m_DoLog || !m_Flushed) return;
		
		s_TraceDepth = s_TraceDepth.Substring(0, s_TraceDepth.Length() - 1);

		m_Ticks = TickCount(m_Ticks);

		CF_Log.Trace("%1-%2 Time: %3ms", Depth(), FormatStack(m_InstanceName, m_StackName), (m_Ticks / 10000.0).ToString());
	}

	bool IsLogged()
	{
		return m_DoLog;
	}

	void Output()
	{
		if (!m_DoLog || m_Flushed) return;
		m_Flushed = true;

		string params;
		for (int i = 0; i < m_Count - 1; i++)
		{
			params += m_Strings[i] + ", ";
		}

		if (m_Count > 0) params += m_Strings[m_Count - 1];

		CF_Log.Trace("%1+%2 (%3)", Depth(), FormatStack(m_InstanceName, m_StackName), params);

		s_TraceDepth += " ";
		
		m_Ticks = TickCount(0);
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

	CF_Trace Add(typename value)
	{
		m_Strings[m_Index] = value.ToString();
		m_Index++;

		if (m_Index < m_Count || m_Count == -1) return this;

		Output();

		return this;
	}

	CF_Trace Add(Class value)
	{
		string val = "" + value;

		if (value) val = "\"" + value.GetDebugName() + "\"";

		m_Strings[m_Index] = val;
		m_Index++;

		if (m_Index < m_Count || m_Count == -1) return this;

		Output();
		
		return this;
	}

	CF_Trace Add(int value, typename type)
	{
		return Add(typename.EnumToString(type, value));
	}

	CF_Trace Add(int value, array<string> values)
	{
		string vName = "INVALID";
		if (value >= 0 && value < values.Count())
		{
			vName = values[value];
		}

		return Add(vName);
	}
};

static CF_Trace CF_Trace_Instance(Class instance)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), string.Empty, 0, true);
	return trace;
}

static CF_Trace CF_Trace_0(Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 0, true);
	return trace;
}

static CF_Trace CF_Trace_1(Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 1, true);
	return trace;
}

static CF_Trace CF_Trace_2(Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 2, true);
	return trace;
}

static CF_Trace CF_Trace_3(Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 3, true);
	return trace;
}

static CF_Trace CF_Trace_4(Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 4, true);
	return trace;
}

static CF_Trace CF_Trace_5(Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 5, true);
	return trace;
}

static CF_Trace CF_Trace_6(Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 6, true);
	return trace;
}

static CF_Trace CF_Trace_7(Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 7, true);
	return trace;
}

static CF_Trace CF_Trace_8(Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 8, true);
	return trace;
}

static CF_Trace CF_Trace_9(Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 9, true);
	return trace;
}

static CF_Trace CF_Trace_0(string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 0, true);
	return trace;
}

static CF_Trace CF_Trace_1(string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 1, true);
	return trace;
}

static CF_Trace CF_Trace_2(string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 2, true);
	return trace;
}

static CF_Trace CF_Trace_3(string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 3, true);
	return trace;
}

static CF_Trace CF_Trace_4(string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 4, true);
	return trace;
}

static CF_Trace CF_Trace_5(string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 5, true);
	return trace;
}

static CF_Trace CF_Trace_6(string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 6, true);
	return trace;
}

static CF_Trace CF_Trace_7(string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 7, true);
	return trace;
}

static CF_Trace CF_Trace_8(string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 8, true);
	return trace;
}

static CF_Trace CF_Trace_9(string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 9, true);
	return trace;
}

static CF_Trace CF_Trace_Instance(bool doLog, Class instance)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), string.Empty, 0, doLog);
	return trace;
}

static CF_Trace CF_Trace_0(bool doLog, Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 0, doLog);
	return trace;
}

static CF_Trace CF_Trace_1(bool doLog, Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 1, doLog);
	return trace;
}

static CF_Trace CF_Trace_2(bool doLog, Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 2, doLog);
	return trace;
}

static CF_Trace CF_Trace_3(bool doLog, Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 3, doLog);
	return trace;
}

static CF_Trace CF_Trace_4(bool doLog, Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 4, doLog);
	return trace;
}

static CF_Trace CF_Trace_5(bool doLog, Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 5, doLog);
	return trace;
}

static CF_Trace CF_Trace_6(bool doLog, Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 6, doLog);
	return trace;
}

static CF_Trace CF_Trace_7(bool doLog, Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 7, doLog);
	return trace;
}

static CF_Trace CF_Trace_8(bool doLog, Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 8, doLog);
	return trace;
}

static CF_Trace CF_Trace_9(bool doLog, Class instance, string stackName = string.Empty)
{
	auto trace = new CF_Trace(CF_Trace.FormatInstance(instance), stackName, 9, doLog);
	return trace;
}

static CF_Trace CF_Trace_0(bool doLog, string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 0, doLog);
	return trace;
}

static CF_Trace CF_Trace_1(bool doLog, string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 1, doLog);
	return trace;
}

static CF_Trace CF_Trace_2(bool doLog, string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 2, doLog);
	return trace;
}

static CF_Trace CF_Trace_3(bool doLog, string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 3, doLog);
	return trace;
}

static CF_Trace CF_Trace_4(bool doLog, string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 4, doLog);
	return trace;
}

static CF_Trace CF_Trace_5(bool doLog, string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 5, doLog);
	return trace;
}

static CF_Trace CF_Trace_6(bool doLog, string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 6, doLog);
	return trace;
}

static CF_Trace CF_Trace_7(bool doLog, string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 7, doLog);
	return trace;
}

static CF_Trace CF_Trace_8(bool doLog, string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 8, doLog);
	return trace;
}

static CF_Trace CF_Trace_9(bool doLog, string instance = string.Empty, string stackName = string.Empty)
{
	auto trace = new CF_Trace(instance, stackName, 9, doLog);
	return trace;
}
