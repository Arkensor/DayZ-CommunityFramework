# Events

## Creating the Event in the Model

Inside the model class you will want a method that handles the event called from the view. Follow the `Events` table below.

e.g. Handling a click event would require the function signature:

```csharp
void OnClick(CF_ModelBase sender, CF_MouseEventArgs args)
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
| Name                  | EventArgs                                          | Notes                                                        |
| --------------------- | -------------------------------------------------- | ------------------------------------------------------------ |
| Event_Click           | [CF_MouseEventArgs](#CF_MouseEventArgs)            |                                                              |
| Event_ModalResult     | [CF_ModalEventArgs](#CF_ModalEventArgs)            |                                                              |
| Event_DoubleClick     | [CF_MouseEventArgs](#CF_MouseEventArgs)            |                                                              |
| Event_Select          | [CF_SelectEventArgs](#CF_SelectEventArgs)          |                                                              |
| Event_ItemSelected    | [CF_ItemSelectEventArgs](#CF_ItemSelectEventArgs)  |                                                              |
| Event_Focus           | [CF_PositionEventArgs](#CF_PositionEventArgs)      |                                                              |
| Event_FocusLost       | [CF_PositionEventArgs](#CF_PositionEventArgs)      |                                                              |
| Event_MouseEnter      | [CF_MouseEventArgs](#CF_MouseEventArgs)            |                                                              |
| Event_MouseLeave      | [CF_MouseEventArgs](#CF_MouseEventArgs)            |                                                              |
| Event_MouseWheel      | [CF_MouseEventArgs](#CF_MouseEventArgs)            |                                                              |
| Event_MouseButtonDown | [CF_MouseEventArgs](#CF_MouseEventArgs)            | `Continue` set to `false` prevents `Event_Click` from firing |
| Event_MouseButtonUp   | [CF_MouseEventArgs](#CF_MouseEventArgs)            |                                                              |
| Event_Controller      | [CF_ControllerEventArgs](#CF_ControllerEventArgs)  |                                                              |
| Event_KeyDown         | [CF_KeyEventArgs](#CF_KeyEventArgs)                |                                                              |
| Event_KeyUp           | [CF_KeyEventArgs](#CF_KeyEventArgs)                |                                                              |
| Event_KeyPress        | [CF_KeyEventArgs](#CF_KeyEventArgs)                |                                                              |
| Event_Change          | [CF_ChangeEventArgs](#CF_ChangeEventArgs)          |                                                              |
| Event_Drag            | [CF_DragEventArgs](#CF_DragEventArgs)              |                                                              |
| Event_Dragging        | [CF_DragEventArgs](#CF_DragEventArgs)              |                                                              |
| Event_DraggingOver    | [CF_DragEventArgs](#CF_DragEventArgs)              |                                                              |
| Event_Drop            | [CF_DragEventArgs](#CF_DragEventArgs)              |                                                              |
| Event_DropReceived    | [CF_DragEventArgs](#CF_DragEventArgs)              |                                                              |
| Event_Resize          | [CF_ResizeEventArgs](#CF_ResizeEventArgs)          |                                                              |
| Event_ChildAdd        | [CF_ChildEventArgs](#CF_ChildEventArgs)            |                                                              |
| Event_ChildRemove     | [CF_ChildEventArgs](#CF_ChildEventArgs)            |                                                              |
| Event_Update          | [CF_ViewEventArgs](#CF_ViewEventArgs)              |                                                              |
| Event_Show            | [CF_ViewEventArgs](#CF_ViewEventArgs)              |                                                              |
| Event_Hide            | [CF_ViewEventArgs](#CF_ViewEventArgs)              |                                                              |
| Event_Destroyed       | [CF_ViewEventArgs](#CF_ViewEventArgs)              |                                                              |

## Event Args

### CF_ChangeEventArgs

Inherits arguments from [CF_PositionEventArgs](#CF_PositionEventArgs)

| Name              | Type          | Description                                                                |
| ----------------- | ------------- | -------------------------------------------------------------------------- | 
| What              | string        | The name of the variable in the model for what was changed                 |
| Finished          | bool          | If the change event is finished                                            |

### CF_ChildEventArgs

Inherits arguments from [CF_PositionEventArgs](#CF_PositionEventArgs)

| Name              | Type          | Description                                                                |
| ----------------- | ------------- | -------------------------------------------------------------------------- | 
| Child             | Widget        | The widget that was changed                                                |
| Remove            | bool          | True if the change was removal, false if addition                          |

### CF_ControllerEventArgs

Inherits arguments from [CF_ViewEventArgs](#CF_ViewEventArgs)

| Name              | Type          | Description                                                                |
| ----------------- | ------------- | -------------------------------------------------------------------------- | 
| Control           | int           | The controller code                                                        |
| Value             | int           | The value of the controller                                                |

### CF_DragEventArgs

Inherits arguments from [CF_PositionEventArgs](#CF_PositionEventArgs)

| Name              | Type          | Description                                                                |
| ----------------- | ------------- | -------------------------------------------------------------------------- | 
| Reciever          | Widget        | The widget recieving the dragged widget                                    |

### CF_ItemSelectEventArgs

Inherits arguments from [CF_PositionEventArgs](#CF_PositionEventArgs)

| Name              | Type          | Description                                                                |
| ----------------- | ------------- | -------------------------------------------------------------------------- | 
| Row               | int           | The row the selected item is in                                            |
| Column            | int           | The column the selected item is in                                         |
| OldRow            | int           | The row the selected item was in                                           |
| OldColumn         | int           | The column the selected item was in                                        |

### CF_KeyEventArgs

Inherits arguments from [CF_PositionEventArgs](#CF_PositionEventArgs)

| Name              | Type          | Description                                                                |
| ----------------- | ------------- | -------------------------------------------------------------------------- | 
| Key               | int           | The key code                                                               |
| State             | CF_KeyState   | The state of the key code                                                  |

### CF_ModalEventArgs

Inherits arguments from [CF_PositionEventArgs](#CF_PositionEventArgs)

| Name              | Type          | Description                                                                |
| ----------------- | ------------- | -------------------------------------------------------------------------- | 
| Code              | int           | The code assigned to the modal                                             |
| Result            | int           | The result the modal gave                                                  |

### CF_MouseEventArgs

Inherits arguments from [CF_PositionEventArgs](#CF_PositionEventArgs)

| Name              | Type          | Description                                                                |
| ----------------- | ------------- | -------------------------------------------------------------------------- | 
| Button            | int           | The mouse button click                                                     |
| Enter             | int           | The widget the mouse left the target for                                   |
| Wheel             | int           | The amount the mouse wheel moved                                           |
| Type              | int           | The type of mouse event, 0 for default, 1 for enter and 2 for leave        |

### CF_PositionEventArgs

Inherits arguments from [CF_ViewEventArgs](#CF_ViewEventArgs)

| Name              | Type          | Description                                                                |
| ----------------- | ------------- | -------------------------------------------------------------------------- | 
| X                 | int           | The screen X position the mouse is at                                      |
| Y                 | int           | The screen Y position the mouse is at                                      |

### CF_ResizeEventArgs

Inherits arguments from [CF_PositionEventArgs](#CF_PositionEventArgs)

### CF_SelectEventArgs

Inherits arguments from [CF_PositionEventArgs](#CF_PositionEventArgs)

### CF_ViewEventArgs

| Name              | Type          | Description                                                                |
| ----------------- | ------------- | -------------------------------------------------------------------------- | 
| Target            | Widget        | The target widget the event is firing upon                                 |
| Continue          | bool          | If the event should continue with default behaviour                        |
