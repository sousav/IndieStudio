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


// A game application wrapper class

#ifndef __C_BULLET_PHYSICS_H_INCLUDED__
#define __C_BULLET_PHYSICS_H_INCLUDED__

//! Bullet
#include <LinearMath/btVector3.h>
#include <LinearMath/btMatrix3x3.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btQuickprof.h>
#include <LinearMath/btIDebugDraw.h>
#include <LinearMath/btAlignedObjectArray.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>

class btConstraintSolver;
class btCollisionDispatcher;
class btDiscreteDynamicsWorld;
class btTypedConstraint;
class btTriangleIndexVertexArray;
class btTriangleMesh;
class btCollisionShape;
class btRigidBody;

// Irrlicht
#include "irrlicht.h"
using namespace irr;

#include "SPhysicsParams.h"
#include "SPhysicsCarParams.h"
#include "CBulletPhysicsAnimator.h"
#include "PhysicsObject.h"
#include "CDebugNode.h"


namespace irr
{
	namespace scene
	{
		class TDebugNode;
	}

	namespace physics
	{
		class btDebugDrawer : public btIDebugDraw
		{
			int m_debugMode;
			scene::TDebugNode* m_debugNode;

			public:

				btDebugDrawer();

				virtual void	drawLine(const btVector3& from,const btVector3& to,const btVector3& fromColor, const btVector3& toColor);
				virtual void	drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
				virtual void	drawSphere (const btVector3& p, btScalar radius, const btVector3& color);
				virtual void	drawBox (const btVector3& boxMin, const btVector3& boxMax, const btVector3& color, btScalar alpha);
				virtual void	drawTriangle(const btVector3& a,const btVector3& b,const btVector3& c,const btVector3& color,btScalar alpha);
				virtual void	drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color);
				virtual void	reportErrorWarning(const char* warningString);
				virtual void	draw3dText(const btVector3& location,const char* textString);

				virtual void	setDebugMode(int debugMode);

				virtual int		getDebugMode() const
				{
					return m_debugMode;
				}


				scene::TDebugNode* getDebugNode(void) { return m_debugNode; }
				void setDebugNode(scene::TDebugNode* debugNode) { m_debugNode = debugNode; }
		};

		//------------------------------------------------------------------------------
		//!	CBulletPhysicsAnimatorGeometryTypes
		//! All available bullet's geometry types
		enum CPhysicsGeometryTypes
		{
			CBPAGT_SPHERE = 0,
			CBPAGT_BOX,
			CBPAGT_CYLINDER,
			CBPAGT_CAPSULE,
			CBPAGT_CONE,
			CBPAGT_STATIC_PLANE,

			CBPAGT_CONVEX_MESH,
			CBPAGT_CONCAVE_MESH,
			CBPAGT_CONCAVE_GIMPACT_MESH,

			//! This enum is never used, it only forces the compiler to
			//! compile these enumeration values to 32 bit.
			CBPAGT_FORCE_32_BIT = 0x7fffffff
		};

		//------------------------------------------------------------------------------
		//! Helper structure to configure animator geometry
		class CPhysicsGeometry
		{
		public:

			CPhysicsGeometryTypes type;
			scene::ISceneNode* node;
			bool AutoCalculate;

			class CSphereGeom
			{
			public:

				f32 radius;             //! sphere radius
			} sphere;

			class CBoxGeom
			{
			public:

				f32 X, Y, Z;            //! boxHalfExtents
			} box;

			class CMesh
			{
			public:

				scene::IMesh* irrMesh;  //! mesh interface
			} mesh;
		};


		//!	CBulletPhysics
		class CBulletPhysics
		{
		public:

			//! Ctor
			CBulletPhysics();

			//! Dtor
			~CBulletPhysics();

			//! Base initialization
			bool Create();

			//! Update
			void OnUpdate(u32 timeMs);

			//! Create animator
			CPhysicsObject* createWorldObject(
				scene::ISceneNode* sceneNode,
				CPhysicsGeometry* geometry,
				SPhysicsParams* physicsParams,
				bool animated = true);

			//! Adds mesh scene node
			bool AddMeshSceneNode(scene::ISceneNode* pNode, scene::IMesh* pMesh, bool pIsStatic);

			//! Adds a box object
			CPhysicsObject* addBox(
				scene::ISceneNode* sceneNode,
				core::vector3df& halfExtends,
				SPhysicsParams* physicsParams,
				bool autoCalculate = true,
				bool staticObject = false
			);

			//! Adds a sphere object
			CPhysicsObject* addSphere(
				scene::ISceneNode* sceneNode,
				f32 radius,
				SPhysicsParams* physicsParams,
				bool autoCalculate = true,
				bool staticObject = false
			);


			//! Adds a cylinder object
			CPhysicsObject* addCylinder(
				scene::ISceneNode* sceneNode,
				core::vector3df& halfExtends,
				SPhysicsParams* physicsParams,
				bool autoCalculate = true,
				bool staticObject = false
			);


			//! Adds a terrain object
			CPhysicsObject* addTerrain(
				scene::ISceneNode* sceneNode,
				SPhysicsParams* physicsParams,
				bool useQuantizedAabbCompression = true
			);


			//! Adds a concave mesh (ex. terrain) object
			CPhysicsObject* addConcaveMesh(
				scene::ISceneNode* sceneNode,
				scene::IMesh* mesh,
				SPhysicsParams* physicsParams,
				bool useQuantizedAabbCompression = true,
				bool staticObject = false
			);

			//! Adds collision filter Callback
			void AddCollisionFilter(btOverlapFilterCallback *filter);

			//! Adds a rigid body to the world.
			btRigidBody* AddRigidBody(float pMass, const btTransform& pStartTransform, btCollisionShape* pShape);

#ifdef IRRBT_CHAR_ANIMATION_CONTROLLER

			class IrrCharController;

			//!
			typedef struct
			{
				core::vector3df origin;
				f32 stepHeight;
				int upAxis;
				int Width,height;
				f32 characterHeight;
				core::vector3df CharacterOffset;
				f32 WalkStep;
				f32 TurnStep;

				//internal
				btKinematicCharacterController* character;
				btPairCachingGhostObject* ghostObject;
				scene::ISceneNode* node;
				IrrCharController *Control;

			} CharacterContInfo;


			//! We need animator to control char object
			class IrrCharController : public scene::ISceneNodeAnimator
			{
				s32 LastAnimationTime;
				CBulletPhysics::CharacterContInfo *cinfo;

			public:
				bool RunForward,RunBackward;
				bool TurnLeft,TurnRight;
				bool Jump;


			public:
				IrrCharController(CBulletPhysics::CharacterContInfo *c)
				{
					cinfo= c;
					RunForward=RunBackward=TurnLeft=TurnRight=Jump=false;
					LastAnimationTime= 0 ;
					/* cinfo->character->setJumpSpeed(20);
					cinfo->character->setMaxJumpHeight(100);*/
				}

				void Update()
				{
					if (TurnLeft) {
						core::vector3df rot= cinfo->node->getRotation();
						cinfo->node->setRotation(rot + (core::vector3df(0, -180, 0) * cinfo->TurnStep));
					} else if (TurnRight)    {
						core::vector3df rot= cinfo->node->getRotation();
						cinfo->node->setRotation(rot + (core::vector3df(0, 180, 0) * cinfo->TurnStep));
					}

					btVector3 walkDir(0,0,0);
					if (RunForward || RunBackward)        {
						core::vector3df rot = cinfo->node->getRotation();
						core::matrix4 mat;
						mat.setRotationDegrees(rot + cinfo->CharacterOffset );
						btVector3 forwardDir(mat[8],mat[9],mat[10]);

						if (RunForward) walkDir += forwardDir*cinfo->WalkStep;
						else walkDir -= forwardDir*cinfo->WalkStep;
					}

					cinfo->character->setWalkDirection(walkDir);

					if (Jump && cinfo->character->canJump()) cinfo->character->jump();
				}


				virtual void animateNode (scene::ISceneNode *node, u32 timeMs)
				{
					btVector3 c = cinfo->ghostObject->getWorldTransform().getOrigin();
					core::vector3df pos= core::vector3df(c.getX(),c.getY()+cinfo->characterHeight,c.getZ());
					cinfo->node->setPosition(pos);
				}

				virtual scene::ESCENE_NODE_ANIMATOR_TYPE getType() const
				{
					// if anyone asks, this is a 'walk' animator
					return (scene::ESCENE_NODE_ANIMATOR_TYPE)MAKE_IRR_ID('w','a','l','k');
				}

				virtual scene::ISceneNodeAnimator* createClone(scene::ISceneNode* node, scene::ISceneManager* newManager=0)
				{
					return NULL;
				};
			};//char controller



			//character control node
			void AddCharacterController(CharacterContInfo *info);

#endif

			btDiscreteDynamicsWorld* getDynamicsWorld(void) { return m_dynamicsWorld; }

			scene::TDebugNode* getDebugNode(void) { return m_btDebugDrawer.getDebugNode(); }
			void setDebugNode(scene::TDebugNode* debugNode) { m_btDebugDrawer.setDebugNode(debugNode); }


		private:

			//! Physics clocks
			//btClock m_clock;

			//! constraint for mouse picking
			//btTypedConstraint* m_pickConstraint;

			btDebugDrawer m_btDebugDrawer;

			btAlignedObjectArray<CPhysicsObject*> m_worldObjects;

			btDiscreteDynamicsWorld* m_dynamicsWorld;
			btBroadphaseInterface* m_broadphase;
			btConstraintSolver* m_constraintSolver;
			btCollisionDispatcher* m_collisionDispatcher;
			btCollisionConfiguration* m_collisionConfiguration;


			core::aabbox3d<f32> GetBoundingBox(scene::ISceneNode* node);
			void getHalfExtends(scene::ISceneNode* sceneNode, core::vector3df& halfExtends);

		};

	} // end of namespace physics
} // end of namespace irr

#endif //__C_BULLET_PHYSICS_H_INCLUDED__
