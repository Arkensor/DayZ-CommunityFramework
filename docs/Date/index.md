# Date
A simple utility class for calculating time differences and rudimentry outputting.

## Comparision

Two date objects can be compared.

### Example

```csharp
CF_Date dateA = CF_Date.CreateDateTime(2021, 12, 2, 10, 24, 3);
CF_Date dateB = CF_Date.CreateDateTime(2021, 12, 4, 10, 24, 3);
Print(dateB.Compare(dateA).GetDay());
// "2"
```

## Converting to string

A date object can be converted to a string using `ToString`. It only supports the following format specifiers. The number of times the specifier exists is the length of the string.

| Specifier | Name   |
| --------- | ------ |
| Y         | Year   |
| M         | Month  |
| D         | Day    |
| h         | Hour   |
| m         | Minute |
| s         | Second |

### Example

```csharp
CF_Date date = CF_Date.CreateDateTime(2021, 12, 2, 10, 24, 3); // year, month, day, hour, minute, second
Print(date.ToString(CF_Date.DATETIME));
// "2021-12-02 10:24:03"
```
