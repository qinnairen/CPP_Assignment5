/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
	symtable = new SymbolTable();
}

void Parser::parse(vector<string> code) {
    vector<ExprTreeNode*> operands;
    vector<string> operators;
    SymbolTable* globalSym = new SymbolTable();
    
    ExprTreeNode* equality = new ExprTreeNode();
	equality->type = "EQL";
	equality->id = ":=";

    ExprTreeNode* node = new ExprTreeNode();
	if (code[0]=="del") {
    	node->type = "DEL";
    	node->id = code[0];
		ExprTreeNode* variable = new ExprTreeNode();
		variable->type = "VAR";
		variable->id = code[2];
		equality->right = variable;
		equality->left = node;
		equality->right->num = globalSym->search(code[2]);
		expr_trees.push_back(equality);
    } else {
    	if (code[0]=="ret") {
    		node->type = "RET" ;
    		node->id = code[0];
		} else {
			node->type = "VAR";
			node->id = code[0];
		}
		equality->left = node;
	    int l = code.size();
	
	    for (int i = 2; i < l; i++) {
	        const string token = code[i];
	        if (token == "(") {
	            operators.push_back(token);
	
			} 
	        
	        else if (token == ")") {
	            while (!operators.empty() && operators.back() != "(") {
	                string op = operators.back();
	                operators.pop_back();
	
	                ExprTreeNode* right = operands.back();
	                operands.pop_back();
	
	                ExprTreeNode* left = operands.back();
	                operands.pop_back();
					
					ExprTreeNode* n = new ExprTreeNode();
					if (op=="+") {
						n->type = "ADD";
					} else if (op=="-") {
						n->type = "SUB";
					} else if (op=="*") {
						n->type = "MUL";
					} else if (op=="/") {
						n->type = "DIV";
					}
	               
	                n->left = left;
	                n->right = right;
	
	                operands.push_back(n);
	            }
	
	            if (!operators.empty() && operators.back() == "(") {
	                operators.pop_back(); 
	            }
	        } 
	        
	        else if (token=="+" || token=="-" || token=="*" || token=="/") {
	        	operators.push_back(token);
			} 
	        
	        else if (isdigit(token[0]) || token[0]=='-') { 
	            int x = stoi(token);
				ExprTreeNode* n = new ExprTreeNode("VAL", x);
	            operands.push_back(n);
	        } 
	        
	        else {
	            ExprTreeNode* n = new ExprTreeNode();
				n->type = "VAR";
				n->id = code[i];
				operands.push_back(n);
	        }
	    }
	    equality->right = operands.back();
	    expr_trees.push_back(equality);
	}
}


Parser:: ~Parser() {

}