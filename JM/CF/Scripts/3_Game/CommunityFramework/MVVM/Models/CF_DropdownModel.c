class CF_DropdownBaseModel<Class T> : CF_Model
{
	ref CF_ObservableArray<T> Elements = new CF_ObservableArray<T>(); // SubModelProperty0
	int Selected; // SubModelProperty1
};

class CF_DropdownTextModel : CF_DropdownBaseModel<string>
{

};