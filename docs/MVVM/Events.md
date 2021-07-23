# Events

## Creating the Event in the Model

Inside the model class you will want a method that handles the event called from the view. Follow the `Events` table below.

e.g. Handling a click event would require the function signature:

```csharp
void SomeClickEvent(Class sender, CF_MouseEventArgs args)
```

## Adding an Event in Workbench

On the selected widget, navigate to the properties tab. Ensure that the `scriptclass` property is set to the relevant one for the widget. Read [Creating View](Creating-View.md) for more information. Scroll down to `Script Properties` and assign the model method created earlier to the `Event_X` property.

## Adding an Event in a Text Editor

Ensure that the `scriptclass` property is set to the relevant one for the widget. Read [Creating View](Creating-View.md) for more information. 

Within `ScriptParamsClass` assign the model method created earlier to the `Event_X` property.

```
ButtonWidgetClass button {
 scriptclass "CF_ButtonWidget"
 {
  ScriptParamsClass {
   Event_Click "OnClick"
  }
 }
}
```

## Events
| Name                  | EventArgs               | Notes                                                        |
| --------------------- | ----------------------- | ------------------------------------------------------------ |
| Event_Click           | CF_MouseEventArgs       |                                                              |
| Event_ModalResult     | CF_ModalEventArgs       |                                                              |
| Event_DoubleClick     | CF_MouseEventArgs       |                                                              |
| Event_Select          | CF_SelectEventArgs      |                                                              |
| Event_ItemSelected    | CF_ItemSelectEventArgs  |                                                              |
| Event_Focus           | CF_PositionEventArgs    |                                                              |
| Event_FocusLost       | CF_PositionEventArgs    |                                                              |
| Event_MouseEnter      | CF_MouseEventArgs       |                                                              |
| Event_MouseLeave      | CF_MouseEventArgs       |                                                              |
| Event_MouseWheel      | CF_MouseEventArgs       |                                                              |
| Event_MouseButtonDown | CF_MouseEventArgs       | `Continue` set to `false` prevents `Event_Click` from firing |
| Event_MouseButtonUp   | CF_MouseEventArgs       |                                                              |
| Event_Controller      | CF_ControllerEventArgs  |                                                              |
| Event_KeyDown         | CF_KeyEventArgs         |                                                              |
| Event_KeyUp           | CF_KeyEventArgs         |                                                              |
| Event_KeyPress        | CF_KeyEventArgs         |                                                              |
| Event_Change          | CF_ChangeEventArgs      |                                                              |
| Event_Drag            | CF_DragEventArgs        |                                                              |
| Event_Dragging        | CF_DragEventArgs        |                                                              |
| Event_DraggingOver    | CF_DragEventArgs        |                                                              |
| Event_Drop            | CF_DragEventArgs        |                                                              |
| Event_DropReceived    | CF_DragEventArgs        |                                                              |
| Event_Resize          | CF_ResizeEventArgs      |                                                              |
| Event_ChildAdd        | CF_ChildEventArgs       |                                                              |
| Event_ChildRemove     | CF_ChildEventArgs       |                                                              |
| Event_Update          | CF_ViewEventArgs        |                                                              |
| Event_Show            | CF_ViewEventArgs        |                                                              |
| Event_Hide            | CF_ViewEventArgs        |                                                              |
| Event_Destroyed       | CF_ViewEventArgs        |                                                              |