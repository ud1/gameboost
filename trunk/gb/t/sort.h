/**  \file
 \brief sort template functions

*/


#pragma once

#include <assert.h> 

namespace gb 
{
	namespace t 
	{



		template<typename T>
		/** \brief Пузырьковая сортировка буфера   */
		void sortBuffer_bubble(T* items, const int count) 
		{
			if(count == 0) return ;

			register int i, j;
			register T t;
			// void bubble(char *items, int count)
			for(i = 1; i < count; ++i)
				for( j = count-1; j >= i; --j) 
				{
					if( !(items[j - 1] < items[ j ]) ) 
					{
						// exchange elements 
						t = items[j - 1];
						items[j - 1] = items[ j ];
						items[ j ] = t;
					}
				}
		};



		template<typename T>
		/** \brief  Сортировака массива выборкой */
		void sortBuffer_select(T* items, const int count) 
		{
			if(count == 0) return;

			register int a, b, c;
			int exchange;
			T t;

			for(a = 0; a < count-1; ++a) 
			{
				exchange = 0;
				c = a;
				t = items[ a ];
				for(b = a + 1; b < count; ++b) 
				{
					if(items[ b ] < t) 
					{
						c = b;
						t = items[ b ];
						exchange = 1;
					}
				}
				if(exchange) 
				{
					items[ c ] = items[ a ];
					items[ a ] = t;
				}
			}
		};



		template <typename T>
		/** \brief  Сортировка буфера вставкой */
		void sortBuffer_insertion(T* t, const int length) 
		{
			if(0==length) return;
			int i;
			T key ;
			for(int j=1;j<length;j++)
			{
				key=t[j];
				i=j-1;
				while(  !(t[i]<key) && i>=0  )
				{
					t[i+1]=t[i];
					i--;
				}
				t[i+1]=key;
			}
		};



		template <typename T>
		/** \brief Сортировка буфера перемешиванием  */
		void sortBuffer_shaker(T* items, const int count) 
		{
			if(0==count) return;
			register int i;
			int exchange;
			T t;

			do {
				exchange = 0;
				for(i = count - 1; i > 0; --i) 
				{
					if( !(items[i - 1] < items[ i ]) ) 
					{
						t = items[i - 1];
						items[i - 1] = items[ i ];
						items[ i ] = t;
						exchange = 1;
					}
				}

				for(i = 1; i < count; ++i) 
				{
					if(  !(items[i - 1] < items[ i ])  ) 
					{
						t = items[i-1];
						items[i - 1] = items[ i ];
						items[ i ] = t;
						exchange = 1;
					}
				}
			} while(exchange); // sort until no exchanges  
		};


		template <typename T>
		/** \brief Сортировка буфера методом Шелла */
		void sortBuffer_shell(T* items, const int count) 
		{
			if(0==count) return ;
			int i, j, gap, k;
			T x;
			char a[5];

			a[0]=8; a[1]=5; a[2]=3; a[3]=2; a[4]=1;

			for(k=0; k < 5; k++) 
			{
				gap = a[k];
				for(i=gap; i < count; ++i) 
				{
					x = items[i];
					for(j=i-gap; (x < items[j]) && (j >= 0); j=j-gap)
					{
						items[j+gap] = items[j];
					}
					items[j+gap] = x;
				}
			}
		};



		template <typename T>
		/** \brief Быстрая сортировка буфера  по индексам диапазона */
		void sortBuffer_quick(T* items, int left, int right)
		{
			int i, j;
			T x;
			T y;

			i = left;
			j = right;
			x = items[(left+right)/2];

			do {
				while((items[i] < x) && (i < right))
					i++;
				while((x < items[j]) && (j > left))
					j--;

				if(i <= j) 
				{
					y = items[i];
					items[i] = items[j];
					items[j] = y;
					i++; j--;
				}
			} while(i <= j);

			if(i < right)
				sortBuffer_quick(items, i, right);
			if(left < j)
				sortBuffer_quick(items, left, j);

		};



		template <typename T>
		/** \brief Быстрая сортировка  буфера */
		void sortBuffer_quick(T* items, const int nLen) 
		{
			if(0==nLen) return;
			sortBuffer_quick(items, 0, nLen-1);
		};

 

	}
}
// end file