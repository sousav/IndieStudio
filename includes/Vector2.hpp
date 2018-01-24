//
// Vector2.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio_/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Mon May 15 00:38:56 2017 Sousa Victor
// Last update Tue Jun  6 19:14:42 2017 Sousa Victor
//

#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_

#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#endif

namespace indie {

	class Vector2 {

	public:
        Vector2(float x = 0, float y = 0);
        Vector2(const Vector2 &rhs);
        virtual ~Vector2();

		float x = 0;
		float y = 0;

		static float kEpsilon;

		float &operator [](int index);
        Vector2 operator + (Vector2 b);
		Vector2 operator - (Vector2 b);
		Vector2 operator - ();
		Vector2 operator *(float d);
		Vector2 operator / (float d);
        Vector2 &operator = (const Vector2 &rhs);
		bool operator == (Vector2 rhs);
		bool operator != (Vector2 rhs);
        virtual std::string ToString();

        Vector2 getnormalized() const;
		float getmagnitude() const;
		float getsqrMagnitude() const;

        static Vector2 getzero();
		static Vector2 getone();

        static Vector2 getup();
		static Vector2 getdown();
		static Vector2 getleft();
		static Vector2 getright();

        static Vector2 MoveTowards(Vector2 current, Vector2 target, float maxDistanceDelta);

        static Vector2 Lerp(Vector2 a, Vector2 b, float t);
		static Vector2 LerpUnclamped(Vector2 a, Vector2 b, float t);

		static Vector2 SmoothDamp(Vector2 current, Vector2 target, Vector2 &currentVelocity, float smoothTime, float maxSpeed, float deltaTime);

		void Set(float newX, float newY);

		static Vector2 Scale(Vector2 a, Vector2 b);
		void Scale(Vector2 scale);

		void Normalize();
		static Vector2 Reflect(Vector2 inDirection, Vector2 inNormal);
		static float Dot(Vector2 lhs, Vector2 rhs);
		static float Angle(Vector2 from, Vector2 to);
		static float Distance(Vector2 a, Vector2 b);
		static Vector2 ClampMagnitude(Vector2 vector, float maxLength);
		static float SqrMagnitude(Vector2 a);
		float SqrMagnitude();
		static Vector2 Min(Vector2 lhs, Vector2 rhs);
		static Vector2 Max(Vector2 lhs, Vector2 rhs);

	};
}

#endif /*VECTOR2_HPP_*/
