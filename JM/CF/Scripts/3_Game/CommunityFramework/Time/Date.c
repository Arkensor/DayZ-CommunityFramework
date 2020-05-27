class Date
{
    static const string MONTHS_FULL_NAME[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    static const string MONTHS_SHORT_NAME[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    static const int DAYS_IN_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    protected bool m_UseUTC;
    protected int m_Year;
    protected int m_Month;
    protected int m_Day;
    protected int m_Hours;
    protected int m_Minutes;
    protected int m_Seconds;

    void Date( bool useUTC = true )
    {
        m_UseUTC = useUTC;

        if ( useUTC )
        {
            GetYearMonthDayUTC( m_Year, m_Month, m_Day );
            GetHourMinuteSecondUTC( m_Hours, m_Minutes, m_Seconds );
        }
        else
        {
            GetYearMonthDay( m_Year, m_Month, m_Day );
            GetHourMinuteSecond( m_Hours, m_Minutes, m_Seconds );
        }
    }

    /** Utils */
    static bool IsLeapYear( int year )
    {
        if ( year % 400 == 0 )
		{
            return true;
		}
        if ( year % 100 == 0 )
		{
            return false;
		}
        if ( year % 4 == 0 )
		{
            return true;
		}
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
	static int Timestamp( int year, int month, int day, int hours, int minutes, int seconds )
	{
		bool isLeapYear = IsLeapYear( year );
        int timestamp = 0;

        for ( int iYear = 1970; iYear < year; ++iYear )
        {
            if ( IsLeapYear(iYear) )
			{
                timestamp += 31622400;
			}
            else
			{
                timestamp += 31536000;
			}
        }
        for ( int iMonth = 1; iMonth < month; iMonth++ )
        {
            if ( isLeapYear && iMonth == 2 )
			{
                timestamp += 86400;
			}
            timestamp += DAYS_IN_MONTH[ iMonth - 1 ] * 86400;
        }
        for ( int iDay = 1; iDay < day; iDay++ )
        {
            timestamp += 86400;
        }
        timestamp += hours * 3600;
        timestamp += minutes * 60;
        timestamp += seconds;
        return timestamp;
	}

    static void TimestampToDate( int timestamp, out int year, out int month, out int day, out int hours, out int minutes, out int seconds )
    {
        int iTimestamp = 0;

        iTimestamp = TimestampCalculYear( timestamp, year );
        iTimestamp = TimestampCalculMonth( iTimestamp, timestamp, year, month );
        iTimestamp = TimestampCalculDays( iTimestamp, timestamp, day );
        iTimestamp = TimestampCalculHours( iTimestamp, timestamp, hours );
        iTimestamp = TimestampCalculMinutes( iTimestamp, timestamp, minutes );
        iTimestamp = TimestampCalculSeconds( iTimestamp, timestamp, seconds );
    }

    static int TimestampCalculYear( int timestamp, out int year )
    {
        int iTimestamp = 0;
        year = 1970;

        while ( iTimestamp < timestamp )
        {
			int yearTimestamp;

            if ( IsLeapYear( year ) )
			{
                yearTimestamp = 31622400;
			}
			else
			{
				yearTimestamp = 31536000;
			}
			if ( iTimestamp + yearTimestamp > timestamp ) break;
			iTimestamp += yearTimestamp;
            year++;
        }
        return iTimestamp;
    }

	static int TimestampCalculMonth( int iTimestamp, int timestamp, int year, out int month )
    {
        bool isLeapYear = IsLeapYear( year );
        month = 0;

        while ( iTimestamp < timestamp )
        {
			int monthTimestamp;
			if ( isLeapYear && month == 1 )
			{
				monthTimestamp = 2505600;
			}
			else
			{
				monthTimestamp = DAYS_IN_MONTH[ month ] * 86400;
			}
			if ( iTimestamp + monthTimestamp > timestamp ) break;
			iTimestamp += monthTimestamp;
            month++;
        }
		month++;
        return iTimestamp;
    }

    static int TimestampCalculDays( int iTimestamp, int timestamp, out int days )
    {
        days = 1;

        while ( iTimestamp < timestamp )
        {
            if ( iTimestamp + 86400 > timestamp ) break;
            iTimestamp += 86400;
            days++;
        }
        return iTimestamp;
    }

    static int TimestampCalculHours( int iTimestamp, int timestamp, out int hours )
    {
        hours = 0;

        while ( iTimestamp < timestamp )
        {
            if ( iTimestamp + 3600 > timestamp ) break;
            iTimestamp += 3600;
            hours++;
        }
        return iTimestamp;
    }

    static int TimestampCalculMinutes( int iTimestamp, int timestamp, out int minutes )
    {
        minutes = 0;

        while ( iTimestamp < timestamp )
        {
            if ( iTimestamp + 60 > timestamp ) break;
            iTimestamp += 60;
            minutes++;
        }
        return iTimestamp;
    }

    static int TimestampCalculSeconds( int iTimestamp, int timestamp, out int seconds )
    {
        seconds = 0;

        while ( iTimestamp < timestamp )
        {
            iTimestamp++;
            seconds++;
        }
        return iTimestamp;
    }

	/**
	*	@return {string} Date with format: "month day, year hours:minutes:seconds"
	*
	*	Note:
	*		0 in front of numbers are not includes.
	*/
	string DateToString()
	{
		string dateToString = GetFullMonthString();

		dateToString += " " + m_Day;
		dateToString += ", " + m_Year;
		dateToString += " " + m_Hours + ":" + m_Minutes + ":" + m_Seconds;
		return dateToString;
	}

    /** Getters */
    bool isUsingUTC()
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
        if ( 0 < m_Month && m_Month < 13 )
		{
            return MONTHS_FULL_NAME[ m_Month - 1 ];
		}
        return "undefined";
    }

    string GetShortMonthString()
    {
        if ( 0 < m_Month && m_Month < 13 )
		{
            return MONTHS_SHORT_NAME[ m_Month - 1 ];
		}
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
		return Timestamp( m_Year, m_Month, m_Day, m_Hours, m_Minutes, m_Seconds );
	}

    /** Setters */
    void SetDate( int year, int month, int day, int hours, int minutes, int seconds )
    {
        SetYear( year );
        SetMonth( month );
        SetDay( day );
        SetHours( hours );
        SetMinutes( minutes );
        SetSeconds( seconds );
    }

    void SetDate( int month, int day, int hours, int minutes, int seconds )
    {
        SetMonth( month );
        SetDay( day );
        SetHours( hours );
        SetMinutes( minutes );
        SetSeconds( seconds );
    }

    void SetDate( int day, int hours, int minutes, int seconds )
    {
        SetDay( day );
        SetHours( hours );
        SetMinutes( minutes );
        SetSeconds( seconds );
    }

    void SetDate( int hours, int minutes, int seconds )
    {
        SetHours( hours );
        SetMinutes( minutes );
        SetSeconds( seconds );
    }

    void SetDate( int minutes, int seconds )
    {
        SetMinutes( minutes );
        SetSeconds( seconds );
    }

    void SetYear( int year )
    {
        m_Year = year;
    }

    void SetMonth( int month )
    {
        if ( 0 < month && month < 13 )
		{
            m_Month = month;
			if ( m_Day > DAYS_IN_MONTH[ m_Month - 1 ] )
			{
				m_Day = DAYS_IN_MONTH[ m_Month - 1 ];
			}
		}
		else
		{
			GetLogger().Err("Invalid SetMonth: " + month + ". Expected a value between 1 and 12", "Date", false);
		}
    }

    void SetDay( int day )
    {
        int monthDays = DAYS_IN_MONTH[ m_Month - 1 ] + 1;

        if ( IsLeapYear( m_Year ) && m_Month == 2 )
		{
            monthDays++;
		}
        if ( 0 < day && day < monthDays )
		{
            m_Day = day;
		}
		else
		{
			GetLogger().Err( "Invalid SetDay: " + day + ". Expected a value between 1 and " + DAYS_IN_MONTH[ m_Month - 1 ], "Date", false );
		}
    }

    void SetHours( int hours )
    {
        if ( -1 < hours && hours < 24 )
		{
            m_Hours = hours;
		}
		else
		{
			GetLogger().Err( "Invalid SetHours: " + hours + ". Expected a value between 0 and 23", "Date", false );
		}
    }

    void SetMinutes( int minutes )
    {
        if ( -1 < minutes && minutes < 60 )
		{
            m_Minutes = minutes;
		}
		else
		{
			GetLogger().Err( "Invalid SetMinutes: " + minutes + ". Expected a value between 0 and 59", "Date", false );
		}
    }

    void SetSeconds( int seconds )
    {
        if ( -1 < seconds && seconds < 60 )
		{
            m_Seconds = seconds;
		}
		else
		{
			GetLogger().Err( "Invalid SetSeconds: " + seconds + ". Expected a value between 0 and 59", "Date", false );
		}
    }
};