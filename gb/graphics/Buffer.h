#pragma once
#include "../base/IRefCountable.h"

namespace gb
{
	namespace graphics
	{
		
		/**
		 * @ingroup graphics_group
		 * \brief Интерфейс вершинных или индексных буфферов
		 */
		class Buffer : public base::IRefCountable
		{
		public:
			/** Задаёт размер элемента в байтах */
			void setElementSize(size_t bytes)
			{
				element_size = bytes;
				is_created = false;
			}

			/** Задаёт размер буффера */
			void setElementsNumber(size_t num)
			{
				nelements = num;
				is_created = false;
			}

			/** \return Число элементов */
			size_t getElementSize() const {return element_size;}
			
			/** \return Размер буфера */
			size_t getElementsNumber() const {return nelements;}
			
			/** Маппинг части буффера. Возвращаемый указатель действителен до первого вызова unmap(). Данные в указанном регионе затираются. */
			virtual void* map(size_t offset_bytes, size_t size_in_bytes) = 0;
			
			/** Удаляет маппинг буфера, записанные в него данные заполняют соответсвующий блок буфера */
			virtual void unmap() = 0;
			
			/** Обновление части или всего буфера */
			virtual void subData(size_t offset_bytes, size_t size_in_bytes, void *data) = 0;
			
		protected:
			bool is_created;
			size_t nelements, element_size;
		};
		
		typedef base::RefCntHolder<Buffer> PBuffer;
		
	}
}