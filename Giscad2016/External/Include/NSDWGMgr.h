/*!
 @Class		CNSDWGMgr
 @Brief		Provides functionality to perform drawing operations on DWG database
 @Author	Neilsoft Ltd
 @Date		14 June 2007
 @History 	
 */

#pragma once

#include "vector"
#include "map"
#include "NSPoint3D.h"
#include "NSBlock.h"
#include "..\Include\NSCompositeGeometry.h"
#include "NSDelBlock.h"
#include "..\Include\NSLayer.h"
#include "..\Include\NSTextStyle.h"
#include "..\Include\NSLineType.h"
#include "..\Include\NSDimStyle.h"
#include "..\Include\NSValidationDataCollector.h"
#include "..\Include\NSTextHeight.h"
#include "..\Include\NSAsset.h"
//#include "dbid.h" 


class AcDbDatabase;
class AcDbObjectId;
class AcDbEntity;
class AcDbPolyline;
class AcDbMline;
class AcDbText;
class AcGePoint3d;
class CNSAsset;
class AcDbBlockTableRecord;
class AcDbBlockReference;
class AcDb3dPolyline;
class AcDb2dPolyline;


typedef std::map<NSSTRING, NSSTRING> STRING_MAP;
typedef std::vector<CNSAsset*> ASSET_VECTOR;

class _declspec(dllexport) CNSDWGMgr//_declspec(dllexport)
{
public:
	CNSDWGMgr(void);
	virtual ~CNSDWGMgr(void);

	NSSTRING getDWGVersionInfo(const wchar_t *m_strDWGFilename);
	int openDWG(TCHAR* pszFileName, bool bOpenExisting);
	int setDatabase(AcDbDatabase* pDatabase);
    int addNewLayer(TCHAR* pszLayerName, AcDbObjectId &layerId,bool bNonPlotting = false);
    int addTextElement(TCHAR* pszText, double dXX, double dYY, double dZZ,NSSTRING strLayerName);
	int saveCurrentDWG(TCHAR* pszFileName, bool bAs2004, NSSTRING saveFormat = _T("AutoCAD 2013"));
    int addNewTextStyle(TCHAR* pszStyleName, TCHAR* pszFontName);
	int closeDatabase();
	int ReleaseHostDwg();
	
	int getBlock(const TCHAR* pszBlkname, AcDbObjectId& blockId);
	int insertBlockWithAttributes(CNSBlock*  pBlkBlock, TCHAR* pszLayerName, ATT_MAP &mapOfBlkAtt, STRING_MAP &mapOfXData);
	//int drawPolyLine(std::vector<CNSPoint3D>& vectPoints, TCHAR* szLineType, TCHAR* szLayerName, bool bClosed, STRING_MAP &mapOfXData);
	int drawPolyLine(CNSCompositeGeometry *pCompositeGeo, TCHAR* pszLineType, TCHAR* pszLayerName, bool bClosed, STRING_MAP &mapOfXData);
    // Multiline change request start
    int drawMultiLine(CNSCompositeGeometry *pCompositeGeo, TCHAR* pszLineType, TCHAR* pszLayerName, bool bClosed, STRING_MAP &mapOfXData);
    int addMLineSegment(AcDbMline *pMLine, NSSTRING strVertexPoints);
    void getMultiLineStyleIdFromString(const TCHAR* str, AcDbObjectId& id);
    int getMultiLineSegments(AcDbEntity *pMLineEntity, CNSCompositeGeometry *pTempMLine, CNSFeatureContainer *pFeatContainer);
	int getMultiLineSegmentsEx(AcDbEntity *pMLineEntity, CNSCompositeGeometry *pTempMLine,  double sx, double sy, double sz,double ParentRotRad, double ParPosX, double ParPosY, CNSFeatureContainer *pSubFeatContainer);
    // Multiline change request end
	int createCompositeGeometry(CNSFeatureContainer* pFeatureContainer);
	int createCompositeGeometryEx(CNSFeatureContainer* pFeatureContainer);
	int convertString2Vertices(NSSTRING pszPolyLineVertices, std::vector<CNSPoint3D>& vctPolyLineVertices);
	int setBlockAttributes(TCHAR* pBlockName, std::map<NSSTRING,NSSTRING> mAttributes);
	std::vector<TCHAR*> getTitleBlockNames();
	//int setTitleBlockAttributes(std::map<NSSTRING,NSSTRING> mAttributes);
	int setTitleBlockAttributes(std::map<NSSTRING,NSSTRING> mAttributes,int xmlConversion=0);
	int listTitleBlockHeaderAttributes(std::map<NSSTRING, NSSTRING>& mapTableAttributes, std::map<NSSTRING, NSSTRING> &mapofPrompValues);	

	//int selectBlocks(std::vector<CNSBlock*>& vectBlocks, TCHAR* pszLayerName, TCHAR* pszBlockName,std::map<NSSTRING, NSSTRING> &mapBlkAtt, STRING_MAP &mapOfXData);
	//int selectBlocks(std::vector<CNSCompositeContainer*>& vectBlocks, TCHAR* pszLayerName, TCHAR* pszBlockName,std::map<NSSTRING, NSSTRING> &mapBlkAtt, STRING_MAP &mapOfXData);
	int selectBlocks(std::vector<CNSFeatureContainer*>& vectBlocks, TCHAR* pszLayerName, TCHAR* pszBlockName);
	int selectDeletedBlocks(std::vector<CNSDelBlock*> &vectDelBlocks);
	int insertGhostBlock(CNSBlock* blkBlock, std::map<NSSTRING, CNSAttributeRef*> &mapOfBlkAtt);
	int selectPolyLines(std::vector<CNSFeatureContainer*>& vectFeatures, std::vector<NSSTRING>&vectCadestrialLayers, NSSTRING strLayerName = _T("all"), NSSTRING strLineType = _T("all"), bool bWithCableCode=false, short nExcludeFlag = 0);
    int addPolyLineArcSegment(AcDbPolyline *pPolyLine, NSSTRING strArcpoints);
	int addPolyLineLinearSegment(AcDbPolyline *pPolyLine, NSSTRING strVertexPoints);
	int setDatabasePrecision(int);
	//int selectTextLabels(std::vector<CNSBlock*> &vectTextLabels, NSSTRING strLayerName);
	int selectTextLabels(std::vector<CNSFeatureContainer*> &vectTextLabels, std::vector<NSSTRING> szCadastreLayers);
    int selectTextLabelsOnDP(std::map<NSSTRING, TEXTINFO_VECTOR*> &mapTextLabels, std::vector<NSSTRING> szCadastreLayers);
    int clearTextLabels(std::map<NSSTRING, TEXTINFO_VECTOR*> &mapTextLabels);
	//int drawMPolygon(CNSCompositeGeometry *pCompositeGeo, NSSTRING strLineType, NSSTRING strLayerName, STRING_MAP &mapOfXData);
	int insertText(CNSBlock* pBlkBlock, NSSTRING strText, NSSTRING strLayerName);
	int getLayerProperties(std::map<NSSTRING,CNSLayer*> &layerProperties);
	int getTextStyleProperties(std::map<NSSTRING,CNSTextStyle*> &TextStyleProperties);
	int getLineTypeList(std::map<NSSTRING,CNSLineType*> &LineTypeProperties);
	int getDimStyleList(std::map<NSSTRING,CNSDimStyle*> &DimStyleProperties);
	int checkBlockAttributeVisibility(std::map<NSSTRING, std::map<NSSTRING,CNSAttributeRef*>*>&mapBlockAttrVisibility);

	// Validation functions
	int getFeaturesToBeValidated(std::map<long, CNSValidationDataCollector*> &mapBlocksToBeValidated, std::map<long, CNSValidationDataCollector*> &mapLinearFeaturesToBeValidated, bool bGetXInfo, bool getLinerFeatures, TCHAR* pszLayerNameSuffix);
	int addXDATA(long lObjectId, std::map<NSSTRING, NSSTRING> &mapXData);
	int getFeaturesOnLayer(std::map<long, CNSValidationDataCollector*> &mapBlocksToBeValidated, std::map<long, CNSValidationDataCollector*> &mapLinearFeaturesToBeValidated, int nRelationshipFlag, TCHAR* pszLayerName);
	int getTextHeight(std::vector<CNSTextHeight*> &vectTxtHt);
    // There is no DEVELOPER_PLAN layer now. So we passed list of layers names to check on.
	int getOpenPLinesOnDeveloperPlan(std::vector<CNSPoint3D> &vectPtsOnDevPlan, std::vector<NSSTRING> szLayersToCheck);
	int getGeometryOnZeroLayer(std::vector<CNSPoint3D> &vectZeroLayer);
	int getPlineRecord(long ObjectId, CNSPoint3D &pointStart, CNSPoint3D &pointVertex, double &dArea);
	int selectNonStdBlocks(std::map<long, CNSValidationDataCollector*> &mapBlocksToBeValidated);
	int isTypeStd(NSSTRING strExtName);
	int GetBlockObjectsWithInsertionPoint(std::map<AcDbObjectId,AcGePoint3d> &blockData);
    int GetInsertionPoint(long nObjectID, CNSPoint3D &pt);

	//# ifndef _INTERNAL_	
		void withinarea(std::vector<CNSPoint3D> vectPoints, std::vector<CNSPoint3D> &vectPositions);
		int GetLineObjects(std::map<AcDbObjectId,std::vector<AcGePoint3d> > &lineData);
	//#endif
	bool isPointInsideBoundary(AcGePoint3d point,std::vector<CNSPoint3D>vectPoints);
	bool CheckIfLineWithinBlockBoundary(std::vector<CNSPoint3D>vectLinePoints,std::vector<AcGePoint3d>points);
	void purge();
	int eraseGISErrorLayer();
	int setCurrentDatabaseActive();
	int getArcSegments(AcDbEntity *pArcEntity, CNSCompositeGeometry *pTempPolyLine, CNSFeatureContainer *pFeatContainer);
	int getArcSegmentsEx(AcDbEntity *pArcEntity, CNSCompositeGeometry *pTempPolyLine,  double sx, double sy, double sz,double ParentRotRad, double ParPosX, double ParPosY, CNSFeatureContainer *pSubFeatContainer);
	int validateTitleBlockAttributes(/*std::map<NSSTRING, NSSTRING> mapTitleAttributes,*/ std::map<NSSTRING, NSSTRING> &mapTitleAttributesNames);
	int getPromptValues(long lblkTblID, std::map<NSSTRING, NSSTRING> &mapofPrompValues);
	NSSTRING getVersionInfo(CNSDWGMgr &pStdDatabase);
	int selectInvalidBlocks(std::vector<CNSValidationDataCollector *> &vectBlocks);
//	int scanSubStationAssets(std::map<long, SWITCH_MAP*> & mapofSwitches);
	int getAssetNumbers(std::vector<CNSAsset*> & assetVector);

	#ifdef _INTERNAL_
		int WriteToLoglayout(NSSTRING strLog);
	#endif
	int saveActiveDWGAs2004();
    int isPaperSpaceValid();
	int scanAssets(ASSET_VECTOR &m_vectofAssets);
	//int setAssetNumber(long blkObjID, NSSTRING strAssetNo);
	//int readBlockAttributes(long nBlockObjID, std::map<NSSTRING, NSSTRING> & mapOfAttributes);
	//int getBlockName(long nBlockObjID, NSSTRING &strBlockName);
	void setTextHeight(double dTextHeight);
	int copyBlockFromDrawing(CNSDWGMgr &pStdDatabase,NSSTRING szBlockToCopy);
	int rFindString(NSSTRING strBaseString, NSSTRING strStringToBeFind);
	int findString(NSSTRING strBaseString, NSSTRING strStringToBeFind);
	int isPointInsidePolyLine(int nvert, double *vertx, double *verty, double testx, double testy);
	void getSourceDatabase(AcDbDatabase* db);
	//
	void getEffectiveName( AcDbBlockTableRecord *blkTblRecord, AcDbBlockReference *pBlockRef, NSSTRING &strTempBlkName/*, TCHAR* pszInsertedBlockName*/);
	// introduced in Phase II enhancement for Nested Block on 09.04.09 by Subir @ Neilsoft
	int createSubFeatures(AcDbBlockReference *pBlockRef, CNSFeatureContainer *pFeatContainer);
	//int push_backSubFeatures(CNSFeatureContainer *pFeatContainer, std::vector<CNSFeatureContainer*>& vectBlocks);
	// introduced in Phase II enhancement for Nested Block on 09.04.09 by Subir @ Neilsoft

private:
    AcDbDatabase* m_pCurrentDatabase;		// pointer to current database
	void getLinetypeIdFromString(const TCHAR* str, AcDbObjectId& id);
	void getLayerNameIdFromString(const TCHAR* str, AcDbObjectId& id);
	int addXDATA(AcDbObjectId ObjectId, NSSTRING pszAppName, NSSTRING pszAppValue);
	int readXDATA(AcDbObjectId ObjectId, std::map<NSSTRING, NSSTRING> &mapXData);
	void registerApplication(AcDbDatabase* pDatabase, NSSTRING pszAppName);
	int blockDefHasAttributeDef(NSSTRING szAttributeDefinitionName, AcDbObjectId blockDefId);
	int addAttributeDefinition(TCHAR* pszBlkname,TCHAR* pszAttributeTag, TCHAR* pszAttributeValue);
	int getPolyLineSegments(AcDbEntity *pPolyLineEntity, CNSCompositeGeometry *pTempPolyLine, CNSFeatureContainer *pFeatContainer);
	int getPolyLineSegmentsEx(AcDbEntity *pPolyLineEntity, CNSCompositeGeometry *pTempPolyLine,  double sx, double sy, double sz,double ParentRotRad, double ParPosX, double ParPosY, CNSFeatureContainer *pSubFeatContainer);
	int getLineSegments(AcDbEntity *pLineEntity, CNSCompositeGeometry *pTempPolyLine, CNSFeatureContainer *pFeatContainer);
	int getLineSegmentsEx(AcDbEntity *pLineEntity, CNSCompositeGeometry *pTempPolyLine,  double sx, double sy, double sz,double ParentRotRad, double ParPosX, double ParPosY, CNSFeatureContainer *pSubFeatContainer);
	int postToDb(AcDbEntity* pEnt, AcDbObjectId& objId);
	int setAlignment(AcDbText *pText, int nAlignment);
	int getAlignment(AcDbText *pText);
	int getBlockXData(CNSCompositeGeometry *pCompositeGeo, STRING_MAP &mapOfXData);
	//int addAttributeText(std::map<NSSTRING, CNSAttributeRef*>& mapOfBlkAtt, NSSTRING strLayerName);
	int addAttributeText(ATT_MAP& mapOfBlkAtt, NSSTRING strLayerName);
	int getPrimaryCompIndex(CNSCompositeContainer *pContainer);

	// inplemented to incorporate nested features
	int setRelationInfo(AcDbObjectId ObjectId, CNSFeatureContainer *pSubFeatContainer,CNSFeatureContainer *pNestedFeatContainer );
	int readXDATAEx(AcDbObjectId ObjectId, std::map<NSSTRING, NSSTRING> &mapXData);

	void normalizePoint(double &ptX, double &ptY,  double sx, double sy, double sz, double ParentRotRad, double ParX, double ParY);
bool stdFlag;

public:
	int getBlocksOnNonMatchingLayer(std::map<long, CNSValidationDataCollector*> &mapBlocksOnWrongLayer,  TCHAR* pszNameSuff);
	double getZvalue(CNSFeatureContainer *pFeatContainer, NSSTRING strXDataKey);
	void setDrawingNumber(NSSTRING strDrawingNum);
	void setStdDwgFileName(bool flag){stdFlag=flag;}
	
private:
	double m_dTextHeight;
	NSSTRING m_strDrawingNum;
};
