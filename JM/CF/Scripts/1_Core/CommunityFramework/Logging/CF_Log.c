class CF_Log
{
#ifdef CF_TRACE_ENABLED
	static int Level = CF_LogLevel.TRACE;
#else
#ifdef DIAG_DEVELOPER
	static int Level = CF_LogLevel.DEBUG;
#else
#ifdef BUILD_EXPERIMENTAL
	static int Level = CF_LogLevel.INFO;
#else
	static int Level = CF_LogLevel.ERROR;
#endif
#endif
#endif

	static ref CF_TimestampHelperCore s_TimestampHelper;

	static bool IsLogging(CF_LogLevel level)
	{
		return level >= Level;
	}

	/**
	 * @brief Logs that contain the most detailed messages. These messages should never be enabled in a production environment.
	 */
	static void Trace(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (Level > CF_LogLevel.TRACE) return;

		PrintFormat("%1 [TRACE]\t%2", FormatTime(), string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}

	/**
	 * @brief Logs that should primarily contain information useful for debugging. 
	 */
	static void Debug(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (Level > CF_LogLevel.DEBUG) return;

		PrintFormat("%1 [DEBUG]\t%2", FormatTime(), string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}

	/**
	 * @brief Logs that output information that may be relevant to the user.
	 */
	static void Info(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (Level > CF_LogLevel.INFO) return;

		PrintFormat("%1 [INFO]\t%2", FormatTime(), string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}

	/**
	 * @brief Logs that highlight an abnormal action, but does not cause the user to notice anything different.
	 */
	static void Warn(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (Level > CF_LogLevel.WARNING) return;

		PrintFormat("%1 [WARNING]\t%2", FormatTime(), string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}

	/**
	 * @brief Logs that highlight when the current flow of execution is stopped due to a failure. This should indicate if the current activity has a failure and will not result in the game shutting down. Produces a stack trace.
	 */
	static void Error(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (Level > CF_LogLevel.ERROR) return;

		PrintFormat("%1 [ERROR]\t%2", FormatTime(), string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));

		string dump = "";
		DumpStackString(dump);
		array<string> outputs = new array<string>();
		dump.Split("\n", outputs);

		for (int i = 1; i < outputs.Count(); i++)
		{
			Print("\t" + outputs[i]);
		}
	}

	/**
	 * @brief Logs that describe an unrecoverable event and will most likely lead to the shutdown of the game. Produces a stack trace.
	 */
	static void Critical(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (Level > CF_LogLevel.CRITICAL) return;

		PrintFormat("%1 [CRITICAL]\t%2", FormatTime(), string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));

		string dump = "";
		DumpStackString(dump);
		array<string> outputs = new array<string>();
		dump.Split("\n", outputs);

		for (int i = 1; i < outputs.Count(); i++)
		{
			Print("\t" + outputs[i]);
		}
	}

	static string FormatTime(bool useUTC = false, string delimHMS = ":")
	{
		if (s_TimestampHelper)
			return s_TimestampHelper.FormatTime(useUTC, delimHMS);

		int hours;
		int minutes;
		int seconds;

		if (useUTC)
			GetHourMinuteSecondUTC(hours, minutes, seconds);
		else
			GetHourMinuteSecond(hours, minutes, seconds);

		return hours.ToStringLen(2) + delimHMS + minutes.ToStringLen(2) + delimHMS + seconds.ToStringLen(2);
	}
};
