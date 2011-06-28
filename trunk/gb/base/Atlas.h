#pragma once

#include "Rectangle.h"
#include <cstdlib>

namespace gb
{
	namespace base
	{
		
		/**
		 * Класс управлющий добавлением прямоугольных областей в текстурный атлас
		 * Используемый алгоритм: http://www.gamedev.ru/pages/coriolis/articles/Packing_Lightmaps 
		 */
		class Atlas {
		public:
			/**
			 * Колбэк вызываемый функцией insert для увеличения размера
			 * текстуры в два раза по ширине или по высоте в случае,
			 * если не хватает места для добавления прямоугольника в атлас.
			 * Должна возвращать true если увеличение размера текстуры прошло успешно,
			 * и false в противном случае
			 */
			typedef bool (*ResizeFunc)(int new_width, int new_height, void *user_data);
			
			Atlas(int w, int h)
			{
				root = new Node;
				root->rc.width = w;
				root->rc.height = h;
				root->rc.left = root->rc.top = 0;
				
				resizeFunc = NULL;
				user_data = NULL;
			}

			Atlas()
			{
				root = new Node;
				root->rc.left = root->rc.top = 0;
			}
			
			void setResizeFunc(ResizeFunc resizeFunc_, void *user_data_)
			{
				resizeFunc = resizeFunc_;
				user_data = user_data_;
			}

			void setSize(int w, int h)
			{
				root->rc.width = w;
				root->rc.height = h;
			}

			~Atlas()
			{
				delete root;
			}

			int getWidth()
			{
				return root->rc.width;
			}

			int getHeight()
			{
				return root->rc.height;
			}

			/**
			 * rc должен содержать размеры width/height прямоугольника,
			 * который вставляеся в атлас. При успешной вставке
			 * функция устанавливает координаты left/top угла в rc и возвращает true
			 */
			bool insert(Rectangle &rc);

		private:
			ResizeFunc resizeFunc;
			void *user_data;
			
			struct Node
			{
				Node()
				{
					child[0] = child[1] = NULL;
					has_image = false;
				}
				
				~Node()
				{
					if (child[0])
					{
						delete child[0];
						delete child[1];
					}
				}
				
				Node *child[2];
				Rectangle rc;
				bool has_image;
			} *root;

			Node *insert(Node *node, Rectangle &rc);
		};
		
	}
}
