#pragma once

#include <boost/intrusive/list.hpp>
#include <boost/concept_check.hpp>

namespace gb
{
	namespace base
	{
		
		/**
		 * \brief Используется для переиспользования ненужных объектов, без необходимости их пересоздания.
		 * 
		 * Целью является снижение количества вызовов new/delete в программе.
		 * RecycleContainer хранит список объектов типа T. Для использования должен быть задан
		 * источник не используемых объектов - такой же контейнер RecycleContainer.
		 * При вызове оператора () извлекается объект из источника, если он не пуст,
		 * или создаётся новый объект в противном случае. Результат сохраняется во внутренем списке.
		 * Тип T должен иметь конструктор без параметров, а так же функцию reset() сбрасывающую состояние
		 * объекта в первоначальное состояние.
		 */
		template <typename T>
		class RecycleContainer
		{
		public:
			
			~RecycleContainer()
			{
				clear();
			}
			
			/** Задаёт источник объектов */
			void setSource(RecycleContainer<T> *src)
			{
				source = src;
			}
			
			/** Возвращает объект из источника или создаёт новый, если в источнике больше не осталось объектов */
			T *operator()()
			{
				Node *result;
				if (!source->objects.empty())
				{
					result = &*source->objects.begin();
					result->node.reset();
					source->objects.erase(source->objects.begin());
				}
				else
				{
					result = new Node<T>;
				}
				
				objects.push_front(*result);
				return &result->node;
			}
			
			/** Удаляет все объекты из источника */
			void clearSource()
			{
				source->clear();
			}
			
		private:
			typedef boost::intrusive::list_base_hook<> ListHook;
			
			struct Node : public ListHook
			{
				T node;
			};
			
			typedef boost::intrusive::list<Node> ObjectList;
			
			ObjectList objects;
			
			RecycleContainer<T> *source;
			
			void clear()
			{
				while(!objects.empty())
				{
					Node *p = &*objects.begin();
					objects.erase(objects.begin());
					delete p;
				}
			}
		};
	}
}
