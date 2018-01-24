//
// Vector3.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio_/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun May 14 22:05:46 2017 Sousa Victor
// Last update Tue Jun  6 19:15:29 2017 Sousa Victor
//

#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <sstream>
#include <string>
#include <cmath>
#include <math.h>
#include <vector>
#include <limits>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#endif

#include "DeltaTimer.hpp"

namespace indie
{

    class IGame;

	class Vector3 {
	public:
        Vector3(float x = 0, float y = 0, float z = 0);
        ~Vector3();

		float x = 0;
		float y = 0;
		float z = 0;

        static float kEpsilon;

		float &operator [](int index);
        Vector3 operator + (Vector3 b);
		Vector3 operator - (Vector3 b);
		Vector3 operator - ();
		Vector3 operator * (float d);
		Vector3 operator / (float d);
        Vector3 operator = (Vector3 const &rhs);
		bool operator == (Vector3 rhs);
		bool operator != (Vector3 rhs);
		virtual std::string ToString();

		Vector3 getnormalized() const;
		float getmagnitude() const;
		float getsqrMagnitude() const;

		static Vector3 getzero();
		static Vector3 getone();

		static Vector3 getforward();
		static Vector3 getback();
		static Vector3 getup();
		static Vector3 getdown();
		static Vector3 getleft();
		static Vector3 getright();

		// static Vector3 Slerp(Vector3 a, Vector3 b, float t);
		// static Vector3 SlerpUnclamped(Vector3 a, Vector3 b, float t);
        //
		// static void OrthoNormalize(Vector3 &normal, Vector3 &tangent);
		// static void OrthoNormalize(Vector3 &normal, Vector3 &tangent, Vector3 &binormal);
        //
		// static Vector3 RotateTowards(Vector3 current, Vector3 target, float maxRadiansDelta, float maxMagnitudeDelta);
        static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta);

		static Vector3 Exclude(Vector3 excludeThis, Vector3 fromThat);
		static Vector3 Lerp(Vector3 a, Vector3 b, float t);
		static Vector3 LerpUnclamped(Vector3 a, Vector3 b, float t);

		static Vector3 SmoothDamp(Vector3 current, Vector3 target, Vector3 &currentVelocity, float smoothTime, float maxSpeed);
		static Vector3 SmoothDamp(Vector3 current, Vector3 target, Vector3 &currentVelocity, float smoothTime);
		static Vector3 SmoothDamp(Vector3 current, Vector3 target, Vector3 &currentVelocity, float smoothTime, float maxSpeed, float deltaTime);

		void Set(float new_x, float new_y, float new_z);

		static Vector3 Scale(Vector3 a, Vector3 b);
		void Scale(Vector3 scale);

		static Vector3 Cross(Vector3 lhs, Vector3 rhs);
		static Vector3 Reflect(Vector3 inDirection, Vector3 inNormal);
		static Vector3 Normalize(Vector3 value);
		void Normalize();
		static float Dot(Vector3 lhs, Vector3 rhs);
		static Vector3 Project(Vector3 vector, Vector3 onNormal);
		static Vector3 ProjectOnPlane(Vector3 vector, Vector3 planeNormal);
		static float Angle(Vector3 from, Vector3 to);
		static float Distance(Vector3 a, Vector3 b);
        static Vector3 ClampMagnitude(Vector3 vector, float maxLength);
		static float Magnitude(Vector3 a);
		static float SqrMagnitude(Vector3 a);
		static Vector3 Min(Vector3 lhs, Vector3 rhs);
		static Vector3 Max(Vector3 lhs, Vector3 rhs);

		static float AngleBetween(Vector3 from, Vector3 to);
	};
}

#endif /*VECTOR3_HPP_*/
