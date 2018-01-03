#pragma once
#include"myhashtable.h"
extern hash_map<string, ClassNode*>classmap;
extern hash_map<string, Node*>funcmap;
//类型检查在构建语法树的时候完成，所以类定义之类的必须放在最前面，先定义后使用

static bool isleft(TreeNode*s) {//需要是左值：存在于符号表√ 或 最后是【】运算 最后是-> . 运算 最后是*运算  这个需要树的节点了
	if (s == NULL)return NULL;//大概是不合理的写法导致的
	if (s->nodekind == EXPK && s->kind.exp == CONSTK)return false;//常量不可能是左值
	if (s->kind.exp == IDK)return true;//该变量必定存在
	if (s->kind.exp == OPK) {
		if (s->attri.op == ARRAYCK)return true;
		else if (s->attri.op == CLASSMCK || s->attri.op == POINTK)return true;
		else if (s->attri.op == GETCONTENTK)return true;
		else return false;//不把剩余的作为左值
	}
}
//返回0ok，返回-1不可以，
//类 比较特殊，只有名字完全一样才能算一样，不可能做类型转换
//可能会提供 强制类型转换 看看完成时间
//目前只支持int float char 之间的转换，涉及指针的目前一律不理
static CType* checkEqual(TreeNode*s, CType*t2) {
	if (s == NULL || t2 == NULL)return NULL;//大概是不合理的写法导致的
	if (!isleft(s))return NULL;//不是左值 不可以赋值
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
//由下至上的类型检查，保证t1与t2都是合法合适正确的值
//为了这个目的，可能需要在翻译模式中写
//进入时，已经保证ID一定是存在的
static CType* checkOp(OpType op,CType*t1, CType*t2) {
	if (t1 == NULL || t2 == NULL)return NULL;//大概是不合理的写法导致的
	if (t1->tcode == 5)return NULL;
	if (t1->tcode == 0)return NULL;//string 与 void绝不云巽参加运算
	if (op == BTCNK || op == UMINUSK || op==LGCCNK) {
		
		if ((t1->tcode) == 4 && op!=LGCCNK)return NULL;//不允许类对象的负非
		if (op == BTCNK && t1->tcode != 1)return NULL;//位运算必须是整数
		BaseType b = CVOID;
		if (t1->tcode == 1)b = CINT;
		else if (t1->tcode == 2)b = CCHAR;
		else if (t1->tcode == 3)b = CFLOAT;
		return new CType(b);
	}
	if ((t1->tcode) == 5 || (t2->tcode) == 5)return NULL;
	if ((t1->tcode) == 0 || (t2->tcode) == 0)return NULL;//不允许void的

	if (op == ALGCADDK || op == ALGCMINUSK || op == ALGCMULK || op == ALGCMODK) {
		if ((t1->tcode)  == 4 || (t2->tcode) == 4)return NULL;//不允许类对象的加减
		if (op == ALGCMODK) {
			if ((t1->tcode)  == 3 || (t2->tcode) == 3)return NULL;//不允许float的mod运算
		}
		//不是基本数据类型：不允许运算（最好允许指针加减）
		//允许指针与int
		if ((CType::ispointer(t1) && (t2->tcode = 1))) {
			return t1;
		}
		if ((CType::ispointer(t1) && (t2->tcode = 1))) {
			return t2;
		}
		//就算是func class array pointer也必须是上述情况

		//返回类型：优先级f>i>c
		if (t1->tcode == 2 && t2->tcode == 2)return new CType(CCHAR);
		if (t1->tcode != 3 && t2->tcode != 3)return new CType(CINT);
		return new CType(CFLOAT);
	}

	else if (op == GETCONTENTK ) {//只允许对指针类型
		return CType::depointer(t1);
	}
	//位运算处理
	else if (op == BTCLEFTK || op == BTCRIGHTK || op == BTCYHK || op == BTCANDK || op == BTCORK) {
		if (t1->tcode != 1 || t2->tcode != 1)return NULL;
	}
	else if (op == ARRAYCK) {//
		if (t2->tcode != 1)return NULL;//只能是int
		return CType::dearray0(t1);
	}

	//getaadr与增量需要左值，放在单独的函数中检验
	else if (op == GETADDRK) {//需要是左值：存在于符号表√ 或 最后是【】运算 最后是-> . 运算 最后是*运算  这个需要树的节点了
		
		return NULL;
	}
	//前增量 前减量 	//后增量 后减量： 需要是左值
	else if (op == ALGCTADDPK || op == ALGCTMINUSPK || op == ALGCTADDBK || op == ALGCTMINUSBK) {
		
		return NULL;
	}
}
//这个s是单目运算的另外一个变量
static CType* checkleft(OpType op, TreeNode*s) {
	if (s == NULL)return NULL;//大概是不合理的写法导致的
	//getaadr与增量需要左值，放在单独的函数中检验
	if (op == GETADDRK) {//需要是左值：存在于符号表√ 或 最后是【】运算 最后是-> . 运算 最后是*运算  这个需要树的节点了

		if (s->nodekind == EXPK && s->kind.exp == CONSTK)return NULL;//常量不可能是左值
		if (s->kind.exp == IDK)return CType::pointer(s->exptype);//该变量必定存在
		if (s->kind.exp == OPK) {
			if (s->attri.op == ARRAYCK)return CType::pointer(s->exptype);
			else if (s->attri.op == CLASSMCK || s->attri.op == POINTK)return CType::pointer(s->exptype);
			else if (s->attri.op == GETCONTENTK)return CType::pointer(s->exptype);
			else return NULL;//不把剩余的作为左值
		}
		return NULL;
	}
	//前增量 前减量 	//后增量 后减量： 需要是左值
	else if (op == ALGCTADDPK || op == ALGCTMINUSPK || op == ALGCTADDBK || op == ALGCTMINUSBK) {
		if (s->nodekind == EXPK && s->kind.exp == CONSTK)return NULL;//常量不可能是左值
		if (s->kind.exp == IDK)return (s->exptype);//该变量必定存在
		if (s->kind.exp == OPK) {
			if (s->attri.op == ARRAYCK)return CType::pointer(s->exptype);
			else if (s->attri.op == CLASSMCK || s->attri.op == POINTK)return (s->exptype);
			else if (s->attri.op == GETCONTENTK)return (s->exptype);
			else return NULL;//不把剩余的作为左值
		}
		return NULL;
	}
}
static CType* checkclass(OpType op,CType*t1,string name,CType*t2){//t2用于函数的参数列表类型
	if (t1 == NULL )return NULL;//大概是不合理的写法导致的
	//类成员选择处理
	if (op == CLASSMCK) {
		if ((t1->tcode & 4) != 4)return NULL;//根本不是类对象
		CType*p = CType::depointer(t1);
		if (!(p)) {//根本不是指针
			return NULL;
		}
		if (classmap.find(p->cname) == classmap.end())//所指类不存在
			return NULL;
		//所指类存在，需要额外判断所致变量是否该类的类成员以及其类型
		CType*t=NULL;
		if(t2==NULL)t= (classmap[t1->cname])->findMemv(name);
		else {
			Node*n= (classmap[t1->cname])->findMemf(name);//因为...我不支持重载，所以只要找到了一个函数，它的参数列表不符合规定，就算是没找到
			//defunc是不太好实现的，直接去符号表中找：value
			if (!n)return NULL;
			if ((CType::defunc(n->exptype)->tcode)== (t2->tcode)) {
				CType*s = CType::defuncr(n->exptype);
				return s;
			}

		}
		return t;
	}
	else if (op == POINTK) {
		if ((t1->tcode) != 4)return NULL;//根本不是类对象
		if (classmap.find(t1->cname) == classmap.end())//所指类不存在
			return NULL;
		//所指类存在，需要额外判断所致变量是否该类的类成员以及其类型
		CType*t=NULL;
		if (t2 == NULL) {
			ClassNode*cn = (classmap[t1->cname]);
			t = cn->findMemv(name);
		}
		else {
			Node*n = (classmap[t1->cname])->findMemf(name);//因为...我不支持重载，所以只要找到了一个函数，它的参数列表不符合规定，就算是没找到
			//defunc是不太好实现的，直接去符号表中找：value
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
//更加重要的是，在语法树的分析中，我根本不知道func应该被哪个check
//因此，在类中被调用的，就单独写出了语法
//由于不支持静态，所有类成员都应该由类对象调用
static CType*checkfunc(string name, CType*t) {
	if (t == NULL)return NULL;//大概是不合理的写法导致的
	if (funcmap.find(name) == funcmap.end())//所指hs不存在
		return NULL;
	Node*n = funcmap[name];
	if (n == NULL)return NULL;
	if ((CType::defunc(n->exptype)->tcode) == (t->tcode)) {
		CType*s = CType::defuncr(n->exptype);
		return s;
	}
	return NULL;
}







//由于涉及到对函数以及类的类型检查。因此类型检查放在最后，在语法树建立之后完成
//语法树建立完成之后只有叶子结点才会有类型
//类型检查：
//1. 在声明语句中：检查赋值语句是不是可以实现 检查类是不是真的存在 √
//2. 在表达式语句中：检查运算是不是合法 检查赋值是不是成立 检查对应变量是不是存在 √
//3.在函数中：生成参数列表的code并存在函数 未完成
//4.在类中：不生成对应编码，将对应id的name以及属性加到对应符号表的表向中。函数也是 
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