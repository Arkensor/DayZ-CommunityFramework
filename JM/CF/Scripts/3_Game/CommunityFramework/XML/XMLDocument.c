// TODO: Templates

class FileReader
{
    private FileHandle _fileHandle;
    private bool _isClosed;

    private string _currBuffer = "";
    private int _bufferReadPrevious = 0;
    private int _bufferSize = 100;
    private int _bufferIdx = -1;

    private string _newBuffer = "";
    private int _newBufferStart = 0;
    private int _fileLeft = 0;

    private void FileReader()
    {
    }

    void ~FileReader()
    {
        Close();
    }

    static ref FileReader Open( string path, FileMode mode = FileMode.READ )
    {
        FileReader reader = new FileReader();

        reader._fileHandle = OpenFile( path, mode );

        return reader;
    }

    void Close()
    {
        if ( !_isClosed )
        {
            CloseFile( _fileHandle );
        }

        _isClosed = true;
    }

    string BackChar()
    {
        _bufferIdx--;
        if ( _bufferIdx < 0 )
        {
            _bufferIdx = 0;

            Error( "Attempted to go back too far in the buffer!" );

            return "";
        }

        return _currBuffer.Substring( _bufferIdx, 1 );
    }

    private string ReadChar()
    {
        _bufferIdx++;

        if ( _bufferIdx >= _currBuffer.Length() - 1 )
        {
            /*
            if ( _bufferReadPrevious != 0 )
            {
                _bufferIdx -= _bufferReadPrevious;
                _currBuffer = _currBuffer.Substring( 0, _bufferReadPrevious );
            }

            _bufferReadPrevious = _currBuffer.Length();

            _newBufferStart = _bufferIdx;
            _fileLeft = ReadFile( _fileHandle, _newBuffer, _bufferSize );

            _currBuffer = _currBuffer + _newBuffer;
            */

            string lineContent;
            while ( FGets( _fileHandle, lineContent ) >= 0 )
            {
                _fileLeft += lineContent.Length();
                _currBuffer = _currBuffer + lineContent;
            }
        }

        //Print( "c=" + _currBuffer.Substring( _bufferIdx, 1 ) + " bufferIdx=" + _bufferIdx + " bufferLen=" + _currBuffer.Length() );

        return _currBuffer.Substring( _bufferIdx, 1 );
    }

    bool EOF()
    {
        return _bufferIdx >= _newBufferStart + _fileLeft;
    }

    private void SkipComment()
    {
        string c = ReadChar();
        while ( true  )
        {
            if ( EOF() )
            {
                Error( "Unexpected end of file while parsing XML comment!" );
                break;
            }

            if ( c != ">" )
            {
                c = ReadChar();
                continue;
            }

            BackChar();
            BackChar();
            BackChar();

            string check = ReadChar() + ReadChar() + ReadChar();
            if ( check == "-->" )
            {
                return;
            } else
            {
                c = ReadChar();
            }
        }
    }

    string GetCharacter()
    {        
        string c = ReadChar();
        while ( true )
        {
            if ( c == "<" )
            {
                c = ReadChar();
                if ( c == "!" )
                {
                    c = ReadChar();
                    if ( c == "-" )
                    {
                        c = ReadChar();
                        if ( c == "-" )
                        {
                            SkipComment();
                        } else
                        {
                            BackChar();
                            BackChar();
                            BackChar();
                            return "<";
                        }
                    } else
                    {
                        BackChar();
                        BackChar();
                        return "<";
                    }
                } else
                {
                    BackChar();
                    return "<";
                }
            } else
            {
                return c;
            }

            c = ReadChar();
        }

        return c;
    }

    bool IsWhitespace( string c )
    {
        if ( c == " " )
            return true;
        if ( c == "\t" )
            return true;
        if ( c == "\n" )
            return true;
        if ( c == "\r" )
            return true;

        if ( c == "" )
            Error( "Unexpected end of string" );

        return false;
    }

    bool IsLetterOrDigit( string c )
    {
        return IsLetterOrDigit( c, false );
    }

    bool IsLetterOrDigit( string c, bool isQuoted )
    {
        int i = _cf_characters.Find( c );
        if ( i == -1 )
        {
            return false;
        }

        if ( isQuoted && i >= 32 && i <= 126 )
        {
            return true;
        }
            
        if ( i >= 48 && i <= 57 )
        {
            return true;
        }

        i -= 32;

        if ( i >= 65 && i <= 90 )
        {
            return true;
        }

        return false;
    }

    string SkipWhitespace()
    {
        string c = GetCharacter();
        while ( IsWhitespace( c ) && !EOF() )
            c = GetCharacter();

        return c;
    }

    string GetWord()
    {
        string word = "";
        
        string c = SkipWhitespace();

        while ( IsLetterOrDigit( c ) && !EOF() )
        {
            word = word + c;
            c = GetCharacter();
        }

        BackChar();

        return word;
    }

    string GetQuotedWord( out bool isQuoted )
    {
        string word = "";
        
        string c = SkipWhitespace();

        if ( c == "\"" )
        {
            c = "";
            isQuoted = true;
        }

        while ( ( IsLetterOrDigit( c, isQuoted ) || c == "" ) && !EOF() )
        {
            word = word + c;
            c = GetCharacter();
            if ( isQuoted && c == "\"" )
            {
                break;
            }
        }

        if ( !isQuoted )
            BackChar();

        return word;
    }
};

class XMLDocument : XMLElement
{
    private XMLTag _currentTag;

    private ref FileReader _reader;

    static ref XMLDocument Read( string file )
    {
        XMLDocument document = new XMLDocument( NULL );
        document._reader = FileReader.Open( file );

        document.Read();

        document.Debug();

        return document;
    }

    override ref XMLTag CreateTag( string name )
    {
        if ( _currentTag )
        {
            _currentTag = _currentTag.CreateTag( name );
        } else
        {
            _currentTag = super.CreateTag( name );
        }

        return _currentTag;
    }

    private bool ReadAttribute()
    {
        if ( !_currentTag )
        {
            Error( "Attempting to read attribute when not in tag!" );
            return false;
        }

        bool isQuoted;
        string name = _reader.GetWord();
        string eq = _reader.GetCharacter();
        string value = _reader.GetQuotedWord( isQuoted );

        //Print( "name=" + name + " eq=" + eq + " value=" + value );

        if ( eq != "=" )
        {
            Error( "Expected '=' for attribute, got: " + eq );
            return false;
        }

        XMLAttribute attrib = _currentTag.CreateAttribute( name );
        attrib.SetValue( value );

        return true;
    }

    private bool PopTag()
    {
        if ( !_currentTag )
            return true;

        if ( _currentTag.GetParent() )
            _currentTag = _currentTag.GetParent().GetParent();
        else
            _currentTag = NULL;

        return true;
    }

    private bool ReadTag()
    {
        string c = _reader.SkipWhitespace();
        string tagName = "";

        if ( c == "<" )
        {
            c = _reader.GetCharacter();
            if ( c == "/" )
            {
                tagName = _reader.GetWord();

                if ( _currentTag == NULL )
                {
                    Error( "Unexpected closing tag: " + tagName );
                }

                c = _reader.GetCharacter();
                if ( c != ">" )
                {
                    Error( "Expected '>' for closing tag, got: " + c );
                }

                PopTag();

                return true;
            }

            if ( c != "?" )
                _reader.BackChar();

            tagName = _reader.GetWord();

            CreateTag( tagName );

            c = _reader.SkipWhitespace();
            while ( c != "/" && c != "?" && c != ">" )
            {
                c = _reader.BackChar();
                
                if ( !ReadAttribute() )
                    return false;

                c = _reader.SkipWhitespace();
            }

            if ( c == "/" || c == "?" )
            {
                string expected = c;
                c = _reader.GetCharacter();
                if ( c != ">" )
                {
                    Error( "Expected '" + expected + "' for inline closing tag, got: " + c );
                }

                PopTag();
            } else if ( c == ">" )
            {

            } else
            {
                Error( "Expected '>' for opening element within tag, got: " + c );
            }

            return true;
        }

        // could just be an element. for now treat as wrong format.
        return true;
    }

    private bool Read()
    {
        bool reading = true;
        while ( reading )
        {
            if ( !ReadTag() )
                return false;

            reading = !_reader.EOF();
        }

        return true;
    }
};