/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line


SymbolTable::SymbolTable(){
	root = nullptr;
	size = 0;
}



SymNode* minValue(SymNode* root) {
        if (root==nullptr) {
            return nullptr;
        }
        SymNode* ptr = root;
        SymNode* parent = nullptr;
        while (ptr!=nullptr) {
            parent = ptr;
            ptr=ptr->left;
        } 

        return parent ; 
    }

SymNode* inOrderSuccessor(SymNode* n) {
    SymNode* i = minValue(n->right);
    return i;
}

int height1(SymNode* n) {
        if (n==nullptr) {
            return -1;
        }
        else {
            int lheight = height1(n->left);
            int rheight = height1(n->right);
            if (lheight>rheight) {
                return lheight+1;
            }
            return rheight+1;
        }
    }


int balanceFactor(SymNode* n) {
        if (n==nullptr) {
            return -1;
        }
        return (height1(n->left)-height1(n->right));
    }

SymNode* rotation(SymNode* root, string k) {
    int bf = balanceFactor(root);
    if (bf > 1 && root->left->key > k ) {
        root = root->RightRightRotation();
    } else if (bf < -1 && root->right->key <= k) {
        root = root->LeftLeftRotation();
    } else if (bf > 1 && k >= root->left->key) {
        root = root->LeftRightRotation();
    } else if (bf < -1 && k < root->right->key) {
        root = root->RightLeftRotation();
    }
    return root; 
}
int get_balance(SymNode* node) {
    int leftH = 0, rightH = 0;
    if (node->left) {
        leftH = node->left->height;
    }
    if (node->right) {
        rightH = node->right->height;
    }
    return (leftH - rightH);
}

SymNode* insertHelper(SymNode* root, SymNode* target) {
    if (target==nullptr) {
         return nullptr;
    }
    if (root==nullptr) {
        root = target ;
        root = rotation(root, target->key);
        return root;
    }
    else if (target->key >= root->key) {
        root->right = insertHelper(root->right, target);
        root = rotation(root, target->key);
        return root;
    }
    else if (target->key < root->key) {
        root->left = insertHelper(root->left, target);
        root = rotation(root, target->key);
        return root;
    }
}

void SymbolTable::insert(string k){
	SymNode* target = new SymNode(k);
    root = insertHelper(root, target);
    size++ ;
    return;
}

void balanceTree(SymNode* &root) {
    if (root == nullptr) {
        return;
    }
    int bf = balanceFactor(root);
    if (bf > 1) {
        if (balanceFactor(root->left) < 0) {
            root->left->RightRightRotation();
        }
        root->LeftLeftRotation();
    } else if (bf < -1) {
        if (balanceFactor(root->right) > 0) {
            root->right->LeftLeftRotation();
        }
        root->RightRightRotation();
    }
}

SymNode* least(SymNode* node) {
	SymNode* ptr = node;
	while (ptr->left != nullptr) {
		ptr = ptr->left; 
	}
    return ptr; 
}
SymNode* predecessor(SymNode* node) {
	SymNode* current = node;
	while (current->left != nullptr) {
		current = current->left; 
	}
    return current; 
}
 
SymNode* deleteHelper(SymNode* root, string  k) {
	if (root==nullptr) {
		return nullptr;
	}
	if (k < root->key) {
		root->left = deleteHelper(root->left, k); 
	} 
    
    else if (k > root->key) {
		root->right = deleteHelper(root->right, k); 
	} 
    
    else {
		if ((root->left == nullptr) || (root->right == nullptr)) { 
            SymNode* temp = new SymNode();
            if (root->left!=nullptr) {
                temp = root->left;
            }
            else {
                temp = root->right ; 
            }
        if (temp == nullptr) {
        	temp = root;
        	root = nullptr;
		} 
        else {
				root = temp;
			}
        } 
        else {
        	//cout<<"both children"<<endl;
        	SymNode* temp = least(root->right); 
        	root->key = temp->key;
        	root->address = temp->address;
        	root->right = deleteHelper(root->right, temp->key); 
		}
	}
    if (root == nullptr) {
    	return root;
	}
    balanceTree(root);
    return root; 
}

void SymbolTable::remove(string k){
	//cout<<"entered remove"<<endl;
    root = deleteHelper(root, k);
    //cout<<"delete helper done"<<endl;
	size--;
}

int searchHelper(SymNode* root, string k) {
	if (!root) {
		return -2;
	}
	if (root->key == k) {
		return root->address;
	} else {
		if (root->key < k) {
			return searchHelper(root->right, k);
		} else {
			return searchHelper(root->left, k);
		}
	}
}

int SymbolTable::search(string k) {
	int v = searchHelper(root,k);
	return v;
}

void assignH(string k,int idx, SymNode* node){
	if (node == nullptr) {
        return;
    }
    if (node->key == k) {
        node->address = idx ;
        return;
    } else if (node->key > k) {
        return assignH( k , idx,node->left);
    } else {
        return assignH( k, idx, node->right);
    }
}

void SymbolTable::assign_address(string k, int idx) {
    assignH(k, idx, root);
}

int SymbolTable::get_size(){
    return size ; 
}

SymNode* SymbolTable::get_root(){
    return root ; 
}

SymbolTable:: ~SymbolTable() {
    
}