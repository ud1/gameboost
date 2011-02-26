
#include <gb/math/geom3d.h>
#include <assert.h>

namespace gb
{

namespace math
{

namespace geom3d
{

//=========================================================================
//                          Quaternion
//=========================================================================



//=========================================================================
Quaternion Quaternion::slerp(const Quaternion &q0, const Quaternion &q1, float t)
{

	// Check for out-of range parameter and return edge points if so

	if (t <= 0.0f) return q0;
	if (t >= 1.0f) return q1;

	// Compute "cosine of angle between quaternions" using dot product

	float cosOmega =   q0.dot(q1); //  xx  dotProduct(q0, q1);

	// If negative dot, use -q1.  Two quaternions q and -q
	// represent the same rotation, but may produce
	// different slerp.  We chose q or -q to rotate using
	// the acute angle.

	float q1w = q1.w;
	float q1x = q1.x;
	float q1y = q1.y;
	float q1z = q1.z;

	if (cosOmega < 0.0f) 
	{
		q1w = -q1w;
		q1x = -q1x;
		q1y = -q1y;
		q1z = -q1z;
		cosOmega = -cosOmega;
	}

	// We should have two unit quaternions, so dot should be <= 1.0

	assert(cosOmega < 1.1f);

	// Compute interpolation fraction, checking for quaternions
	// almost exactly the same

	float k0, k1;
	if (cosOmega > 0.9999f) 
	{

		// Very close - just use linear interpolation,
		// which will protect againt a divide by zero

		k0 = 1.0f-t;
		k1 = t;

	} 
	else 
	{

		// Compute the sin of the angle using the
		// trig identity sin^2(omega) + cos^2(omega) = 1

		float sinOmega = sqrt(1.0f - cosOmega*cosOmega);

		// Compute the angle from its sin and cosine

		float omega = atan2(sinOmega, cosOmega);

		// Compute inverse of denominator, so we only have
		// to divide once

		float oneOverSinOmega = 1.0f / sinOmega;

		// Compute interpolation parameters

		k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
		k1 = sin(t * omega) * oneOverSinOmega;
	}

	// Interpolate

	Quaternion result;
	result.x = k0*q0.x + k1*q1x;
	result.y = k0*q0.y + k1*q1y;
	result.z = k0*q0.z + k1*q1z;
	result.w = k0*q0.w + k1*q1w;

	// Return it

	return result;
};

//=======================================================================
Quaternion Quaternion::pow(const Quaternion &q, float exponent) const 
{

	// Check for the case of an identity quaternion.
	// This will protect against divide by zero

	if (fabs(q.w) > .9999f) {
		return q;
	}

	// Extract the half angle alpha (alpha = theta/2)

	float	alpha = acos(q.w);

	// Compute new alpha value

	float	newAlpha = alpha * exponent;

	// Compute new w value

	Quaternion result;
	result.w = cos(newAlpha);

	// Compute new xyz values

	float	mult = sin(newAlpha) / sin(alpha);
	result.x = q.x * mult;
	result.y = q.y * mult;
	result.z = q.z * mult;

	// Return it

	return result;
}

//=========================================================================
base::vec3_s	Quaternion::getRotationAxis() const 
{

	// Compute sin^2(theta/2).  Remember that w = cos(theta/2),
	// and sin^2(x) + cos^2(x) = 1

	float sinThetaOver2Sq = 1.0f - w*w;

	// Protect against numerical imprecision

	if (sinThetaOver2Sq <= 0.0f) {

		// Identity quaternion, or numerical imprecision.  Just
		// return any valid vector, since it doesn't matter

		return base::vec3_s(1.0f, 0.0f, 0.0f);
	}

	// Compute 1 / sin(theta/2)

	float	oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);

	// Return axis of rotation

	return base::vec3_s (
		x * oneOverSinThetaOver2,
		y * oneOverSinThetaOver2,
		z * oneOverSinThetaOver2
		);
}

//=========================================================================
Quaternion&  Quaternion::setRotationAboutAxisAngle(const base::vec3_s &axis, float theta) 
{

	// The axis of rotation must be normalized

#pragma message("KS777: MATH::QUAT::setRotationAboutAxisAngle >> NEED CHECK !!"   __FILE__ )
	// assert( fabs(vectorMag(axis) - 1.0f) < 0.01f );

	// Compute the half angle and its sin
	const float	thetaOver2 = theta*0.5f;
	const float	sinThetaOver2 = sin(thetaOver2);

	// Set the values
	w = cos(thetaOver2);
	x = axis.x * sinThetaOver2;
	y = axis.y * sinThetaOver2;
	z = axis.z * sinThetaOver2;
	return *this;
}





} // end ns

} // end ns

} // end ns