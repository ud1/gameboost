#include "Device.h"
#include "opengl/GLDevice.h"

namespace gb
{
	namespace graphics
	{
		Device *createDevice(const char *)
		{
			return new GLDevice;
		}
	}
}