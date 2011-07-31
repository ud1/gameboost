#include "Atlas.h"

namespace gb
{
	namespace base
	{

		bool Atlas::insert(Rectangle &rc)
		{
			Node *node = insert(root, rc);
			
			if (!node && resizeFunc)
			{
				Node *new_root, *child;
				if (root->rc.width <= root->rc.height)
				{
					if (resizeFunc(2*root->rc.width, root->rc.height, user_data))
					{
						if (!root->child[0])
						{
							root->rc.width *= 2;
							return insert(rc);
						}
						
						new_root = new Node;
						new_root->rc.init(0, 0, 2*root->rc.width, root->rc.height);
						
						if (root->child[1]->has_image || root->child[1]->rc.top)
						{
							child = new Node;
							child->rc.init(root->rc.width, 0, root->rc.width, root->rc.height);
						}
						else
						{
							child = root->child[1];
							root = root->child[0];
							child->rc.init(root->rc.width, 0, new_root->rc.width - root->rc.width, new_root->rc.height);
						}
					}
					else return false;
				}
				else
				{
					if (resizeFunc(root->rc.width, 2*root->rc.height, user_data))
					{
						if (!root->child[0])
						{
							root->rc.height *= 2;
							return insert(rc);
						}
						
						new_root = new Node;
						new_root->rc.init(0, 0, root->rc.width, 2*root->rc.height);
						
						if (root->child[1]->has_image || root->child[1]->rc.left)
						{
							child = new Node;
							child->rc.init(0, root->rc.height, root->rc.width, root->rc.height);
						}
						else
						{
							child = root->child[1];
							root = root->child[0];
							child->rc.init(0, root->rc.height, new_root->rc.width, new_root->rc.height - root->rc.height);
						}
					}
					else return false;
				}
				
				new_root->child[0] = root;
				new_root->child[1] = child;
				
				root = new_root;
				
				return insert(rc);
			}
			
			if (node)
			{
				node->has_image = true;
				rc.left = node->rc.left;
				rc.top = node->rc.top;
				return true;
			}
			
			return false;
		}
		
		Atlas::Node *Atlas::insert(Atlas::Node *node, Rectangle &rc)
		{
			if (node->child[0])
			{ // we're not a leaf
				Node *new_node = insert(node->child[0], rc);
				if (new_node != NULL)
					return new_node;
				return insert(node->child[1], rc);
			}
			else
			{
				if (node->has_image)
					return NULL;
				if (node->rc.width < rc.width || node->rc.height < rc.height)
					return NULL;
				if (node->rc.width == rc.width && node->rc.height == rc.height)
					return node;
				
				node->child[0] = new Node;
				node->child[1] = new Node;

				int dw = node->rc.width - rc.width;
				int dh = node->rc.height - rc.height;

				if (dw > dh)
				{
					//	|------------|
					//	|     |      |
					//	|  rc |      |
					//	|     |      |
					//	|-----|      |
					//	|     |      |
					//	|------------|
					node->child[0]->rc.init(
						node->rc.left, node->rc.top, 
						rc.width, node->rc.height);
					node->child[1]->rc.init(
						node->rc.left + rc.width, node->rc.top,
						dw, node->rc.height);
				}
				else
				{
					//	|-----------|
					//	|  rc |     |
					//	|     |     |
					//	|-----|-----|
					//	|           |
					//	|           |
					//	|-----------|
					node->child[0]->rc.init(
						node->rc.left, node->rc.top,
						node->rc.width, rc.height);
					node->child[1]->rc.init(
						node->rc.left, node->rc.top + rc.height,
						node->rc.width, dh);
				}
				return insert(node->child[0], rc);
			}
		}
		
	}
}