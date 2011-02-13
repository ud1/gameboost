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

#include "BBox.h"

//------------------------------------------------------------------------------
//
// namespace gb
//
//------------------------------------------------------------------------------

namespace gb
{

	//--------------------------------------------------------------------------
	//
	// namespace base
	//
	//--------------------------------------------------------------------------
	
	namespace base
	{
		
		//----------------------------------------------------------------------

		BBox::BBox(const Vector3f &p0, const Vector3f &p1) {
			min.x = min(p0.x, p1.x);
			min.y = min(p0.y, p1.y);
			min.z = min(p0.z, p1.z);

			max.x = max(p0.x, p1.x);
			max.y = max(p0.y, p1.y);
			max.z = max(p0.z, p1.z);
		}

		//----------------------------------------------------------------------

		bool BBox::trace(const Line &l, TracePoint &r, bool fs, bool fd) const {
			Plane planes[6];

			planes[0].normal = Vector3f(-1, 0, 0);
			planes[1].normal = Vector3f(0, -1, 0);
			planes[2].normal = Vector3f(0, 0, -1);
			planes[0].setOrigin(min);
			planes[1].setOrigin(min);
			planes[2].setOrigin(min);

			planes[3].normal = Vector3f(1, 0, 0);
			planes[4].normal = Vector3f(0, 1, 0);
			planes[5].normal = Vector3f(0, 0, 1);
			planes[3].setOrigin(max);
			planes[4].setOrigin(max);
			planes[5].setOrigin(max);

			bool result = false;
			float dist = -1;

			TracePoint itr;

			for (int i=0; i<6; i++) {
				if (/*distance(planes[i], l.src) > 0 && */planes[i].trace(l, itr, fs, fd)) {
					Vector3f p = itr.point - planes[i].normal * getExtents(); // смещаем пересечение к центру, чтобы не применять эпсилон в проверке
					if (p >= min && p <= max - planes[i].normal * 0.01f) {
						float len = (itr.point - l.src).lengthSquared();
						if (len < dist || dist < 0) {
							r = itr;
							dist = len;
							result = true;
						}
					}
				}
			}
			return result;

		}

		//----------------------------------------------------------------------

		Vector3f BBox::getVertex(int i) const {

			assert(i > 0 && i <= 7);
			const Vector3f *bounds = &min;

			return Vector3f(bounds[i % 2].x, bounds[(i / 2) % 2].y, bounds[(i / 4) % 2].z);
		}

		//----------------------------------------------------------------------

		Plane BBox::getPlane(int i) const {

			assert(i > 0 && i <= 5);

			const Vector3f *bounds = &min;

			Plane ret;
			ret.normal[i % 3] = float((i / 3) % 2) * 2.0f - 1.0f;
			ret.setOrigin(bounds[(i / 3) % 2]);

			return ret;
		}

		//----------------------------------------------------------------------

		void BBox::include(const Vector3f &v, float r) {
			if (v.x - r < min.x) min.x = v.x - r;
			if (v.y - r < min.y) min.y = v.y - r;
			if (v.z - r < min.z) min.z = v.z - r;

			if (v.x + r > max.x) max.x = v.x + r;
			if (v.y + r > max.y) max.y = v.y + r;
			if (v.z + r > max.z) max.z = v.z + r;
		}
		
		//----------------------------------------------------------------------
		
	}
	
	//--------------------------------------------------------------------------
	
}
