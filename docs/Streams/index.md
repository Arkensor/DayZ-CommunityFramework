# Streams

A stream is a doubly linked list of bytes. It can be used for file input/output, DayZ serializers, hex conversion or string parsing. Once you are finished with the stream it is recommended to close the stream. This is done by using the `Close` method but the process automatically happens in the destructor.

Streams can be manipulated with `CF_TextWriter`, and `CF_BinaryWriter`. Streams can be read with `CF_TextReader`, and`CF_BinaryReader`.

In binary format, all values are in little-endian format.

## Files

Use the `CF_FileStream` class to read and write files on the a file system. 

```csharp
string path = "$profile:test.txt";

// Create the file
CF_TextWriter writer = new CF_TextWriter(new CF_FileStream(path, FileMode.WRITE));
writer.WriteLine("This is some text");
writer.Close();

// Open the file and read it back
CF_TextReader reader = new CF_TextReader(new CF_FileStream(path, FileMode.READ));
Print(reader.ReadLine()); // "This is some text"
reader.Close();
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

## Hex

Use the `CF_HexStream` class to read and write to a string source as a hex output.

```csharp
CF_HexStream stream = new CF_HexStream();

CF_BinaryWriter writer = new CF_BinaryWriter(stream);
writer.WriteFloat(5);
writer.Close();

Print(stream.GetDebugName());	// "40A00000"
```

## Serializer

Use the `CF_SerializerReadStream` class to read to from the DayZ serializer and `CF_SerializerWriteStream` to write to the DayZ serializer.

```csharp
ScriptReadWriteContext ctx = new ScriptReadWriteContext();

// Write to the context
CF_BinaryWriter writer = new CF_BinaryWriter(new CF_SerializerWriteStream(ctx.GetWriteContext()));
writer.WriteFloat(0.1);
writer.Close();

// Read the context
CF_BinaryReader reader = new CF_BinaryReader(new CF_SerializerReadStream(ctx.GetReadContext()));
Print(reader.ReadFloat());	// "0.1"
reader.Close();
```
