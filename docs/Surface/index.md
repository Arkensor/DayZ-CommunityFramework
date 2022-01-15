# Surface

An easy and optimized way to retrieve the information from the surface classes. Rather than running the `CGame::ConfigGet` functions everytime you wish to get any surface information just use the existing classes here.

```csharp
auto surface = CF_Surface.At(GetGame().GetPlayer().GetPosition());
Print(surface.Name);
```

## CF_Surface

Taken from `CfgSurfaces`

| Name              | Type               | Explanation                                                                                                                    |
| ----------------- | ------------------ | ------------------------------------------------------------------------------------------------------------------------------ |
| Interior          | float              | If the surface is interior or exterior                                                                                         |
| Deflection        | float              | Defines which ground texture and roadway texture filenames this surface will apply to                                          |
| Friction          | float              | Smoothness value of the surface                                                                                                |
| Restitution       | float              | The bounciness value of the surface                                                                                            |
| SoundEnvironment  | string             | Defines the sound played when walking or driving a vehicle on the surface                                                      |
| SoundHit          | string             | Defines the sound played when the surface is struck by a bullet                                                                |
| Character         | string             | Points to a corresponding CfgSurfaceCharacters entry, which defines the clutter on this surface.                               |
| FootDamage        | float              | Multiplier for the amount of damage the surface does on bare feet                                                              |
| Audibility        | float              | Multiplier for how loud the sound is on the surface                                                                            |
| Impact            | string             | Defines what particle effect is shown when the surface is hit by a bullet, points to a class registered in `ImpactMaterials`   |
| IsDigable         | bool               | If the surface is digable for placing a `Torch` or burying bodies                                                              |
| IsFertile         | bool               | If the surface is fertile for using a shovel and growing crops                                                                 |
| ChanceForCatch    | float              | Unknown, interior surfaces is 0, exterior surfaces is 1                                                                        |
| WindModifier      | float              | Speed of the wind on the `Character` clutter                                                                                   |
| VehicleSurface    | CF_VehicleSurface  | Corresponding `CF_VehicleSurface` for the vehicle                                                                              |


## CF_VehicleSurface

Taken from `CfgVehicleSurfaces`

| Name              | Type               | Explanation                                                                                                                    |
| ----------------- | ------------------ | ------------------------------------------------------------------------------------------------------------------------------ |
| NoiseSteer        | float              | Multiplier for how much noise the steering wheel produces                                                                      |
| NoiseFrequency    | float              | Multiplier for how often the noise plays while steering                                                                        |
| Roughness         | float              | Multiplier for how rough the surface is                                                                                        |
| FrictionOffroad   | float              | Friction for low tread, high roughness tyres                                                                                   |
| FrictionSlick     | float              | Friction for high tread, low roughness tyres                                                                                   |
| RollResistance    | float              | Value for how much resistance there is on the tyres preventing rolling                                                         |
| RollDrag          | float              | Value for how much drag there is on the tyres preventing rolling                                                               |
