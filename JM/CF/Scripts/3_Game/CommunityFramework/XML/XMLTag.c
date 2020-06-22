class XMLTag : Managed
{
    private string _name;

    private autoptr map< string, ref XMLAttribute > _attributes;

    private ref XMLElement _element;

    private XMLElement _parentElement;

    void XMLTag( ref XMLElement parent, string name )
    {
        _attributes = new map< string, ref XMLAttribute >;
        _parentElement = parent;
        _name = name;
        _element = new XMLElement( this );
    }

    void ~XMLTag()
    {
        for ( int i = 0; i < _attributes.Count(); ++i )
        {
            delete _attributes.GetElement( i );
        }

        delete _attributes;

        delete _element;
    }

    string GetName()
    {
        return _name;
    }

    ref XMLTag CreateTag( string name )
    {
        return _element.CreateTag( name );
    }

    ref XMLAttribute CreateAttribute( string name )
    {
        XMLAttribute attrb = new XMLAttribute( this, name );

        _attributes.Insert( name, attrb );

        return attrb;
    }

    ref XMLAttribute GetAttribute( string name )
    {
        return _attributes.Get( name );
    }

    XMLElement GetContent()
    {
        return _element;
    }

    XMLElement GetParent()
    {
        return _parentElement;
    }

    void Debug( int level = 0 )
    {
        string indent = CF_Indent( level );

        Print( indent + "Tag:" );
        Print( indent + " name=" + _name );

        Print( indent + "Attributes: count=" + _attributes.Count() );
        for ( int i = 0; i < _attributes.Count(); ++i )
        {
            _attributes.GetElement( i ).Debug( level );
        }

        Print( indent + "Element:" );
        _element.Debug( level + 1 );
    }
};