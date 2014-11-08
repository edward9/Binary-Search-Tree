#include "bst.h"

BST::BST()
{
	root = NULL;
}

BST::~BST()
{
   Clear();
}

void BST::Clear()
{
	Clear(root);
	setNil(root);
}

void BST::Clear(BTNode* & node)
{
	if (isNil(node))
		return;
	Clear(node->left);
	Clear(node->right);
	delete node;
}

void BST::Insert (const T & el)
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

	z = new BTNode(el, y);

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
}

bool BST::Delete (const T & el)
{
	BTNode * dnode = Search(el);
	if (dnode==NULL)
		return false;
	Delete(dnode);
	return true;
}


void BST::Delete (BTNode * node)
{
	BTNode * s;
	if (node->isNilLeft())
		_Transplant(node,node->right);
	else if (node->isNilRight())
		_Transplant(node,node->left);
	else
	{
		s = Minimum(node->right);
		if (s->parent != node)
		{
			_Transplant(s, s->right);
			s->right = node->right;
			(s->right)->parent = s;
		}
		_Transplant(node, s);
		s->left = node->left;
		(s->left)->parent = s;
	}
	delete node;
}

void BST::_Transplant(BTNode *a, BTNode *b)
{
	if (a->isNilParent())
		root = b;
	else if ( a == (a->parent)->left)
		(a->parent)->left = b;
	else
		(a->parent)->right = b;
	if (!(isNil(b)))
		b->parent = a->parent;

}

BTNode* BST::Root() const
{
	if(isNil(root))
		return NULL;
	return root;
}

bool BST::Empty() const
{
	return (isNil(root));
}

BTNode * BST::Search(const T & el) const
{
	BTNode *x = root;
	while ( (!(isNil(x))) && (el != x->key))
	{
		if (el < x->key)
			x = x->left;
		else
			x = x->right;
	}
	if (isNil(x))
		return NULL;
	return x;
}

BTNode * BST::Search(BTNode * node, const T & el) const
{
	if (isNil(node))
		return NULL;
	if (el == node->key)
		return node;
	if (el > node->key)
		return Search(node->right, el);
	else
		return Search(node->left, el);
}

T * BST::Minimum() const
{
	if (isNil(root))
		return NULL;
	BTNode *x = root;
	T *y;
	while (!(x->isNilLeft()))
	{
		x = x->left;
	}

	y = & (x->key);
	return y;
}

BTNode * BST::Minimum(BTNode * node) const
{
	if (node->isNilLeft())
		return node;
	else
		return Minimum(node->left);
}

T * BST::Maximum() const
{
	if (isNil(root))
		return NULL;
	BTNode *x = root;
	T *y;
	while (!(x->isNilRight()))
	{
		x = x->right;
	}
	y = & (x->key);
	return y;
}

BTNode * BST::Maximum(BTNode * node) const
{
	if (node->isNilRight())
		return node;
	else
		return Maximum(node->right);
}

BTNode * BST::Predecessor(BTNode * node) const
{
	BTNode *pnode;
	if (!(node->isNilLeft()))
		return Maximum(node->left);
	pnode = node->parent;
	while ( (!(isNil(pnode))) && (node== pnode->left) )
	{
		node = pnode;
		pnode = pnode->parent;
	}
	if (isNil(pnode))
		return NULL;
	return pnode;
}

BTNode * BST::Successor(BTNode * node) const
{
	BTNode *pnode;
	if (!(node->isNilRight()))
		return Minimum(node->right);
	pnode = node->parent;
	while ( !(isNil(pnode)) && (node== pnode->right) )
	{
		node = pnode;
		pnode = pnode->parent;
	}
	if (isNil(pnode))
		return NULL;
	return pnode;
}

int BST::Count() const
{
	return Count(root);
}

int BST::Count(BTNode * node) const
{
	if (isNil(node))
		return 0;
	return 1 + Count(node->left) + Count(node->right);
}

void BST::Inorder() const
{
	Inorder(root);
	std::cout<< std::endl;
}

void BST::Inorder(BTNode * node) const
{
	if (!(isNil(node)))
	{
		Inorder(node->left);
		node->display(std::cout);
		std::cout<<" ";
		Inorder(node->right);
	}

}

void BST::Preorder() const
{
	Preorder(root);
	std::cout<< std::endl;
}

void BST::Preorder(BTNode * node) const
{
	if (!(isNil(node)))
	{
		node->display(std::cout);
		std::cout<<" ";
		Preorder(node->left);
		Preorder(node->right);
	}
}

void BST::Postorder() const
{
	Postorder(root);
	std::cout<< std::endl;
}

void BST::Postorder(BTNode * node) const
{
	if (!(isNil(node)))
	{
		Postorder(node->left);
		Postorder(node->right);
		node->display(std::cout);
		std::cout<<" ";
		
	}
}

void BST::Breadth() const
{
	Breadth(root);
}

void BST::Breadth(BTNode * node) const
{
	if (isNil(node))
	{
		std::cout << endl;
		return;
	}
	std::queue<BTNode *> que;
	que.push(node);
	BTNode *c;
	while(!que.empty())
	{
		c = que.front();
		que.pop();
		if(!(isNil(c->left)))
		{
			que.push(c->left);
		}
		if(!(isNil(c->right)))
		{
			que.push(c->right);
		}
		c->display(std::cout);
		std::cout<<" ";

	}
	std::cout<<std::endl;
}

// functions below are added for RBT

void BST::RotLeft(BTNode * x)
{
    BTNode *y = x->right;
    x->right = y->left;

    if (!(y->isNilLeft()))
        y->left->parent=x;

    y->parent = x->parent;

    if (x->isNilParent()){
        root = y;
    }
    else if (x->parent->left == x){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;

}

void BST::RotRight(BTNode * x)
{
    BTNode *y = x->left;
    x->left = y->right;

    if (!(y->isNilRight()))
        y->right->parent=x;

    y->parent = x->parent;

    if (x->isNilParent()){
        root = y;
    }
    else if (x->parent->right == x){
        x->parent->right = y;
    }
    else{
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;

}


bool BST::isNil(BTNode * node) const
{
    return node == NULL;
}

void BST::setNil(BTNode * &node)
{
	node = NULL;
}
