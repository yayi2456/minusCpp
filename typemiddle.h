#pragma once
#include"myhashtable.h"
extern hash_map<string, ClassNode*>classmap;
extern hash_map<string, Node*>funcmap;
//���ͼ���ڹ����﷨����ʱ����ɣ������ඨ��֮��ı��������ǰ�棬�ȶ����ʹ��

static bool isleft(TreeNode*s) {//��Ҫ����ֵ�������ڷ��ű�� �� ����ǡ������� �����-> . ���� �����*����  �����Ҫ���Ľڵ���
	if (s == NULL)return NULL;//����ǲ������д�����µ�
	if (s->nodekind == EXPK && s->kind.exp == CONSTK)return false;//��������������ֵ
	if (s->kind.exp == IDK)return true;//�ñ����ض�����
	if (s->kind.exp == OPK) {
		if (s->attri.op == ARRAYCK)return true;
		else if (s->attri.op == CLASSMCK || s->attri.op == POINTK)return true;
		else if (s->attri.op == GETCONTENTK)return true;
		else return false;//����ʣ�����Ϊ��ֵ
	}
}
//����0ok������-1�����ԣ�
//�� �Ƚ����⣬ֻ��������ȫһ��������һ����������������ת��
//���ܻ��ṩ ǿ������ת�� �������ʱ��
//Ŀǰֻ֧��int float char ֮���ת�����漰ָ���Ŀǰһ�ɲ���
static CType* checkEqual(TreeNode*s, CType*t2) {
	if (s == NULL || t2 == NULL)return NULL;//����ǲ������д�����µ�
	if (!isleft(s))return NULL;//������ֵ �����Ը�ֵ
	CType*t1 = s->exptype;
	if (t1->tcode == t2->tcode && t1->tcode != 4)return new CType(t1);
	if (t1->tcode == 3 || t1->tcode == 2 || t1->tcode == 1) {//float
		if (t2->tcode <= 3 && t2->tcode != 0) {
			return new CType(t1);
			/*if (t1->tcode == 2 && t2->tcode == 2)return new CType(CCHAR);
			if (t1->tcode != 3 && t2->tcode != 3)return new CType(CINT);
			return new CType(CFLOAT);*/
		}
		else return NULL;
	}
	else if (t1->tcode == 4 && t2->tcode == 4) {
		if (t1->cname == t2->cname)return new CType(t1->cname);
		else return NULL;
	}

	else {
		return NULL;
	}
	//return 0;
}
//�������ϵ����ͼ�飬��֤t1��t2���ǺϷ�������ȷ��ֵ
//Ϊ�����Ŀ�ģ�������Ҫ�ڷ���ģʽ��д
//����ʱ���Ѿ���֤IDһ���Ǵ��ڵ�
static CType* checkOp(OpType op,CType*t1, CType*t2) {
	if (t1 == NULL || t2 == NULL)return NULL;//����ǲ������д�����µ�
	if (t1->tcode == 5)return NULL;
	if (t1->tcode == 0)return NULL;//string �� void��������μ�����
	if (op == BTCNK || op == UMINUSK || op==LGCCNK) {
		
		if ((t1->tcode) == 4 && op!=LGCCNK)return NULL;//�����������ĸ���
		if (op == BTCNK && t1->tcode != 1)return NULL;//λ�������������
		BaseType b = CVOID;
		if (t1->tcode == 1)b = CINT;
		else if (t1->tcode == 2)b = CCHAR;
		else if (t1->tcode == 3)b = CFLOAT;
		return new CType(b);
	}
	if ((t1->tcode) == 5 || (t2->tcode) == 5)return NULL;
	if ((t1->tcode) == 0 || (t2->tcode) == 0)return NULL;//������void��

	if (op == ALGCADDK || op == ALGCMINUSK || op == ALGCMULK || op == ALGCMODK) {
		if ((t1->tcode)  == 4 || (t2->tcode) == 4)return NULL;//�����������ļӼ�
		if (op == ALGCMODK) {
			if ((t1->tcode)  == 3 || (t2->tcode) == 3)return NULL;//������float��mod����
		}
		//���ǻ����������ͣ����������㣨�������ָ��Ӽ���
		//����ָ����int
		if ((CType::ispointer(t1) && (t2->tcode = 1))) {
			return t1;
		}
		if ((CType::ispointer(t1) && (t2->tcode = 1))) {
			return t2;
		}
		//������func class array pointerҲ�������������

		//�������ͣ����ȼ�f>i>c
		if (t1->tcode == 2 && t2->tcode == 2)return new CType(CCHAR);
		if (t1->tcode != 3 && t2->tcode != 3)return new CType(CINT);
		return new CType(CFLOAT);
	}

	else if (op == GETCONTENTK ) {//ֻ�����ָ������
		return CType::depointer(t1);
	}
	//λ���㴦��
	else if (op == BTCLEFTK || op == BTCRIGHTK || op == BTCYHK || op == BTCANDK || op == BTCORK) {
		if (t1->tcode != 1 || t2->tcode != 1)return NULL;
	}
	else if (op == ARRAYCK) {//
		if (t2->tcode != 1)return NULL;//ֻ����int
		return CType::dearray0(t1);
	}

	//getaadr��������Ҫ��ֵ�����ڵ����ĺ����м���
	else if (op == GETADDRK) {//��Ҫ����ֵ�������ڷ��ű�� �� ����ǡ������� �����-> . ���� �����*����  �����Ҫ���Ľڵ���
		
		return NULL;
	}
	//ǰ���� ǰ���� 	//������ ������� ��Ҫ����ֵ
	else if (op == ALGCTADDPK || op == ALGCTMINUSPK || op == ALGCTADDBK || op == ALGCTMINUSBK) {
		
		return NULL;
	}
}
//���s�ǵ�Ŀ���������һ������
static CType* checkleft(OpType op, TreeNode*s) {
	if (s == NULL)return NULL;//����ǲ������д�����µ�
	//getaadr��������Ҫ��ֵ�����ڵ����ĺ����м���
	if (op == GETADDRK) {//��Ҫ����ֵ�������ڷ��ű�� �� ����ǡ������� �����-> . ���� �����*����  �����Ҫ���Ľڵ���

		if (s->nodekind == EXPK && s->kind.exp == CONSTK)return NULL;//��������������ֵ
		if (s->kind.exp == IDK)return CType::pointer(s->exptype);//�ñ����ض�����
		if (s->kind.exp == OPK) {
			if (s->attri.op == ARRAYCK)return CType::pointer(s->exptype);
			else if (s->attri.op == CLASSMCK || s->attri.op == POINTK)return CType::pointer(s->exptype);
			else if (s->attri.op == GETCONTENTK)return CType::pointer(s->exptype);
			else return NULL;//����ʣ�����Ϊ��ֵ
		}
		return NULL;
	}
	//ǰ���� ǰ���� 	//������ ������� ��Ҫ����ֵ
	else if (op == ALGCTADDPK || op == ALGCTMINUSPK || op == ALGCTADDBK || op == ALGCTMINUSBK) {
		if (s->nodekind == EXPK && s->kind.exp == CONSTK)return NULL;//��������������ֵ
		if (s->kind.exp == IDK)return (s->exptype);//�ñ����ض�����
		if (s->kind.exp == OPK) {
			if (s->attri.op == ARRAYCK)return CType::pointer(s->exptype);
			else if (s->attri.op == CLASSMCK || s->attri.op == POINTK)return (s->exptype);
			else if (s->attri.op == GETCONTENTK)return (s->exptype);
			else return NULL;//����ʣ�����Ϊ��ֵ
		}
		return NULL;
	}
}
static CType* checkclass(OpType op,CType*t1,string name,CType*t2){//t2���ں����Ĳ����б�����
	if (t1 == NULL )return NULL;//����ǲ������д�����µ�
	//���Աѡ����
	if (op == CLASSMCK) {
		if ((t1->tcode & 4) != 4)return NULL;//�������������
		CType*p = CType::depointer(t1);
		if (!(p)) {//��������ָ��
			return NULL;
		}
		if (classmap.find(p->cname) == classmap.end())//��ָ�಻����
			return NULL;
		//��ָ����ڣ���Ҫ�����ж����±����Ƿ��������Ա�Լ�������
		CType*t=NULL;
		if(t2==NULL)t= (classmap[t1->cname])->findMemv(name);
		else {
			Node*n= (classmap[t1->cname])->findMemf(name);//��Ϊ...�Ҳ�֧�����أ�����ֻҪ�ҵ���һ�����������Ĳ����б����Ϲ涨��������û�ҵ�
			//defunc�ǲ�̫��ʵ�ֵģ�ֱ��ȥ���ű����ң�value
			if (!n)return NULL;
			if ((CType::defunc(n->exptype)->tcode)== (t2->tcode)) {
				CType*s = CType::defuncr(n->exptype);
				return s;
			}

		}
		return t;
	}
	else if (op == POINTK) {
		if ((t1->tcode) != 4)return NULL;//�������������
		if (classmap.find(t1->cname) == classmap.end())//��ָ�಻����
			return NULL;
		//��ָ����ڣ���Ҫ�����ж����±����Ƿ��������Ա�Լ�������
		CType*t=NULL;
		if (t2 == NULL) {
			ClassNode*cn = (classmap[t1->cname]);
			t = cn->findMemv(name);
		}
		else {
			Node*n = (classmap[t1->cname])->findMemf(name);//��Ϊ...�Ҳ�֧�����أ�����ֻҪ�ҵ���һ�����������Ĳ����б����Ϲ涨��������û�ҵ�
			//defunc�ǲ�̫��ʵ�ֵģ�ֱ��ȥ���ű����ң�value
			if (n == NULL)return NULL;
//			if((n->exptype->root->))
			if ((CType::defunc(n->exptype)->tcode) == (t2->tcode)) {
				 CType*s=CType::defuncr(n->exptype);
				 return s;
			}

		}
		return t;
	}
}
//������Ҫ���ǣ����﷨���ķ����У��Ҹ�����֪��funcӦ�ñ��ĸ�check
//��ˣ������б����õģ��͵���д�����﷨
//���ڲ�֧�־�̬���������Ա��Ӧ������������
static CType*checkfunc(string name, CType*t) {
	if (t == NULL)return NULL;//����ǲ������д�����µ�
	if (funcmap.find(name) == funcmap.end())//��ָhs������
		return NULL;
	Node*n = funcmap[name];
	if (n == NULL)return NULL;
	if ((CType::defunc(n->exptype)->tcode) == (t->tcode)) {
		CType*s = CType::defuncr(n->exptype);
		return s;
	}
	return NULL;
}







//�����漰���Ժ����Լ�������ͼ�顣������ͼ�����������﷨������֮�����
//�﷨���������֮��ֻ��Ҷ�ӽ��Ż�������
//���ͼ�飺
//1. ����������У���鸳ֵ����ǲ��ǿ���ʵ�� ������ǲ�����Ĵ��� ��
//2. �ڱ��ʽ����У���������ǲ��ǺϷ� ��鸳ֵ�ǲ��ǳ��� ����Ӧ�����ǲ��Ǵ��� ��
//3.�ں����У����ɲ����б��code�����ں��� δ���
//4.�����У������ɶ�Ӧ���룬����Ӧid��name�Լ����Լӵ���Ӧ���ű�ı����С�����Ҳ�� 
/*
static bool checkType(TreeNode*node) {
	if (node->nodkind != STMTK)return 0;
	if (node->kind.stmt != STARTK) {
		if (node->kind.stmt == MAINK)return checkfunc(node);
		else if (node->kind.stmt == BASEK)return checkbase(node);
		else if (node->kind.stmt == CLASSK)return checkclass(node);
		else if (node->kind.stmt == FUNCDK)return checkfunc(node);
		else return 0;
	}
	checkType(node->child[0]);
	checkType(node->child[1]);
}
static bool checkfunc(TreeNode*node) {
	CType*returntype = funcmap[node->child[1]->attri.name]->exptype;
}

static bool checkbase(TreeNode*s) {
	if (s == NULL)return false;
	if (node->nodekind == EXPK && node->kind.exp == OPK && node->attri.op == EQUEK) {
		return checkequek(node);
	}
	checkbase(s->child[0]);
	checkbase(s->child[1]);
	checkbase(s->sibling);
}
*/