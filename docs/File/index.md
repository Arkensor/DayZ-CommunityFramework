# File

Using `CF_File` you can get and iterate over all the script.log files within the dayz profile directory.

```csharp
array<ref CF_File> files();
CF_Directory.GetFiles("$profile:script*", files);
foreach (auto file : files)
{
	Print(file.GetDebugName());
}
```

There are also helper file functions that allow you to `Delete`, `Rename`, `Copy` and `Move`.