# View

## Properties

Properies are linked through script to the name of the variable in the model. [TypeConverters](../TypeConverters/index.md) is used for making the input variable as expected for the property. 

```
TextWidgetClass {
 scriptclass "CF_TextWidget"
 {
  ScriptParamsClass {
   Text "NameOfVariable"
  }
 }
}
```

For all properties, custom TypeConverters can be used. Documentation for creating [TypeConverters](../TypeConverters/index.md). You do not need to register the TypeConverter using attributes. Just place the name of the class at the end of the variable, preceeded by a colon (`:`). This is beneficial for when you want to create a custom typeconverter for a primitive type that does not affect the existing type converters for that primitive type.

```
TextWidgetClass {
 scriptclass "CF_TextWidget"
 {
  ScriptParamsClass {
   Text "NameOfVariable:NameOfTypeConverterClass"
  }
 }
}
```
