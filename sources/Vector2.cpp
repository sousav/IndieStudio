//
// Vector2.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio_/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Mon May 15 00:48:15 2017 Sousa Victor
// Last update Thu Jun  8 16:23:46 2017 Sousa Victor
//

#include "Vector2.hpp"

using namespace indie;

float Vector2::kEpsilon = 1E-05;

Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2::Vector2(const Vector2 &rhs) {
    *this = rhs;
}

Vector2::~Vector2() {

}

float &Vector2::operator [](int index) {
	float result;
	if (index != 0) {
		if (index != 1) {
			throw std::out_of_range("Invalid Vector2 index!");
		}
		return this->y;
	} else {
		return this->x;
	}
}

Vector2 Vector2::operator + (Vector2 b) {
	return Vector2(this->x + b.x, this->y + b.y);
}

Vector2 Vector2::operator - (Vector2 b) {
	return Vector2(this->x - b.x, this->y - b.y);
}

Vector2 Vector2::operator - () {
	return Vector2(-this->x, -this->y);
}

Vector2 Vector2::operator *(float d) {
	return Vector2(this->x * d, this->y * d);
}

Vector2 Vector2::operator / (float d) {
	return Vector2(this->x / d, this->y / d);
}

Vector2 &Vector2::operator =(const Vector2 &rhs) {
    this->x = rhs.x;
    this->y = rhs.y;
    return *this;
}

bool Vector2::operator == (Vector2 rhs) {
	return this->SqrMagnitude() - rhs.SqrMagnitude() < 9.99999944E-11f;
}

bool Vector2::operator != (Vector2 rhs) {
	return !(*this == rhs);
}

std::string Vector2::ToString() {
    std::stringstream ss;
    ss << "({x: " << this->x << "}, {y: " << this->y << "})";
	return ss.str();
}

Vector2 Vector2::getnormalized() const {
	Vector2 result = Vector2(this->x, this->y);
	result.Normalize();
	return result;
}

float Vector2::getmagnitude() const {
#ifdef SYSTEM_LINUX
  return sqrtf(this->x * this->x + this->y * this->y);
#else
  return std::sqrtf(this->x * this->x + this->y * this->y);
#endif


}

float Vector2::getsqrMagnitude() const {
	return this->x * this->x + this->y * this->y;
}

Vector2 Vector2::getzero() {
	return Vector2(0.0f, 0.0f);
}

Vector2 Vector2::getone() {
	return Vector2(1.0f, 1.0f);
}

Vector2 Vector2::getup() {
	return Vector2(0.0f, 1.0f);
}

Vector2 Vector2::getdown() {
	return Vector2(0.0f, -1.0f);
}

Vector2 Vector2::getleft() {
	return Vector2(-1.0f, 0.0f);
}

Vector2 Vector2::getright() {
	return Vector2(1.0f, 0.0f);
}

Vector2 Vector2::MoveTowards(Vector2 current, Vector2 target, float maxDistanceDelta) {
	Vector2 a = target - current;
	float magnitude = a.getmagnitude();
	Vector2 result;
	if (magnitude <= maxDistanceDelta || magnitude == 0.0f) {
		result = target;
	} else {
		result = current + a / magnitude * maxDistanceDelta;
	}
	return result;
}

Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float t) {
	t = (t > 1.0) ? 1.0 : (t < 0.0) ? 0.0 : t;
	return Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
}

Vector2 Vector2::LerpUnclamped(Vector2 a, Vector2 b, float t) {
	return Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
}

Vector2 Vector2::SmoothDamp(Vector2 current, Vector2 target, Vector2 &currentVelocity, float smoothTime, float maxSpeed, float deltaTime) {
#ifdef _WIN32
    smoothTime = max(0.0001f, smoothTime);
#else
    smoothTime = std::max(0.0001f, smoothTime);
#endif
	float num = 2.0f / smoothTime;
	float num2 = num * deltaTime;
	float d = 1.0f / (1.0f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
	Vector2 vector = current - target;
	Vector2 vector2 = target;
	float maxLength = maxSpeed * smoothTime;
	vector = Vector2::ClampMagnitude(vector, maxLength);
	target = current - vector;
	Vector2 vector3 = (currentVelocity + vector * num) * deltaTime;
	currentVelocity = (currentVelocity - vector3 * num) * d;
	Vector2 vector4 = target + (vector + vector3) * d;
	if (Vector2::Dot(vector2 - current, vector4 - vector2) > 0.0f) {
		vector4 = vector2;
		currentVelocity = (vector4 - vector2) / deltaTime;
	}
	return vector4;
}

void Vector2::Set(float newX, float newY) {
	this->x = newX;
	this->y = newY;
}


Vector2 Vector2::Scale(Vector2 a, Vector2 b) {
	return Vector2(a.x * b.x, a.y * b.y);
}

void Vector2::Scale(Vector2 scale) {
	this->x *= scale.x;
	this->y *= scale.y;
}

void Vector2::Normalize() {
	float magnitude = this->getmagnitude();
	if (magnitude > 1E-05) {
        Vector2 result = *this / magnitude;
		*this = result;
	} else {
		*this = Vector2::getzero();
	}
}

Vector2 Vector2::Reflect(Vector2 inDirection, Vector2 inNormal) {
	return inNormal * Vector2::Dot(inNormal, inDirection) * -2.0f + inDirection;
}

float Vector2::Dot(Vector2 lhs, Vector2 rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Vector2::Angle(Vector2 from, Vector2 to) {
    float angle = Vector2::Dot(from.getnormalized(), to.getnormalized());
	return std::cos((angle > 1.0) ? 1.0 : (angle < -1.0) ? -1.0 : angle) * 57.29578f;
}

float Vector2::Distance(Vector2 a, Vector2 b) {
	return (a - b).getmagnitude();
}

Vector2 Vector2::ClampMagnitude(Vector2 vector, float maxLength) {
	Vector2 result;
	if (vector.getsqrMagnitude() > maxLength * maxLength) {
		result = vector.getnormalized() * maxLength;
	} else {
		result = vector;
	}
	return result;
}

float Vector2::SqrMagnitude(Vector2 a) {
	return a.x * a.x + a.y * a.y;
}

float Vector2::SqrMagnitude() {
	return this->x * this->x + this->y * this->y;
}

Vector2 Vector2::Min(Vector2 lhs, Vector2 rhs) {
#ifdef _WIN32
    return Vector2(min(lhs.x, rhs.x), min(lhs.y, rhs.y));
#else
    return Vector2(std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y));
#endif
}

Vector2 Vector2::Max(Vector2 lhs, Vector2 rhs) {
#ifdef _WIN32
    return Vector2(max(lhs.x, rhs.x), max(lhs.y, rhs.y));
#else
    return Vector2(std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y));
#endif
}
