/****************************************************************************
*                     U N R E G I S T E R E D   C O P Y
* 
* You are on day 109 of your 30 day trial period.
* 
* This file was produced by an UNREGISTERED COPY of Parser Generator. It is
* for evaluation purposes only. If you continue to use Parser Generator 30
* days after installation then you are required to purchase a license. For
* more information see the online help or go to the Bumble-Bee Software
* homepage at:
* 
* http://www.bumblebeesoftware.com
* 
* This notice must remain present in the file. It cannot be removed.
****************************************************************************/

/****************************************************************************
* myparser.cpp
* C++ source file generated from myparser.y.
* 
* Date: 01/02/18
* Time: 22:59:50
* 
* AYACC Version: 2.07
****************************************************************************/

#include <yycpars.h>

// namespaces
#ifdef YYSTDCPPLIB
using namespace std;
#endif
#ifdef YYNAMESPACE
using namespace yl;
#endif

#line 1 ".\\myparser.y"

/****************************************************************************
myparser.y
ParserWizard generated YACC file.

Date: 2017年12月2日
****************************************************************************/

#include "mylexer.h"
//包括了这个
#include<iomanip>
#include <fstream>
#include<iostream>
#include<cctype>
#include<string>
#include<stack>
#include <sstream>
#include <stdlib.h> //要将string类和int类型直接转换最好有这些包含，
#include "mytreenode.h"
#include"myhashtable.h"
#include"mytype.h"
#include"typemiddle.h"

using namespace std;

extern stack<CHash*> allsymbol;
extern stack<CHash*>storesymbol;
//CHash*classname;//为了支持类操作，检查类类型。
extern int lineno;
ExpType nowattri;
BaseType nowcode;
string nowclass;
TreeNode*startnode;


ofstream rout("result.txt");
ofstream trout("tree.txt");

hash_map<string,ClassNode*>classmap;
hash_map<string,Node*>funcmap;

TreeNode*lastt;
TreeNode*comlastt;
stack<TreeNode*>cstlastt;
string getstring(const int n);
string getstringd(const float f);
//int getint(string s);
Node*findfexist(stack<CHash*> ms, string lexeme, int &count);
TreeNode*newStmtsNode(StmtsKind kind);
TreeNode*newExpNode(ExpKind kind);
TreeNode*newTypeNode(ExpType type);
TreeNode*newTypeNode(ExpType type,string classname);

string getType(TreeNode*n){
	return (n->nodekind==EXPK ? "expr:" :(n->nodekind==TYPEK ? "type:":"stmt:"));
}
NodeKind getTypep(TreeNode*n){
	return (n->nodekind==EXPK ? EXPK :(n->nodekind==TYPEK ? TYPEK:STMTSK));
}
string getOp(OpType op){
	if(op== ALGCADDK )return "+";
	if(op== ALGCMINUSK )return "-";
	if(op== ALGCMULK )return "*";
	if(op== ALGCDIVK )return "/";
	if(op== UMINUSK )return "-";
	if(op== ALGCMODK )return "%";
	if(op== LGCCLESSK )return "<";
	if(op== LGCCMOREK )return ">";
	if(op== LGCCLESSEQK )return "<=";
	if(op== LGCCMOREEQK )return ">=";
	if(op== LGCCEQK )return "==";
	if(op== LGCCNK )return "!=";
	if(op== BTCYHK )return "^";
	if(op== BTCANDK )return "&";
	if(op== LGCCANDK )return "&&";
	if(op== LGCCORK )return "||";
	if(op== BTCORK )return "|";
	if(op== BTCNK )return "~";
	if(op== BTCLEFTK )return "<<";
	if(op== BTCRIGHTK )return "<<";
	if(op== NEWK )return "new";
	if(op== DELETEK )return "delete";
	if(op== GETADDRK )return "&";
	if(op== GETCONTENTK )return "*";
	if(op== FUNCK )return "()";
	if(op== EQUEK )return "=";
	if(op== ARRAYCK )return "[]";
	if(op== ALGCTMINUSPK )return "--";
	if(op== ALGCTADDPK )return "++";
	if(op== ALGCTADDBK )return "++";
	if(op== ALGCTMINUSBK )return "--";
	if(op==CLASSMCK)return "->/.";
}
string getVal(TreeNode*s){
	if(s->kind.exp!=CONSTK)return "error";
	else {
		if(s->type==STRINGK)return s->attri.conststring;
		else if(s->type==INTK )return ""+getstring((s->attri.val));
		else if(s->type==FLOATK)return ""+getstringd((s->attri.val));
		else if(s->type==CHARK)return ""+(char)(s->attri.val);
	}
	return "error";
}
string getInfo(TreeNode*n){
	NodeKind kind=getTypep(n);
	if(kind==TYPEK){
		//hash_map<int,string>tmpmap;
		//switch (n->type){
		if(n->type== INTK) return "int";
		if(n->type== CHARK)return "char";
		if(n->type== INTSK) return "int*";
		if(n->type== CHARSK)return "char*";
		if(n->type== FLOATK)return "float";
		if(n->type== FLOATSK)return "float*";
		if(n->type== STRINGK) return "string";
		if(n->type==NOTK) return "class:"+(n->classname);
	//	}
	}
	else if(kind==STMTSK){
		if(n->kind.stmt==EXPSK)return "stmt:expr";
		if(n->kind.stmt== IFK)return "stmt:if";
		if(n->kind.stmt== WHILEK)return "stmt:while";
		if(n->kind.stmt== FOREK)return "expr in for";
		if(n->kind.stmt== FUNCDK)return "func define:";
		if(n->kind.stmt== CLASSK)return "class define";
		if(n->kind.stmt== CINK)return "stmt:cin";
		if(n->kind.stmt== COUTK)return "stmt:cout";
		if(n->kind.stmt== FUNCSK)return "func declare";
		if(n->kind.stmt== BASEK)return "type define";
		if(n->kind.stmt== STARTK)return "stmt:startnode";
		if(n->kind.stmt== COMSTMTK)return "stmt:comstmt";
		if(n->kind.stmt== RETURNK )return "stmt:return";
		if(n->kind.stmt== MAINK )return "entry of main";
		if(n->kind.stmt==FORK)return "stmt:for";
		if(n->kind.stmt==NULLK)return "nullstmt:semi";
	}
	else if(kind==EXPK){
		if(n->kind.exp==OPK){
			return "op:"+getOp(n->attri.op);
		}
		else if(n->kind.exp==CONSTK){
			return "const:"+getVal(n);
		}
		else if(n->kind.exp==IDK){
			return "symbol: "+n->attri.name;
		}
	}
	else{
		return "error type";
	}
}

TreeNode*makenodeT(TreeNode*f,TreeNode*s,OpType op);
TreeNode*makenodeS(TreeNode*t,OpType op);
string getCSinfo(int a,int b,int c,int d){
	string s="children:";
	if(a!=-1)s=s+getstring(a)+" , ";
	if(b!=-1)s=s+getstring(b)+" , ";
	if(c!=-1)s=s+getstring(c)+" , ";
	s+=" sibling: ";
	if(d!=-1)s+=getstring(d);
	return s;
}
string getTypeCode(TreeNode*s){
	int code=0;
	if(s->exptype){
		return s->exptype->code22();
	}
	else return "------";
}
	
int i=0;
int overTree(TreeNode*s){
	if(s==NULL)return -1;
	int a=overTree(s->child[0]);
	int b=overTree(s->child[1]);
	int c=overTree(s->child[2]);
	int d=overTree(s->sibling);
//	cout.setf(ios::left);
//	cout<<i<<":"<<setw(8)<<getType(s)<<setw(24)<<getTypeCode(s)<<setw(25)<<getInfo(s)<<setw(45)<<getCSinfo(a,b,c,d)<<endl;
	trout.setf(ios::left);
	trout<<i<<":"<<setw(8)<<getType(s)<<setw(24)<<getTypeCode(s)<<setw(25)<<getInfo(s)<<setw(45)<<getCSinfo(a,b,c,d)<<endl;
//	cout<<"return"<<i<<endl;
	return i++;
}




#line 228 "myparser.cpp"
// repeated because of possible precompiled header
#include <yycpars.h>

// namespaces
#ifdef YYSTDCPPLIB
using namespace std;
#endif
#ifdef YYNAMESPACE
using namespace yl;
#endif

#include ".\myparser.h"

/////////////////////////////////////////////////////////////////////////////
// constructor

YYPARSERNAME::YYPARSERNAME()
{
	yytables();
#line 205 ".\\myparser.y"

	// place any extra initialisation code here

#line 252 "myparser.cpp"
}

/////////////////////////////////////////////////////////////////////////////
// destructor

YYPARSERNAME::~YYPARSERNAME()
{
	// allows virtual functions to be called properly for correct cleanup
	yydestroy();
#line 210 ".\\myparser.y"

	// place any extra cleanup code here

#line 266 "myparser.cpp"
}

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#ifndef YYSTACK_SIZE
#define YYSTACK_SIZE 100
#endif
#ifndef YYSTACK_MAX
#define YYSTACK_MAX 0
#endif

/****************************************************************************
* N O T E
* 
* If the compiler generates a YYPARSERNAME error then you have not declared
* the name of the parser. The easiest way to do this is to use a name
* declaration. This is placed in the declarations section of your YACC
* source file and is introduced with the %name keyword. For instance, the
* following name declaration declares the parser myparser:
* 
* %name myparser
* 
* For more information see help.
****************************************************************************/

// yyattribute
#ifdef YYDEBUG
void YYFAR* YYPARSERNAME::yyattribute1(int index) const
{
	YYSTYPE YYFAR* p = &((YYSTYPE YYFAR*)yyattributestackptr)[yytop + index];
	return p;
}
#define yyattribute(index) (*(YYSTYPE YYFAR*)yyattribute1(index))
#else
#define yyattribute(index) (((YYSTYPE YYFAR*)yyattributestackptr)[yytop + (index)])
#endif

void YYPARSERNAME::yystacktoval(int index)
{
	yyassert(index >= 0);
	*(YYSTYPE YYFAR*)yyvalptr = ((YYSTYPE YYFAR*)yyattributestackptr)[index];
}

void YYPARSERNAME::yyvaltostack(int index)
{
	yyassert(index >= 0);
	((YYSTYPE YYFAR*)yyattributestackptr)[index] = *(YYSTYPE YYFAR*)yyvalptr;
}

void YYPARSERNAME::yylvaltoval()
{
	*(YYSTYPE YYFAR*)yyvalptr = *(YYSTYPE YYFAR*)yylvalptr;
}

void YYPARSERNAME::yyvaltolval()
{
	*(YYSTYPE YYFAR*)yylvalptr = *(YYSTYPE YYFAR*)yyvalptr;
}

void YYPARSERNAME::yylvaltostack(int index)
{
	yyassert(index >= 0);
	((YYSTYPE YYFAR*)yyattributestackptr)[index] = *(YYSTYPE YYFAR*)yylvalptr;
}

void YYFAR* YYPARSERNAME::yynewattribute(int count)
{
	yyassert(count >= 0);
	return new YYFAR YYSTYPE[count];
}

void YYPARSERNAME::yydeleteattribute(void YYFAR* attribute)
{
	delete[] (YYSTYPE YYFAR*)attribute;
}

void YYPARSERNAME::yycopyattribute(void YYFAR* dest, const void YYFAR* src, int count)
{
	for (int i = 0; i < count; i++) {
		((YYSTYPE YYFAR*)dest)[i] = ((YYSTYPE YYFAR*)src)[i];
	}
}

#ifdef YYDEBUG
void YYPARSERNAME::yyinitdebug(void YYFAR** p, int count) const
{
	yyassert(p != NULL);
	yyassert(count >= 1);

	YYSTYPE YYFAR** p1 = (YYSTYPE YYFAR**)p;
	for (int i = 0; i < count; i++) {
		p1[i] = &((YYSTYPE YYFAR*)yyattributestackptr)[yytop + i - (count - 1)];
	}
}
#endif

void YYPARSERNAME::yyaction(int action)
{
	switch (action) {
	case 0:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 284 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);startnode=(*(YYSTYPE YYFAR*)yyvalptr);cout<<"start1"<<endl;
#line 376 "myparser.cpp"
			}
		}
		break;
	case 1:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 285 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(STARTK);
						(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 2);
						(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(2 - 2);
						//结合代码
						(*(YYSTYPE YYFAR*)yyvalptr)->midcode=Fcodes::combinecode(yyattribute(1 - 2)->midcode,yyattribute(2 - 2)->midecode);
						//---
						startnode=(*(YYSTYPE YYFAR*)yyvalptr);
						
						cout<<"start 2"<<endl;
#line 397 "myparser.cpp"
			}
		}
		break;
	case 2:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 300 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 410 "myparser.cpp"
			}
		}
		break;
	case 3:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 302 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 423 "myparser.cpp"
			}
		}
		break;
	case 4:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 303 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 436 "myparser.cpp"
			}
		}
		break;
	case 5:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 304 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 449 "myparser.cpp"
			}
		}
		break;
	case 6:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 309 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newTypeNode(INTK);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CINT);nowattri=INTK;nowcode=CINT;
#line 462 "myparser.cpp"
			}
		}
		break;
	case 7:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 310 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newTypeNode(CHARK);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CCHAR);nowattri=CHARK;nowcode=CCHAR;
#line 475 "myparser.cpp"
			}
		}
		break;
	case 8:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 311 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newTypeNode(FLOATK);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CFLOAT);nowattri=FLOATK;nowcode=CFLOAT;
#line 488 "myparser.cpp"
			}
		}
		break;
	case 9:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 312 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newTypeNode(VOIDK);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CVOID);nowattri=VOIDK;nowcode=CVOID;
#line 501 "myparser.cpp"
			}
		}
		break;
	case 10:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 317 ".\\myparser.y"

					//添加类型
					yyattribute(3 - 3)->exptype=new CType(nowcode);
					if(nowcode==CCLASS)yyattribute(3 - 3)->exptype->cname=nowclass;
					Node*addr=allsymbol.top()->findexist(yyattribute(3 - 3)->attri.name);
					if(addr==NULL){
						Node*n=new Node("ID",yyattribute(3 - 3)->attri.name);
						n->setType(yyattribute(3 - 3)->exptype);
						addr=allsymbol.top()->insert(n);
						cout<<yyattribute(3 - 3)->attri.name<<":my addr is:"<<allsymbol.top()<<" : "<<addr<<endl;
					}
					else rout<<"  redefine at line :"<<lineno<<" symbol:"<<yyattribute(3 - 3)->attri.name<<endl;
					addr->attri=nowattri;
					if(nowattri==NOTK)addr->classname=nowclass;
					(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(3 - 3);
					yyattribute(3 - 3)->sibling=yyattribute(1 - 3);
					//可能的中阿锦代码的设置
					(*(YYSTYPE YYFAR*)yyvalptr)->midcode=yyattribute(1 - 3)->midcode;
					
				
#line 533 "myparser.cpp"
			}
		}
		break;
	case 11:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 337 ".\\myparser.y"
	//cout<<"hhh"<<endl;
					//添加类型
					yyattribute(1 - 1)->exptype=new CType(nowcode);
					if(nowcode==CCLASS)yyattribute(1 - 1)->exptype->cname=nowclass;
					
					Node*addr=allsymbol.top()->findexist(yyattribute(1 - 1)->attri.name);
					if(addr==NULL){
						Node *n=new Node("ID",yyattribute(1 - 1)->attri.name);
						n->setType(yyattribute(1 - 1)->exptype);
						addr=allsymbol.top()->insert(n);
						cout<<yyattribute(1 - 1)->attri.name<<":my addr is:"<<allsymbol.top()<<" : "<<addr<<endl;
					}
					else rout<<"  redefine at line :"<<lineno<<" symbol:"<<yyattribute(1 - 1)->attri.name<<endl;
					
					addr->attri=nowattri;
					if(nowattri==NOTK)addr->classname=nowclass;
					(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
					//不可能有中间代码
					
					
#line 565 "myparser.cpp"
			}
		}
		break;
	case 12:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 358 ".\\myparser.y"

					//类型检查：这里的类型检查就不拖到语法树建立完成了
					yyattribute(3 - 5)->exptype=new CType(nowcode);
					if(nowcode==CCLASS)yyattribute(3 - 5)->exptype->cname=nowclass;
					//checkEqual($3->exptype,$5->exptype);
					Node*addr=allsymbol.top()->findexist(yyattribute(3 - 5)->attri.name);
					if(addr==NULL){
						Node*n=new Node("ID",yyattribute(3 - 5)->attri.name);
						n->setType(yyattribute(3 - 5)->exptype);
						addr=allsymbol.top()->insert(n);
						cout<<yyattribute(3 - 5)->attri.name<<":my addr is:"<<allsymbol.top()<<" : "<<addr<<endl;
					}
					else rout<<"  redefine at line :"<<lineno<<" symbol:"<<yyattribute(3 - 5)->attri.name<<endl;
					addr->attri=nowattri;
					if(nowattri==NOTK)addr->classname=nowclass;
					TreeNode*tmp=newExpNode(OPK);
					tmp->attri.op=EQUEK;
					(*(YYSTYPE YYFAR*)yyvalptr)=tmp;
					tmp->child[0]=yyattribute(3 - 5);
					tmp->child[1]=yyattribute(5 - 5);
					(*(YYSTYPE YYFAR*)yyvalptr)->sibling=yyattribute(1 - 5);	
					//设置中间代码：（赋值语句）
					(*(YYSTYPE YYFAR*)yyvalptr)->
					
					
#line 602 "myparser.cpp"
			}
		}
		break;
	case 13:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 383 ".\\myparser.y"

					//类型检查：这里的类型检查就不拖到语法树建立完成了
					yyattribute(1 - 3)->exptype=new CType(nowcode);
					if(nowcode==CCLASS)yyattribute(1 - 3)->exptype->cname=nowclass;
					//checkEqual($1->exptype,$3->exptype);
					Node*addr=allsymbol.top()->findexist(yyattribute(1 - 3)->attri.name);
					if(addr==NULL){
						Node*n=new Node("ID",yyattribute(1 - 3)->attri.name);
						n->setType(yyattribute(1 - 3)->exptype);
						addr=allsymbol.top()->insert(n);
						cout<<yyattribute(1 - 3)->attri.name<<":my addr is:"<<allsymbol.top()<<" : "<<addr<<endl;
					}
					else rout<<"  redefine at line :"<<lineno<<" symbol:"<<yyattribute(1 - 3)->attri.name<<endl;
					addr->attri=nowattri;
					if(nowattri==NOTK)addr->classname=nowclass;
					TreeNode*tmp=newExpNode(OPK);
					tmp->attri.op=EQUEK;
					(*(YYSTYPE YYFAR*)yyvalptr)=tmp;
					tmp->child[0]=yyattribute(1 - 3);
					tmp->child[1]=yyattribute(3 - 3);
				
							
						
#line 637 "myparser.cpp"
			}
		}
		break;
	case 14:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 408 ".\\myparser.y"

						//添加类型
					yyattribute(4 - 4)->exptype=CType::pointer(new CType(nowcode));
					if(nowcode==CCLASS)yyattribute(4 - 4)->exptype->cname=nowclass;
					Node*addr=allsymbol.top()->findexist(yyattribute(4 - 4)->attri.name);
					if(addr==NULL){
						Node*n=new Node("ID",yyattribute(4 - 4)->attri.name);
						n->setType(yyattribute(4 - 4)->exptype);
						addr=allsymbol.top()->insert(n);
						cout<<yyattribute(4 - 4)->attri.name<<":my addr is:"<<allsymbol.top()<<" : "<<addr<<endl;
					}
					else rout<<"  redefine at line :"<<lineno<<" symbol:"<<yyattribute(4 - 4)->attri.name<<endl;
					addr->attri=((nowattri==INTK ? INTSK:(nowattri==CHARK ?CHARSK:(nowattri==FLOATK ? FLOATSK:NOTK))));
					if(nowattri==NOTK)addr->classname=nowclass;
					TreeNode*tmp=newExpNode(OPK);
					tmp->attri.op=GETCONTENTK;
					(*(YYSTYPE YYFAR*)yyvalptr)=tmp;
					tmp->child[0]=yyattribute(4 - 4);
					(*(YYSTYPE YYFAR*)yyvalptr)->sibling=yyattribute(1 - 4);
				//	cout<<"???"<<endl;
				
					
					
#line 672 "myparser.cpp"
			}
		}
		break;
	case 15:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 432 ".\\myparser.y"

					//添加类型
					yyattribute(3 - 6)->exptype=CType::array0(yyattribute(5 - 6)->attri.val,new CType(nowcode));
					if(nowcode==CCLASS)yyattribute(3 - 6)->exptype->cname=nowclass;
					Node*addr=allsymbol.top()->findexist(yyattribute(3 - 6)->attri.name);
					if(addr==NULL){
						Node*n=new Node("ID",yyattribute(3 - 6)->attri.name);
						n->setType(yyattribute(3 - 6)->exptype);
						addr=allsymbol.top()->insert(n);
						cout<<yyattribute(3 - 6)->attri.name<<":my addr is:"<<allsymbol.top()<<" : "<<addr<<endl;
					}
					else rout<<"  redefine at line :"<<lineno<<" symbol:"<<yyattribute(3 - 6)->attri.name<<endl;
					TreeNode*tmp=newExpNode(OPK);
					addr->attri=((nowattri==INTK ? INTSK:(nowattri==CHARK ?CHARSK:(nowattri==FLOATK ? FLOATSK:NOTK))));
					if(nowattri==NOTK)addr->classname=nowclass;
					tmp->attri.op=ARRAYCK;
					(*(YYSTYPE YYFAR*)yyvalptr)=tmp;
					tmp->child[0]=yyattribute(3 - 6);
					tmp->child[1]=yyattribute(5 - 6);
					(*(YYSTYPE YYFAR*)yyvalptr)->sibling=yyattribute(1 - 6);
					
						
#line 706 "myparser.cpp"
			}
		}
		break;
	case 16:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 454 ".\\myparser.y"

					//添加类型
					yyattribute(2 - 2)->exptype=CType::pointer(new CType(nowcode));
					if(nowcode==CCLASS)yyattribute(2 - 2)->exptype->cname=nowclass;
					
					Node*addr=allsymbol.top()->findexist(yyattribute(2 - 2)->attri.name);
					if(addr==NULL){
						Node*n=new Node("ID",yyattribute(2 - 2)->attri.name);
						n->setType(yyattribute(2 - 2)->exptype);
						addr=allsymbol.top()->insert(n);
						cout<<yyattribute(2 - 2)->attri.name<<":my addr is:"<<allsymbol.top()<<" : "<<addr<<endl;
					}
					else rout<<"  redefine at line :"<<lineno<<" symbol:"<<yyattribute(2 - 2)->attri.name<<endl;
					TreeNode*tmp=newExpNode(OPK);
					addr->attri=((nowattri==INTK ? INTSK:(nowattri==CHARK ?CHARSK:(nowattri==FLOATK ? FLOATSK:NOTK))));
					if(nowattri==NOTK)addr->classname=nowclass;
					tmp->attri.op=GETCONTENTK;
					(*(YYSTYPE YYFAR*)yyvalptr)=tmp;
					tmp->child[0]=yyattribute(2 - 2);//cout<<"???"<<endl;
					
					
#line 739 "myparser.cpp"
			}
		}
		break;
	case 17:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 476 ".\\myparser.y"

					//添加类型
					yyattribute(1 - 4)->exptype=CType::array0(yyattribute(3 - 4)->attri.val,new CType(nowcode));
					if(nowcode==CCLASS)yyattribute(1 - 4)->exptype->cname=nowclass;
					
					Node*addr=allsymbol.top()->findexist(yyattribute(1 - 4)->attri.name);
					if(addr==NULL){
						Node*n=new Node("ID",yyattribute(1 - 4)->attri.name);
						n->setType(yyattribute(1 - 4)->exptype);
						addr=allsymbol.top()->insert(n);
						cout<<yyattribute(1 - 4)->attri.name<<":my addr is:"<<allsymbol.top()<<" : "<<addr<<endl;
					}
					else rout<<"  redefine at line :"<<lineno<<" symbol:"<<yyattribute(1 - 4)->attri.name<<endl;
					TreeNode*tmp=newExpNode(OPK);
					addr->attri=((nowattri==INTK ? INTSK:(nowattri==CHARK ?CHARSK:(nowattri==FLOATK ? FLOATSK:NOTK))));
					if(nowattri==NOTK)addr->classname=nowclass;
					tmp->attri.op=ARRAYCK;
					(*(YYSTYPE YYFAR*)yyvalptr)=tmp;
					tmp->child[0]=yyattribute(1 - 4);
					tmp->child[1]=yyattribute(3 - 4);
					
						
#line 773 "myparser.cpp"
			}
		}
		break;
	case 18:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 501 ".\\myparser.y"
lastt->sibling=yyattribute(3 - 3);lastt=yyattribute(3 - 3);(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 3);
#line 786 "myparser.cpp"
			}
		}
		break;
	case 19:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 502 ".\\myparser.y"
lastt=yyattribute(1 - 1);(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 799 "myparser.cpp"
			}
		}
		break;
	case 20:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 508 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(BASEK);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(2 - 3);
					//cout<<"basetype:"<<$1->type<<$2->nodekind<<endl;
					//类型
					
				
#line 819 "myparser.cpp"
			}
		}
		break;
	case 21:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 516 ".\\myparser.y"

		//ID可能是在类表里面，也可能不在
		//语法分析部分不做判断
					(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(BASEK);
					string name=yyattribute(1 - 3)->attri.name;
//					delete $1;
					//$1=newTypeNode(NOTK,name);
					yyattribute(1 - 3)->nodekind=TYPEK;
					yyattribute(1 - 3)->type=NOTK;
					yyattribute(1 - 3)->classname=name;
					(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(2 - 3);
				
#line 844 "myparser.cpp"
			}
		}
		break;
	case 22:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 531 ".\\myparser.y"
nowattri=NOTK;nowcode=CCLASS;nowclass=yyattribute(1 - 1)->attri.name;(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 857 "myparser.cpp"
			}
		}
		break;
	case 23:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 538 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(2 - 4),DELETEK);
#line 870 "myparser.cpp"
			}
		}
		break;
	case 24:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 541 ".\\myparser.y"

			int count=0;
			if(findfexist(allsymbol,yyattribute(1 - 1)->attri.name,count)==NULL){
				rout<<"error undefined symbol:"<<yyattribute(1 - 1)->attri.name<<" at line:"<<lineno<<endl;
				yyattribute(1 - 1)->exptype=new CType(CVOID);
			}
			(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
		
#line 890 "myparser.cpp"
			}
		}
		break;
	case 25:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 550 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),CLASSMCK);
#line 903 "myparser.cpp"
			}
		}
		break;
	case 26:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 551 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(2 - 2),GETCONTENTK);
#line 916 "myparser.cpp"
			}
		}
		break;
	case 27:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 553 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 4),yyattribute(3 - 4),ARRAYCK);
#line 929 "myparser.cpp"
			}
		}
		break;
	case 28:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 554 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(2 - 2),ALGCTADDPK);
#line 942 "myparser.cpp"
			}
		}
		break;
	case 29:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 555 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(2 - 2),ALGCTMINUSPK);
#line 955 "myparser.cpp"
			}
		}
		break;
	case 30:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 556 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(2 - 3);
#line 968 "myparser.cpp"
			}
		}
		break;
	case 31:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 557 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),POINTK);
#line 981 "myparser.cpp"
			}
		}
		break;
	case 32:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 560 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),ALGCADDK);
#line 994 "myparser.cpp"
			}
		}
		break;
	case 33:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 561 ".\\myparser.y"
 (*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),ALGCMINUSK); 
#line 1007 "myparser.cpp"
			}
		}
		break;
	case 34:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 562 ".\\myparser.y"
 (*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),ALGCMULK); 
#line 1020 "myparser.cpp"
			}
		}
		break;
	case 35:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 563 ".\\myparser.y"
 (*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),ALGCDIVK); 
#line 1033 "myparser.cpp"
			}
		}
		break;
	case 36:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 564 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),ALGCMODK);
#line 1046 "myparser.cpp"
			}
		}
		break;
	case 37:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 566 ".\\myparser.y"
 (*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(2 - 3);
#line 1059 "myparser.cpp"
			}
		}
		break;
	case 38:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 567 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(2 - 2),UMINUSK);
#line 1072 "myparser.cpp"
			}
		}
		break;
	case 39:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 569 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CINT);
#line 1085 "myparser.cpp"
			}
		}
		break;
	case 40:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 570 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CINT);
#line 1098 "myparser.cpp"
			}
		}
		break;
	case 41:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 571 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CFLOAT);
#line 1111 "myparser.cpp"
			}
		}
		break;
	case 42:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 572 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CSTRING);
#line 1124 "myparser.cpp"
			}
		}
		break;
	case 43:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 573 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CCHAR);
#line 1137 "myparser.cpp"
			}
		}
		break;
	case 44:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 576 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(1 - 2),ALGCTADDBK);
#line 1150 "myparser.cpp"
			}
		}
		break;
	case 45:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 577 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(1 - 2),ALGCTMINUSBK);
#line 1163 "myparser.cpp"
			}
		}
		break;
	case 46:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 578 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(2 - 2),LGCCNK);
#line 1176 "myparser.cpp"
			}
		}
		break;
	case 47:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 579 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(2 - 2),BTCNK);
#line 1189 "myparser.cpp"
			}
		}
		break;
	case 48:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 580 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),BTCRIGHTK);
#line 1202 "myparser.cpp"
			}
		}
		break;
	case 49:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 581 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),BTCLEFTK);
#line 1215 "myparser.cpp"
			}
		}
		break;
	case 50:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 582 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),LGCCMOREEQK);
#line 1228 "myparser.cpp"
			}
		}
		break;
	case 51:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 583 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),LGCCLESSEQK);
#line 1241 "myparser.cpp"
			}
		}
		break;
	case 52:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 584 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),LGCCLESSK);
#line 1254 "myparser.cpp"
			}
		}
		break;
	case 53:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 585 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),LGCCMOREK);
#line 1267 "myparser.cpp"
			}
		}
		break;
	case 54:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 586 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),LGCCEQK);
#line 1280 "myparser.cpp"
			}
		}
		break;
	case 55:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 587 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),LGCCNK);
#line 1293 "myparser.cpp"
			}
		}
		break;
	case 56:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 588 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),BTCANDK);
#line 1306 "myparser.cpp"
			}
		}
		break;
	case 57:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 589 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),BTCORK);
#line 1319 "myparser.cpp"
			}
		}
		break;
	case 58:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 590 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),BTCYHK);
#line 1332 "myparser.cpp"
			}
		}
		break;
	case 59:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 591 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),LGCCANDK);
#line 1345 "myparser.cpp"
			}
		}
		break;
	case 60:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 592 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),LGCCORK);
#line 1358 "myparser.cpp"
			}
		}
		break;
	case 61:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 595 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 4),yyattribute(3 - 4),FUNCK);
#line 1371 "myparser.cpp"
			}
		}
		break;
	case 62:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 596 ".\\myparser.y"
TreeNode*t=makenodeT(yyattribute(3 - 6),yyattribute(5 - 6),FUNCK);(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 6),t,CLASSMCK);
#line 1384 "myparser.cpp"
			}
		}
		break;
	case 63:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 597 ".\\myparser.y"
TreeNode*t=makenodeT(yyattribute(3 - 6),yyattribute(5 - 6),FUNCK);(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 6),t,CLASSMCK);
#line 1397 "myparser.cpp"
			}
		}
		break;
	case 64:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 599 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(1 - 3),FUNCK);
#line 1410 "myparser.cpp"
			}
		}
		break;
	case 65:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 600 ".\\myparser.y"
TreeNode*t=makenodeS(yyattribute(3 - 5),FUNCK);(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 5),t,CLASSMCK);
#line 1423 "myparser.cpp"
			}
		}
		break;
	case 66:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 601 ".\\myparser.y"
TreeNode*t=makenodeS(yyattribute(3 - 5),FUNCK);(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 5),t,CLASSMCK);
#line 1436 "myparser.cpp"
			}
		}
		break;
	case 67:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 603 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),EQUEK);
#line 1449 "myparser.cpp"
			}
		}
		break;
	case 68:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 607 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(2 - 2),GETADDRK);
#line 1462 "myparser.cpp"
			}
		}
		break;
	case 69:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 626 ".\\myparser.y"

			(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(RETURNK);
			(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(2 - 3);
			
		
#line 1479 "myparser.cpp"
			}
		}
		break;
	case 70:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 634 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(EXPSK);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 2);;
#line 1492 "myparser.cpp"
			}
		}
		break;
	case 71:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 635 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(EXPSK);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=NULL;rout<<"error at line:"<<lineno<<" missing rbracess"<<endl;
#line 1505 "myparser.cpp"
			}
		}
		break;
	case 72:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 636 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 1518 "myparser.cpp"
			}
		}
		break;
	case 73:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 643 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(NULLK);
#line 1531 "myparser.cpp"
			}
		}
		break;
	case 74:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 649 ".\\myparser.y"

			if(cstlastt.top()!=NULL){
				cstlastt.top()->sibling=yyattribute(2 - 2);
				cstlastt.pop();
				cstlastt.push(yyattribute(2 - 2)) ;
			}
//			else if(comlastt==NULL)comlastt=$2;
			else {
				cstlastt.top()->sibling=yyattribute(2 - 2);
				cstlastt.pop();
				cstlastt.push(yyattribute(2 - 2));
			}
			(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 2);
			
#line 1557 "myparser.cpp"
			}
		}
		break;
	case 75:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 663 ".\\myparser.y"

			cstlastt.top()->sibling=yyattribute(2 - 2);cstlastt.pop();cstlastt.push(yyattribute(2 - 2));(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 2);
			
#line 1572 "myparser.cpp"
			}
		}
		break;
	case 76:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 666 ".\\myparser.y"
cstlastt.pop();cstlastt.push(yyattribute(1 - 1));(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 1585 "myparser.cpp"
			}
		}
		break;
	case 77:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 667 ".\\myparser.y"
cstlastt.pop();cstlastt.push(yyattribute(1 - 1));(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 1598 "myparser.cpp"
			}
		}
		break;
	case 78:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 673 ".\\myparser.y"

				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(COMSTMTK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 4);
				cstlastt.pop();
			
#line 1615 "myparser.cpp"
			}
		}
		break;
	case 79:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 683 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(COMSTMTK);cstlastt.pop();
#line 1628 "myparser.cpp"
			}
		}
		break;
	case 80:
		{
#line 696 ".\\myparser.y"
TreeNode*lat;cstlastt.push(lat);
#line 1636 "myparser.cpp"
		}
		break;
	case 81:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 707 ".\\myparser.y"

				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(IFK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 7);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 7);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=yyattribute(7 - 7);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
			
#line 1655 "myparser.cpp"
			}
		}
		break;
	case 82:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 716 ".\\myparser.y"

				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(IFK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 5);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 5);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
			
#line 1674 "myparser.cpp"
			}
		}
		break;
	case 83:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 723 ".\\myparser.y"

				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(IFK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 7);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 7);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=yyattribute(7 - 7);
				rout<<"error at line:"<<lineno<<" missing ')'"<<endl;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
			
#line 1695 "myparser.cpp"
			}
		}
		break;
	case 84:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 733 ".\\myparser.y"

				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(IFK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 5);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 5);
				rout<<"error at line:"<<lineno<<" missing ')'"<<endl;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
	
#line 1715 "myparser.cpp"
			}
		}
		break;
	case 85:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 744 ".\\myparser.y"

				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(WHILEK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 5);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 5);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
			
#line 1734 "myparser.cpp"
			}
		}
		break;
	case 86:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 751 ".\\myparser.y"

				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(WHILEK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 5);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 5);
				rout<<"error at line:"<<lineno<<" missing ')'"<<endl;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
			
#line 1754 "myparser.cpp"
			}
		}
		break;
	case 87:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[10];
			yyinitdebug((void YYFAR**)yya, 10);
#endif
			{
#line 761 ".\\myparser.y"


				TreeNode*t=newStmtsNode(FOREK);
				t->child[0]=yyattribute(3 - 9);
				t->child[1]=yyattribute(5 - 9);
				t->child[2]=yyattribute(7 - 9);
				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FORK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=t;
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(9 - 9);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();

#line 1778 "myparser.cpp"
			}
		}
		break;
	case 88:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[9];
			yyinitdebug((void YYFAR**)yya, 9);
#endif
			{
#line 773 ".\\myparser.y"

				TreeNode*t=newStmtsNode(FOREK);
				t->child[0]=yyattribute(3 - 8);
				t->child[1]=yyattribute(5 - 8);
				t->child[2]=NULL;
				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FORK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=t;
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(8 - 8);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();

#line 1801 "myparser.cpp"
			}
		}
		break;
	case 89:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[9];
			yyinitdebug((void YYFAR**)yya, 9);
#endif
			{
#line 784 ".\\myparser.y"

				TreeNode*t=newStmtsNode(FOREK);
				t->child[0]=yyattribute(3 - 8);
				t->child[1]=NULL;
				t->child[2]=yyattribute(6 - 8);
				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FORK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=t;
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(8 - 8);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();

#line 1824 "myparser.cpp"
			}
		}
		break;
	case 90:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[9];
			yyinitdebug((void YYFAR**)yya, 9);
#endif
			{
#line 795 ".\\myparser.y"

				TreeNode*t=newStmtsNode(FOREK);
				t->child[0]=NULL;
				t->child[1]=yyattribute(4 - 8);
				t->child[2]=yyattribute(6 - 8);
				
				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FORK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=t;
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(8 - 8);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();

#line 1848 "myparser.cpp"
			}
		}
		break;
	case 91:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 807 ".\\myparser.y"

				TreeNode*t=newStmtsNode(FOREK);
				t->child[0]=yyattribute(3 - 7);
				
				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FORK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=t;
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(7 - 7);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();

#line 1870 "myparser.cpp"
			}
		}
		break;
	case 92:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 817 ".\\myparser.y"

				TreeNode*t=newStmtsNode(FOREK);
				//$$->child[0]=$1;
				t->child[1]=yyattribute(4 - 7);
				
				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FORK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=t;
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(7 - 7);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();

#line 1893 "myparser.cpp"
			}
		}
		break;
	case 93:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 828 ".\\myparser.y"

				TreeNode*t=newStmtsNode(FOREK);
				//$$->child[0]=$1;
				//$$->child[1]=$3;
				t->child[2]=yyattribute(5 - 7);
				
				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FORK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=t;
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(7 - 7);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();

#line 1917 "myparser.cpp"
			}
		}
		break;
	case 94:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 840 ".\\myparser.y"

				TreeNode*t=newStmtsNode(FOREK);
				
				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FORK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=t;
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(6 - 6);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();

#line 1938 "myparser.cpp"
			}
		}
		break;
	case 95:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 855 ".\\myparser.y"

			(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 3);
			lastt->sibling=yyattribute(3 - 3);
			lastt=yyattribute(3 - 3);

#line 1955 "myparser.cpp"
			}
		}
		break;
	case 96:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 860 ".\\myparser.y"

			(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(2 - 2);
			lastt=(*(YYSTYPE YYFAR*)yyvalptr);
		
	
#line 1972 "myparser.cpp"
			}
		}
		break;
	case 97:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 866 ".\\myparser.y"

			(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(COUTK);
			(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(2 - 3);

#line 1988 "myparser.cpp"
			}
		}
		break;
	case 98:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 871 ".\\myparser.y"

			(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 3);
			lastt->sibling=yyattribute(3 - 3);
			lastt=yyattribute(3 - 3);
	

#line 2006 "myparser.cpp"
			}
		}
		break;
	case 99:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 877 ".\\myparser.y"

			(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(2 - 2);
			lastt=(*(YYSTYPE YYFAR*)yyvalptr);	
	
#line 2022 "myparser.cpp"
			}
		}
		break;
	case 100:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 882 ".\\myparser.y"

			(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(CINK);
			(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(2 - 3);

#line 2038 "myparser.cpp"
			}
		}
		break;
	case 101:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 891 ".\\myparser.y"

		ExpType type=yyattribute(1 - 2)->type;
		ExpType nt=(type==INTK ?INTSK:(type==CHARK ?CHARSK:FLOATSK));
		
		
		
		yyattribute(1 - 2)->type=nt;
		(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 2);
		//类型
		(*(YYSTYPE YYFAR*)yyvalptr)->exptype=CType::pointer(yyattribute(1 - 2)->exptype);
	
#line 2061 "myparser.cpp"
			}
		}
		break;
	case 102:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 905 ".\\myparser.y"

		TreeNode*t=newStmtsNode(BASEK);
		t->child[0]=yyattribute(3 - 4);
		t->child[1]=yyattribute(4 - 4);
		(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 4);
		lastt->sibling=t;
		lastt=t;

#line 2081 "myparser.cpp"
			}
		}
		break;
	case 103:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 913 ".\\myparser.y"

			TreeNode*t=newStmtsNode(BASEK);
			TreeNode*te=newExpNode(OPK);
			te->attri.op=ARRAYCK;
			te->child[0]=yyattribute(4 - 7);
			te->child[1]=yyattribute(6 - 7);
			t->child[0]=yyattribute(3 - 7);
			t->child[1]=te;
			lastt->sibling=t;
			(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 7);
			lastt=t;
	
#line 2105 "myparser.cpp"
			}
		}
		break;
	case 104:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 926 ".\\myparser.y"

			TreeNode*t=newStmtsNode(BASEK);
			t->child[0]=yyattribute(1 - 2);
			t->child[1]=yyattribute(2 - 2);
			(*(YYSTYPE YYFAR*)yyvalptr)=t;
			lastt=t;
	
#line 2124 "myparser.cpp"
			}
		}
		break;
	case 105:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 933 ".\\myparser.y"

			TreeNode*t=newStmtsNode(BASEK);
			TreeNode*te=newExpNode(OPK);
			te->attri.op=ARRAYCK;
			te->child[0]=yyattribute(2 - 5);
			te->child[1]=yyattribute(4 - 5);
			t->child[0]=yyattribute(1 - 5);
			t->child[1]=te;
			lastt=t;	

#line 2146 "myparser.cpp"
			}
		}
		break;
	case 106:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 966 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FUNCDK);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 6);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(2 - 6);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=yyattribute(4 - 6);
					(*(YYSTYPE YYFAR*)yyvalptr)->sibling=yyattribute(6 - 6);
					if(funcmap.find(yyattribute(2 - 6)->attri.name)!=funcmap.end())rout<<"error at line :"<<lineno<<"redefined func:"<<yyattribute(2 - 6)->attri.name<<endl; 
					else{
						Node*n=new Node("FUNC",yyattribute(2 - 6)->attri.name);
						n->setType(yyattribute(1 - 6)->exptype);
						funcmap[yyattribute(2 - 6)->attri.name]=n;//$$;
						cout<<yyattribute(2 - 6)->attri.name<<":my addr is:"<<funcmap[yyattribute(2 - 6)->attri.name]<<endl;
					}
					

#line 2173 "myparser.cpp"
			}
		}
		break;
	case 107:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 981 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FUNCDK);
					ExpType type=((yyattribute(1 - 7)->type==INTK ? INTSK:(yyattribute(1 - 7)->type==CHARK ? CHARSK:FLOATSK)));
					TreeNode*tmp=newTypeNode(type);
					delete yyattribute(1 - 7);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=tmp;
					(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 7);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=yyattribute(5 - 7);
					(*(YYSTYPE YYFAR*)yyvalptr)->sibling=yyattribute(7 - 7);
					if(funcmap.find(yyattribute(3 - 7)->attri.name)!=funcmap.end())rout<<"error at line :"<<lineno<<"redefined func:"<<yyattribute(3 - 7)->attri.name<<endl; 
					else{
						Node*n=new Node("FUNC",yyattribute(3 - 7)->attri.name);
						n->setType(yyattribute(1 - 7)->exptype);
						funcmap[yyattribute(3 - 7)->attri.name]=n;//$$;
						cout<<yyattribute(3 - 7)->attri.name<<":my addr is:"<<funcmap[yyattribute(3 - 7)->attri.name]<<endl;
					}

#line 2202 "myparser.cpp"
			}
		}
		break;
	case 108:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 998 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FUNCDK);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 5);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(2 - 5);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=NULL;
					(*(YYSTYPE YYFAR*)yyvalptr)->sibling=yyattribute(5 - 5);
					//cout<<($$->sibling==NULL)<<"the func's sibling is null?"<<endl;
					if(funcmap.find(yyattribute(2 - 5)->attri.name)!=funcmap.end())rout<<"error at line :"<<lineno<<" redefined func:"<<yyattribute(2 - 5)->attri.name<<endl; 
					else{
						Node*n=new Node("FUNC",yyattribute(2 - 5)->attri.name);
						n->setType(yyattribute(1 - 5)->exptype);
						funcmap[yyattribute(2 - 5)->attri.name]=n;//$$;
						cout<<yyattribute(2 - 5)->attri.name<<":my addr is:"<<funcmap[yyattribute(2 - 5)->attri.name]<<endl;
					}
	
	
#line 2230 "myparser.cpp"
			}
		}
		break;
	case 109:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 1014 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FUNCDK);
					ExpType type=((yyattribute(1 - 6)->type==INTK ? INTSK:(yyattribute(1 - 6)->type==CHARK ? CHARSK:FLOATSK)));
					TreeNode*tmp=newTypeNode(type);
					delete yyattribute(1 - 6);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=tmp;
					(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 6);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=NULL;
					(*(YYSTYPE YYFAR*)yyvalptr)->sibling=yyattribute(6 - 6);
					if(funcmap.find(yyattribute(3 - 6)->attri.name)!=funcmap.end())rout<<"error at line :"<<lineno<<" redefined func:"<<yyattribute(3 - 6)->attri.name<<endl; 
					else{
						Node*n=new Node("FUNC",yyattribute(3 - 6)->attri.name);
						n->setType(yyattribute(1 - 6)->exptype);
						funcmap[yyattribute(3 - 6)->attri.name]=n;//$$;
						cout<<yyattribute(3 - 6)->attri.name<<":my addr is:"<<funcmap[yyattribute(3 - 6)->attri.name]<<endl;
					}

#line 2259 "myparser.cpp"
			}
		}
		break;
	case 110:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 1035 ".\\myparser.y"

		(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(MAINK);
		(*(YYSTYPE YYFAR*)yyvalptr)->type=INTK;
		(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=newTypeNode(INTK);
		(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 5);
	
#line 2277 "myparser.cpp"
			}
		}
		break;
	case 111:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 1042 ".\\myparser.y"

			(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(MAINK);
		(*(YYSTYPE YYFAR*)yyvalptr)->type=INTK;
		(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=newTypeNode(INTK);
		(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 5);
		rout<<"error at line :"<<lineno<<" missing ')'"<<endl;
		
#line 2296 "myparser.cpp"
			}
		}
		break;
	case 112:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 1068 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 2);lastt->sibling=yyattribute(2 - 2);lastt=yyattribute(2 - 2);
#line 2309 "myparser.cpp"
			}
		}
		break;
	case 113:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 1071 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 2);lastt->sibling=yyattribute(2 - 2);lastt=yyattribute(2 - 2);
#line 2322 "myparser.cpp"
			}
		}
		break;
	case 114:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 1072 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);lastt=(*(YYSTYPE YYFAR*)yyvalptr);
#line 2335 "myparser.cpp"
			}
		}
		break;
	case 115:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 1074 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);lastt=(*(YYSTYPE YYFAR*)yyvalptr);
#line 2348 "myparser.cpp"
			}
		}
		break;
	case 116:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 1077 ".\\myparser.y"

		(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(CLASSK);
		if(classmap.find(yyattribute(2 - 6)->attri.name)!=classmap.end())
			rout<<"error at line:"<<lineno<<"   redefine of class:"<<yyattribute(2 - 6)->attri.name<<endl;
			
		else{
			classmap[yyattribute(2 - 6)->attri.name]=new ClassNode(yyattribute(2 - 6)->attri.name);
			cout<<yyattribute(2 - 6)->attri.name<<":my addr :"<<classmap[yyattribute(2 - 6)->attri.name]<<endl;	
		}
		
		(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(2 - 6);
		(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(4 - 6);
		//类型
		(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(yyattribute(2 - 6)->attri.name);
		//$$->w
		//其他的都会在自己的basetypestmt里面有自己的类型的编码。
		//关于ID声明变量
	
#line 2378 "myparser.cpp"
			}
		}
		break;
	default:
		yyassert(0);
		break;
	}
}

void YYPARSERNAME::yytables()
{
	yyattribute_size = sizeof(YYSTYPE);
	yysstack_size = YYSTACK_SIZE;
	yystack_max = YYSTACK_MAX;

#ifdef YYDEBUG
	static const yysymbol_t YYNEARFAR YYBASED_CODE symbol[] = {
		{ "$end", 0 },
		{ "error", 256 },
		{ "ALGCADD", 257 },
		{ "ALGCMINUS", 258 },
		{ "ALGCMUL", 259 },
		{ "ALGCDIV", 260 },
		{ "ALGCMOD", 261 },
		{ "ALGCTADD", 262 },
		{ "ALGCTMINUS", 263 },
		{ "NUMBERD", 264 },
		{ "DIGIT", 265 },
		{ "STRING", 266 },
		{ "ONECHAR", 267 },
		{ "FLOATD", 268 },
		{ "LBRACESS", 269 },
		{ "RBRACESS", 270 },
		{ "EQ", 271 },
		{ "INT", 272 },
		{ "FLOAT", 273 },
		{ "CHAR", 274 },
		{ "VOID", 275 },
		{ "IF", 276 },
		{ "ELSE", 277 },
		{ "WHILE", 278 },
		{ "FOR", 279 },
		{ "MAIN", 280 },
		{ "COUT", 282 },
		{ "CIN", 283 },
		{ "CLASS", 285 },
		{ "RETURN", 293 },
		{ "LBRACE", 294 },
		{ "RBRACE", 295 },
		{ "LBRACEM", 296 },
		{ "RBRACEM", 297 },
		{ "LBRACES", 298 },
		{ "RBRACES", 299 },
		{ "SEMI", 300 },
		{ "COMMA", 301 },
		{ "POINT", 302 },
		{ "LGCCEQ", 306 },
		{ "LGCCLESSEQ", 307 },
		{ "LGCCMOREEQ", 308 },
		{ "LGCCNEQ", 309 },
		{ "LGCCAND", 310 },
		{ "LGCCOR", 311 },
		{ "LGCCN", 312 },
		{ "BTCYH", 313 },
		{ "BTCOR", 314 },
		{ "BTCAND", 315 },
		{ "BTCLEFT", 316 },
		{ "BTCRIGHT", 317 },
		{ "BTCN", 318 },
		{ "ID", 319 },
		{ "CLASSMC", 320 },
		{ "DELETE", 323 },
		{ "LGCCMORE", 325 },
		{ "LGCCLESS", 326 },
		{ "UMINUS", 327 },
		{ "GETADDR", 328 },
		{ "GETCONTENT", 329 },
		{ "ALGCTADDP", 330 },
		{ "ALGCTMINUSP", 331 },
		{ "ALGCTADDB", 332 },
		{ "ALGCTMINUSB", 333 },
		{ "FUNCUSE", 334 },
		{ "ARRAYC", 335 },
		{ NULL, 0 }
	};
	yysymbol = symbol;

	static const char* const YYNEARFAR YYBASED_CODE rule[] = {
		"$accept: start",
		"start: startinfo",
		"start: start startinfo",
		"startinfo: classdef",
		"startinfo: basetypestmt",
		"startinfo: funcdef",
		"startinfo: funcdefmain",
		"basetype: INT",
		"basetype: CHAR",
		"basetype: FLOAT",
		"basetype: VOID",
		"idlistwithvar: idlistwithvar COMMA ID",
		"idlistwithvar: ID",
		"idlistwithvar: idlistwithvar COMMA ID EQ expr",
		"idlistwithvar: ID EQ expr",
		"idlistwithvar: idlistwithvar COMMA ALGCMUL ID",
		"idlistwithvar: idlistwithvar COMMA ID LBRACEM NUMBERD RBRACEM",
		"idlistwithvar: ALGCMUL ID",
		"idlistwithvar: ID LBRACEM NUMBERD RBRACEM",
		"exprlist: exprlist COMMA expr",
		"exprlist: expr",
		"basetypestmt: basetype idlistwithvar SEMI",
		"basetypestmt: among idlistwithvar SEMI",
		"among: ID",
		"expr: valueexpr",
		"expr: calexpr",
		"expr: DELETE valueexpr LBRACEM RBRACEM",
		"valueexpr: ID",
		"valueexpr: valueexpr CLASSMC valueexpr",
		"valueexpr: ALGCMUL valueexpr",
		"valueexpr: valueexpr LBRACEM expr RBRACEM",
		"valueexpr: ALGCTADD valueexpr",
		"valueexpr: ALGCTMINUS valueexpr",
		"valueexpr: LBRACESS valueexpr RBRACESS",
		"valueexpr: valueexpr POINT valueexpr",
		"calexpr: expr ALGCADD expr",
		"calexpr: expr ALGCMINUS expr",
		"calexpr: expr ALGCMUL expr",
		"calexpr: expr ALGCDIV expr",
		"calexpr: expr ALGCMOD expr",
		"calexpr: LBRACESS calexpr RBRACESS",
		"calexpr: ALGCMINUS expr",
		"calexpr: NUMBERD",
		"calexpr: DIGIT",
		"calexpr: FLOATD",
		"calexpr: STRING",
		"calexpr: ONECHAR",
		"calexpr: valueexpr ALGCTADD",
		"calexpr: valueexpr ALGCTMINUS",
		"calexpr: LGCCN expr",
		"calexpr: BTCN expr",
		"calexpr: expr BTCRIGHT expr",
		"calexpr: expr BTCLEFT expr",
		"calexpr: expr LGCCMOREEQ expr",
		"calexpr: expr LGCCLESSEQ expr",
		"calexpr: expr LBRACES expr",
		"calexpr: expr RBRACES expr",
		"calexpr: expr LGCCEQ expr",
		"calexpr: expr LGCCNEQ expr",
		"calexpr: expr BTCAND expr",
		"calexpr: expr BTCOR expr",
		"calexpr: expr BTCYH expr",
		"calexpr: expr LGCCAND expr",
		"calexpr: expr LGCCOR expr",
		"calexpr: ID LBRACESS exprlist RBRACESS",
		"calexpr: valueexpr CLASSMC ID LBRACESS exprlist RBRACESS",
		"calexpr: valueexpr POINT ID LBRACESS exprlist RBRACESS",
		"calexpr: ID LBRACESS RBRACESS",
		"calexpr: valueexpr CLASSMC ID LBRACESS RBRACESS",
		"calexpr: valueexpr POINT ID LBRACESS RBRACESS",
		"calexpr: expr EQ expr",
		"calexpr: BTCAND expr",
		"returnstmt: RETURN expr SEMI",
		"stmt: expr SEMI",
		"stmt: LBRACESS error SEMI",
		"stmt: basetypestmt",
		"stmt: ifstmt",
		"stmt: whilestmt",
		"stmt: forstmt",
		"stmt: cinstmt",
		"stmt: coutstmt",
		"stmt: returnstmt",
		"stmt: SEMI",
		"cstmtlist: cstmtlist comstmt",
		"cstmtlist: cstmtlist stmt",
		"cstmtlist: comstmt",
		"cstmtlist: stmt",
		"comstmt: LBRACE midum cstmtlist RBRACE",
		"comstmt: LBRACE midum RBRACE",
		"midum:",
		"stmtcomstmt: stmt",
		"stmtcomstmt: comstmt",
		"ifstmt: IF LBRACESS expr RBRACESS stmtcomstmt ELSE stmtcomstmt",
		"ifstmt: IF LBRACESS expr RBRACESS stmtcomstmt",
		"ifstmt: IF LBRACESS expr error stmtcomstmt ELSE stmtcomstmt",
		"ifstmt: IF LBRACESS expr error stmtcomstmt",
		"whilestmt: WHILE LBRACESS expr RBRACESS stmtcomstmt",
		"whilestmt: WHILE LBRACESS expr error stmtcomstmt",
		"forstmt: FOR LBRACESS expr SEMI expr SEMI expr RBRACESS stmtcomstmt",
		"forstmt: FOR LBRACESS expr SEMI expr SEMI RBRACESS stmtcomstmt",
		"forstmt: FOR LBRACESS expr SEMI SEMI expr RBRACESS stmtcomstmt",
		"forstmt: FOR LBRACESS SEMI expr SEMI expr RBRACESS stmtcomstmt",
		"forstmt: FOR LBRACESS expr SEMI SEMI RBRACESS stmtcomstmt",
		"forstmt: FOR LBRACESS SEMI expr SEMI RBRACESS stmtcomstmt",
		"forstmt: FOR LBRACESS SEMI SEMI expr RBRACESS stmtcomstmt",
		"forstmt: FOR LBRACESS SEMI SEMI RBRACESS stmtcomstmt",
		"coutlist: coutlist BTCLEFT expr",
		"coutlist: BTCLEFT expr",
		"coutstmt: COUT coutlist SEMI",
		"cinlist: cinlist BTCRIGHT valueexpr",
		"cinlist: BTCRIGHT valueexpr",
		"cinstmt: CIN cinlist SEMI",
		"typep: basetype",
		"typep: basetype ALGCMUL",
		"typeidlist: typeidlist COMMA typep ID",
		"typeidlist: typeidlist COMMA typep ID LBRACEM NUMBERD RBRACEM",
		"typeidlist: typep ID",
		"typeidlist: typep ID LBRACEM NUMBERD RBRACEM",
		"funcdef: basetype ID LBRACESS typeidlist RBRACESS comstmt",
		"funcdef: basetype ALGCMUL ID LBRACESS typeidlist RBRACESS comstmt",
		"funcdef: basetype ID LBRACESS RBRACESS comstmt",
		"funcdef: basetype ALGCMUL ID LBRACESS RBRACESS comstmt",
		"funcdefmain: INT MAIN LBRACESS RBRACESS comstmt",
		"funcdefmain: INT MAIN LBRACESS error comstmt",
		"inclass: inclass basetypestmt",
		"inclass: inclass funcdef",
		"inclass: basetypestmt",
		"inclass: funcdef",
		"classdef: CLASS ID LBRACE inclass RBRACE SEMI"
	};
	yyrule = rule;
#endif

	static const yyreduction_t YYNEARFAR YYBASED_CODE reduction[] = {
		{ 0, 1, -1 },
		{ 1, 1, 0 },
		{ 1, 2, 1 },
		{ 2, 1, 2 },
		{ 2, 1, 3 },
		{ 2, 1, 4 },
		{ 2, 1, 5 },
		{ 3, 1, 6 },
		{ 3, 1, 7 },
		{ 3, 1, 8 },
		{ 3, 1, 9 },
		{ 4, 3, 10 },
		{ 4, 1, 11 },
		{ 4, 5, 12 },
		{ 4, 3, 13 },
		{ 4, 4, 14 },
		{ 4, 6, 15 },
		{ 4, 2, 16 },
		{ 4, 4, 17 },
		{ 5, 3, 18 },
		{ 5, 1, 19 },
		{ 6, 3, 20 },
		{ 6, 3, 21 },
		{ 7, 1, 22 },
		{ 8, 1, -1 },
		{ 8, 1, -1 },
		{ 8, 4, 23 },
		{ 9, 1, 24 },
		{ 9, 3, 25 },
		{ 9, 2, 26 },
		{ 9, 4, 27 },
		{ 9, 2, 28 },
		{ 9, 2, 29 },
		{ 9, 3, 30 },
		{ 9, 3, 31 },
		{ 10, 3, 32 },
		{ 10, 3, 33 },
		{ 10, 3, 34 },
		{ 10, 3, 35 },
		{ 10, 3, 36 },
		{ 10, 3, 37 },
		{ 10, 2, 38 },
		{ 10, 1, 39 },
		{ 10, 1, 40 },
		{ 10, 1, 41 },
		{ 10, 1, 42 },
		{ 10, 1, 43 },
		{ 10, 2, 44 },
		{ 10, 2, 45 },
		{ 10, 2, 46 },
		{ 10, 2, 47 },
		{ 10, 3, 48 },
		{ 10, 3, 49 },
		{ 10, 3, 50 },
		{ 10, 3, 51 },
		{ 10, 3, 52 },
		{ 10, 3, 53 },
		{ 10, 3, 54 },
		{ 10, 3, 55 },
		{ 10, 3, 56 },
		{ 10, 3, 57 },
		{ 10, 3, 58 },
		{ 10, 3, 59 },
		{ 10, 3, 60 },
		{ 10, 4, 61 },
		{ 10, 6, 62 },
		{ 10, 6, 63 },
		{ 10, 3, 64 },
		{ 10, 5, 65 },
		{ 10, 5, 66 },
		{ 10, 3, 67 },
		{ 10, 2, 68 },
		{ 11, 3, 69 },
		{ 12, 2, 70 },
		{ 12, 3, 71 },
		{ 12, 1, 72 },
		{ 12, 1, -1 },
		{ 12, 1, -1 },
		{ 12, 1, -1 },
		{ 12, 1, -1 },
		{ 12, 1, -1 },
		{ 12, 1, -1 },
		{ 12, 1, 73 },
		{ 13, 2, 74 },
		{ 13, 2, 75 },
		{ 13, 1, 76 },
		{ 13, 1, 77 },
		{ 14, 4, 78 },
		{ 14, 3, 79 },
		{ 15, 0, 80 },
		{ 16, 1, -1 },
		{ 16, 1, -1 },
		{ 17, 7, 81 },
		{ 17, 5, 82 },
		{ 17, 7, 83 },
		{ 17, 5, 84 },
		{ 18, 5, 85 },
		{ 18, 5, 86 },
		{ 19, 9, 87 },
		{ 19, 8, 88 },
		{ 19, 8, 89 },
		{ 19, 8, 90 },
		{ 19, 7, 91 },
		{ 19, 7, 92 },
		{ 19, 7, 93 },
		{ 19, 6, 94 },
		{ 20, 3, 95 },
		{ 20, 2, 96 },
		{ 21, 3, 97 },
		{ 22, 3, 98 },
		{ 22, 2, 99 },
		{ 23, 3, 100 },
		{ 24, 1, -1 },
		{ 24, 2, 101 },
		{ 25, 4, 102 },
		{ 25, 7, 103 },
		{ 25, 2, 104 },
		{ 25, 5, 105 },
		{ 26, 6, 106 },
		{ 26, 7, 107 },
		{ 26, 5, 108 },
		{ 26, 6, 109 },
		{ 27, 5, 110 },
		{ 27, 5, 111 },
		{ 28, 2, 112 },
		{ 28, 2, 113 },
		{ 28, 1, 114 },
		{ 28, 1, 115 },
		{ 29, 6, 116 }
	};
	yyreduction = reduction;

	yytokenaction_size = 548;

	static const yytokenaction_t YYNEARFAR YYBASED_CODE tokenaction[] = {
		{ 7, YYAT_ACCEPT, 0 },
		{ 268, YYAT_SHIFT, 93 },
		{ 268, YYAT_SHIFT, 94 },
		{ 268, YYAT_SHIFT, 95 },
		{ 268, YYAT_SHIFT, 96 },
		{ 268, YYAT_SHIFT, 97 },
		{ 147, YYAT_SHIFT, 93 },
		{ 147, YYAT_SHIFT, 94 },
		{ 147, YYAT_SHIFT, 95 },
		{ 147, YYAT_SHIFT, 96 },
		{ 147, YYAT_SHIFT, 97 },
		{ 65, YYAT_SHIFT, 119 },
		{ 258, YYAT_SHIFT, 266 },
		{ 217, YYAT_SHIFT, 232 },
		{ 268, YYAT_SHIFT, 272 },
		{ 268, YYAT_SHIFT, 98 },
		{ 225, YYAT_SHIFT, 46 },
		{ 214, YYAT_SHIFT, 229 },
		{ 73, YYAT_SHIFT, 124 },
		{ 225, YYAT_SHIFT, 47 },
		{ 225, YYAT_SHIFT, 48 },
		{ 210, YYAT_SHIFT, 93 },
		{ 210, YYAT_SHIFT, 94 },
		{ 210, YYAT_SHIFT, 95 },
		{ 210, YYAT_SHIFT, 96 },
		{ 210, YYAT_SHIFT, 97 },
		{ 225, YYAT_SHIFT, 80 },
		{ 217, YYAT_SHIFT, 233 },
		{ 146, YYAT_SHIFT, 93 },
		{ 146, YYAT_SHIFT, 94 },
		{ 146, YYAT_SHIFT, 95 },
		{ 146, YYAT_SHIFT, 96 },
		{ 146, YYAT_SHIFT, 97 },
		{ 216, YYAT_SHIFT, 230 },
		{ 172, YYAT_REDUCE, 23 },
		{ 210, YYAT_SHIFT, 98 },
		{ 65, YYAT_SHIFT, 120 },
		{ 175, YYAT_SHIFT, 21 },
		{ 31, YYAT_SHIFT, 64 },
		{ 13, YYAT_SHIFT, 18 },
		{ 238, YYAT_SHIFT, 114 },
		{ 256, YYAT_SHIFT, 264 },
		{ 268, YYAT_SHIFT, 99 },
		{ 268, YYAT_SHIFT, 100 },
		{ 172, YYAT_SHIFT, 91 },
		{ 250, YYAT_SHIFT, 259 },
		{ 238, YYAT_SHIFT, 129 },
		{ 216, YYAT_SHIFT, 231 },
		{ 214, YYAT_SHIFT, 189 },
		{ 73, YYAT_SHIFT, 77 },
		{ 268, YYAT_SHIFT, 101 },
		{ 268, YYAT_SHIFT, 102 },
		{ 268, YYAT_SHIFT, 103 },
		{ 268, YYAT_SHIFT, 104 },
		{ 268, YYAT_SHIFT, 105 },
		{ 268, YYAT_SHIFT, 106 },
		{ 249, YYAT_SHIFT, 257 },
		{ 268, YYAT_SHIFT, 107 },
		{ 268, YYAT_SHIFT, 108 },
		{ 268, YYAT_SHIFT, 109 },
		{ 268, YYAT_SHIFT, 110 },
		{ 268, YYAT_SHIFT, 111 },
		{ 210, YYAT_SHIFT, 99 },
		{ 210, YYAT_SHIFT, 100 },
		{ 238, YYAT_SHIFT, 130 },
		{ 147, YYAT_SHIFT, 110 },
		{ 147, YYAT_SHIFT, 111 },
		{ 61, YYAT_SHIFT, 112 },
		{ 61, YYAT_SHIFT, 113 },
		{ 248, YYAT_SHIFT, 255 },
		{ 210, YYAT_SHIFT, 101 },
		{ 210, YYAT_SHIFT, 102 },
		{ 210, YYAT_SHIFT, 103 },
		{ 210, YYAT_SHIFT, 104 },
		{ 210, YYAT_SHIFT, 105 },
		{ 210, YYAT_SHIFT, 106 },
		{ 225, YYAT_SHIFT, 81 },
		{ 210, YYAT_SHIFT, 107 },
		{ 210, YYAT_SHIFT, 108 },
		{ 210, YYAT_SHIFT, 109 },
		{ 210, YYAT_SHIFT, 110 },
		{ 210, YYAT_SHIFT, 111 },
		{ 161, YYAT_SHIFT, 93 },
		{ 161, YYAT_SHIFT, 94 },
		{ 161, YYAT_SHIFT, 95 },
		{ 161, YYAT_SHIFT, 96 },
		{ 161, YYAT_SHIFT, 97 },
		{ 146, YYAT_SHIFT, 110 },
		{ 146, YYAT_SHIFT, 111 },
		{ 144, YYAT_SHIFT, 93 },
		{ 144, YYAT_SHIFT, 94 },
		{ 144, YYAT_SHIFT, 95 },
		{ 144, YYAT_SHIFT, 96 },
		{ 144, YYAT_SHIFT, 97 },
		{ 172, YYAT_REDUCE, 23 },
		{ 128, YYAT_SHIFT, 131 },
		{ 161, YYAT_SHIFT, 98 },
		{ 175, YYAT_SHIFT, 22 },
		{ 31, YYAT_SHIFT, 65 },
		{ 13, YYAT_SHIFT, 19 },
		{ 92, YYAT_ERROR, 0 },
		{ 61, YYAT_SHIFT, 114 },
		{ 142, YYAT_SHIFT, 93 },
		{ 142, YYAT_SHIFT, 94 },
		{ 142, YYAT_SHIFT, 95 },
		{ 142, YYAT_SHIFT, 96 },
		{ 142, YYAT_SHIFT, 97 },
		{ 61, YYAT_SHIFT, 115 },
		{ 247, YYAT_SHIFT, 254 },
		{ 143, YYAT_SHIFT, 93 },
		{ 143, YYAT_SHIFT, 94 },
		{ 143, YYAT_SHIFT, 95 },
		{ 143, YYAT_SHIFT, 96 },
		{ 143, YYAT_SHIFT, 97 },
		{ 200, YYAT_SHIFT, 221 },
		{ 24, YYAT_SHIFT, 34 },
		{ 142, YYAT_SHIFT, 98 },
		{ 138, YYAT_SHIFT, 95 },
		{ 138, YYAT_SHIFT, 96 },
		{ 138, YYAT_SHIFT, 97 },
		{ 19, YYAT_SHIFT, 27 },
		{ 128, YYAT_SHIFT, 114 },
		{ 19, YYAT_SHIFT, 28 },
		{ 161, YYAT_SHIFT, 99 },
		{ 161, YYAT_SHIFT, 100 },
		{ 61, YYAT_SHIFT, 116 },
		{ 92, YYAT_SHIFT, 136 },
		{ 128, YYAT_SHIFT, 129 },
		{ 243, YYAT_SHIFT, 252 },
		{ 24, YYAT_SHIFT, 35 },
		{ 200, YYAT_SHIFT, 222 },
		{ 161, YYAT_SHIFT, 101 },
		{ 161, YYAT_SHIFT, 102 },
		{ 161, YYAT_SHIFT, 103 },
		{ 161, YYAT_SHIFT, 104 },
		{ 161, YYAT_SHIFT, 105 },
		{ 161, YYAT_SHIFT, 106 },
		{ 241, YYAT_SHIFT, 251 },
		{ 161, YYAT_SHIFT, 107 },
		{ 161, YYAT_SHIFT, 108 },
		{ 161, YYAT_SHIFT, 109 },
		{ 161, YYAT_SHIFT, 110 },
		{ 161, YYAT_SHIFT, 111 },
		{ 142, YYAT_SHIFT, 99 },
		{ 142, YYAT_SHIFT, 100 },
		{ 128, YYAT_SHIFT, 130 },
		{ 22, YYAT_SHIFT, 28 },
		{ 19, YYAT_SHIFT, 29 },
		{ 144, YYAT_SHIFT, 110 },
		{ 144, YYAT_SHIFT, 111 },
		{ 236, YYAT_SHIFT, 249 },
		{ 142, YYAT_SHIFT, 101 },
		{ 142, YYAT_SHIFT, 102 },
		{ 142, YYAT_SHIFT, 103 },
		{ 142, YYAT_SHIFT, 104 },
		{ 142, YYAT_SHIFT, 105 },
		{ 142, YYAT_SHIFT, 106 },
		{ 235, YYAT_SHIFT, 248 },
		{ 142, YYAT_SHIFT, 107 },
		{ 142, YYAT_SHIFT, 108 },
		{ 142, YYAT_SHIFT, 109 },
		{ 142, YYAT_SHIFT, 110 },
		{ 142, YYAT_SHIFT, 111 },
		{ 134, YYAT_SHIFT, 93 },
		{ 134, YYAT_SHIFT, 94 },
		{ 134, YYAT_SHIFT, 95 },
		{ 134, YYAT_SHIFT, 96 },
		{ 134, YYAT_SHIFT, 97 },
		{ 143, YYAT_SHIFT, 110 },
		{ 143, YYAT_SHIFT, 111 },
		{ 223, YYAT_SHIFT, 114 },
		{ 22, YYAT_SHIFT, 29 },
		{ 160, YYAT_SHIFT, 114 },
		{ 202, YYAT_SHIFT, 224 },
		{ 158, YYAT_SHIFT, 114 },
		{ 84, YYAT_SHIFT, 114 },
		{ 223, YYAT_SHIFT, 129 },
		{ 134, YYAT_SHIFT, 98 },
		{ 160, YYAT_SHIFT, 129 },
		{ 234, YYAT_SHIFT, 246 },
		{ 158, YYAT_SHIFT, 129 },
		{ 84, YYAT_SHIFT, 129 },
		{ 83, YYAT_SHIFT, 114 },
		{ 60, YYAT_SHIFT, 93 },
		{ 60, YYAT_SHIFT, 94 },
		{ 60, YYAT_SHIFT, 95 },
		{ 60, YYAT_SHIFT, 96 },
		{ 60, YYAT_SHIFT, 97 },
		{ 83, YYAT_SHIFT, 129 },
		{ 227, YYAT_SHIFT, 239 },
		{ 202, YYAT_SHIFT, 225 },
		{ 137, YYAT_SHIFT, 95 },
		{ 137, YYAT_SHIFT, 96 },
		{ 137, YYAT_SHIFT, 97 },
		{ 223, YYAT_SHIFT, 130 },
		{ 222, YYAT_ERROR, 0 },
		{ 160, YYAT_SHIFT, 130 },
		{ 60, YYAT_SHIFT, 98 },
		{ 158, YYAT_SHIFT, 130 },
		{ 84, YYAT_SHIFT, 130 },
		{ 23, YYAT_SHIFT, 33 },
		{ 23, YYAT_SHIFT, 31 },
		{ 82, YYAT_SHIFT, 114 },
		{ 219, YYAT_SHIFT, 236 },
		{ 134, YYAT_SHIFT, 99 },
		{ 134, YYAT_SHIFT, 100 },
		{ 83, YYAT_SHIFT, 130 },
		{ 218, YYAT_SHIFT, 234 },
		{ 82, YYAT_SHIFT, 129 },
		{ 212, YYAT_SHIFT, 228 },
		{ 208, YYAT_SHIFT, 227 },
		{ 203, YYAT_SHIFT, 226 },
		{ 134, YYAT_SHIFT, 101 },
		{ 134, YYAT_SHIFT, 102 },
		{ 134, YYAT_SHIFT, 103 },
		{ 134, YYAT_SHIFT, 104 },
		{ 134, YYAT_SHIFT, 105 },
		{ 134, YYAT_SHIFT, 106 },
		{ 198, YYAT_SHIFT, 218 },
		{ 134, YYAT_SHIFT, 107 },
		{ 134, YYAT_SHIFT, 108 },
		{ 134, YYAT_SHIFT, 109 },
		{ 134, YYAT_SHIFT, 110 },
		{ 134, YYAT_SHIFT, 111 },
		{ 60, YYAT_SHIFT, 99 },
		{ 60, YYAT_SHIFT, 100 },
		{ 82, YYAT_SHIFT, 130 },
		{ 155, YYAT_SHIFT, 93 },
		{ 155, YYAT_SHIFT, 94 },
		{ 155, YYAT_SHIFT, 95 },
		{ 155, YYAT_SHIFT, 96 },
		{ 155, YYAT_SHIFT, 97 },
		{ 60, YYAT_SHIFT, 101 },
		{ 60, YYAT_SHIFT, 102 },
		{ 60, YYAT_SHIFT, 103 },
		{ 60, YYAT_SHIFT, 104 },
		{ 60, YYAT_SHIFT, 105 },
		{ 60, YYAT_SHIFT, 106 },
		{ 195, YYAT_SHIFT, 215 },
		{ 60, YYAT_SHIFT, 107 },
		{ 60, YYAT_SHIFT, 108 },
		{ 60, YYAT_SHIFT, 109 },
		{ 60, YYAT_SHIFT, 110 },
		{ 60, YYAT_SHIFT, 111 },
		{ 193, YYAT_SHIFT, 213 },
		{ 237, YYAT_SHIFT, 93 },
		{ 237, YYAT_SHIFT, 94 },
		{ 237, YYAT_SHIFT, 95 },
		{ 237, YYAT_SHIFT, 96 },
		{ 237, YYAT_SHIFT, 97 },
		{ 154, YYAT_SHIFT, 93 },
		{ 154, YYAT_SHIFT, 94 },
		{ 154, YYAT_SHIFT, 95 },
		{ 154, YYAT_SHIFT, 96 },
		{ 154, YYAT_SHIFT, 97 },
		{ 77, YYAT_SHIFT, 36 },
		{ 77, YYAT_SHIFT, 2 },
		{ 77, YYAT_SHIFT, 3 },
		{ 77, YYAT_SHIFT, 4 },
		{ 237, YYAT_SHIFT, 98 },
		{ 192, YYAT_SHIFT, 211 },
		{ 187, YYAT_SHIFT, 209 },
		{ 186, YYAT_SHIFT, 208 },
		{ 184, YYAT_SHIFT, 205 },
		{ 173, YYAT_SHIFT, 204 },
		{ 220, YYAT_SHIFT, 93 },
		{ 220, YYAT_SHIFT, 94 },
		{ 220, YYAT_SHIFT, 95 },
		{ 220, YYAT_SHIFT, 96 },
		{ 220, YYAT_SHIFT, 97 },
		{ 168, YYAT_SHIFT, 201 },
		{ 167, YYAT_SHIFT, 199 },
		{ 7, YYAT_SHIFT, 1 },
		{ 166, YYAT_SHIFT, 198 },
		{ 165, YYAT_SHIFT, 197 },
		{ 164, YYAT_SHIFT, 196 },
		{ 163, YYAT_SHIFT, 195 },
		{ 162, YYAT_SHIFT, 194 },
		{ 159, YYAT_SHIFT, 193 },
		{ 220, YYAT_SHIFT, 98 },
		{ 157, YYAT_SHIFT, 192 },
		{ 156, YYAT_SHIFT, 191 },
		{ 136, YYAT_SHIFT, 190 },
		{ 135, YYAT_SHIFT, 188 },
		{ 127, YYAT_SHIFT, 187 },
		{ 7, YYAT_SHIFT, 5 },
		{ 237, YYAT_SHIFT, 99 },
		{ 237, YYAT_SHIFT, 100 },
		{ 150, YYAT_SHIFT, 93 },
		{ 150, YYAT_SHIFT, 94 },
		{ 150, YYAT_SHIFT, 95 },
		{ 150, YYAT_SHIFT, 96 },
		{ 150, YYAT_SHIFT, 97 },
		{ 126, YYAT_SHIFT, 186 },
		{ 237, YYAT_SHIFT, 101 },
		{ 237, YYAT_SHIFT, 102 },
		{ 237, YYAT_SHIFT, 103 },
		{ 237, YYAT_SHIFT, 104 },
		{ 237, YYAT_SHIFT, 105 },
		{ 237, YYAT_SHIFT, 106 },
		{ 124, YYAT_SHIFT, 66 },
		{ 237, YYAT_SHIFT, 107 },
		{ 237, YYAT_SHIFT, 108 },
		{ 237, YYAT_SHIFT, 109 },
		{ 121, YYAT_SHIFT, 170 },
		{ 237, YYAT_SHIFT, 111 },
		{ 220, YYAT_SHIFT, 99 },
		{ 220, YYAT_SHIFT, 100 },
		{ 149, YYAT_SHIFT, 93 },
		{ 149, YYAT_SHIFT, 94 },
		{ 149, YYAT_SHIFT, 95 },
		{ 149, YYAT_SHIFT, 96 },
		{ 149, YYAT_SHIFT, 97 },
		{ 120, YYAT_SHIFT, 162 },
		{ 220, YYAT_SHIFT, 101 },
		{ 220, YYAT_SHIFT, 102 },
		{ 220, YYAT_SHIFT, 103 },
		{ 220, YYAT_SHIFT, 104 },
		{ 220, YYAT_SHIFT, 105 },
		{ 220, YYAT_SHIFT, 106 },
		{ 116, YYAT_SHIFT, 159 },
		{ 220, YYAT_SHIFT, 107 },
		{ 220, YYAT_SHIFT, 108 },
		{ 220, YYAT_SHIFT, 109 },
		{ 115, YYAT_SHIFT, 157 },
		{ 220, YYAT_SHIFT, 111 },
		{ 91, YYAT_SHIFT, 133 },
		{ 87, YYAT_SHIFT, 132 },
		{ 85, YYAT_ERROR, 0 },
		{ 150, YYAT_SHIFT, 99 },
		{ 150, YYAT_SHIFT, 100 },
		{ 152, YYAT_SHIFT, 93 },
		{ 152, YYAT_SHIFT, 94 },
		{ 152, YYAT_SHIFT, 95 },
		{ 152, YYAT_SHIFT, 96 },
		{ 152, YYAT_SHIFT, 97 },
		{ 78, YYAT_SHIFT, 127 },
		{ 150, YYAT_SHIFT, 101 },
		{ 150, YYAT_SHIFT, 102 },
		{ 150, YYAT_SHIFT, 103 },
		{ 150, YYAT_SHIFT, 104 },
		{ 150, YYAT_SHIFT, 105 },
		{ 69, YYAT_SHIFT, 122 },
		{ 64, YYAT_SHIFT, 118 },
		{ 150, YYAT_SHIFT, 107 },
		{ 150, YYAT_SHIFT, 108 },
		{ 150, YYAT_SHIFT, 109 },
		{ 150, YYAT_SHIFT, 110 },
		{ 150, YYAT_SHIFT, 111 },
		{ 149, YYAT_SHIFT, 99 },
		{ 149, YYAT_SHIFT, 100 },
		{ 151, YYAT_SHIFT, 93 },
		{ 151, YYAT_SHIFT, 94 },
		{ 151, YYAT_SHIFT, 95 },
		{ 151, YYAT_SHIFT, 96 },
		{ 151, YYAT_SHIFT, 97 },
		{ 63, YYAT_SHIFT, 117 },
		{ 149, YYAT_SHIFT, 101 },
		{ 149, YYAT_SHIFT, 102 },
		{ 149, YYAT_SHIFT, 103 },
		{ 149, YYAT_SHIFT, 104 },
		{ 58, YYAT_SHIFT, 91 },
		{ 44, YYAT_SHIFT, 78 },
		{ 43, YYAT_SHIFT, 76 },
		{ 149, YYAT_SHIFT, 107 },
		{ 149, YYAT_SHIFT, 108 },
		{ 149, YYAT_SHIFT, 109 },
		{ 149, YYAT_SHIFT, 110 },
		{ 149, YYAT_SHIFT, 111 },
		{ 42, YYAT_SHIFT, 75 },
		{ 40, YYAT_SHIFT, 72 },
		{ 39, YYAT_SHIFT, 69 },
		{ 152, YYAT_SHIFT, 99 },
		{ 152, YYAT_SHIFT, 100 },
		{ 29, YYAT_SHIFT, 63 },
		{ 27, YYAT_SHIFT, 41 },
		{ 26, YYAT_SHIFT, 40 },
		{ 25, YYAT_SHIFT, 6 },
		{ 21, YYAT_SHIFT, 32 },
		{ 20, YYAT_SHIFT, 30 },
		{ 152, YYAT_SHIFT, 101 },
		{ 152, YYAT_SHIFT, 102 },
		{ 152, YYAT_SHIFT, 103 },
		{ 152, YYAT_SHIFT, 104 },
		{ 18, YYAT_SHIFT, 26 },
		{ 16, YYAT_SHIFT, 25 },
		{ 15, YYAT_SHIFT, 24 },
		{ 152, YYAT_SHIFT, 107 },
		{ 5, YYAT_SHIFT, 16 },
		{ 152, YYAT_SHIFT, 109 },
		{ 152, YYAT_SHIFT, 110 },
		{ 152, YYAT_SHIFT, 111 },
		{ 151, YYAT_SHIFT, 99 },
		{ 151, YYAT_SHIFT, 100 },
		{ 1, YYAT_SHIFT, 15 },
		{ 0, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 151, YYAT_SHIFT, 101 },
		{ 151, YYAT_SHIFT, 102 },
		{ 151, YYAT_SHIFT, 103 },
		{ 151, YYAT_SHIFT, 104 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 259, YYAT_SHIFT, 45 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 151, YYAT_SHIFT, 109 },
		{ 151, YYAT_SHIFT, 110 },
		{ 151, YYAT_SHIFT, 111 },
		{ 259, YYAT_SHIFT, 49 },
		{ 259, YYAT_SHIFT, 50 },
		{ 259, YYAT_SHIFT, 51 },
		{ 259, YYAT_SHIFT, 52 },
		{ 259, YYAT_SHIFT, 53 },
		{ 259, YYAT_SHIFT, 54 },
		{ 259, YYAT_SHIFT, 267 },
		{ 272, YYAT_SHIFT, 163 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 272, YYAT_SHIFT, 36 },
		{ 272, YYAT_SHIFT, 2 },
		{ 272, YYAT_SHIFT, 3 },
		{ 272, YYAT_SHIFT, 4 },
		{ 272, YYAT_SHIFT, 164 },
		{ -1, YYAT_ERROR, 0 },
		{ 272, YYAT_SHIFT, 165 },
		{ 272, YYAT_SHIFT, 166 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 272, YYAT_SHIFT, 167 },
		{ 272, YYAT_SHIFT, 168 },
		{ 153, YYAT_SHIFT, 93 },
		{ 153, YYAT_SHIFT, 94 },
		{ 153, YYAT_SHIFT, 95 },
		{ 153, YYAT_SHIFT, 96 },
		{ 153, YYAT_SHIFT, 97 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 272, YYAT_SHIFT, 169 },
		{ 272, YYAT_SHIFT, 66 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 272, YYAT_SHIFT, 171 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 148, YYAT_SHIFT, 93 },
		{ 148, YYAT_SHIFT, 94 },
		{ 148, YYAT_SHIFT, 95 },
		{ 148, YYAT_SHIFT, 96 },
		{ 148, YYAT_SHIFT, 97 },
		{ -1, YYAT_ERROR, 0 },
		{ 259, YYAT_SHIFT, 55 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 259, YYAT_SHIFT, 56 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 259, YYAT_SHIFT, 57 },
		{ 259, YYAT_SHIFT, 58 },
		{ -1, YYAT_ERROR, 0 },
		{ 272, YYAT_SHIFT, 172 },
		{ -1, YYAT_ERROR, 0 },
		{ 259, YYAT_SHIFT, 59 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 153, YYAT_SHIFT, 99 },
		{ 153, YYAT_SHIFT, 100 },
		{ 145, YYAT_SHIFT, 93 },
		{ 145, YYAT_SHIFT, 94 },
		{ 145, YYAT_SHIFT, 95 },
		{ 145, YYAT_SHIFT, 96 },
		{ 145, YYAT_SHIFT, 97 },
		{ -1, YYAT_ERROR, 0 },
		{ 153, YYAT_SHIFT, 101 },
		{ 153, YYAT_SHIFT, 102 },
		{ 153, YYAT_SHIFT, 103 },
		{ 153, YYAT_SHIFT, 104 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 86, YYAT_SHIFT, 112 },
		{ 86, YYAT_SHIFT, 113 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 153, YYAT_SHIFT, 110 },
		{ 153, YYAT_SHIFT, 111 },
		{ 148, YYAT_SHIFT, 99 },
		{ 148, YYAT_SHIFT, 100 },
		{ 86, YYAT_SHIFT, 131 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 148, YYAT_SHIFT, 102 },
		{ 148, YYAT_SHIFT, 103 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 148, YYAT_SHIFT, 110 },
		{ 148, YYAT_SHIFT, 111 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 145, YYAT_SHIFT, 99 },
		{ 145, YYAT_SHIFT, 100 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 86, YYAT_SHIFT, 114 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 145, YYAT_SHIFT, 102 },
		{ 145, YYAT_SHIFT, 103 },
		{ 86, YYAT_SHIFT, 115 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 145, YYAT_SHIFT, 110 },
		{ 145, YYAT_SHIFT, 111 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 86, YYAT_SHIFT, 116 }
	};
	yytokenaction = tokenaction;

	static const yystateaction_t YYNEARFAR YYBASED_CODE stateaction[] = {
		{ 395, 1, YYAT_DEFAULT, 7 },
		{ 114, 1, YYAT_REDUCE, 7 },
		{ 0, 0, YYAT_REDUCE, 9 },
		{ 0, 0, YYAT_REDUCE, 8 },
		{ 0, 0, YYAT_REDUCE, 10 },
		{ 69, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 23 },
		{ 0, 1, YYAT_DEFAULT, 25 },
		{ 0, 0, YYAT_REDUCE, 3 },
		{ 0, 0, YYAT_REDUCE, 5 },
		{ 0, 0, YYAT_REDUCE, 6 },
		{ 0, 0, YYAT_REDUCE, 1 },
		{ 0, 0, YYAT_REDUCE, 4 },
		{ -220, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 175 },
		{ 117, 1, YYAT_ERROR, 0 },
		{ 91, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 2 },
		{ 65, 1, YYAT_ERROR, 0 },
		{ -149, 1, YYAT_REDUCE, 12 },
		{ 79, 1, YYAT_DEFAULT, 23 },
		{ 59, 1, YYAT_ERROR, 0 },
		{ -125, 1, YYAT_REDUCE, 12 },
		{ -100, 1, YYAT_ERROR, 0 },
		{ -141, 1, YYAT_ERROR, 0 },
		{ 58, 1, YYAT_DEFAULT, 77 },
		{ 107, 1, YYAT_REDUCE, 17 },
		{ 105, 1, YYAT_DEFAULT, 77 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 110, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 21 },
		{ -221, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 17 },
		{ 0, 0, YYAT_REDUCE, 22 },
		{ 0, 0, YYAT_DEFAULT, 124 },
		{ 0, 0, YYAT_DEFAULT, 124 },
		{ 0, 0, YYAT_REDUCE, 7 },
		{ 0, 0, YYAT_REDUCE, 127 },
		{ 0, 0, YYAT_REDUCE, 126 },
		{ 76, 1, YYAT_DEFAULT, 25 },
		{ 100, 1, YYAT_DEFAULT, 77 },
		{ 0, 0, YYAT_DEFAULT, 124 },
		{ 110, 1, YYAT_REDUCE, 112 },
		{ 93, 1, YYAT_DEFAULT, 73 },
		{ 43, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 225 },
		{ 0, 0, YYAT_DEFAULT, 225 },
		{ 0, 0, YYAT_DEFAULT, 225 },
		{ 0, 0, YYAT_REDUCE, 42 },
		{ 0, 0, YYAT_REDUCE, 43 },
		{ 0, 0, YYAT_REDUCE, 45 },
		{ 0, 0, YYAT_REDUCE, 46 },
		{ 0, 0, YYAT_REDUCE, 44 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 92, 1, YYAT_REDUCE, 27 },
		{ 0, 0, YYAT_DEFAULT, 225 },
		{ -74, 1, YYAT_REDUCE, 14 },
		{ -195, 1, YYAT_REDUCE, 24 },
		{ 0, 0, YYAT_REDUCE, 25 },
		{ 59, 1, YYAT_ERROR, 0 },
		{ 24, 1, YYAT_ERROR, 0 },
		{ -260, 1, YYAT_REDUCE, 11 },
		{ 0, 0, YYAT_REDUCE, 89 },
		{ 0, 0, YYAT_REDUCE, 123 },
		{ 0, 0, YYAT_REDUCE, 122 },
		{ 42, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 125 },
		{ 0, 0, YYAT_REDUCE, 124 },
		{ 0, 0, YYAT_DEFAULT, 124 },
		{ -252, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 120 },
		{ 0, 0, YYAT_REDUCE, 113 },
		{ 0, 0, YYAT_DEFAULT, 124 },
		{ -17, 1, YYAT_ERROR, 0 },
		{ 40, 1, YYAT_REDUCE, 116 },
		{ 0, 0, YYAT_REDUCE, 41 },
		{ 0, 0, YYAT_DEFAULT, 225 },
		{ 0, 0, YYAT_REDUCE, 27 },
		{ -94, 1, YYAT_REDUCE, 29 },
		{ -114, 1, YYAT_REDUCE, 31 },
		{ -121, 1, YYAT_REDUCE, 32 },
		{ 58, 1, YYAT_DEFAULT, 268 },
		{ 227, 1, YYAT_REDUCE, 24 },
		{ 57, 1, YYAT_REDUCE, 25 },
		{ 0, 0, YYAT_REDUCE, 49 },
		{ 0, 0, YYAT_REDUCE, 71 },
		{ 0, 0, YYAT_REDUCE, 50 },
		{ 56, 1, YYAT_DEFAULT, 259 },
		{ -170, 1, YYAT_DEFAULT, 128 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_REDUCE, 47 },
		{ 0, 0, YYAT_REDUCE, 48 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 5, 1, YYAT_DEFAULT, 225 },
		{ 1, 1, YYAT_DEFAULT, 225 },
		{ 0, 0, YYAT_REDUCE, 18 },
		{ 0, 0, YYAT_REDUCE, 15 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 49, 1, YYAT_ERROR, 0 },
		{ 9, 1, YYAT_DEFAULT, 272 },
		{ 0, 0, YYAT_REDUCE, 128 },
		{ 0, 0, YYAT_REDUCE, 121 },
		{ 6, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 118 },
		{ -26, 1, YYAT_ERROR, 0 },
		{ 20, 1, YYAT_ERROR, 0 },
		{ -175, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 225 },
		{ 0, 0, YYAT_DEFAULT, 225 },
		{ 0, 0, YYAT_REDUCE, 33 },
		{ 0, 0, YYAT_REDUCE, 40 },
		{ 0, 0, YYAT_REDUCE, 67 },
		{ -94, 1, YYAT_REDUCE, 20 },
		{ 13, 1, YYAT_DEFAULT, 214 },
		{ -15, 1, YYAT_DEFAULT, 222 },
		{ -68, 1, YYAT_REDUCE, 35 },
		{ -142, 1, YYAT_REDUCE, 36 },
		{ 0, 0, YYAT_REDUCE, 37 },
		{ 0, 0, YYAT_REDUCE, 38 },
		{ 0, 0, YYAT_REDUCE, 39 },
		{ -155, 1, YYAT_REDUCE, 70 },
		{ -148, 1, YYAT_REDUCE, 55 },
		{ -168, 1, YYAT_REDUCE, 56 },
		{ 220, 1, YYAT_REDUCE, 57 },
		{ -229, 1, YYAT_REDUCE, 54 },
		{ -251, 1, YYAT_REDUCE, 53 },
		{ 197, 1, YYAT_REDUCE, 58 },
		{ 51, 1, YYAT_REDUCE, 62 },
		{ 31, 1, YYAT_REDUCE, 63 },
		{ 94, 1, YYAT_REDUCE, 61 },
		{ 74, 1, YYAT_REDUCE, 60 },
		{ 177, 1, YYAT_REDUCE, 59 },
		{ -7, 1, YYAT_REDUCE, 52 },
		{ -30, 1, YYAT_REDUCE, 51 },
		{ -16, 1, YYAT_DEFAULT, 85 },
		{ 11, 1, YYAT_REDUCE, 27 },
		{ -122, 1, YYAT_REDUCE, 34 },
		{ 9, 1, YYAT_REDUCE, 27 },
		{ -124, 1, YYAT_REDUCE, 28 },
		{ -175, 1, YYAT_REDUCE, 13 },
		{ -20, 1, YYAT_ERROR, 0 },
		{ 20, 1, YYAT_DEFAULT, 222 },
		{ 6, 1, YYAT_ERROR, 0 },
		{ 5, 1, YYAT_ERROR, 0 },
		{ 4, 1, YYAT_ERROR, 0 },
		{ -45, 1, YYAT_ERROR, 0 },
		{ -47, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_REDUCE, 88 },
		{ 0, 0, YYAT_REDUCE, 82 },
		{ -225, 1, YYAT_REDUCE, 27 },
		{ -36, 1, YYAT_DEFAULT, 250 },
		{ 0, 0, YYAT_REDUCE, 75 },
		{ -222, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 81 },
		{ 0, 0, YYAT_REDUCE, 86 },
		{ 0, 0, YYAT_REDUCE, 76 },
		{ 0, 0, YYAT_REDUCE, 77 },
		{ 0, 0, YYAT_REDUCE, 78 },
		{ 0, 0, YYAT_REDUCE, 79 },
		{ 0, 0, YYAT_REDUCE, 80 },
		{ 0, 0, YYAT_REDUCE, 85 },
		{ -32, 1, YYAT_DEFAULT, 272 },
		{ 0, 0, YYAT_REDUCE, 119 },
		{ -34, 1, YYAT_REDUCE, 114 },
		{ -36, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 64 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_REDUCE, 26 },
		{ 0, 0, YYAT_REDUCE, 30 },
		{ -10, 1, YYAT_DEFAULT, 259 },
		{ -26, 1, YYAT_DEFAULT, 259 },
		{ 0, 0, YYAT_REDUCE, 16 },
		{ -62, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ -82, 1, YYAT_DEFAULT, 236 },
		{ 0, 0, YYAT_DEFAULT, 222 },
		{ -186, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 225 },
		{ -127, 1, YYAT_ERROR, 0 },
		{ -89, 1, YYAT_DEFAULT, 250 },
		{ 0, 0, YYAT_REDUCE, 73 },
		{ 0, 0, YYAT_REDUCE, 87 },
		{ 0, 0, YYAT_REDUCE, 84 },
		{ 0, 0, YYAT_REDUCE, 83 },
		{ -54, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 117 },
		{ -236, 1, YYAT_REDUCE, 19 },
		{ 0, 0, YYAT_REDUCE, 69 },
		{ -61, 1, YYAT_DEFAULT, 214 },
		{ 0, 0, YYAT_REDUCE, 68 },
		{ -253, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 74 },
		{ -223, 1, YYAT_DEFAULT, 268 },
		{ -243, 1, YYAT_DEFAULT, 268 },
		{ -93, 1, YYAT_DEFAULT, 236 },
		{ -97, 1, YYAT_DEFAULT, 250 },
		{ 8, 1, YYAT_REDUCE, 107 },
		{ 0, 0, YYAT_REDUCE, 108 },
		{ -75, 1, YYAT_DEFAULT, 259 },
		{ -126, 1, YYAT_REDUCE, 110 },
		{ 0, 0, YYAT_REDUCE, 111 },
		{ -243, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 72 },
		{ -108, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 66 },
		{ 0, 0, YYAT_REDUCE, 65 },
		{ 0, 0, YYAT_DEFAULT, 272 },
		{ 0, 0, YYAT_DEFAULT, 272 },
		{ 0, 0, YYAT_DEFAULT, 272 },
		{ 0, 0, YYAT_DEFAULT, 272 },
		{ -91, 1, YYAT_DEFAULT, 259 },
		{ -143, 1, YYAT_DEFAULT, 250 },
		{ -150, 1, YYAT_DEFAULT, 222 },
		{ -12, 1, YYAT_REDUCE, 106 },
		{ -256, 1, YYAT_REDUCE, 109 },
		{ 0, 0, YYAT_REDUCE, 115 },
		{ 0, 0, YYAT_REDUCE, 90 },
		{ -140, 1, YYAT_REDUCE, 95 },
		{ 0, 0, YYAT_REDUCE, 91 },
		{ -149, 1, YYAT_REDUCE, 93 },
		{ 0, 0, YYAT_REDUCE, 97 },
		{ 0, 0, YYAT_REDUCE, 96 },
		{ 0, 0, YYAT_DEFAULT, 272 },
		{ -162, 1, YYAT_DEFAULT, 268 },
		{ -201, 1, YYAT_DEFAULT, 259 },
		{ -214, 1, YYAT_DEFAULT, 259 },
		{ -255, 1, YYAT_DEFAULT, 85 },
		{ 0, 0, YYAT_DEFAULT, 272 },
		{ 0, 0, YYAT_DEFAULT, 272 },
		{ 0, 0, YYAT_REDUCE, 105 },
		{ 0, 0, YYAT_DEFAULT, 272 },
		{ 0, 0, YYAT_DEFAULT, 272 },
		{ -229, 1, YYAT_DEFAULT, 268 },
		{ 0, 0, YYAT_DEFAULT, 272 },
		{ -258, 1, YYAT_DEFAULT, 268 },
		{ 148, 1, YYAT_DEFAULT, 225 },
		{ 0, 0, YYAT_REDUCE, 94 },
		{ 0, 0, YYAT_REDUCE, 92 },
		{ 0, 0, YYAT_REDUCE, 104 },
		{ 0, 0, YYAT_REDUCE, 103 },
		{ 0, 0, YYAT_DEFAULT, 272 },
		{ 0, 0, YYAT_REDUCE, 102 },
		{ 0, 0, YYAT_DEFAULT, 272 },
		{ 0, 0, YYAT_DEFAULT, 272 },
		{ -256, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 101 },
		{ 0, 0, YYAT_REDUCE, 100 },
		{ 0, 0, YYAT_REDUCE, 99 },
		{ 150, 1, YYAT_DEFAULT, 236 },
		{ 0, 0, YYAT_REDUCE, 98 }
	};
	yystateaction = stateaction;

	yynontermgoto_size = 119;

	static const yynontermgoto_t YYNEARFAR YYBASED_CODE nontermgoto[] = {
		{ 272, 175 },
		{ 267, 271 },
		{ 7, 17 },
		{ 272, 174 },
		{ 272, 14 },
		{ 272, 173 },
		{ 7, 12 },
		{ 77, 42 },
		{ 272, 176 },
		{ 272, 240 },
		{ 25, 38 },
		{ 272, 242 },
		{ 266, 270 },
		{ 272, 273 },
		{ 272, 178 },
		{ 272, 179 },
		{ 272, 180 },
		{ 264, 269 },
		{ 272, 182 },
		{ 39, 13 },
		{ 272, 181 },
		{ 193, 214 },
		{ 39, 71 },
		{ 39, 14 },
		{ 193, 134 },
		{ 257, 265 },
		{ 7, 9 },
		{ 7, 10 },
		{ 77, 126 },
		{ 7, 8 },
		{ 25, 37 },
		{ 184, 206 },
		{ 25, 39 },
		{ 184, 207 },
		{ 255, 263 },
		{ 184, -1 },
		{ 259, 268 },
		{ 259, 61 },
		{ 259, 62 },
		{ 163, 85 },
		{ 163, 86 },
		{ 163, 87 },
		{ 39, 70 },
		{ 121, 177 },
		{ 121, 184 },
		{ 121, 183 },
		{ 40, 44 },
		{ 40, 73 },
		{ 0, 7 },
		{ 0, 11 },
		{ 254, 262 },
		{ 252, 261 },
		{ 251, 260 },
		{ 249, 258 },
		{ 248, 256 },
		{ 246, 253 },
		{ 236, 250 },
		{ 234, 247 },
		{ 233, 245 },
		{ 232, 244 },
		{ 231, 243 },
		{ 230, 241 },
		{ 225, 238 },
		{ 222, 237 },
		{ 218, 235 },
		{ 201, 223 },
		{ 199, 220 },
		{ 198, 219 },
		{ 197, 217 },
		{ 196, 216 },
		{ 192, 212 },
		{ 189, 210 },
		{ 175, 20 },
		{ 169, 203 },
		{ 168, 202 },
		{ 167, 200 },
		{ 136, 156 },
		{ 130, 160 },
		{ 129, 158 },
		{ 124, 185 },
		{ 119, 161 },
		{ 111, 155 },
		{ 110, 154 },
		{ 109, 153 },
		{ 108, 152 },
		{ 107, 151 },
		{ 106, 150 },
		{ 105, 149 },
		{ 104, 148 },
		{ 103, 147 },
		{ 102, 146 },
		{ 101, 145 },
		{ 100, 144 },
		{ 99, 143 },
		{ 98, 142 },
		{ 97, 141 },
		{ 96, 140 },
		{ 95, 139 },
		{ 94, 138 },
		{ 93, 137 },
		{ 91, 135 },
		{ 80, 128 },
		{ 76, 125 },
		{ 72, 123 },
		{ 66, 121 },
		{ 59, 92 },
		{ 57, 90 },
		{ 56, 89 },
		{ 55, 88 },
		{ 48, 84 },
		{ 47, 83 },
		{ 46, 82 },
		{ 45, 79 },
		{ 41, 74 },
		{ 35, 68 },
		{ 34, 67 },
		{ 28, 60 },
		{ 27, 43 },
		{ 14, 23 }
	};
	yynontermgoto = nontermgoto;

	static const yystategoto_t YYNEARFAR YYBASED_CODE stategoto[] = {
		{ 47, 7 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, 39 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, 175 },
		{ 114, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 4, 39 },
		{ 0, -1 },
		{ 92, 40 },
		{ 108, 259 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 101, -1 },
		{ 100, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 16, -1 },
		{ 22, 77 },
		{ 99, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 104, 259 },
		{ 102, -1 },
		{ 101, -1 },
		{ 100, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, 163 },
		{ 100, 259 },
		{ 99, 259 },
		{ 98, 259 },
		{ 0, -1 },
		{ 96, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 89, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 89, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 88, -1 },
		{ 4, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 92, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 95, 193 },
		{ 0, -1 },
		{ 91, 259 },
		{ 90, 259 },
		{ 89, 259 },
		{ 88, 259 },
		{ 87, 259 },
		{ 86, 259 },
		{ 85, 259 },
		{ 84, 259 },
		{ 83, 259 },
		{ 82, 259 },
		{ 81, 259 },
		{ 80, 259 },
		{ 79, 259 },
		{ 78, 259 },
		{ 77, 259 },
		{ 76, 259 },
		{ 75, 259 },
		{ 74, 259 },
		{ 73, 259 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, 136 },
		{ 0, 129 },
		{ 0, 130 },
		{ 0, -1 },
		{ 0, -1 },
		{ 72, 259 },
		{ 0, -1 },
		{ 31, 184 },
		{ 0, -1 },
		{ 0, -1 },
		{ 65, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 69, -1 },
		{ 68, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 68, 259 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 31, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 55, -1 },
		{ 52, -1 },
		{ 65, 259 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 68, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 19, 272 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 63, 259 },
		{ 0, -1 },
		{ 0, -1 },
		{ 65, 193 },
		{ 16, 259 },
		{ 0, -1 },
		{ 0, -1 },
		{ 61, 259 },
		{ 60, 259 },
		{ 59, 259 },
		{ 58, 259 },
		{ 0, -1 },
		{ 56, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 56, 259 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 55, 259 },
		{ 0, -1 },
		{ 0, -1 },
		{ 53, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 45, 272 },
		{ 44, 272 },
		{ 43, 272 },
		{ 42, 272 },
		{ 49, 259 },
		{ 0, -1 },
		{ 48, 259 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 39, 272 },
		{ 0, -1 },
		{ 46, 259 },
		{ 45, 259 },
		{ 0, -1 },
		{ 36, 272 },
		{ 35, 272 },
		{ 0, -1 },
		{ 34, 272 },
		{ 18, 272 },
		{ 0, -1 },
		{ 9, 272 },
		{ 0, -1 },
		{ 28, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 1, 272 },
		{ 0, -1 },
		{ -4, 272 },
		{ -15, 272 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ -3, 259 },
		{ 0, -1 }
	};
	yystategoto = stategoto;

	yydestructorptr = NULL;

	yytokendestptr = NULL;
	yytokendest_size = 0;

	yytokendestbaseptr = NULL;
	yytokendestbase_size = 0;
}
#line 1105 ".\\myparser.y"


/////////////////////////////////////////////////////////////////////////////
// programs section
string getstring ( const int n )

{

std::stringstream newstr;
newstr<<n;
return newstr.str();

}

/*
int getint(string s){
    return atoi(s.c_str());
}

float getfloat(const string &s){
	istringstream iss(s);
	float num;
	iss>>num;
	return num;
}*/
string getstringd(const float f){
	std::stringstream newstr;
	newstr<<f;
	return newstr.str();
}
Node*findfexist(stack<CHash*> ms, string lexeme, int &count) {
	stack<CHash*>tmps;
	Node*tmp;
	count = 0;
	while (!ms.empty()) {
		if (tmp = ms.top()->findexist(lexeme)) {
			while (!tmps.empty()) {
				ms.push(tmps.top());
				tmps.pop();
			}
			return tmp;
		}
		tmps.push(ms.top());
		ms.pop();
		count++;
	}
	while (!tmps.empty()) {
		ms.push(tmps.top());
		tmps.pop();
	}
	return NULL;
}


TreeNode*newStmtsNode(StmtsKind kind) {
	TreeNode*t = new TreeNode();
	int i;
	if (t == NULL)cout << "out of mem at "<<lineno<<"\n";
	else {
		for (i = 0;i < MAXCHILD;i++)
			t->child[i] = NULL;
		t->sibling = NULL;
		t->nodekind = STMTSK;
		t->kind.stmt = kind;
		t->lineno = lineno;
		t->type=NOTK;
		t->exptype=NULL;
	}
	return t;
}

/*
TreeNode * newExpNode(ExpKind kind)
{
  	TreeNode*t = new TreeNode();
  int i;
  if (t==NULL)
    cout<<"Out of memory error at line "<<lineno<<endl;
  else {
    for (i=0;i<MAXCHILD;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = EXPK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = INTK;
  }
  return t;
}
*/


TreeNode*makenodeT(TreeNode*f,TreeNode*s,OpType op){
	TreeNode*expr=newExpNode(OPK);
	expr->attri.op=op;
	expr->child[0]=f;
	expr->child[1]=s;
	return expr;
}
TreeNode*makenodeS(TreeNode*t,OpType op){
	TreeNode*expr=newExpNode(OPK);
	expr->child[0]=t;
	expr->attri.op=op;
	return expr;
}

TreeNode*newTypeNode(ExpType type){
	TreeNode*t = new TreeNode();
  int i;
  if (t==NULL)
    cout<<"Out of memory error at line "<<lineno<<endl;
  else {
    for (i=0;i<MAXCHILD;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = TYPEK;
    //t->kind.exp = kind;
	t->type=type;
    t->lineno = lineno;
	t->classname="";
	t->attri.name="";
	t->attri.conststring="";
	t->exptype=NULL;
  }
  return t;
}
TreeNode*newTypeNode(ExpType type,string classname){
		TreeNode*t = new TreeNode();
  int i;
  if (t==NULL)
    cout<<"Out of memory error at line "<<lineno<<endl;
  else {
    for (i=0;i<MAXCHILD;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = TYPEK;
    //t->kind.exp = kind;
	t->type=type;
    t->lineno = lineno;
	t->classname=classname;
	t->attri.name="";
	t->attri.conststring="";
	t->exptype=NULL;
  }
  return t;
}

int main(int argc, char *argv[])
{
int n = 1;
	
//	allsymbol.push(symbtb);
	Fcode::initnum();
	mylexer lexer;
	myparser parser;
	if (parser.yycreate(&lexer)) {
		if (lexer.yycreate(&parser)) {
			
			if (argc > 1)
          lexer.yyin = new std::ifstream(argv[1]);
		lexer.yyout=new std::ofstream("result.txt");
      if (!lexer.yyin->fail()) n = parser.yyparse();
		//n = parser.yyparse();
		//cout<<n<<endl;
//	if(n){
//最终输出：
		if(startnode!=NULL){
			cout<<"--------------------grammer tree:-------------------"<<endl;
			overTree(startnode);
			cout<<"u can also find it in text file :tree.txt"<<endl;
			cout<<"u may also wanna check file result.txt to find out if there are some other grammer mistakes"<<endl;
		}
		else{
			cout<<"error occurs,the tree cannot be built"<<endl;
			cout<<"see more info in file result.txt"<<endl;
		}
		//storesymbol
		}
	}
	return n;
}


