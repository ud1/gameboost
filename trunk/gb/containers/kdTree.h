/*=======================================================*\
 * file:      gb/graphics/containers/kdTree.h            *
 * author:    Sharov "Zefick" Sergey  zefick@mail.ru     *
 * date:      27.03.2011                                 *
 * version:   1.0                                        *
\*=======================================================*/

#ifndef KDTREE_H
#define KDTREE_H

#include <cstdlib>

namespace gb {
namespace containers {

/**
 * Класс двухмерного kd-дерева<br/>
 * http://en.wikipedia.org/wiki/Kd-tree<br/>
 *
 * Данная реализация предназначена для быстрого поиска точки
 * среди множества других, которая была бы ближе всех остальных
 * к другой заданной точке, не входящей во вможество.<br/>
 *
 * Польза от класса при разработке игр очевидна - можно легко находить
 * объекты на карте, ближайшие к некоторой позиции.<br/>
 *
 * Следует учитывать, что специфика класса такова, что узлы хранятся именно как
 * точки, а не как протяжённые объекты.<br/>
 *
 * <future> В следующей версии планируется добавить функцию поиска по предикату,
 * которая позволит исключать из поиска узлы, неудовлетворяющие
 * заданным свойствам.<br/>
 * Также неплохо бы добавить функцию построения дерева по коллекции точек,
 * которая будет вычислять оптимальный порядок добавления.<br/>
 *
 * @param T тип данных, которые будут храниться в узлах дерева.
 * Функция поиска возвращает именно данные, а не найденный узел дерева.
 * Данными могут служить, например, указатели на объекты.<br/>
 */
template <typename T>
class kdTree {

	/**
	 * Структура для узла kd-дерева
	 */
	struct kdNode {
		kdNode (int x, int y, char t, T value)
				: type(t), data(value) {
			child[0] = child[1] = NULL;
			coord[0] = x;
			coord[1] = y;
		}

	    kdNode *child[2];   // указатели на потомков
	    float coord[2];     // позиция разделяющего узла
	    char type;          // тип разделения (0-x, 1-y)
	    T data;             // пользовательские данные
	};

	kdNode *root;           // корневой узел дерева

public:

	/**
	 * Создание пустого дерева.
	 */
	kdTree () {
		root = NULL;
	}

	/**
	 * Добавление узла в дерево
	 *
	 * @param {x, y} координаты нового узла
	 * @param value значение, которое будет храниться в узле
	 */
	void add (float x, float y, T value) {
	    add (&root, x, y, value);
	}

	/**
	 * Поиск ближайщего к указанным координатам узла в дереве
	 *
	 * @param {x, y} коориднаты тестируемой точки
	 * @return значение ближайшего к точке узла. Если в дереве нет подходящего
	 * узла, то возвращается значение хранимого типа по умолчанию.
	 *
	 * <!-- планы на будущее - сделать шаблонную функцию search,
	 * принимающую предикат, который будет отсеивать проверяемые узлы -->
	 */
	T search (float x, float y) {
		kdNode * node = search(root, x, y);
		if (node != NULL)
			return node->data;
		return T();
	}

private:

	/**
	 * вычисление квадрата расстояния между узлом и заданными координатами
	 */
	float kdDist(kdNode *node, float x, float y) {
	    float dx = node->coord[0]-x, dy = node->coord[1]-y;
	    return dx*dx + dy*dy;
	}

	/**
	 * Добавление потомка в заданный узел
	 *
	 * @param указатель на местоположение узла, в который осуществляется вставка
	 * @param {x, y} коориднаты вставляемого узла
	 * @param value значение, хранящееся во вставляемом узле
	 * @param dim координата, по которой узел делит полупространство родителя
	 */
	void add (kdNode **pnode, float x, float y, T value, char dim=0) {

	    if (*pnode == NULL) {
	    	*pnode = new kdNode (x, y, dim, value);
	    	return;
	    }

	    kdNode *node = *pnode;
	    kdNode **adds = (
	    		(node->type == 0 && x < node->coord[0]) ||
	    		(node->type == 1 && y < node->coord[1]))
		    ? &node->child[0] : &node->child[1];

		add(adds, x, y, value, 1-dim);
	}

	/**
	 * Поиск ближайшего к указанным координатам узла среди потомков node.
	 *
	 * @return найденный узел либо NULL, если нет подходящего узла.
	 */
	kdNode * search (kdNode *node, float x, float y) {

	    if (!node || (!node->child[0] && !node->child[1]))
	    	return node;

	    kdNode *tr1, *tr2;
	    float point[2];
	    point[0] = x, point[1] = y;
	    int side = node->type;

		// ближайший узел с той стороны корня, где находится точка
		tr1 = search((point[side] < node->coord[side])
				? node->child[0] : node->child[1], x, y);

		float d = node->coord[side]-point[side];
		if (tr1 && kdDist(tr1, x, y) < d*d) {
			// Ближе быть не может
			return tr1;
		}

		// ближайший узел с другой стороны
		tr2 = search((point[side] < node->coord[side])
				? node->child[1] : node->child[0], x, y);

		// Поиск ближайшего узла
		tr1 = (!tr2 || (tr1 && kdDist(tr1, x, y) < kdDist(tr2, x, y)))
			? tr1 : tr2;

		return (!tr1 || (kdDist(node, x, y) < kdDist(tr1, x, y)))
			? node : tr1;
	}

};

}} // namespaces

#endif /* KDTREE_H */
