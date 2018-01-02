#pragma once
#define MAXCHILD 3
#include "mytype.h"
typedef enum{EXPK,STMTSK,TYPEK}NodeKind;
typedef enum{OPK,CONSTK,IDK}ExpKind;
typedef enum{ IFK,WHILEK, FOREK,FORK,FUNCDK, CLASSK,CINK,COUTK,FUNCSK,BASEK,STARTK,COMSTMTK,RETURNK,MAINK,EXPSK,NULLK}StmtsKind;
typedef enum { INTK, CHARK, INTSK,CHARSK,STRINGK,FLOATK,FLOATSK,NOTK,VOIDK }ExpType;//����ֻ���һ����С�Լ�һ����ʶ��id����val�����ڴ��е�һ����ʼ��ַ��
typedef enum{ALGCADDK,ALGCMINUSK,UMINUSK,ALGCMULK,ALGCDIVK,ALGCMODK,ALGCTADDPK,ALGCTMINUSPK,ALGCTADDBK,ALGCTMINUSBK,
			LGCCNK,LGCCLESSK,LGCCLESSEQK,LGCCMOREK,LGCCMOREEQK,LGCCEQK,LGCC,BTCNK,BTCLEFTK,BTCRIGHTK,
			BTCYHK,BTCORK,BTCANDK,LGCCORK,LGCCANDK,FUNCK,EQUEK,NEWK,DELETEK,ARRAYCK,CLASSRSTK,CLASSMCK,
			GETADDRK,GETCONTENTK}OpType;//����Ҳ��һ��expr����������Ĳ����Ƚ϶�....��¼���������Ķ���λ�á����ݲ�����
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
	TreeNode*sibling;//������������������ı����б�
	int lineno;
	NodeKind nodekind;
	Kind kind;
	Attri attri;
	ExpType type;//yongyu���ʽ�뺯��
	string classname;
	//last
	CType*exptype;//Ӧ�������ͱ��ʽ

};




