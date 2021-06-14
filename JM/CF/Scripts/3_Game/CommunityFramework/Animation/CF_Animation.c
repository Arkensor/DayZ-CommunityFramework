class CF_Animation
{
	static const string VANILA_GRAPH_FILE = "dz\\anims\\workspaces\\player\\player_main\\player_main.agr";
	static const string VANILA_INSTANCE_FILE = "dz\\anims\\workspaces\\player\\player_main\\player_main.asi";

	static const string GRAPH_FILE = "$profile:player.agr";
	static const string INSTANCE_FILE = "$profile:player.asi";

	static void Init()
	{
		CF_Animation_Graph graph = new CF_Animation_Graph(VANILA_GRAPH_FILE);
		CF_Animation_Instance instance = new CF_Animation_Instance(VANILA_INSTANCE_FILE);

		int count = g_Game.ConfigGetChildrenCount( "CfgMods" );
		for (int i = 0; i < count; i++)
		{
			string mod_name;
			g_Game.ConfigGetChildName("CfgMods", i, mod_name);

			Print(mod_name);

			if (g_Game.ConfigIsExisting("CfgMods " + mod_name + " enfAnimSys"))
			{
				string graph_file;
				if (g_Game.ConfigGetText("CfgMods " + mod_name + " enfAnimSys graph", graph_file))
				{
					graph.Merge(new CF_Animation_Graph(graph_file));
				}

				string instance_file;
				if (g_Game.ConfigGetText("CfgMods " + mod_name + " enfAnimSys instance", instance_file))
				{
					instance.Merge(new CF_Animation_Instance(instance_file));
				}
			}
		}

		graph.Export();
		instance.Export();
	}
};