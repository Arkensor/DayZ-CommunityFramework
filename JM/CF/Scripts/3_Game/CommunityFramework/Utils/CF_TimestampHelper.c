class CF_TimestampHelper: CF_TimestampHelperCore
{
	DayZGame m_Game;
	int m_StartTime;
	int m_StartTimeUTC;

	void CF_TimestampHelper(DayZGame game)
	{
		m_Game = game;

		int ms = m_Game.GetTime();

		int hours;
		int minutes;
		int seconds;

		GetHourMinuteSecond(hours, minutes, seconds);
		m_StartTime = hours * 3600000 + minutes * 60000 + seconds * 1000 - ms;

		GetHourMinuteSecondUTC(hours, minutes, seconds);
		m_StartTimeUTC = hours * 3600000 + minutes * 60000 + seconds * 1000 - ms;
	}

	override string FormatTime(bool useUTC = false, string delimHMS = ":")
	{
		int ms = GetTime(useUTC);

		int hours = ms / 3600000;
		ms -= hours * 3600000;

		hours = hours % 24;

		int minutes = ms / 60000;
		ms -= minutes * 60000;

		int seconds = ms / 1000;
		ms -= seconds * 1000;

		return hours.ToStringLen(2) + delimHMS + minutes.ToStringLen(2) + delimHMS + seconds.ToStringLen(2) + "." + ms.ToStringLen(3);
	}

	override int GetTime(bool useUTC = false)
	{
		int ms = m_Game.GetTime();

		if (useUTC)
			return m_StartTimeUTC + ms;

		return m_StartTime + ms;
	}
};
