class CF_Trace
{
	private static int s_TraceDepth = 0;

	private string m_ClassName;
	private string m_StackName;
	private int m_TickCount;

	private static string Depth()
	{
		int depth = s_TraceDepth;
		string str = "";
		while (depth > 0)
		{
			str += " ";
			depth--;
		}
		return str;
	}

	void CF_Trace(Class cls, string stackName, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		m_TickCount = TickCount(m_TickCount);

		m_ClassName = "";
		if (cls)
		{
			m_ClassName = "" + cls + "::";
			Object obj;
			if (Class.CastTo(obj, cls)) m_ClassName = "(" + Object.GetDebugName(obj) + ")::";
		}
		
		m_StackName = stackName;

		string trace = "";
		     if (param9 != "") trace += "%1, %2, %3, %4, %5, %6, %7, %8, %9";
		else if (param8 != "") trace += "%1, %2, %3, %4, %5, %6, %7, %8";
		else if (param7 != "") trace += "%1, %2, %3, %4, %5, %6, %7";
		else if (param6 != "") trace += "%1, %2, %3, %4, %5, %6";
		else if (param5 != "") trace += "%1, %2, %3, %4, %5";
		else if (param4 != "") trace += "%1, %2, %3, %4";
		else if (param3 != "") trace += "%1, %2, %3";
		else if (param2 != "") trace += "%1, %2";
		else if (param1 != "") trace += "%1";

		trace = string.Format(trace, param1, param2, param3, param4, param5, param6);

		string message = string.Format("%1+%2%3 (%4)", Depth(), m_ClassName, m_StackName, trace);
		if (CF.LogLevel == CF_LogLevel.TRACE) Print("" + message);

		s_TraceDepth++;
	}

	void ~CF_Trace()
	{
		s_TraceDepth--;

		m_TickCount = TickCount(m_TickCount);

		string message = string.Format("%1-%2%3 CPU Ticks: %4", Depth(), m_ClassName, m_StackName, m_TickCount.ToString());
		if (CF.LogLevel == CF_LogLevel.TRACE) Print("" + message);
	}
};