#include <iostream>
#include "CriminalSystem.h"

using namespace CriminalSystem;
typedef CrimeRecord Node;

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
    void countRB(Node* r,int& red, int& black);
    void display(int* months);
    vector<Node*> Interval(Node* node, int time1, int time2);
    
public:
    RB_Tree(void){
        nil = new Node(1,nil,nil,nil);
        root = nil;
    }
    void Insert(RB_Tree& T, Node* z);
    void Delete(RB_Tree& T, Node* z);
    void printInorder();
    void printPreorder();
    void countRB();     // for check use
    void countLongestPath();    // for check use
    void countShortestPath();   // for check use
    vector<Node*> SearchTime(int year, int month, int day, int hour, int minute);
    vector<Node*> SearchInterval(int year1, int month1, int day1, int hour1, int minute1, int year2, int month2, int day2, int hour2, int minute2);
    // vector<Node*> SearchTimeType();
    // vector<Node*> SearchIntervalType();
    // vector<Node*> SearchCriminal();
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
    cout << "(\'" << (r->getRealTime()).at(0) << "/" << (r->getRealTime()).at(1) << "/" << (r->getRealTime()).at(2) << "\', " << ((r->getColor()==0)? "RED":"BLACK") << "), ";//cout << "(" << r->minute << ", " << ((r->color==0)? "RED":"BLACK") << "), ";
    if(r->getLeft() != this->nil)   printPreorder(r->getLeft());//if(r->left!=this->nil)  printPreorder(r->left);
    if(r->getRight() != this->nil)  printPreorder(r->getRight());//if(r->right!=this->nil) printPreorder(r->right);
}

void RB_Tree::countRB(){
    int R=0, B=0;
    countRB(this->root, R, B);
    cout << "The number of Red nodes  : " << R << endl;
    cout << "The number of Black nodes: " << B << endl;
    cout << "R / B = " << (double) R / B*1.0 << endl;
}

void RB_Tree::countRB(Node* r, int& red, int& black){
    if(r==this->nil)    return;
    if(r->getColor()==0)    red++;
    else    black++;
    countRB(r->getLeft(),red,black);
    countRB(r->getRight(),red,black);
}

void RB_Tree::countLongestPath(){
    int length = 0;
    Node* cur = this->root;
    while(cur!=this->nil){
        length++;
        cur = cur->getRight();
    }
    cout << "The longest path has length: " << length << endl;
}

void RB_Tree::countShortestPath(){
    int length = 0;
    Node* cur = this->root;
    while(cur!=this->nil){
        length++;
        cur = cur->getLeft();
    }
    cout << "The shortest path has length: " << length << endl;
}

void RB_Tree::display(int* months){
    for(int i=2;i<=12;i++){
        months[i]+=months[i-1];
    }
}

vector<Node*> RB_Tree::SearchTime(int year, int month, int day, int hour, int minute){
    int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    display(months);
    int time = year*525600+(months[month-1]+day)*1440+hour*60+minute;

    vector<Node*> ans;
    Node* cur = root;
    while(cur != nil){
        if(time < cur->getTime()){
            cur = cur->getLeft();
        }
        else{
            if(cur->getTime() == time){
                ans.push_back(cur);
            }
            cur = cur->getRight();
        }
    }
    return ans;
}

vector<Node*> RB_Tree::Interval(Node* node, int time1, int time2){
    vector<Node*> result;
    if (node == nil) return result;

    if (node->getTime() >= time1) {
        vector<Node*> leftNodes = Interval(node->getLeft(), time1, time2);
        result.insert(result.end(), leftNodes.begin(), leftNodes.end());
    }

    if (node->getTime() >= time1 && node->getTime() <= time2) {
        result.push_back(node);
    }

    if (node->getTime() <= time2) {
        vector<Node*> rightNodes = Interval(node->getRight(), time1, time2);
        result.insert(result.end(), rightNodes.begin(), rightNodes.end());
    }

    return result;
}

vector<Node*> RB_Tree::SearchInterval(int year1, int month1, int day1, int hour1, int minute1, int year2, int month2, int day2, int hour2, int minute2){
    int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    display(months);
    int time1 = year1*525600+(months[month1-1]+day1)*1440+hour1*60+minute1;
    int time2 = year2*525600+(months[month2-1]+day2)*1440+hour2*60+minute2;
    vector<Node*> ans;
    Node* cur = root;

    if(cur != nil){
        if(cur->getTime() < time1){
            ans = Interval(cur->getRight(), time1, time2);
        }
        else if (cur->getTime() > time2){
            ans = Interval(cur->getLeft(), time1, time2);
        } 
        else{
            vector<Node*> left = Interval(cur->getLeft(), time1, time2);
            vector<Node*> right = Interval(cur->getRight(), time1, time2);

            ans.insert(ans.end(), left.begin(), left.end());
            ans.push_back(cur);
            ans.insert(ans.end(), right.begin(), right.end());
        }
    }
    return ans;
}



int main(){
    RB_Tree tree;
    for(int y=2000;y<2010;y++){
        for(int m=1;m<3;m++){
            for(int d=1;d<3;d++){
                Criminal *c = new Criminal("H12344","2000/5/9","Male","good downtown ok_street","David");
                CrimeRecord *record=new CrimeRecord("kill","Kill a person",y,m,d,0,0,c);
                tree.Insert(tree,record);
            }
        }
        //cout << "----------------------------\n\n\n";
    }
    tree.printPreorder();
    cout << endl;
    tree.countRB();
    tree.countLongestPath();
    tree.countShortestPath();
    vector<Node*> ans;
    ans = tree.SearchTime(2000,1,1,0,0);
    ans = tree.SearchInterval(2000,1,1,0,0,2009,2,2,0,0);
    for(int i=0; i<ans.size(); i++){
        ans[i]->getCriminal()->outputAllinfo();
        cout << *ans[i] << endl;
    }
    cout << ans.size() << endl;
    
    


    return 0;
}