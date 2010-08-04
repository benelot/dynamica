#ifndef MAX_WORLD_H
#define MAX_WORLD_H


//#include <NxPhysics.h>
#include <max.h>
//#include "SimpleMesh.h"
#include <list>
#include <map>
#include <iterator>
#include "MxUtils.h"

class ccMaxNode;

typedef std::map<INode*, ccMaxNode*>             ccMaxNodeMapContainer;
typedef std::map<INode*, ccMaxNode*>::iterator   ccMaxNodeMapContainerIter;


/*
  ccMaxWorld holds the ccMaxNode, which can be re-used. It also helps unit change between Max and PhysX.
  Every used Max nodes will be created with a counterpart ccMaxNode object.
  ccMaxNode has PxSimpleMesh as one member variable, which stores the mesh in PhysX unit.
*/

class ccMaxWorld
{
	static ccMaxNodeMapContainer Nodes;
public:

	static TimeValue          MaxTime();
	//static Matrix3            SystemTM;				                  // the overall system transfrom from Max to PhysiX; currently we only consider unit-change
	//static Matrix3            SystemTMInv;		                      // inverted systemTM

	static ccMaxNode*         FindNode(INode* node);
	static void               FreeNodes();
	static void               FreeNode(INode* node);

	static void               RefreshTime();

	static void               SetUnitChange(float unitChange);	       // from Max to PhysX
	static float              GetUnitChange() { return UnitChange; }
	static Matrix3            ChangeToPhysXUnit(Matrix3& tm);
	static Matrix3            ChangeToMaxUnit(Matrix3& tm);

	static Point3             ParseScale(const Matrix3& tm, Matrix3 &scale, Matrix3 &pose);
	//static Matrix3            GetCurrentTM(INode* node);               // get current pose TM, unit changed

	//static Matrix3            MaxTMToPhysX(Matrix3& nodeTM);           // make the max pose to physX pose, considering scaling and world unit change

	static Point3             ChangeToMaxUnit(const Point3& pos);      // convert one Point from PhysX global to Max
	static Point3             ChangeToPhysXUnit(const Point3& pos);      // convert one Point from max to physX


private:
	static float    UnitChange;				// from Max unit to PhysX
};


#endif
