#ifndef S_PHYSICS_CAR_PARAMS_H
#define S_PHYSICS_CAR_PARAMS_H

#include <irrlicht.h>

#include "SPhysicsParams.h"

namespace irr
{
	namespace physics
	{

		//! Helper structure to configure animator physics parameters
		struct SPhysicsCarParams : SPhysicsParams
		{
			SPhysicsCarParams() : 
				CarBodyOffset(-0.325f),
				FrontAxeOffset(1.37f),
				FrontAxeHalfWidth(0.8f),
				RearAxeOffset(-1.37f),
				RearAxeHalfWidth(0.8f),

				MaxEngineForce(1000.0f),
				MaxBreakingForce(100.0f),
				SteeringIncrement(0.04f),
				SteeringClamp(0.3f),
				WheelRadius(0.5f),
				WheelWidth(0.3f),
				WheelFriction(10.0f),
				SuspensionStiffness(50.0f),
				SuspensionDamping(0.3f),
				SuspensionCompression(0.2f),
				SuspensionRestLength(0.15f),
				RollInfluence(0.25f) 
			{
			}

			f32 CarBodyOffset;
			f32 FrontAxeOffset;
			f32 FrontAxeHalfWidth;
			f32 RearAxeOffset;
			f32 RearAxeHalfWidth;
			

			f32 MaxEngineForce;	//this should be engine/velocity dependent
			f32 MaxBreakingForce;

			f32 SteeringIncrement;
			f32 SteeringClamp;

			f32 WheelRadius;
			f32 WheelWidth;

			// The coefficient of friction between the tyre and the ground. 
			// Should be about 0.8 for realistic cars, but can increased for better handling.
			// Set large (10000.0) for kart racers
			f32 WheelFriction;

			// The stiffness constant for the suspension. 
			// 10.0 - Offroad buggy, 50.0 - Sports car, 200.0 - F1 Car
			f32 SuspensionStiffness;

			// The damping coefficient for when the suspension is expanding. 
			// See the comments for m_wheelsDampingCompression for how to set k.
            // m_wheelsDampingRelaxation should be slightly larger than m_wheelsDampingCompression, eg 0.2 to 0.5
			f32 SuspensionDamping;

			// The damping coefficient for when the suspension is compressed. 
			// Set to k * 2.0 * btSqrt(m_suspensionStiffness) so k is proportional to critical damping.
            // k = 0.0 undamped & bouncy, k = 1.0 critical damping
            // 0.1 to 0.3 are good values
			f32 SuspensionCompression;

			// The maximum length of the suspension (metres)
			f32 SuspensionRestLength;

			// Reduces the rolling torque applied from the wheels that cause the vehicle to roll over.
            // This is a bit of a hack, but it's quite effective. 0.0 = no roll, 1.0 = physical behaviour.
            // If m_frictionSlip is too high, you'll need to reduce this to stop the vehicle rolling over.
            // You should also try lowering the vehicle's centre of mass
			f32 RollInfluence;
		};

	} // end of namespace physics
} // end of namespace irr

#endif
