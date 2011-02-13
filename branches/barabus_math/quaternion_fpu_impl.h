//------------------------------------------------------------------------------
//
// GameBoost
//
// copyright:	(c) 2011 GameDev.ru
// authors:		Alexey Egorov (FadeToBlack aka EvilSpirit) anandamide@mail.ru
//
// url:			http://gameboost.googlecode.com/
//				http://www.gamedev.ru/community/gameboost
//
//------------------------------------------------------------------------------

inline Quaternion Quaternion::operator * (const Quaternion &q) const
{
	Quaternion r;
	r.x = w * q.x + x * q.w + y * q.z - z * q.y;
	r.y = w * q.y + y * q.w + z * q.x - x * q.z;
	r.z = w * q.z + z * q.w + x * q.y - y * q.x;
	r.w = w * q.w - x * q.x - y * q.y - z * q.z;
	return r;
}

//------------------------------------------------------------------------------

inline Quaternion &Quaternion::operator *= (const Quaternion &q)
{
	Quaternion r;
	r.x = w * q.x + x * q.w + y * q.z - z * q.y;
	r.y = w * q.y + y * q.w + z * q.x - x * q.z;
	r.z = w * q.z + z * q.w + x * q.y - y * q.x;
	r.w = w * q.w - x * q.x - y * q.y - z * q.z;
	*this = r;
	return *this;
}

//------------------------------------------------------------------------------

inline void Quaternion::setAxisAngle(const Vector3f &dir, float angle)
{

	float length = dir.length();
	if (length > 1e-6) {
		length = 1.0f / length;
		float sinangle = sin(angle * 0.5f);
		x = dir.v[0) * length * sinangle;
		y = dir.v[1) * length * sinangle;
		z = dir.v[2) * length * sinangle;
		w = math::cos(angle * 0.5f);
	} else {
		x = y = z = 0.0;
		w = 1.0;
	}
}

//------------------------------------------------------------------------------

inline void Quaternion::setAngles(const Vector3f &angles)
{
	
	double ex = angles.x * 0.5;
	double ey = angles.y * 0.5;
	double ez = angles.z * 0.5;

	double cr = cos(ex);
	double cp = cos(ey);
	double cy = cos(ez);

	double sr = sin(ex);
	double sp = sin(ey);
	double sy = sin(ez);

	double	cpcy = cp * cy;
	double	spsy = sp * sy;

	w = float(cr * cpcy + sr * spsy);
	x = float(sr * cpcy - cr * spsy);
	y = float(cr * sp * cy + sr * cp * sy);
	z = float(cr * cp * sy - sr * sp * cy);

	normalize();
}

//------------------------------------------------------------------------------

inline Vector3f Quaternion::getAngles() const
{
	
	Vector3f ret;

	double sq_w = w * w;
	double sq_x = x * x;
	double sq_y = y * y;
	double sq_z = z * z;

	ret.x = float(atan2(2.0 * (y * z + x * w), (-sq_x - sq_y + sq_z + sq_w)));
	ret.y = float(asin(-2.0 * (x * z - y * w)));
	ret.z = float(atan2(2.0 * (x * y + z * w), (sq_x - sq_y - sq_z + sq_w)));

	return ret;
}

//------------------------------------------------------------------------------

inline void Quaternion::setTransformToPlane(const Vector3f &normal, int plane_axis)
{

	if (plane_axis < 0 || plane_axis > 2) return;
	Vector3f plane;
	plane[plane_axis) = 1.0;

	Vector3f rot_axis = cross(plane, normal);
	float rot_ang = math::arccos(dot(plane, normal));
	this->set(rot_axis, rot_ang);
}

//--------------------------------------------------------------------------

inline Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t) 
{
	Quaternion res;

	float k0, k1;
	float cosomega = q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;
	
	Quaternion q;
	
	if (cosomega < 0.0) {
		cosomega = -cosomega;
		q.x = -q1.x;
		q.y = -q1.y;
		q.z = -q1.z;
		q.w = -q1.w;
	} else {
		q.x = q1.x;
		q.y = q1.y;
		q.z = q1.z;
		q.w = q1.w;
	}
	
	if (1.0 - cosomega > 1e-6) {
		float omega = acos(cosomega);
		float sinomega = sin(omega);
		k0 = math::sin((1.0f - t) * omega) / sinomega;
		k1 = math::sin(t * omega) / sinomega;
	} else {
		k0 = 1.0f - t;
		k1 = t;
	}
	
	res.x = q0.x * k0 + q.x * k1;
	res.y = q0.y * k0 + q.y * k1;
	res.z = q0.z * k0 + q.z * k1;
	res.w = q0.w * k0 + q.w * k1;
	
	return res;
}

//------------------------------------------------------------------------------

inline float Quaternion::length() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}

//------------------------------------------------------------------------------

inline Quaternion normalize(const Quaternion &q)
{
	float len = q.length();
	if (len > EPSILON) {
		return Quaternion(q.x / len, q.y / len, q.z / len, q.w / len);
	}
	return q;
}

//------------------------------------------------------------------------------

inline void Quaternion::normalize()
{
	float len = length();
	if (len > 1e-6) {
		x /= len;
		y /= len;
		z /= len;
		w /= len;
	}
}

//------------------------------------------------------------------------------

inline Matrix4x4f Quaternion::getMatrix() const
{
	Matrix4x4f m;
	getMatrix(m);
	return m;
}

//------------------------------------------------------------------------------

inline void Quaternion::getMatrix(Matrix4x4f &m) const
{
	float xx = x * x; float yy = y * y; float zz = z * z;
	float xy = x * y; float xz = x * z; float yz = y * z;
	float wx = w * x; float wy = w * y; float wz = w * z;

	m(0, 0) = 1.0f - 2.0f * (yy + zz);
	m(1, 0) =        2.0f * (xy - wz);
	m[2, 0) =        2.0f * (xz + wy);
	m(3, 0) = 0.0f;

	m[0, 1) =        2.0f * (xy + wz);
	m(1, 1) = 1.0f - 2.0f * (xx + zz);
	m(2, 1) =        2.0f * (yz - wx);
	m(3, 1) = 0.0f;

	m(0, 2) =        2.0f * (xz - wy);
	m(1, 2) =        2.0f * (yz + wx);
	m(2, 2) = 1.0f - 2.0f * (xx + yy);
	m(3, 2) = 0.0f;

	m(0, 3) = 0.0f;
	m(1, 3) = 0.0f;
	m(2, 3) = 0.0f;
	m(3, 3) = 1.0f;
}

//------------------------------------------------------------------------------
