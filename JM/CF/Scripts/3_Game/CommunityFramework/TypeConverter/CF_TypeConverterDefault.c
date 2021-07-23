static ref CF_TypeConverterDefault g_CF_TypeConverterDefault = new CF_TypeConverterDefault();

static CF_TypeConverterDefault CF_GetDefaultTC()
{
	if (!g_CF_TypeConverterDefault) g_CF_TypeConverterDefault = new CF_TypeConverterDefault();
	return g_CF_TypeConverterDefault;
}

class CF_TypeConverterDefault : CF_TypeConverter
{
	override bool IsDefault()
	{
		return true;
	}

	override void FromVariable(Class instance, string variable)
	{
	}

	override void ToVariable(Class instance, string variable)
	{
	}
};