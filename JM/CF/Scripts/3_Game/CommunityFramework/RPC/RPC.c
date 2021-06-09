class CF_RPC
{
    //!Single static instance. Do not create with new or spawn - use CF.RPC for access instead.
    protected void CF_RPC();
    protected void ~CF_RPC();

    protected static ref map<string, Class> m_RegisteredInstances = new map<string, Class>();
    protected static ref map<string, ref CF_RPC_Whitelist> m_FunctionWhitelists = new map<string, ref CF_RPC_Whitelist>();
    protected static ref map<string, typename> m_FunctionParameterTypes = new map<string, typename>();

    static const int CF_RPC_SCRIPT_ID = 10043;

    static const PlayerIdentity SERVER = NULL;

    /**
     * @brief Registers a handler instance for the RPC receiving machine. A handler is a class instance which RPC functions will be invoked on.
     *        Alternatively you can inherit your handler class from CF_RPC_HandlerBase which registers it automatically.
     *
     * @code
     * constructor()
     * {
     *     CF.RPC.RegisterHandler(this);
     * }
     * @endcode
     *
     * @param instance  The handler instance to be registered.
     * @return bool     Returns true if successfully registered, false otherwise (see script log for details).
     */
	static bool RegisterHandler(Class instance)
	{
	    if(!instance)
	    {
            PrintFormat("[ERROR][CommunityFramework][RPC] Failed to register the handler instance %1. NULL-reference given as instance. See trace below:");
            DumpStack();
            return false;
	    }
        else if(m_RegisteredInstances.Contains(instance.ClassName()))
        {
            PrintFormat("[WARNING][CommunityFramework][RPC] Failed to register the handler instance %1. An instance for the handler type %2 was already registered. See trace below:", instance, instance.ClassName());
            DumpStack();
            return false;
        }

        m_RegisteredInstances.Set(instance.ClassName(), instance);

        return true;
	}

    /**
     * @brief Unregisters a handler instance. Alternatively you can inherit your handler class from CF_RPC_HandlerBase which unregisters it automatically.
     *
     * @code
     * destructor()
     * {
     *     CF.RPC.UnregisterHandler(this);
     * }
     * @endcode
     *
     * @param instance  The handler instance to be unregistered.
     * @return bool     Returns true if successfully unregistered, false otherwise (see script log for details).
     */
	static bool UnregisterHandler(Class instance)
	{
	    if(!instance)
	    {
            PrintFormat("[ERROR][CommunityFramework][RPC] Failed to unregister the handler instance %1. NULL-reference given as instance. See trace below:");
            DumpStack();
            return false;
	    }
	    if(m_RegisteredInstances.Contains(instance.ClassName()))
	    {
            PrintFormat("[WARNING][CommunityFramework][RPC] Failed to unregister the handler instance %1. The handler was not previously registered. See trace below:", instance, instance.ClassName());
            DumpStack();
            return false;
	    }

        m_RegisteredInstances.Remove(instance.ClassName());

        return true;
	}

    /**
     * @brief Registers the handler-function parameters to allow for automatic unpacking of the received RPC data.
     *        The PlayerIdentity of the RPC sender is automatically included as the FIRST parameter. Only specific ADDITIONAL parameters.
     *
     *        NOTE: Once parameters are registered, the default overload with Fnc(PlayerIdentity sender, ParamsReadContext ctx) will NOT work anymore.
     *              The function MUST match the parameters that are registered for it, or else you will see an error like: Cannot convert '<type>' to '<type>'...
     *
     * @code
     * constructor()
     * {
     *     CF.RPC.RegisterFunctionParameters(this, "MyAutomaticUnpackingFunction", new CF_RPC_Param3<int, array<string>, vector>);
     * }
     *
     * void MyAutomaticUnpackingFunction(PlayerIdentity sender, int integerValue, array<string> stringValues, vector vectorValue){}
     *
     * @endcode
     *
     * @param handlerInstance   Instance of the handler that contains the target function.
     * @param functionName      Name of the function that the parameters are being registered for.
     * @param parameters        Parameter declaration as CF_RPC_Param1...CF_RPC_Param7 instance. Note: You should use the default constructor of CF_RPC_Param - so no parameters.
     * @return bool             Returns true if successfully unregistered, false otherwise (see script log for details).
     */
    static bool RegisterFunctionParameters(Class handlerInstance, string functionName, CF_RPC_Param parameters)
    {
        auto hashKey = handlerInstance.ClassName() + "::" + functionName;

        if(m_FunctionParameterTypes.Contains(hashKey))
        {
            PrintFormat("[WARNING][CommunityFramework][RPC] Failed to register function parameters for %1. Already registered.\n               Existing parameters: %2. See trace below:", hashKey, m_FunctionParameterTypes.Get(hashKey));
            DumpStack();
            return false;
        }

        m_FunctionParameterTypes.Set(hashKey, parameters.Type());

        return true;
    }

    /**
     * @brief Get the whitelist for a specific type of handler.
     *
     * @code
     * MyHandlerType handler = GetHandlerInstanceFunction();
     * auto whitelist = CF.RPC.GetWhitelist(handler);
     * @endcode
     *
     * @param handlerType       Instance from which the handler type is derived.
     * @return CF_RPC_Whitelist Whitelist instance. NULL if handlerType was invalid.
     */
    static CF_RPC_Whitelist GetWhitelist(Class handlerType)
    {
        if(!handlerType) //Prevent invoke on NULL below
        {
            PrintFormat("[ERROR][CommunityFramework][RPC] Failed to access whitelist. handlerType was NULL. See trace below:");
            DumpStack();
            return NULL;
        }

        return _GetWhitelist(handlerType.ClassName());
    }

    /**
     * @brief Get the whitelist for a specific type of handler.
     *
     * @code
     * auto whitelist = CF.RPC.GetWhitelist(MyHandlerType);
     * @endcode
     *
     * @param handlerType       Typename of the handler.
     * @return CF_RPC_Whitelist Whitelist instance. NULL if handlerType was invalid.
     */
    static CF_RPC_Whitelist GetWhitelist(typename handlerType)
    {
        if(!handlerType) //Prevent invoke on NULL below
        {
            PrintFormat("[ERROR][CommunityFramework][RPC] Failed to access whitelist. handlerType was NULL. See trace below:");
            DumpStack();
            return NULL;
        }

        return _GetWhitelist(handlerType.ToString());
    }

    /**
     * @brief [Internal] Get the whitelist instance.
     * @param handlerType       Type(string) of the handler.
     * @return CF_RPC_Whitelist Whitelist instance. NULL if handlerType was invalid.
     */
    static CF_RPC_Whitelist _GetWhitelist(string handlerType)
    {
        if(!m_FunctionWhitelists.Contains(handlerType))
        {
            /*
                Inherited lookup required to match compile-time types with runtime.
                e.g. "PlayerBase" is the key but the runtime instance is SurvivorM_Jose. Without the check it would not match.

                The first matching instance is the result and will be cached for future RPCs of the handlerType.
            */
            auto handlerTypename = handlerType.ToType();

            if(!handlerTypename) return NULL;

            foreach(auto key, auto value : m_FunctionWhitelists)
            {
                if(handlerTypename.IsInherited(key.ToType()))
                {
                    //Store the alias for future requests
                    m_FunctionWhitelists.Set(handlerType, value);

                    //Return early with the same whitelist but under alias name
                    return value;
                }
            }

            m_FunctionWhitelists.Set(handlerType, new CF_RPC_Whitelist());
        }

        return m_FunctionWhitelists.Get(handlerType);
    }

    /**
     * @brief Prepares a new RPC send context, which data can be written to using Write() and that is transmitted using SendTo()
     *
     * @code
     * auto rpc = CF.RPC.Prepare("MyHandler", "MyFunction", true);
     * rpc.Write("My data");
     * rpc.SendTo(receiverIdentity1);
     * rpc.SendTo(receiverIdentity2);
     * @endcode
     *
     * @param handlerType       Type(string) of handler class on the receiving machine.
     * @param functionName      The name of the function that shall be invoked in the handler instance on the receiving machine.
     * @param guaranteed        Guaranteed RPC delivery. True = Will arrive eventually. False = Might be dropped after first attempt.
     * @return CF_RPC_Context   RPC write and send context.
     */
    static ref CF_RPC_Context Prepare(string handlerType, string functionName, bool guaranteed)
    {
        if(handlerType == "")
        {
            PrintFormat("[ERROR][CommunityFramework][RPC] Failed to prepare RPC context. handlerType was not set. See trace below:");
            DumpStack();
            return NULL;
        }

        if(functionName == "")
        {
            PrintFormat("[ERROR][CommunityFramework][RPC] Failed to prepare RPC context. functionName was not set. See trace below:");
            DumpStack();
            return NULL;
        }

        return CF_RPC_Context._Prepare(handlerType, functionName, guaranteed);
    }

    /**
     * @brief Prepares a new RPC send context, which data can be written to using Write() and that is transmitted using SendTo()
     *
     * @code
     * auto rpc = CF.RPC.Prepare(MyHandler, "MyFunction", true);
     * rpc.Write("My data");
     * rpc.SendTo(receiverIdentity1);
     * rpc.SendTo(receiverIdentity2);
     * @endcode
     *
     * @param handlerType       Typename of handler class on the receiving machine.
     * @param functionName      The name of the function that shall be invoked in the handler instance on the receiving machine.
     * @param guaranteed        Guaranteed RPC delivery. True = Will arrive eventually. False = Might be dropped after first attempt.
     * @return CF_RPC_Context   RPC write and send context. Will be NULL if the parameters were invalid.
     */
    static ref CF_RPC_Context Prepare(typename handlerType, string functionName, bool guaranteed)
    {
	    if(!handlerType) //Prevent invoke on NULL below
	    {
            PrintFormat("[ERROR][CommunityFramework][RPC] Failed to prepare RPC context. handlerType was NULL. See trace below:");
            DumpStack();
            return NULL;
	    }

        return CF_RPC_Context._Prepare(handlerType.ToString(), functionName, guaranteed);
    }

    /**
     * @brief Prepares a new RPC send context, which data can be written to using Write() and that is transmitted using SendTo()
     *
     * @code
     * Object myGlobalObject = GetGlobalObjectFunction();
     * auto rpc = CF.RPC.Prepare(myGlobalObject, "MyFunction", true);
     * rpc.Write("My data");
     * rpc.SendTo(receiverIdentity1);
     * rpc.SendTo(receiverIdentity2);
     * @endcode
     *
     * @param handlerObject     Global object (e.g. baked map objects, or entities spawned by the server globally) that the RPC shall be executed on.
     * @param functionName      The name of the function from the object instance that shall be invoked on the receiving machine.
     * @param guaranteed        Guaranteed RPC delivery. True = Will arrive eventually. False = Might be dropped after first attempt.
     * @return CF_RPC_Context   RPC write and send context.
     */
    static ref CF_RPC_Context Prepare(Object handlerObject, string functionName, bool guaranteed)
    {
        if(!handlerObject) //Prevent invoke on NULL below
        {
            PrintFormat("[ERROR][CommunityFramework][RPC] Failed to prepare RPC context. handlerObject was NULL. See trace below:");
            DumpStack();
            return NULL;
        }

        return CF_RPC_Context._Prepare(handlerObject.ClassName(), functionName, guaranteed, handlerObject);
    }

    /**
     * @brief [Internal] Handle incoming RPCs
     *
     * @return bool Returns if the RPC has been consumed by CF.
     */
    static bool _OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
    {
        if(rpc_type != CF_RPC_SCRIPT_ID) return false;

        string handlerType, functionName;

        if(ctx.Read(handlerType) && ctx.Read(functionName))
        {
            if(handlerType == "")
            {
                PrintFormat("[ERROR][CommunityFramework][RPC] Invalid value for parameter handlerType: '%1'. RPC ignored!", handlerType);
                return true;
            }

            if(functionName == "")
            {
                PrintFormat("[ERROR][CommunityFramework][RPC] Invalid value for parameter functionName: '%1'. RPC ignored!", functionName);
                return true;
            }

            Class invoke = NULL;

            if(target) //Direct execution on a known object instance
            {
                invoke = target;
            }
            else if(m_RegisteredInstances.Contains(handlerType)) //Lookup instance in registry
            {
                invoke = m_RegisteredInstances[handlerType];
            }
            else //Lookup inherited types in registry
            {
                /*
                    Inherited handlers will have the function the rpc is looking for, but might not match the class name.
                    The first matching instance is the result and will be cached for future RPCs of the handlerType.
                */
                auto handlerTypename = handlerType.ToType();

                if(handlerTypename)
                {
                    foreach(auto key, auto value : m_RegisteredInstances)
                    {
                        if(key.ToType().IsInherited(handlerTypename))
                        {
                            invoke = value;
                            m_RegisteredInstances.Set(handlerType, invoke);
                            break;
                        }
                    }
                }
            }

            if(invoke)
            {
                //Validate if the invoke is allowed
                auto whitelist = _GetWhitelist(handlerType);

                /*
                    If no whitelist is set, the default behavior for handler classes is to allow everything.
                    For a direct object or mission handler invoke - the default behavior is to not allow anything because objects always contain various function that should not be invokable.
                */
                if(whitelist && ((whitelist.IsEmpty() && !invoke.IsInherited(Object) && !invoke.IsInherited(Mission)) || whitelist.IsWhitelisted(functionName)))
                {
                    auto paramsHashKey = handlerType + "::" + functionName;

                    if(m_FunctionParameterTypes.Contains(paramsHashKey))
                    {
                        auto paramInstance = CF_RPC_Param.Cast(m_FunctionParameterTypes.Get(paramsHashKey).Spawn());

                        if(paramInstance && paramInstance.Deserializer(ctx))
                        {
                            paramInstance._SetSenderIdentity(sender);

                            g_Game.GameScript.CallFunctionParams(invoke, functionName, NULL, paramInstance);
                        }
                        else
                        {
                            PrintFormat("[ERROR][CommunityFramework][RPC] Could not unpack RPC data for %1 into %2", paramsHashKey, m_FunctionParameterTypes.Get(paramsHashKey));
                        }
                    }
                    else
                    {
                        g_Game.GameScript.CallFunctionParams(invoke, functionName, NULL, new Param2<ref PlayerIdentity, ref ParamsReadContext>(sender, ctx));
                    }
                }
                else
                {
                    //Note from Arkensor: Yes this must be one line, or else the format breaks in the scripts log.
                    PrintFormat("[ERROR][CommunityFramework][RPC] Function invoke '%1::%2' is not allowed. RPC ignored!\n               As the developer you can fix this by calling CF.RPC.GetWhitelist(%1).Add(\"%2\").", handlerType, functionName);
                }
            }
            else
            {
                PrintFormat("[ERROR][CommunityFramework][RPC] No instance found for handler type '%1' to execute function '%2'. RPC ignored!", handlerType, functionName);
            }
        }

        return true;
    }

    /**
     * @brief [Internal] CommunityFramework cleanup
     *
     * @return void
     */
    static void _Cleanup()
    {
        m_RegisteredInstances.Clear();
        delete m_RegisteredInstances;

        m_FunctionWhitelists.Clear();
        delete m_FunctionWhitelists;

        m_FunctionParameterTypes.Clear();
        delete m_FunctionParameterTypes;
    }
}
