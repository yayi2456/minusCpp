#pragma once
#include"myhashtable.h"
extern hash_map<string, ClassNode*>classmap;
extern hash_map<string, Node*>funcmap;


//����0ok������-1�����ԣ�����1������������ת��
//�� �Ƚ����⣬ֻ��������ȫһ��������һ����������������ת��
//���ܻ��ṩ ǿ������ת�� �������ʱ��
//Ŀǰֻ֧��int float char ֮���ת�����漰ָ�������Ŀǰһ�ɲ���
static int checkEqual(CType*t1, CType*t2) {
	if (t1->tcode == t2->tcode && t1->tcode != 4)return 0;
	if (t1->tcode == 3 || t1->tcode == 2 || t1->tcode == 1) {//float
		if (t2->tcode <= 3 && t2->tcode != 0) {
			return 1;
		}
		else return -1;
	}
	else if (t1->tcode == 4 && t2->tcode == 4) {
		if (t1->cname == t2->cname)return 0;
		else return -1;
	}

	else {
		return -1;
	}
	return 0;
}

//�����漰���Ժ����Լ�������ͼ�顣������ͼ�����������﷨������֮�����
//�﷨���������֮��ֻ��Ҷ�ӽ��Ż�������
//���ͼ�飺
//1. ����������У���鸳ֵ����ǲ��ǿ���ʵ�� ������ǲ�����Ĵ��� 
//2. �ڱ��ʽ����У���������ǲ��ǺϷ� ��鸳ֵ�ǲ��ǳ��� ����Ӧ�����ǲ��Ǵ���
//3.�ں����У����ɲ����б��code�����ں��� 
//4.�����У������ɶ�Ӧ���룬����Ӧid��name�Լ����Լӵ���Ӧ���ű�ı����С�����Ҳ��
static bool checkType(TreeNode*node) {

	return true;
}