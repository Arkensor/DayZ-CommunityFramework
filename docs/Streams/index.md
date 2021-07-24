### Streams

There are currently two Streams avaliable, `CF_BinaryStream` and `CF_StringStream`.

`CF_BinaryStream` is optimized for working with binary files and allowing reading of characters, bytes, ints, floats, booleans and vectors.

`CF_StringStream` is optimized for working with text files and allows reading of characters.

### Working with files

Using the `File` method in the target stream, different `FileMode`'s can be used. They are `READ`, `WRITE` and `APPEND`.

**$profile:text.txt**:
```
Hello, World!
```

#### Read

```csharp
CF_StringStream stream = new CF_StringStream();
stream.File("$profile:test.txt", FileMode.READ);
string output = stream.ReadLine();
Print(output); // 'Hello, World!'
```

#### Write

```csharp
CF_StringStream stream = new CF_StringStream();
stream.WriteString("Why, World?");
stream.File("$profile:test.txt", FileMode.WRITE);
```

#### Append

```csharp
CF_StringStream stream = new CF_StringStream();
stream.WriteString("Bye, World!");
stream.File("$profile:test.txt", FileMode.APPEND);
```

#### Passing data

To send raw data to another stream through an intermediatry source, such as an RPC, then `GetBytes` and `SetBytes` must be used for optimal performance.

On the sender the following would be done

```csharp
CF_BinaryStream stream = new CF_BinaryStream();
// ... write data to the stream here
array<CF_Byte> data = stream.GetBytes();
```

On the reciever the following would be done

```csharp
array<CF_Byte> data = new array<CF_Byte>();

CF_BinaryStream stream = new CF_BinaryStream();
stream.SetBytes(data);

// ... read data from the stream here
```

### Getting raw data

```csharp
CF_BinaryStream stream = new CF_BinaryStream();
if (stream.File("$profile:Test.png", FileMode.READ))
{
  array<CF_Byte> data = stream.GetBytes();
}
```

### Setting raw data

```csharp
array<CF_Byte> data = new array<CF_Byte>();

CF_BinaryStream stream = new CF_BinaryStream();
if (stream.File("$profile:Test.png", FileMode.WRITE))
{
  stream.SetBytes(data);
}
```