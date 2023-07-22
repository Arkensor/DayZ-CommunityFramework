class CF_VideoPath
{
	string Path;
	int SoundScene;
};

class CF_VideoWidget : CF_Widget
{
	reference string Path;
	reference string Command;
	reference string Subtitles;

	protected VideoWidget _VideoWidget;
	protected ref CF_VideoPath _Path = new CF_VideoPath();
	protected VideoCommand _Command;
	protected bool _Subtitles;

	override void GetProperties()
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_0(this, "GetProperties");
#endif

		super.GetProperties();

		AddProperty(Path, "Path");
		AddProperty(Command, "Command");
		AddProperty(Subtitles, "Subtitles");
	}

	override void OnWidgetScriptInit(Widget w)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_VideoWidget, w);
	}

	void OnView_Path(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_Path").Add(sender).Add(args);
#endif

		EnScript.SetClassVar(m_Model, Path, 0, _Path);
	}

	void OnModel_Path(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_Path").Add(sender).Add(args);
#endif

		EnScript.GetClassVar(m_Model, Path, 0, _Path);
		_VideoWidget.LoadVideo(_Path.Path, _Path.SoundScene);
	}

	void OnView_Command(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_Command").Add(sender).Add(args);
#endif

		EnScript.SetClassVar(m_Model, Command, 0, _Command);
	}

	void OnModel_Command(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_Command").Add(sender).Add(args);
#endif

		EnScript.GetClassVar(m_Model, Command, 0, _Command);
		_VideoWidget.Play(_Command);
	}

	void OnView_Subtitles(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_Subtitles").Add(sender).Add(args);
#endif

		EnScript.SetClassVar(m_Model, Subtitles, 0, _Subtitles);
	}

	void OnModel_Subtitles(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_Subtitles").Add(sender).Add(args);
#endif

		EnScript.GetClassVar(m_Model, Subtitles, 0, _Subtitles);
		_VideoWidget.DisableSubtitles(_Subtitles);
	}
};
