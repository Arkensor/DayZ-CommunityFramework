typedef CF_XML_Callback XMLCallback;

class CF_XML_Callback : Managed
{
	void OnStart(ref CF_XML_Document document);

	void OnSuccess(ref CF_XML_Document document);

	void OnFailure(ref CF_XML_Document document);
};