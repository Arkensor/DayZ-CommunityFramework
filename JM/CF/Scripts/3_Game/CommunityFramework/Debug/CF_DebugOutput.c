class CF_DebugOutput : CF_Model
{
	void CF_DebugOutput(CF_Debug parent, string name);

	void SetName(string name);

	void Add(string value);

	void Add(string name, int value);

	void Add(string name, bool value);

	void Add(string name, float value);

	void Add(string name, vector value);

	void Add(string name, string value);

	void IncrementTab();

	void DecrementTab();

	void ResetBuffer();

	void PushBuffer();
};
