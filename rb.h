/*
 * rb.h
 *
 *  Created on: March 26, 2012
 *      Author: Edward
 */

#ifndef RB_H_
#define RB_H_

//#include <stdio.h>
//#include <queue>
#include <iostream>
#include "bst.h"

//using namespace std;
typedef int T;
enum Color{RED,BLACK};

class RBT;

class RBNode:public BTNode
{
	
    public:
		RBNode(): BTNode(), color(BLACK){}
    RBNode(const T & el, BTNode *p = NULL, BTNode *l = NULL, BTNode *r = NULL, Color c = RED):BTNode(el,p,l,r),color(c){}
    void display(std::ostream &os) const
    {
        os << key;
        if(color == RED) os << "r";
        else os << "b";
    }
    bool isNilLeft() const;
    bool isNilRight() const;
    bool isNilParent() const;
		Color color;
};




class RBT: public BST
{
	public:
		RBT();
		//Avoid calling virtual functions during construction or destruction
    virtual ~RBT();
		virtual void Insert(const T & el);
		virtual void Delete (BTNode * node);
    virtual bool isNil(BTNode *) const;
    static BTNode* Nil;
    private:
    virtual void setNil(BTNode *&);
    void Insert_Fixup(BTNode *);
    void Delete_Fixup(BTNode *);
    Color getColor(BTNode * ) const;
    void setColor(BTNode *, Color);
};




#endif /* BST_H_ */
