#pragma once

namespace gb
{
	namespace fs
	{
		namespace eSeekType
		{
			enum SeekType {
				HEAD = 0,
				CURRENT,
				TAIL,
			};
		}
		
		typedef long off_t;
	}
}