# Splines

## Inserting

All points are inserted at the tail end of the spline. Inserting using indices starts at the head.

```csharp
CF_Spline spline = new CF_Spline();
spline.Insert(new CF_SplinePoint("0 0 0"));
spline.Insert(new CF_SplinePoint("5 5 0"));
spline.InsertAt(new CF_SplinePoint("10 3 0"), 1);
```

## Removing

Removal of points are done by index

```csharp
spline.Remove(0);
spline.InsertAt(new CF_SplinePoint("10 3 0"), 0);
```

## Applying the spline

Tick the spline in time by running `Tick` with the amount of seconds to advance.

```csharp
override void EOnSimulate(float pDt)
{
	spline.Tick(pDt);
	if (spline.Completed()) spline.SetTime(0);

	SetPosition(spline.GetPosition());
	SetOrientation(spline.GetOrientation());
}
```
