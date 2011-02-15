//------------------------------------------------------------------------------
//
// 
//
// copyright:	
// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)
// mailto:		anandamide@mail.ru
//
//------------------------------------------------------------------------------

#ifndef MathCoreH
#define MathCoreH

//------------------------------------------------------------------------------

#include <math.h>

//------------------------------------------------------------------------------

#define EPSILON		1.0e-6f

#define PI			3.14159265358979323846f
#define PI_2		1.57079632679489661923f
#define PI_4		0.78539816339744830961f
#define EXP			2.71828182845904523536f
#define GOLD_RATIO	1.61803398874988749894f

#define DEG_TO_RAD	0.01745329251994329576f
#define RAD_TO_DEG	57.2957795130823209071f

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {
	
	//--------------------------------------------------------------------------

	class vec3;
	class quat;
	class BBox;
	class BSphere;

	//--------------------------------------------------------------------------

	namespace math {

		//----------------------------------------------------------------------
		// basic math functions
		//----------------------------------------------------------------------

		float	sqr(float a);
		float	sqrt(float a);
		float	invsqrt(float a);
		
		float	cos(float a);
		float	sin(float a);
		float	arctg(float y, float x);
		float	arccos(float x);
		float	arcsin(float x);
		void	sincos(float alpha, float &sn, float &cs);

		float	abs(float a);
		vec3	abs(const vec3 &a);
		float	sign(float x);

		//----------------------------------------------------------------------
		// templates
		//----------------------------------------------------------------------
		
		#undef min
		#undef max

		template <class T> 
		static T min(const T &a, const T &b) {
			return (a < b) ? a : b;
		}
		
		template <class T> 
		static T max(const T &a, const T &b) {
			return (a > b) ? a : b;
		}
		
		template <class T> 
		static T abs(const T &a) {
			return (a < 0) ? -a : a;
		}
		
		template <class T>
		static void swap(T &a, T &b) {
			T temp = a; a = b; b = temp;
		}
		
		template <class T> 
		static T lerp(const T &a, const T &b, float k) {
			return a + (b - a) * k;
		}

		//----------------------------------------------------------------------
		// random
		//----------------------------------------------------------------------

		float random(float range);
		vec3 random(const vec3 &range);
		vec3 random(const BBox &range);
		vec3 random(const BSphere &range);
		int random(int __num);
		void randomize(void);

		//----------------------------------------------------------------------

	}

	//--------------------------------------------------------------------------
	//
	// class vec3
	//
	//--------------------------------------------------------------------------

	class vec3 {

	public:

		//----------------------------------------------------------------------

		union {
			struct { float x, y, z; };
			struct { float r, g, b; };
			struct { float v[3]; };
		};

		//----------------------------------------------------------------------

		vec3() : x(0.0f), y(0.0f), z(0.0f) {}
		vec3(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {}
		vec3(const vec3 &v) : x(v.x), y(v.y), z(v.z) {}

		//----------------------------------------------------------------------

		vec3 &operator= (const vec3 &v) { x = v.x; y = v.y;	z = v.z; return *this; }
		vec3 operator- () const { return vec3(-x, -y, -z); }
		vec3 operator+ () const { return vec3(x, y, z); }

		//----------------------------------------------------------------------

		vec3 operator+ (const vec3 &v) const { return vec3(x + v.x, y + v.y, z + v.z); }
		vec3 operator- (const vec3 &v) const { return vec3(x - v.x, y - v.y, z - v.z); }
		vec3 operator* (const vec3 &v) const { return vec3(x * v.x, y * v.y, z * v.z); }
		vec3 operator/ (const vec3 &v) const { return vec3(x / v.x, y / v.y, z / v.z); }
		vec3 operator* (float a) const { return vec3(x * a, y * a, z * a); }
		vec3 operator/ (float a) const { return vec3(x / a, y / a, z / a); }

		//----------------------------------------------------------------------

		vec3 &operator+= (const vec3 &v) { x += v.x; y += v.y; z += v.z; return *this; }
		vec3 &operator-= (const vec3 &v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		vec3 &operator/= (const vec3 &v) { x /= v.x; y /= v.y; z /= v.z; return *this; }
		vec3 &operator*= (const vec3 &v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
		vec3 &operator*= (float a) { x *= a; y *= a; z *= a; return *this; }
		vec3 &operator/= (float a) { x /= a; y /= a; z /= a; return *this; }

		//----------------------------------------------------------------------

		float &operator[] (int i) { return v[i]; }
		float operator[] (int i) const { return v[i]; }

		//----------------------------------------------------------------------

		bool operator== (const vec3 &v) const { return math::abs(x - v.x) <= EPSILON && math::abs(y - v.y) <= EPSILON && math::abs(z - v.z) <= EPSILON; }
		bool operator!= (const vec3 &v) const { return math::abs(x - v.x) > EPSILON || math::abs(y - v.y) > EPSILON || math::abs(z - v.z) > EPSILON; }

		//----------------------------------------------------------------------

		bool operator> (const vec3 &v) const { return (x - v.x) > EPSILON && (y - v.y) > EPSILON && (z - v.z) > EPSILON; }
		bool operator< (const vec3 &v) const { return (x - v.x) < -EPSILON && (y - v.y) < -EPSILON && (z - v.z) < -EPSILON; }
		bool operator>= (const vec3 &v) const { return (x - v.x) >= -EPSILON && (y - v.y) >= -EPSILON && (z - v.z) >= -EPSILON; }
		bool operator<= (const vec3 &v) const { return (x - v.x) <= EPSILON && (y - v.y) <= EPSILON && (z - v.z) <= EPSILON; }

		bool isZero() const { return math::abs(x) < EPSILON && math::abs(y) < EPSILON && math::abs(z) < EPSILON; }
		bool isOne() const { return math::abs(x - 1.0f) < EPSILON && math::abs(y - 1.0f) < EPSILON && math::abs(z - 1.0f) < EPSILON; }
		bool equals(const vec3 &v, float eps = EPSILON) const { return math::abs(x - v.x) <= eps && math::abs(y - v.y) <= eps && math::abs(z - v.z) <= eps; }

		//----------------------------------------------------------------------

		float length() const { return math::sqrt(x * x + y * y + z * z); }
		float lengthSquared() const { return x * x + y * y + z * z; }

		//----------------------------------------------------------------------

		friend float dot(const vec3 &, const vec3 &);
		friend vec3 cross(const vec3 &, const vec3 &);
		friend vec3 normalize(const vec3 &);

		//----------------------------------------------------------------------

		void normalize();

		//----------------------------------------------------------------------
		
	};

	//--------------------------------------------------------------------------
	//
	// template vec2x
	//
	//--------------------------------------------------------------------------

	template <class T>
	class vec2x {

	public:

		union {
			struct { T x, y; };
			struct { T u, v; };
		};

		vec2x(T nx = 0, T ny = 0) : x(nx), y(ny) { }
		
	};
	
	//--------------------------------------------------------------------------
	//
	// template vec3x
	//
	//--------------------------------------------------------------------------

	template <class T>
	class vec3x {

	public:

		union {
			struct { T x, y, z; };
			struct { T r, g, b; };
			struct { T v[3]; };
		};

		vec3x(T nx = 0, T ny = 0, T nz = 0) : x(nx), y(ny), z(nz) { }
		
	};

	//--------------------------------------------------------------------------
	//
	// template vec4x
	//
	//--------------------------------------------------------------------------

	template <class T>
	class vec4x {

	public:

		union {
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			struct { T v[4]; };
		};

		vec4x(T nx = 0, T ny = 0, T nz = 0, T nw = 0) : x(nx), y(ny), z(nz), w(nw) { }

	};

	//--------------------------------------------------------------------------
	//
	// vector types
	//
	//--------------------------------------------------------------------------

	typedef vec2x <float> vec2f;
	typedef vec2x <short> vec2s;
	typedef vec2x <char> vec2b;
	typedef vec2x <int> vec2i;
	
	typedef vec3x <short> vec3s;
	typedef vec3x <char> vec3b;
	typedef vec3x <int> vec3i;

	typedef vec4x <float> vec4f;
	typedef vec4x <int> vec4i;

	#define vec3f vec3
	#define vec2 vec2f
	#define vec4 vec4f

	//--------------------------------------------------------------------------
	//
	// class mat4
	//
	//--------------------------------------------------------------------------

	class mat4 {

	public:

		//----------------------------------------------------------------------
		
		union {
			struct { float data[4][4]; };
			struct { float v[16]; };
		};

		//----------------------------------------------------------------------

		mat4();

		//----------------------------------------------------------------------
		
		void identity();
		bool inverse();
		void transpose();

		//----------------------------------------------------------------------
		
		void basis(const vec3 &, const vec3 &, const vec3 &, const vec3 &);

		//----------------------------------------------------------------------
		
		mat4 operator* (const mat4 &) const;
		vec3 operator* (const vec3 &) const;
		vec4 operator* (const vec4 &) const;

		//----------------------------------------------------------------------
		
		bool operator== (const mat4 &o);
		bool operator!= (const mat4 &o);

		bool equals(const mat4 &o, float eps);

		//----------------------------------------------------------------------

		static mat4 rotateX(float);
		static mat4 rotateY(float);
		static mat4 rotateZ(float);
		static mat4 translate(const vec3 &);
		static mat4 scale(const vec3 &);

		//----------------------------------------------------------------------
		
		vec3 getPos() const;
		void setPos(const vec3 &pos);
		void setScale(const vec3 &scale);

		//----------------------------------------------------------------------
		
		void mult(const mat4 &m);
		void multOrder(const mat4 &m);
		void normalize();
		void decompose(vec3 &pos, quat &rot, vec3 &scale) const;

		//----------------------------------------------------------------------
		
		vec4 getRow(int i) const;
		vec4 getColumn(int i) const;

		//----------------------------------------------------------------------
		
		operator float *() { return (float *)data; }
		operator const float *() const { return (const float *)data; }

		//----------------------------------------------------------------------
		
	};

	//--------------------------------------------------------------------------
	//
	// struct quat
	//
	//--------------------------------------------------------------------------

	class quat {

	public:

		union {
			struct { float x, y, z, w; };
			struct { float v[4]; };
		};

		quat() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
		quat(const vec3 &dir, float angle) { set(dir,angle); }
		quat(const vec3 &ang) { set(ang); }
		quat(const quat &q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
		quat(float nx, float ny, float nz, float nw) : x(nx), y(ny), z(nz), w(nw) { }

		bool operator== (const quat &v) const { return 
				math::abs(x - v.x) <= EPSILON && 
				math::abs(y - v.y) <= EPSILON && 
				math::abs(z - v.z) <= EPSILON && 
				math::abs(w - v.w) <= EPSILON;
		}
		
		bool operator!= (const quat &v) const {
			return 
				math::abs(x - v.x) > EPSILON ||
				math::abs(y - v.y) > EPSILON || 
				math::abs(z - v.z) > EPSILON || 
				math::abs(w - v.w) > EPSILON;
		}

		bool isIdentity() const { 
			return 
				math::abs(x) < EPSILON && 
				math::abs(y) < EPSILON && 
				math::abs(z) < EPSILON && 
				math::abs(w) - 1.0f < EPSILON;
		}

		float &operator[](int i) { return v[i]; }
		float operator[](int i) const { return v[i]; }

		quat operator- () const { return quat(x, y, z, -w); }
		quat operator* (const quat &q) const;
		quat &operator*=(const quat &q);
		void normalize();
		float length() const;

		void set(const vec3 &dir, float angle);
		void set(const vec3 &angles);

		vec3 getAngles() const;
		vec3 getLocalAngles() const;

		mat4 getMatrix() const;
		void fromMatrix(const mat4 &m);
		void getMatrix(mat4 &) const;
		void transformToPlane(const vec3 &normal, int plane_axis = 2);

		friend quat slerp(const quat &q0, const quat &q1, float t);
		friend quat normalize(const quat &);
		
	};

	//--------------------------------------------------------------------------
	//
	// struct Line
	//
	//--------------------------------------------------------------------------

	class Line {

	public:

		vec3 src;
		vec3 dst;

		Line() { }
		Line(const vec3 &s, const vec3 &d) : src(s), dst(d) { }

		vec3 getDirection() const { return (dst - src); }
	};

	//--------------------------------------------------------------------------
	//
	// struct TracePoint
	//
	//--------------------------------------------------------------------------

	struct TracePoint {

		vec3 point;
		vec3 normal;
		vec3 texcoord;

	};

	//--------------------------------------------------------------------------
	//
	// class Plane
	//
	//--------------------------------------------------------------------------

	class Plane {

	public:
		vec3 normal;
		float dist;

		Plane() : normal(0.0f, 0.0f, 1.0f), dist(0.0f) {}
		Plane(const vec3 &n, float d) : normal(n), dist(d) {}
		Plane(const vec3 &, const vec3 &);

		vec3 getOrigin();
		void setOrigin(const vec3 &);

		void normalize();
		friend Plane normalize(const Plane &);
		bool trace(const Line &, TracePoint &, bool = false, bool = false) const;
	};

	//--------------------------------------------------------------------------
	//
	// class BSphere
	//
	//--------------------------------------------------------------------------

	class BSphere {

	public:
		vec3 center;
		float radius;

		BSphere() : radius(0.0f) {};
		BSphere(const vec3 &c, float r) : center(c), radius(r) {}
		bool trace(const Line &, TracePoint &, bool = false, bool = false) const;

		void include(const vec3 &, float = 0.0f);

	};

	//--------------------------------------------------------------------------
	//
	// class BBox
	//
	//--------------------------------------------------------------------------

	class BBox {

	public:

		vec3 min;
		vec3 max;

		BBox() {};
		BBox(const vec3 &mn, const vec3 &mx);

		vec3 getOrigin() const { return min + (max - min) * 0.5f; }
		vec3 getExtents() const { return (max - min) * 0.5; }

		vec3 getVertex(int) const;
		Plane getPlane(int) const;

		bool trace(const Line &, TracePoint &, bool = false, bool = false) const;
		void include(const vec3 &, float = 0.0f);

	};

	//--------------------------------------------------------------------------
	//
	// class Frustum
	//
	//--------------------------------------------------------------------------

	class Frustum {

		Plane planes[6];

		int viewport[4];
		mat4 modelview;
		mat4 projection;

		void invalidate();

	public:

		Frustum();
		Frustum(const float *mv, const float *p, int *vp) { set(mv, p, vp); }
		void set(const float *mv, const float *p, int *vp);

		const mat4 &getModelview() const { return modelview; }
		const mat4 &getProjection() const { return projection; }

		const int *getViewport() const { return viewport; }
		const Plane &getPlane(int i) const { return planes[i]; }

		void setPerspective(float fov, float ratio, float near, float far);

		void setModelview(const mat4 &);
		void setProjection(const mat4 &);

		void setViewport(int *);
		
		virtual vec3 unproject(const vec3 &v) const;
		virtual vec3 project(const vec3 &) const;


	};

	//--------------------------------------------------------------------------
	//
	// class Origin
	//
	//--------------------------------------------------------------------------

	class Origin {

	public:

		vec3 pos;
		quat rot;
		vec3 scale;

		Origin() : scale(1.0, 1.0, 1.0) {}
		Origin(const vec3 &p, const quat &r, const vec3 &s) : pos(p), rot(r), scale(s) { }

		void getMatrix(mat4 &m) const {
			m = mat4::scale(scale) * rot.getMatrix() * mat4::translate(pos);
		}

		mat4 getMatrix() const {
			mat4 ret;
			getMatrix(ret);
			return ret;
		}

		void getInverseMatrix(mat4 &m) const {
			vec3 iScale(1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z);
			quat iRot(rot.x, rot.y, rot.z, -rot.w);
			vec3 iPos(-pos.x, -pos.y, -pos.z);
			m = mat4::translate(iPos) * iRot.getMatrix() * mat4::scale(iScale);
		}

		mat4 getInverseMatrix() const {
			mat4 ret;
			getInverseMatrix(ret);
			return ret;
		}

		Origin operator *(const Origin &o) const {
			return Origin(pos + o.pos, rot * o.rot, scale * o.scale);
		}

		Origin getInverted() {
			return Origin(-pos, -rot, vec3(1.0f, 1.0f, 1.0f) / scale);
		}

		Origin &operator*=(const Origin &o) {
			pos += o.pos;
			rot *= o.rot;
			scale *= o.scale;
			return *this;
		}

		friend Origin interp(const Origin &o1, const Origin &o2, float t) {
			Origin res;
			res.pos = math::lerp(o1.pos, o2.pos, t);
			res.rot = slerp(o1.rot, o2.rot, t);
			res.scale = math::lerp(o1.scale, o2.scale, t);
			return res;
		}
		
	};

	//--------------------------------------------------------------------------
	//
	// template Integrator
	//
	//--------------------------------------------------------------------------
	
	template <class Class>
	class Integrator {

	public:

		Class pos;
		Class velocity;
		Class force;

		void update(float dt) {
			pos += (velocity + force * dt * 0.5f) * dt;
			velocity += force * dt;
		}

		Class getPosDelta(float dt) const {
			return (velocity + force * dt * 0.5f) * dt;
		}

		Class getVelocityDelta(float dt) const {
			return force * dt;
		}

	};

	//--------------------------------------------------------------------------
	//
	// distance
	//
	//--------------------------------------------------------------------------

	float distance(const vec3 &, const vec3 &);
	float distance(const Plane &, const vec3 &);
	float distance(const Line &, const vec3 &);

	//--------------------------------------------------------------------------
	//
	// overlap test
	//
	//--------------------------------------------------------------------------

	bool overlaps(const BSphere &, const BSphere &);
	bool overlaps(const BBox &, const BBox &);
	bool overlaps(const BSphere &, const BBox &);
	bool overlaps(const BSphere &, const BBox &, const mat4 &boxMatrix);
	bool overlaps(const BBox &a, const mat4 &aInvTransform, const BBox &b, const mat4 &bTransform);

	bool overlaps(const BBox &, const Frustum &);
	bool overlaps(const BBox &, const mat4 &boxTransform, const Frustum &);
	bool overlaps(const BSphere &, const Frustum &);

	bool overlapsExact(const BSphere &, const BBox &, const mat4 &boxMatrix);

	//--------------------------------------------------------------------------
	//
	// tracing
	//
	//--------------------------------------------------------------------------

	bool traceTriangle(
		const Line &ray, 
		const vec3 &v0, 
		const vec3 &v1, 
		const vec3 &v2, 
		vec3 &res, 
		bool fs = false, 
		bool fd = false
	);

	//--------------------------------------------------------------------------
	//
	// string functions
	//
	//--------------------------------------------------------------------------

    const char *intToStr(int i);
    const char *floatToStr(float i);
    const char *vec3ToStr(const vec3 &v);
    const char *quatToStr(const quat &q);
    const char *mat4ToStr(const mat4 &m);

    inline const char *toString(int i) { return intToStr(i); }
    inline const char *toString(float f) { return floatToStr(f); }
    inline const char *toString(const vec3 &v) { return vec3ToStr(v); }
    inline const char *toString(const quat &q) { return quatToStr(q); }
    inline const char *toString(const mat4 &m) { return mat4ToStr(m); }

    int strToInt(const char *str);
    float strToFloat(const char *str);
    vec3 strToVec3(const char *str);
    quat strToQuat(const char *str);
    mat4 strToMat4(const char *str);

    void fromString(const char *str, int &i);
    void fromString(const char *str, float &f);
    void fromString(const char *str, vec3 &v);
    void fromString(const char *str, quat &q);
    void fromString(const char *str, mat4 &m);
    
	//--------------------------------------------------------------------------
	
}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
