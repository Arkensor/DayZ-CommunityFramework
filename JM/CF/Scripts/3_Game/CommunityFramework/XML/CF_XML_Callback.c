typedef CF_XML_Callback XMLCallback;

class CF_XML_Callback : Managed
{
	void OnStart(CF_XML_Document document);

	void OnSuccess(CF_XML_Document document);

	void OnFailure(CF_XML_Document document);
};