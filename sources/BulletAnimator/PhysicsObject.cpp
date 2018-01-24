#include "PhysicsObject.h"
//#include "../utils.h"


namespace irr
{
	namespace physics
	{

		CPhysicsObject::CPhysicsObject(
			CBulletPhysics* physicsWorld,
			SPhysicsParams* physicsParams,
			scene::ISceneNode* sceneNode,
			btCollisionShape* collisionShape,
			bool animated)
		{
			m_physicsWorld = physicsWorld;

			m_mass = 1.0f;
			m_ccdThreshold = 0.0f;
			m_linearDamping = 0.0f;
			m_angularDamping = 0.0f;
			m_friction = 0.5f;
			m_restitution = 0.0f;
			m_filterGroup = 0;
			m_filterMask = 0;
			m_centerOfMassOffset = core::vector3df(0, 0, 0);

			if (physicsParams != NULL)
			{
				m_mass = physicsParams->Mass;
				m_ccdThreshold = physicsParams->CcdThreshold;
				m_linearDamping = physicsParams->LinearDamping;
				m_angularDamping = physicsParams->AngularDamping;
				m_friction = physicsParams->Friction;
				m_restitution = physicsParams->Restitution;
				m_centerOfMassOffset = physicsParams->CenterOfMassOffset;
				m_filterGroup = physicsParams->FilterGroup;
				m_filterMask = physicsParams->FilterMask;
			}

			m_selfCollisionShape = false;
			m_collisionShape = collisionShape;
			m_massOffsetShape = NULL;
			m_sceneNode = sceneNode;

			m_rigidBody = NULL;
			m_motionState = NULL;

			initPhysics();

			m_animator = NULL;
			if (animated)
			{
				m_animator = scene::CBulletPhysicsAnimator::CreateInstance(this);
				m_sceneNode->addAnimator(m_animator);
			}
		}


		CPhysicsObject::~CPhysicsObject(void)
		{
			// Remove body from btDynamicsWorld, cleanup
			if (m_physicsWorld && m_rigidBody) m_physicsWorld->getDynamicsWorld()->removeRigidBody(m_rigidBody);

			//SAFE_DELETE(m_motionState);
			if(m_motionState) {
				delete (m_motionState);	
				(m_motionState)=0;
			}
			//SAFE_DELETE(m_rigidBody);
			if(m_rigidBody) {
				delete (m_rigidBody);	
				(m_rigidBody)=0;
			}

			if (m_selfCollisionShape == true) {
				//SAFE_DELETE(m_collisionShape);
				if(m_collisionShape) {
					delete (m_collisionShape);	
					(m_collisionShape)=0;
				}
			}

			if (m_animator) m_animator->drop();
		}


		//------------------------------------------------------------------------------
		//! InitPhysics
		//! Adds body to btDynamicsWorld
		void CPhysicsObject::initPhysics(void)
		{
			//rigidbody is dynamic if and only if mass is non zero, otherwise static
			bool isDynamic = (isStatic() == false);

			// create collision shape
			core::aabbox3d<f32> box = m_sceneNode->getBoundingBox();
			core::vector3df extent = box.getExtent() / 2.0f;

			// default collision shape is a box
			if (m_collisionShape == NULL)
			{
				m_collisionShape = new btBoxShape(btVector3(extent.X, extent.Y, extent.Z));
				m_selfCollisionShape = true;
			}

			// body mass offset set = create the compound shape
			if (m_centerOfMassOffset.X != 0.0f || m_centerOfMassOffset.Y != 0.0f || m_centerOfMassOffset.Z != 0.0f)
			{
				m_massOffsetShape = new btCompoundShape();
				
				//localTrans effectively shifts the center of mass with respect to the chassis
				btTransform localTrans;
				localTrans.setIdentity();
				localTrans.setOrigin(
					btVector3(
						m_centerOfMassOffset.X, 
						m_centerOfMassOffset.Y, 
						m_centerOfMassOffset.Z
					)
				);

				m_massOffsetShape->addChildShape(localTrans, m_collisionShape);
			}

			btCollisionShape* collisionShape = m_collisionShape;
			if (m_massOffsetShape != NULL) collisionShape = m_massOffsetShape;

			// calculate inertia vector
			btVector3 localInertia(0, 0, 0);
			if (isDynamic) collisionShape->calculateLocalInertia(m_mass, localInertia);

			// calculate value for ccdThreshold
			// get max extend / 2.0
			f32 ret = 0;
			if (extent.X > ret) ret = extent.X;
			if (extent.Y > ret) ret = extent.Y;
			if (extent.Z > ret) ret = extent.Z;
			m_ccdThreshold = ret; // / 2.0f

			// evaluate start transform in terms of btTransform
			// and set offset of center of mass
			btTransform	startTransform;//, centerOfMassOffset;
			GetNodeTransform(m_sceneNode, startTransform);
			//centerOfMassOffset.setIdentity();
			//centerOfMassOffset.setOrigin(btVector3(
			//	m_centerOfMassOffset.X,
			//	m_centerOfMassOffset.Y, 
			//	m_centerOfMassOffset.Z)
			//);

			//using motionstate is recommended, it provides interpolation capabilities,
			//and only synchronizes 'active' objects
			//m_motionState = new btDefaultMotionState(startTransform, centerOfMassOffset);
			m_motionState = new btDefaultMotionState(startTransform);

			// create body
			btRigidBody::btRigidBodyConstructionInfo rigidBodyInfo(
				m_mass,
				m_motionState,
				collisionShape,
				localInertia
			);

			m_rigidBody = new btRigidBody(rigidBodyInfo);
			if (isDynamic == false) m_rigidBody->setCollisionFlags(
				m_rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT
			);

			m_rigidBody->setUserPointer((void *)m_sceneNode);

			// add body to the world
			//m_physicsWorld->getDynamicsWorld()->addRigidBody(m_rigidBody, m_filterGroup, m_filterMask);
			m_physicsWorld->getDynamicsWorld()->addRigidBody(m_rigidBody);

			// Only do CCD if  motion in one timestep (1.f/60.f) exceeds half dims
			m_rigidBody->setCcdMotionThreshold(m_ccdThreshold);

			//Experimental: better estimation of CCD Time of Impact:
			m_rigidBody->setCcdSweptSphereRadius(0.2f * m_ccdThreshold);
		}

		//------------------------------------------------------------------------------

		void CPhysicsObject::animate(void)
		{
			if (m_mass != 0.0f && m_rigidBody && m_rigidBody->getMotionState())
			{

#if 1

# if 1

				// update the chassis position and rotation
				btTransform objectWorldTrans;
				m_rigidBody->getMotionState()->getWorldTransform(objectWorldTrans);

				// set pos
				btVector3 &p = objectWorldTrans.getOrigin();
				m_sceneNode->setPosition(core::vector3df(p.getX(), p.getY(), p.getZ()));

				// set rot
				core::vector3df rot;
				btQuaternion btq = objectWorldTrans.getRotation();
				QuaternionToEulerXYZ(btq, rot);
				rot *= BPU_180_PI;
				m_sceneNode->setRotation(rot);

# else
				core::matrix4 mat;
				btTransform objectWorldTrans;
				m_rigidBody->getMotionState()->getWorldTransform(objectWorldTrans);
				objectWorldTrans.getOpenGLMatrix((btScalar*)&mat);
				m_sceneNode->setPosition(mat.getTranslation());
				m_sceneNode->setRotation(mat.getRotationDegrees());

# endif

#else

				// set pos
				btVector3 p = m_rigidBody->getCenterOfMassPosition();
				m_sceneNode->setPosition(core::vector3df(p.getX(), p.getY(), p.getZ()));

				// set rot
				core::vector3df rot;
				btQuaternion btq = m_rigidBody->getOrientation();
				QuaternionToEulerXYZ(btq, rot);
				rot *= BPU_180_PI;
				m_sceneNode->setRotation(rot);

#endif

			}

		}


		void CPhysicsObject::removeAnimator(void)
		{
			if (m_animator != NULL)
			{
				m_sceneNode->removeAnimator(m_animator);
				m_animator->drop();
				m_animator = NULL;
			}
		}

		//------------------------------------------------------------------------------
		//! setPosition
		//! Set animator position
		void CPhysicsObject::setPosition(const core::vector3df& v) const
		{
			_IRR_DEBUG_BREAK_IF(m_rigidBody == NULL);

			btTransform t = m_rigidBody->getWorldTransform();
			btVector3 btv(v.X, v.Y, v.Z);
			t.setOrigin(btv);
			m_rigidBody->setWorldTransform(t);
		}

		//------------------------------------------------------------------------------
		//! getPosition
		//! Get wobject position
		core::vector3df CPhysicsObject::getPosition(void) const
		{
			_IRR_DEBUG_BREAK_IF(m_rigidBody == NULL);

			btVector3 p = m_rigidBody->getCenterOfMassPosition();
			return core::vector3df(p.getX(), p.getY(), p.getZ());
		}

		//------------------------------------------------------------------------------
		//! setRotation
		//! Set animator rotation (v measured in radians)
		void CPhysicsObject::setRotation(const core::vector3df& v) const
		{
			_IRR_DEBUG_BREAK_IF(m_rigidBody == NULL);

			btTransform t = m_rigidBody->getWorldTransform();
			btQuaternion btq;
			EulerXYZToQuaternion(v, btq);
			t.setRotation(btq);
			m_rigidBody->setWorldTransform(t);
		}

		//------------------------------------------------------------------------------
		//! getRotation
		//! Get animator rotation
		core::vector3df CPhysicsObject::getRotation(void) const
		{
			_IRR_DEBUG_BREAK_IF(m_rigidBody == NULL);

			core::vector3df rot;
			btQuaternion btq = m_rigidBody->getOrientation();
			QuaternionToEulerXYZ(btq, rot);
			rot *= BPU_360_PI2;

			return rot;
		}

		//------------------------------------------------------------------------------
		//! setLinearVelocity
		//! Set animator linear vel
		void CPhysicsObject::setLinearVelocity(const core::vector3df& vel) const
		{
			_IRR_DEBUG_BREAK_IF(m_rigidBody == NULL);

			//bullet hangs if attempt to set lin. or ang. velocity on static object
			if (isStatic() == false)
			{
				m_rigidBody->setLinearVelocity(btVector3(vel.X, vel.Y, vel.Z));
			}

			// note - apparently, need to use motion state on kinematic objects, and rigid body functions
			// on dynamic rigid bodies to change pos / rot etc.
		}

		//------------------------------------------------------------------------------
		//! getLinearVelocity
		//! Get animator linear vel
		core::vector3df CPhysicsObject::getLinearVelocity(void) const
		{
			_IRR_DEBUG_BREAK_IF(m_rigidBody == NULL);

			// static bodies have no linear velocity
			if (isStatic() == false) return core::vector3df(0, 0, 0);

			btVector3 btV = m_rigidBody->getLinearVelocity();
			return core::vector3df(btV.getX(), btV.getY(), btV.getZ());
		}

		//------------------------------------------------------------------------------
		//! setLinearVelocity
		//! Set animator linear vel
		void CPhysicsObject::setAngularVelocity(const core::vector3df & vel) const
		{
			_IRR_DEBUG_BREAK_IF(m_rigidBody == NULL);

			//bullet hangs if attempt to set lin. or ang. velocity on static object
			if (isStatic() == false)
			{
				m_rigidBody->setAngularVelocity(btVector3(vel.X, vel.Y, vel.Z));
			}
		}

		//------------------------------------------------------------------------------
		//! getAngularVelocity
		//! Get animator angular vel
		core::vector3df CPhysicsObject::getAngularVelocity() const
		{
			_IRR_DEBUG_BREAK_IF(m_rigidBody == NULL);

			if (isStatic() == 0.0f)	return core::vector3df(0,0,0);

			btVector3 btV = m_rigidBody->getAngularVelocity();
			return core::vector3df(btV.getX(), btV.getY(), btV.getZ());
		}

		//------------------------------------------------------------------------------
		//! applyImpulse
		//! Apply impulse to object
		void CPhysicsObject::applyImpulse(
			const core::vector3df& force,
			const core::vector3df& rel_pos /* = core::vector3df(0,0,0)*/
			) const
		{
			_IRR_DEBUG_BREAK_IF(m_rigidBody == NULL);

			m_rigidBody->applyImpulse(
				btVector3(force.X, force.Y, force.Z),
				btVector3(rel_pos.X, rel_pos.Y, rel_pos.Z)
				);

			m_rigidBody->activate();
		}

		//------------------------------------------------------------------------------
		//! applyForce
		//! Apply force to object
		void CPhysicsObject::applyForce(
			const core::vector3df& force,
			const core::vector3df& rel_pos
			/* = core::vector3df(0,0,0)*/
			) const
		{
			_IRR_DEBUG_BREAK_IF(m_rigidBody == NULL);

			m_rigidBody->applyForce(
				btVector3(force.X, force.Y, force.Z),
				btVector3(rel_pos.X, rel_pos.Y, rel_pos.Z)
				);

			m_rigidBody->activate();
		}

		//------------------------------------------------------------------------------
		//! zeroForces
		//! Zero all forces
		void CPhysicsObject::zeroForces(void)
		{
			_IRR_DEBUG_BREAK_IF(m_rigidBody == NULL);

			m_rigidBody->setLinearVelocity(btVector3(0,0,0));
			m_rigidBody->setAngularVelocity(btVector3(0,0,0));
		}

		//------------------------------------------------------------------------------
		//! setActivationState
		//! Zero all forces
		void CPhysicsObject::setActivationState(bool active)
		{
			_IRR_DEBUG_BREAK_IF(m_rigidBody == NULL);

			m_rigidBody->setActivationState((active) ? 1 : 0);
		}


		//------------------------------------------------------------------------------
		//! activate
		//! Zero all forces
		void CPhysicsObject::activate(bool force)
		{
			_IRR_DEBUG_BREAK_IF(m_rigidBody == NULL);

			m_rigidBody->activate(force);
		}

	} // end of namespace physics
} // end of namespace irr
