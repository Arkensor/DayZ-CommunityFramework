# Cryptography

A variety of cryptography functions may be added to Community Framework in the future.

## SHA-256

```csharp
string path = "$profile:test.txt";

// Create the file
CF_TextReader reader = new CF_TextReader(new CF_FileStream(path, FileMode.READ));
Print(reader.ReadLine()); // "This is some text"

CF_Base16Stream hexStream = new CF_Base16Stream();
CF_SHA256.Process(reader, hexStream);

Print(hexStream.Encode()); // "2263D8DD95CCFE1AD45D732C6EAAF59B3345E6647331605CB15AAE52002DFF75"

reader.Close();

```