class CF_EventChatArgs : CF_EventArgs
{
	int Channel;
	string From;
	string Text;
	string ColorConfig;

	void CF_EventChatArgs(int channel, string from, string text, string colorConfig)
	{
		Channel = channel;
		From = from;
		Text = text;
		ColorConfig = colorConfig;
	}
};
