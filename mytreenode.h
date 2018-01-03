#pragma once
#define MAXCHILD 3
#include "mytype.h"
#include<string>

typedef enum{EXPK,STMTSK,TYPEK}NodeKind;
typedef enum{OPK,CONSTK,IDK}ExpKind;

typedef enum{ IFK,WHILEK, FOREK,FORK,FUNCDK, CLASSK,CINK,COUTK,FUNCSK,BASEK,STARTK,COMSTMTK,RETURNK,MAINK,EXPSK,NULLK}StmtsKind;
typedef enum { INTK, CHARK, INTSK,CHARSK,STRINGK,FLOATK,FLOATSK,NOTK,VOIDK }ExpType;//数组只会存一个大小以及一个标识符id。其val是在内存中的一个初始地址。

typedef enum{ALGCADDK,ALGCMINUSK,UMINUSK,ALGCMULK,ALGCDIVK,ALGCMODK,ALGCTADDPK,ALGCTMINUSPK,ALGCTADDBK,ALGCTMINUSBK,
			LGCCNK,LGCCLESSK,LGCCLESSEQK,LGCCMOREK,LGCCMOREEQK,LGCCEQK,LGCC,BTCNK,BTCLEFTK,BTCRIGHTK,
			BTCYHK,BTCORK,BTCANDK,LGCCORK,LGCCANDK,FUNCK,EQUEK,NEWK,DELETEK,ARRAYCK,CLASSRSTK,CLASSMCK,POINTK,
			GETADDRK,GETCONTENTK, IFGOTOK,GOTOK,CALLK,PARAMK,COUTOPK,CINOPK,COUTPK,CINPK}OpType;//函数也是一种expr。如果函数的参数比较多....记录函数的树的顶点位置。类暂不处理
		//所有的逻辑运算符 都是IFRELOPGOTOK
typedef enum { PUBLICK, PRIVATEK, PROTECTEDK }StatusType;
//typedef enum { FUCDEF, CLASSDEF };
class Fcode {
public:
	OpType op;
	string arg1;
	string arg2;
	string result;
	Fcode*next;
	Fcode*last;
	static int num;
	static int labelnum;
	//用于控制语句
	string truel;
	string falsel;
	string nextl;
	Fcode(OpType o, string a1, string a2, string r) {
		op = o;
		arg1 = a1;
		arg2 = a2;
		result = r;
	}
	Fcode() {}
	void combine2(Fcode*c) {
		next = c;
		c->last = this;
	}
	//在分析文件之前必须调用
	static void initnum() {
		num = 0;
		labelnum = 0;
	}
	static string genTmp() {
		return "tmp_" + num++;
	}
	static string genLabel() {
		return "@_" + labelnum++;
	}
};

class Fcodes {
public:
	Fcode*head;
	Fcode*tail;
	Fcodes() {}
	Fcodes(Fcode*l, Fcode*r) {
		head = l;
		tail = r;
	}
	//将两段代码连接在一起
	static Fcodes*combinecode(Fcodes*c, Fcodes*b) {
		if (c == b)return NULL;//不允许这种情况出现
		Fcodes*n = new Fcodes(c->head, b->tail);
		c->tail->combine2(b->head);
		return n;
	}
	//生成代码：
	/*
	typedef enum{ALGCADDK,ALGCMINUSK,UMINUSK,ALGCMULK,ALGCDIVK,ALGCMODK
	,ALGCTADDPK,ALGCTMINUSPK,ALGCTADDBK,ALGCTMINUSBK,
			LGCCNK,LGCCLESSK,LGCCLESSEQK,LGCCMOREK,LGCCMOREEQK,LGCCEQK,LGCC,
			BTCNK,BTCLEFTK,BTCRIGHTK,BTCYHK,BTCORK,BTCANDK,
			LGCCORK,LGCCANDK,
			FUNCK,EQUEK,NEWK,DELETEK,ARRAYCK,CLASSRSTK,CLASSMCK,//->
			GETADDRK,GETCONTENTK}OpType;
			*/
	

};


class Kind {
public:
	StmtsKind stmt;
	ExpKind exp; 
};
class  Attri{
public:
	OpType op; float val; string conststring;  string name;
};

class TreeNode {
public:
	TreeNode*child[MAXCHILD];
	TreeNode*sibling;//声明多个变量，函数的变量列表
	int lineno;
	NodeKind nodekind;//type，exp还是stmt
	Kind kind;//具体是哪种类型
	Attri attri;
	ExpType type;//yongyu表达式与函数
	string classname;
	//last
	CType*exptype;//应用于类型表达式
	Fcodes*midcode;//用于中间代码生成

};



