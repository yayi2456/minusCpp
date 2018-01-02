#pragma once
//#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 1
//#include"mytreenode.h"
#include<iostream>
#include<string>
//�����include������
//oû�����
using namespace std;
typedef enum { CVOID=0,CINT=1, CCHAR=2 , CFLOAT=3 , CCLASS=4,CSTRING }BaseType;//3
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
		 num += 3;
		if(3+i<=32)
			switch (f) {
			case POINTER:
				return (POINTER << i) + tcode;
			case ARRAY:
				return (ARRAY << i) + tcode;
			case RECORD:
				return(RECORD << i) + tcode;
			default:
				return -1;
			}
			
		else {
			return -1;
		}
	}
	 int addcoded(CType*r) {
		int i = num, j = r->num;
		num += (3 + j);
		if (tcode + r->tcode + 3 <= 32)return (tcode << (i + 3)) + (DICAR << i) + r->tcode;
		else return -1;
	}
	 int addcodef(CType*r) {
		 int i = num, j = r->num;
		 num += (3 + j);
		 if (tcode + r->tcode + 3 <= 32)return (tcode << (i + 3)) + (FUNC << i) + r->tcode;
		 else return -1;

	 }
	static CType* pointer(CType*type) {
		TypeNode*node=new TypeNode(POINTER, type->root, NULL);
		type->tcode = type->addcode(POINTER);
		type->root = node;
		return type;
	}
	static CType* array0(int size,CType*type) {
		TypeNode*node = new TypeNode(ARRAY, new TypeNode(size), type->root);
		type->tcode = type->addcode( ARRAY);
		type->root = node;
		return type;
	}
	//record�Ĵ����Ƚϼ򵥣�������Ϊ1.��������жϱȽ��ϸ���ֻ�ᰴ�������ж�2.��������������Ϣ�ڷ��ű���
	static CType* record(CType*type) {
		TypeNode*node = new TypeNode(RECORD, type->root, NULL);
		type->tcode = type->addcode( RECORD);
		type->root = node;
		return type;
	}
	static CType* dicar(CType*type, CType*t) {
		TypeNode*node = new TypeNode(DICAR, type->root, t->root);
		type->tcode = type->addcoded(t);
		type->root = node;
		return type;
	}
	static CType*func(CType*type, CType*t) {
		TypeNode*node = new TypeNode(FUNC, type->root, t->root);
		type->tcode = type->addcodef(t);
		type->root = node;
		return type;
	}

};