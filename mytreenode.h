#pragma once
#define MAXCHILD 3
#include "mytype.h"
#include<string>

typedef enum{EXPK,STMTSK,TYPEK}NodeKind;
typedef enum{OPK,CONSTK,IDK}ExpKind;

typedef enum{ IFK,WHILEK, FOREK,FORK,FUNCDK, CLASSK,CINK,COUTK,FUNCSK,BASEK,STARTK,COMSTMTK,RETURNK,MAINK,EXPSK,NULLK}StmtsKind;
typedef enum { INTK, CHARK, INTSK,CHARSK,STRINGK,FLOATK,FLOATSK,NOTK,VOIDK }ExpType;//����ֻ���һ����С�Լ�һ����ʶ��id����val�����ڴ��е�һ����ʼ��ַ��

typedef enum{ALGCADDK,ALGCMINUSK,UMINUSK,ALGCMULK,ALGCDIVK,ALGCMODK,ALGCTADDPK,ALGCTMINUSPK,ALGCTADDBK,ALGCTMINUSBK,
			LGCCNK,LGCCLESSK,LGCCLESSEQK,LGCCMOREK,LGCCMOREEQK,LGCCEQK,LGCC,BTCNK,BTCLEFTK,BTCRIGHTK,
			BTCYHK,BTCORK,BTCANDK,LGCCORK,LGCCANDK,FUNCK,EQUEK,NEWK,DELETEK,ARRAYCK,CLASSRSTK,CLASSMCK,POINTK,
			GETADDRK,GETCONTENTK, IFGOTOK,GOTOK,CALLK,PARAMK,COUTOPK,CINOPK,COUTPK,CINPK}OpType;//����Ҳ��һ��expr����������Ĳ����Ƚ϶�....��¼���������Ķ���λ�á����ݲ�����
		//���е��߼������ ����IFRELOPGOTOK
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
	//���ڿ������
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
	//�ڷ����ļ�֮ǰ�������
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
	//�����δ���������һ��
	static Fcodes*combinecode(Fcodes*c, Fcodes*b) {
		if (c == b)return NULL;//�����������������
		Fcodes*n = new Fcodes(c->head, b->tail);
		c->tail->combine2(b->head);
		return n;
	}
	//���ɴ��룺
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
	TreeNode*sibling;//������������������ı����б�
	int lineno;
	NodeKind nodekind;//type��exp����stmt
	Kind kind;//��������������
	Attri attri;
	ExpType type;//yongyu���ʽ�뺯��
	string classname;
	//last
	CType*exptype;//Ӧ�������ͱ��ʽ
	Fcodes*midcode;//�����м��������

};



