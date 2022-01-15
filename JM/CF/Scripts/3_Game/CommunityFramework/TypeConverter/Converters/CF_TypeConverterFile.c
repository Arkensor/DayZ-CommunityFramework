[CF_RegisterTypeConverter(CF_TypeConverterFile)]
class CF_TypeConverterFile : CF_TypeConverterClass
{
	override string GetString()
	{
		CF_File file = GetFile();
		if (!file)
		{
			return "";
		}
		
		return file.GetFileName();
	}

	override void SetString(string value)
	{
		CF_File file = GetFile();
		if (!file)
		{
			return;
		}

		file.Rename(value);
	}

	override typename GetType()
	{
		typename type = CF_File;
		return type;
	}
	
	CF_File GetFile()
	{
		return CF_File.Cast(m_Value);
	}
};
