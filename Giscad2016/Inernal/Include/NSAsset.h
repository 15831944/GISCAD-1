#pragma once
#include "map"
#include "vector"
#include "..\..\Include\NSDirectives.h"
class __declspec(dllexport)CNSAsset
{
public:
	CNSAsset(void);
	~CNSAsset(void);
public:
	void setAssetNumber(NSSTRING strAssetNum);
	NSSTRING getAssetNumber() const;
	void setObjectID(const long nObjID);
	long getObjectID() const;
	void setBlockName(NSSTRING strBlkName);
	NSSTRING getBlockName();
	void setLayerName(NSSTRING strLayerName);
	NSSTRING getLayerName();
//	bool validateAsset();
	NSSTRING generateAccountCode();
	//NSSTRING getAccountCode(NSSTRING strDepot, NSSTRING strEquipClass);
	NSSTRING getEquipNumberD1();
	int getFNO() const;
	int getAttributeValue(NSSTRING pszKey, NSSTRING& pszValue);
	void setFNO(const int nFNO);
	int checkAttribute(NSSTRING strAttribute/*, std::map<NSSTRING, NSSTRING> & mapOfAttributes*/);

private:
	//int readBlockAttributes(std::map<NSSTRING, NSSTRING> & mapOfAttributes);
private:
	long m_nObjectID;
	int m_nFNO;
	NSSTRING m_strAssetNum;
	NSSTRING m_strLayerName;
	NSSTRING m_strBlockName;
	NSSTRING m_strDepot;
	NSSTRING m_strEquipClass;
public:
	std::map<NSSTRING,NSSTRING> m_mapOfAttributes;
	
};
