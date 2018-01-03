#pragma once
//#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 1
//#include"mytreenode.h"
#include<iostream>
#include<string>
#include<math.h>
//�����include������
//oû�����
using namespace std;
typedef enum { CVOID=0,CINT=1, CCHAR=2 , CFLOAT=3 , CCLASS=4,CSTRING=5 }BaseType;//3
typedef enum { POINTER = 1, ARRAY = 2, DICAR, RECORD,FUNC }FuncType;//3
class TypeNode {
public:
	BaseType baset;
	FuncType funct;
	TypeNode*left;
	TypeNode*right;
//	string name;
	int size;
	TypeNode() {}
	TypeNode(BaseType b) {
		baset = b;
	}
	TypeNode(FuncType f, TypeNode*l, TypeNode*r) {
		funct = f;
		left = l;
		right = r;
	}
	TypeNode(int s) {
		size = s;
	}
};
class CType {
public:
	int tcode;//���ͱȽϱ���
	int num;
	TypeNode*root;
	string cname;
	//ǳ����������ȥ��rootָ��Ķ���
	CType(CType*t) {
		tcode = t->tcode;
		num = t->num;
		root = t->root;
		cname = t->cname;
	}
	CType() { tcode = 0; root = NULL; num = 3; }
	CType(BaseType type) {//ÿ�ζ���ӻ������Ϳ�ʼ����
		tcode = type;
		root = new TypeNode(type);
		num = 3;
	}
	CType(string n) {
		tcode = CCLASS;
		root = new TypeNode(CCLASS);
		cname=n;
		num = 3;
	}
	CType(BaseType type, string n) {
		tcode = type;
		root = new TypeNode(type);
		num = 3;
		if (type == CCLASS) {
			cname = n;
		}
	}
	bool isnotype(CType*type) {
		if (type->root == NULL && type->tcode == 0)return true;
		return false;
	}
	string code22() {
		string r = "";
		int c = tcode, cc = 0;
		while ((c / 2) > 0) {
			cc = c % 2;
			r = (cc == 0 ? "0" : "1") + r;
			c = c / 2;
		}
		r = (c == 0 ? "0" : "1") + r;
		return r;
	}
	//ʧ�ܵĺ�����û������
	static int cbits(int code) {
		int i = 0;
		while ((code / 2) >= 1) {
			i++;
			code = code / 2;
		}
		i++;
		return i;
	}
	//ע�⣡����һ��Ϊ����˵����������ʱ���ǲ�̫���ܵõ���ȷ�Ľ���ģ����ֱ���㲻�������������
	 int addcode(FuncType f) {
		 int i = num;
//		 num += 3;
		if(3+i<=32)
			switch (f) {
			case POINTER:
				return (POINTER << i) + tcode;
			case ARRAY:
				return (ARRAY << i) + tcode;
			case RECORD:
				return(RECORD << i) + tcode;
			default:
				return tcode;
			}
			
		else {
			return -1;
		}
	}
	 int addcoded(CType*r) {
		int i = num, j = r->num;
//		num += (3 + j);
		if (num + r->num + 3 <= 32)return (tcode << (j + 3)) + (DICAR << j) + r->tcode;
		else return -1;
	}
	 int addcodef(CType*r) {
		 int i = num, j = r->num;
//		 num += (3 + j);
		 if (num + r->num + 3 <= 32)return (tcode << (j + 3)) + (FUNC << j) + r->tcode;
		 else return -1;

	 }
	static CType* pointer(CType*type) {
		CType*n = new CType();
		TypeNode*node=new TypeNode(POINTER, type->root, NULL);
		n->tcode = type->addcode(POINTER);
		n->root = node;
		n->num = type->num + 3;
		n->cname = type->cname;
		return n;
	}
	static CType*depointer(CType*p) {
		int si = p->num;
		int c = (p->tcode);
		if ((c >> (si - 3)) != 1)return NULL;//��������pointer���޷�de
		else {
			CType*t = new CType();
			//t->tcode = si - 3;
			t->tcode = (p->tcode & ((int)(pow(2,si-3)-1)));
			t->root = p->root->left;
			t->num = p->num - 3;
			t->cname = p->cname;
			return t;
		}
	}
	static bool ispointer(CType*p) {
		int si = p->num;
		int c = (p->tcode);
		if ((c >> (si - 3)) != 1)return 0;//��������pointer���޷�de
		return 1;
	}
	static CType* array0(int size,CType*type) {
		CType*c = new CType();
		TypeNode*node = new TypeNode(ARRAY, new TypeNode(size), type->root);
		c->tcode = type->addcode( ARRAY);
		c->root = node;
		c->num = type->num + 3;
		c->cname = type->cname;
		return c;
	}
	static CType*dearray0(CType*p) {
		int si = p->num;
		int c = (p->tcode);
		if ((c >> (si - 3)) != ARRAY)return NULL;//��������pointer���޷�de
		else {
			CType*t = new CType();
			//t->tcode = si - 3;
			t->tcode = (p->tcode & ((int)(pow(2, si - 3) - 1)));
			t->root = p->root->right;
			t->num = p->num - 3;
			t->cname = p->cname;
			return t;
		}
	}

	//record�Ĵ����Ƚϼ򵥣�������Ϊ1.��������жϱȽ��ϸ���ֻ�ᰴ�������ж�2.��������������Ϣ�ڷ��ű���
	static CType* record(CType*type) {
		CType*c = new CType();
		TypeNode*node = new TypeNode(RECORD, type->root, NULL);
		c->tcode = type->addcode( RECORD);
		c->root = node;
		c->num = type->num + 3;
		c->cname = type->cname;
		return c;
	}
	static CType*derecord(CType*p) {
		int si = p->num;
		int c = (p->tcode);
		if ((c >> (si - 3)) != RECORD)return NULL;//��������pointer���޷�de
		else {
			CType*t = new CType();
			
			t->tcode = (p->tcode & ((int)(pow(2, si - 3) - 1)));
			t->root = p->root->left;
			t->num = p->num - 3;
			t->cname = p->cname;
			return t;
		}
	}
	static CType* dicar(CType*type, CType*t) {
		CType*c=new CType();
		TypeNode*node = new TypeNode(DICAR, type->root, t->root);
		c->tcode = type->addcoded(t);
		c->root = node;
		c->num = type->num + 3 + t->num;
		c->cname = type->cname;
		return c;
	}
	static CType*func(CType*type, CType*t) {
		CType*c = new CType();
		TypeNode*node = new TypeNode(FUNC, type->root, t->root);
		c->tcode = type->addcodef(t);
		c->root = node;
		c->num = type->num + 3 + t->num;
		c->cname = type->cname;
		return c;
	}
	//��Ϊfunc�в�����Ƕ��func��ֻ��Ҫ��λ��λ����FUNC�ͺ�
	static CType*defunc(CType*t) {
		//����������Ϊ
		//��֧������Ϊ����ֵ�����
		//��˷���ֵֻ������*����ͨ����
		int code = t->tcode;
		int numb = 0;
		while (code >= 8) {
			if (code % 8 == FUNC)break;
			code = code / 8;
			numb += 3;
		}
		code = t->tcode;
		code = code&((int)(pow(2, numb) - 1));
		CType*c = new CType();
		c->tcode = code;
		c->root = t->root->right;
		c->num = numb;
		c->cname = t->cname;//Ӧ��û��
		return c;
	}
	static CType*defuncr(CType*t) {
		int code = t->tcode;
		int numb = 0;
		while (code >= 8) {
			if (code % 8 == FUNC)break;
			code = code / 8;
			numb += 3;
		}
		code = t->tcode;
		code = code >> (numb + 3);
		CType*c = new CType();
		c->tcode = code;
		c->root = t->root->left;
		c->num = t->num - numb - 3;
		c->cname = t->cname;//Ӧ��û��
		return c;
	}

};