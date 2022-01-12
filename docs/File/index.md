# Table Of Contents

- [CF_Directory](#cf-directory)
  * [GetFiles](#getfiles)
  * [CreateDirectory](#createdirectory)
- [CF_Path](#cf-path)
  * [GetDirectoryName](#getdirectoryname)
  * [GetFileName](#getfilename)
  * [GetFileNameEx](#getfilenameex)
  * [GetFileNameWithoutExtension](#getfilenamewithoutextension)
  * [GetFileNameWithoutExtensionEx](#getfilenamewithoutextensionex)
  * [GetExtension](#getextension)
- [CF_File](#cf-file)
  * [GetFullPath](#getfullpath)
  * [GetFileName](#getfilename-1)
  * [GetFileNameWithoutExtension](#getfilenamewithoutextension-1)
  * [GetExtension](#getextension-1)
  * [GetDirectory](#getdirectory)
  * [CreateStream](#createstream)
  * [Delete](#delete)
  * [Rename](#rename)
  * [Move](#move)
  * [Copy](#copy)
  * [Copy](#copy-1)

# CF_Directory

## GetFiles

```csharp
static bool GetFiles(string pattern, inout array<ref CF_File> files, FindFileFlags flags = 2)
```

### Parameters

`pattern` The search pattern  
`files` [inout]  An array where the list of files will be written to  
`flags` If it should be looked in directories or .pak files, or both  

### Return

If any files were found that matched the pattern

### Example

```csharp
array<ref CF_File> files();
CF_Directory.GetFiles("$profile:script*", files);
foreach (auto file : files)
{
	Print(file.GetDebugName());
}
```

## CreateDirectory

Creates all directories and subdirectories in the specified path unless they already exist. 

```csharp
static bool CreateDirectory(string directory)
```

### Parameters

`directory` The directory to create.  

### Return

If the directories could be created

# CF_Path

## GetDirectoryName

Returns the directory information for the specified path.

```csharp
static string GetDirectoryName(CF_String path)
```

### Parameters

`path` The path of a file or directory.  

### Return

Directory information for path. Returns an empty string if path does not contain directory information.

## GetFileName

Returns the file name and extension of the specified path string.

```csharp
static string GetFileName(string path)
```

### Parameters

`path` The path string from which to obtain the file name and extension.  

### Return

The characters after the last directory separator character in path. If the last character of path is a directory or volume separator character, this method returns an empty string.

## GetFileNameEx

Returns the file name and extension of the specified path string.

```csharp
static string GetFileNameEx(string path, string folder)
```

### Parameters

`path` The path string from which to obtain the file name and extension.  

### Return

The characters after the last directory separator character in path. If the last character of path is a directory or volume separator character, this method returns an empty string.

## GetFileNameWithoutExtension

Returns the file name of the specified path string.

```csharp
static string GetFileNameWithoutExtension(string path)
```

### Parameters

`path` The path string from which to obtain the file name.  

### Return

The characters after the last directory separator character in path. If the last character of path is a directory or volume separator character, this method returns an empty string.

## GetFileNameWithoutExtensionEx

Returns the file name of the specified path string.

```csharp
static string GetFileNameWithoutExtensionEx(string path, string folder)
```

### Parameters

`path` The path string from which to obtain the file name.  

### Return

The characters after the last directory separator character in path. If the last character of path is a directory or volume separator character, this method returns an empty string.

## GetExtension

Returns the extension (including the period ".") of the specified path string.

```csharp
static string GetExtension(CF_String path)
```

### Parameters

`path` The path string from which to get the extension.  

### Return

The path string from which to get the extension. If path does not have extension information, this method returns an empty string.

# CF_File

## GetFullPath

Returns the path, including file name and extension if they exist

```csharp
string GetFullPath()
```

### Return

Returns the path, including file name and extension if they exist

## GetFileName

Returns the file name and extension

```csharp
string GetFileName()
```

### Return

Returns the file name and extension

## GetFileNameWithoutExtension

Returns the file name without the extension 

```csharp
string GetFileNameWithoutExtension()
```

### Return

Returns the file name without the extension 

## GetExtension

Returns the extension (including the period ".")

```csharp
string GetExtension()
```

### Return

Returns the extension (including the period ".")

## GetDirectory

Returns the full path of the parent folder

```csharp
string GetDirectory()
```

### Return

Returns the full path of the parent folder

## CreateStream

Creates and opens a new instance of a FileStream for the current file

```csharp
CF_Stream CreateStream(FileMode mode)
```

### Parameters

`mode` Sets the file mode the stream will be opened in  

### Return

new instance of CF_FileStream

## Delete

Deletes the current file

```csharp
bool Delete()
```

### Return

true if the operation was successful

## Rename

Renames the current file (copy to new name, then delete original)

```csharp
bool Rename(string name)
```

### Parameters

`name` The new name of the file  

### Return

true if the operation was successful

## Move

Moves the file to the new path (copy to folder, then delete original)

```csharp
bool Move(string name)
```

### Parameters

`path` The new path  

### Return

true if the operation was successful

## Copy

Copies the file to the new path

```csharp
bool Copy(string name)
```

### Parameters

`path` The new path  

### Return

true if the operation was successful

## Copy

Copies the file to the new path, returning the instance of the file

```csharp
bool Copy(string path, out CF_File newFile)
```

### Parameters

`path` The new path  
`newFile` [out] Outputs the new instance of the file  

### Return

true if the operation was successful