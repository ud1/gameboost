/*=======================================================*\
 * file:      examples/containers/main.cpp               *
 * author:    Sharov "Zefick" Sergey  zefick@mail.ru     *
 * date:      28.03.2011                                 *
\*=======================================================*/

#include "kdtree.h"
#include <cstdlib>
#include <cstdio>

/**
 * Тестовая программа для демонстрации работы kd-деревьев
 */
int main () {
	// Создание экземпляра дерева
	gb::containers::kdTree<int> tree;

	// Вставка случайных точек в дерево
	for (int i=0; i<20; ++i) {
		int x = rand()%100, y = rand()%100;
		tree.add(x, y, i+1);
		printf("%3d: (%d, %d)\n", i+1, x, y);
	}
	// Вывод ближайшего к точке (50, 50) узла
	printf("%d", tree.search(50, 50));
}
