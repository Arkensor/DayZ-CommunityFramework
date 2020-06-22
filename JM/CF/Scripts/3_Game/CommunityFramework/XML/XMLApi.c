class XMLApi
{
    private ref array< ref XMLDocument > _documents = new array< ref XMLDocument >;

    void Read( string file, notnull ref XMLCallback callback )
    {
        ref XMLDocument document = new XMLDocument();
        _documents.Insert( document );
		GetGame().GameScript.Call( this, "ReadInt", new Param3< ref XMLDocument, ref XMLReader, ref XMLCallback >( document, XMLReader.Open( file ), callback ) );
    }

    private void ReadInt( Param3< ref XMLDocument, ref XMLReader, ref XMLCallback > params )
    {
        params.param3.OnStart( params.param1 );

        bool success = false;
        if ( params.param1 && params.param2 )
        {
            success = params.param1.Read( params.param2 );
        }

        if ( success )
        {
            params.param3.OnSuccess( params.param1 );
        } else 
        {
            params.param3.OnFailure( params.param1 );
        }
    }
};

static ref XMLApi GetXMLApi()
{
    static ref XMLApi g_reader;
    if ( g_reader == NULL )
        g_reader = new XMLApi();

    return g_reader;
}