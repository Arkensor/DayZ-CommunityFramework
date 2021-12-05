# Localiser
A utility to construct multi-part localised strings which can also be sent across the network

## Creating and Using

The following example is using strings found in the DayZ stringtable. 

The localiser class has overloaded the array assignment operator to allow setting of the string table keys and placing in other variables at the desired format.

```csharp
CF_Localiser localiser = new CF_Localiser("STR_DATE_FORMAT"); // "%a, %b %d"
localiser.Add(5);
localiser[1] = "Hello";
localiser[2] = "STR_NOVEMBER"; // "Dec"

Print(localiser.Format());
// English: "5, Hello Nov"
```
