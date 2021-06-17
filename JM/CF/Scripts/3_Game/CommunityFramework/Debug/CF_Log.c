class CF_Log
{
	static int Level = 0;

	static void _Init()
	{
	}

	static void _Cleanup()
	{

	}

	static int Set(int mask)
	{
		Level |= mask;
		return Level;
	}

	static int Remove(int mask)
	{
		Level &= ~mask;
		return Level;
	}

	static bool IsLogging(CF_LogLevel level)
	{
		return (Level & level) != 0;
	}

	static void Trace(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (!IsLogging(CF_LogLevel.TRACE)) return;

		PrintFormat("[TRACE] %1", string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}

	static void Debug(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (!IsLogging(CF_LogLevel.DEBUG)) return;

		PrintFormat("[DEBUG] %1", string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}

	static void Info(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (!IsLogging(CF_LogLevel.INFO)) return;

		PrintFormat("[INFO] %1", string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}

	static void Warn(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (!IsLogging(CF_LogLevel.WARNING)) return;

		PrintFormat("[WARNING] %1", string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}

	static void Error(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (!IsLogging(CF_LogLevel.ERROR)) return;

		PrintFormat("[ERROR] %1", string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}
};