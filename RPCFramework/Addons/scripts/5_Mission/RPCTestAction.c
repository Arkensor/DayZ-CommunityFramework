class RPCTestAction extends RPCActionBase
{
    override int GetRPCType()
    {
        return super.GetRPCType() + 1;
    }   

    protected override ref Param ServerRead( ParamsReadContext ctx )
    {
        ref Param1< int > param;

        if ( ctx.Read( param ) )
        {
            return param;
        }
        return NULL;
    }

    protected override ref Param ClientRead( ParamsReadContext ctx )
    {
        ref Param1< int > param;

        if ( ctx.Read( param ) )
        {
            return param;
        }
        return NULL;
    }  

    // Verifies the action
    protected override bool VerifyAction( ref Param getParams, ref PlayerIdentity sender, ref Object target = NULL )
    {
        return true;
    }

    // Performs the action on the server (or in local multiplayer).
    protected override void PerformServer( ref Param getParams, ref PlayerIdentity sender, ref Object target = NULL )
    {
        ref Param1< int > param = getParams;

        Send( param.param1 );
    }

    // Performs the action on the client.
    protected override void PerformClient( ref Param getParams, ref PlayerIdentity sender, ref Object target = NULL )
    {
        ref Param1< int > param = getParams;

        PlayerBase player = GetGame().GetPlayer();
        player.MessageStatus( "Recieved the param " + param.param1 );
    }

    void Send( int number )
    {
        if ( GetGame().IsClient() )
        {
            SendServer( new ref Param1< int >( number ) );
        } else {
            SendClient( new ref Param1< int >( number ), NULL );
        }
    }
}