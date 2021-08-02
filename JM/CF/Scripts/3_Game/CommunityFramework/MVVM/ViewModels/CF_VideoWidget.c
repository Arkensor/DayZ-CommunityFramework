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
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(Path, "Path");
		AddProperty(Command, "Command");
		AddProperty(Subtitles, "Subtitles");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_VideoWidget, w);
	}

	void OnView_Path(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Path", "" + sender, args.ToStr());

		EnScript.SetClassVar(m_Model, Path, 0, _Path);
	}

	void OnModel_Path(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Path", "" + sender, args.ToStr());

		EnScript.GetClassVar(m_Model, Path, 0, _Path);
		_VideoWidget.LoadVideo(_Path.Path, _Path.SoundScene);
	}

	void OnView_Command(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Command", "" + sender, args.ToStr());

		EnScript.SetClassVar(m_Model, Command, 0, _Command);
	}

	void OnModel_Command(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Command", "" + sender, args.ToStr());

		EnScript.GetClassVar(m_Model, Command, 0, _Command);
		_VideoWidget.Play(_Command);
	}

	void OnView_Subtitles(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Subtitles", "" + sender, args.ToStr());

		EnScript.SetClassVar(m_Model, Subtitles, 0, _Subtitles);
	}

	void OnModel_Subtitles(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Subtitles", "" + sender, args.ToStr());

		EnScript.GetClassVar(m_Model, Subtitles, 0, _Subtitles);
		_VideoWidget.DisableSubtitles(_Subtitles);
	}

};
