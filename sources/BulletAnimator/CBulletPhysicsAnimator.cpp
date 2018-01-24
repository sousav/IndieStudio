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

#include "CBulletPhysicsAnimator.h"


namespace irr
{
	namespace scene
	{

		//------------------------------------------------------------------------------
		//! CreateInstance
		//! Creates CBulletPhysicsAnimator or returns NULL
		CBulletPhysicsAnimator* CBulletPhysicsAnimator::CreateInstance(physics::CPhysicsObject* worldObject)
		{
			CBulletPhysicsAnimator* animator = new CBulletPhysicsAnimator();
			animator->m_worldObject = worldObject;

			return animator;
		}

		//------------------------------------------------------------------------------
		//! Ctor
		//!
		CBulletPhysicsAnimator::CBulletPhysicsAnimator() :
			m_worldObject(NULL)
		{
		}

		//------------------------------------------------------------------------------
		//! Dtor
		//!
		CBulletPhysicsAnimator::~CBulletPhysicsAnimator()
		{
		}


		//------------------------------------------------------------------------------
		//! animateNode
		//! animates a scene node
		void CBulletPhysicsAnimator::animateNode(scene::ISceneNode* node, u32 timeMs)
		{
			_IRR_DEBUG_BREAK_IF(node != m_worldObject->getNode());

			if (m_worldObject->isStatic() == false) m_worldObject->animate();
		}

		//------------------------------------------------------------------------------
		scene::ISceneNodeAnimator* CBulletPhysicsAnimator::createClone(scene::ISceneNode *, scene::ISceneManager *)
		{
			return NULL;
		}

		//------------------------------------------------------------------------------
		//! serializeAttributes
		//! Writes attributes of the scene node animator.
		void CBulletPhysicsAnimator::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options/*=0*/)
		{

		}

		//------------------------------------------------------------------------------
		//! deserializeAttributes
		//! Reads attributes of the scene node animator.
		void CBulletPhysicsAnimator::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options/*=0*/)
		{

		}

	} // end namespace scene
} // end namespace irr


