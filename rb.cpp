#include "rb.h"

BTNode* RBT::Nil;

bool RBNode::isNilLeft() const
{
	return left == RBT::Nil;
}
bool RBNode::isNilRight() const
{
	return right == RBT::Nil;
}
bool RBNode::isNilParent() const
{
	return parent == RBT::Nil;
}


RBT::RBT()
{
	Nil = new RBNode();
	root = Nil;
}

RBT::~RBT()
{
	Clear();
}

void RBT::Insert(const T & el)
{	
	BTNode* x = root;
	BTNode* y;
	BTNode* z;
	setNil(y);
	while(!(isNil(x)))
	{
		y = x;

		if (el < x->key)
		{
			x = x->left;
		}
		else if(el > x->key)
		{
			x = x->right;
		}
		else
			return;

	}
	
	z = new RBNode(el, y);

	if (isNil(y))
	{
		root = z;
	}
	else if (el < y->key)
	{
		y->left = z;
	}
	else
	{
		y->right = z;
	}
	setNil(z->left);
	setNil(z->right);
	setColor(z,RED);
	Insert_Fixup(z);
}

void RBT::Insert_Fixup(BTNode * z)
{
	BTNode *y;
	while( getColor(z->parent) == RED)
	{
		if(z->parent == z->parent->parent->left)
		{
			y = z->parent->parent->right;
			if (getColor(y) == RED)
			{
				setColor(z->parent,BLACK);
				setColor(y,BLACK);
				setColor(z->parent->parent, RED);
				z = z->parent->parent;
			}
			else if(z == z->parent->right)
			{
				z = z->parent;
				RotLeft(z);
				setColor(z->parent, BLACK);
				setColor(z->parent->parent, RED);
				RotRight(z->parent->parent);
			}
			else
			{
				setColor(z->parent, BLACK);
				setColor(z->parent->parent, RED);
				RotRight(z->parent->parent);
			}
		}
		else
		{
			y = z->parent->parent->left;
			if (getColor(y) == RED)
			{
				setColor(z->parent,BLACK);
				setColor(y,BLACK);
				setColor(z->parent->parent, RED);
				z = z->parent->parent;
			}
			else if(z == z->parent->left)
			{
				z = z->parent;
				RotRight(z);
				setColor(z->parent, BLACK);
				setColor(z->parent->parent, RED);
				RotLeft(z->parent->parent);
			}
			else
			{
				setColor(z->parent, BLACK);
				setColor(z->parent->parent, RED);
				RotLeft(z->parent->parent);
			}
		}
	}
	setColor(root,BLACK);
}


void RBT::Delete(BTNode * node)
{
	BTNode *x;
	BTNode * y = node;
	Color y_original_color = getColor(y);
	if (node->isNilLeft())
	{
		x = node->right;
		_Transplant(node, node->right);		
		(node->right)->parent = node->parent;
	}
	else if(node->isNilRight())
	{
		x = node->left;
		_Transplant(node, node->left);
		(node->left)->parent = node->parent;
	}
	else
	{
		y = Minimum(node->right);
		y_original_color = getColor(y);
		x = y->right;
		if(y->parent == node)
		{
			x->parent = y;
		}
		else
		{
			_Transplant(y, y->right);
			(y->right)->parent = y->parent;
			y->right = node->right;
			(y->right)->parent = y;
		}
		_Transplant(node, y);
		y->parent = node->parent;
		y->left = node->left;
		(y->left)->parent = y;
		setColor(y, getColor(node));
	}
	if (y_original_color == BLACK)
	{
		Delete_Fixup(x);
	}
}

void RBT::Delete_Fixup(BTNode * x)
{

	BTNode *w;
	while(x!=root and getColor(x) == BLACK)
	{
		if (x == (x->parent)->left)
		{
			w = (x->parent)->right;
			if(getColor(w) == RED)
			{
				//case 1
				setColor(w,BLACK);
				setColor(x->parent, RED);
				RotLeft(x->parent);
				w = (x->parent)->right;
			}
			if(getColor(w->left) == BLACK and getColor(w->right) == BLACK)
			{
				//case 2
				setColor(w, RED);
				x = x->parent;
			}
			else if(getColor(w->right) == BLACK)
			{
				//case 3
				setColor(w->left,BLACK);
				setColor(w, RED);
				RotRight(w);
				w = (x->parent)->right;
				//case 4
				setColor(w, getColor(x->parent));
				setColor(x->parent, BLACK);
				setColor(w->right, BLACK);
				RotLeft(x->parent);
				x = root;
			}
			else //case4
			{
				setColor(w, getColor(x->parent));
				setColor(x->parent, BLACK);
				setColor(w->right, BLACK);
				RotLeft(x->parent);
				x = root;
			}
		}
		else
		{
			w = (x->parent)->left;
			if(getColor(w) == RED)
			{
				//case 1
				setColor(w,BLACK);
				setColor(x->parent, RED);
				RotRight(x->parent);
				w = (x->parent)->left;
			}
			if(getColor(w->right) == BLACK and getColor(w->left) == BLACK)
			{
				//case 2
				setColor(w, RED);
				x = x->parent;
			}
			else if(getColor(w->left) == BLACK)
			{
				//case 3
				setColor(w->right,BLACK);
				setColor(w, RED);
				RotLeft(w);
				w = (x->parent)->left;
				//case 4
				setColor(w, getColor(x->parent));
				setColor(x->parent, BLACK);
				setColor(w->left, BLACK);
				RotRight(x->parent);
				x = root;
			}
			else //case4
			{
				setColor(w, getColor(x->parent));
				setColor(x->parent, BLACK);
				setColor(w->left, BLACK);
				RotRight(x->parent);
				x = root;
			}
		}
	}
	setColor(x, BLACK);
}

bool RBT::isNil(BTNode * node) const
{
	return node == Nil;
}

void RBT::setNil(BTNode * &node)
{
	node = Nil;
}

Color RBT::getColor(BTNode * node) const
{
	return ((RBNode*)node)->color;
}
void RBT::setColor(BTNode * node, Color c)
{
	((RBNode *)node)->color = c;
}
