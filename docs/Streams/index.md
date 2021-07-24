# Streams

A stream is a doubly linked list of bytes. It can be used for file input/output, DayZ serializers, hex conversion or string parsing. Once you are finished with the stream it is recommended to close the stream. This is done by using the `Close` method but the process automatically happens in the destructor.

Streams can be manipulated with `CF_TextWriter`, and `CF_BinaryWriter`. Streams can be read with `CF_TextReader`, and`CF_BinaryReader`.

In binary format, all values are in little-endian format.

In text format, only ASCII characters are supported.

Using the `File` method in the target stream, different `FileMode`'s can be used. They are `READ`, `WRITE` and `APPEND`.

**$profile:text.txt**:
```
Hello, World!
```

```csharp
string path = "$profile:test.txt";

```csharp
CF_StringStream stream = new CF_StringStream();
stream.File("$profile:test.txt", FileMode.READ);
string output = stream.ReadLine();
Print(output); // 'Hello, World!'
```

## String

Use the `CF_StringStream` class to read and write to a string source. This stream does not accept '\0' bytes.

```csharp
string data = "Hello, World!";

CF_TextReader reader = new CF_TextReader(new CF_StringStream(data));
Print("ReadWord: " + reader.ReadWord());				// "Hello"
Print("ReadChar: " + reader.ReadChar());				// ","
Print("ReadWhitespace: " + reader.ReadWhitespace());	// ""
Print("ReadWord: " + reader.ReadWord());				// "World"
Print("ReadChar: " + reader.ReadChar());				// "!"
reader.Close();
```

Note: `ReadWord` will read continously from the current position till it finds a character that isn't alphanumeric.

## Hex

Use the `CF_HexStream` class to read and write to a string source as a hex output.

```csharp
CF_HexStream stream = new CF_HexStream();

CF_BinaryWriter writer = new CF_BinaryWriter(stream);
writer.WriteFloat(5);
writer.Close();

Print(stream.ToStr());	// "40A00000"
```

## Serializer

Use `CF_SerializerReadStream`/`CF_SerializerWriteStream` for read and write interaction with anything inherited from the DayZ `Serializer` class.

```csharp
Serializer serializer; // could be ScriptRPC, FileSerializer, ScriptInputUserData, anything that inherits from Serializer
ScriptReadWriteContext ctx = new ScriptReadWriteContext();

// Write to the context
serializer = ctx.GetWriteContext();
CF_BinaryWriter writer = new CF_BinaryWriter(new CF_SerializerWriteStream(serializer));
writer.WriteFloat(0.1);
writer.Close();

// Read from the context
serializer = ctx.GetReadContext();
CF_BinaryReader reader = new CF_BinaryReader(new CF_SerializerReadStream(serializer));
Print(reader.ReadFloat());	// "0.1"
reader.Close();
```
