class XMLAttribute : Managed
{
    private string _name;
    private string _value;

    private XMLTag _parentTag;

    void XMLAttribute( ref XMLTag parent, string name )
    {
        _parentTag = parent;
        _name = name;
        _value = "";
    }

    void SetValue( string value )
    {
        _value = value;
    }

    string GetValue()
    {
        return _value;
    }

    XMLTag GetParent()
    {
        return _parentTag;
    }

    void Debug( int level = 0 )
    {
        string indent = CF_Indent( level );
        Print( indent + " name=" + _name + " value=" + _value );
    }
};