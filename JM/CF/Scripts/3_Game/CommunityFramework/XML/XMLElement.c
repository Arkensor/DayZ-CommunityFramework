class XMLElement : Managed
{
    private autoptr array< ref XMLTag > _tags;

    private XMLTag _parentTag;
    
    void XMLElement( ref XMLTag parent = NULL )
    {
        _tags = new array< ref XMLTag >;
        _parentTag = parent;
    }

    void ~XMLElement()
    {
        for ( int i = 0; i < _tags.Count(); ++i )
        {
            delete _tags[i];
        }

        delete _tags;
    }

    ref XMLTag CreateTag( string name )
    {
        ref XMLTag tag = new XMLTag( this, name );

        _tags.Insert( tag );

        return tag;
    }

    XMLTag GetParent()
    {
        return _parentTag;
    }

    void Debug( int level = 0 )
    {
        string indent = CF_Indent( level );
        
        Print( indent + "Tags: count=" + _tags.Count() );
        for ( int i = 0; i < _tags.Count(); ++i )
        {
            _tags[i].Debug( level + 1 );
        }
    }
};