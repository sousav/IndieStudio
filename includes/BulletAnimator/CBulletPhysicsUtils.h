/*
 *  Copyright (c) 2007-2009  zet.dp.ua
 *  Copyright (c) 2009 Colombian Developers - Team
 *
 *  This file is part of IrrBullet (Bullet Physics Wrapper for Irrlicht)
 *
 *  IrrBullet is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  IrrBullet is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */


// Helper functions to use with CBulletPhysics

#ifndef __C_BULLET_PHYSICS_UTILS_H_INCLUDED__
#define __C_BULLET_PHYSICS_UTILS_H_INCLUDED__


//! Irrlicht
#include "irrlicht.h"
using namespace irr;

class btTriangleIndexVertexArray;
class btTriangleMesh;
class btConvexHullShape;

//! Bullet
#include "LinearMath/btVector3.h"
#include "LinearMath/btMatrix3x3.h"
#include "LinearMath/btTransform.h"



//! useful defines
/*#define SAFE_DELETE(p)			  {if(p) {delete (p);	(p)=0;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete [] (p); (p)=0;}}*/

//! useful constants
const double BPU_PI = 3.1415926535897932384626433832795;
const double BPU_PI2 = 3.1415926535897932384626433832795/2.;
const double BPU_360_PI2 = 360./(BPU_PI2);
const double BPU_PI_180 = BPU_PI/180.;
const double BPU_180_PI = 180./BPU_PI;


//==============================================================================
//==============================================================================
//==============================================================================


//------------------------------------------------------------------------------
//! Convert Quaternion to Euler (btQuaternion to irr::core::vector3df)
//! euler is measured in radians
SIMD_FORCE_INLINE void QuaternionToEulerXYZ(const btQuaternion& quat, irr::core::vector3df& euler)
{
  irr::f32 w=quat.getW(), x=quat.getX(), y=quat.getY(), z=quat.getZ();
  double   sqx = x*x, sqy = y*y, sqz = z*z;
  // heading
  euler.Z = atan2(btScalar(2.0*(z*w+x*y)), btScalar(1.0 - 2.0*(sqy + sqz)));
  // bank
  euler.X = atan2(btScalar(2.0*(x*w+y*z)), btScalar(1.0 - 2.0*(sqx + sqy)));
  // attitude
  euler.Y = asin(btScalar(2.0*(-x*z + y*w)));
}

//------------------------------------------------------------------------------
//! Convert Euler to Quaternion (irr::core::vector3df to btQuaternion)
//! euler is measured in radians
SIMD_FORCE_INLINE void EulerXYZToQuaternion(const irr::core::vector3df& euler, btQuaternion &quat)
{
  btScalar _heading=euler.Z*0.5;
  btScalar _attitude=euler.Y*0.5;
  btScalar _bank=euler.X*0.5;
  btScalar c1 = cos(_heading);
  btScalar s1 = sin(_heading);
  btScalar c2 = cos(_attitude);
  btScalar s2 = sin(_attitude);
  btScalar c3 = cos(_bank);
  btScalar s3 = sin(_bank);
  double c1c2 = c1*c2;
  double s1s2 = s1*s2;
  //w
  quat.setW((btScalar) (c1c2*c3 + s1s2*s3));
  //x
  quat.setX((btScalar) (c1c2*s3 - s1s2*c3));
  //y
  quat.setY((btScalar) (c1*s2*c3 + s1*c2*s3));
  //z
  quat.setZ((btScalar) (s1*c2*c3 - c1*s2*s3));
}


//==============================================================================
//==============================================================================
//==============================================================================


//------------------------------------------------------------------------------
//! Extract node position to btTransform
SIMD_FORCE_INLINE void GetNodeTransform(irr::scene::ISceneNode* pNode, btTransform& pTransform)
{
  pTransform.setIdentity();

  irr::core::vector3df rot = pNode->getRotation();
  rot *= BPU_PI_180;
  btQuaternion btq;
  EulerXYZToQuaternion(rot, btq);
  pTransform.setRotation(btq);

  irr::core::vector3df pos = pNode->getPosition();
  btVector3 btv(pos.X, pos.Y, pos.Z);
  pTransform.setOrigin(btv);
}

//------------------------------------------------------------------------------
//! ConvertIrrMeshToBulletTriangleArray
//! Irrlicht uses u16 index buffer, we should convert it to use with bullet
//! (btTriangleIndexVertexArray seems to be slower than btTriangleMesh, strange)
btTriangleIndexVertexArray* ConvertIrrMeshToBulletTriangleArray(irr::scene::IMesh* pMesh,
  const irr::core::vector3df& scaling = irr::core::vector3df(1.0f, 1.0f, 1.0f));

//------------------------------------------------------------------------------
//! ConvertIrrMeshToBulletTriangleMesh
//! Convert to IMesh data to btTriangleMesh
btTriangleMesh* ConvertIrrMeshToBulletTriangleMesh(irr::scene::IMesh* pMesh,
  const irr::core::vector3df& scaling = irr::core::vector3df(1.0f, 1.0f, 1.0f));

//------------------------------------------------------------------------------
//! ConvertIrrMeshToBulletConvexHullShape
//! ConvexHullShape implements an implicit (getSupportingVertex)
//! Convex Hull of a Point Cloud (vertices)
//! No connectivity is needed.
btConvexHullShape* ConvertIrrMeshToBulletConvexHullShape(irr::scene::IMesh* pMesh,
  const irr::core::vector3df& scaling = irr::core::vector3df(1.0f, 1.0f, 1.0f));


btTriangleMesh * ConvertTerrainToBulletTriangleMesh(
    irr::scene::ITerrainSceneNode* terrain,
    const irr::core::vector3df& Scaling);


f32 GetMaxRadius(const core::aabbox3d<f32> &box,const core::vector3df &scale);

irr::scene::IAnimatedMeshSceneNode* RepairBoundingBox(irr::scene::IAnimatedMeshSceneNode* node) ;


void BulletToIrr(const btVector3& in, core::vector3df& result);

#endif //__C_BULLET_PHYSICS_UTILS_H_INCLUDED__
