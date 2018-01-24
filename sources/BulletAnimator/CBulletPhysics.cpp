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


#include "CBulletPhysics.h"

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/Gimpact/btGImpactShape.h>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>

//#define USE_PARALLEL_DISPATCHER 1
#ifdef USE_PARALLEL_DISPATCHER
#include "../../Extras/BulletMultiThreaded/SpuGatheringCollisionDispatcher.h"
#endif//USE_PARALLEL_DISPATCHER

namespace irr
{
	namespace physics
	{

		//------------------------------------------------------------------------------
		//! Ctor
		//! Base initialization
		CBulletPhysics::CBulletPhysics()
		{
			m_dynamicsWorld = NULL;
			m_broadphase = NULL;
			m_constraintSolver = NULL;
			m_collisionDispatcher = NULL;
			m_collisionConfiguration = NULL;
		}

		//------------------------------------------------------------------------------
		//! Dtor
		//!
		CBulletPhysics::~CBulletPhysics()
		{
			//problem here is the engine may have cleaned up before this destructor
			// is called, so can't touch the SceneNodes.
			//This destructor will only be called once on application close so no
			// need to remove() scenenodes anyway
			int numItems = m_worldObjects.size();
			for (int i = 0; i < numItems; i++)
			{
				delete m_worldObjects[i];
				m_worldObjects[i] = NULL;
			}

			m_worldObjects.clear();

			if (m_dynamicsWorld != NULL) delete m_dynamicsWorld;
			if (m_constraintSolver != NULL) delete m_constraintSolver;
			if (m_collisionDispatcher != NULL) delete m_collisionDispatcher;
			if (m_collisionConfiguration != NULL) delete m_collisionConfiguration;
			if (m_broadphase != NULL) delete m_broadphase;
		}

		//------------------------------------------------------------------------------
		//! Do additional init work after irrlicht device was created
		//!
		bool CBulletPhysics::Create()
		{
			m_btDebugDrawer.setDebugMode(btIDebugDraw::DBG_DrawWireframe);

#if 0

			m_collisionConfiguration = new btDefaultCollisionConfiguration();
			m_collisionDispatcher = new btCollisionDispatcher(m_collisionConfiguration);
			btVector3 worldMin(-10000,-10000,-10000);
			btVector3 worldMax(10000,10000,10000);
			m_broadphase = new btAxisSweep3(worldMin, worldMax);
			m_constraintSolver = new btSequentialImpulseConstraintSolver();
			m_dynamicsWorld = new btDiscreteDynamicsWorld(
				m_collisionDispatcher,
				m_broadphase,
				m_constraintSolver,
				m_collisionConfiguration
			);

#else

			// Register algorithm
			m_collisionConfiguration = new btDefaultCollisionConfiguration();
			m_collisionDispatcher = new	btCollisionDispatcher(m_collisionConfiguration);
			btGImpactCollisionAlgorithm::registerAlgorithm(m_collisionDispatcher);

			// The default constraint solver.
			// For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
			m_constraintSolver = new btSequentialImpulseConstraintSolver();
			m_broadphase = new  btDbvtBroadphase(); // btSimpleBroadphase();

			m_dynamicsWorld = new btDiscreteDynamicsWorld(
				m_collisionDispatcher,
				m_broadphase,
				m_constraintSolver,
				m_collisionConfiguration
			);

			//m_dynamicsWorld->setGravity(btVector3(0,-9.81f,0));

#endif

			m_dynamicsWorld->setDebugDrawer(&m_btDebugDrawer);

			return true;
		}

		//------------------------------------------------------------------------------
		//! Custom per tick update func
		//!
		void CBulletPhysics::OnUpdate(u32 timeMs)
		{
			if (m_dynamicsWorld)
			{
				//remember, Bullet uses a fixed internal timestep and interpolates
				// if the delta time is different. Damn useful.
				/*
				float dt = iClock.getTimeMicroseconds() * 0.00001f;
				iClock.reset();

				iDynamicsWorld->stepSimulation(dt);
				*/
				//time speed (by ColDev Team)
				//m_dynamicsWorld->stepSimulation(timeMs * 0.0005, 30);

				m_dynamicsWorld->stepSimulation(timeMs * 0.001, 10);

				// apply the new positions and rotations to the scenenodes
				// iDynamicsWorld->updateAabbs();

				/*
				//// update positions
				s32 numObjects = iDynamicsWorld->getNumCollisionObjects();
				for (s32 i=0; i < numObjects; i++)
				{
				scene::ISceneNode* node = iSceneNodes[i];
				btCollisionObject* colObj = iDynamicsWorld->getCollisionObjectArray()[i];
				btRigidBody* body = btRigidBody::upcast(colObj);

				if (node && body && body->getMotionState())
				{
				btVector3 p = body->getCenterOfMassPosition();
				node->setPosition(core::vector3df(p.getX(), p.getY(), p.getZ()));

				const double GRAD_PI = 360./3.1415926535897932384626433832795;
				core::vector3df btv;
				btQuaternion btq=body->getOrientation();
				QuaternionToEulerXYZ(btq, btv);
				core::vector3df v(btv.X, btv.Y, btv.Z);
				v *= GRAD_PI;
				node->setRotation(v);
				}
				}*/
			}
		}

		//------------------------------------------------------------------------------
		//! createBulletPhysicsAnimator
		//! Create CBulletPhysicsAnimator
		CPhysicsObject* CBulletPhysics::createWorldObject(
			scene::ISceneNode* sceneNode,
			CPhysicsGeometry* geometry,
			SPhysicsParams* physicsParams,
			bool animated)
		{
			core::aabbox3d<f32> box;
			irr::core::vector3df scaling = sceneNode->getScale(); // get node scaling

			if (geometry->AutoCalculate)
			{
				if (sceneNode->getType() == scene::ESNT_ANIMATED_MESH)
				{
					if (sceneNode->getBoundingBox().isEmpty())
					{
						RepairBoundingBox((scene::IAnimatedMeshSceneNode*)sceneNode);
					}

					// auto size shapes (by ColDev Team)
					box = sceneNode->getBoundingBox();
					core::vector3df extent = box.getExtent();

					geometry->box.X = extent.X * scaling.X * 0.5f;
					geometry->box.Y = extent.Y * scaling.Y * 0.5f;
					geometry->box.Z = extent.Z * scaling.Z * 0.5f;
					geometry->sphere.radius = GetMaxRadius(box, scaling) * 0.5f;
				}
			}


			// prepare collision shape
			btCollisionShape* collisionShape = NULL;
			switch (geometry->type)
			{
			case CBPAGT_SPHERE:   // ***
				{
					collisionShape = new btSphereShape(geometry->sphere.radius);
				}
				break;

			case CBPAGT_BOX:   // ***
				{
					collisionShape = new btBoxShape(btVector3(geometry->box.X, geometry->box.Y, geometry->box.Z));
				}
				break;

			case CBPAGT_CYLINDER:  // ***
				{
					collisionShape = new btCylinderShape(btVector3(geometry->box.X, geometry->box.Y, geometry->box.Z));
				}
				break;

			case CBPAGT_CAPSULE:
				{
					if (geometry->AutoCalculate)
					{
						box = sceneNode->getTransformedBoundingBox();
						collisionShape = new btCapsuleShape(
							(box.MaxEdge.X - box.getCenter().X) * scaling.X,	//radio
							(box.MaxEdge.Y - box.MinEdge.Y) * scaling.Y * 0.5	//altura
							);
					}
					else
					{
						collisionShape = new btCapsuleShape(geometry->box.X, geometry->box.Y * 2);
					}
				}
				break;

			case CBPAGT_CONE:
				{
					collisionShape = new btConeShape(geometry->box.X, geometry->box.Y * 2);
				}
				break;

			case CBPAGT_STATIC_PLANE:
				{
					collisionShape = new btStaticPlaneShape(btVector3(geometry->box.X, geometry->box.Y, geometry->box.Z), 1);
				}
				break;

			case CBPAGT_CONVEX_MESH:
				{
					btTriangleMesh* triangleMesh = ConvertIrrMeshToBulletTriangleMesh(geometry->mesh.irrMesh, scaling);
					//btTriangleIndexVertexArray* triangleMesh = ConvertIrrMeshToBulletTriangleArray(geometry->mesh.irrMesh, scaling);

					collisionShape = new btConvexTriangleMeshShape(triangleMesh);
					//collisionShape = ConvertIrrMeshToBulletConvexHullShape(geometry->mesh.irrMesh);
				}
				break;

			case CBPAGT_CONCAVE_MESH:  // ***
				{
					btTriangleMesh* triangleMesh;
					bool useQuantizedAabbCompression = true;

					if (sceneNode->getType() == scene::ESNT_TERRAIN )
						triangleMesh = ConvertTerrainToBulletTriangleMesh((scene::ITerrainSceneNode*)sceneNode, scaling);
					else
						triangleMesh = ConvertIrrMeshToBulletTriangleMesh(geometry->mesh.irrMesh, scaling);

					collisionShape = new btBvhTriangleMeshShape(triangleMesh, useQuantizedAabbCompression);
					//collisionShape = new btConvexHullShape();
				}
				break;

			case CBPAGT_CONCAVE_GIMPACT_MESH:
				{
					btTriangleMesh* triangleMesh = ConvertIrrMeshToBulletTriangleMesh(geometry->mesh.irrMesh, scaling);
					//btTriangleIndexVertexArray* triangleMesh = ConvertIrrMeshToBulletTriangleArray(pGeom->mesh.irrMesh);

					btGImpactMeshShape* gimpactShape = new btGImpactMeshShape(triangleMesh);
					gimpactShape->updateBound();
					collisionShape = gimpactShape;
				}
				break;

			default:
				// unknown type
				break;
			}

			if (collisionShape == NULL)
			{
				return NULL;
			}


			CPhysicsObject* worldObject = new CPhysicsObject(
				this,
				physicsParams,
				sceneNode,
				collisionShape,
				animated);

			//scene::CBulletPhysicsAnimator* animator = scene::CBulletPhysicsAnimator::CreateInstance(worldObject);

			// add scene node to control
			m_worldObjects.push_back(worldObject);

			return worldObject;
		}

		//------------------------------------------------------------------------------
		//! Adds scene node
		//!
		bool CBulletPhysics::AddMeshSceneNode(scene::ISceneNode* pNode, scene::IMesh* pMesh, bool pIsStatic)
		{
			//btTriangleIndexVertexArray* indexVertexArrays = ConvertIrrMeshToBulletTriangleArray(pMesh);
			//btTriangleMeshShape* trimeshShape = new btTriangleMeshShape(indexVertexArrays);

			btTriangleMesh* indexVertexArrays = ConvertIrrMeshToBulletTriangleMesh(pMesh);
			bool useQuantizedAabbCompression = true;
			btBvhTriangleMeshShape* trimeshShape = new btBvhTriangleMeshShape(indexVertexArrays, useQuantizedAabbCompression);

			btTransform	startTransform;
			GetNodeTransform(pNode, startTransform);

			float mass = 0.0f;
			btRigidBody* aRigidBody = NULL;

			if (pIsStatic)
			{
				mass = 0.0f;

				aRigidBody = AddRigidBody(mass, startTransform, trimeshShape);
				aRigidBody->setCollisionFlags(aRigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
			}
			else
			{
				mass = 1.0f;

				aRigidBody = AddRigidBody(mass, startTransform, trimeshShape);
			}

			// add scene node to control
			//m_sceneNodes.push_back(pNode);

			return true;
		}

		//------------------------------------------------------------------------------

		void CBulletPhysics::getHalfExtends(scene::ISceneNode* sceneNode, core::vector3df& halfExtends)
		{
			core::aabbox3d<f32> box;
			irr::core::vector3df scaling = sceneNode->getScale(); // get node scaling

			if (sceneNode->getBoundingBox().isEmpty())
			{
				RepairBoundingBox((scene::IAnimatedMeshSceneNode*)sceneNode);
			}

			// auto size shapes
			box = sceneNode->getBoundingBox();
			core::vector3df extent = box.getExtent();

			halfExtends.X = extent.X * scaling.X * 0.5f;
			halfExtends.Y = extent.Y * scaling.Y * 0.5f;
			halfExtends.Z = extent.Z * scaling.Z * 0.5f;
		}

		//------------------------------------------------------------------------------
		//! Adds scene node
		//!
		CPhysicsObject* CBulletPhysics::addBox(
			scene::ISceneNode* sceneNode,
			core::vector3df& halfExtends,
			SPhysicsParams* physicsParams,
			bool autoCalculate,
			bool staticObject
		)
		{
			if (autoCalculate)
			{
				if (sceneNode->getType() == scene::ESNT_ANIMATED_MESH)
				{
					getHalfExtends(sceneNode, halfExtends);
				}
			}

			CPhysicsObject* worldObject = new CPhysicsObject(
				this,
				physicsParams,
				sceneNode,

				// TODO: this collision shape is never released!
				new btBoxShape(btVector3(halfExtends.X, halfExtends.Y, halfExtends.Z)),

				staticObject == false);

			// add scene node to control
			m_worldObjects.push_back(worldObject);

			return worldObject;
		}

		//------------------------------------------------------------------------------
		//! Adds scene node
		//!
		CPhysicsObject* CBulletPhysics::addSphere(
			scene::ISceneNode* sceneNode,
			f32 radius,
			SPhysicsParams* physicsParams,
			bool autoCalculate,
			bool staticObject
		)
		{
			//core::vector3df halfExtends;

			if (autoCalculate)
			{
				if (sceneNode->getType() == scene::ESNT_ANIMATED_MESH)
				{
					//getHalfExtends(sceneNode, halfExtends);

					if (sceneNode->getBoundingBox().isEmpty())
					{
						RepairBoundingBox((scene::IAnimatedMeshSceneNode*)sceneNode);
					}

					radius = GetMaxRadius(sceneNode->getBoundingBox(), sceneNode->getScale()) * 0.5f;
				}
			}

			CPhysicsObject* worldObject = new CPhysicsObject(
				this,
				physicsParams,
				sceneNode,

				// TODO: this collision shape is never released!
				new btSphereShape(radius),

				staticObject == false);

			// add scene node to control
			m_worldObjects.push_back(worldObject);

			return worldObject;
		}

		//------------------------------------------------------------------------------
		//! Adds scene node
		//!
		CPhysicsObject* CBulletPhysics::addCylinder(
			scene::ISceneNode* sceneNode,
			core::vector3df& halfExtends,
			SPhysicsParams* physicsParams,
			bool autoCalculate,
			bool staticObject
		)
		{
			if (autoCalculate)
			{
				if (sceneNode->getType() == scene::ESNT_ANIMATED_MESH)
				{
					getHalfExtends(sceneNode, halfExtends);
				}
			}

			CPhysicsObject* worldObject = new CPhysicsObject(
				this,
				physicsParams,
				sceneNode,

				// TODO: this collision shape is never released!
				new btCylinderShape(btVector3(halfExtends.X, halfExtends.Y, halfExtends.Z)),

				staticObject == false);

			// add scene node to control
			m_worldObjects.push_back(worldObject);

			return worldObject;
		}

		//------------------------------------------------------------------------------
		//! Adds a terrain object
		CPhysicsObject* CBulletPhysics::addTerrain(
			scene::ISceneNode* sceneNode,
			SPhysicsParams* physicsParams,
			bool useQuantizedAabbCompression
		)
		{
			return addConcaveMesh(
				sceneNode,
				NULL,
				physicsParams,
				useQuantizedAabbCompression,
				true
			);
		}

		//------------------------------------------------------------------------------
		//! Adds a concave mesh (ex. terrain) object
		CPhysicsObject* CBulletPhysics::addConcaveMesh(
			scene::ISceneNode* sceneNode,
			scene::IMesh* mesh,
			SPhysicsParams* physicsParams,
			bool useQuantizedAabbCompression,
			bool staticObject
		)
		{
			if (sceneNode == NULL) return NULL;

			btTriangleMesh* triangleMesh;
			irr::core::vector3df scaling = sceneNode->getScale(); // get node scaling

			if (sceneNode->getType() == scene::ESNT_TERRAIN )
			{
				triangleMesh = ConvertTerrainToBulletTriangleMesh((scene::ITerrainSceneNode*)sceneNode, scaling);
			}
			else
			{
				if (mesh == NULL) return NULL;
				triangleMesh = ConvertIrrMeshToBulletTriangleMesh(mesh, scaling);
			}

			CPhysicsObject* worldObject = new CPhysicsObject(
				this,
				physicsParams,
				sceneNode,

				// TODO: this collision shape is never released!
				new btBvhTriangleMeshShape(triangleMesh, useQuantizedAabbCompression),
				// new btConvexHullShape();

				staticObject == false);

			// add scene node to control
			m_worldObjects.push_back(worldObject);

			return worldObject;
		}

		//------------------------------------------------------------------------------
		//! Adds scene node
		//!
		btRigidBody* CBulletPhysics::AddRigidBody(float pMass, const btTransform& pStartTransform, btCollisionShape* pShape)
		{
			//rigidbody is dynamic if and only if mass is non zero, otherwise static
			bool isDynamic = (pMass != 0.0f);

			btVector3 localInertia(0, 0, 0);
			if (isDynamic) pShape->calculateLocalInertia(pMass, localInertia);

			btScalar linearDumping = 0.0f;
			btScalar angularDamping = 0.0f;
			btScalar friction = 0.5f;
			btScalar restitution = 0.3f;

			//using motionstate is recommended, it provides interpolation capabilities,
			// and only synchronizes 'active' objects
			btDefaultMotionState* myMotionState = new btDefaultMotionState(pStartTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(
				pMass,
				myMotionState,
				pShape,
				localInertia
			);

			rbInfo.m_friction = friction;
			rbInfo.m_restitution = restitution;
			rbInfo.m_linearDamping = linearDumping;
			rbInfo.m_angularDamping = angularDamping;

			btRigidBody* body = new btRigidBody(rbInfo);

			m_dynamicsWorld->addRigidBody(body, -1, -1);

			return body;
		}

#ifdef IRRBT_CHAR_ANIMATION_CONTROLLER

		void CBulletPhysics::AddCharacterController(CharacterContInfo *info)
		{
			m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

			btKinematicCharacterController* character = 0;
			btPairCachingGhostObject* ghostObject = new btPairCachingGhostObject();
			btConvexShape* characterShape = new btCapsuleShape(info->Width,info->height);

			btTransform trans;
			trans.setIdentity();
			trans.setOrigin(btVector3(info->origin.X, info->origin.Y, info->origin.Z));

			ghostObject->setWorldTransform(trans);
			ghostObject->setCollisionShape(characterShape);
			ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

			btScalar stepHeight = info->stepHeight;
			int upAxis = info->upAxis;

			character = new btKinematicCharacterController(ghostObject, characterShape, stepHeight, upAxis);
			m_dynamicsWorld->addCollisionObject(ghostObject, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);
			m_dynamicsWorld->addAction(character);

			info->character = character;
			info->ghostObject = ghostObject;

			info->Control = new IrrCharController(info);
			info->node->addAnimator(info->Control);
		}

#endif

		void CBulletPhysics::AddCollisionFilter(btOverlapFilterCallback *filter)
		{
			m_dynamicsWorld->getPairCache()->setOverlapFilterCallback(filter);
		}


		core::aabbox3d<f32> CBulletPhysics::GetBoundingBox(scene::ISceneNode* node)
		{
			core::aabbox3d<f32> extent;
			if (node) extent = node->getBoundingBox();
			if (extent.isEmpty())
			{
				extent.addInternalPoint(core::vector3df(-0.5, -0.5, -0.5));
				extent.addInternalPoint(core::vector3df(0.5, 0.5, 0.5));

#if 0

				gui::IGUIEnvironment* guienv = m_pIrrDevice->getGUIEnvironment();

				//NOTE - loading of (these) .X files will not work properly with Irrlicht 1.2,
				// unless CXAnimationPlayer.cpp is patched (bounding box wrong size)
				//Line 805, updateBoundingBoxFromAnimation(): Drop these 3 lines
				//		if (first)
				//			Box.reset(p);
				//		else
				guienv->addMessageBox(L"Error: ", L"Error in Irrlicht: Bounding box zero size - see IrrlichtObject::GetBoundingBox() code for patch");

#endif

			}

			return extent;
		}


		// -------------------------------------------------------

		btDebugDrawer::btDebugDrawer() :
			m_debugMode(0),
			m_debugNode(NULL)
		{
		}


		void btDebugDrawer::drawLine(const btVector3& from,const btVector3& to,const btVector3& fromColor, const btVector3& toColor)
		{
			//glBegin(GL_LINES);
			//	glColor3f(fromColor.getX(), fromColor.getY(), fromColor.getZ());
			//	glVertex3d(from.getX(), from.getY(), from.getZ());
			//	glColor3f(toColor.getX(), toColor.getY(), toColor.getZ());
			//	glVertex3d(to.getX(), to.getY(), to.getZ());
			//glEnd();

			//printf(">> TDebugNode::drawLine\n");

			if (m_debugNode != NULL)
			{
				core::vector3df v1, v2;
				BulletToIrr(from, v1);
				BulletToIrr(to, v2);

				// this solves the color bug in btRaycastVehicle
				btScalar r = fromColor.x();
				if (r <= 1) r *= 255;  // 0..1 to 0..255

				btScalar g = fromColor.y();
				if (g <= 1) g *= 255;  // 0..1 to 0..255

				btScalar b = fromColor.z();
				if (b <= 1) b *= 255;  // 0..1 to 0..255

				// handle bullet simplex debug color bug...
				//video::SColor icolor(255, (u32)fromColor.x() * 255.0, (u32)fromColor.y() * 255.0, (u32)fromColor.z() * 255.0);
				video::SColor icolor(255, (u32)r, (u32)g, (u32)b);

				video::S3DVertex vert1(v1, v1, icolor, core::vector2df());
				video::S3DVertex vert2(v2, v2, icolor, core::vector2df());

				m_debugNode->addLine(vert1, vert2);
			}
		}


		void btDebugDrawer::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
		{
			//printf(">> TDebugNode::drawLine2\n");

			drawLine(from, to, color, color);

			//	if (m_debugMode > 0)
			// {
			// 	glBegin(GL_LINES);
			// 	glColor4f(color.getX(), color.getY(), color.getZ(),1.f);
			// 	glVertex3d(from.getX(), from.getY(), from.getZ());
			// 	glVertex3d(to.getX(), to.getY(), to.getZ());
			// 	glEnd();
			// }
		}


		void btDebugDrawer::drawSphere (const btVector3& p, btScalar radius, const btVector3& color)
		{
			//printf(">> TDebugNode::drawSphere\n");

			//glColor4f (color.getX(), color.getY(), color.getZ(), btScalar(1.0f));
			//glPushMatrix ();
			//glTranslatef (p.getX(), p.getY(), p.getZ());

			//int lats = 5;
			//int longs = 5;

			//int i, j;
			//for(i = 0; i <= lats; i++) {
			//	btScalar lat0 = SIMD_PI * (-btScalar(0.5) + (btScalar) (i - 1) / lats);
			//	btScalar z0  = radius*sin(lat0);
			//	btScalar zr0 =  radius*cos(lat0);

			//	btScalar lat1 = SIMD_PI * (-btScalar(0.5) + (btScalar) i / lats);
			//	btScalar z1 = radius*sin(lat1);
			//	btScalar zr1 = radius*cos(lat1);

			//	glBegin(GL_QUAD_STRIP);
			//	for(j = 0; j <= longs; j++) {
			//		btScalar lng = 2 * SIMD_PI * (btScalar) (j - 1) / longs;
			//		btScalar x = cos(lng);
			//		btScalar y = sin(lng);

			//		glNormal3f(x * zr0, y * zr0, z0);
			//		glVertex3f(x * zr0, y * zr0, z0);
			//		glNormal3f(x * zr1, y * zr1, z1);
			//		glVertex3f(x * zr1, y * zr1, z1);
			//	}
			//	glEnd();
			//}

			//glPopMatrix();
		}


		void btDebugDrawer::drawBox (const btVector3& boxMin, const btVector3& boxMax, const btVector3& color, btScalar alpha)
		{
			//printf(">> TDebugNode::drawBox\n");

		//	btVector3 halfExtent = (boxMax - boxMin) * btScalar(0.5f);
		//	btVector3 center = (boxMax + boxMin) * btScalar(0.5f);
		//	//glEnable(GL_BLEND);     // Turn blending On
		//	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		//	glColor4f (color.getX(), color.getY(), color.getZ(), alpha);
		//	glPushMatrix ();
		//	glTranslatef (center.getX(), center.getY(), center.getZ());
		//	glScaled(2*halfExtent[0], 2*halfExtent[1], 2*halfExtent[2]);
		////	glutSolidCube(1.0);
		//	glPopMatrix ();
		//	//glDisable(GL_BLEND);
		}


		void	btDebugDrawer::drawTriangle(const btVector3& a,const btVector3& b,const btVector3& c,const btVector3& color,btScalar alpha)
		{
			//printf(">> TDebugNode::drawTriangle\n");

			////	if (m_debugMode > 0)
			//{
			//	const btVector3	n=btCross(b-a,c-a).normalized();
			//	glBegin(GL_TRIANGLES);
			//	glColor4f(color.getX(), color.getY(), color.getZ(),alpha);
			//	glNormal3d(n.getX(),n.getY(),n.getZ());
			//	glVertex3d(a.getX(),a.getY(),a.getZ());
			//	glVertex3d(b.getX(),b.getY(),b.getZ());
			//	glVertex3d(c.getX(),c.getY(),c.getZ());
			//	glEnd();
			//}
		}


		void	btDebugDrawer::setDebugMode(int debugMode)
		{
			m_debugMode = debugMode;
		}


		void	btDebugDrawer::draw3dText(const btVector3& location,const char* textString)
		{
			//printf(">> TDebugNode::drawTriangle\n");

			//glRasterPos3f(location.x(),  location.y(),  location.z());
			////BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),textString);
		}


		void	btDebugDrawer::reportErrorWarning(const char* warningString)
		{
			//printf(warningString);
		}


		void	btDebugDrawer::drawContactPoint(const btVector3& pointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color)
		{
			//printf(">> TDebugNode::drawContactPoint\n");

			//{
			//	btVector3 to=pointOnB+normalOnB*distance;
			//	const btVector3&from = pointOnB;
			//	glColor4f(color.getX(), color.getY(), color.getZ(),1.f);
			//	//glColor4f(0,0,0,1.f);

			//	glBegin(GL_LINES);
			//	glVertex3d(from.getX(), from.getY(), from.getZ());
			//	glVertex3d(to.getX(), to.getY(), to.getZ());
			//	glEnd();

			//
			//	glRasterPos3f(from.x(),  from.y(),  from.z());
			//	char buf[12];
			//	sprintf(buf," %d",lifeTime);
			//	//BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			//}
		}


	} // end of namespace physics
} // end of namespace irr
