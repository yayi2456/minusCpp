#pragma once
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 1
#include "mytreenode.h"
#include"mytype.h"
#include<string>
#include<hash_map>
using namespace stdext;
const int hashlength = 128;

//将会存进符号表的
//typedef enum { INTT, CHART, INTST, CHARST, FLOATT, FLOATST }AttrType;
class Node {
public:
	string lexeme;//a\b\c\d id
	string token;// ID FUNC CLASS
	ExpType attri;//int char 
	string classname;


	Node*varlist;//用于函数
	TreeNode* value;//是对应TreeNode的地址,主要用于函数
	int szsize;
	//新的符号表中的类型
	CType*exptype;
	
	Node(string classname) {
		this->classname = classname;
	}
	Node(ExpType type) {
		attri = type;
	}
	Node() { lexeme = ""; token = ""; attri = INTK; value = NULL; }
	Node(string token, string lexeme) {
		this->lexeme = lexeme;
		this->token = token;
	}
	Node(string token, string lexeme, ExpType attri,TreeNode* value) {
		this->lexeme = lexeme;
		this->token = token;
		this->attri = attri;
		this->value = value;
	}
	Node(string token, string lexeme, ExpType attri, TreeNode* value,int szsize) {
		this->lexeme = lexeme;
		this->token = token;
		this->attri = attri;
		this->value = value;
		this->szsize = szsize;
	}
	//设置属性。a=2,func
	void setAttri(ExpType attri) {
		this->attri = attri;
	}
	//新的类型的设置
	void setType(CType*t) {
		exptype = t;
	}
	void setVal(TreeNode* value) {
		this->value = value;
	}
	void setszSize(int size) { this->szsize = size; }
};
//存入溢出桶的以及classnode中的
class ListNode {
public:
	Node *nodevalue;
//	StatusType status;
	ListNode*next;
};
//hash
class CHash {
public:
	Node* hashtable[hashlength];
	ListNode*overflow;//溢出部分，应该较小；以链表方式存储
	int sizetable;
	int sizeover;

	int parse(string lexeme) {//散列函数
		const char*clex = lexeme.c_str();
		//cout<<clex<<endl;
		unsigned int *intkey = (unsigned int*)clex;
		int intlength = strlen(clex) / 4;
		unsigned int sum = 0;
		for (int i = 0; i<intlength; i++)sum += intkey[i];

		int extra = strlen(clex) - 4 * intlength;//cout<<extra<<endl;
		char tmp[4];
		intkey = (unsigned int*)tmp;
		intkey[0] = 0;
		for (int i = 0; i<extra; i++)tmp[i] = clex[intlength * 4 + i];
		sum += intkey[0];//cout<<tmp<<"  "<<sum<<endl;
		return sum%hashlength;
	}
	Node* insert(Node*node) {//插入函数
		int value = findinsert(node->lexeme);
		if (hashlength - sizetable <= 1) {
			ListNode*tmp = new ListNode();
			tmp->nodevalue = node;
			ListNode*curr = overflow->next;
			overflow->next = tmp;
			tmp->next = curr;
			sizeover++;
			return tmp->nodevalue;
		}
		else {
			hashtable[value] = node;
			sizetable++;
			return node;
		}
	}
	int findinsert(string lexeme) {//探查函数
		int value = parse(lexeme);
		int i = 0;
		while (hashtable[(value + ((i*i + i) / 2)) % hashlength] != NULL)i++;
		//findinsert 只负责在hashtable里面找一个空位，由于size的限制和length、散列函数的限制，
		//一定能找到一个空位，不管数字记录与比较。在insert里面处理只有一个空位以及overflow的建立。由于没有对overflow的处理，希望它不大
		return (value + ((i*i + i) / 2)) % hashlength;
	}
	Node*findexist(string lexeme) {//
		int value = parse(lexeme);
		int i = 0;
		while (hashtable[(value + ((i*i + i) / 2)) % hashlength] != NULL && hashtable[(value + ((i*i) + i) / 2) % hashlength]->lexeme != lexeme)i++;
		if (hashtable[(value + ((i*i + i) / 2)) % hashlength] == NULL) {
			if (overflow == NULL)return NULL;
			else {
				ListNode*curr = overflow;
				while (curr->next != NULL) {
					if (curr->next->nodevalue->lexeme == lexeme)
						return curr->next->nodevalue;
					curr = curr->next;
				}
				return NULL;
			}
		}
		else {

			return hashtable[(value + ((i*i) + i) / 2) % hashlength];
		}
	}
	//默认构造函数
	CHash() { overflow = NULL; sizetable = 0; sizeover = 0; overflow = new ListNode(); };
};
struct IHashable {
	virtual unsigned long hash_value() const = 0;
	virtual bool operator < (const IHashable& val) const = 0;
	virtual IHashable& operator = (const IHashable& val) = 0;
};
//class这里除了语法树，主要只是classname。其他的可能会在语义阶段完成。或者这阶段完成也可以啦。
//令人感到悲伤的是，在需要检查func以及idname是否冲突的时刻，却需要在list里面来添加项
//因此一个类里面声明的东西最好别太多
class ClassNode{
public:
	string name;
	CType*exptype;
	//大概是没有用了吧
	ListNode*idlist;
	ListNode*funclist;

	CHash*classv;
	hash_map<string,Node*>*classf;

	ClassNode() { name = ""; idlist = funclist = NULL; }
	ClassNode(const ClassNode&obj) {
		name = obj.name;
		idlist = obj.idlist;//浅拷贝
		funclist = obj.funclist;
		exptype = obj.exptype;
		classv = obj.classv;
		classf = obj.classf;
	}
	ClassNode(string name) {
		this->name = name;
		idlist = funclist = NULL;
	}
	ClassNode(string name, CHash*h, hash_map<string, Node*>*m) {
		this->name = name;
		classv = h;
		classf = m;
	}
	//设置类型
	void setType(CType*t) {
		exptype = t;
	}
	//在类中寻找某一个类成员
	CType*findMemv(string name) {
		/*Node*now = idlist;
		while (now) {
			if (now->nodevalue->lexeme == name)return now->nodevalue->exptype;
			now = now->next;
		}
		return NULL;//没有对应的变量*/
		Node*now = classv->findexist(name);
		if (now == NULL)return NULL;
		return now->exptype;
	}
	Node*findMemf(string name) {
	/*	Node*now = funclist;
		while (now) {
			if (now->lexeme == name)return now;
			now = now->varlist;
		}
		return NULL;//没有对应的hanshu*/
		if (classf->find(name) == classf->end())//所指类不存在
			return NULL;
		if (classf->find(name) == classf->end())return NULL;//所指函数不存在
		return (*classf)[name];
	}
};
struct string_less : public binary_function<const string, const string, bool>
{
public:
	result_type operator()(const first_argument_type& _Left, const second_argument_type& _Right) const
	{
		return(_Left.compare(_Right) < 0 ? true : false);
	}
};







