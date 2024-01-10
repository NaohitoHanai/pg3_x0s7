#pragma once

/// <summary>
/// DxLib‚Ì‹@”\‚ðŠg’£‚µ‚Ü‚µ‚½
/// </summary>
/// <author>N.Hanai</author>

#include <DxLib.h>

namespace DxLib {
	inline float DegToRad(float deg) { return deg * DX_PI_F / 180.0f; };
	inline double DegToRad(double deg) { return deg * DX_PI / 180.0; };
	inline float RadToDeg(float rad) { return rad *180.0f / DX_PI_F; };
	inline double RadToDeg(double rad) { return rad * 180.0 / DX_PI; };

	inline VECTOR VGet(VECTOR_D v) { return VGet((float)v.x, (float)v.y, (float)v.z);	}
	inline VECTOR_D VGetD(VECTOR v) { return VGetD((double)v.x, (double)v.y, (double)v.z); }

	inline const VECTOR operator +(const VECTOR& v1, const VECTOR& v2) { return VAdd(v1, v2); }
	inline const VECTOR_D operator +(const VECTOR_D& v1, const VECTOR_D& v2) { return VAddD(v1, v2); }

	inline VECTOR& operator +=(VECTOR& v1, const VECTOR& v2) { return v1 = VAdd(v1, v2); }
	inline VECTOR_D& operator +=(VECTOR_D& v1, const VECTOR_D& v2) { return v1 = VAddD(v1, v2); }

	inline const VECTOR operator -(const VECTOR& v1, const VECTOR& v2) { return VSub(v1, v2); }
	inline const VECTOR_D operator -(const VECTOR_D& v1, const VECTOR_D& v2) { return VSubD(v1, v2); }

	inline VECTOR& operator -=(VECTOR& v1, const VECTOR& v2) { return v1 = VSub(v1, v2); }
	inline VECTOR_D& operator -=(VECTOR_D& v1, const VECTOR_D& v2) { return v1 = VSubD(v1, v2); }

	inline const VECTOR operator *(const VECTOR& v1, const float& scale) { return VScale(v1, scale); }
	inline const VECTOR_D operator *(const VECTOR_D& v1, const double& scale) { return VScaleD(v1, scale); }

	inline const VECTOR operator *(const float& scale, const VECTOR& v1) { return VScale(v1, scale); }
	inline const VECTOR_D operator *(const double& scale, const VECTOR_D& v1) { return VScaleD(v1, scale); }

	inline const VECTOR operator /(const VECTOR& v1, const float& scale) { return VScale(v1, 1.0f/scale); }
	inline const VECTOR_D operator /(const VECTOR_D& v1, const double& scale) { return VScaleD(v1, 1.0/scale); }

	inline VECTOR& operator *=(VECTOR& v1, const float& scale) { return v1 = VScale(v1, scale); }
	inline VECTOR_D& operator *=(VECTOR_D& v1, const double& scale) { return v1 = VScaleD(v1, scale); }

	inline VECTOR& operator *=(const float& scale, VECTOR& v1) { return v1 = VScale(v1, scale); }
	inline VECTOR_D& operator *=(const double& scale, VECTOR_D& v1) { return v1 = VScaleD(v1, scale); }

	inline VECTOR& operator /=(VECTOR& v1, const float& scale) { return v1 = VScale(v1, 1.0f / scale); }
	inline VECTOR_D& operator /=(VECTOR_D& v1, const double& scale) { return v1 = VScaleD(v1, 1.0 / scale); }

	inline const MATRIX operator +(const MATRIX& m1, const MATRIX& m2) { return MAdd(m1, m2); }
	inline const MATRIX_D operator +(const MATRIX_D& m1, const MATRIX_D& m2) { return MAddD(m1, m2); }

	inline MATRIX& operator +=(MATRIX& m1, const MATRIX& m2) { return m1 = MAdd(m1, m2); }
	inline MATRIX_D& operator +=(MATRIX_D& m1, const MATRIX_D& m2) { return m1 = MAddD(m1, m2); }

	inline const MATRIX operator *(const MATRIX& m1, const MATRIX& m2) { return MMult(m1, m2); }
	inline const MATRIX_D operator *(const MATRIX_D& m1, const MATRIX_D& m2) { return MMultD(m1, m2); }

	inline MATRIX& operator *=(MATRIX& m1, const MATRIX& m2) { return m1 = MMult(m1, m2); }
	inline MATRIX_D& operator *=(MATRIX_D& m1, const MATRIX_D& m2) { return m1 = MMultD(m1, m2); }

	inline const VECTOR operator *(const VECTOR& v, const MATRIX& m1) { return VTransform(v, m1); }
	inline const VECTOR_D operator *(const VECTOR_D& v, const MATRIX_D& m1) { return VTransformD(v, m1); }

	inline VECTOR& operator *=(VECTOR& v, const MATRIX& m1) { return v = VTransform(v, m1); }
	inline VECTOR_D& operator *=(VECTOR_D& v, const MATRIX_D& m1) { return v = VTransformD(v, m1); }

	struct VECTOR2 {
		float x, y;
		VECTOR2() : x(0.0f), y(0.0f) {}
		VECTOR2(float _x, float _y) : x(_x), y(_y) {}

		inline VECTOR2 operator +(const VECTOR2& v) {
			return VECTOR2(x + v.x, y + v.y);
		}
		inline const VECTOR2& operator +=(const VECTOR2& v) {
			x += v.x;
			y += v.y;
			return *this;
		}

		inline VECTOR2 operator -(const VECTOR2& v) {
			return VECTOR2(x - v.x, y - v.y);
		}
		inline const VECTOR2& operator -=(const VECTOR2& v) {
			x -= v.x;
			y -= v.y;
			return *this;
		}

		inline VECTOR2 operator *(float s) {
			return VECTOR2(x*s, y*s);
		}
		inline const VECTOR2& operator *=(float s) {
			x *= s;
			y *= s;
			return *this;
		}

		inline VECTOR2 operator /(float s) {
			return VECTOR2(x / s, y / s);
		}
		inline const VECTOR2& operator /=(float s) {
			x /= s;
			y /= s;
			return *this;
		}

		inline int intx() { return static_cast<int>(x); }
		inline int inty() { return static_cast<int>(y); }
	};
};