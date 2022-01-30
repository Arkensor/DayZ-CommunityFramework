class CF_ModStoragePerformance
{
	ref set<string> m_Set = new set<string>();
	autoptr map<int, ref map<int, ref map<int, ref map<int, ref Param>>>> m_Map = new map<int, ref map<int, ref map<int, ref map<int, ref Param>>>>();

	void Run()
	{
		int numPerBlock = 32;
		int start;
		int time;

		int b1, b2, b3, b4;

		start = TickCount(0);
		for (b1 = 0; b1 < numPerBlock; b1++)
		{
			for (b2 = 0; b2 < numPerBlock; b2++)
			{
				for (b3 = 0; b3 < numPerBlock; b3++)
				{
					for (b4 = 0; b4 < numPerBlock; b4++)
					{
						Set_AddEntity(b1, b2, b3, b4);
					}
				}
			}
		}
		time = TickCount(start);

		Print("Set insert took " + time + "ticks");

		start = TickCount(0);
		for (b1 = 0; b1 < numPerBlock; b1++)
		{
			for (b2 = 0; b2 < numPerBlock; b2++)
			{
				for (b3 = 0; b3 < numPerBlock; b3++)
				{
					for (b4 = 0; b4 < numPerBlock; b4++)
					{
						Map_AddEntity(b1, b2, b3, b4);
					}
				}
			}
		}
		time = TickCount(start);

		Print("Map insert took " + time + "ticks");

		start = TickCount(0);
		for (b1 = 0; b1 < numPerBlock; b1++)
		{
			for (b2 = 0; b2 < numPerBlock; b2++)
			{
				for (b3 = 0; b3 < numPerBlock; b3++)
				{
					for (b4 = 0; b4 < numPerBlock; b4++)
					{
						Set_IsEntity(b1, b2, b3, b4);
					}
				}
			}
		}
		time = TickCount(start);

		Print("Set find took " + time + "ticks");

		start = TickCount(0);
		for (b1 = 0; b1 < numPerBlock; b1++)
		{
			for (b2 = 0; b2 < numPerBlock; b2++)
			{
				for (b3 = 0; b3 < numPerBlock; b3++)
				{
					for (b4 = 0; b4 < numPerBlock; b4++)
					{
						Map_IsEntity(b1, b2, b3, b4);
					}
				}
			}
		}
		time = TickCount(start);

		Print("Map find took " + time + "ticks");
	}

	void Set_AddEntity(int b1, int b2, int b3, int b4)
	{
		m_Set.Insert(string.Format("%1_%2_%3_%4", b1, b2, b3, b4));
	}

	void Map_AddEntity(int b1, int b2, int b3, int b4)
	{
		auto map_b1 =  m_Map[b1];
		if (!map_b1)
		{
			map_b1 = new map<int, ref map<int, ref map<int, ref Param>>>();
			m_Map[b1] = map_b1;
		}

		auto map_b2 = map_b1[b2];
		if (!map_b2)
		{
			map_b2 = new map<int, ref map<int, ref Param>>();
			map_b1[b2] = map_b2;
		}

		auto map_b3 = map_b2[b3];
		if (!map_b3)
		{
			map_b3 = new map<int, ref Param>();
			map_b2[b3] = map_b3;
		}

		auto val_b4 = map_b3[b4] 
		if (!val_b4)
		{
			val_b4 = new Param();
			map_b3[b4] = val_b4;
		}
	}

	bool Set_IsEntity(int b1, int b2, int b3, int b4)
	{
		return m_Set.Find(string.Format("%1_%2_%3_%4", b1, b2, b3, b4)) != -1;
	}

	bool Map_IsEntity(int b1, int b2, int b3, int b4)
	{
		auto map_b1 =  m_Map[b1];
		if (!map_b1)
		{
			return false;
		}

		auto map_b2 = map_b1[b2];
		if (!map_b2)
		{
			return false;
		}

		auto map_b3 = map_b2[b3];
		if (!map_b3)
		{
			return false;
		}

		auto val_b4 = map_b3[b4] 
		if (!val_b4)
		{
			return false;
		}

		return true;
	}

};
