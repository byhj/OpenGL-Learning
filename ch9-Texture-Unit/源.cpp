//-
// ==========================================================================
// Copyright 1995,2006,2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================
//+

//#include <Simulate/HairSimulator.h>
//#include <Simulate/HeadSimulator.h>

#include <maya/MSimple.h>
#include <maya/MFnlight.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>
#include <maya/MArgList.h>
#include <maya/MGlobal.h>
#include <maya/MSelectionList.h>
#include <maya/MItSelectionList.h>
#include <maya/MPoint.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MPointArray.h>
#include <maya/MDagPath.h>
#include <maya/MDagPathArray.h>
#include <maya/MFnMesh.h>
#include <maya/MFnSet.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MItMeshVertex.h>
#include <maya/MItMeshEdge.h>
#include <maya/MFloatVector.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MFloatArray.h>
#include <maya/MObjectArray.h>
#include <maya/MObject.h>
#include <maya/MPlug.h>
#include <maya/MPxFileTranslator.h>
#include <maya/MFnDagNode.h>
#include <maya/MItDag.h>
#include <maya/MFnCamera.h>
#include <maya/MDistance.h>
#include <maya/MIntArray.h>
#include <maya/MIOStream.h>
#include <maya/MMaterial.h>
#include <maya/MFloatMatrix.h>
#include <maya/MPxLocatorNode.h>
#include <maya/MString.h>
#include <maya/MDagPath.h>
#include <maya/MTypeId.h>
#include <maya/MPlug.h>
#include <maya/MVector.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/M3dView.h>
#include <maya/MFnPlugin.h>
#include <maya/MDistance.h>
#include <maya/MMatrix.h>
#include "maya/MItDag.h"
#include "maya/MDagPath.h"
#include "maya/MGlobal.h"
#include "maya/MObjectHandle.h"
#include "maya/MFnDagNode.h"
#include <maya/MFnMesh.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MItMeshVertex.h>
#include <maya/MDistance.h>
#include <maya/MFnTransform.h>
#include "HairUI.h"
#include "ExportHead.h"
//;#include "ExportShave.h"

class HairSimulation : public MPxLocatorNode
{
public:
	HairSimulation();
	virtual ~HairSimulation();

	virtual MStatus   compute(const MPlug& plug, MDataBlock& data);

	virtual void      draw(M3dView & view, const MDagPath & path,
		M3dView::DisplayStyle style,
		M3dView::DisplayStatus status);

	virtual bool            isBounded() const;
	virtual MBoundingBox    boundingBox() const;
	static  void *          creator();
	static  MStatus         initialize();
	static  MObject         size;         // The size of the foot

public:
	static	MTypeId		id;
	static	MString		drawDbClassification;
	static	MString		drawRegistrantId;
	static  HairUI      *hairUI;  //hair UI
};

HairUI* HairSimulation::hairUI;
MObject HairSimulation::size;
MTypeId HairSimulation::id(0x80007);
MString	HairSimulation::drawDbClassification("drawdb/geometry/HairSimulation");
MString	HairSimulation::drawRegistrantId("HairSimulationNodePlugin");

HairSimulation::HairSimulation() {}
HairSimulation::~HairSimulation() {}

MStatus HairSimulation::compute(const MPlug& /*plug*/, MDataBlock& /*data*/)
{
	return MS::kUnknownParameter;
}

const int numHair = 30000;
const int numVertex = 100;

void HairSimulation::draw(M3dView & view, const MDagPath & path,   //更新每一帧
	M3dView::DisplayStyle style,
	M3dView::DisplayStatus /*status*/)
{
	static int frameID = 0;
	static bool flag = true;
	static bool headflag = true;
	static double HeadTranslate[3] = { 0 };
	static double HeadScale[3] = { 0 };
	static double HeadRotate[4] = { 0 };
	static double HairData[numHair][numVertex][3];
	MStatus status;

	if (hairUI->run)
	{

		view.beginGL();
		MDagPath node = path;
		Output::outputHead(node);
		/*
		MObject component;
		MSelectionList list;
		MFnDagNode nodeFn;
		MGlobal::getActiveSelectionList( list );

		for ( unsigned int index = 0; index < list.length(); index++)
		{
		list.getDagPath(index, node, component);
		MDagPath dagPath = node;
		MFnTransform transfn(node);
		if (headflag) {
		cout << "-----Head Position in World-------" << endl;
		headflag = false;
		}
		//get the head transform information
		MVector translate = transfn.getTranslation(MSpace::kWorld);
		HeadTranslate[0] = translate.x;
		HeadTranslate[1] = translate.y;
		HeadTranslate[2] = translate.z;

		transfn.getScale(HeadScale);
		transfn.getRotationQuaternion(HeadRotate[0], HeadRotate[1], HeadRotate[2], HeadRotate[3], MSpace::kWorld);   //get the head transform information

		if (dagPath.hasFn(MFn::kTransform))
		{
		continue;
		}
		if(dagPath.hasFn(MFn::kNurbsSurface))//&&goin == 1
		{
		continue;
		}
		if(dagPath.hasFn(MFn::kMesh)) // we only get the geometry node otherwise there will be two nodes in modellist for every model
		{
		continue;
		}

		MObjectHandle ohTmp = MObjectHandle(dagPath.node());   //output the first frame hair information
		if(isShave(&ohTmp) && flag)                           //shaveHair
		{
		MObjectArray curArr(1);
		curArr[0] = ohTmp.object();
		shaveAPI::HairInfo hairInfo;
		status = shaveAPI::exportHair(curArr, &hairInfo);  //导出头发信息

		for (int i = 0; i != hairInfo.numHairs; ++i)
		{
		int j = 0;
		for (int iter = hairInfo.hairStartIndices[i]; iter != hairInfo.hairEndIndices[i]-1; ++iter, ++j)
		{
		shaveAPI::Vertex hair = hairInfo.vertices[hairInfo.hairVertices[iter]];
		HairData[i][j][0] = hair.x;
		HairData[i][j][1] = hair.y;
		HairData[i][j][2] = hair.z;
		cout << "Output the first frame shave hair information:" << endl;
		cout << "X:" << hair.x << "; "
		<< "Y:" << hair.y << "; "
		<< "Z:" << hair.z << endl;
		flag = false;
		}
		}
		}
		}
		*/
		view.endGL();
		// ++frameID;
	}
	MObject thisNode = thisMObject();
	MPlug plug(thisNode, size);
	MDistance sizeVal;
	plug.getValue(sizeVal);

	float multiplier = (float)sizeVal.asCentimeters();

}

bool HairSimulation::isBounded() const
{
	return true;
}

MBoundingBox HairSimulation::boundingBox() const  //包围盒
{
	// Get the size
	//
	MObject thisNode = thisMObject();
	MPlug plug(thisNode, size);
	MDistance sizeVal;
	plug.getValue(sizeVal);

	double multiplier = sizeVal.asCentimeters();

	MPoint corner1(-0.17, 0.0, -0.7);
	MPoint corner2(0.17, 0.0, 0.3);

	corner1 = corner1 * multiplier;
	corner2 = corner2 * multiplier;

	return MBoundingBox(corner1, corner2);
}

void* HairSimulation::creator()
{
	return new HairSimulation();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Plugin Registration
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

MStatus HairSimulation::initialize()
{
	MFnUnitAttribute unitFn;
	MStatus			 stat;
	hairUI = new HairUI;
	hairUI->show();
	size = unitFn.create("size", "sz", MFnUnitAttribute::kDistance);
	unitFn.setDefault(1.0);

	stat = addAttribute(size);
	if (!stat) {
		stat.perror("addAttribute");
		return stat;
	}

	return MS::kSuccess;
}

MStatus initializePlugin(MObject obj)
{
	MStatus   status;
	MFnPlugin plugin(obj, PLUGIN_COMPANY, "3.0", "Any");

	status = plugin.registerNode(
		"HairSimulation",
		HairSimulation::id,
		&HairSimulation::creator,
		&HairSimulation::initialize,
		MPxNode::kLocatorNode,
		&HairSimulation::drawDbClassification);

	if (!status) {
		status.perror("registerNode");
		return status;
	}

	return status;
}

MStatus uninitializePlugin(MObject obj)
{
	MStatus   status;
	MFnPlugin plugin(obj);
	status = plugin.deregisterNode(HairSimulation::id);
	if (!status) {
		status.perror("deregisterNode");
		return status;
	}

	return status;
}
