#ifndef C_PHYSICS_OBJECT_H
#define C_PHYSICS_OBJECT_H

// Irrlicht
#include "irrlicht.h"
using namespace irr;

// Bullet
#include <btBulletDynamicsCommon.h>

#include "CBulletPhysics.h"
#include "CBulletPhysicsUtils.h"


namespace irr
{

	namespace scene
	{
		class CBulletPhysicsAnimator;
	}

	namespace physics
	{

		class CBulletPhysics;

		class CPhysicsObject
		{
		public:

			CPhysicsObject(
				CBulletPhysics* physicsWorld, 
				SPhysicsParams* physicsParams,
				scene::ISceneNode* sceneNode,
				btCollisionShape* collisionShape = 0,
				bool animated = true);

			~CPhysicsObject(void);

			bool isStatic(void) const { return m_mass == 0.0f; }

			f32 getMass(void) { return m_mass; }
			f32 getCcdThreshold(void) { return m_ccdThreshold; }
			f32 getLinearDamping(void) { return m_linearDamping; }
			f32 getAngularDamping(void) { return m_angularDamping; }
			f32 getFriction(void) { return m_friction; } 
			f32 getRestitution(void) { return m_restitution; }
			core::vector3df& getCenterOfMassOffset(void) { return m_centerOfMassOffset; }


			scene::ISceneNode* getNode(void) { return m_sceneNode; }
			btCollisionShape* getCollisionShape(void) { return m_collisionShape; }
			btRigidBody* getRigidBody(void) { return m_rigidBody; }
			btDefaultMotionState* getMotionState(void) { return m_motionState; }
			scene::CBulletPhysicsAnimator* getAnimator(void) { return m_animator; }


			void animate(void);

			void removeAnimator(void);

			core::vector3df getPosition(void) const;
			void setPosition(const core::vector3df& newPosition) const;

			core::vector3df getRotation(void) const;
			void setRotation(const core::vector3df& v) const;

			core::vector3df getLinearVelocity(void) const;
			void setLinearVelocity(const core::vector3df& vel = core::vector3df(0,0,0)) const;

			core::vector3df getAngularVelocity(void) const;
			void setAngularVelocity(const core::vector3df & vel = core::vector3df(0,0,0)) const;

			void applyImpulse(
				const core::vector3df& force,
				const core::vector3df& rel_pos = core::vector3df(0.0f, 0.0f, 0.0f)) const;

			void applyForce(
				const core::vector3df& force, 
				const core::vector3df& rel_pos = core::vector3df(0.0f, 0.0f, 0.0f)) const;

			void zeroForces(void);

			void setActivationState(bool active);
			void activate(bool force);


		private:

			// the physics world
			CBulletPhysics* m_physicsWorld;

			// physics atributes
			f32 m_mass;
			f32 m_ccdThreshold;
			f32 m_linearDamping;
			f32 m_angularDamping;
			f32 m_friction;
			f32 m_restitution;
			core::vector3df m_centerOfMassOffset;
			short m_filterGroup, m_filterMask;

			btRigidBody* m_rigidBody;
			btDefaultMotionState* m_motionState;
			scene::ISceneNode* m_sceneNode;

			bool m_selfCollisionShape;
			btCollisionShape* m_collisionShape;
			btCompoundShape* m_massOffsetShape;

			scene::CBulletPhysicsAnimator* m_animator;

			void initPhysics(void);
		};

	} // end of namespace physics
} // end of namespace irr

#endif
