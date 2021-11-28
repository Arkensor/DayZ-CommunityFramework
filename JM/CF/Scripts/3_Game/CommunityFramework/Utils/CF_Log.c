class CF_Log
{
	static int Level = CF_LogLevel.ERROR;

	static bool IsLogging(CF_LogLevel level)
	{
		return level >= Level;
	}

	static void Trace(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (Level > CF_LogLevel.TRACE) return;

		PrintFormat("[TRACE] %1", string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}

	static void Debug(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (Level > CF_LogLevel.DEBUG) return;

		PrintFormat("[DEBUG] %1", string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}

	static void Info(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (Level > CF_LogLevel.INFO) return;

		PrintFormat("[INFO] %1", string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}

	static void Warn(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (Level > CF_LogLevel.WARNING) return;

		PrintFormat("[WARNING] %1", string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}

	static void Error(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (Level > CF_LogLevel.ERROR) return;

		PrintFormat("[ERROR] %1", string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}
};
