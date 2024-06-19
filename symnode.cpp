/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line




SymNode::SymNode(){
	key = "";
	height = 0;
	address = -1;
	par = nullptr;
	left = nullptr;
	right = nullptr;
}

SymNode::SymNode(string k){
	key = k;
	height = 0 ;
	address = -1;
	par = nullptr;
	left = nullptr ;
	right = nullptr; 
}

int height(SymNode* n) {
    if (n==NULL) {
        return -1;
    }
    else {
        int lheight = height(n->left);
        int rheight = height(n->right);
        if (lheight>rheight) {
            return lheight+1;
        }
        return rheight+1;
    }
}

void update_height(SymNode* n) {
    n->height = height(n);
}

SymNode* rightRotate(SymNode* x) {
    SymNode* y = x->left;
    SymNode* T2 = y->right;
    y->right = x;
    x->left  = T2;
    update_height(x);
    update_height(y);
    return y;
}

SymNode* leftRotate(SymNode* x) {
    SymNode* y = x->right;
    SymNode* T2= y->left;
    y->left = x;
    x->right = T2;
    update_height(x);
    update_height(y);
    return y;
}

SymNode* SymNode::LeftLeftRotation(){
    return leftRotate(this);
}

SymNode* SymNode::RightRightRotation(){
    return rightRotate(this);
}

SymNode* SymNode::LeftRightRotation(){
    this->left = leftRotate(this->left);
    return rightRotate(this);
}

SymNode* SymNode::RightLeftRotation(){
    this->right = rightRotate(this->right);
    return leftRotate(this);
}

SymNode::~SymNode(){

}