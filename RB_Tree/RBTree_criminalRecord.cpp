#include <iostream>
using namespace std;

class Criminal; // the criminal class

class RB_Tree;
class Node{
friend class RB_Tree;
private:
    Node* left;
    Node* right;
    Node* p;
    Criminal* criminal;
    int minute;    // time

    bool color; // 0: red, 1: black
public:
    Node(int k, bool c=0, Criminal* cr=nullptr, Node* parent=nullptr, Node* l=nullptr, Node* r=nullptr){
        minute = k;
        color = c;
        p = parent;
        left = l;
        right = r;

        // node points to the criminal object
        criminal = cr;
    }
};
typedef struct Node Node;

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
    Node* y = x->right;
    x->right = y->left;
    y->left->p = x;
    y->p = x->p;
    if(x->p==T.nil) T.root = y;
    else if(x==x->p->left)  x->p->left = y;
    else    x->p->right = y;
    y->left = x;
    x->p = y;
    return;
}

void RB_Tree::_rightRotate(RB_Tree& T, Node* x){
    Node* y = x->left;
    x->left = y->right;
    y->right->p = x;
    y->p = x->p;
    if(x->p==T.nil) T.root = y;
    else if(x==x->p->left)  x->p->left = y;
    else    x->p->right = y;
    y->right = x;
    x->p = y;
    return;
}

void RB_Tree::Transplant(RB_Tree& T, Node* z, Node* y){
    if(z->p==T.nil) T.root = y;
    else if(z==z->p->left)  z->p->left = y;
    else    z->p->right = y;
    y->p = z->p;
}

void RB_Tree::Insert(RB_Tree& T, Node* z){
    Node* x = T.root;
    Node* y = T.nil;
    while(x!=T.nil){
        y = x;
        if(z->minute < x->minute) x = x->left;
        else    x = x->right;
    }
    z->p = y;
    if(y==T.nil)    T.root = z;
    else if(z->minute < y->minute)    y->left = z;
    else    y->right = z;
    // z is already set to red
    z->left = T.nil;
    z->right = T.nil;
    this->InsertFixup(T, z);
}

void RB_Tree::InsertFixup(RB_Tree& T, Node* z){
    while(z->p->color==0){  // color == RED
        if(z->p == z->p->p->left){
            Node* y = z->p->p->right;
            if(y->color == 0){
                z->p->p->color = 0;
                z->p->color = 1;
                y->color = 1;
                z = z->p->p;
            }
            else{
                if(z==z->p->right){  
                    z = z->p;
                    this->_leftRotate(T,z);
                }
                z->p->color = 1;
                z->p->p->color = 0;
                this->_rightRotate(T,z->p->p);
            }
        }
        else{
            Node* y = z->p->p->left;
            if(y->color == 0){
                z->p->p->color = 0;
                z->p->color = 1;
                y->color = 1;
                z = z->p->p;
            }
            else{
                if(z==z->p->left){
                    z = z->p;
                    this->_rightRotate(T,z);
                }
                z->p->color = 1;
                z->p->p->color = 0;
                this->_leftRotate(T,z->p->p);
            }
        }
    }
    T.root->color = 1;
}

void RB_Tree::Delete(RB_Tree& T, Node* z){
    Node* y = z;
    bool y_original_color = y->color;
    Node* x;
    if(z->left==T.nil){
        x = z->right;
        this->Transplant(T,z,x);
    }
    else if(z->right==T.nil){
        x = z->left;
        this->Transplant(T,z,x);
    }
    else{
        y = this->TreeMinimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if(y!=z->right){
            this->Transplant(T,y,x);
            y->right = z->right;
            y->right->p = y;
        }else{
            x->p = y;
        }
        this->Transplant(T,z,y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }
    
    if(y_original_color==1) this->DeleteFixup(T,x);
}


Node* RB_Tree::TreeMinimum(Node* r){
    Node* y = this->nil;
    while(r!=this->nil){
        y = r;
        r = r->left;
    }
    return y;
}

void RB_Tree::DeleteFixup(RB_Tree& T, Node* x){
    while(x!=T.root && x->color==1){
        if(x==x->p->left){
            Node* w = x->p->right;
            if(w->color==0){
                w->color = 1;
                x->p->color = 0;
                this->_leftRotate(T,x->p);
                w = x->right;
            }
            if(w->left->color==1 && w->right->color==1){
                w->color = 0;
                x = x->p;
            }
            else{
                if(w->right->color==1){
                    w->left->color = 1;
                    w->color = 0;
                    this->_rightRotate(T,w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                w->right->color = 1;
                x->p->color = 1;
                this->_leftRotate(T,x->p);
                x = T.root;
            }
        }
        else{
            Node* w = x->p->left;
            if(w->color==0){
                x->p->color = 0;
                w->color = 1;
                this->_rightRotate(T,x->p);
                w = x->left;
            }
            if(w->left->color==1 && w->right->color==1){
                w->color = 0;
                x = x->p;
            }
            else{
                if(w->left->color==1){
                    w->right->color = 1;
                    w->color = 0;
                    this->_leftRotate(T,w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                w->left->color = 1;
                x->p->color = 1;
                this->_rightRotate(T,x->p);
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

    if(r->left!=this->nil)  printInorder(r->left);
    cout << r->minute << ", ";
    if(r->right!=this->nil) printInorder(r->right);
}

void RB_Tree::printPreorder(){
    Node* r = this->root;
    this->printPreorder(r);
}

void RB_Tree::printPreorder(Node* r){
    if(r==this->nil)    return;
    cout << "(" << r->minute << ", " << ((r->color==0)? "RED":"BLACK") << "), ";
    if(r->left!=this->nil)  printPreorder(r->left);
    if(r->right!=this->nil) printPreorder(r->right);
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