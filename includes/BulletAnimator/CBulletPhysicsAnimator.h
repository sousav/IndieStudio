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

#ifndef __C_BULLET_PHYSICS_ANIMATOR_H_INCLUDED__
#define __C_BULLET_PHYSICS_ANIMATOR_H_INCLUDED__

#include "irrlicht.h"
#include <btBulletDynamicsCommon.h>


namespace irr
{
	namespace scene
	{
		class CBulletPhysicsAnimator;
	}
}


#include "CBulletPhysics.h"


namespace irr
{
	namespace physics
	{
		class CPhysicsObject;	
	}


	namespace scene
	{

		//------------------------------------------------------------------------------
		//!	CBulletPhysicsAnimator
		/** Performs synchronization task between Bullet's object and corresponding
		*   scene node, also applies external forces to Bullet's object
		*/
		class CBulletPhysicsAnimator: public ISceneNodeAnimator
		{
		public:

			static CBulletPhysicsAnimator* CreateInstance(physics::CPhysicsObject* worldObject);


			//! Dtor
			virtual ~CBulletPhysicsAnimator();

			//! animates a scene node
			void animateNode(scene::ISceneNode* node, u32 timeMs);

			//! Writes attributes of the scene node animator.
			void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options = 0);

			//! Reads attributes of the scene node animator.
			void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options = 0);

			//! Returns type of the scene node animator
			ESCENE_NODE_ANIMATOR_TYPE getType() const { return ESNAT_COLLISION_RESPONSE; }

			scene::ISceneNodeAnimator* createClone(scene::ISceneNode *, scene::ISceneManager *);


		protected:

			//! Ctor
			CBulletPhysicsAnimator();


		private:

			physics::CPhysicsObject* m_worldObject;
		};

	} // end namespace scene
} // end namespace irr

#endif //__C_BULLET_PHYSICS_ANIMATOR_H_INCLUDED__
