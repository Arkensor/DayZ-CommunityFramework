# Surface

An easy and optimized way to retrieve the information from the surface classes. Rather than running the `CGame::ConfigGet` functions everytime you wish to get any surface information just use the existing classes here.

```csharp
auto surface = CF_Surface.At(GetGame().GetPlayer().GetPosition());
Print(surface.Name);
```
