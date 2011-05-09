#pragma once

#include <gb/base/nullptr.h>
#include <gb/base/RecycleContainer.h>

#include <cassert>

namespace gb
{
	namespace math
	{
		
		/**
		 * \brief Структура для квадродерева, каждый узер хранит ссылки на дочерние узлы
		 * и на родительский узел. Пользовательские данные можно хранить в value.
		 * Разрешается изменять только пользовательские данные, все остальные поля должны
		 * использоваться только для чтения.
		 */
		template<typename T>
		struct Node
		{
			/** Пользовательские данные */
			T value;
			
			// ---------
			// | 0 | 1 |
			// ---------
			// | 2 | 3 |
			// ---------
			/** Дочерние узлы */
			Node<T> *childrens;
			
			/** Родительский узел */
			Node<T> *parent;
			
			/** Шраничащие соседи с таким же lod */
			Node<T> *W, *E, *N, *S; // neighbors
			
			/** абсолютные координаты узла, могут при нимать значения от 0 до (2^lod - 1) */
			int abs_x, abs_y;
			
			/** Уровень, равен 0 для корневого узла дерева, у дочерних узлов на 1 выше чем у родительского */
			int lod;
		
			/** Сброс значений для корневого узла, используется для переиспользования старых узлов без
			 * их пересоздания.
			 */
			void resetRoot()
			{
				abs_x = abs_y = 0;
				lod = 0;
				reset();
			}

			/** Сброс значений для не корневого узла, используется для переиспользования старых узлов без
			 * их пересоздания.
			 */
			void reset()
			{
				parent = W = E = N = S = nullptr;
				childrens = nullptr;
				value.reset();
			}

			/**
			 * Разбивает узел на 4 дочерних, и рекурсивно повторяет операцию при необходимости вверх по дереву.
			 * Разница lod между любыми граничищими узлами не будет превышать 1.
			 * Узлы создаются вызовом createNodes(), которая должна возвращать массив из 4х элементов.
			 * Для каждого новосозданного узла вызывается func(), которая может быть использована для инициализации
			 * пользовательских данных.
			 */
			template <typename CreateNodes, typename Func>
			void split(CreateNodes &createNodes, Func &func)
			{
				if (!this->childrens)
				{
					this->childrens = createNodes();

					childrens[0].abs_x = abs_x*2;
					childrens[0].abs_y = abs_y*2;
					childrens[0].lod = lod + 1;
					childrens[0].parent = this;

					childrens[1].abs_x = abs_x*2 + 1;
					childrens[1].abs_y = abs_y*2;
					childrens[1].lod = lod + 1;
					childrens[1].parent = this;

					childrens[2].abs_x = abs_x*2;
					childrens[2].abs_y = abs_y*2 + 1;
					childrens[2].lod = lod + 1;
					childrens[2].parent = this;

					childrens[3].abs_x = abs_x*2 + 1;
					childrens[3].abs_y = abs_y*2 + 1;
					childrens[3].lod = lod + 1;
					childrens[3].parent = this;
				}

				func(childrens[0]);
				func(childrens[1]);
				func(childrens[2]);
				func(childrens[3]);

				if (parent)
				{
					if (!W && parent->W)
					{
						parent->W->split(createNodes, func);
					}

					if (!E && parent->E)
					{
						parent->E->split(createNodes, func);
					}

					if (!N && parent->N)
					{
						parent->N->split(createNodes, func);
					}

					if (!S && parent->S)
					{
						parent->S->split(createNodes, func);
					}
				}
				
				childrens[0].E = &childrens[1];
				childrens[0].S = &childrens[2];

				childrens[1].W = &childrens[0];
				childrens[1].S = &childrens[3];

				childrens[2].E = &childrens[3];
				childrens[2].N = &childrens[0];

				childrens[3].N = &childrens[1];
				childrens[3].W = &childrens[2];

				if (W && W->childrens)
				{
					W->childrens[1].E = &childrens[0];
					childrens[0].W = &W->childrens[1];

					W->childrens[3].E = &childrens[2];
					childrens[2].W = &W->childrens[3];
				}

				if (E && E->childrens)
				{
					E->childrens[0].W = &childrens[1];
					childrens[1].E = &E->childrens[0];

					E->childrens[2].W = &childrens[3];
					childrens[3].E = &E->childrens[2];
				}

				if (N && N->childrens)
				{
					N->childrens[2].S = &childrens[0];
					childrens[0].N = &N->childrens[2];

					N->childrens[3].S = &childrens[1];
					childrens[1].N = &N->childrens[3];
				}

				if (S && S->childrens)
				{
					S->childrens[0].N = &childrens[2];
					childrens[2].S = &S->childrens[0];

					S->childrens[1].N = &childrens[3];
					childrens[3].S = &S->childrens[1];
				}
			}
			
			/**
			 * Рекурсивный обход зависящих от данного узла других узлов дерева.
			 * Будут посещены только те, которые должны будут быть разбиты при вызове split на данном узле.
			 * Для каждого из посещаемых узлов вызывается func()
			 */
			template <typename Func>
			bool visitRecursive(Func &func)
			{
				func(this);
				
				if (parent)
				{
					if (!W && parent->W && !parent->W->visitRecursive(func))
						return false;

					if (!E && parent->E && !parent->E->visitRecursive(func))
						return false;

					if (!N && parent->N && !parent->N->visitRecursive(func))
						return false;

					if (!S && parent->S && !parent->S->visitRecursive(func))
						return false;
				}

				return true;
			}
		};
		
		/** Так как создавать узлы нужно только по четыре, этот класс объединяет их. */
		template <typename T>
		struct NodeQuad
		{
			typedef Node<T> NodeType;
			NodeType nodes[4];
			
			void reset()
			{
				nodes[0].reset();
				nodes[1].reset();
				nodes[2].reset();
				nodes[3].reset();
			}
		};
		
		/** Контейнер для переиспользования узлов */
		template <typename T>
		struct NodeContainer : public base::RecycleContainer<NodeQuad<T> > {};
		
		/** Адаптер, преобразующий интерфейс контейнера к виду, пригодному для передачи функции Node::split() */
		template <typename T>
		class CreateNodesAdapter
		{
		public:
			typedef Node<T> NodeType;
			
			CreateNodesAdapter(NodeContainer<T> &cont) : container(cont) {}
			
			NodeType *operator()()
			{
				return container()->nodes;
			}
			
		private:
			NodeContainer<T> &container;
		};
	}
}
