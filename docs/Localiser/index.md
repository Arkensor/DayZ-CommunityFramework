# Localiser
A utility to construct multi-part localised strings which can also be sent across the network

## Creating and Using

The following example is using strings found in the DayZ stringtable. 

The localiser class has overloaded the array assignment operator to allow setting of the string table keys and placing in other variables at the desired format. There are 10 possible slots for text replacement starting at 0. To override the main text use -1 as the index.

```csharp
CF_Localiser localiser = new CF_Localiser("console_log_in"); // "Press %1 to log in."
localiser[0] = "STR_NOVEMBER"; // "Nov"

Print(localiser.Format());
// English: "Press Nov to log in."
```

Otherwise the `Add` method can be used instead. It increments from the last used index, starting at 0 if none used.

```csharp
CF_Localiser localiser = new CF_Localiser("console_log_in"); // "Press %1 to log in."
localiser.Add("STR_NOVEMBER");

Print(localiser.Format());
// English: "Press Nov to log in."
```

The strings don't have to be localised to be used.

```csharp
CF_Localiser localiser = new CF_Localiser("Press %1 to log in.");
localiser[0] = "Nov";

Print(localiser.Format());
// English: "Press Nov to log in."
```

And the parameters don't have to be strings.

```csharp
CF_Localiser localiser = new CF_Localiser("Press %1 to log in.");
localiser[0] = 5;

Print(localiser.Format());
// English: "Press 5 to log in."
```
