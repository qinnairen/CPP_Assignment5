/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    type = "";
    id = "";
    num = 0;

}

ExprTreeNode::ExprTreeNode(string t,int v){
    if (t == "VAR") {
        id = t;
    }
    else {
        type = t;
        num = v;
        id = to_string(v);
    }
}

ExprTreeNode::~ExprTreeNode(){
    delete left;
    delete right; 
}

