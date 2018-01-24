#ifndef LOADCAR_H
#define LOADCAR_H

#include <irrlicht.h>
#include "BulletAnimator/CBulletPhysics.h"
#include "BulletAnimator/PhysicsCar.h"

using namespace irr;

class CLoadCar{

	public:
		//constructor
		CLoadCar();
		//destructor
		~CLoadCar();
		//pretty self explanatory...
		void Init(irr::scene::ISceneManager* smgr, physics::CBulletPhysics* BPS, s32 val);
		void Update(s32 drivetype, bool reverse);
		//return car
		physics::PhysicsCar* getCar() { return car; }
		//return car node
		irr::scene::IAnimatedMeshSceneNode* getCarNode() { return carNode; }
		//set pos for car
		void setCarPos(core::vector3df carpos) { car_pos = carpos; }
		//set rotation at start
		void setCarStRot(s32 amount) { angle = amount; }
		//reset da' car
		void resetCar(s32 newangle);
		//return car's drive type
		irr::s32 returnDrive() { return drive; }

		irr::f32 getMaxSpeed() const {
			return max_speed;
		}

		void Clear();

	private:
		physics::CBulletPhysics* bulletPhysSys;
		physics::SPhysicsParams physicsParams;
		physics::PhysicsCar* car;
		physics::SPhysicsCarParams carParams;
		irr::scene::IAnimatedMeshSceneNode* loadMeshFromFile(const char* filename);
		irr::scene::ISceneManager* sm;
		irr::scene::IAnimatedMeshSceneNode* carNode;
        irr::scene::IAnimatedMeshSceneNode* tire1;
        irr::scene::IAnimatedMeshSceneNode* tire2;
        irr::scene::IAnimatedMeshSceneNode* tire3;
        irr::scene::IAnimatedMeshSceneNode* tire4;
		core::vector3df car_pos;
		s32 angle;
		s32 drive, stopPos;
		f32 max_speed;

};

#endif /* LOADCAR_H */
