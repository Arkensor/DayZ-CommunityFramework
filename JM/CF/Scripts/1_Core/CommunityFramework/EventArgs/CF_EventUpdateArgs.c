class CF_EventUpdateArgs : CF_EventArgs
{
	float DeltaTime;

	void CF_EventUpdateArgs(float deltaTime = 0)
	{
		DeltaTime = deltaTime;
	}
};
