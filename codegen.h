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
	//�Ӽ��˳�
	if (op == ALGCADDK || op == ALGCMINUSK || op == ALGCMULK || op == ALGCMODK) {
		string tmp = Fcode::genTmp();
		Fcode*c1 = new Fcode(op, arg1, arg2, tmp);
		//		Fcode*c2 = new Fcode(EQUEK, tmp, "", tmp); result��������EQUAEK
		return new Fcodes(c1,c1);
	}
	//�� ȡ��ַ ȡ���� �� 
	else if (op == UMINUSK || op == GETCONTENTK || op == GETADDRK || op == BTCNK) {
		string tmp = Fcode::genTmp();
		Fcode*c1 = new Fcode(op, arg1, "", tmp);
		return new Fcodes(c1, c1);
	}
	//ǰ���� ǰ����
	else if (op == ALGCTADDPK || op == ALGCTMINUSPK) {
		string tmp = Fcode::genTmp();
		Fcode*c1 = new Fcode((op == ALGCTADDPK ? ALGCADDK : ALGCMINUSK), arg1, "1", tmp);
		Fcode*c2 = new Fcode(EQUEK, tmp, "", arg1);
		c1->combine2(c2);
		return new Fcodes(c1, c2);
	}
	//������ �������genLabel
	else if (op == ALGCTADDBK || op == ALGCTMINUSBK) {
		//???
		string tmp = Fcode::genTmp();
		Fcode*c1 = new Fcode(EQUEK, arg1, "", tmp);
		return new Fcodes(c1, c1);
	}
	//λ���㴦��
	else if (op == BTCLEFTK || op == BTCRIGHTK || op == BTCYHK || op == BTCANDK || op == BTCORK) {
		string tmp = Fcode::genTmp();
		Fcode*c1 = new Fcode(op, arg1, arg2, tmp);
		return new Fcodes(c1, c1);
	}
	//���Աѡ���������ڳ�Ա����ѡ��
	else if (op == CLASSMCK || op == POINTK) {
		string tmp = Fcode::genTmp();
		Fcode*c1 = new Fcode(op, arg1, arg2, tmp);
		return new Fcodes(c1, c1);
	}
	//�߼����㾿��Ҫ��Ҫ���Լ��㣬����һ�����⡣
	//return����

}
Fcodes*gencodeasm(Fcodes*f) {//expstmt���ɻ�ദ��
	return NULL;
}
//cin cout��gencode
//������cout���棬�Ѿ�����Щexp����ʱ�洢����λ�ö��������
//gencode��˳������﷨���е�˳��
//����ֱ�Ӹ��ݴ�������ݶ����ض���
//�������ɲ�ͬ�����ְ�
//tmpֵ
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
//�߼����㣺ֻ������ifwhilefor�жϣ������д���Ϊû���趨bool���ͣ��ݶ���
//��stmt�������ʱ��Żᱻ����true��false
//�߼���
static Fcodes*geniwfcode(TreeNode*s) {
	if (s->nodekind == EXPK && s->kind.exp == IFK) {
		if (s->child[2] == NULL) {//ֻ��ifû��else
/*			s->midcode->truel = Fcode::genLabel();
			s->midcode->nextl = Fcode::genLabel();
			s->midcode->falsel = "";*/


		}
	}
}

//��������
