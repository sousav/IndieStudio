#include "PhysicsCar.h"


namespace irr
{
	namespace physics
	{

		PhysicsCar::PhysicsCar(
			CBulletPhysics* bulletPhysicsSystem,
			scene::IAnimatedMeshSceneNode* carNode,
            scene::IAnimatedMeshSceneNode* carCollision,
			scene::IAnimatedMeshSceneNode* wheelNode_FL,
			scene::IAnimatedMeshSceneNode* wheelNode_FR,
			scene::IAnimatedMeshSceneNode* wheelNode_RL,
			scene::IAnimatedMeshSceneNode* wheelNode_RR
		)
		{
			m_bulletPhysicsSystem = bulletPhysicsSystem;
			m_dynamicsWorld = m_bulletPhysicsSystem->getDynamicsWorld();

			m_engineForce = 0.0f;
			m_breakingForce = 0.0f;
			m_vehicleSteering = 0.0f;

			m_vehicleRayCaster = NULL;
			m_vehicle = NULL;

			m_chassisObject = NULL;
			m_chassisNode = carNode;

            m_chassisCollision = carCollision;

			m_wheelNode_FL = wheelNode_FL;
			m_wheelNode_FR = wheelNode_FR;
			m_wheelNode_RL = wheelNode_RL;
			m_wheelNode_RR = wheelNode_RR;

            gear = 1;

            wheels = 25.f;
			maxrpm = 4500.f;
			minrpm = 1500.f;
		}


		PhysicsCar::~PhysicsCar(void)
		{
			if (m_vehicleRayCaster != NULL) {
                delete m_vehicleRayCaster;
            }
            m_dynamicsWorld->removeAction(m_vehicle);
            delete m_vehicle;

            delete m_chassisObject;

			//if (m_chassisObject != NULL) delete m_chassisObject;  // never delete - it is done by physics world
		}


		bool PhysicsCar::init(physics::SPhysicsCarParams *carParams)
		{
			if (carParams == NULL) return false;

			m_carParams = *carParams;

            // CPhysicsGeometry chassi_geom;
            // chassi_geom.type = CPhysicsGeometryTypes::CBPAGT_CONCAVE_MESH;
			// chassi_geom.node = m_chassisNode;
			// chassi_geom.AutoCalculate = true;
            // chassi_geom.mesh.irrMesh = m_chassisCollision->getMesh();
			//
            core::vector3df halfExtends(1, 1, 1);
            // m_chassisObject = m_bulletPhysicsSystem->createWorldObject(
            //     m_chassisCollision,
            //     &chassi_geom,
			// 	&m_carParams
			// );
			m_chassisObject = m_bulletPhysicsSystem->addBox(
				m_chassisNode,
				halfExtends,
				&m_carParams,
				true,						// we need the collision shape calculated authomaticaly
				false						// this is not a static object, so the irr. animator will be created
			);

			// we are using our own animator
			m_chassisObject->removeAnimator();

			//m_chassisObject->getRigidBody()->setDamping(0.2,0.2);

			reset();

			// create vehicle
			m_vehicleRayCaster = new btDefaultVehicleRaycaster(m_dynamicsWorld);
			m_vehicle = new btRaycastVehicle(
				m_tuning,
				m_chassisObject->getRigidBody(),
				m_vehicleRayCaster
			);

			///never deactivate the vehicle
			m_chassisObject->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);

			// add the car to the physics world
			m_dynamicsWorld->addAction(m_vehicle);


			// car axes definition
			s32 rightIndex = 0;
			s32 upIndex = 1;
			s32 forwardIndex = 2;

			//choose coordinate system
			m_vehicle->setCoordinateSystem(rightIndex, upIndex, forwardIndex);

			// wheel joints
			btVector3 m_wheelDirectionCS0 = btVector3(0,-1,0);
			btVector3 m_wheelAxleCS = btVector3(-1, 0, 0);

			f32 carBodyOffset = m_carParams.CarBodyOffset;
			f32 frontWheelAxeOffset = m_carParams.FrontAxeOffset;
			f32 frontWheelAxeHalfWidth = m_carParams.FrontAxeHalfWidth;
			f32 rearWheelAxeOffset = m_carParams.RearAxeOffset;
			f32 rearWheelAxeHalfWidth = m_carParams.RearAxeHalfWidth;

			bool isFrontWheel = true;

			// front left
			btVector3 connectionPointCS0 = btVector3(
				-frontWheelAxeHalfWidth,
				carBodyOffset,
				frontWheelAxeOffset
			);

			btWheelInfo& wheel_FL = m_vehicle->addWheel(
				connectionPointCS0,
				m_wheelDirectionCS0,
				m_wheelAxleCS,
				m_carParams.SuspensionRestLength,
				m_carParams.WheelRadius,
				m_tuning,
				isFrontWheel
			);

			wheel_FL.m_suspensionStiffness = m_carParams.SuspensionStiffness;
			wheel_FL.m_wheelsDampingRelaxation = m_carParams.SuspensionDamping;
			wheel_FL.m_wheelsDampingCompression = m_carParams.SuspensionCompression;
			wheel_FL.m_frictionSlip = m_carParams.WheelFriction;
			wheel_FL.m_rollInfluence = m_carParams.RollInfluence;
			wheel_FL.m_clientInfo = (void*)m_wheelNode_FL;


			// front right
			connectionPointCS0 = btVector3(
				frontWheelAxeHalfWidth,
				carBodyOffset,
				frontWheelAxeOffset
			);

			btWheelInfo& wheel_FR = m_vehicle->addWheel(
				connectionPointCS0,
				m_wheelDirectionCS0,
				m_wheelAxleCS,
				m_carParams.SuspensionRestLength,
				m_carParams.WheelRadius,
				m_tuning,
				isFrontWheel
			);

			wheel_FR.m_suspensionStiffness = m_carParams.SuspensionStiffness;
			wheel_FR.m_wheelsDampingRelaxation = m_carParams.SuspensionDamping;
			wheel_FR.m_wheelsDampingCompression = m_carParams.SuspensionCompression;
			wheel_FR.m_frictionSlip = m_carParams.WheelFriction;
			wheel_FR.m_rollInfluence = m_carParams.RollInfluence;
			wheel_FR.m_clientInfo = (void*)m_wheelNode_FR;


			// rear left
			isFrontWheel = false;

			connectionPointCS0 = btVector3(
				-rearWheelAxeHalfWidth,
				carBodyOffset,
				rearWheelAxeOffset
			);

			btWheelInfo& wheel_RL = m_vehicle->addWheel(
				connectionPointCS0,
				m_wheelDirectionCS0,
				m_wheelAxleCS,
				m_carParams.SuspensionRestLength,
				m_carParams.WheelRadius,
				m_tuning,
				isFrontWheel
			);

			wheel_RL.m_suspensionStiffness = m_carParams.SuspensionStiffness;
			wheel_RL.m_wheelsDampingRelaxation = m_carParams.SuspensionDamping;
			wheel_RL.m_wheelsDampingCompression = m_carParams.SuspensionCompression;
			wheel_RL.m_frictionSlip = m_carParams.WheelFriction;
			wheel_RL.m_rollInfluence = m_carParams.RollInfluence;
			wheel_RL.m_clientInfo = (void*)m_wheelNode_RL;


			// rear right
			connectionPointCS0 = btVector3(
				rearWheelAxeHalfWidth,
				carBodyOffset,
				rearWheelAxeOffset
			);

			btWheelInfo& wheel_RR = m_vehicle->addWheel(
				connectionPointCS0,
				m_wheelDirectionCS0,
				m_wheelAxleCS,
				m_carParams.SuspensionRestLength,
				m_carParams.WheelRadius,
				m_tuning,
				isFrontWheel
			);

			wheel_RR.m_suspensionStiffness = m_carParams.SuspensionStiffness;
			wheel_RR.m_wheelsDampingRelaxation = m_carParams.SuspensionDamping;
			wheel_RR.m_wheelsDampingCompression = m_carParams.SuspensionCompression;
			wheel_RR.m_frictionSlip = m_carParams.WheelFriction;
			wheel_RR.m_rollInfluence = m_carParams.RollInfluence;
			wheel_RR.m_clientInfo = (void*)m_wheelNode_RR;

			return true;
		}

		void PhysicsCar::reset(void)
		{
			m_vehicleSteering = 0.0f;

			btRigidBody* chassisBody = m_chassisObject->getRigidBody();

			chassisBody->setCenterOfMassTransform(btTransform::getIdentity());
			chassisBody->setLinearVelocity(btVector3(0, 0, 0));
			chassisBody->setAngularVelocity(btVector3(0, 0, 0));

			m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(
				chassisBody->getBroadphaseHandle(),
				m_dynamicsWorld->getDispatcher()
			);

			if (m_vehicle)
			{
				m_vehicle->resetSuspension();
				for (int i = 0; i < m_vehicle->getNumWheels(); i++)
				{
					//synchronize the wheels with the (interpolated) chassis worldtransform
					m_vehicle->updateWheelTransform(i, true);
				}
			}
		}


		void PhysicsCar::update(s32 car_drive, f32 max_speed, bool reverse)
		{
			switch (car_drive) {
				case RWD: {
					//for rear wheel drive cars
					for (int i = 0; i < m_vehicle->getNumWheels(); i++)
					{
						if (m_vehicle->getWheelInfo(i).m_bIsFrontWheel == true)
						{
							if( vel > max_speed ) {
								m_engineForce = 0.0f;
								//m_breakingForce = 0.0f;
							}
							//printf("speed: %f", vel);

							m_vehicle->setSteeringValue(m_vehicleSteering, i);
							m_vehicle->setBrake(m_breakingForce, i);
						}
						else
						{
							m_vehicle->applyEngineForce(m_engineForce, i);
							m_vehicle->setBrake(m_breakingForce, i);
						}
					}
				}break;
				case FWD: {
					//for front wheel drive cars
					for (int i = 0; i < m_vehicle->getNumWheels(); i++)
					{
						if (m_vehicle->getWheelInfo(i).m_bIsFrontWheel == true)
						{
							if( vel > max_speed ) {
								m_engineForce = 0.0f;
								//m_breakingForce = 0.0f;
							}
							//printf("speed: %f", vel);

							m_vehicle->setSteeringValue(m_vehicleSteering, i);
							m_vehicle->applyEngineForce(m_engineForce, i);
							//m_vehicle->setBrake(m_breakingForce, i);
						}
						else
						{
							m_vehicle->setBrake(m_breakingForce, i);
						}
					}
				}break;
				case AWD: {
					//for 4x4 wheel drive cars
					for (int i = 0; i < m_vehicle->getNumWheels(); i++)
					{
						if (m_vehicle->getWheelInfo(i).m_bIsFrontWheel == true)
						{
							if( vel > max_speed ) {
								m_engineForce = 0.0f;
								//m_breakingForce = 0.0f;
							}
							//printf("speed: %f", vel);

							m_vehicle->setSteeringValue(m_vehicleSteering, i);
							m_vehicle->applyEngineForce(m_engineForce * 0.5f, i);   // TODO: allow different force distribution
							m_vehicle->setBrake(m_breakingForce * 0.75f, i);		// TODO: allow different force distribution
						}
						else
						{
							m_vehicle->applyEngineForce(m_engineForce * 0.5f, i);	// TODO: allow different force distribution
							m_vehicle->setBrake(m_breakingForce * 1.0, i);			// TODO: allow different force distribution
						}
					}
				}break;
			}


			//btScalar m[16];
			core::matrix4 mat;

#if 1

			// update the chassis position and rotation
			btTransform chassisWorldTrans;
			m_chassisObject->getRigidBody()->getMotionState()->getWorldTransform(chassisWorldTrans);

			// set pos
			btVector3 &p = chassisWorldTrans.getOrigin();
			//btVector3 p = m_chassisObject->getRigidBody()->getCenterOfMassPosition();
			m_chassisNode->setPosition(core::vector3df(p.getX(), p.getY(), p.getZ()));

			//// set rot
			core::vector3df rot;
			btQuaternion btq = chassisWorldTrans.getRotation();
			QuaternionToEulerXYZ(btq, rot);
			rot *= BPU_180_PI;
			m_chassisNode->setRotation(rot);

#else

			//core::matrix4 mat;
			btTransform chassisWorldTrans;
			m_chassisObject->getRigidBody()->getMotionState()->getWorldTransform(chassisWorldTrans);
			chassisWorldTrans.getOpenGLMatrix((btScalar*)&mat);
			m_chassisNode->setPosition(mat.getTranslation());
			m_chassisNode->setRotation(mat.getRotationDegrees());

#endif


			//draw wheels
			for (int i = 0; i < m_vehicle->getNumWheels(); i++)
			{
				//synchronize the wheels with the (interpolated) chassis worldtransform
				m_vehicle->updateWheelTransform(i, true);

				scene::IAnimatedMeshSceneNode* wheelNode =
					(scene::IAnimatedMeshSceneNode*)m_vehicle->getWheelInfo(i).m_clientInfo;

				if (wheelNode != NULL)
				{
#if 0

					// this works too
					m_vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix((btScalar*)&mat);
					wheelNode->setPosition(mat.getTranslation());
					wheelNode->setRotation(mat.getRotationDegrees());

#else

					// set pos
					btVector3 &p = m_vehicle->getWheelInfo(i).m_worldTransform.getOrigin();
					wheelNode->setPosition(core::vector3df(p.getX(), p.getY(), p.getZ()));

					// set rot
					core::vector3df rot;
					btQuaternion btq = m_vehicle->getWheelInfo(i).m_worldTransform.getRotation();
					QuaternionToEulerXYZ(btq, rot);
					rot *= BPU_180_PI;
					wheelNode->setRotation(rot);
#endif

				}
			}

            vel = getlinVel();

            switch(gear)
            {
                case 0: ratio = 3.38f;	//reverse
                    break;
                case 1: ratio = 3.47f;
                    break;
                case 2: ratio = 2.47f;
                    break;
                case 3: ratio = 1.73f;
                    break;
                case 4: ratio = 1.30f;
                    break;
                case 5: ratio = 1.04f;
                    break;
                case 6: ratio = 0.76f;
                    break;
                default: ratio = 2.97f;
            }

            //calculate rpm
            rpm = vel*ratio*wheels;

            if( rpm > maxrpm && gear < 6  && !reverse ) {
                gear++;
            }
            else if ( rpm < minrpm && gear > 1 )
                --gear;
            else if ( reverse )
                gear = 0;
            else if ( !reverse && gear == 0 )
                gear = 1;

		}


		core::vector3df PhysicsCar::getPosition(void)
		{
			btTransform chassisWorldTrans;
			m_chassisObject->getRigidBody()->getMotionState()->getWorldTransform(chassisWorldTrans);

			// get the position
			btVector3 p = chassisWorldTrans.getOrigin();

			return core::vector3df(p.getX(), p.getY(), p.getZ());
		}

		//returning car's speed...
		irr::f32 PhysicsCar::getlinVel(void)
		{
			btRigidBody* chassisBody = m_chassisObject->getRigidBody();
			linvel.X = chassisBody->getLinearVelocity().getX();
			linvel.Y = chassisBody->getLinearVelocity().getY();
			linvel.Z = chassisBody->getLinearVelocity().getZ();

			vel = 3.6f * sqrt(pow(linvel.X, 2) + pow(linvel.Y, 2) + pow(linvel.Z, 2));

			return vel;

		}

		void PhysicsCar::setPosition(core::vector3df const& v)
		{
			btTransform t = m_vehicle->getRigidBody()->getWorldTransform();

			btVector3 btv(v.X, v.Y, v.Z);
			t.setOrigin(btv);

			m_vehicle->getRigidBody()->setWorldTransform(t);

			if (m_vehicle)
			{
				m_vehicle->resetSuspension();
				for (int i = 0; i < m_vehicle->getNumWheels(); i++)
				{
					//synchronize the wheels with the (interpolated) chassis worldtransform
					m_vehicle->updateWheelTransform(i, true);
				}
			}
		}

        core::vector3df PhysicsCar::getRotation(bool mult) const
        {
            core::vector3df rot;
            btQuaternion btq = m_chassisObject->getRigidBody()->getOrientation();
            QuaternionToEulerXYZ(btq, rot);
            if (mult)
                rot *= BPU_180_PI;

            return rot;
        }

		btScalar PhysicsCar::getAngle(void)
		{
			btQuaternion btq = m_chassisObject->getRigidBody()->getOrientation();
			btScalar angle = btq.getAngle();

			return angle;
		}

		void PhysicsCar::setRotation(core::vector3df const &rot)
		{
            btTransform tr = m_vehicle->getRigidBody()->getWorldTransform();
            //tr.setIdentity();
            btQuaternion quat;
            quat.setEulerZYX(rot.X, rot.Y, rot.Z);
            tr.setRotation(quat);

			m_vehicle->getRigidBody()->setWorldTransform(tr);

			if (m_vehicle)
			{
				m_vehicle->resetSuspension();
				for (int i = 0; i < m_vehicle->getNumWheels(); i++)
				{
					//synchronize the wheels with the (interpolated) chassis worldtransform
					m_vehicle->updateWheelTransform(i, true);
				}
			}
		}

        irr::core::vector3df const PhysicsCar::getAngularVelocity() const {
            btRigidBody* chassisBody = m_chassisObject->getRigidBody();
            return irr::core::vector3df(chassisBody->getAngularVelocity().getX(), chassisBody->getAngularVelocity().getY(), chassisBody->getAngularVelocity().getZ());
        }

        irr::core::vector3df const PhysicsCar::getLinearVelocity() const {
            btRigidBody* chassisBody = m_chassisObject->getRigidBody();
            return irr::core::vector3df(chassisBody->getLinearVelocity().getX(), chassisBody->getLinearVelocity().getY(), chassisBody->getLinearVelocity().getZ());
        }

        void PhysicsCar::setAngularVelocity(irr::core::vector3df const &vec) {
            btRigidBody* chassisBody = m_chassisObject->getRigidBody();
            chassisBody->setAngularVelocity(btVector3(vec.X, vec.Y, vec.Z));
        }

        void PhysicsCar::setLinearVelocity(irr::core::vector3df const &vec) {
            btRigidBody* chassisBody = m_chassisObject->getRigidBody();
            chassisBody->setLinearVelocity(btVector3(vec.X, vec.Y, vec.Z));
        }

        void PhysicsCar::changeMesh(int id, irr::scene::ISceneManager *sceneManager) {
            m_chassisNode->remove();
            switch (id) {
        		case 0:
                    m_chassisNode = loadMeshFromFile("car/SV/SV.obj", sceneManager);
        		    break;
                case 1:
                    m_chassisNode = loadMeshFromFile("car/SV/SV_blue.obj", sceneManager);
        		    break;
                case 2:
                    m_chassisNode = loadMeshFromFile("car/SV/SV_green.obj", sceneManager);
        		    break;
                case 3:
                    m_chassisNode = loadMeshFromFile("car/SV/SV_orange.obj", sceneManager);
        		    break;
                case 4:
                    m_chassisNode = loadMeshFromFile("car/SV/SV_pink.obj", sceneManager);
        		    break;
                case 5:
                    m_chassisNode = loadMeshFromFile("car/SV/SV_white.obj", sceneManager);
        		    break;
                case 6:
                    m_chassisNode = loadMeshFromFile("car/SV/SV_yellow.obj", sceneManager);
        		    break;
            }
        }

        irr::scene::IAnimatedMeshSceneNode* PhysicsCar::loadMeshFromFile(const char* filename, irr::scene::ISceneManager *sm)
        {

        	irr::scene::IAnimatedMesh* mesh = sm->getMesh(filename);
        	if (mesh == NULL) return NULL;

        	irr::scene::IAnimatedMeshSceneNode* node = sm->addAnimatedMeshSceneNode(mesh);
        	if (node == NULL)
        	{
        		//mesh->drop();
        		return NULL;
        	}

        	node->setMaterialFlag(video::EMF_LIGHTING, false);	// no lighting
        	//shadows....uncomment if shit isn't working
            //node->addShadowVolumeSceneNode(NULL, -1, true);

        	return node;
        }

	} // end of namespace physics
} // end of namespace irr
