#pragma once
#include"myhashtable.h"
extern hash_map<string, ClassNode*>classmap;
extern hash_map<string, Node*>funcmap;


//返回0ok，返回-1不可以，返回1代表做了类型转换
//类 比较特殊，只有名字完全一样才能算一样，不可能做类型转换
//可能会提供 强制类型转换 看看完成时间
//目前只支持int float char 之间的转换，涉及指针数组的目前一律不理
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

//由于涉及到对函数以及类的类型检查。因此类型检查放在最后，在语法树建立之后完成
//语法树建立完成之后只有叶子结点才会有类型
//类型检查：
//1. 在声明语句中：检查赋值语句是不是可以实现 检查类是不是真的存在 
//2. 在表达式语句中：检查运算是不是合法 检查赋值是不是成立 检查对应变量是不是存在
//3.在函数中：生成参数列表的code并存在函数 
//4.在类中：不生成对应编码，将对应id的name以及属性加到对应符号表的表向中。函数也是
static bool checkType(TreeNode*node) {

	return true;
}