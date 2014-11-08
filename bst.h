/*
 * bst.h
 *
 *  Created on: Jan 26, 2012
 *      Author: tashi
 */

#ifndef BST_H_
#define BST_H_

#include <stdio.h>
#include <queue>
#include <iostream>
using namespace std;

typedef int T;

class BTNode {
 public:
 BTNode() : key(0), parent(NULL), left(NULL), right(NULL) {}
 BTNode(const T & e1, BTNode *p = NULL, BTNode *l = NULL, BTNode *r = NULL) :
  key(e1), parent(p), left(l), right(r) {}
  T key;
  BTNode * parent;
  BTNode * left;
  BTNode * right;

  virtual void display(std::ostream &os) const
  {
      os << key;
  }
  virtual bool isNilLeft() const
  {
      return left == NULL;
  }
  virtual bool isNilRight() const
  {
      return right == NULL;
  }
  virtual bool isNilParent() const
  {
      return parent == NULL;
  }
};




class BST {
 public:
 BST();
  virtual ~BST(); // deallocates BST
  void Clear(); // calls Clear(root)
  void Clear(BTNode * &); // Clears the subtree of node
  virtual void Insert (const T & el); // inserts a node with key el
  bool Delete (const T & el); // deletes a node with key el
  virtual void Delete (BTNode * node); // deletes a specific node
  BTNode * Root() const; // returns root node
  bool Empty() const; // returns true iff an empty tree
  BTNode * Search(const T & el) const; // returns a node with key el
  BTNode * Search(BTNode *, const T &) const; /* search recurssively and returns a node with key el*/
  T * Minimum() const; // returns minimum key in tree
  BTNode * Minimum(BTNode *) const; // returns a node with minimum key
  T * Maximum() const; // returns maximum key in tree
  BTNode * Maximum(BTNode *) const; // returns a node with maximum key
  BTNode * Predecessor(BTNode *) const; // return a predecessor node
  BTNode * Successor(BTNode *) const; // return a successor node
  int Count() const; // calls Count(root)
  int Count(BTNode *) const; // returns number of descedants
  void Inorder() const; // calls Inorder(root)
  void Inorder(BTNode *) const; // prints inorder
  void Preorder() const; // calls Preorder(root)
  void Preorder(BTNode *) const; // prints preorder
  void Postorder() const; // calls Postorder(root)
  void Postorder(BTNode *) const; // prints postorder
  void Breadth() const; // calls Breadth(root)
  void Breadth(BTNode *) const; // prints breadth-search research
  void RotLeft(BTNode *);
  void RotRight(BTNode *);
  virtual bool isNil(BTNode *) const;
  virtual void setNil(BTNode *&);
  
  BTNode * root; // root of a tree
  void _Transplant(BTNode * a, BTNode * b); // used for delete


};



#endif /* BST_H_ */
