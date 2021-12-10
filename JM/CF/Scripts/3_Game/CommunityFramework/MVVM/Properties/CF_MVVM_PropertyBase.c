static ref CF_MVVM_PropertyBase g_CF_MVVM_DefaultProperty = new CF_MVVM_PropertyBase();

static CF_MVVM_PropertyBase CF_MVVM_GetDefaultProperty()
{
	#ifdef CF_TRACE_ENABLED
	auto trace = CF_Trace_0("CF_MVVM_GetDefaultProperty");
	#endif

	if (!g_CF_MVVM_DefaultProperty) g_CF_MVVM_DefaultProperty = new CF_MVVM_PropertyBase();
	return g_CF_MVVM_DefaultProperty;
}

class CF_MVVM_PropertyBase : CF_TypeConverterBase
{
	bool IsDefault()
	{
		return true;
	}

	override bool Read(Class instance, string variableName)
	{
	}

	override bool Write(Class instance, string variableName)
	{
	}
};
