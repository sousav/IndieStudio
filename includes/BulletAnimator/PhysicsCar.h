#pragma once

// Bullet
#include <btBulletDynamicsCommon.h>
#include <BulletDynamics/Vehicle/btRaycastVehicle.h>

#include "CBulletPhysics.h"
#include <math.h>

enum CAR_DRIVE {
	FWD,
	RWD,
	AWD
};

namespace irr
{
	namespace physics
	{
		class PhysicsCar
		{
		public:

			PhysicsCar(
				CBulletPhysics* bulletPhysicsSystem,
				scene::IAnimatedMeshSceneNode* carNode,
                scene::IAnimatedMeshSceneNode* carCollision,
				scene::IAnimatedMeshSceneNode* wheelNode_FL,
				scene::IAnimatedMeshSceneNode* wheelNode_FR,
				scene::IAnimatedMeshSceneNode* wheelNode_RL,
				scene::IAnimatedMeshSceneNode* wheelNode_RR
			);

			~PhysicsCar(void);

			bool init(physics::SPhysicsCarParams *carParams);
			void reset(void);
			void update(s32 car_drive, f32 max_speed, bool reverse);

			float getEngineForce(void) const { return m_engineForce; }
			void setEngineForce(float newForce) { m_engineForce = newForce; }

			float getBreakingForce(void) const { return m_breakingForce; }
			void setBreakingForce(float newForce) { m_breakingForce = newForce; }

            float getSteeringValue(void) const { return m_vehicleSteering; }
			void setSteeringValue(float newForce) { m_vehicleSteering = newForce; }


            float getRPM() { return this->rpm; }
            float getGear() { return this->gear; }

			void resetSteering(void)
			{
				if(m_vehicleSteering != 0)
					//m_vehicleSteering = m_carParams.SteeringIncrement;
					m_vehicleSteering = 0.f;
			}

            void steer(float ratio = 0)
			{
                m_vehicleSteering = m_carParams.SteeringClamp * ratio;
			}
            void move(float ratio = 0)
            {
                m_engineForce = m_carParams.MaxEngineForce * (ratio < 0 ? ratio / 2 : ratio);
            }
            void brake(float ratio = 0)
            {
                m_breakingForce = (ratio > 0.9 ? m_carParams.MaxBreakingForce + 100 : m_carParams.MaxBreakingForce) * ratio;
            }

			void steerRight()
			{
                m_vehicleSteering += m_carParams.SteeringIncrement;
				if (m_vehicleSteering > m_carParams.SteeringClamp) m_vehicleSteering = m_carParams.SteeringClamp;
			}


			void steerLeft()
			{
                m_vehicleSteering -= m_carParams.SteeringIncrement;
				if (m_vehicleSteering < -m_carParams.SteeringClamp) m_vehicleSteering = -m_carParams.SteeringClamp;
			}


			void goForward(void)
			{
				m_engineForce = m_carParams.MaxEngineForce;
				m_breakingForce = 0.0f;
			}


			void goBackwards(void)
			{
				m_engineForce -= m_carParams.MaxEngineForce;
				if(m_engineForce < -2500)	m_engineForce = -2500.f;
				m_breakingForce = 10.0f;
				//printf("eng force: %f", m_engineForce);
			}


			void stop(void)
			{
				m_breakingForce = m_carParams.MaxBreakingForce;
				m_engineForce = 0.0f;
			}


			void slowdown(void)
			{
				irr::f32 bla = m_carParams.MaxBreakingForce;
				m_breakingForce = bla/2;
				m_engineForce = 0.0f;
			}


			void handbrake(void)
			{
				m_breakingForce = m_carParams.MaxBreakingForce+100.f;
				m_engineForce = 0.0f;
			}

			//returning car's speed...
			irr::f32 getlinVel(void);

			//angle
			btScalar getAngle(void);

			core::vector3df getPosition(void);
			void setPosition(core::vector3df const& v);

            core::vector3df getRotation(bool mult = true) const;
			void setRotation(irr::core::vector3df const &rot);

            physics::CPhysicsObject *getChassis() const {
                return this->m_chassisObject;
            }

            virtual irr::core::vector3df const getAngularVelocity() const;
            void setAngularVelocity(irr::core::vector3df const &vec);
            virtual irr::core::vector3df const getLinearVelocity() const;
            void setLinearVelocity(irr::core::vector3df const &vec);

            void changeMesh(int id, irr::scene::ISceneManager *sm);

		private:

			//core::vector3df m_chassisOffset;

			core::vector3df linvel;
			irr::f32 vel;

			CBulletPhysics* m_bulletPhysicsSystem;
			btDynamicsWorld* m_dynamicsWorld;

			// actual forces for engine and brakes
			f32 m_engineForce;
			f32 m_breakingForce;

			// the steering angle (0 for no steering)
			f32 m_vehicleSteering;

			// parameters used for building the car
			physics::SPhysicsCarParams m_carParams;

			// physics representation of the car chassis
			physics::CPhysicsObject* m_chassisObject;

			// the car's raycaster
			btRaycastVehicle::btVehicleTuning m_tuning;
			btVehicleRaycaster* m_vehicleRayCaster;
			btRaycastVehicle* m_vehicle;

            irr::s32 gear, rpm;
            irr::f32 ratio, wheels, maxrpm, minrpm;

			// scene nodes (visual objects)
			scene::IAnimatedMeshSceneNode* m_chassisNode;
            scene::IAnimatedMeshSceneNode* m_chassisCollision;
			scene::IAnimatedMeshSceneNode* m_wheelNode_FL;
			scene::IAnimatedMeshSceneNode* m_wheelNode_FR;
			scene::IAnimatedMeshSceneNode* m_wheelNode_RL;
			scene::IAnimatedMeshSceneNode* m_wheelNode_RR;

            irr::scene::IAnimatedMeshSceneNode* loadMeshFromFile(const char* filename, irr::scene::ISceneManager *sm);
		};

	} // end of namespace physics
} // end of namespace irr
