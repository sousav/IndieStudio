//
// Vector3.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio_/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun May 14 22:44:53 2017 Sousa Victor
// Last update Thu Jun  8 16:23:20 2017 Sousa Victor
//

#include "Vector3.hpp"

using namespace indie;

float Vector3::kEpsilon = 1E-05;

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::~Vector3() {

}

float &Vector3::operator [](int index) {
	float result;
	switch (index) {
	case 0:
		return this->x;
		break;
	case 1:
		return this->y;
		break;
	case 2:
		return this->z;
		break;
	default:
		throw std::out_of_range("Invalid Vector3 index!");
	}
}

Vector3 Vector3::operator + (Vector3 b) {
	return Vector3(this->x + b.x, this->y + b.y, this->z + b.z);
}

Vector3 Vector3::operator - (Vector3 b) {
	return Vector3(this->x - b.x, this->y - b.y, this->z - b.z);
}

Vector3 Vector3::operator - () {
	return Vector3(-this->x, -this->y, -this->z);
}

Vector3 Vector3::operator *(float d) {
	return Vector3(this->x * d, this->y * d, this->z * d);
}

Vector3 Vector3::operator / (float d) {
	return Vector3(this->x / d, this->y / d, this->z / d);
}

Vector3 Vector3::operator = (Vector3 const &rhs) {
    this->x = rhs.x;
    this->y = rhs.y;
    this->z = rhs.z;
    return *this;
}

bool Vector3::operator == (Vector3 rhs) {
	return Vector3::SqrMagnitude(*this - rhs) < 9.99999944E-11f;
}

bool Vector3::operator != (Vector3 rhs) {
		return !(*this == rhs);
}

std::string Vector3::ToString() {
    std::stringstream ss;
    ss << "({x: " << this->x << "}, {y: " << this->y << "}, {z: " << this->z << "})";
	return ss.str();
}

Vector3 Vector3::getnormalized() const {
	return Vector3::Normalize(*this);
}

float Vector3::getmagnitude() const {
	#ifdef SYSTEM_LINUX
			return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	#else
		return std::sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	#endif
}

float Vector3::getsqrMagnitude() const {
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

Vector3 Vector3::getzero() {
	return Vector3(0.0f, 0.0f, 0.0f);
}

Vector3 Vector3::getone() {
	return Vector3(1.0f, 1.0f, 1.0f);
}

Vector3 Vector3::getforward() {
	return Vector3(0.0f, 0.0f, 1.0f);
}

Vector3 Vector3::getback() {
	return Vector3(0.0f, 0.0f, -1.0f);
}

Vector3 Vector3::getup() {
	return Vector3(0.0f, 1.0f, 0.0f);
}

Vector3 Vector3::getdown() {
	return Vector3(0.0f, -1.0f, 0.0f);
}

Vector3 Vector3::getleft() {
	return Vector3(-1.0f, 0.0f, 0.0f);
}

Vector3 Vector3::getright() {
	return Vector3(1.0f, 0.0f, 0.0f);
}

// Vector3 Vector3::Slerp(Vector3 a, Vector3 b, float t) {
// 	Vector3 result;
// 	Vector3::INTERNAL_CALL_Slerp(a, b, t, result);
// 	return result;
// }
//
// Vector3 Vector3::SlerpUnclamped(Vector3 a, Vector3 b, float t) {
// 	Vector3 result;
// 	Vector3::INTERNAL_CALL_SlerpUnclamped(a, b, t, result);
// 	return result;
// }
//
// void Vector3::OrthoNormalize(Vector3 &normal, Vector3 &tangent) {
// 	Vector3::Internal_OrthoNormalize2(normal, tangent);
// }
//
// void Vector3::OrthoNormalize(Vector3 &normal, Vector3 &tangent, Vector3 &binormal) {
// 	Vector3::Internal_OrthoNormalize3(normal, tangent, binormal);
// }
//
// Vector3 Vector3::RotateTowards(Vector3 current, Vector3 target, float maxRadiansDelta, float maxMagnitudeDelta) {
// 	Vector3 result;
// 	Vector3::INTERNAL_CALL_RotateTowards(current, target, maxRadiansDelta, maxMagnitudeDelta, result);
// 	return result;
// }

Vector3 Vector3::MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta) {
	Vector3 a = target - current;
	float magnitude = a.getmagnitude();
	Vector3 result;
	if (magnitude <= maxDistanceDelta || magnitude == 0.0f) {
		result = target;
	} else {
		result = current + a / magnitude * maxDistanceDelta;
	}
	return result;
}

Vector3 Vector3::Exclude(Vector3 excludeThis, Vector3 fromThat) {
	return fromThat - Vector3::Project(fromThat, excludeThis);
}

Vector3 Vector3::Lerp(Vector3 a, Vector3 b, float t) {
	t = (t > 1.0) ? 1.0 : (t < 0.0) ? 0.0 : t;
	return Vector3(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t);
}

Vector3 Vector3::LerpUnclamped(Vector3 a, Vector3 b, float t) {
	return Vector3(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t);
}

Vector3 Vector3::SmoothDamp(Vector3 current, Vector3 target, Vector3 &currentVelocity, float smoothTime, float maxSpeed) {
	float deltaTime = DeltaTimer::DeltaTime;
	return Vector3::SmoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
}

Vector3 Vector3::SmoothDamp(Vector3 current, Vector3 target, Vector3 &currentVelocity, float smoothTime) {
	float deltaTime = DeltaTimer::DeltaTime;
	float maxSpeed = std::numeric_limits<float>::infinity();
	return Vector3::SmoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
}

Vector3 Vector3::SmoothDamp(Vector3 current, Vector3 target, Vector3 &currentVelocity, float smoothTime, float maxSpeed, float deltaTime) {
#ifdef _WIN32
    smoothTime = max(0.0001f, smoothTime);
#else
    smoothTime = std::max(0.0001f, smoothTime);
#endif
	float num = 2.0f / smoothTime;
	float num2 = num * deltaTime;
	float d = 1.0f / (1.0f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
	Vector3 vector = current - target;
	Vector3 vector2 = target;
	float maxLength = maxSpeed * smoothTime;
	vector = Vector3::ClampMagnitude(vector, maxLength);
	target = current - vector;
	Vector3 vector3 = (currentVelocity + vector * num) * deltaTime;
	currentVelocity = (currentVelocity - vector3 * num) * d;
	Vector3 vector4 = target + (vector + vector3) * d;
	if (Vector3::Dot(vector2 - current, vector4 - vector2) > 0.0f) {
		vector4 = vector2;
		currentVelocity = (vector4 - vector2) / deltaTime;
	}
	return vector4;
}

void Vector3::Set(float new_x, float new_y, float new_z) {
	this->x = new_x;
	this->y = new_y;
	this->z = new_z;
}

Vector3 Vector3::Scale(Vector3 a, Vector3 b) {
	return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

void Vector3::Scale(Vector3 scale) {
	this->x *= scale.x;
	this->y *= scale.y;
	this->z *= scale.z;
}

Vector3 Vector3::Cross(Vector3 lhs, Vector3 rhs) {
	return Vector3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
}

Vector3 Vector3::Reflect(Vector3 inDirection, Vector3 inNormal) {
	return inNormal * Vector3::Dot(inNormal, inDirection) * -2.0f + inDirection;
}

Vector3 Vector3::Normalize(Vector3 value) {
	float num = Vector3::Magnitude(value);
	Vector3 result;
	if (num > 1E-05) {
		result = value / num;
	} else {
		result = Vector3::getzero();
	}
	return result;
}

void Vector3::Normalize() {
	float num = Vector3::Magnitude(*this);
	if (num > 1E-05) {
        Vector3 result = *this / num;
		*this = result;
	} else {
		*this = Vector3::getzero();
	}
}

float Vector3::Dot(Vector3 lhs, Vector3 rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 Vector3::Project(Vector3 vector, Vector3 onNormal) {
	float num = Vector3::Dot(onNormal, onNormal);
	Vector3 result;
	if (num < Vector3::kEpsilon) {
		result = Vector3::getzero();
	} else {
		result = onNormal * Vector3::Dot(vector, onNormal) / num;
	}
	return result;
}

Vector3 Vector3::ProjectOnPlane(Vector3 vector, Vector3 planeNormal) {
	return vector - Vector3::Project(vector, planeNormal);
}

float Vector3::Angle(Vector3 from, Vector3 to) {
    float angle = Vector3::Dot(from.getnormalized(), to.getnormalized());
	return std::acos((angle > 1.0) ? 1.0 : (angle < -1.0) ? -1.0 : angle) * 57.29578f;
}

float Vector3::Distance(Vector3 a, Vector3 b) {
	Vector3 vector = Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	#ifdef SYSTEM_LINUX
			return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	#else
			return std::sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	#endif
}

Vector3 Vector3::ClampMagnitude(Vector3 vector, float maxLength) {
	Vector3 result;
	if (vector.getsqrMagnitude() > maxLength * maxLength) {
		result = vector.getnormalized() * maxLength;
	} else {
		result = vector;
	}
	return result;
}

float Vector3::Magnitude(Vector3 a) {
	#ifdef SYSTEM_LINUX
			return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
	#else
			return std::sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
	#endif
}

float Vector3::SqrMagnitude(Vector3 a) {
	return a.x * a.x + a.y * a.y + a.z * a.z;
}

Vector3 Vector3::Min(Vector3 lhs, Vector3 rhs) {
#ifdef _WIN32
    return Vector3(min(lhs.x, rhs.x), min(lhs.y, rhs.y), min(lhs.z, rhs.z));
#else
    return Vector3(std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y), std::min(lhs.z, rhs.z));
#endif
}

Vector3 Vector3::Max(Vector3 lhs, Vector3 rhs) {
#ifdef _WIN32
    return Vector3(max(lhs.x, rhs.x), max(lhs.y, rhs.y), max(lhs.z, rhs.z));
#else
    return Vector3(std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y), std::max(lhs.z, rhs.z));
#endif
}

float Vector3::AngleBetween(Vector3 from, Vector3 to) {
    float angle = Vector3::Dot(from.getnormalized(), to.getnormalized());
	return std::acos((angle > 1.0) ? 1.0 : (angle < -1.0) ? -1.0 : angle);
}
