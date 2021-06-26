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
	protected ref CF_VideoPath _Path;
	protected VideoCommand _Command;
	protected bool _Subtitles;

	override void GetProperties()
	{
		super.GetProperties();
		
		AddProperty(Path, "Path");
		AddProperty(Command, "Command");
		AddProperty(Subtitles, "Subtitles");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_VideoWidget, w);
	}

	void OnView_Path(CF_ModelBase model, CF_Event evt)
	{
		EnScript.SetClassVar(model, Path, 0, _Path);
	}

	void OnModel_Path(CF_ModelBase model, CF_Event evt)
	{
		EnScript.GetClassVar(model, Path, 0, _Path);
		_VideoWidget.LoadVideo(_Path.Path, _Path.SoundScene);
	}

	void OnView_Command(CF_ModelBase model, CF_Event evt)
	{
		EnScript.SetClassVar(model, Command, 0, _Command);
	}

	void OnModel_Command(CF_ModelBase model, CF_Event evt)
	{
		EnScript.GetClassVar(model, Command, 0, _Command);
		_VideoWidget.Play(_Command);
	}

	void OnView_Subtitles(CF_ModelBase model, CF_Event evt)
	{
		EnScript.SetClassVar(model, Subtitles, 0, _Subtitles);
	}

	void OnModel_Subtitles(CF_ModelBase model, CF_Event evt)
	{
		EnScript.GetClassVar(model, Subtitles, 0, _Subtitles);
		_VideoWidget.DisableSubtitles(_Subtitles);
	}

};
