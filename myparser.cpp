/****************************************************************************
*                     U N R E G I S T E R E D   C O P Y
* 
* You are on day 110 of your 30 day trial period.
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
* Date: 01/04/18
* Time: 02:52:38
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
#include "codegen.h"
#include"toasm.h"

using namespace std;

bool gtf=false;

extern stack<CHash*> allsymbol;
extern stack<CHash*>storesymbol;
hash_map<string,ClassNode*>classmap;
hash_map<string,Node*>funcmap;
hash_map<string,Node*>*tofuncmap;


//CHash*classname;//为了支持类操作，检查类类型。
extern int lineno;
ExpType nowattri;
BaseType nowcode;
string nowclass;
TreeNode*startnode;
TreeNode*mainnode=NULL;

ofstream rout("result.txt");
ofstream trout("tree.txt");
ofstream asmf("test.asm");



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
	if(op==CLASSMCK)return "->";
	if(op==POINTK)return ".";
	return "none";
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




#line 239 "myparser.cpp"
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
#line 216 ".\\myparser.y"

	// place any extra initialisation code here

#line 263 "myparser.cpp"
}

/////////////////////////////////////////////////////////////////////////////
// destructor

YYPARSERNAME::~YYPARSERNAME()
{
	// allows virtual functions to be called properly for correct cleanup
	yydestroy();
#line 221 ".\\myparser.y"

	// place any extra cleanup code here

#line 277 "myparser.cpp"
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
#line 295 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);startnode=(*(YYSTYPE YYFAR*)yyvalptr);cout<<"start1"<<endl;
#line 387 "myparser.cpp"
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
#line 296 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(STARTK);
						(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 2);
						(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(2 - 2);
						//结合代码
						(*(YYSTYPE YYFAR*)yyvalptr)->midcode=Fcodes::combinecode(yyattribute(1 - 2)->midcode,yyattribute(2 - 2)->midcode);
						//---
						startnode=(*(YYSTYPE YYFAR*)yyvalptr);
						
						cout<<"start 2"<<endl;
#line 408 "myparser.cpp"
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
#line 311 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 421 "myparser.cpp"
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
#line 313 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 434 "myparser.cpp"
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
#line 314 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 447 "myparser.cpp"
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
#line 315 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 460 "myparser.cpp"
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
#line 320 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newTypeNode(INTK);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CINT);nowattri=INTK;nowcode=CINT;
#line 473 "myparser.cpp"
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
#line 321 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newTypeNode(CHARK);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CCHAR);nowattri=CHARK;nowcode=CCHAR;
#line 486 "myparser.cpp"
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
#line 322 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newTypeNode(FLOATK);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CFLOAT);nowattri=FLOATK;nowcode=CFLOAT;
#line 499 "myparser.cpp"
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
#line 323 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newTypeNode(VOIDK);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CVOID);nowattri=VOIDK;nowcode=CVOID;
#line 512 "myparser.cpp"
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
#line 328 ".\\myparser.y"

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
					
				
#line 545 "myparser.cpp"
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
#line 349 ".\\myparser.y"
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
					
					
#line 577 "myparser.cpp"
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
#line 370 ".\\myparser.y"

					//类型检查
					yyattribute(3 - 5)->exptype=new CType(nowcode);
					if(nowcode==CCLASS)yyattribute(3 - 5)->exptype->cname=nowclass;
					if(checkEqual(yyattribute(3 - 5),yyattribute(5 - 5)->exptype)==NULL)gtf=true;
					
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
					//$$->
					
					
#line 615 "myparser.cpp"
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
#line 396 ".\\myparser.y"

					//类型检查：这里的类型检查就不拖到语法树建立完成了
					yyattribute(1 - 3)->exptype=new CType(nowcode);
					if(nowcode==CCLASS)yyattribute(1 - 3)->exptype->cname=nowclass;
					if(!checkEqual(yyattribute(1 - 3),yyattribute(3 - 3)->exptype))gtf=true;
					
					Node*addr=(allsymbol.top())->findexist(yyattribute(1 - 3)->attri.name);
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
				
							
						
#line 651 "myparser.cpp"
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
#line 422 ".\\myparser.y"

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
				
					
					
#line 687 "myparser.cpp"
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
#line 447 ".\\myparser.y"

					//添加类型
					yyattribute(3 - 6)->exptype=CType::array0(yyattribute(5 - 6)->attri.val,new CType(nowcode));
					if(nowcode==CCLASS)yyattribute(3 - 6)->exptype->cname=nowclass;
					yyattribute(5 - 6)->exptype=new CType(CINT);
					
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
					
						
#line 723 "myparser.cpp"
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
#line 471 ".\\myparser.y"

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
					
					
#line 756 "myparser.cpp"
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
#line 493 ".\\myparser.y"

					//添加类型
					yyattribute(1 - 4)->exptype=CType::array0(yyattribute(3 - 4)->attri.val,new CType(nowcode));
					if(nowcode==CCLASS)yyattribute(1 - 4)->exptype->cname=nowclass;
					yyattribute(3 - 4)->exptype=new CType(CINT);
					
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
					
						
#line 791 "myparser.cpp"
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
#line 522 ".\\myparser.y"
lastt->sibling=yyattribute(3 - 3);lastt=yyattribute(3 - 3);(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=CType::dicar(yyattribute(1 - 3)->exptype,yyattribute(3 - 3)->exptype);
#line 804 "myparser.cpp"
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
#line 523 ".\\myparser.y"
lastt=yyattribute(1 - 1);(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(yyattribute(1 - 1)->exptype);
#line 817 "myparser.cpp"
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
#line 529 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(BASEK);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(2 - 3);
					//cout<<"basetype:"<<$1->type<<$2->nodekind<<endl;
					//类型
					
				
#line 837 "myparser.cpp"
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
#line 537 ".\\myparser.y"

		//ID可能是在类表里面，也可能不在
		//要求类在使用前必须定义，函数也是一样
					
					(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(BASEK);
					string name=yyattribute(1 - 3)->attri.name;
//					delete $1;
					//$1=newTypeNode(NOTK,name);
					yyattribute(1 - 3)->nodekind=TYPEK;
					yyattribute(1 - 3)->type=NOTK;
					yyattribute(1 - 3)->classname=name;
					(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(2 - 3);
				
#line 863 "myparser.cpp"
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
#line 556 ".\\myparser.y"


	if(classmap.find(yyattribute(1 - 1)->attri.name)==classmap.end()){
		gtf=true;
		rout<<"error:undefined symbol:"<<yyattribute(1 - 1)->attri.name<<" at line:"<<lineno<<endl;
	}
	nowattri=NOTK;nowcode=CCLASS;nowclass=yyattribute(1 - 1)->attri.name;(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 882 "myparser.cpp"
			}
		}
		break;
	case 23:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 572 ".\\myparser.y"

			int count=0;
			Node*idnode;
			if((idnode=findfexist(allsymbol,yyattribute(1 - 1)->attri.name,count))==NULL){
			//	gtf=true;
			//	rout<<"error undefined symbol:"<<$1->attri.name<<" at line:"<<lineno<<endl;
				yyattribute(1 - 1)->exptype=new CType(CVOID);
			}else{
				yyattribute(1 - 1)->exptype=new CType(idnode->exptype);
			}
			(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
		
#line 906 "myparser.cpp"
			}
		}
		break;
	case 24:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 585 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),CLASSMCK);
					//类型检查与赋值
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkclass(CLASSMCK,yyattribute(1 - 3)->exptype,yyattribute(3 - 3)->attri.name,NULL);
					if(!((*(YYSTYPE YYFAR*)yyvalptr)->exptype)){
						gtf=1;
						rout<<"error:bad type '->' at line :"<<lineno<<endl;
						}
					
#line 926 "myparser.cpp"
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
#line 593 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),POINTK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkclass(POINTK,yyattribute(1 - 3)->exptype,yyattribute(3 - 3)->attri.name,NULL);
					if(!((*(YYSTYPE YYFAR*)yyvalptr)->exptype)){
						gtf=1;
						rout<<"error:bad type '.' at line :"<<lineno<<endl;
						}
					
					
#line 947 "myparser.cpp"
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
#line 602 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(2 - 2),GETCONTENTK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkOp(GETCONTENTK,yyattribute(2 - 2)->exptype,NULL);
					if(!((*(YYSTYPE YYFAR*)yyvalptr)->exptype)){
						gtf=1;
						rout<<"error:bad type '*' at line :"<<lineno<<endl;
						}
					
#line 967 "myparser.cpp"
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
#line 611 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 4),yyattribute(3 - 4),ARRAYCK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkOp(ARRAYCK,yyattribute(1 - 4)->exptype,yyattribute(3 - 4)->exptype);
					if(!((*(YYSTYPE YYFAR*)yyvalptr)->exptype)){
						gtf=1;
						rout<<"error:bad type '[]' at line :"<<lineno<<endl;
						}
					
					
#line 988 "myparser.cpp"
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
#line 620 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(2 - 2),ALGCTADDPK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkleft(ALGCTADDPK,yyattribute(2 - 2));
					if(!((*(YYSTYPE YYFAR*)yyvalptr)->exptype)){
						gtf=1;
						rout<<"error:bad type '++' at line :"<<lineno<<endl;
						}

					
#line 1009 "myparser.cpp"
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
#line 629 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(2 - 2),ALGCTMINUSPK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkleft(ALGCTMINUSPK,yyattribute(2 - 2));
					if(!((*(YYSTYPE YYFAR*)yyvalptr)->exptype)){
						gtf=1;
						rout<<"error:bad type '--' at line :"<<lineno<<endl;
						}
					
					
#line 1030 "myparser.cpp"
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
#line 638 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(2 - 3);
#line 1043 "myparser.cpp"
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
#line 642 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),ALGCADDK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkOp(ALGCADDK,yyattribute(1 - 3)->exptype,yyattribute(3 - 3)->exptype);
					if(!((*(YYSTYPE YYFAR*)yyvalptr)->exptype)){
						gtf=1;
						rout<<"error:bad type '+' at line :"<<lineno<<endl;
						}
					
					
#line 1064 "myparser.cpp"
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
#line 651 ".\\myparser.y"
 
					(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),ALGCMINUSK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkOp(ALGCMINUSK,yyattribute(1 - 3)->exptype,yyattribute(3 - 3)->exptype);
					if(!((*(YYSTYPE YYFAR*)yyvalptr)->exptype)){
						gtf=1;
						rout<<"error:bad type '-' at line :"<<lineno<<endl;
						}
					
					 
#line 1085 "myparser.cpp"
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
#line 660 ".\\myparser.y"
 
					(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),ALGCMULK); 
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkOp(ALGCMULK,yyattribute(1 - 3)->exptype,yyattribute(3 - 3)->exptype);
					if(!((*(YYSTYPE YYFAR*)yyvalptr)->exptype)){
						gtf=1;
						rout<<"error:bad type '*' at line :"<<lineno<<endl;
						}
					
					
#line 1106 "myparser.cpp"
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
#line 669 ".\\myparser.y"
 (*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),ALGCDIVK); 
	
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkOp(ALGCDIVK,yyattribute(1 - 3)->exptype,yyattribute(3 - 3)->exptype);
					if(!((*(YYSTYPE YYFAR*)yyvalptr)->exptype)){
						gtf=1;
						rout<<"error:bad type '/' at line :"<<lineno<<endl;
						}
	
#line 1126 "myparser.cpp"
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
#line 677 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),ALGCMODK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkOp(ALGCMODK,yyattribute(1 - 3)->exptype,yyattribute(3 - 3)->exptype);
					if(!((*(YYSTYPE YYFAR*)yyvalptr)->exptype)){
						gtf=1;
						rout<<"error:bad type '%' at line :"<<lineno<<endl;
						}
	
		
#line 1146 "myparser.cpp"
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
#line 686 ".\\myparser.y"
 (*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(2 - 3);
#line 1159 "myparser.cpp"
			}
		}
		break;
	case 37:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 687 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(2 - 2),UMINUSK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkOp(UMINUSK,yyattribute(1 - 2)->exptype,NULL);
					if(!((*(YYSTYPE YYFAR*)yyvalptr)->exptype)){
						gtf=1;
						rout<<"error:bad type 'uminus' at line :"<<lineno<<endl;
						}
	
	
	
#line 1180 "myparser.cpp"
			}
		}
		break;
	case 38:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 697 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CINT);
#line 1193 "myparser.cpp"
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
#line 698 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CINT);
#line 1206 "myparser.cpp"
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
#line 699 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CFLOAT);
#line 1219 "myparser.cpp"
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
#line 700 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CSTRING);
#line 1232 "myparser.cpp"
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
#line 701 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(CCHAR);
#line 1245 "myparser.cpp"
			}
		}
		break;
	case 43:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 705 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(1 - 2),ALGCTADDBK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkleft(ALGCTADDBK,yyattribute(1 - 2));
					if((*(YYSTYPE YYFAR*)yyvalptr)->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '++' at line :"<<lineno<<endl;
					}
					
					
					
#line 1267 "myparser.cpp"
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
#line 715 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(1 - 2),ALGCTMINUSBK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkleft(ALGCTMINUSBK,yyattribute(1 - 2));
					if((*(YYSTYPE YYFAR*)yyvalptr)->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '--' at line :"<<lineno<<endl;
					}
					
					
#line 1288 "myparser.cpp"
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
#line 726 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(2 - 2),BTCNK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkOp(BTCNK,yyattribute(2 - 2)->exptype,NULL);
					if((*(YYSTYPE YYFAR*)yyvalptr)->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '~' at line :"<<lineno<<endl;
					}
	
	
#line 1308 "myparser.cpp"
			}
		}
		break;
	case 46:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 735 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),BTCRIGHTK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkOp(BTCRIGHTK,yyattribute(1 - 3)->exptype,yyattribute(3 - 3)->exptype);
					//$$->exptype=checkOp(BTCNK,$2->exptype);
					if((*(YYSTYPE YYFAR*)yyvalptr)->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '>>' at line :"<<lineno<<endl;
					}
	
	
#line 1329 "myparser.cpp"
			}
		}
		break;
	case 47:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 744 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),BTCLEFTK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkOp(BTCLEFTK,yyattribute(1 - 3)->exptype,yyattribute(3 - 3)->exptype);
					if((*(YYSTYPE YYFAR*)yyvalptr)->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '<<' at line :"<<lineno<<endl;
					}
	
	
#line 1349 "myparser.cpp"
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
#line 752 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),BTCANDK);
						(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkOp(BTCANDK,yyattribute(1 - 3)->exptype,yyattribute(3 - 3)->exptype);
					if((*(YYSTYPE YYFAR*)yyvalptr)->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '&' at line :"<<lineno<<endl;
					}
	
#line 1368 "myparser.cpp"
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
#line 759 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),BTCORK);
						(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkOp(BTCORK,yyattribute(1 - 3)->exptype,yyattribute(3 - 3)->exptype);
					if((*(YYSTYPE YYFAR*)yyvalptr)->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '||' at line :"<<lineno<<endl;
					}
			
#line 1387 "myparser.cpp"
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
#line 766 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),BTCYHK);
						(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkOp(BTCYHK,yyattribute(1 - 3)->exptype,yyattribute(3 - 3)->exptype);
					if((*(YYSTYPE YYFAR*)yyvalptr)->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '^' at line :"<<lineno<<endl;
					}
					
#line 1406 "myparser.cpp"
			}
		}
		break;
	case 51:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 774 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 4),yyattribute(3 - 4),FUNCK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkfunc(yyattribute(1 - 4)->attri.name,yyattribute(3 - 4)->exptype);
					if((*(YYSTYPE YYFAR*)yyvalptr)->exptype==NULL){
						gtf=1;
						rout<<"error:bad type 'func' at line :"<<lineno<<endl;
					}
	
	
#line 1426 "myparser.cpp"
			}
		}
		break;
	case 52:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 783 ".\\myparser.y"

					TreeNode*t=makenodeT(yyattribute(3 - 6),yyattribute(5 - 6),FUNCK);
					(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 6),t,CLASSMCK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkclass(CLASSMCK,yyattribute(1 - 6)->exptype,yyattribute(3 - 6)->attri.name,yyattribute(5 - 6)->exptype);
					if((*(YYSTYPE YYFAR*)yyvalptr)->exptype==NULL){
						gtf=1;
						rout<<"error:bad type 'func' at line :"<<lineno<<endl;
					}
					
					
#line 1448 "myparser.cpp"
			}
		}
		break;
	case 53:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 793 ".\\myparser.y"

					TreeNode*t=makenodeT(yyattribute(3 - 6),yyattribute(5 - 6),FUNCK);
					(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 6),t,POINTK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkclass(POINTK,yyattribute(1 - 6)->exptype,yyattribute(3 - 6)->attri.name,yyattribute(5 - 6)->exptype);
					if((*(YYSTYPE YYFAR*)yyvalptr)->exptype==NULL){
						gtf=1;
						rout<<"error:bad type 'func' at line :"<<lineno<<endl;
					}
		
#line 1469 "myparser.cpp"
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
#line 802 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(1 - 3),FUNCK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkfunc(yyattribute(1 - 3)->attri.name,new CType(CVOID));
					if((*(YYSTYPE YYFAR*)yyvalptr)->exptype==NULL){
						gtf=1;
						rout<<"error:bad type 'func' at line :"<<lineno<<endl;
					}
	
	
#line 1489 "myparser.cpp"
			}
		}
		break;
	case 55:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 811 ".\\myparser.y"

					TreeNode*t=makenodeS(yyattribute(3 - 5),FUNCK);
					(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 5),t,CLASSMCK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkclass(CLASSMCK,yyattribute(1 - 5)->exptype,yyattribute(3 - 5)->attri.name,new CType(CVOID));
					if((*(YYSTYPE YYFAR*)yyvalptr)->exptype==NULL){
						gtf=1;
						rout<<"error:bad type 'func' at line :"<<lineno<<endl;
					}
					
					
#line 1511 "myparser.cpp"
			}
		}
		break;
	case 56:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 821 ".\\myparser.y"

					TreeNode*t=makenodeS(yyattribute(3 - 5),FUNCK);
					(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 5),t,POINTK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkclass(POINTK,yyattribute(1 - 5)->exptype,yyattribute(3 - 5)->attri.name,new CType(CVOID));
					if((*(YYSTYPE YYFAR*)yyvalptr)->exptype==NULL){
						gtf=1;
						rout<<"error:bad type 'func' at line :"<<lineno<<endl;
					}
					
#line 1532 "myparser.cpp"
			}
		}
		break;
	case 57:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 832 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(2 - 2),LGCCNK);
					//$$->exptype=checkOp(
	
#line 1547 "myparser.cpp"
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
#line 835 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),LGCCMOREEQK);
					/*$$->exptype=checkOp(BTCLEFTK,$1->exptype,$3->exptype);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '<<' at line :"<<lineno<<endl;
					}*/
	
	
#line 1567 "myparser.cpp"
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
#line 843 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),LGCCLESSEQK);
				/*		$$->exptype=checkOp(BTCLEFTK,$1->exptype,$3->exptype);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '<<' at line :"<<lineno<<endl;
					}*/
	
#line 1586 "myparser.cpp"
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
#line 850 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),LGCCLESSK);
#line 1599 "myparser.cpp"
			}
		}
		break;
	case 61:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 851 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),LGCCMOREK);
#line 1612 "myparser.cpp"
			}
		}
		break;
	case 62:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 852 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),LGCCEQK);
#line 1625 "myparser.cpp"
			}
		}
		break;
	case 63:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 853 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),LGCCNK);
#line 1638 "myparser.cpp"
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
#line 857 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),LGCCANDK);
				/*		$$->exptype=checkOp(BTCLEFTK,$1->exptype,$3->exptype);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '<<' at line :"<<lineno<<endl;
					}*/
	
#line 1657 "myparser.cpp"
			}
		}
		break;
	case 65:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 864 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),LGCCORK);
#line 1670 "myparser.cpp"
			}
		}
		break;
	case 66:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 869 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeT(yyattribute(1 - 3),yyattribute(3 - 3),EQUEK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkEqual(yyattribute(1 - 3),yyattribute(3 - 3)->exptype);
					if((*(YYSTYPE YYFAR*)yyvalptr)->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '=' at line :"<<lineno<<endl;
					}
	
#line 1689 "myparser.cpp"
			}
		}
		break;
	case 67:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 879 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=makenodeS(yyattribute(2 - 2),GETADDRK);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=checkleft(GETADDRK,yyattribute(2 - 2));
					if((*(YYSTYPE YYFAR*)yyvalptr)->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '&' at line :"<<lineno<<endl;
					}
	
	
#line 1709 "myparser.cpp"
			}
		}
		break;
	case 68:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 905 ".\\myparser.y"

			(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(RETURNK);
			(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(2 - 3);
			(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(yyattribute(2 - 3)->exptype);
		
#line 1726 "myparser.cpp"
			}
		}
		break;
	case 69:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 913 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(EXPSK);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 2);;
#line 1739 "myparser.cpp"
			}
		}
		break;
	case 70:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 914 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(EXPSK);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=NULL;rout<<"error at line:"<<lineno<<" missing rbracess"<<endl;
#line 1752 "myparser.cpp"
			}
		}
		break;
	case 71:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 915 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 1765 "myparser.cpp"
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
#line 922 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(NULLK);
#line 1778 "myparser.cpp"
			}
		}
		break;
	case 73:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 928 ".\\myparser.y"

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
			
#line 1804 "myparser.cpp"
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
#line 942 ".\\myparser.y"

			cstlastt.top()->sibling=yyattribute(2 - 2);cstlastt.pop();cstlastt.push(yyattribute(2 - 2));(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 2);
			
#line 1819 "myparser.cpp"
			}
		}
		break;
	case 75:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 945 ".\\myparser.y"
cstlastt.pop();cstlastt.push(yyattribute(1 - 1));(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 1832 "myparser.cpp"
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
#line 946 ".\\myparser.y"
cstlastt.pop();cstlastt.push(yyattribute(1 - 1));(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 1845 "myparser.cpp"
			}
		}
		break;
	case 77:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 952 ".\\myparser.y"

				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(COMSTMTK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 4);
				cstlastt.pop();
			
#line 1862 "myparser.cpp"
			}
		}
		break;
	case 78:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 962 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(COMSTMTK);cstlastt.pop();
#line 1875 "myparser.cpp"
			}
		}
		break;
	case 79:
		{
#line 975 ".\\myparser.y"
TreeNode*lat;cstlastt.push(lat);
#line 1883 "myparser.cpp"
		}
		break;
	case 80:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 986 ".\\myparser.y"

				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(IFK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 7);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 7);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=yyattribute(7 - 7);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
			
#line 1902 "myparser.cpp"
			}
		}
		break;
	case 81:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 995 ".\\myparser.y"

				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(IFK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 5);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 5);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
			
#line 1921 "myparser.cpp"
			}
		}
		break;
	case 82:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 1002 ".\\myparser.y"

				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(IFK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 7);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 7);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=yyattribute(7 - 7);
				rout<<"error at line:"<<lineno<<" missing ')'"<<endl;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
			
#line 1942 "myparser.cpp"
			}
		}
		break;
	case 83:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 1012 ".\\myparser.y"

				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(IFK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 5);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 5);
				rout<<"error at line:"<<lineno<<" missing ')'"<<endl;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
	
#line 1962 "myparser.cpp"
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
#line 1023 ".\\myparser.y"

				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(WHILEK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 5);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 5);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
			
#line 1981 "myparser.cpp"
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
#line 1030 ".\\myparser.y"

				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(WHILEK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 5);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 5);
				rout<<"error at line:"<<lineno<<" missing ')'"<<endl;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
			
#line 2001 "myparser.cpp"
			}
		}
		break;
	case 86:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[10];
			yyinitdebug((void YYFAR**)yya, 10);
#endif
			{
#line 1040 ".\\myparser.y"


				TreeNode*t=newStmtsNode(FOREK);
				t->child[0]=yyattribute(3 - 9);
				t->child[1]=yyattribute(5 - 9);
				t->child[2]=yyattribute(7 - 9);
				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FORK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=t;
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(9 - 9);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();

#line 2025 "myparser.cpp"
			}
		}
		break;
	case 87:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[9];
			yyinitdebug((void YYFAR**)yya, 9);
#endif
			{
#line 1052 ".\\myparser.y"

				TreeNode*t=newStmtsNode(FOREK);
				t->child[0]=yyattribute(3 - 8);
				t->child[1]=yyattribute(5 - 8);
				t->child[2]=NULL;
				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FORK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=t;
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(8 - 8);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();

#line 2048 "myparser.cpp"
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
#line 1063 ".\\myparser.y"

				TreeNode*t=newStmtsNode(FOREK);
				t->child[0]=yyattribute(3 - 8);
				t->child[1]=NULL;
				t->child[2]=yyattribute(6 - 8);
				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FORK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=t;
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(8 - 8);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();

#line 2071 "myparser.cpp"
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
#line 1074 ".\\myparser.y"

				TreeNode*t=newStmtsNode(FOREK);
				t->child[0]=NULL;
				t->child[1]=yyattribute(4 - 8);
				t->child[2]=yyattribute(6 - 8);
				
				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FORK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=t;
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(8 - 8);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();

#line 2095 "myparser.cpp"
			}
		}
		break;
	case 90:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 1086 ".\\myparser.y"

				TreeNode*t=newStmtsNode(FOREK);
				t->child[0]=yyattribute(3 - 7);
				
				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FORK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=t;
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(7 - 7);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();

#line 2117 "myparser.cpp"
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
#line 1096 ".\\myparser.y"

				TreeNode*t=newStmtsNode(FOREK);
				//$$->child[0]=$1;
				t->child[1]=yyattribute(4 - 7);
				
				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FORK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=t;
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(7 - 7);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();

#line 2140 "myparser.cpp"
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
#line 1107 ".\\myparser.y"

				TreeNode*t=newStmtsNode(FOREK);
				//$$->child[0]=$1;
				//$$->child[1]=$3;
				t->child[2]=yyattribute(5 - 7);
				
				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FORK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=t;
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(7 - 7);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();

#line 2164 "myparser.cpp"
			}
		}
		break;
	case 93:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 1119 ".\\myparser.y"

				TreeNode*t=newStmtsNode(FOREK);
				
				(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FORK);
				(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=t;
				(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(6 - 6);
				storesymbol.push(allsymbol.top());
				allsymbol.pop();

#line 2185 "myparser.cpp"
			}
		}
		break;
	case 94:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 1134 ".\\myparser.y"

			(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 3);
			lastt->sibling=yyattribute(3 - 3);
			lastt=yyattribute(3 - 3);

#line 2202 "myparser.cpp"
			}
		}
		break;
	case 95:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 1139 ".\\myparser.y"

			(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(2 - 2);
			lastt=(*(YYSTYPE YYFAR*)yyvalptr);
		
	
#line 2219 "myparser.cpp"
			}
		}
		break;
	case 96:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 1145 ".\\myparser.y"

			(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(COUTK);
			(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(2 - 3);

#line 2235 "myparser.cpp"
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
#line 1152 ".\\myparser.y"

			(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 3);
			lastt->sibling=yyattribute(3 - 3);
			lastt=yyattribute(3 - 3);
	

#line 2253 "myparser.cpp"
			}
		}
		break;
	case 98:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 1158 ".\\myparser.y"

			(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(2 - 2);
			lastt=(*(YYSTYPE YYFAR*)yyvalptr);	
	
#line 2269 "myparser.cpp"
			}
		}
		break;
	case 99:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 1163 ".\\myparser.y"

			(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(CINK);
			(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(2 - 3);

#line 2285 "myparser.cpp"
			}
		}
		break;
	case 100:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 1173 ".\\myparser.y"

		ExpType type=yyattribute(1 - 2)->type;
		ExpType nt=(type==INTK ?INTSK:(type==CHARK ?CHARSK:FLOATSK));
		yyattribute(1 - 2)->type=nt;
		(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 2);
		//类型
		(*(YYSTYPE YYFAR*)yyvalptr)->exptype=CType::pointer(yyattribute(1 - 2)->exptype);
	
#line 2305 "myparser.cpp"
			}
		}
		break;
	case 101:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 1187 ".\\myparser.y"

		TreeNode*t=newStmtsNode(BASEK);
		t->child[0]=yyattribute(3 - 4);
		t->child[1]=yyattribute(4 - 4);
		(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 4);
		lastt->sibling=t;
		lastt=t;
		//类型：由于直接是给函数用的，于是直接定义成dicar
		(*(YYSTYPE YYFAR*)yyvalptr)->exptype=CType::dicar(yyattribute(1 - 4)->exptype,yyattribute(3 - 4)->exptype);
		

#line 2328 "myparser.cpp"
			}
		}
		break;
	case 102:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 1198 ".\\myparser.y"

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
			//类型：由于直接是给函数用的，于是直接定义成dicar
			(*(YYSTYPE YYFAR*)yyvalptr)->exptype=CType::dicar(yyattribute(1 - 7)->exptype,CType::array0(yyattribute(6 - 7)->attri.val,yyattribute(3 - 7)->exptype));
	
#line 2354 "myparser.cpp"
			}
		}
		break;
	case 103:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 1213 ".\\myparser.y"

			TreeNode*t=newStmtsNode(BASEK);
			t->child[0]=yyattribute(1 - 2);
			t->child[1]=yyattribute(2 - 2);
			(*(YYSTYPE YYFAR*)yyvalptr)=t;
			lastt=t;
			//类型
			(*(YYSTYPE YYFAR*)yyvalptr)->exptype=yyattribute(1 - 2)->exptype;
	
#line 2375 "myparser.cpp"
			}
		}
		break;
	case 104:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 1222 ".\\myparser.y"

			TreeNode*t=newStmtsNode(BASEK);
			TreeNode*te=newExpNode(OPK);
			te->attri.op=ARRAYCK;
			te->child[0]=yyattribute(2 - 5);
			te->child[1]=yyattribute(4 - 5);
			t->child[0]=yyattribute(1 - 5);
			t->child[1]=te;
			lastt=t;
			//类型
			(*(YYSTYPE YYFAR*)yyvalptr)->exptype=CType::array0(yyattribute(4 - 5)->attri.val,yyattribute(1 - 5)->exptype);	

#line 2399 "myparser.cpp"
			}
		}
		break;
	case 105:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 1263 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FUNCDK);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 6);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(2 - 6);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=yyattribute(4 - 6);
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=CType::func(yyattribute(1 - 6)->exptype,yyattribute(4 - 6)->exptype);
					(*(YYSTYPE YYFAR*)yyvalptr)->sibling=yyattribute(6 - 6);
					if(funcmap.find(yyattribute(2 - 6)->attri.name)!=funcmap.end())rout<<"error at line :"<<lineno<<"redefined func:"<<yyattribute(2 - 6)->attri.name<<endl; 
					else{
						Node*n=new Node("FUNC",yyattribute(2 - 6)->attri.name);
						n->exptype=(*(YYSTYPE YYFAR*)yyvalptr)->exptype;//符号表中的exptype
					//	n->setType($1->exptype);
						funcmap[yyattribute(2 - 6)->attri.name]=n;//$$;
						cout<<yyattribute(2 - 6)->attri.name<<":my addr is:"<<funcmap[yyattribute(2 - 6)->attri.name]<<endl;
						
					}
					

#line 2429 "myparser.cpp"
			}
		}
		break;
	case 106:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 1281 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FUNCDK);
					ExpType type=((yyattribute(1 - 7)->type==INTK ? INTSK:(yyattribute(1 - 7)->type==CHARK ? CHARSK:FLOATSK)));
					TreeNode*tmp=newTypeNode(type);
					//类型
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=CType::func(CType::pointer(yyattribute(1 - 7)->exptype),yyattribute(5 - 7)->exptype);
					
					delete yyattribute(1 - 7);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=tmp;
					(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 7);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=yyattribute(5 - 7);
					(*(YYSTYPE YYFAR*)yyvalptr)->sibling=yyattribute(7 - 7);
					if(funcmap.find(yyattribute(3 - 7)->attri.name)!=funcmap.end())rout<<"error at line :"<<lineno<<"redefined func:"<<yyattribute(3 - 7)->attri.name<<endl; 
					else{
						Node*n=new Node("FUNC",yyattribute(3 - 7)->attri.name);
					//	n->setType($1->exptype);
						n->exptype=(*(YYSTYPE YYFAR*)yyvalptr)->exptype;//符号表中的exptype
						funcmap[yyattribute(3 - 7)->attri.name]=n;//$$;
						cout<<yyattribute(3 - 7)->attri.name<<":my addr is:"<<funcmap[yyattribute(3 - 7)->attri.name]<<endl;
					}

#line 2462 "myparser.cpp"
			}
		}
		break;
	case 107:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 1303 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FUNCDK);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 5);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(2 - 5);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=NULL;
					(*(YYSTYPE YYFAR*)yyvalptr)->sibling=yyattribute(5 - 5);
					//符号
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=CType::func(yyattribute(1 - 5)->exptype,new CType(CVOID));
					
					//cout<<($$->sibling==NULL)<<"the func's sibling is null?"<<endl;
					if(funcmap.find(yyattribute(2 - 5)->attri.name)!=funcmap.end())rout<<"error at line :"<<lineno<<" redefined func:"<<yyattribute(2 - 5)->attri.name<<endl; 
					else{
						Node*n=new Node("FUNC",yyattribute(2 - 5)->attri.name);
					//	n->setType($1->exptype);
						n->exptype=(*(YYSTYPE YYFAR*)yyvalptr)->exptype;//符号表中的exptype
						funcmap[yyattribute(2 - 5)->attri.name]=n;//$$;
						cout<<yyattribute(2 - 5)->attri.name<<":my addr is:"<<funcmap[yyattribute(2 - 5)->attri.name]<<endl;
					}
	
	
#line 2494 "myparser.cpp"
			}
		}
		break;
	case 108:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 1323 ".\\myparser.y"

					(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(FUNCDK);
					ExpType type=((yyattribute(1 - 6)->type==INTK ? INTSK:(yyattribute(1 - 6)->type==CHARK ? CHARSK:FLOATSK)));
					TreeNode*tmp=newTypeNode(type);
					//符号
					(*(YYSTYPE YYFAR*)yyvalptr)->exptype=CType::func(CType::pointer(yyattribute(1 - 6)->exptype),new CType(CVOID));
					delete yyattribute(1 - 6);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=tmp;
					(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 6);
					(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=NULL;
					(*(YYSTYPE YYFAR*)yyvalptr)->sibling=yyattribute(6 - 6);
					if(funcmap.find(yyattribute(3 - 6)->attri.name)!=funcmap.end())rout<<"error at line :"<<lineno<<" redefined func:"<<yyattribute(3 - 6)->attri.name<<endl; 
					else{
						Node*n=new Node("FUNC",yyattribute(3 - 6)->attri.name);
					//	n->setType($1->exptype);
						n->exptype=(*(YYSTYPE YYFAR*)yyvalptr)->exptype;//符号
						funcmap[yyattribute(3 - 6)->attri.name]=n;//$$;
						cout<<yyattribute(3 - 6)->attri.name<<":my addr is:"<<funcmap[yyattribute(3 - 6)->attri.name]<<endl;
					}

#line 2526 "myparser.cpp"
			}
		}
		break;
	case 109:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 1349 ".\\myparser.y"

		(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(MAINK);
		(*(YYSTYPE YYFAR*)yyvalptr)->type=INTK;
		(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=newTypeNode(INTK);
		(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 5);
		mainnode=(*(YYSTYPE YYFAR*)yyvalptr);//
	
#line 2545 "myparser.cpp"
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
#line 1357 ".\\myparser.y"

		(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(MAINK);
		(*(YYSTYPE YYFAR*)yyvalptr)->type=INTK;
		(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=newTypeNode(INTK);
		(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 5);
		rout<<"error at line :"<<lineno<<" missing ')'"<<endl;
		
		
#line 2565 "myparser.cpp"
			}
		}
		break;
	case 111:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 1382 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 2);lastt->sibling=yyattribute(2 - 2);lastt=yyattribute(2 - 2);
#line 2578 "myparser.cpp"
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
#line 1385 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 2);lastt->sibling=yyattribute(2 - 2);lastt=yyattribute(2 - 2);
#line 2591 "myparser.cpp"
			}
		}
		break;
	case 113:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 1386 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);lastt=(*(YYSTYPE YYFAR*)yyvalptr);
#line 2604 "myparser.cpp"
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
#line 1388 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);lastt=(*(YYSTYPE YYFAR*)yyvalptr);
#line 2617 "myparser.cpp"
			}
		}
		break;
	case 115:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 1393 ".\\myparser.y"

		ClassNode*n=new ClassNode(yyattribute(2 - 6)->attri.name);
		n->classv=storesymbol.top();
		cout<<"llll"<<(n->classv)->findexist("m");
//		allsymbol.pop();
		(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(CLASSK);
		if(classmap.find(yyattribute(2 - 6)->attri.name)!=classmap.end()){
			gtf=1;
			rout<<"error at line:"<<lineno<<"   redefine of class:"<<yyattribute(2 - 6)->attri.name<<endl;
		}
		else{
		
			n->classf=&(funcmap);
			funcmap=*tofuncmap;
			classmap[yyattribute(2 - 6)->attri.name]=n;
			cout<<yyattribute(2 - 6)->attri.name<<":my addr :"<<classmap[yyattribute(2 - 6)->attri.name]<<endl;	
		}
		
		(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(2 - 6);
		(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(4 - 6);
		//类型
		(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(yyattribute(2 - 6)->attri.name);
		
		cout<<"更换回来"<<endl;
		//$$->w
		//其他的都会在自己的basetypestmt里面有自己的类型的编码。
		//关于ID声明变量
	
#line 2657 "myparser.cpp"
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
#line 1422 ".\\myparser.y"

		rout<<"missing ; ?  at line:"<<lineno<<endl;
		gtf=1;
		ClassNode*n=new ClassNode(yyattribute(2 - 6)->attri.name);
//		n->classv=storesymbol.top();
		allsymbol.pop();
		(*(YYSTYPE YYFAR*)yyvalptr)=newStmtsNode(CLASSK);
		if(classmap.find(yyattribute(2 - 6)->attri.name)!=classmap.end()){
			gtf=1;
			rout<<"error at line:"<<lineno<<"   redefine of class:"<<yyattribute(2 - 6)->attri.name<<endl;
		}
		else{
		
			n->classf=&(funcmap);
			funcmap=*tofuncmap;
			classmap[yyattribute(2 - 6)->attri.name]=n;
			cout<<yyattribute(2 - 6)->attri.name<<":my addr :"<<classmap[yyattribute(2 - 6)->attri.name]<<endl;	
		}
		
		(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(2 - 6);
		(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(4 - 6);
		//类型
		(*(YYSTYPE YYFAR*)yyvalptr)->exptype=new CType(yyattribute(2 - 6)->attri.name);
		
		cout<<"更换回来"<<endl;
	
	
	
	
#line 2698 "myparser.cpp"
			}
		}
		break;
	case 117:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 1454 ".\\myparser.y"

	//	allsymbol.push(new CHash());
		tofuncmap=&funcmap;
		funcmap=*(new hash_map<string,Node*>());
		//进入类的作用域，将类中的变量信息存储
		//question类与变量
		cout<<"更换"<<endl;

#line 2718 "myparser.cpp"
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
		"valueexpr: ID",
		"valueexpr: valueexpr CLASSMC valueexpr",
		"valueexpr: valueexpr POINT valueexpr",
		"valueexpr: ALGCMUL valueexpr",
		"valueexpr: valueexpr LBRACEM expr RBRACEM",
		"valueexpr: ALGCTADD valueexpr",
		"valueexpr: ALGCTMINUS valueexpr",
		"valueexpr: LBRACESS valueexpr RBRACESS",
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
		"calexpr: BTCN expr",
		"calexpr: expr BTCRIGHT expr",
		"calexpr: expr BTCLEFT expr",
		"calexpr: expr BTCAND expr",
		"calexpr: expr BTCOR expr",
		"calexpr: expr BTCYH expr",
		"calexpr: ID LBRACESS exprlist RBRACESS",
		"calexpr: valueexpr CLASSMC ID LBRACESS exprlist RBRACESS",
		"calexpr: valueexpr POINT ID LBRACESS exprlist RBRACESS",
		"calexpr: ID LBRACESS RBRACESS",
		"calexpr: valueexpr CLASSMC ID LBRACESS RBRACESS",
		"calexpr: valueexpr POINT ID LBRACESS RBRACESS",
		"calexpr: LGCCN expr",
		"calexpr: expr LGCCMOREEQ expr",
		"calexpr: expr LGCCLESSEQ expr",
		"calexpr: expr LBRACES expr",
		"calexpr: expr RBRACES expr",
		"calexpr: expr LGCCEQ expr",
		"calexpr: expr LGCCNEQ expr",
		"calexpr: expr LGCCAND expr",
		"calexpr: expr LGCCOR expr",
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
		"classdef: class ID LBRACE inclass RBRACE SEMI",
		"classdef: class ID LBRACE inclass RBRACE error",
		"class: CLASS"
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
		{ 9, 1, 23 },
		{ 9, 3, 24 },
		{ 9, 3, 25 },
		{ 9, 2, 26 },
		{ 9, 4, 27 },
		{ 9, 2, 28 },
		{ 9, 2, 29 },
		{ 9, 3, 30 },
		{ 10, 3, 31 },
		{ 10, 3, 32 },
		{ 10, 3, 33 },
		{ 10, 3, 34 },
		{ 10, 3, 35 },
		{ 10, 3, 36 },
		{ 10, 2, 37 },
		{ 10, 1, 38 },
		{ 10, 1, 39 },
		{ 10, 1, 40 },
		{ 10, 1, 41 },
		{ 10, 1, 42 },
		{ 10, 2, 43 },
		{ 10, 2, 44 },
		{ 10, 2, 45 },
		{ 10, 3, 46 },
		{ 10, 3, 47 },
		{ 10, 3, 48 },
		{ 10, 3, 49 },
		{ 10, 3, 50 },
		{ 10, 4, 51 },
		{ 10, 6, 52 },
		{ 10, 6, 53 },
		{ 10, 3, 54 },
		{ 10, 5, 55 },
		{ 10, 5, 56 },
		{ 10, 2, 57 },
		{ 10, 3, 58 },
		{ 10, 3, 59 },
		{ 10, 3, 60 },
		{ 10, 3, 61 },
		{ 10, 3, 62 },
		{ 10, 3, 63 },
		{ 10, 3, 64 },
		{ 10, 3, 65 },
		{ 10, 3, 66 },
		{ 10, 2, 67 },
		{ 11, 3, 68 },
		{ 12, 2, 69 },
		{ 12, 3, 70 },
		{ 12, 1, 71 },
		{ 12, 1, -1 },
		{ 12, 1, -1 },
		{ 12, 1, -1 },
		{ 12, 1, -1 },
		{ 12, 1, -1 },
		{ 12, 1, -1 },
		{ 12, 1, 72 },
		{ 13, 2, 73 },
		{ 13, 2, 74 },
		{ 13, 1, 75 },
		{ 13, 1, 76 },
		{ 14, 4, 77 },
		{ 14, 3, 78 },
		{ 15, 0, 79 },
		{ 16, 1, -1 },
		{ 16, 1, -1 },
		{ 17, 7, 80 },
		{ 17, 5, 81 },
		{ 17, 7, 82 },
		{ 17, 5, 83 },
		{ 18, 5, 84 },
		{ 18, 5, 85 },
		{ 19, 9, 86 },
		{ 19, 8, 87 },
		{ 19, 8, 88 },
		{ 19, 8, 89 },
		{ 19, 7, 90 },
		{ 19, 7, 91 },
		{ 19, 7, 92 },
		{ 19, 6, 93 },
		{ 20, 3, 94 },
		{ 20, 2, 95 },
		{ 21, 3, 96 },
		{ 22, 3, 97 },
		{ 22, 2, 98 },
		{ 23, 3, 99 },
		{ 24, 1, -1 },
		{ 24, 2, 100 },
		{ 25, 4, 101 },
		{ 25, 7, 102 },
		{ 25, 2, 103 },
		{ 25, 5, 104 },
		{ 26, 6, 105 },
		{ 26, 7, 106 },
		{ 26, 5, 107 },
		{ 26, 6, 108 },
		{ 27, 5, 109 },
		{ 27, 5, 110 },
		{ 28, 2, 111 },
		{ 28, 2, 112 },
		{ 28, 1, 113 },
		{ 28, 1, 114 },
		{ 29, 6, 115 },
		{ 29, 6, 116 },
		{ 30, 1, 117 }
	};
	yyreduction = reduction;

	yytokenaction_size = 528;

	static const yytokenaction_t YYNEARFAR YYBASED_CODE tokenaction[] = {
		{ 10, YYAT_ACCEPT, 0 },
		{ 266, YYAT_SHIFT, 92 },
		{ 266, YYAT_SHIFT, 93 },
		{ 266, YYAT_SHIFT, 94 },
		{ 266, YYAT_SHIFT, 95 },
		{ 266, YYAT_SHIFT, 96 },
		{ 146, YYAT_SHIFT, 92 },
		{ 146, YYAT_SHIFT, 93 },
		{ 146, YYAT_SHIFT, 94 },
		{ 146, YYAT_SHIFT, 95 },
		{ 146, YYAT_SHIFT, 96 },
		{ 65, YYAT_SHIFT, 118 },
		{ 69, YYAT_SHIFT, 121 },
		{ 215, YYAT_SHIFT, 230 },
		{ 266, YYAT_SHIFT, 270 },
		{ 266, YYAT_SHIFT, 97 },
		{ 223, YYAT_SHIFT, 47 },
		{ 212, YYAT_SHIFT, 227 },
		{ 73, YYAT_SHIFT, 124 },
		{ 223, YYAT_SHIFT, 48 },
		{ 223, YYAT_SHIFT, 49 },
		{ 208, YYAT_SHIFT, 92 },
		{ 208, YYAT_SHIFT, 93 },
		{ 208, YYAT_SHIFT, 94 },
		{ 208, YYAT_SHIFT, 95 },
		{ 208, YYAT_SHIFT, 96 },
		{ 223, YYAT_SHIFT, 80 },
		{ 215, YYAT_SHIFT, 231 },
		{ 145, YYAT_SHIFT, 92 },
		{ 145, YYAT_SHIFT, 93 },
		{ 145, YYAT_SHIFT, 94 },
		{ 145, YYAT_SHIFT, 95 },
		{ 145, YYAT_SHIFT, 96 },
		{ 214, YYAT_SHIFT, 228 },
		{ 171, YYAT_REDUCE, 23 },
		{ 208, YYAT_SHIFT, 97 },
		{ 65, YYAT_SHIFT, 119 },
		{ 174, YYAT_SHIFT, 22 },
		{ 32, YYAT_SHIFT, 64 },
		{ 8, YYAT_SHIFT, 18 },
		{ 236, YYAT_SHIFT, 113 },
		{ 256, YYAT_SHIFT, 264 },
		{ 266, YYAT_SHIFT, 98 },
		{ 266, YYAT_SHIFT, 99 },
		{ 171, YYAT_SHIFT, 91 },
		{ 254, YYAT_SHIFT, 262 },
		{ 236, YYAT_SHIFT, 129 },
		{ 214, YYAT_SHIFT, 229 },
		{ 212, YYAT_SHIFT, 188 },
		{ 73, YYAT_SHIFT, 76 },
		{ 266, YYAT_SHIFT, 100 },
		{ 266, YYAT_SHIFT, 101 },
		{ 266, YYAT_SHIFT, 102 },
		{ 266, YYAT_SHIFT, 103 },
		{ 266, YYAT_SHIFT, 104 },
		{ 266, YYAT_SHIFT, 105 },
		{ 69, YYAT_SHIFT, 122 },
		{ 266, YYAT_SHIFT, 106 },
		{ 266, YYAT_SHIFT, 107 },
		{ 266, YYAT_SHIFT, 108 },
		{ 266, YYAT_SHIFT, 109 },
		{ 266, YYAT_SHIFT, 110 },
		{ 208, YYAT_SHIFT, 98 },
		{ 208, YYAT_SHIFT, 99 },
		{ 236, YYAT_SHIFT, 130 },
		{ 146, YYAT_SHIFT, 109 },
		{ 146, YYAT_SHIFT, 110 },
		{ 61, YYAT_SHIFT, 111 },
		{ 61, YYAT_SHIFT, 112 },
		{ 248, YYAT_SHIFT, 257 },
		{ 208, YYAT_SHIFT, 100 },
		{ 208, YYAT_SHIFT, 101 },
		{ 208, YYAT_SHIFT, 102 },
		{ 208, YYAT_SHIFT, 103 },
		{ 208, YYAT_SHIFT, 104 },
		{ 208, YYAT_SHIFT, 105 },
		{ 223, YYAT_SHIFT, 81 },
		{ 208, YYAT_SHIFT, 106 },
		{ 208, YYAT_SHIFT, 107 },
		{ 208, YYAT_SHIFT, 108 },
		{ 208, YYAT_SHIFT, 109 },
		{ 208, YYAT_SHIFT, 110 },
		{ 160, YYAT_SHIFT, 92 },
		{ 160, YYAT_SHIFT, 93 },
		{ 160, YYAT_SHIFT, 94 },
		{ 160, YYAT_SHIFT, 95 },
		{ 160, YYAT_SHIFT, 96 },
		{ 145, YYAT_SHIFT, 109 },
		{ 145, YYAT_SHIFT, 110 },
		{ 143, YYAT_SHIFT, 92 },
		{ 143, YYAT_SHIFT, 93 },
		{ 143, YYAT_SHIFT, 94 },
		{ 143, YYAT_SHIFT, 95 },
		{ 143, YYAT_SHIFT, 96 },
		{ 171, YYAT_REDUCE, 23 },
		{ 128, YYAT_SHIFT, 131 },
		{ 160, YYAT_SHIFT, 97 },
		{ 174, YYAT_SHIFT, 23 },
		{ 32, YYAT_SHIFT, 65 },
		{ 8, YYAT_SHIFT, 19 },
		{ 200, YYAT_SHIFT, 222 },
		{ 61, YYAT_SHIFT, 113 },
		{ 141, YYAT_SHIFT, 92 },
		{ 141, YYAT_SHIFT, 93 },
		{ 141, YYAT_SHIFT, 94 },
		{ 141, YYAT_SHIFT, 95 },
		{ 141, YYAT_SHIFT, 96 },
		{ 61, YYAT_SHIFT, 114 },
		{ 247, YYAT_SHIFT, 255 },
		{ 142, YYAT_SHIFT, 92 },
		{ 142, YYAT_SHIFT, 93 },
		{ 142, YYAT_SHIFT, 94 },
		{ 142, YYAT_SHIFT, 95 },
		{ 142, YYAT_SHIFT, 96 },
		{ 198, YYAT_SHIFT, 219 },
		{ 25, YYAT_SHIFT, 35 },
		{ 141, YYAT_SHIFT, 97 },
		{ 200, YYAT_SHIFT, 223 },
		{ 24, YYAT_SHIFT, 34 },
		{ 24, YYAT_SHIFT, 32 },
		{ 19, YYAT_SHIFT, 28 },
		{ 128, YYAT_SHIFT, 113 },
		{ 19, YYAT_SHIFT, 29 },
		{ 160, YYAT_SHIFT, 98 },
		{ 160, YYAT_SHIFT, 99 },
		{ 61, YYAT_SHIFT, 115 },
		{ 246, YYAT_SHIFT, 253 },
		{ 128, YYAT_SHIFT, 129 },
		{ 245, YYAT_SHIFT, 252 },
		{ 25, YYAT_SHIFT, 36 },
		{ 198, YYAT_SHIFT, 220 },
		{ 160, YYAT_SHIFT, 100 },
		{ 160, YYAT_SHIFT, 101 },
		{ 160, YYAT_SHIFT, 102 },
		{ 160, YYAT_SHIFT, 103 },
		{ 160, YYAT_SHIFT, 104 },
		{ 160, YYAT_SHIFT, 105 },
		{ 241, YYAT_SHIFT, 250 },
		{ 160, YYAT_SHIFT, 106 },
		{ 160, YYAT_SHIFT, 107 },
		{ 160, YYAT_SHIFT, 108 },
		{ 160, YYAT_SHIFT, 109 },
		{ 160, YYAT_SHIFT, 110 },
		{ 141, YYAT_SHIFT, 98 },
		{ 141, YYAT_SHIFT, 99 },
		{ 128, YYAT_SHIFT, 130 },
		{ 23, YYAT_SHIFT, 29 },
		{ 19, YYAT_SHIFT, 30 },
		{ 143, YYAT_SHIFT, 109 },
		{ 143, YYAT_SHIFT, 110 },
		{ 239, YYAT_SHIFT, 249 },
		{ 141, YYAT_SHIFT, 100 },
		{ 141, YYAT_SHIFT, 101 },
		{ 141, YYAT_SHIFT, 102 },
		{ 141, YYAT_SHIFT, 103 },
		{ 141, YYAT_SHIFT, 104 },
		{ 141, YYAT_SHIFT, 105 },
		{ 234, YYAT_SHIFT, 247 },
		{ 141, YYAT_SHIFT, 106 },
		{ 141, YYAT_SHIFT, 107 },
		{ 141, YYAT_SHIFT, 108 },
		{ 141, YYAT_SHIFT, 109 },
		{ 141, YYAT_SHIFT, 110 },
		{ 135, YYAT_SHIFT, 92 },
		{ 135, YYAT_SHIFT, 93 },
		{ 135, YYAT_SHIFT, 94 },
		{ 135, YYAT_SHIFT, 95 },
		{ 135, YYAT_SHIFT, 96 },
		{ 142, YYAT_SHIFT, 109 },
		{ 142, YYAT_SHIFT, 110 },
		{ 221, YYAT_SHIFT, 113 },
		{ 23, YYAT_SHIFT, 30 },
		{ 159, YYAT_SHIFT, 113 },
		{ 233, YYAT_SHIFT, 246 },
		{ 157, YYAT_SHIFT, 113 },
		{ 84, YYAT_SHIFT, 113 },
		{ 221, YYAT_SHIFT, 129 },
		{ 135, YYAT_SHIFT, 97 },
		{ 159, YYAT_SHIFT, 129 },
		{ 232, YYAT_SHIFT, 244 },
		{ 157, YYAT_SHIFT, 129 },
		{ 84, YYAT_SHIFT, 129 },
		{ 83, YYAT_SHIFT, 113 },
		{ 60, YYAT_SHIFT, 92 },
		{ 60, YYAT_SHIFT, 93 },
		{ 60, YYAT_SHIFT, 94 },
		{ 60, YYAT_SHIFT, 95 },
		{ 60, YYAT_SHIFT, 96 },
		{ 83, YYAT_SHIFT, 129 },
		{ 154, YYAT_SHIFT, 92 },
		{ 154, YYAT_SHIFT, 93 },
		{ 154, YYAT_SHIFT, 94 },
		{ 154, YYAT_SHIFT, 95 },
		{ 154, YYAT_SHIFT, 96 },
		{ 221, YYAT_SHIFT, 130 },
		{ 225, YYAT_SHIFT, 237 },
		{ 159, YYAT_SHIFT, 130 },
		{ 60, YYAT_SHIFT, 97 },
		{ 157, YYAT_SHIFT, 130 },
		{ 84, YYAT_SHIFT, 130 },
		{ 220, YYAT_ERROR, 0 },
		{ 217, YYAT_SHIFT, 234 },
		{ 82, YYAT_SHIFT, 113 },
		{ 216, YYAT_SHIFT, 232 },
		{ 135, YYAT_SHIFT, 98 },
		{ 135, YYAT_SHIFT, 99 },
		{ 83, YYAT_SHIFT, 130 },
		{ 210, YYAT_SHIFT, 226 },
		{ 82, YYAT_SHIFT, 129 },
		{ 137, YYAT_SHIFT, 94 },
		{ 137, YYAT_SHIFT, 95 },
		{ 137, YYAT_SHIFT, 96 },
		{ 135, YYAT_SHIFT, 100 },
		{ 135, YYAT_SHIFT, 101 },
		{ 135, YYAT_SHIFT, 102 },
		{ 135, YYAT_SHIFT, 103 },
		{ 135, YYAT_SHIFT, 104 },
		{ 135, YYAT_SHIFT, 105 },
		{ 206, YYAT_SHIFT, 225 },
		{ 135, YYAT_SHIFT, 106 },
		{ 135, YYAT_SHIFT, 107 },
		{ 135, YYAT_SHIFT, 108 },
		{ 135, YYAT_SHIFT, 109 },
		{ 135, YYAT_SHIFT, 110 },
		{ 60, YYAT_SHIFT, 98 },
		{ 60, YYAT_SHIFT, 99 },
		{ 82, YYAT_SHIFT, 130 },
		{ 153, YYAT_SHIFT, 92 },
		{ 153, YYAT_SHIFT, 93 },
		{ 153, YYAT_SHIFT, 94 },
		{ 153, YYAT_SHIFT, 95 },
		{ 153, YYAT_SHIFT, 96 },
		{ 60, YYAT_SHIFT, 100 },
		{ 60, YYAT_SHIFT, 101 },
		{ 60, YYAT_SHIFT, 102 },
		{ 60, YYAT_SHIFT, 103 },
		{ 60, YYAT_SHIFT, 104 },
		{ 60, YYAT_SHIFT, 105 },
		{ 201, YYAT_SHIFT, 224 },
		{ 60, YYAT_SHIFT, 106 },
		{ 60, YYAT_SHIFT, 107 },
		{ 60, YYAT_SHIFT, 108 },
		{ 60, YYAT_SHIFT, 109 },
		{ 60, YYAT_SHIFT, 110 },
		{ 196, YYAT_SHIFT, 216 },
		{ 235, YYAT_SHIFT, 92 },
		{ 235, YYAT_SHIFT, 93 },
		{ 235, YYAT_SHIFT, 94 },
		{ 235, YYAT_SHIFT, 95 },
		{ 235, YYAT_SHIFT, 96 },
		{ 76, YYAT_SHIFT, 37 },
		{ 76, YYAT_SHIFT, 2 },
		{ 76, YYAT_SHIFT, 3 },
		{ 76, YYAT_SHIFT, 4 },
		{ 136, YYAT_SHIFT, 94 },
		{ 136, YYAT_SHIFT, 95 },
		{ 136, YYAT_SHIFT, 96 },
		{ 193, YYAT_SHIFT, 213 },
		{ 191, YYAT_SHIFT, 211 },
		{ 235, YYAT_SHIFT, 97 },
		{ 190, YYAT_SHIFT, 209 },
		{ 186, YYAT_SHIFT, 207 },
		{ 185, YYAT_SHIFT, 206 },
		{ 175, YYAT_SHIFT, 205 },
		{ 172, YYAT_SHIFT, 202 },
		{ 218, YYAT_SHIFT, 92 },
		{ 218, YYAT_SHIFT, 93 },
		{ 218, YYAT_SHIFT, 94 },
		{ 218, YYAT_SHIFT, 95 },
		{ 218, YYAT_SHIFT, 96 },
		{ 167, YYAT_SHIFT, 199 },
		{ 166, YYAT_SHIFT, 197 },
		{ 10, YYAT_SHIFT, 1 },
		{ 165, YYAT_SHIFT, 196 },
		{ 164, YYAT_SHIFT, 195 },
		{ 163, YYAT_SHIFT, 194 },
		{ 162, YYAT_SHIFT, 193 },
		{ 161, YYAT_SHIFT, 192 },
		{ 158, YYAT_SHIFT, 191 },
		{ 218, YYAT_SHIFT, 97 },
		{ 156, YYAT_SHIFT, 190 },
		{ 155, YYAT_SHIFT, 189 },
		{ 134, YYAT_SHIFT, 187 },
		{ 127, YYAT_SHIFT, 186 },
		{ 126, YYAT_SHIFT, 185 },
		{ 10, YYAT_SHIFT, 5 },
		{ 235, YYAT_SHIFT, 98 },
		{ 235, YYAT_SHIFT, 99 },
		{ 149, YYAT_SHIFT, 92 },
		{ 149, YYAT_SHIFT, 93 },
		{ 149, YYAT_SHIFT, 94 },
		{ 149, YYAT_SHIFT, 95 },
		{ 149, YYAT_SHIFT, 96 },
		{ 124, YYAT_SHIFT, 66 },
		{ 235, YYAT_SHIFT, 100 },
		{ 235, YYAT_SHIFT, 101 },
		{ 235, YYAT_SHIFT, 102 },
		{ 235, YYAT_SHIFT, 103 },
		{ 235, YYAT_SHIFT, 104 },
		{ 235, YYAT_SHIFT, 105 },
		{ 120, YYAT_SHIFT, 169 },
		{ 235, YYAT_SHIFT, 106 },
		{ 235, YYAT_SHIFT, 107 },
		{ 235, YYAT_SHIFT, 108 },
		{ 119, YYAT_SHIFT, 161 },
		{ 235, YYAT_SHIFT, 110 },
		{ 218, YYAT_SHIFT, 98 },
		{ 218, YYAT_SHIFT, 99 },
		{ 148, YYAT_SHIFT, 92 },
		{ 148, YYAT_SHIFT, 93 },
		{ 148, YYAT_SHIFT, 94 },
		{ 148, YYAT_SHIFT, 95 },
		{ 148, YYAT_SHIFT, 96 },
		{ 115, YYAT_SHIFT, 158 },
		{ 218, YYAT_SHIFT, 100 },
		{ 218, YYAT_SHIFT, 101 },
		{ 218, YYAT_SHIFT, 102 },
		{ 218, YYAT_SHIFT, 103 },
		{ 218, YYAT_SHIFT, 104 },
		{ 218, YYAT_SHIFT, 105 },
		{ 114, YYAT_SHIFT, 156 },
		{ 218, YYAT_SHIFT, 106 },
		{ 218, YYAT_SHIFT, 107 },
		{ 218, YYAT_SHIFT, 108 },
		{ 91, YYAT_SHIFT, 133 },
		{ 218, YYAT_SHIFT, 110 },
		{ 87, YYAT_SHIFT, 132 },
		{ 85, YYAT_ERROR, 0 },
		{ 77, YYAT_SHIFT, 127 },
		{ 149, YYAT_SHIFT, 98 },
		{ 149, YYAT_SHIFT, 99 },
		{ 151, YYAT_SHIFT, 92 },
		{ 151, YYAT_SHIFT, 93 },
		{ 151, YYAT_SHIFT, 94 },
		{ 151, YYAT_SHIFT, 95 },
		{ 151, YYAT_SHIFT, 96 },
		{ 64, YYAT_SHIFT, 117 },
		{ 149, YYAT_SHIFT, 100 },
		{ 149, YYAT_SHIFT, 101 },
		{ 149, YYAT_SHIFT, 102 },
		{ 149, YYAT_SHIFT, 103 },
		{ 149, YYAT_SHIFT, 104 },
		{ 63, YYAT_SHIFT, 116 },
		{ 59, YYAT_SHIFT, 91 },
		{ 149, YYAT_SHIFT, 106 },
		{ 149, YYAT_SHIFT, 107 },
		{ 149, YYAT_SHIFT, 108 },
		{ 149, YYAT_SHIFT, 109 },
		{ 149, YYAT_SHIFT, 110 },
		{ 148, YYAT_SHIFT, 98 },
		{ 148, YYAT_SHIFT, 99 },
		{ 150, YYAT_SHIFT, 92 },
		{ 150, YYAT_SHIFT, 93 },
		{ 150, YYAT_SHIFT, 94 },
		{ 150, YYAT_SHIFT, 95 },
		{ 150, YYAT_SHIFT, 96 },
		{ 45, YYAT_SHIFT, 78 },
		{ 148, YYAT_SHIFT, 100 },
		{ 148, YYAT_SHIFT, 101 },
		{ 148, YYAT_SHIFT, 102 },
		{ 148, YYAT_SHIFT, 103 },
		{ 44, YYAT_SHIFT, 77 },
		{ 43, YYAT_SHIFT, 75 },
		{ 41, YYAT_SHIFT, 72 },
		{ 148, YYAT_SHIFT, 106 },
		{ 148, YYAT_SHIFT, 107 },
		{ 148, YYAT_SHIFT, 108 },
		{ 148, YYAT_SHIFT, 109 },
		{ 148, YYAT_SHIFT, 110 },
		{ 38, YYAT_SHIFT, 69 },
		{ 30, YYAT_SHIFT, 63 },
		{ 28, YYAT_SHIFT, 42 },
		{ 151, YYAT_SHIFT, 98 },
		{ 151, YYAT_SHIFT, 99 },
		{ 27, YYAT_SHIFT, 41 },
		{ 26, YYAT_SHIFT, 6 },
		{ 22, YYAT_SHIFT, 33 },
		{ 20, YYAT_SHIFT, 31 },
		{ 18, YYAT_SHIFT, 27 },
		{ 17, YYAT_SHIFT, 26 },
		{ 151, YYAT_SHIFT, 100 },
		{ 151, YYAT_SHIFT, 101 },
		{ 151, YYAT_SHIFT, 102 },
		{ 151, YYAT_SHIFT, 103 },
		{ 16, YYAT_SHIFT, 25 },
		{ 7, YYAT_SHIFT, 17 },
		{ 1, YYAT_SHIFT, 16 },
		{ 151, YYAT_SHIFT, 106 },
		{ 0, YYAT_ERROR, 0 },
		{ 151, YYAT_SHIFT, 108 },
		{ 151, YYAT_SHIFT, 109 },
		{ 151, YYAT_SHIFT, 110 },
		{ 150, YYAT_SHIFT, 98 },
		{ 150, YYAT_SHIFT, 99 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 150, YYAT_SHIFT, 100 },
		{ 150, YYAT_SHIFT, 101 },
		{ 150, YYAT_SHIFT, 102 },
		{ 150, YYAT_SHIFT, 103 },
		{ 152, YYAT_SHIFT, 92 },
		{ 152, YYAT_SHIFT, 93 },
		{ 152, YYAT_SHIFT, 94 },
		{ 152, YYAT_SHIFT, 95 },
		{ 152, YYAT_SHIFT, 96 },
		{ 150, YYAT_SHIFT, 108 },
		{ 150, YYAT_SHIFT, 109 },
		{ 150, YYAT_SHIFT, 110 },
		{ 270, YYAT_SHIFT, 162 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 270, YYAT_SHIFT, 37 },
		{ 270, YYAT_SHIFT, 2 },
		{ 270, YYAT_SHIFT, 3 },
		{ 270, YYAT_SHIFT, 4 },
		{ 270, YYAT_SHIFT, 163 },
		{ -1, YYAT_ERROR, 0 },
		{ 270, YYAT_SHIFT, 164 },
		{ 270, YYAT_SHIFT, 165 },
		{ 257, YYAT_SHIFT, 46 },
		{ -1, YYAT_ERROR, 0 },
		{ 270, YYAT_SHIFT, 166 },
		{ 270, YYAT_SHIFT, 167 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 257, YYAT_SHIFT, 50 },
		{ 257, YYAT_SHIFT, 51 },
		{ 257, YYAT_SHIFT, 52 },
		{ 257, YYAT_SHIFT, 53 },
		{ 257, YYAT_SHIFT, 54 },
		{ 257, YYAT_SHIFT, 55 },
		{ 257, YYAT_SHIFT, 265 },
		{ 270, YYAT_SHIFT, 168 },
		{ 270, YYAT_SHIFT, 66 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 270, YYAT_SHIFT, 170 },
		{ -1, YYAT_ERROR, 0 },
		{ 152, YYAT_SHIFT, 98 },
		{ 152, YYAT_SHIFT, 99 },
		{ 147, YYAT_SHIFT, 92 },
		{ 147, YYAT_SHIFT, 93 },
		{ 147, YYAT_SHIFT, 94 },
		{ 147, YYAT_SHIFT, 95 },
		{ 147, YYAT_SHIFT, 96 },
		{ -1, YYAT_ERROR, 0 },
		{ 152, YYAT_SHIFT, 100 },
		{ 152, YYAT_SHIFT, 101 },
		{ 152, YYAT_SHIFT, 102 },
		{ 152, YYAT_SHIFT, 103 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 270, YYAT_SHIFT, 171 },
		{ 152, YYAT_SHIFT, 109 },
		{ 152, YYAT_SHIFT, 110 },
		{ 86, YYAT_SHIFT, 111 },
		{ 86, YYAT_SHIFT, 112 },
		{ 144, YYAT_SHIFT, 92 },
		{ 144, YYAT_SHIFT, 93 },
		{ 144, YYAT_SHIFT, 94 },
		{ 144, YYAT_SHIFT, 95 },
		{ 144, YYAT_SHIFT, 96 },
		{ -1, YYAT_ERROR, 0 },
		{ 86, YYAT_SHIFT, 131 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 257, YYAT_SHIFT, 56 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 257, YYAT_SHIFT, 57 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 257, YYAT_SHIFT, 58 },
		{ 257, YYAT_SHIFT, 59 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 147, YYAT_SHIFT, 98 },
		{ 147, YYAT_SHIFT, 99 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 147, YYAT_SHIFT, 101 },
		{ 147, YYAT_SHIFT, 102 },
		{ 86, YYAT_SHIFT, 113 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 86, YYAT_SHIFT, 114 },
		{ 147, YYAT_SHIFT, 109 },
		{ 147, YYAT_SHIFT, 110 },
		{ 144, YYAT_SHIFT, 98 },
		{ 144, YYAT_SHIFT, 99 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 144, YYAT_SHIFT, 101 },
		{ 144, YYAT_SHIFT, 102 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 86, YYAT_SHIFT, 115 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 144, YYAT_SHIFT, 109 },
		{ 144, YYAT_SHIFT, 110 }
	};
	yytokenaction = tokenaction;

	static const yystateaction_t YYNEARFAR YYBASED_CODE stateaction[] = {
		{ 388, 1, YYAT_DEFAULT, 10 },
		{ 106, 1, YYAT_REDUCE, 7 },
		{ 0, 0, YYAT_REDUCE, 9 },
		{ 0, 0, YYAT_REDUCE, 8 },
		{ 0, 0, YYAT_REDUCE, 10 },
		{ 0, 0, YYAT_REDUCE, 129 },
		{ 0, 0, YYAT_REDUCE, 23 },
		{ 66, 1, YYAT_ERROR, 0 },
		{ -220, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 5 },
		{ 0, 1, YYAT_DEFAULT, 26 },
		{ 0, 0, YYAT_REDUCE, 1 },
		{ 0, 0, YYAT_REDUCE, 6 },
		{ 0, 0, YYAT_REDUCE, 3 },
		{ 0, 0, YYAT_REDUCE, 4 },
		{ 0, 0, YYAT_DEFAULT, 174 },
		{ 115, 1, YYAT_ERROR, 0 },
		{ 85, 1, YYAT_ERROR, 0 },
		{ 59, 1, YYAT_ERROR, 0 },
		{ -149, 1, YYAT_REDUCE, 12 },
		{ 77, 1, YYAT_DEFAULT, 24 },
		{ 0, 0, YYAT_REDUCE, 2 },
		{ 57, 1, YYAT_ERROR, 0 },
		{ -125, 1, YYAT_REDUCE, 12 },
		{ -182, 1, YYAT_ERROR, 0 },
		{ -141, 1, YYAT_ERROR, 0 },
		{ 56, 1, YYAT_DEFAULT, 76 },
		{ 105, 1, YYAT_REDUCE, 17 },
		{ 101, 1, YYAT_DEFAULT, 76 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 106, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 21 },
		{ -221, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 17 },
		{ 0, 0, YYAT_REDUCE, 22 },
		{ 0, 0, YYAT_DEFAULT, 124 },
		{ 0, 0, YYAT_DEFAULT, 124 },
		{ 0, 0, YYAT_REDUCE, 7 },
		{ 74, 1, YYAT_DEFAULT, 26 },
		{ 0, 0, YYAT_REDUCE, 126 },
		{ 0, 0, YYAT_REDUCE, 125 },
		{ 93, 1, YYAT_DEFAULT, 76 },
		{ 0, 0, YYAT_DEFAULT, 124 },
		{ 92, 1, YYAT_DEFAULT, 73 },
		{ 42, 1, YYAT_ERROR, 0 },
		{ 97, 1, YYAT_REDUCE, 111 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 223 },
		{ 0, 0, YYAT_DEFAULT, 223 },
		{ 0, 0, YYAT_DEFAULT, 223 },
		{ 0, 0, YYAT_REDUCE, 41 },
		{ 0, 0, YYAT_REDUCE, 42 },
		{ 0, 0, YYAT_REDUCE, 44 },
		{ 0, 0, YYAT_REDUCE, 45 },
		{ 0, 0, YYAT_REDUCE, 43 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 74, 1, YYAT_REDUCE, 26 },
		{ -74, 1, YYAT_REDUCE, 14 },
		{ -195, 1, YYAT_REDUCE, 24 },
		{ 0, 0, YYAT_REDUCE, 25 },
		{ 45, 1, YYAT_ERROR, 0 },
		{ 17, 1, YYAT_ERROR, 0 },
		{ -260, 1, YYAT_REDUCE, 11 },
		{ 0, 0, YYAT_REDUCE, 88 },
		{ 0, 0, YYAT_REDUCE, 122 },
		{ 0, 0, YYAT_REDUCE, 121 },
		{ -244, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 124 },
		{ 0, 0, YYAT_REDUCE, 123 },
		{ 0, 0, YYAT_DEFAULT, 124 },
		{ -252, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 119 },
		{ 0, 0, YYAT_DEFAULT, 124 },
		{ -22, 1, YYAT_ERROR, 0 },
		{ 32, 1, YYAT_REDUCE, 115 },
		{ 0, 0, YYAT_REDUCE, 112 },
		{ 0, 0, YYAT_REDUCE, 40 },
		{ 0, 0, YYAT_DEFAULT, 223 },
		{ 0, 0, YYAT_REDUCE, 26 },
		{ -94, 1, YYAT_REDUCE, 29 },
		{ -114, 1, YYAT_REDUCE, 31 },
		{ -121, 1, YYAT_REDUCE, 32 },
		{ 57, 1, YYAT_DEFAULT, 266 },
		{ 203, 1, YYAT_REDUCE, 24 },
		{ 56, 1, YYAT_REDUCE, 25 },
		{ 0, 0, YYAT_REDUCE, 60 },
		{ 0, 0, YYAT_REDUCE, 70 },
		{ 0, 0, YYAT_REDUCE, 48 },
		{ 54, 1, YYAT_DEFAULT, 257 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_REDUCE, 46 },
		{ 0, 0, YYAT_REDUCE, 47 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 1, 1, YYAT_DEFAULT, 223 },
		{ -6, 1, YYAT_DEFAULT, 223 },
		{ 0, 0, YYAT_REDUCE, 18 },
		{ 0, 0, YYAT_REDUCE, 15 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 40, 1, YYAT_ERROR, 0 },
		{ 5, 1, YYAT_DEFAULT, 270 },
		{ 0, 0, YYAT_REDUCE, 128 },
		{ 0, 0, YYAT_REDUCE, 127 },
		{ 0, 0, YYAT_REDUCE, 120 },
		{ -1, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 117 },
		{ -35, 1, YYAT_ERROR, 0 },
		{ 19, 1, YYAT_ERROR, 0 },
		{ -175, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 223 },
		{ 0, 0, YYAT_DEFAULT, 223 },
		{ 0, 0, YYAT_REDUCE, 33 },
		{ 0, 0, YYAT_REDUCE, 39 },
		{ 0, 0, YYAT_REDUCE, 57 },
		{ 12, 1, YYAT_DEFAULT, 212 },
		{ -94, 1, YYAT_REDUCE, 20 },
		{ -5, 1, YYAT_REDUCE, 34 },
		{ -50, 1, YYAT_REDUCE, 35 },
		{ 0, 0, YYAT_REDUCE, 36 },
		{ 0, 0, YYAT_REDUCE, 37 },
		{ 0, 0, YYAT_REDUCE, 38 },
		{ -155, 1, YYAT_REDUCE, 69 },
		{ -148, 1, YYAT_REDUCE, 63 },
		{ -168, 1, YYAT_REDUCE, 64 },
		{ 210, 1, YYAT_REDUCE, 65 },
		{ -229, 1, YYAT_REDUCE, 62 },
		{ -251, 1, YYAT_REDUCE, 61 },
		{ 190, 1, YYAT_REDUCE, 66 },
		{ 51, 1, YYAT_REDUCE, 67 },
		{ 31, 1, YYAT_REDUCE, 68 },
		{ 94, 1, YYAT_REDUCE, 53 },
		{ 74, 1, YYAT_REDUCE, 52 },
		{ 147, 1, YYAT_REDUCE, 51 },
		{ -30, 1, YYAT_REDUCE, 50 },
		{ -68, 1, YYAT_REDUCE, 49 },
		{ -16, 1, YYAT_DEFAULT, 85 },
		{ 11, 1, YYAT_REDUCE, 26 },
		{ -122, 1, YYAT_REDUCE, 28 },
		{ 9, 1, YYAT_REDUCE, 26 },
		{ -124, 1, YYAT_REDUCE, 27 },
		{ -175, 1, YYAT_REDUCE, 13 },
		{ -20, 1, YYAT_ERROR, 0 },
		{ 20, 1, YYAT_DEFAULT, 220 },
		{ 6, 1, YYAT_ERROR, 0 },
		{ 5, 1, YYAT_ERROR, 0 },
		{ 4, 1, YYAT_ERROR, 0 },
		{ -45, 1, YYAT_ERROR, 0 },
		{ -47, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_REDUCE, 87 },
		{ 0, 0, YYAT_REDUCE, 81 },
		{ -225, 1, YYAT_REDUCE, 26 },
		{ -31, 1, YYAT_DEFAULT, 270 },
		{ 0, 0, YYAT_REDUCE, 84 },
		{ -222, 1, YYAT_ERROR, 0 },
		{ -37, 1, YYAT_DEFAULT, 248 },
		{ 0, 0, YYAT_REDUCE, 74 },
		{ 0, 0, YYAT_REDUCE, 76 },
		{ 0, 0, YYAT_REDUCE, 85 },
		{ 0, 0, YYAT_REDUCE, 80 },
		{ 0, 0, YYAT_REDUCE, 75 },
		{ 0, 0, YYAT_REDUCE, 78 },
		{ 0, 0, YYAT_REDUCE, 79 },
		{ 0, 0, YYAT_REDUCE, 77 },
		{ 0, 0, YYAT_REDUCE, 118 },
		{ -34, 1, YYAT_REDUCE, 113 },
		{ -36, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 54 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_REDUCE, 30 },
		{ -10, 1, YYAT_DEFAULT, 257 },
		{ -12, 1, YYAT_DEFAULT, 257 },
		{ 0, 0, YYAT_REDUCE, 16 },
		{ -43, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ -56, 1, YYAT_DEFAULT, 234 },
		{ 0, 0, YYAT_DEFAULT, 220 },
		{ -186, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 223 },
		{ -200, 1, YYAT_ERROR, 0 },
		{ -62, 1, YYAT_DEFAULT, 248 },
		{ 0, 0, YYAT_REDUCE, 86 },
		{ 0, 0, YYAT_REDUCE, 82 },
		{ 0, 0, YYAT_REDUCE, 83 },
		{ 0, 0, YYAT_REDUCE, 72 },
		{ -46, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 116 },
		{ -236, 1, YYAT_REDUCE, 19 },
		{ 0, 0, YYAT_REDUCE, 59 },
		{ -63, 1, YYAT_DEFAULT, 212 },
		{ 0, 0, YYAT_REDUCE, 58 },
		{ -253, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 73 },
		{ -223, 1, YYAT_DEFAULT, 266 },
		{ -243, 1, YYAT_DEFAULT, 266 },
		{ -97, 1, YYAT_DEFAULT, 234 },
		{ -99, 1, YYAT_DEFAULT, 248 },
		{ 8, 1, YYAT_REDUCE, 106 },
		{ 0, 0, YYAT_REDUCE, 107 },
		{ -70, 1, YYAT_DEFAULT, 257 },
		{ -126, 1, YYAT_REDUCE, 109 },
		{ 0, 0, YYAT_REDUCE, 110 },
		{ -243, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 71 },
		{ -102, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 56 },
		{ 0, 0, YYAT_REDUCE, 55 },
		{ 0, 0, YYAT_DEFAULT, 270 },
		{ 0, 0, YYAT_DEFAULT, 270 },
		{ 0, 0, YYAT_DEFAULT, 270 },
		{ 0, 0, YYAT_DEFAULT, 270 },
		{ -91, 1, YYAT_DEFAULT, 257 },
		{ -127, 1, YYAT_DEFAULT, 248 },
		{ -143, 1, YYAT_DEFAULT, 220 },
		{ -12, 1, YYAT_REDUCE, 105 },
		{ -256, 1, YYAT_REDUCE, 108 },
		{ 0, 0, YYAT_REDUCE, 114 },
		{ 0, 0, YYAT_REDUCE, 90 },
		{ -127, 1, YYAT_REDUCE, 94 },
		{ 0, 0, YYAT_REDUCE, 89 },
		{ -140, 1, YYAT_REDUCE, 92 },
		{ 0, 0, YYAT_REDUCE, 96 },
		{ 0, 0, YYAT_REDUCE, 95 },
		{ 0, 0, YYAT_DEFAULT, 270 },
		{ -142, 1, YYAT_DEFAULT, 266 },
		{ -144, 1, YYAT_DEFAULT, 257 },
		{ -162, 1, YYAT_DEFAULT, 257 },
		{ -231, 1, YYAT_DEFAULT, 85 },
		{ 0, 0, YYAT_DEFAULT, 270 },
		{ 0, 0, YYAT_DEFAULT, 270 },
		{ 0, 0, YYAT_REDUCE, 104 },
		{ 0, 0, YYAT_DEFAULT, 270 },
		{ 0, 0, YYAT_DEFAULT, 270 },
		{ -225, 1, YYAT_DEFAULT, 266 },
		{ 0, 0, YYAT_DEFAULT, 270 },
		{ -229, 1, YYAT_DEFAULT, 266 },
		{ 165, 1, YYAT_DEFAULT, 223 },
		{ 0, 0, YYAT_REDUCE, 93 },
		{ 0, 0, YYAT_REDUCE, 91 },
		{ 0, 0, YYAT_REDUCE, 103 },
		{ 0, 0, YYAT_REDUCE, 102 },
		{ 0, 0, YYAT_DEFAULT, 270 },
		{ 0, 0, YYAT_REDUCE, 101 },
		{ 0, 0, YYAT_DEFAULT, 270 },
		{ 0, 0, YYAT_DEFAULT, 270 },
		{ -256, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 100 },
		{ 0, 0, YYAT_REDUCE, 99 },
		{ 0, 0, YYAT_REDUCE, 98 },
		{ 143, 1, YYAT_DEFAULT, 234 },
		{ 0, 0, YYAT_REDUCE, 97 }
	};
	yystateaction = stateaction;

	yynontermgoto_size = 119;

	static const yynontermgoto_t YYNEARFAR YYBASED_CODE nontermgoto[] = {
		{ 270, 174 },
		{ 265, 269 },
		{ 10, 21 },
		{ 270, 176 },
		{ 270, 15 },
		{ 270, 175 },
		{ 10, 14 },
		{ 76, 45 },
		{ 270, 179 },
		{ 270, 240 },
		{ 264, 268 },
		{ 270, 238 },
		{ 26, 40 },
		{ 270, 271 },
		{ 270, 180 },
		{ 270, 177 },
		{ 270, 183 },
		{ 262, 267 },
		{ 270, 182 },
		{ 38, 8 },
		{ 270, 181 },
		{ 191, 212 },
		{ 38, 71 },
		{ 38, 15 },
		{ 191, 135 },
		{ 255, 263 },
		{ 10, 9 },
		{ 10, 12 },
		{ 76, 126 },
		{ 10, 13 },
		{ 10, 7 },
		{ 172, 204 },
		{ 26, 39 },
		{ 172, 203 },
		{ 26, 38 },
		{ 172, -1 },
		{ 257, 266 },
		{ 257, 61 },
		{ 257, 62 },
		{ 162, 85 },
		{ 162, 86 },
		{ 162, 87 },
		{ 38, 70 },
		{ 120, 178 },
		{ 120, 172 },
		{ 120, 173 },
		{ 41, 44 },
		{ 41, 73 },
		{ 0, 10 },
		{ 0, 11 },
		{ 253, 261 },
		{ 252, 260 },
		{ 250, 259 },
		{ 249, 258 },
		{ 247, 256 },
		{ 246, 254 },
		{ 244, 251 },
		{ 234, 248 },
		{ 232, 245 },
		{ 231, 243 },
		{ 230, 242 },
		{ 229, 241 },
		{ 228, 239 },
		{ 223, 236 },
		{ 220, 235 },
		{ 216, 233 },
		{ 199, 221 },
		{ 197, 218 },
		{ 196, 217 },
		{ 195, 215 },
		{ 194, 214 },
		{ 190, 210 },
		{ 188, 208 },
		{ 174, 20 },
		{ 168, 201 },
		{ 167, 200 },
		{ 166, 198 },
		{ 130, 159 },
		{ 129, 157 },
		{ 124, 184 },
		{ 118, 160 },
		{ 113, 155 },
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
		{ 92, 136 },
		{ 91, 134 },
		{ 80, 128 },
		{ 75, 125 },
		{ 72, 123 },
		{ 66, 120 },
		{ 58, 90 },
		{ 57, 89 },
		{ 56, 88 },
		{ 49, 84 },
		{ 48, 83 },
		{ 47, 82 },
		{ 46, 79 },
		{ 42, 74 },
		{ 36, 68 },
		{ 35, 67 },
		{ 29, 60 },
		{ 28, 43 },
		{ 15, 24 }
	};
	yynontermgoto = nontermgoto;

	static const yystategoto_t YYNEARFAR YYBASED_CODE stategoto[] = {
		{ 47, 10 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, 174 },
		{ 0, -1 },
		{ 0, 38 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
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
		{ 6, 38 },
		{ 0, -1 },
		{ 92, 41 },
		{ 108, 257 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 101, -1 },
		{ 100, -1 },
		{ 0, -1 },
		{ 16, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 22, 76 },
		{ 99, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 104, 257 },
		{ 102, -1 },
		{ 101, -1 },
		{ 100, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, 162 },
		{ 100, 257 },
		{ 99, 257 },
		{ 98, 257 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 90, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 90, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 89, -1 },
		{ 4, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 93, -1 },
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
		{ 96, 191 },
		{ 92, 257 },
		{ 91, 257 },
		{ 90, 257 },
		{ 89, 257 },
		{ 88, 257 },
		{ 87, 257 },
		{ 86, 257 },
		{ 85, 257 },
		{ 84, 257 },
		{ 83, 257 },
		{ 82, 257 },
		{ 81, 257 },
		{ 80, 257 },
		{ 79, 257 },
		{ 78, 257 },
		{ 77, 257 },
		{ 76, 257 },
		{ 75, 257 },
		{ 74, 257 },
		{ 0, -1 },
		{ 0, -1 },
		{ 73, 257 },
		{ 0, 129 },
		{ 0, 130 },
		{ 0, -1 },
		{ 0, -1 },
		{ 72, 257 },
		{ 0, -1 },
		{ 31, 172 },
		{ 0, -1 },
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
		{ 56, -1 },
		{ 53, -1 },
		{ 66, 257 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 19, 270 },
		{ 0, -1 },
		{ 69, -1 },
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
		{ 64, 257 },
		{ 0, -1 },
		{ 66, 191 },
		{ 16, 257 },
		{ 0, -1 },
		{ 0, -1 },
		{ 62, 257 },
		{ 61, 257 },
		{ 60, 257 },
		{ 59, 257 },
		{ 0, -1 },
		{ 57, -1 },
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
		{ 57, 257 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 56, 257 },
		{ 0, -1 },
		{ 0, -1 },
		{ 54, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 46, 270 },
		{ 45, 270 },
		{ 44, 270 },
		{ 43, 270 },
		{ 50, 257 },
		{ 0, -1 },
		{ 49, 257 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 40, 270 },
		{ 0, -1 },
		{ 47, 257 },
		{ 46, 257 },
		{ 0, -1 },
		{ 37, 270 },
		{ 36, 270 },
		{ 0, -1 },
		{ 35, 270 },
		{ 34, 270 },
		{ 0, -1 },
		{ 9, 270 },
		{ 0, -1 },
		{ 28, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 1, 270 },
		{ 0, -1 },
		{ -6, 270 },
		{ -15, 270 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ -3, 257 },
		{ 0, -1 }
	};
	yystategoto = stategoto;

	yydestructorptr = NULL;

	yytokendestptr = NULL;
	yytokendest_size = 0;

	yytokendestbaseptr = NULL;
	yytokendestbase_size = 0;
}
#line 1464 ".\\myparser.y"


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


int Fcode::num = 0;
int Fcode::labelnum = 0;
int main(int argc, char *argv[])
{
int n = 1;
	
//	allsymbol.push(symbtb);
//	Fcode::initnum();
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
			if(gtf){
			cout<<"error occurs,the tree cannot be built"<<endl;
			cout<<"see more info in file result.txt"<<endl;
			}
		}
		//storesymbol
		}
	}
	return n;
}


