/* Example:

void EOnSimulate(...)
{
	auto dbg_Helicopters = CF.Debugger.Get("Helicopters", this);

	dbg_Helicopters.Add("Position", GetPosition());
	dbg_Helicopters.Add("Orientation", GetOrientation());

	CF.Debugger.Display("Helicopters", this, "Velocity", GetVelocity(this));
}

*/

class CF_Debugger
{
	private autoptr array<ref CF_Debugger_Block> m_Blocks;

	void CF_Debugger()
	{
		m_Blocks = new array<ref CF_Debugger_Block>();
	}

	/*
		Retrieves the Debugger block if it exists based on the name and if specified, the target. 
		Creates a new block if no existing block was found.
	*/
	CF_Debugger_Block Get(string name, Object target = null)
	{
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
	array<CF_Debugger_Block> GetAll(string name = "")
	{
		array<CF_Debugger_Block> blocks = new array<CF_Debugger_Block>();

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
		Get(name, target).Set(key, text);
	}

	void Display(string name, Object target, string key, bool text)
	{
		Get(name, target).Set(key, text);
	}

	void Display(string name, Object target, string key, float text)
	{
		Get(name, target).Set(key, text);
	}

	void Display(string name, Object target, string key, vector text)
	{
		Get(name, target).Set(key, text);
	}

	void Display(string name, Object target, string key, string text)
	{
		Get(name, target).Set(key, text);
	}
};