class CF_RPC_Whitelist
{
	protected ref set<string> m_FunctionWhitelist;

	void CF_RPC_Whitelist()
	{
	    m_FunctionWhitelist = new set<string>();
	}

    /**
     * @brief Check if a given function is whitelisted to be executed via RPC.
     *
     * @code
     * bool rpcExecutionAllowed = CF.RPC.GetWhitelist(MyHandlerType).IsWhitelisted("MyFirstFunction");
     * @endcode
     *
     * @param functionName  Name of the function to be checked.
     * @return bool         Returns true if the function is whitelisted.
     */
	bool IsWhitelisted(string functionName)
	{
	    return m_FunctionWhitelist.Find(functionName) >= 0;
	}

    /**
     * @brief Determine whether the whitelist has any entries or not.
     *
     * @code
     * bool whitelistIsEmpty = CF.RPC.GetWhitelist(MyHandlerType).IsEmpty();
     * @endcode
     *
     * @return bool Returns true if the whitelist is empty.
     */
    bool IsEmpty()
    {
        return m_FunctionWhitelist.Count() == 0;
    }

    /**
     * @brief Whitelist a function.
     *
     * @code
     * CF.RPC.GetWhitelist(MyHandlerType).Add("MyFirstFunction");
     * @endcode
     *
     * @param functionName Name of the function to be added.
     * @return void
     */
	void Add(string functionName)
	{
	    m_FunctionWhitelist.Insert(functionName);
	}

    /**
     * @brief Whitelist multiple functions.
     *
     * @code
     * CF.RPC.GetWhitelist(MyHandlerType).AddArray({"MyFirstFunction", "MySecondFunction"});
     * @endcode
     *
     * @param functionNames Array of function names to be added.
     * @return void
     */
    void AddArray(array<string> functionNames)
    {
        foreach(auto functionName: functionNames)
        {
            Add(functionName);
        }
    }

    /**
     * @brief Remove a function from the whitelist.
     *
     * @code
     * CF.RPC.GetWhitelist(MyHandlerType).Remove("MyFirstFunction");
     * @endcode
     *
     * @param functionName Name of the function to be removed.
     * @return void
     */
	void Remove(string functionName)
	{
        auto idx = m_FunctionWhitelist.Find(functionName);

        if(idx >= 0) m_FunctionWhitelist.Remove(idx);
	}

    /**
     * @brief Remove multiple functions from the whitelist.
     *
     * @code
     * CF.RPC.GetWhitelist(MyHandlerType).RemoveArray({"MyFirstFunction", "MySecondFunction"});
     * @endcode
     *
     * @param functionNames Array of function names to be removed.
     * @return void
     */
    void RemoveArray(array<string> functionNames)
    {
        foreach(auto functionName: functionNames)
        {
            Remove(functionName);
        }
    }
}
