/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler() {
	memory_size = 0;
    output_file = "";
    ofstream file(output_file);
    file.close();
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
	output_file = out_file;
	memory_size = mem_limit;
	for (int i=0; i<memory_size; i++) {
		mem_loc.push_back(i);
	}
	ofstream file(output_file);
   file.close();
}

void EPPCompiler::compile(vector<vector<string>> code){
    for (int i = 0 ; i < code.size(); i++) {
        vector<string> expression = code[i];
        targ.parse(expression);
        if (expression.size() >=3 && expression[1]== ":=") {
        if (expression[0]=="del") {
            int address = targ.symtable->search(expression[2]);
            mem_loc.push_back(address);
        }

        else if (expression[0]!="del" && expression[0]!="ret") {
            int l = mem_loc.size();
            int address = mem_loc[l-1];
            mem_loc.pop_back();
            if (targ.symtable->search(expression[0])==-2 || targ.symtable->search(expression[0])==-1) {
                targ.symtable->insert(expression[0]);
                targ.symtable->assign_address(expression[0], address);
            }
        }
        }
        write_to_file(generate_targ_commands());
        }
}


void command(ExprTreeNode* n, vector<string>& v, Parser targ) {
    
    if (n==nullptr) {
        return ;
    }

    if (n->left==nullptr && n->right==nullptr) {
        if (n->type=="VAL") {
            //this is pushing value 
            v.push_back("PUSH "+ std::to_string(n->num));
            return ;
        }

        else if (n->type=="VAR") {
            //this is variable assignment 
            string m = n->id;
            int address = targ.symtable->search(m);
            v.push_back("PUSH mem[" + to_string(address)+"]" );
            return ;
            }
    }

    command(n->right, v, targ);
    command(n->left, v, targ);

    if (n->type=="ADD") {
        v.push_back("ADD");
    }
    if (n->type=="SUB") {
        v.push_back("SUB");
    }
    if (n->type=="MUL") {
        v.push_back("MUL");
    }
    if (n->type=="DIV") {
        v.push_back("DIV");
    }

    return ;
}

vector<string> EPPCompiler::generate_targ_commands(){
    vector<string> targ_command ; 
    int l = targ.symtable->get_size();
    ExprTreeNode* root = targ.expr_trees.back();
    if (root->left->type=="DEL") {
        string k = root->right->id;
        int address = targ.symtable->search(k);
        targ_command.push_back("DEL = mem[" + to_string(address)+ "]");
    } else if (root->left->type=="RET") {
        command(root->right, targ_command, targ);
        targ_command.push_back("RET = POP");
    } else {
        command(root->right, targ_command, targ);
        string p = root->left->id ;
        int addr = targ.symtable->search(p);
        targ_command.push_back("mem[" + to_string(addr) + "] = POP") ;
}
    return targ_command;
}
void EPPCompiler::write_to_file(vector<string> commands) {
    string result;
    for (int i=0; i<commands.size(); i++) {
    result += commands[i] + "\n";
	}
	fstream file(output_file, ios::app);
	file<<result<<endl;
	file.clear();
}

EPPCompiler::~EPPCompiler(){
  
}
