#pragma once
#define MAXCHILD 3
#include "mytype.h"
typedef enum{EXPK,STMTSK,TYPEK}NodeKind;
typedef enum{OPK,CONSTK,IDK}ExpKind;
typedef enum{ IFK,WHILEK, FOREK,FORK,FUNCDK, CLASSK,CINK,COUTK,FUNCSK,BASEK,STARTK,COMSTMTK,RETURNK,MAINK,EXPSK,NULLK}StmtsKind;
typedef enum { INTK, CHARK, INTSK,CHARSK,STRINGK,FLOATK,FLOATSK,NOTK,VOIDK }ExpType;//数组只会存一个大小以及一个标识符id。其val是在内存中的一个初始地址。
typedef enum{ALGCADDK,ALGCMINUSK,UMINUSK,ALGCMULK,ALGCDIVK,ALGCMODK,ALGCTADDPK,ALGCTMINUSPK,ALGCTADDBK,ALGCTMINUSBK,
			LGCCNK,LGCCLESSK,LGCCLESSEQK,LGCCMOREK,LGCCMOREEQK,LGCCEQK,LGCC,BTCNK,BTCLEFTK,BTCRIGHTK,
			BTCYHK,BTCORK,BTCANDK,LGCCORK,LGCCANDK,FUNCK,EQUEK,NEWK,DELETEK,ARRAYCK,CLASSRSTK,CLASSMCK,
			GETADDRK,GETCONTENTK}OpType;//函数也是一种expr。如果函数的参数比较多....记录函数的树的顶点位置。类暂不处理
typedef enum { PUBLICK, PRIVATEK, PROTECTEDK }StatusType;
//typedef enum { FUCDEF, CLASSDEF };

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
	NodeKind nodekind;
	Kind kind;
	Attri attri;
	ExpType type;//yongyu表达式与函数
	string classname;
	//last
	CType*exptype;//应用于类型表达式

};




