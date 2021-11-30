# Cryptography

A variety of cryptography functions will be added to Community Framework in the future. 

## SHA-256

```csharp
string path = "$profile:test.txt";

// Create the file
CF_FileStream input = new CF_FileStream(path, FileMode.READ);
CF_TextReader reader = new CF_TextReader(input);
Print(reader.ReadLine()); // "This is some text"

CF_Base16Stream output = new CF_Base16Stream();
CF_SHA256.Process(reader, output);

Print(output.Encode()); // "2263D8DD95CCFE1AD45D732C6EAAF59B3345E6647331605CB15AAE52002DFF75"

reader.Close();

```