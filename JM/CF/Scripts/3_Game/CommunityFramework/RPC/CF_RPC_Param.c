class CF_RPC_Param extends Param
{
    private PlayerIdentity m_serverIdentity; //! Private param, only used on receive rpc invoke. NOT to be accessed or set outside of framework code!

    void CF_RPC_Param();

    void _SetSenderIdentity(PlayerIdentity senderIdentity)
    {
        m_serverIdentity = senderIdentity;
    }
}

class CF_RPC_Param1<Class T1> extends CF_RPC_Param
{
	T1 param1;

	void Param1(T1 p1)
	{
		param1 = p1;
	}

	override bool Serialize(Serializer ctx)
	{
		return ctx.Write(param1);
	}

	override bool Deserializer(Serializer ctx)
	{
		return ctx.Read(param1);
	}
}

class CF_RPC_Param2<Class T1, Class T2> extends CF_RPC_Param
{
	T1 param1;
	T2 param2;

	void Param2(T1 p1, T2 p2)
	{
		param1 = p1;
		param2 = p2;
	}

	override bool Serialize(Serializer ctx)
	{
		return ctx.Write(param1) && ctx.Write(param2);
	}

	override bool Deserializer(Serializer ctx)
	{
		return ctx.Read(param1) && ctx.Read(param2);
	}
}

class CF_RPC_Param3<Class T1, Class T2, Class T3> extends CF_RPC_Param
{
	T1 param1;
	T2 param2;
	T3 param3;

	void Param3(T1 p1, T2 p2, T3 p3)
	{
		param1 = p1;
		param2 = p2;
		param3 = p3;
	}

	override bool Serialize(Serializer ctx)
	{
		return ctx.Write(param1) && ctx.Write(param2) && ctx.Write(param3);
	}

	override bool Deserializer(Serializer ctx)
	{
		return ctx.Read(param1) && ctx.Read(param2) && ctx.Read(param3);
	}
}

class CF_RPC_Param4<Class T1, Class T2, Class T3, Class T4> extends CF_RPC_Param
{
	T1 param1;
	T2 param2;
	T3 param3;
	T4 param4;

	void Param4(T1 p1, T2 p2, T3 p3, T4 p4)
	{
		param1 = p1;
		param2 = p2;
		param3 = p3;
		param4 = p4;
	}

	override bool Serialize(Serializer ctx)
	{
		return ctx.Write(param1) && ctx.Write(param2) && ctx.Write(param3) && ctx.Write(param4);
	}

	override bool Deserializer(Serializer ctx)
	{
		return ctx.Read(param1) && ctx.Read(param2) && ctx.Read(param3) && ctx.Read(param4);
	}
}

class CF_RPC_Param5<Class T1, Class T2, Class T3, Class T4, Class T5> extends CF_RPC_Param
{
	T1 param1;
	T2 param2;
	T3 param3;
	T4 param4;
	T5 param5;

	void Param5(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5)
	{
		param1 = p1;
		param2 = p2;
		param3 = p3;
		param4 = p4;
		param5 = p5;
	}

	override bool Serialize(Serializer ctx)
	{
		return ctx.Write(param1) && ctx.Write(param2) && ctx.Write(param3) && ctx.Write(param4) && ctx.Write(param5);
	}

	override bool Deserializer(Serializer ctx)
	{
		return ctx.Read(param1) && ctx.Read(param2) && ctx.Read(param3) && ctx.Read(param4) && ctx.Read(param5);
	}
}

class CF_RPC_Param6<Class T1, Class T2, Class T3, Class T4, Class T5, Class T6> extends CF_RPC_Param
{
	T1 param1;
	T2 param2;
	T3 param3;
	T4 param4;
	T5 param5;
	T6 param6;

	void Param6(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6)
	{
		param1 = p1;
		param2 = p2;
		param3 = p3;
		param4 = p4;
		param5 = p5;
		param6 = p6;
	}

	override bool Serialize(Serializer ctx)
	{
		return ctx.Write(param1) && ctx.Write(param2) && ctx.Write(param3) && ctx.Write(param4) && ctx.Write(param5) && ctx.Write(param6);
	}

	override bool Deserializer(Serializer ctx)
	{
		return ctx.Read(param1) && ctx.Read(param2) && ctx.Read(param3) && ctx.Read(param4) && ctx.Read(param5) && ctx.Read(param6);
	}
}

class CF_RPC_Param7<Class T1, Class T2, Class T3, Class T4, Class T5, Class T6, Class T7> extends CF_RPC_Param
{
    T1 param1;
    T2 param2;
    T3 param3;
    T4 param4;
    T5 param5;
    T6 param6;
    T7 param7;

    void Param7(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7)
    {
        param1 = p1;
        param2 = p2;
        param3 = p3;
        param4 = p4;
        param5 = p5;
        param6 = p6;
        param7 = p7;
    }

    override bool Serialize(Serializer ctx)
    {
        return ctx.Write(param1) && ctx.Write(param2) && ctx.Write(param3) && ctx.Write(param4) && ctx.Write(param5) && ctx.Write(param6) && ctx.Write(param7);
    }

    override bool Deserializer(Serializer ctx)
    {
        return ctx.Read(param1) && ctx.Read(param2) && ctx.Read(param3) && ctx.Read(param4) && ctx.Read(param5) && ctx.Read(param6) && ctx.Read(param7);
    }
}