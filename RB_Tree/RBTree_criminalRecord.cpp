#include <iostream>
#include "../CriminalSystem/CriminalSystem.h"

using namespace CriminalSystem;


class RB_Tree;
// class Node{
// friend class RB_Tree;
// private:
//     Node* left;
//     Node* right;
//     Node* p;
//     Criminal* criminal;
//     int minute;    // time

//     bool color; // 0: red, 1: black
// public:
//     Node(int k, bool c=0, Criminal* cr=nullptr, Node* parent=nullptr, Node* l=nullptr, Node* r=nullptr){
//         minute = k;
//         color = c;
//         p = parent;
//         left = l;
//         right = r;

//         // node points to the criminal object
//         criminal = cr;
//     }
// };
// typedef struct Node Node;

typedef CrimeRecord Node;

class RB_Tree{
    Node* root;
    Node* nil;
    void _leftRotate(RB_Tree& T, Node* x);
    void _rightRotate(RB_Tree& T, Node* x);
    void Transplant(RB_Tree& T, Node* z, Node* y);
    void InsertFixup(RB_Tree& T, Node* x);
    void DeleteFixup(RB_Tree& T, Node* x);
    Node* TreeMinimum(Node* r);
    void printInorder(Node* r);
    void printPreorder(Node* r);
public:
    RB_Tree(void){
        nil = new Node(-1,1,nullptr,nullptr,nil,nil);
        root = nil;
    }
    void Insert(RB_Tree& T, Node* z);
    void Delete(RB_Tree& T, Node* z);
    void printInorder();
    void printPreorder();

};

void RB_Tree::_leftRotate(RB_Tree& T, Node* x){
    Node* y = x->getRight();
    x->setRight(y->getLeft());
    y->getLeft()->setParent(x);//y->left->p = x;
    y->setParent(x->getParent());//y->p = x->p;
    if(x->getParent()==T.nil)   T.root = y;//if(x->p==T.nil) T.root = y;
    else if(x==x->getParent()->getLeft()) x->getParent()->setLeft(y);//else if(x==x->p->left)  x->p->left = y;
    else    x->getParent()->setRight(y);    //else    x->p->right = y;
    y->setLeft(x);//y->left = x;
    x->setParent(y);//x->p = y;
    return;
}

void RB_Tree::_rightRotate(RB_Tree& T, Node* x){
    Node* y = x->getLeft();//Node* y = x->left;
    x->setLeft(y->getRight());//x->left = y->right;
    y->getRight()->setParent(x);//y->right->p = x;
    y->setParent(x->getParent());//y->p = x->p;
    if(x->getParent()==T.nil)   T.root = y;//if(x->p==T.nil) T.root = y;
    else if(x==x->getParent()->getLeft())   x->getParent()->setLeft(y);//else if(x==x->p->left)  x->p->left = y;
    else    x->getParent()->setRight(y);//else    x->p->right = y;
    y->setRight(x);//y->right = x;
    x->setParent(y);//x->p = y;
    return;
}

void RB_Tree::Transplant(RB_Tree& T, Node* z, Node* y){
    if(z->getParent()==T.nil)   T.root = y;//if(z->p==T.nil) T.root = y;
    else if(z==z->getParent()->getLeft())   z->getParent()->setLeft(y);//else if(z==z->p->left)  z->p->left = y;
    else    z->getParent()->setRight(y);//else    z->p->right = y;
    y->setParent(z->getParent());//y->p = z->p;
}

void RB_Tree::Insert(RB_Tree& T, Node* z){
    Node* x = T.root;
    Node* y = T.nil;
    while(x!=T.nil){
        y = x;
        if(z->getTime() < z->getTime()) x = x->getLeft();//if(z->minute < x->minute) x = x->left;
        else    x = x->getRight();//else    x = x->right;
    }
    z->setParent(y);//z->p = y;
    if(y==T.nil)    T.root = z;
    else if(z->getTime() < y->getTime())    y->setLeft(z);//else if(z->minute < y->minute)    y->left = z;
    else    y->setRight(z);//else    y->right = z;
    // z is already set to red
    z->setLeft(T.nil);//z->left = T.nil;
    z->setRight(T.nil);//z->right = T.nil;
    this->InsertFixup(T, z);
}

void RB_Tree::InsertFixup(RB_Tree& T, Node* z){
    while(z->getParent()->getColor()==0){//while(z->p->color==0){  // color == RED
        if(z->getParent()==z->getParent()->getParent()->getParent()->getLeft()){//if(z->p == z->p->p->left){
            Node* y = z->getParent()->getParent()->getRight();//Node* y = z->p->p->right;
            if(y->getColor() == 0){//if(y->color == 0){
                z->getParent()->getParent()->setColor(0);//z->p->p->color = 0;
                z->getParent()->setColor(1);//z->p->color = 1;
                y->setColor(1);//y->color = 1;
                z = z->getParent()->getParent();//z = z->p->p;
            }
            else{
                if(z==z->getParent()->getRight()){//if(z==z->p->right){  
                    z = z->getParent();//z = z->p;
                    this->_leftRotate(T,z);
                }
                z->getParent()->setColor(1);//z->p->color = 1;
                z->getParent()->getParent()->setColor(0);//z->p->p->color = 0;
                this->_rightRotate(T,z->getParent()->getParent());//this->_rightRotate(T,z->p->p);
            }
        }
        else{
            Node* y = z->getParent()->getParent()->getLeft();//Node* y = z->p->p->left;
            if(y->getColor() == 0){//if(y->color == 0){
                z->getParent()->getParent()->setColor(0);//z->p->p->color = 0;
                z->getParent()->setColor(1);//z->p->color = 1;
                y->setColor(1);//y->color = 1;
                z = z->getParent()->getParent();//z = z->p->p;
            }
            else{
                if(z==z->getParent()->getLeft()){//if(z==z->p->left){
                    z = z->getParent();//z = z->p;
                    this->_rightRotate(T,z);
                }
                z->getParent()->setColor(1);//z->p->color = 1;
                z->getParent()->getParent()->setColor(0);//z->p->p->color = 0;
                this->_leftRotate(T,z->getParent()->getParent());//this->_leftRotate(T,z->p->p);
            }
        }
    }
    T.root->setColor(1);//T.root->color = 1;
}

void RB_Tree::Delete(RB_Tree& T, Node* z){
    Node* y = z;
    bool y_original_color = y->getColor();//bool y_original_color = y->color;
    Node* x;
    if(z->getLeft() == T.nil){//if(z->left==T.nil){
        x = z->getRight();//x = z->right;
        this->Transplant(T,z,x);
    }
    else if(z->getRight() == T.nil){//else if(z->right==T.nil){
        x = z->getLeft();//x = z->left;
        this->Transplant(T,z,x);
    }
    else{
        y = this->TreeMinimum(z->getRight());//y = this->TreeMinimum(z->right);
        y_original_color = y->getColor();//y_original_color = y->color;
        x = y->getRight();//x = y->right;
        if(y!=z->getRight()){//if(y!=z->right){
            this->Transplant(T,y,x);
            y->setRight(z->getRight());//y->right = z->right;
            y->getRight()->setParent(y);//y->right->p = y;
        }else{
            x->setParent(y);//x->p = y;
        }
        this->Transplant(T,z,y);
        y->setLeft(z->getLeft());//y->left = z->left;
        y->getLeft()->setParent(y);//y->left->p = y;
        y->setColor(z->getColor());//y->color = z->color;
    }
    
    if(y_original_color==1) this->DeleteFixup(T,x);
}


Node* RB_Tree::TreeMinimum(Node* r){
    Node* y = this->nil;
    while(r!=this->nil){
        y = r;
        r = r->getLeft();//r = r->left;
    }
    return y;
}

void RB_Tree::DeleteFixup(RB_Tree& T, Node* x){
    while(x!=T.root && x->getColor() == 1){//while(x!=T.root && x->color==1){
        if(x == x->getParent()->getLeft()){//if(x==x->p->left){
            Node* w = x->getParent()->getRight();//Node* w = x->p->right;
            if(w->getColor() == 0){//if(w->color==0){
                w->setColor(1);//w->color = 1;
                x->getParent()->setColor(0);//x->p->color = 0;
                this->_leftRotate(T,x->getParent());//this->_leftRotate(T,x->p);
                w = x->getRight();//w = x->right;
            }
            if(w->getLeft()->getColor() == 1 && w->getRight()->getColor() == 1){//if(w->left->color==1 && w->right->color==1){
                w->setColor(0);//w->color = 0;
                x = x->getParent();//x = x->p;
            }
            else{
                if(w->getRight()->getColor() == 1){//if(w->right->color==1){
                    w->getLeft()->setColor(1);//w->left->color = 1;
                    w->setColor(0);//w->color = 0;
                    this->_rightRotate(T,w);
                    w = w->getParent()->getRight();//w = x->p->right;
                }
                w->setColor(x->getParent()->getColor());//w->color = x->p->color;
                w->getRight()->setColor(1);//w->right->color = 1;
                x->getParent()->setColor(1);//x->p->color = 1;
                this->_leftRotate(T,x->getParent());//this->_leftRotate(T,x->p);
                x = T.root;
            }
        }
        else{
            Node* w = x->getParent()->getLeft();//Node* w = x->p->left;
            if(w->getColor() == 0){//if(w->color==0){
                x->getParent()->setColor(0);//x->p->color = 0;
                w->setColor(1);//w->color = 1;
                this->_rightRotate(T,x->getParent());//this->_rightRotate(T,x->p);
                w = x->getLeft();//w = x->left;
            }
            if(w->getLeft()->getColor() == 1 && w->getRight()->getColor() == 1){//if(w->left->color==1 && w->right->color==1){
                w->setColor(0);//w->color = 0;
                x = x->getParent();//x = x->p;
            }
            else{
                if(w->getLeft()->getColor() == 1){//if(w->left->color==1){
                    w->getRight()->setColor(1);//w->right->color = 1;
                    w->setColor(0);//w->color = 0;
                    this->_leftRotate(T,w);
                    w = x->getParent()->getLeft();//w = x->p->left;
                }
                w->setColor(x->getParent()->getColor());//w->color = x->p->color;
                w->getLeft()->setColor(1);//w->left->color = 1;
                x->getParent()->setColor(1);//x->p->color = 1;
                this->_rightRotate(T,x->getParent());//this->_rightRotate(T,x->p);
                x = T.root;
            }
        }
    }
}

void RB_Tree::printInorder(){
    Node* r = this->root;
    this->printInorder(r);
}

void RB_Tree::printInorder(Node* r){
    if(r==this->nil)    return;

    if(r->getLeft() != this->nil)   printInorder(r->getLeft());//if(r->left!=this->nil)  printInorder(r->left);
    std::cout << r->getTime() << ", ";//cout << r->minute << ", ";
    if(r->getRight() != this->nil)  printInorder(r->getRight());//if(r->right!=this->nil) printInorder(r->right);
}

void RB_Tree::printPreorder(){
    Node* r = this->root;
    this->printPreorder(r);
}

void RB_Tree::printPreorder(Node* r){
    if(r==this->nil)    return;
    cout << "(" << r->getTime() << ", " << ((r->getColor()==0)? "RED":"BLACK") << "), ";//cout << "(" << r->minute << ", " << ((r->color==0)? "RED":"BLACK") << "), ";
    if(r->getLeft() != this->nil)   printPreorder(r->getLeft());//if(r->left!=this->nil)  printPreorder(r->left);
    if(r->getRight() != this->nil)  printPreorder(r->getRight());//if(r->right!=this->nil) printPreorder(r->right);
}

int main(){
    RB_Tree tree;
    for(int i=0;i<1000;i++){
        tree.Insert(tree,new Node(i));
        //cout << "----------------------------\n\n\n";
    }
    tree.printPreorder();
    return 0;
}