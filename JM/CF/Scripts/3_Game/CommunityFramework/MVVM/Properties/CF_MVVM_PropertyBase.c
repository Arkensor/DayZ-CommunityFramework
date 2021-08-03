static ref CF_MVVM_PropertyBase g_CF_TypeConverterDefault = new CF_TypeConverterDefault();

static CF_MVVM_PropertyBase CF_MVVM_GetDefaultProperty()
{
	if (!g_CF_TypeConverterDefault) g_CF_TypeConverterDefault = new CF_MVVM_PropertyBase();
	return g_CF_TypeConverterDefault;
}

class CF_MVVM_PropertyBase : CF_TypeConverter
{
	bool IsDefault()
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
