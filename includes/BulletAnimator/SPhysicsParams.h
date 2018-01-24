#ifndef S_PHYSICS_PARAMS_H
#define S_PHYSICS_PARAMS_H

#include <irrlicht.h>

namespace irr
{
	namespace physics
	{

		//! Helper structure to configure animator physics parameters
		struct SPhysicsParams
		{
			SPhysicsParams() : 
				Mass(1.0f), 
				CcdThreshold(0.0f),
				LinearDamping(0.0f), 
				AngularDamping(0.0f), 
				Friction(0.5f),
				Restitution(0.0f), 
				CenterOfMassOffset() 
			{
			}

			f32 Mass;
			f32 CcdThreshold;
			f32 LinearDamping;
			f32 AngularDamping;
			f32 Friction;
			f32 Restitution;
			core::vector3df CenterOfMassOffset;

			short FilterGroup, FilterMask;
		};

	} // end of namespace physics
} // end of namespace irr

#endif
