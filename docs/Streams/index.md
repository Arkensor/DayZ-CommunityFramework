### Streams

There are currently two Streams avaliable, `CF_BinaryStream` and `CF_StringStream`.

`CF_BinaryStream` is optimized for working with binary files and allowing reading of characters, bytes, ints, floats, booleans and vectors.

`CF_StringStream` is optimized for working with text files and allows reading of characters.

### Working with files

Using the `File` method in the target stream, different `FileMode`'s can be used. 

**text.txt**:
```
Hello, World!
```

#### Read

```
CF_StringStream stream();
stream.File("$profile:test.txt", FileMode.READ);
string output = stream.ReadLine();
Print(output);
```

#### Write

```
CF_StringStream stream();
stream.WriteString("Why, World?");
stream.File("$profile:test.txt", FileMode.WRITE);
```

#### Append

```
CF_StringStream stream();
stream.WriteString("Bye, World!");
stream.File("$profile:test.txt", FileMode.APPEND);
```

```
CF_BinaryStream stream();
if (stream.File("$profile:Test.png"))
{
  array<int> data = stream.GetBytes();
  GetRPCManager().
}
```

### **Saving a File**

```
CF_BinaryStream stream();
if (stream.File("$profile:Test.png"))
{
  array<int> data = stream.GetBytes();
  GetRPCManager().
}
```

### Getting raw data

```
CF_BinaryStream stream();
if (stream.File("$profile:Test.png", FileMode.READ))
{
  array<int> data = stream.GetBytes();
}
```

### Setting raw data

```
array<int> data = // ...

CF_BinaryStream stream();
if (stream.File("$profile:Test.png", FileMode.WRITE))
{
   stream.SetBytes(data);
}
```