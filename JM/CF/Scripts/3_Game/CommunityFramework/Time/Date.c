class Date
{
    static const string m_MonthsFullName[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    static const string m_MonthsShortName[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    static const int m_DaysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    protected bool m_useUTC;
    protected int m_Year;
    protected int m_Month;
    protected int m_Day;
    protected int m_Hours;
    protected int m_Minutes;
    protected int m_Seconds;

    void Date(bool useUTC = true)
    {
        m_useUTC = useUTC;

        if (useUTC)
        {
            GetYearMonthDayUTC(m_Year, m_Month, m_Day);
            GetHourMinuteSecondUTC(m_Hours, m_Minutes, m_Seconds);
        }
        else
        {
            GetYearMonthDay(m_Year, m_Month, m_Day);
            GetHourMinuteSecond(m_Hours, m_Minutes, m_Seconds);
        }
    }

    /** Utils */
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
     * @param {int} year
     * @param {int} month
     * @param {int} day
     * @param {int} hours
     * @param {int} minutes
     * @param {int} seconds
     * 
     * @return Timestamp in Seconds
     */
	static int Timestamp(int year, int month, int day, int hours, int minutes, int seconds)
	{
		bool isLeapYear = IsLeapYear(year);
        int timestamp = 0;

        for (int iYear = 1970; iYear < year; ++iYear)
        {
            if (IsLeapYear(iYear))
                timestamp += 86400 * 366;
            else
                timestamp += 86400 * 365;
        }
        for (int iMonth = 1; iMonth < month; iMonth++)
        {
            if (isLeapYear && iMonth == 2)
                timestamp += 86400;
            timestamp += m_DaysInMonth[iMonth - 1] * 86400;
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
        int iTimestamp = 0;
        bool isLeapYear = false;

        iTimestamp = TimestampCalculYear(timestamp, year);
        iTimestamp = TimestampCalculMonth(iTimestamp, timestamp, year, month);
        iTimestamp = TimestampCalculDays(iTimestamp, timestamp, day);
        iTimestamp = TimestampCalculHours(iTimestamp, timestamp, hours);
        iTimestamp = TimestampCalculMinutes(iTimestamp, timestamp, minutes);
        iTimestamp = TimestampCalculSeconds(iTimestamp, timestamp, seconds);
    }

    static int TimestampCalculYear(int timestamp, out int year)
    {
        int iTimestamp = 0;
        year = 1970;

        while (iTimestamp < timestamp)
        {
            if (IsLeapYear(year))
            {
				if ( iTimestamp + 31622400 < timestamp ) break;
                iTimestamp += 31622400;
            }
			else
			{
				if ( iTimestamp + 31536000 < timestamp ) break;
				iTimestamp += 31536000;
			}
            year++;
        }
        return iTimestamp;
    }

	static int TimestampCalculMonth(int iTimestamp, int timestamp, int year, out int month)
    {
        bool isLeapYear = IsLeapYear(year);
        month = 0;

        while (iTimestamp < timestamp)
        {
            if ((iTimestamp + m_DaysInMonth[month - 1] * 86400) > timestamp) return iTimestamp;
            iTimestamp += m_DaysInMonth[month - 1] * 86400;
            if (isLeapYear && month == 2)
            {
                if ((iTimestamp + 86400) > timestamp) return iTimestamp;
                iTimestamp += 86400;
            }
            month++;
        }
        return iTimestamp;
    }

    static int TimestampCalculDays(int iTimestamp, int timestamp, out int days)
    {
        days = 1;

        while (iTimestamp < timestamp)
        {
            if ((iTimestamp + 86400) < timestamp) return iTimestamp;
            iTimestamp += 86400;
            days++;
        }
        return iTimestamp;
    }

    static int TimestampCalculHours(int iTimestamp, int timestamp, out int hours)
    {
        hours = 0;

        while (iTimestamp < timestamp)
        {
            if ((iTimestamp + 3600) < timestamp) return iTimestamp;
            iTimestamp += 3600;
            hours++;
        }
        return iTimestamp;
    }

    static int TimestampCalculMinutes(int iTimestamp, int timestamp, out int minutes)
    {
        minutes = 0;

        while (iTimestamp < timestamp)
        {
            if ((iTimestamp + 60) < timestamp) return iTimestamp;
            iTimestamp += 60;
            minutes++;
        }
        return iTimestamp;
    }

    static int TimestampCalculSeconds(int iTimestamp, int timestamp, out int seconds)
    {
        seconds = 0;

        while (iTimestamp < timestamp)
        {
            iTimestamp++;
            seconds++;
        }
        return iTimestamp;
    }
	
	string DateToString()
	{
		string dateToString = GetFullMonthString();

		dateToString += " " + m_Day;
		dateToString += ", " + m_Year;
		dateToString += " " + m_Hours + ":" + m_Minutes + ":" + m_Seconds;
		return dateToString;
	}

    /** Getters */
    bool UseUTC()
    {
        return m_useUTC;
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
            return m_MonthsFullName[m_Month - 1];
        return "undefined";
    }

    string GetShortMonthString()
    {
        if (0 < m_Month && m_Month < 13)
            return m_MonthsShortName[m_Month - 1];
        return "undefined";
    }

    int GetDay()
    {
        return m_Day;
    }

    int GetHours()
    {
        return m_Hours;
    }

    int GetMinutes()
    {
        return m_Minutes;
    }

    int GetSeconds()
    {
        return m_Seconds;
    }
	
	int GetTimestamp()
	{
		return Timestamp(m_Year, m_Month, m_Day, m_Hours, m_Minutes, m_Seconds);
	}

    /** Setters */
    void SetDate(int year, int month, int day, int hours, int minutes, int seconds)
    {
        m_Year = year;
        m_Month = month;
        m_Day = day;
        m_Hours = hours;
        m_Minutes = minutes;
        m_Seconds = seconds;
    }

    void SetDate(int month, int day, int hours, int minutes, int seconds)
    {
        m_Month = month;
        m_Day = day;
        m_Hours = hours;
        m_Minutes = minutes;
        m_Seconds = seconds;
    }

    void SetDate(int day, int hours, int minutes, int seconds)
    {
        m_Day = day;
        m_Hours = hours;
        m_Minutes = minutes;
        m_Seconds = seconds;
    }

    void SetDate(int hours, int minutes, int seconds)
    {
        m_Hours = hours;
        m_Minutes = minutes;
        m_Seconds = seconds;
    }

    void SetDate(int minutes, int seconds)
    {
        m_Minutes = minutes;
        m_Seconds = seconds;
    }

    void SetYear(int year)
    {
        m_Year = year;
    }

    void SetMonth(int month)
    {
        if (-1 < month && month < 13)
            m_Month = month;
    }

    void SetDay(int day)
    {
        int monthDays = m_DaysInMonth[m_Month] + 1;

        if (IsLeapYear(m_Year) && m_Month == 1)
            monthDays++;
        if (0 < day && day < monthDays)
            m_Day = day;
    }

    void SetHours(int hours)
    {
        if (-1 < hours && hours < 24)
            m_Hours = hours;
    }

    void SetMinutes(int minutes)
    {
        if (-1 < minutes && minutes < 60)
            m_Minutes = minutes;
    }

    void SetSeconds(int seconds)
    {
        if (-1 < seconds && seconds < 60)
            m_Seconds = seconds;
    }
};