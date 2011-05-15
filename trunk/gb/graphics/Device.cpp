#include "Device.h"
#include "opengl/GLDevice.h"

namespace
{
	const char *PrimTypes[] =
	{
		"POINTS",
		"LINE_STRIP",
		"LINE_LOOP",
		"LINES",
		"TRI_STRIP",
		"TRI_FAN",
		"TRIANGLES"
	};
}

namespace gb
{
	namespace graphics
	{
		Device *createDevice(const char *)
		{
			return new GLDevice;
		}
		
		Device::PrimitiveType Device::getPrimTypeByName(const std::string &name)
		{
			for (size_t i = 0; i < Device::PRIMITIVE_TYPES_COUNT; ++i)
			{
				if (name == PrimTypes[i])
					return (Device::PrimitiveType) i;
			}
			return Device::PRIMITIVE_TYPES_COUNT;
		}
		
		const char *Device::getPrimTypeName(PrimitiveType type)
		{
			return PrimTypes[type];
		}
	}
}