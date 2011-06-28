#pragma once

namespace gb
{
	namespace math
	{
		namespace eIntersectionType
		{
			enum IntersectionType
			{
				/** Один объект полностью внутри другого */
				INSIDE,
				/** Один объект полностью вне другого */
				OUTSIDE,
				/** Объекты либо пересекаются, либо трудно достоверно определить находится ли один объект вне другого */
				INTERSECTING
			};
		}
	}
}