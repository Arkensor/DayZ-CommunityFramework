/* Example:

void EOnSimulate(...)
{
	auto dbg_Helicopters = CF.DebugUI.Get("Helicopters", this);

	dbg_Helicopters.Add("Position", GetPosition());
	dbg_Helicopters.Add("Orientation", GetOrientation());

	CF.DebugUI.Display("Helicopters", this, "Velocity", GetVelocity(this));
}

*/

class CF_DebugUI
{
	private autoptr array<ref CF_DebugUI_Block> m_Blocks;
	private bool m_IsEnabled;

	void CF_DebugUI()
	{
		m_Blocks = new array<ref CF_DebugUI_Block>();

		m_IsEnabled = IsCLIParam("CFDebugUI");
		if (GetGame().IsServer() && GetGame().IsMultiplayer()) m_IsEnabled = false;
	}

	/*
		Retrieves the DebugUI block if it exists based on the name and if specified, the target. 
		Creates a new block if no existing block was found.

		@note returning 'Class' as CF may pre-process CF_DebugUI_* out if not running Diag exe in the future
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

		auto block = new CF_DebugUI_Block(name, target);
		m_Blocks.Insert(block);
		return block;
	}

	/*
		Get all blocks by name, if no name specified, gets all blocks. Doesn't create a block if none was found for the name.

		@note returning 'Class' as CF may pre-process CF_DebugUI_* out if not running Diag exe in the future
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

	void SwapBuffer(string name, Object target)
	{
		CF_DebugUI_Block blc;
		if (!Class.CastTo(blc, Get(name, target))) return;
		
		blc.SwapBuffer();
	}

	void Set(string name, Object target, string key, int text)
	{
		CF_DebugUI_Block blc;
		if (!Class.CastTo(blc, Get(name, target))) return;
		
		blc.Set(key, text);
	}

	void Set(string name, Object target, string key, bool text)
	{
		CF_DebugUI_Block blc;
		if (!Class.CastTo(blc, Get(name, target))) return;
		
		blc.Set(key, text);
	}

	void Set(string name, Object target, string key, float text)
	{
		CF_DebugUI_Block blc;
		if (!Class.CastTo(blc, Get(name, target))) return;
		
		blc.Set(key, text);
	}

	void Set(string name, Object target, string key, vector text)
	{
		CF_DebugUI_Block blc;
		if (!Class.CastTo(blc, Get(name, target))) return;
		
		blc.Set(key, text);
	}

	void Set(string name, Object target, string key, Class text)
	{
		CF_DebugUI_Block blc;
		if (!Class.CastTo(blc, Get(name, target))) return;
		
		blc.Set(key, text);
	}

	void Set(string name, Object target, string key, string text)
	{
		CF_DebugUI_Block blc;
		if (!Class.CastTo(blc, Get(name, target))) return;
		
		blc.Set(key, text);
	}

	void Set(string name, string key, int text)
	{
		CF_DebugUI_Block blc;
		if (!Class.CastTo(blc, Get(name, null))) return;
		
		blc.Set(key, text);
	}

	void Set(string name, string key, bool text)
	{
		CF_DebugUI_Block blc;
		if (!Class.CastTo(blc, Get(name, null))) return;
		
		blc.Set(key, text);
	}

	void Set(string name, string key, float text)
	{
		CF_DebugUI_Block blc;
		if (!Class.CastTo(blc, Get(name, null))) return;
		
		blc.Set(key, text);
	}

	void Set(string name, string key, vector text)
	{
		CF_DebugUI_Block blc;
		if (!Class.CastTo(blc, Get(name, null))) return;
		
		blc.Set(key, text);
	}

	void Set(string name, string key, Class text)
	{
		CF_DebugUI_Block blc;
		if (!Class.CastTo(blc, Get(name, null))) return;
		
		blc.Set(key, text);
	}

	void Set(string name, string key, string text)
	{
		CF_DebugUI_Block blc;
		if (!Class.CastTo(blc, Get(name, null))) return;
		
		blc.Set(key, text);
	}
};
