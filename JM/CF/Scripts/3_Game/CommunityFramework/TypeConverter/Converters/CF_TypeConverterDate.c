[CF_RegisterTypeConverter(CF_TypeConverterDate)]
class CF_TypeConverterDate : CF_TypeConverterManaged
{
	private string m_Format = "YYYY-MM-DD hh:mm:ss";

	override void SetInt(int value)
	{
		CF_Date date = GetDate();
		if (!date) return;

		date.EpochToDate(value);
	}

	override int GetInt()
	{
		CF_Date date = GetDate();
		if (!date) return 0;

		return date.DateToEpoch();
	}

	override string GetString()
	{
		CF_Date date = GetDate();
		if (!date) return "1970-01-01 00:00:00";

		return date.ToString(m_Format);
	}

	override void SetString(string value)
	{
		CF_Date date = GetDate();
		if (!date) return;

		//date.StringToDate(value);
	}

	override typename GetType()
	{
		typename type = CF_Date;
		return type;
	}
	
	CF_Date GetDate()
	{
		return CF_Date.Cast(m_Value);
	}
};
