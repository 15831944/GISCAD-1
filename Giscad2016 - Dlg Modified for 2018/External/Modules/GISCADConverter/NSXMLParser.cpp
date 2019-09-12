#include "StdAfx.h"
#include "NSXMLParser.h"
#include "..\..\Include\NSReportWriter.h"
//constructor
CNSXMLParser::CNSXMLParser()
{
	m_pXMLDoc = NULL;
}

//destructor
CNSXMLParser::~CNSXMLParser()
{
}

/*!
@Brief			get root element of the DOMDocument
@Param [in]		none
@Return			Root element pointer
@Date			12-07-2007
*/
CNSTElement* CNSXMLParser::getRootElement()
{
	CComPtr<MSXML2::IXMLDOMElement> iRootElm = 0;
	HRESULT hr = (m_pXMLDoc)->get_documentElement(&iRootElm);
	if(hr == S_OK)
		return new CNSTElement(iRootElm);
	else 
		return NULL;
}

/*!
@Brief			Loads the XML file in DOM Model
@Param [in]		XML filename
@Return			if loading is successful returns success else failure
@Date			12-07-2007
*/
bool CNSXMLParser::loadFile(NSSTRING strFileName)
{
	try
	{
		HRESULT hr;
		hr = CoCreateInstance(MSXML2::CLSID_DOMDocument40, NULL, CLSCTX_INPROC_SERVER, 
			MSXML2::IID_IXMLDOMDocument2, (void**)&m_pXMLDoc);

		if (FAILED(hr)) 
		{
			WriteToLog(LOG_OTHER, _T("Cann't create XMLDocument"));
			return false;
		}
		(m_pXMLDoc)->async           =  VARIANT_FALSE;       
		(m_pXMLDoc)->validateOnParse =  VARIANT_FALSE;
		(m_pXMLDoc)->resolveExternals = VARIANT_FALSE;
	
	// Load the file. 
		VARIANT_BOOL bRes =	m_pXMLDoc->load(strFileName.c_str());
		if( bRes == VARIANT_FALSE)
		{
			TCHAR szFormat[_MAX_PATH + 1];
			NSSPRINTF(szFormat, _T("Cannot load file: %s "), strFileName.c_str());
   			WriteToLog(LOG_OTHER, szFormat);
			return false;
		}
	}
	catch(...)
	{
		return false;
	}
	return true;	
}

/*!
@Brief			validate the XMl fila against schema
@Param [in]		schema filename
@Return			if validation is successful returns success else failure
@Date			12-07-2007
*/
bool CNSXMLParser::validate(const NSSTRING strFileName)
{
	// Load xsd into a DOM instance.
	MSXML2::IXMLDOMDocument2Ptr            pXSDDoc  = NULL;
	MSXML2::IXMLDOMParseErrorPtr           pError   = NULL;
	MSXML2::IXMLDOMSchemaCollectionPtr     pSCache  = NULL;
	try
	{
		HRESULT hr = pXSDDoc.CreateInstance(__uuidof(DOMDocument40));
		if (FAILED(hr))
		{
			WriteToLog(LOG_OTHER, _T("Cann't create XMLDocument"));
			return false;
		}
		pXSDDoc->async           =  VARIANT_FALSE;       
		pXSDDoc->validateOnParse =  VARIANT_FALSE;
		//	pXSDDoc->resolveExternals = VARIANT_FALSE;
		if(pXSDDoc->load(strFileName.c_str()) != VARIANT_TRUE)
		{
			TCHAR szFormat[_MAX_PATH + 1];
			NSSPRINTF(szFormat, _T("Cannot load file: %s "), strFileName.c_str());
			WriteToLog(LOG_OTHER, szFormat);
			return false;
		}

		// Create a schema cache instance.
		hr = pSCache.CreateInstance(__uuidof(XMLSchemaCache40));
		if (FAILED(hr)) 
		{
			WriteToLog(LOG_OTHER, _T("Cann't create schema instance"));
			return false;
		}

		// Add the just-loaded schema definition to the schema collection.
		//	pXSDDoc->P(FALSE);

		hr = pSCache->add(_T("http://www.integral.com.au/giscadloader"), pXSDDoc.GetInterfacePtr());
		//	hr = pSCache->add(_T(""), _T("c:\\base\\XMLSchema.xsd"));
		if (FAILED(hr)) 
		{
			WriteToLog(LOG_OTHER, _T("Cann't create schema instance"));
			return false;
		}
	}
	catch(...)
	{
		WriteToLog(LOG_OTHER, _T("Cann't create schema instance"));
		return false;
	}

	// Associate the schema collection with the XMLDoc instance. 
	m_pXMLDoc->schemas = pSCache.GetInterfacePtr();


	pError = m_pXMLDoc->validate();
	if (pError->errorCode != 0)
	{
		BSTR bstrErr(pError->Getreason());
		WriteToLog(LOG_OTHER, bstrErr);
		return false;
	}
	return true;
}

/*!
@Brief			create XML dom document and header/preprocessor portion
@Param [in]		none
@Return			if DOM document created return true else false
@Date			12-07-2007
*/
bool CNSXMLParser::createFile()
{
	try
	{
		HRESULT hr;
		hr = CoCreateInstance(MSXML2::CLSID_DOMDocument30, NULL, CLSCTX_INPROC_SERVER, 
			MSXML2::IID_IXMLDOMDocument2, (void**)&m_pXMLDoc);
		//	---------------------------------------------
		//	Step 6.1: Creating the Processing Instruction
		MSXML2::IXMLDOMProcessingInstructionPtr pPI = NULL;

		pPI = m_pXMLDoc->createProcessingInstruction
			("xml", "version='1.0' encoding='UTF-8'");

		_variant_t vNullVal;
		vNullVal.vt = VT_NULL;
		m_pXMLDoc->insertBefore(pPI, vNullVal);

		//Creating the Root Element
		//	---------------------------------------------
		//	Step 6.2: Creating the Root Element
	/*	MSXML2::IXMLDOMNodePtr pRootNode= NULL; 
		_variant_t varNodeType((short)MSXML2::NODE_ELEMENT);

		pRootNode= m_pXMLDoc->createNode(varNodeType, 
			_T("IEGISCADInterchange"), _T(""));
		
		m_pXMLDoc->appendChild(pRootNode);*/
	}
	catch(...)
	{
		WriteToLog(LOG_OTHER, _T("Failed to create XML file"));
		return false;
	}
	return true;
}

/*!
@Brief			create root element of the XL dom object
@Param [in]		root nodename
@Return			none
@Date			12-07-2007
*/
void CNSXMLParser::createRootElement(const NSSTRING strFileName, const NSSTRING strNamespaceURI)
{
	//Creating the Root Element
	MSXML2::IXMLDOMNodePtr pRootNode= NULL; 
	_variant_t varNodeType((short)MSXML2::NODE_ELEMENT);

	pRootNode= m_pXMLDoc->createNode(varNodeType, strFileName.c_str(), strNamespaceURI.c_str());
	m_pXMLDoc->appendChild(pRootNode);

}

/*!
@Brief			save the DOM document as XML file
@Param [in]		filename
@Return			if saved returns true else false
@Date			26-07-2007
*/
bool CNSXMLParser::save(const NSSTRING strFileName)
{
	if(m_pXMLDoc == NULL) return false;
	m_pXMLDoc->save(strFileName.c_str());
	return true;
}