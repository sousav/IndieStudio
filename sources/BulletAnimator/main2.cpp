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


/*
  Terrain Demo

*/
#include <irrlicht.h>
#include <iostream>


using namespace irr;


#pragma comment(lib, "Irrlicht.lib")


// -- IrrBullet --
// Include CBulletPhysics header file and declare CBulletPhysics variable
// (to be able to update world, etc.)
#include "CBulletPhysics.h"
CBulletPhysics* bulletPhysicsSystem = NULL;

//! We need events to control sphere object
class CSphereDriver : public IEventReceiver
{
public:

  CSphereDriver() : drivenObject(NULL), refObject(NULL) {}
  ~CSphereDriver()
  {
    if (drivenObject != NULL) drivenObject->drop();
    if (refObject != NULL) refObject->drop();
  }

  void AddReciever(IEventReceiver* rec) { additionalRecievers.push_back(rec); }

  void SetRefObject(scene::ISceneNode* ref)
  {
    if (refObject != NULL) refObject->drop();
    refObject = ref;
    refObject->grab();
  }
  void SetDrivenObject(scene::CBulletPhysicsAnimator* obj)
  {
    if (drivenObject != NULL) drivenObject->drop();
    drivenObject = obj;
    drivenObject->grab();
  }

  bool OnEvent(const SEvent &event)
  {
    // we can move object by using applyForce or applyImpulse
    f32 force = 200.0f;
    if (drivenObject != NULL &&
        event.EventType == irr::EET_KEY_INPUT_EVENT &&
        event.KeyInput.PressedDown)
    {
      switch(event.KeyInput.Key)
      {
        case KEY_KEY_W:
        case KEY_KEY_S:
        {
          core::vector3df currentPos = drivenObject->getPosition();
          core::vector3df followPos = refObject->getAbsolutePosition();
          core::vector3df d = followPos - currentPos;
          d.Y = 0;
          d.setLength(event.KeyInput.Key == KEY_KEY_S ? force : -force);
          drivenObject->applyForce(d);
        } return true;
        case KEY_KEY_A:
        case KEY_KEY_D:
        {
          core::vector3df currentPos = drivenObject->getPosition();
          core::vector3df followPos = refObject->getAbsolutePosition();
          core::vector3df d = (followPos - currentPos);
          d.setLength(event.KeyInput.Key == KEY_KEY_D ? force : -force);
          f32 x = d.X;
          d.set(-d.Z, 0, x);
          drivenObject->applyForce(d);
        } return true;
        case KEY_SPACE:
        {
          core::vector3df v;
          v.Y = force*3;
          drivenObject->applyForce(v);
        } return true;
      }
    }

    for (s32 i = 0; i < additionalRecievers.size(); i++)
    {
      if (additionalRecievers[i]->OnEvent(event))
        return true;
    }
  }

private:

  scene::ISceneNode* refObject;
  scene::CBulletPhysicsAnimator* drivenObject;
  irr::core::array<IEventReceiver*> additionalRecievers;
};
// -- IrrBullet --


/*
Ok, lets start. Again, we use the main() method as start, not the
WinMain(), because its shorter to write.
*/
int main()
{

	// ask user for driver

	video::E_DRIVER_TYPE driverType;

	printf("Please select the driver you want for this example:\n"\
		" (a) Direct3D 9.0c\n (b) Direct3D 8.1\n (c) OpenGL 1.5\n"\
		" (d) Software Renderer\n (e) Burning's Software Renderer\n"\
		" (f) NullDevice\n (otherKey) exit\n\n");

	char i;
	std::cin >> i;

	switch(i)
	{
		case 'a': driverType = video::EDT_DIRECT3D9;break;
		case 'b': driverType = video::EDT_DIRECT3D8;break;
		case 'c': driverType = video::EDT_OPENGL;   break;
		case 'd': driverType = video::EDT_SOFTWARE; break;
		case 'e': driverType = video::EDT_BURNINGSVIDEO;break;
		case 'f': driverType = video::EDT_NULL;     break;
		default: return 1;
	}

	// create device and exit if creation failed

	IrrlichtDevice *device =
		createDevice(driverType, core::dimension2d<u32>(640, 480));

	if (device == 0)
		return 1; // could not create selected driver.

	/*
	Get a pointer to the video driver and the SceneManager so that
	we do not always have to write device->getVideoDriver() and
	device->getSceneManager().
	*/
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();


		scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
		"../../media/terrain-heightmap.bmp",
		0,					// parent node
		-1,					// node id
		core::vector3df(0.f, 0.f, 0.f),		// position
		core::vector3df(0.f, 0.f, 0.f),		// rotation
		core::vector3df(40.f, 4.4f, 40.f),	// scale
		video::SColor ( 255, 255, 255, 255 ),	// vertexColor
		5,					// maxLOD
		scene::ETPS_17,				// patchSize
		4					// smoothFactor
		);

	terrain->setMaterialFlag(video::EMF_LIGHTING, false);

	terrain->setMaterialTexture(0,
			driver->getTexture("../../media/terrain-texture.jpg"));
	terrain->setMaterialTexture(1,
			driver->getTexture("../../media/detailmap3.jpg"));

	terrain->setMaterialType(video::EMT_DETAIL_MAP);

	terrain->scaleTexture(1.0f, 20.0f);

	/*
	Now we only need a Camera to look at the Quake 3 map.
	And we want to create a user controlled camera. There are some
	different cameras available in the Irrlicht engine. For example the
	Maya Camera which can be controlled compareable to the camera in Maya:
	Rotate with left mouse button pressed, Zoom with both buttons pressed,
	translate with right mouse button pressed. This could be created with
	addCameraSceneNodeMaya(). But for this example, we want to create a
	camera which behaves like the ones in first person shooter games (FPS).
	*/
  scene::ICameraSceneNode* cameraNode = smgr->addCameraSceneNodeFPS();

	/*
	The mouse cursor needs not to be visible, so we make it invisible.
	*/

	device->getCursorControl()->setVisible(false);



  // -- IrrBullet --
  // Define parameters, needed to initialize bullet animator
  scene::CBulletPhysicsAnimatorGeometry bullGeom;
  scene::CBulletPhysicsAnimatorParams bullPhysicsParams;

  // Initialize bullet physics
  bulletPhysicsSystem = new CBulletPhysics();
  if (!bulletPhysicsSystem->Create())
  {
    return 1;
  }
  // -- IrrBullet --


  // -- IrrBullet --
  // add some light )
  smgr->addLightSceneNode(0, core::vector3df(0, 100, 0));

  // Add level mesh to physics as triangle mesh
  bullGeom.AutoCalculate= true;
  bullGeom.type = scene::CBPAGT_CONCAVE_MESH;
  // We add level as static object
  bullPhysicsParams.mass = 0.0f;
  // Now create an animator and assign it to the level scene node
  scene::CBulletPhysicsAnimator* bulletAnimator =
    bulletPhysicsSystem->createBulletPhysicsAnimator(
      terrain,
      &bullGeom,
      &bullPhysicsParams
    );
  terrain->addAnimator(bulletAnimator);
  bulletAnimator->drop();

  // Add spherical object to our demo */
  // Add sphere node
  f32 radius = 8.0f;
  scene::ISceneNode* sphereNode = smgr->addSphereSceneNode(radius);
  //sphereNode->setRotation(core::vector3df(45, 0, 0));
  sphereNode->setPosition(core::vector3df(520,550,510));
  // define sphere geom

  bullGeom.type = scene::CBPAGT_SPHERE;
  bullGeom.sphere.radius = radius;
  // Set shpere mass
  bullPhysicsParams.mass = 4.0f;
  // Add animator. Don't drop it now, we'll use it further
  scene::CBulletPhysicsAnimator* sphereAnimator =
    bulletPhysicsSystem->createBulletPhysicsAnimator(
      sphereNode,
      &bullGeom,
      &bullPhysicsParams
    );
  sphereNode->addAnimator(sphereAnimator);


  // Add pins to the scene

  // Get pin mesh
  scene::IAnimatedMesh* pinMesh = smgr->getMesh("../../media/pin.x");
  if (pinMesh == NULL)
    return 1;

  // add group of pins
  core::vector3df groupPos(0,0,0);
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < i; j++)
    {
      scene::ISceneNode* pinSceneNode = smgr->addMeshSceneNode(pinMesh->getMesh(0));

      pinSceneNode->setScale(core::vector3df(10, 10, 10));
      pinSceneNode->setRotation(core::vector3df(0, 0, 0));
      pinSceneNode->setPosition(groupPos + core::vector3df(j*512, 853, i*512));

      // add pin mesh
      bullGeom.type = scene::CBPAGT_CAPSULE;
      bullGeom.mesh.irrMesh = pinMesh->getMesh(0);

      bullPhysicsParams.mass = 1.0f;
      bullPhysicsParams.friction = 0.6;
      bullPhysicsParams.angularDamping = 0.1;
      bullPhysicsParams.restitution = 0.1;
      bullPhysicsParams.linearDamping = 0.1;



      scene::CBulletPhysicsAnimator* pinBulletPhysicsAnimator =
        bulletPhysicsSystem->createBulletPhysicsAnimator(
          pinSceneNode,
          &bullGeom,
          &bullPhysicsParams
        );
      pinSceneNode->addAnimator(pinBulletPhysicsAnimator);
   pinBulletPhysicsAnimator->drop();

    }


  // create an event receiver for controlling sphere
  CSphereDriver sphereDriver;
  sphereDriver.SetRefObject(cameraNode);
  sphereDriver.SetDrivenObject(sphereAnimator);
  sphereDriver.AddReciever(cameraNode);
  device->setEventReceiver(&sphereDriver);

  // -- IrrBullet --



	int lastFPS = -1;

ITimer *irrTimer = device->getTimer();
u32 TimeStamp = irrTimer->getTime(), DeltaTime = 0;

	while(device->run())
	if (device->isWindowActive())
	{
    // -- IrrBullet --
    // Update physics world
    DeltaTime = irrTimer->getTime() - TimeStamp;
        TimeStamp = irrTimer->getTime();
    bulletPhysicsSystem->OnUpdate(DeltaTime);
    // -- IrrBullet --

    driver->beginScene(true, true, video::SColor(0,200,200,200));
		smgr->drawAll();
		driver->endScene();

		int fps = driver->getFPS();

		if (lastFPS != fps)
		{
			core::stringw str = L"Irrlicht Engine - Terrain example [";
			str += driver->getName();
			str += "] FPS:";
			str += fps;

			device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}
	}

	/*
	In the end, delete the Irrlicht device.
	*/
	device->drop();
	return 0;
}

