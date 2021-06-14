class CF_Animation_Graph
{
	string m_Path;

	ref array<string> m_Data = new array<string>();

	void CF_Animation_Graph(string path)
	{
		m_Path = path;
		Load();
	}

	void Load()
	{
		FileHandle file = OpenFile(m_Path, FileMode.READ);
        if (!file) return;
		
		string line_content;
		while (FGets(file, line_content) != -1)
		{
			m_Data.Insert(line_content);
		}
		
		CloseFile(file);
	}

	void Export()
	{
        FileHandle file = OpenFile(CF_Animation.GRAPH_FILE, FileMode.WRITE);
        if (!file) return;

		for (int i = 0; i < m_Data.Count(); i++)
			FPrintln(file, m_Data[i]);
		
		CloseFile(file);
	}

	void Merge(CF_Animation_Graph other)
	{

	}
};