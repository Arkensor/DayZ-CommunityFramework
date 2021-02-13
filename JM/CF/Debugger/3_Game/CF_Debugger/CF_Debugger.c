/* Example:

void EOnSimulate(...)
{
	auto dbg_Helicopters = CF.Debugger.Get("Helicopters", this);

	dbg_Helicopters.Add("Position", GetPosition());
	dbg_Helicopters.Add("Orientation", GetOrientation());

	CF.Debugger.Display("Helicopters", this, "Velocity", GetVelocity(this));
}

*/

static Class CF_Debugger_Get(string name, Object target = null)
{
	return CF.Debugger.Get(name, target);
}

static void CF_Debugger_Display(Class block, string key, int text)
{
	CF_Debugger_Block blc;
	if (!Class.CastTo(blc, block)) return;
	
	blc.Set(key, text);
}

static void CF_Debugger_Display(Class block, string key, bool text)
{
	CF_Debugger_Block blc;
	if (!Class.CastTo(blc, block)) return;
	
	blc.Set(key, text);
}

static void CF_Debugger_Display(Class block, string key, float text)
{
	CF_Debugger_Block blc;
	if (!Class.CastTo(blc, block)) return;
	
	blc.Set(key, text);
}

static void CF_Debugger_Display(Class block, string key, vector text)
{
	CF_Debugger_Block blc;
	if (!Class.CastTo(blc, block)) return;
	
	blc.Set(key, text);
}

static void CF_Debugger_Display(Class block, string key, Class text)
{
	CF_Debugger_Block blc;
	if (!Class.CastTo(blc, block)) return;
	
	blc.Set(key, text);
}

static void CF_Debugger_Display(Class block, string key, string text)
{
	CF_Debugger_Block blc;
	if (!Class.CastTo(blc, block)) return;
	
	blc.Set(key, text);
}

class CF_Debugger
{
	private autoptr array<ref CF_Debugger_Block> m_Blocks;
	private bool m_IsEnabled;

	void CF_Debugger()
	{
		m_Blocks = new array<ref CF_Debugger_Block>();

		m_IsEnabled = FileExist("$profile:CF_Debugger.txt");
		if (GetGame().IsServer() && GetGame().IsMultiplayer()) m_IsEnabled = false;
	}

	/*
		Retrieves the Debugger block if it exists based on the name and if specified, the target. 
		Creates a new block if no existing block was found.
	*/
	Class Get(string name, Object target = null)
	{
		if (!m_IsEnabled) return null;

		for (int i = 0; i < m_Blocks.Count(); i++)
		{
			if (target && !m_Blocks[i].IsTarget(target))
			{
				continue;
			}

			if (m_Blocks[i].GetName() == name)
			{
				return m_Blocks[i];
			}
		}

		auto block = new CF_Debugger_Block(name, target);
		m_Blocks.Insert(block);
		return block;
	}

	/*
		Get all blocks by name, if no name specified, get all blocks
	*/
	array<Class> GetAll(string name = "")
	{
		array<Class> blocks = new array<Class>();
		
		if (!m_IsEnabled) return blocks;

		for (int i = 0; i < m_Blocks.Count(); i++)
		{
			if (name == "" || m_Blocks[i].GetName() == name)
			{
				blocks.Insert(m_Blocks[i]);
			}
		}

		return blocks;
	}

	/*
		Destroys the block based on the name. If target specified, checks for target match before continuing. If target not specified but expected, retrieves first block under name.
	*/
	void Destroy(string name, Object target = null)
	{
		if (!m_IsEnabled) return;

		for (int i = 0; i < m_Blocks.Count(); i++)
		{
			if (target && !m_Blocks[i].IsTarget(target))
			{
				continue;
			}

			if (m_Blocks[i].GetName() == name)
			{
				m_Blocks.Remove(i);
				return;
			}
		}
	}

	void Display(string name, Object target, string key, int text)
	{
		CF_Debugger_Display(Get(name, target), key, text);
	}

	void Display(string name, Object target, string key, bool text)
	{
		CF_Debugger_Display(Get(name, target), key, text);
	}

	void Display(string name, Object target, string key, float text)
	{
		CF_Debugger_Display(Get(name, target), key, text);
	}

	void Display(string name, Object target, string key, vector text)
	{
		CF_Debugger_Display(Get(name, target), key, text);
	}

	void Display(string name, Object target, string key, Class text)
	{
		CF_Debugger_Display(Get(name, target), key, text);
	}

	void Display(string name, Object target, string key, string text)
	{
		CF_Debugger_Display(Get(name, target), key, text);
	}

	void Display(string name, string key, int text)
	{
		CF_Debugger_Display(Get(name, null), key, text);
	}

	void Display(string name, string key, bool text)
	{
		CF_Debugger_Display(Get(name, null), key, text);
	}

	void Display(string name, string key, float text)
	{
		CF_Debugger_Display(Get(name, null), key, text);
	}

	void Display(string name, string key, vector text)
	{
		CF_Debugger_Display(Get(name, null), key, text);
	}

	void Display(string name, string key, Class text)
	{
		CF_Debugger_Display(Get(name, null), key, text);
	}

	void Display(string name, string key, string text)
	{
		CF_Debugger_Display(Get(name, null), key, text);
	}
};