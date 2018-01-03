#pragma once
#include"myhashtable.h"
#include<fstream>
#include<stack>

extern ofstream asmf;
extern stack<CHash*> allsymbol;
extern stack<CHash*>storesymbol;
extern hash_map<string, ClassNode*>classmap;
extern hash_map<string, Node*>funcmap;

static Fcodes*gencode(OpType op, string arg1, string arg2, string result) {
	//加减乘除
	if (op == ALGCADDK || op == ALGCMINUSK || op == ALGCMULK || op == ALGCMODK) {
		string tmp = Fcode::genTmp();
		Fcode*c1 = new Fcode(op, arg1, arg2, tmp);
		//		Fcode*c2 = new Fcode(EQUEK, tmp, "", tmp); result仅仅用于EQUAEK
		return new Fcodes(c1,c1);
	}
	//负 取地址 取内容 非 
	else if (op == UMINUSK || op == GETCONTENTK || op == GETADDRK || op == BTCNK) {
		string tmp = Fcode::genTmp();
		Fcode*c1 = new Fcode(op, arg1, "", tmp);
		return new Fcodes(c1, c1);
	}
	//前增量 前减量
	else if (op == ALGCTADDPK || op == ALGCTMINUSPK) {
		string tmp = Fcode::genTmp();
		Fcode*c1 = new Fcode((op == ALGCTADDPK ? ALGCADDK : ALGCMINUSK), arg1, "1", tmp);
		Fcode*c2 = new Fcode(EQUEK, tmp, "", arg1);
		c1->combine2(c2);
		return new Fcodes(c1, c2);
	}
	//后增量 后减量：genLabel
	else if (op == ALGCTADDBK || op == ALGCTMINUSBK) {
		//???
		string tmp = Fcode::genTmp();
		Fcode*c1 = new Fcode(EQUEK, arg1, "", tmp);
		return new Fcodes(c1, c1);
	}
	//位运算处理
	else if (op == BTCLEFTK || op == BTCRIGHTK || op == BTCYHK || op == BTCANDK || op == BTCORK) {
		string tmp = Fcode::genTmp();
		Fcode*c1 = new Fcode(op, arg1, arg2, tmp);
		return new Fcodes(c1, c1);
	}
	//类成员选择处理（仅用于成员变量选择）
	else if (op == CLASSMCK || op == POINTK) {
		string tmp = Fcode::genTmp();
		Fcode*c1 = new Fcode(op, arg1, arg2, tmp);
		return new Fcodes(c1, c1);
	}
	//逻辑运算究竟要不要各自计算，这是一个问题。
	//return处理

}
Fcodes*gencodeasm(Fcodes*f) {//expstmt生成汇编处理
	return NULL;
}
//cin cout的gencode
//其中在cout里面，已经把那些exp的临时存储变量位置都算出来了
//gencode的顺序就是语法树中的顺序
//不能直接根据代码段数据段来重定义
//还是生成不同的名字吧
//tmp值
Fcodes*gencccode(TreeNode*s) {//
	if (!(s->nodekind == STMTSK))return NULL;
	if (s->kind.stmt == COUTOPK) {
		Fcodes*h=NULL;
		Fcodes*tt=NULL;
		TreeNode*t = s->child[0];
		h = t->midcode;
		while (t) {
			t->midcode->tail->result;
		}
	}
}
//逻辑运算：只能用于ifwhilefor判断，否则判错：因为没有设定bool类型（暂定）
//在stmt被处理的时候才会被处理，true与false
//逻辑非
static Fcodes*geniwfcode(TreeNode*s) {
	if (s->nodekind == EXPK && s->kind.exp == IFK) {
		if (s->child[2] == NULL) {//只有if没有else
/*			s->midcode->truel = Fcode::genLabel();
			s->midcode->nextl = Fcode::genLabel();
			s->midcode->falsel = "";*/


		}
	}
}

//函数处理：
