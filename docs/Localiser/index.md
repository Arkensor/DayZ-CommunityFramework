# Localiser
A localising system for networked messages. 

## Example

```csharp
CF_Localiser localiser = new CF_Localiser("STR_DATE_FORMAT");
localiser.Add(5);
localiser[1] = "Hello";
localiser[2] = "STR_NOVEMBER";

Print(localiser.Format());
// "5, Hello Nov"
```