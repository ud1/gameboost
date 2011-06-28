#pragma once
#include <gb/base/IRefCountable.h>

namespace gb
{
	namespace graphics
	{
		
		class Buffer : public base::IRefCountable
		{
		public:
			void setElementSize(size_t bytes)
			{
				element_size = bytes;
				is_created = false;
			}

			void setElementsNumber(size_t num)
			{
				nelements = num;
				is_created = false;
			}

			size_t getElementSize() const {return element_size;}
			size_t getElementsNumber() const {return nelements;}
			
			virtual void* map(size_t offset_bytes, size_t size_in_bytes) = 0;
			virtual void unmap() = 0;
			virtual void subData(size_t offset_bytes, size_t size_in_bytes, void *data) = 0;
			
		protected:
			bool is_created;
			size_t nelements, element_size;
		};
		
		typedef base::RefCntHolder<Buffer> PBuffer;
		
	}
}