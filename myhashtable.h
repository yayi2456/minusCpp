#pragma once
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 1
#include "mytreenode.h"
#include"mytype.h"
#include<string>
#include<hash_map>
using namespace stdext;
const int hashlength = 128;

//���������ű��
//typedef enum { INTT, CHART, INTST, CHARST, FLOATT, FLOATST }AttrType;
class Node {
public:
	string lexeme;//a\b\c\d id
	string token;// ID FUNC CLASS
	ExpType attri;//int char 
	string classname;


	Node*varlist;//���ں���
	TreeNode* value;//�Ƕ�ӦTreeNode�ĵ�ַ,��Ҫ���ں���
	int szsize;
	//�µķ��ű��е�����
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
	//�������ԡ�a=2,func
	void setAttri(ExpType attri) {
		this->attri = attri;
	}
	//�µ����͵�����
	void setType(CType*t) {
		exptype = t;
	}
	void setVal(TreeNode* value) {
		this->value = value;
	}
	void setszSize(int size) { this->szsize = size; }
};
//�������Ͱ���Լ�classnode�е�
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
	ListNode*overflow;//������֣�Ӧ�ý�С��������ʽ�洢
	int sizetable;
	int sizeover;

	int parse(string lexeme) {//ɢ�к���
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
	Node* insert(Node*node) {//���뺯��
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
	int findinsert(string lexeme) {//̽�麯��
		int value = parse(lexeme);
		int i = 0;
		while (hashtable[(value + ((i*i + i) / 2)) % hashlength] != NULL)i++;
		//findinsert ֻ������hashtable������һ����λ������size�����ƺ�length��ɢ�к��������ƣ�
		//һ�����ҵ�һ����λ���������ּ�¼��Ƚϡ���insert���洦��ֻ��һ����λ�Լ�overflow�Ľ���������û�ж�overflow�Ĵ���ϣ��������
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
	//Ĭ�Ϲ��캯��
	CHash() { overflow = NULL; sizetable = 0; sizeover = 0; overflow = new ListNode(); };
};
struct IHashable {
	virtual unsigned long hash_value() const = 0;
	virtual bool operator < (const IHashable& val) const = 0;
	virtual IHashable& operator = (const IHashable& val) = 0;
};
//class��������﷨������Ҫֻ��classname�������Ŀ��ܻ�������׶���ɡ�������׶����Ҳ��������
//���˸е����˵��ǣ�����Ҫ���func�Լ�idname�Ƿ��ͻ��ʱ�̣�ȴ��Ҫ��list�����������
//���һ�������������Ķ�����ñ�̫��
class ClassNode{
public:
	string name;
	CType*exptype;
	//�����û�����˰�
	ListNode*idlist;
	ListNode*funclist;

	CHash*classv;
	hash_map<string,Node*>*classf;

	ClassNode() { name = ""; idlist = funclist = NULL; }
	ClassNode(const ClassNode&obj) {
		name = obj.name;
		idlist = obj.idlist;//ǳ����
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
	//��������
	void setType(CType*t) {
		exptype = t;
	}
	//������Ѱ��ĳһ�����Ա
	CType*findMemv(string name) {
		/*Node*now = idlist;
		while (now) {
			if (now->nodevalue->lexeme == name)return now->nodevalue->exptype;
			now = now->next;
		}
		return NULL;//û�ж�Ӧ�ı���*/
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
		return NULL;//û�ж�Ӧ��hanshu*/
		if (classf->find(name) == classf->end())//��ָ�಻����
			return NULL;
		if (classf->find(name) == classf->end())return NULL;//��ָ����������
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







