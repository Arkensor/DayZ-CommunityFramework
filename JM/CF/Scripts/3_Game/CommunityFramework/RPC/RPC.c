class CF_RPC
{
    //!Single static instance. Do not create with new or spawn - use CF.RPC for access instead.
    protected void CF_RPC();
    protected void ~CF_RPC();

    protected static ref map<string, Class> m_RegisteredInstances = new map<string, Class>();

    static const int CF_RPC_SCRIPT_ID = 10043;

    static const PlayerIdentity SERVER = NULL;

    /**
     * @brief Registers a handler instance for the RPC receiving machine. A handler is a class instance which RPC functions will be invoked on. Alternatively you can inherit your handler class from CF_RPC_HandlerBase which registers automatically.
     * @code
     * constructor()
     * {
     *     CF.RPC.RegisterHandler(this);
     * }
     * @endcode
     *
     * @param instance  The handler instance to be registered
     * @return bool     Returns true if successfully registered, false otherwise (see script log for details).
     */
	static bool RegisterHandler(Class instance)
	{
        if(!m_RegisteredInstances.Contains(instance.ClassName()))
        {
            m_RegisteredInstances.Set(instance.ClassName(), instance);

            return true;
        }

        PrintFormat("[WARNING][CommunityFramework][RPC] Failed to register the handler instance %1. An instance for the handler type %2 was already registered. See trace below:", instance, instance.ClassName());
        DumpStack();

        return false;
	}

    /**
     * @brief Prepares a new RPC send context, which data can be written to using Write() and that is transmitted using SendTo()
     * @code
     * auto rpc = CF.RPC.Prepare("MyHandler", "MyFunction", true);
     * rpc.Write("My data");
     * rpc.SendTo(receiverIdentity1);
     * rpc.SendTo(receiverIdentity2);
     * @endcode
     *
     * @param handlerType       Typename of handler class on the receiving machine.
     * @param functionName      The name of the function that shall be invoked in the handler instance on the receiving machine.
     * @param guaranteed        Guaranteed RPC delivery. True = Will arrive eventually. False = Might be dropped after first attempt.
     * @param target            Optional target object. Must be globally known in order to work (Map objects, objects spawned by the server globally). NULL by default.
     * @return CF_RPC_Context   RPC write and send context.
     */
    static ref CF_RPC_Context Prepare(typename handlerType, string functionName, bool guaranteed, Object target = null)
    {
        return CF_RPC_Context._Prepare(handlerType.ToString(), functionName, guaranteed, target);
    }

    /**
     * @brief Prepares a new RPC send context, which data can be written to using Write() and that is transmitted using SendTo()
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
     * @param target            Optional target object. Must be globally known in order to work (Map objects, objects spawned by the server globally). NULL by default.
     * @return CF_RPC_Context   RPC write and send context.
     */
    static ref CF_RPC_Context Prepare(string handlerType, string functionName, bool guaranteed, Object target = null)
    {
        return CF_RPC_Context._Prepare(handlerType, functionName, guaranteed, target);
    }

    /**
     * @brief [Internal] Handle incoming RPCs
     *
     * @return bool Returns if the RPC has been consumed by CF
     */
    static bool _OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
    {
        if(rpc_type != CF_RPC_SCRIPT_ID) return false;

        string handlerType, functionName;

        if(ctx.Read(handlerType) && ctx.Read(functionName))
        {
            Class invoke = null;

            if(m_RegisteredInstances.Contains(handlerType))
            {
                invoke = m_RegisteredInstances[handlerType];
            }
            else
            {
                /*
                    Inherited handlers will have the function the rpc is looking for, but might not match the class name.
                    The first matching instance is the result and will be cached for future rpcs of the handlerType.
                */
                auto handlerTypename = handlerType.ToType();

                foreach(auto key, auto value : m_RegisteredInstances)
                {
                    if(key.ToType().IsInherited(handlerTypename))
                    {
                        invoke = value;
                        break;
                    }
                }

                if(invoke)
                {
                    m_RegisteredInstances.Set(handlerType, invoke);
                }
            }

            if(invoke)
            {
                g_Game.GameScript.CallFunctionParams(invoke, functionName, NULL, new Param3<ref ParamsReadContext, ref PlayerIdentity, Object>(ctx, sender, target));
            }
            else
            {
                PrintFormat("[ERROR][CommunityFramework][RPC] No instance found for handler type %1. RPC ignored...", handlerType);
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
    }
}
