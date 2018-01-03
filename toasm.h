#pragma once
#include"myhashtable.h"
#include<fstream>
#include<stack>

extern ofstream asmf;
extern stack<CHash*> allsymbol;
extern stack<CHash*>storesymbol;
extern hash_map<string, ClassNode*>classmap;
extern hash_map<string, Node*>funcmap;
//干脆直接遍历语法树生成汇编代码


