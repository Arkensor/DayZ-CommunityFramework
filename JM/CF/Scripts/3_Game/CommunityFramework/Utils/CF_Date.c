typedef CF_Date JMDate; // Compatability with a variety of mods.

class CF_Date : Managed
{
	// TODO: Stringtable
	static const string MONTHS_FULL_NAME[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	static const string MONTHS_SHORT_NAME[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	static const int DAYS_IN_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	static const string TIME = "hh:mm:ss";
	static const string DATE = "YYYY-MM-DD";
	static const string DATETIME = "YYYY-MM-DD hh:mm:ss";

	protected bool m_UseUTC;

	protected int m_Year;
	protected int m_Month;
	protected int m_Day;
	protected int m_Hour;
	protected int m_Minute;
	protected int m_Second;

	//! Compile error if protected
	private void CF_Date()
	{
	}

	static CF_Date Now(bool useUTC = false)
	{
		CF_Date date = new CF_Date();
		date.m_UseUTC = useUTC;

		if (date.m_UseUTC)
		{
			GetYearMonthDayUTC(date.m_Year, date.m_Month, date.m_Day);
			GetHourMinuteSecondUTC(date.m_Hour, date.m_Minute, date.m_Second);
		}
		else
		{
			GetYearMonthDay(date.m_Year, date.m_Month, date.m_Day);
			GetHourMinuteSecond(date.m_Hour, date.m_Minute, date.m_Second);
		}

		return date;
	}

	static CF_Date Epoch(int timestamp)
	{
		CF_Date date = new CF_Date();
		date.m_UseUTC = false;

		date.EpochToDate(timestamp);

		return date;
	}

	static CF_Date CreateDate(int year, int month, int day)
	{
		CF_Date date = new CF_Date();
		date.m_UseUTC = false;
		date.m_Year = year;
		date.m_Month = month;
		date.m_Day = day;
		GetHourMinuteSecond(date.m_Hour, date.m_Minute, date.m_Second);
		return date;
	}

	static CF_Date CreateTime(int hour, int minute, int second)
	{
		CF_Date date = new CF_Date();
		date.m_UseUTC = false;
		GetYearMonthDay(date.m_Year, date.m_Month, date.m_Day);
		date.m_Hour = hour;
		date.m_Minute = minute;
		date.m_Second = second;
		return date;
	}

	static CF_Date CreateDateTime(int year, int month, int day, int hour, int minute, int second)
	{
		CF_Date date = new CF_Date();
		date.m_UseUTC = false;
		date.m_Year = year;
		date.m_Month = month;
		date.m_Day = day;
		date.m_Hour = hour;
		date.m_Minute = minute;
		date.m_Second = second;
		return date;
	}

	//! UTILS
	static bool IsLeapYear(int year)
	{
		if (year % 400 == 0)
			return true;

		if (year % 100 == 0)
			return false;

		if (year % 4 == 0)
			return true;

		return false;
	}

	/**
	* Based on: https://en.wikipedia.org/wiki/Unix_time
	*
	* MAJOR NOTE:
	*	Timestamp start at Year 1970, if any functions / methods linked
	*	to Timestamp, be aware of using any date at least starting at this
	*	year.
	*
	* @param {int} year
	* @param {int} month
	* @param {int} day
	* @param {int} hour
	* @param {int} minute
	* @param {int} second
	*
	* @return Timestamp in m_Second
	*/
	static int Timestamp(int year, int month, int day, int hours, int minutes, int seconds)
	{
		if (year < 1970)
			return 0;

		bool isLeapYear = IsLeapYear(year);
		int timestamp = 0;

		for (int iYear = 1970; iYear < year; ++iYear)
		{
			if (IsLeapYear(iYear))
			{
				timestamp += 31622400;
			}
			else
			{
				timestamp += 31536000;
			}
		}

		for (int iMonth = 1; iMonth < month; iMonth++)
		{
			if (isLeapYear && iMonth == 2)
			{
				timestamp += 86400;
			}
			timestamp += DAYS_IN_MONTH[iMonth - 1] * 86400;
		}

		for (int iDay = 1; iDay < day; iDay++)
		{
			timestamp += 86400;
		}

		timestamp += hours * 3600;
		timestamp += minutes * 60;
		timestamp += seconds;
		return timestamp;
	}

	static void TimestampToDate(int timestamp, out int year, out int month, out int day, out int hours, out int minutes, out int seconds)
	{
		if (timestamp < 0)
			return;

		int iTimestamp = 0;
		iTimestamp = TimestampCalculYear(timestamp, year);
		iTimestamp = TimestampCalculMonth(iTimestamp, timestamp, year, month);
		iTimestamp = TimestampCalculDays(iTimestamp, timestamp, day);
		iTimestamp = TimestampCalculHours(iTimestamp, timestamp, hours);
		iTimestamp = TimestampCalculMinutes(iTimestamp, timestamp, minutes);
		iTimestamp = TimestampCalculSeconds(iTimestamp, timestamp, seconds);
	}

	protected static int TimestampCalculYear(int timestamp, out int year)
	{
		int iTimestamp = 0;
		year = 1970;

		while (iTimestamp < timestamp)
		{
			int yearTimestamp;

			if (IsLeapYear(year))
				yearTimestamp = 31622400;
			else
				yearTimestamp = 31536000;

			if (iTimestamp + yearTimestamp > timestamp)
				break;

			iTimestamp += yearTimestamp;
			year++;
		}

		return iTimestamp;
	}

	protected static int TimestampCalculMonth(int iTimestamp, int timestamp, int year, out int month)
	{
		bool isLeapYear = IsLeapYear(year);
		month = 0;

		while (iTimestamp < timestamp)
		{
			int monthTimestamp;
			if (isLeapYear && month == 1)
				monthTimestamp = 2505600;
			else
				monthTimestamp = DAYS_IN_MONTH[month] * 86400;

			if (iTimestamp + monthTimestamp > timestamp)
				break;

			iTimestamp += monthTimestamp;
			month++;
		}

		month++;
		return iTimestamp;
	}

	protected static int TimestampCalculDays(int iTimestamp, int timestamp, out int days)
	{
		days = 1;

		while (iTimestamp < timestamp)
		{
			if (iTimestamp + 86400 > timestamp)
				break;

			iTimestamp += 86400;
			days++;
		}

		return iTimestamp;
	}

	protected static int TimestampCalculHours(int iTimestamp, int timestamp, out int hours)
	{
		hours = 0;

		while (iTimestamp < timestamp)
		{
			if (iTimestamp + 3600 > timestamp)
				break;

			iTimestamp += 3600;
			hours++;
		}

		return iTimestamp;
	}

	protected static int TimestampCalculMinutes(int iTimestamp, int timestamp, out int minutes)
	{
		minutes = 0;

		while (iTimestamp < timestamp)
		{
			if (iTimestamp + 60 > timestamp)
				break;
			iTimestamp += 60;
			minutes++;
		}

		return iTimestamp;
	}

	protected static int TimestampCalculSeconds(int iTimestamp, int timestamp, out int seconds)
	{
		seconds = 0;

		while (iTimestamp < timestamp)
		{
			iTimestamp++;
			seconds++;
		}

		return iTimestamp;
	}

	int Compare(CF_Date other)
	{
		int timestamp1 = this.GetTimestamp();
		int timestamp2 = other.GetTimestamp();

		if (timestamp1 < timestamp2) {
			return -1;
		} else if (timestamp1 > timestamp2) {
			return 1;
		} else {
			return 0;
		}
	}

	void CalculateDifference(CF_Date other, out int hoursDiff, out int minutesDiff)
	{
		int timestamp1 = this.GetTimestamp();
		int timestamp2 = other.GetTimestamp();
		
		int timestampDiff = timestamp2 - timestamp1;
		hoursDiff = timestampDiff / 3600;
		minutesDiff = (timestampDiff % 3600) / 60;
	} 

	void EpochToDate(int value)
	{
		int iTimestamp;
		iTimestamp = TimestampCalculYear(value, m_Year);
		iTimestamp = TimestampCalculMonth(iTimestamp, value, m_Year, m_Month);
		iTimestamp = TimestampCalculDays(iTimestamp, value, m_Day);
		iTimestamp = TimestampCalculHours(iTimestamp, value, m_Hour);
		iTimestamp = TimestampCalculMinutes(iTimestamp, value, m_Minute);
		iTimestamp = TimestampCalculSeconds(iTimestamp, value, m_Second);
	}

	int DateToEpoch()
	{
		return Timestamp(m_Year, m_Month, m_Day, m_Hour, m_Minute, m_Second);
	}

	/**
	 * @return string with format: "month day, year hours:minutes:seconds"
	 */
	string DateToString()
	{
		string dateToString = GetFullMonthString();

		dateToString += " " + m_Day.ToStringLen(2);
		dateToString += ", " + m_Year;
		dateToString += " " + m_Hour.ToStringLen(2) + ":" + m_Minute.ToStringLen(2) + ":" + m_Second.ToStringLen(2);
		return dateToString;
	}

	override string GetDebugName()
	{
		return DateToString();
	}

	/** 
	 * @param format Supply a format such as "YYYY-MM-DD hh:mm:ss"
	 */
	string Format(string format)
	{
		FormatField(format, m_Year.ToString(), "Y");
		FormatField(format, m_Month.ToString(), "M");
		FormatField(format, m_Day.ToString(), "D");
		FormatField(format, m_Hour.ToString(), "h");
		FormatField(format, m_Minute.ToString(), "m");
		FormatField(format, m_Second.ToString(), "s");

		return format;
	}

	string ToString(string format)
	{
		return Format(format);
	}
	
	protected void FormatField(inout CF_String format, CF_String field, CF_String char)
	{		
		int index;
		int count = format.CountCharacter(char, index);
		
		int length = field.Length();
		
		if (length < count)
		{
			field = field.PadStringFront(count, "0");
		}

		if (field.Length() > count)
		{
			field = field.Substring(0, count);
		}
		
		format = format.SpliceString(index, field);
	}

	//! GETTERS
	bool IsUsingUTC()
	{
		return m_UseUTC;
	}

	int GetYear()
	{
		return m_Year;
	}

	int GetMonth()
	{
		return m_Month;
	}

	string GetFullMonthString()
	{
		if (0 < m_Month && m_Month < 13)
		{
			return MONTHS_FULL_NAME[m_Month - 1];
		}

		return "undefined";
	}

	string GetShortMonthString()
	{
		if (0 < m_Month && m_Month < 13)
		{
			return MONTHS_SHORT_NAME[m_Month - 1];
		}

		return "undefined";
	}

	//! @note 0 = sunday
	int GetDayOfWeek()
	{
		int y = m_Year;
		int d = m_Day;
		if (m_Month < 3)
			d += y--;
		else
			d += y - 2;
		return (23 * m_Month / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7;
	}

	int GetDay()
	{
		return m_Day;
	}

	int GetHours()
	{
		return m_Hour;
	}

	int GetMinutes()
	{
		return m_Minute;
	}

	int GetSeconds()
	{
		return m_Second;
	}

	int GetTimestamp()
	{
		return Timestamp(m_Year, m_Month, m_Day, m_Hour, m_Minute, m_Second);
	}

	//! SETTERS
	void SetDate(int year, int month, int day, int hours, int minutes, int seconds)
	{
		SetYear(year);
		SetMonth(month);
		SetDay(day);
		SetHours(hours);
		SetMinutes(minutes);
		SetSeconds(seconds);
	}

	void SetDate(int month, int day, int hours, int minutes, int seconds)
	{
		SetMonth(month);
		SetDay(day);
		SetHours(hours);
		SetMinutes(minutes);
		SetSeconds(seconds);
	}

	void SetDate(int day, int hours, int minutes, int seconds)
	{
		SetDay(day);
		SetHours(hours);
		SetMinutes(minutes);
		SetSeconds(seconds);
	}

	void SetDate(int hours, int minutes, int seconds)
	{
		SetHours(hours);
		SetMinutes(minutes);
		SetSeconds(seconds);
	}

	void SetDate(int minutes, int seconds)
	{
		SetMinutes(minutes);
		SetSeconds(seconds);
	}

	void SetYear(int year)
	{
		m_Year = year;
	}

	void SetMonth(int month)
	{
		if (0 < month && month < 13)
		{
			m_Month = month;
			if (m_Day > DAYS_IN_MONTH[m_Month - 1])
			{
				m_Day = DAYS_IN_MONTH[m_Month - 1];
			}
		}
		else
		{
			CF_Log.Error("Invalid SetMonth: " + month + ". Expected a value between 1 and 12!");
		}
	}

	void SetDay(int day)
	{
		int monthDays = DAYS_IN_MONTH[m_Month - 1] + 1;

		if (IsLeapYear(m_Year) && m_Month == 2)
		{
			monthDays++;
		}

		if (0 < day && day < monthDays)
		{
			m_Day = day;
		}
		else
		{
			CF_Log.Error("Invalid SetDay: " + day + ". Expected a value between 1 and " + DAYS_IN_MONTH[m_Month - 1] + "!");
		}
	}

	void SetHours(int hours)
	{
		if (-1 < hours && hours < 24)
		{
			m_Hour = hours;
		}
		else
		{
			CF_Log.Error("Invalid SetHours: " + hours + ". Expected a value between 0 and 23!");
		}
	}

	void SetMinutes(int minutes)
	{
		if (-1 < minutes && minutes < 60)
		{
			m_Minute = minutes;
		}
		else
		{
			CF_Log.Error("Invalid SetMinutes: " + minutes + ". Expected a value between 0 and 59!");
		}
	}

	void SetSeconds(int seconds)
	{
		if (-1 < seconds && seconds < 60)
		{
			m_Second = seconds;
		}
		else
		{
			CF_Log.Error("Invalid SetSeconds: " + seconds + ". Expected a value between 0 and 59!");
		}
	}
};
