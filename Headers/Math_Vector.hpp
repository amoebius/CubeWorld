//-----------------------------
// James Payor - Evolution RTS
// Created 27/03/13
//-----------------------------
//
//------------------
// Math_Vector.hpp |
//-------------------------------------------
// Declares the vector class and methods
// for the linear algebra involved in the 3D
// graphics.
//-------------------------------------------

#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

// Required headers:
#include <cmath>

namespace Math {

	// Templated vector3 class:
	template<class scalar>
	class vector3 {

	public:
		// For reference:
		typedef vector3<scalar> vec3;

		// Constructors:
		vector3(scalar x, scalar y, scalar z) : x(x), y(y), z(z) {}
		vector3(scalar x, scalar z) : x(x), y(0), z(z) {}
		vector3(const vec3& vec) : x(vec.x), y(vec.y), z(vec.z) {}
		vector3() : x(0), y(0), z(0) {}

		// For conversion between types of vectors:
		template<class scalar2>
		vector3(const vector3<scalar2>& v) : x((scalar)v.x), y((scalar)v.y), z((scalar)v.z) {}

		// The components of the vector:
		scalar x,y,z;

		// Cross product:
		inline vec3 cross(const vec3& other) const {
			return vec3(this->y * other.z - this->z * other.y,
						this->z * other.x - this->x * other.z,
						this->x * other.y - this->y * other.x);
		}

		// Dot product:
		inline scalar dot(const vec3& other) const {
			return this->x * other.x + this->y * other.y + this->z * other.z;
		}

		// Vector addition:
		inline vec3 add(const vec3& other) const {
			return vec3(this->x + other.x, this->y + other.y, this->z + other.z);
		}

		// Vector subtraction:
		inline vec3 sub(const vec3& other) const {
			return vec3(this->x - other.x, this->y - other.y, this->z - other.z);
		}

		// Vector-scalar multiplication:
		inline vec3 mult(const scalar& other) const {
			return vec3(other*x, other*y, other*z);
		}

		// Vector-scalar division:
		inline vec3 div(const scalar& other) const {
			return vec3(x/other, y/other, z/other);
		}

		// Magnitude:
		inline scalar abs() const {
			return (scalar)sqrt(x*x + y*y + z*z);
		}

		// Squared magnitude:
		inline scalar abs2() const {
			return x*x + y*y + z*z;
		}

		// Normalised vector:
		inline vec3 norm() const {
			scalar d = this->abs();
			if(d == 0) return vec3::zero();
			return vec3(x/d, y/d, z/d);
		}

		// Projection onto another target:
		inline vec3 projectOn(const vec3& target) const {
			scalar d2 = target.abs2();
			if(d2 == 0) return vec3::zero();
			return target.mult(this->dot(target) / d2);
		}

		// Projection onto this vector:
		inline vec3 project(const vec3& source) const {
			scalar d2 = abs2();
			if(d2 == 0) return vec3::zero();
			return this->mult(this->dot(source) / d2);
		}

		// Dot product:
		inline scalar operator *(const vec3& other) const {
			return x*other.x + y*other.y + z*other.z;
		}

		// Vector-scalar product:
		inline vec3 operator *(const scalar& other) const {
			return vec3(other*x,other*y,other*z);
		}

		// Cross product:
		inline vec3 operator ^(const vec3& other) const {
			return vec3(this->y * other.z - this->z * other.y,
						this->z * other.x - this->x * other.z,
						this->x * other.y - this->y * other.x);
		}

		// Vector-scalar division:
		inline vec3 operator /(const scalar& other) const {
			return vec3(x/other, y/other, z/other);
		}

		// Vector addition:
		inline vec3 operator +(const vec3& other) const {
			return vec3(x+other.x, y+other.y, z+other.z);
		}

		// Vector subtraction:
		inline vec3 operator -(const vec3& other) const {
			return vec3(x-other.x, y-other.y, z-other.z);
		}

		// Vector negation:
		inline vec3 operator -() const {
			return vec3(-this->x, -this->y, -this->z);
		}

		// Assignment:
		inline vec3& operator =(const vec3& rhs) {
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			return *this;
		}

		// += implementation:
		inline vec3& operator +=(const vec3& rhs) {
			this->x += rhs.x;
			this->y += rhs.y;
			this->z += rhs.z;
			return *this;
		}

		// -= implementation:
		inline vec3& operator -=(const vec3& rhs) {
			this->x -= rhs.x;
			this->y -= rhs.y;
			this->z -= rhs.z;
			return *this;
		}

		// ^= (cross-product-equals) implementation:
		inline vec3& operator ^=(const vec3& other) {
			scalar nx = this->y * other.z - this->z * other.y,
				   ny = this->z * other.x - this->x * other.z;
			z = this->x * other.y - this->y * other.x;
			x = nx;
			y = ny;
			return *this;
		}

		// Multiplication by scalar:
		inline vec3& operator *=(const scalar& rhs) {
			this->x *= rhs;
			this->y *= rhs;
			this->z *= rhs;
			return *this;
		}

		// Division by a scalar:
		inline vec3& operator /=(const scalar& rhs) {
			this->x /= rhs;
			this->y /= rhs;
			this->z /= rhs;
			return *this;
		}


		static inline vec3 zero() {	// Zero vector
			return vec3(0,0,0);
		}
		static inline vec3 diag() { // Diagonal vector
			return vec3(1,1,1);
		}
		static inline vec3 diag(scalar size) { // Diagonal vector with specified size
			return vec3(size,size,size);
		}
		static inline vec3 X() {		// Unit vector along x axis
			return vec3(1,0,0);
		}
		static inline vec3 Y() {		// Unit vector along y axis
			return vec3(0,1,0);
		}
		static inline vec3 Z() {		// Unit vector along z axis
			return vec3(0,0,1);
		}

	};

	// Common definitions:  (e.g. vec3 = vector3<double>, vec3f = vector3<float>)
	typedef vector3<double> vec3d;
	typedef vec3d vec3;
	typedef vec3 vec2;
	typedef vector3<float> vec3f;
	typedef vec3f vec2f;
	typedef vector3<int> vec3i;
	typedef vec3i vec2i;

	// Attempt at commutative multiplication for vectors:
	template<class scalar>
	inline vector3<scalar> operator*(const scalar& a, const vector3<scalar>& b) {
		return vector3<scalar>(b.x*a, b.y*a, b.z*a);
	}

}


#endif
