%{
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



%}

/////////////////////////////////////////////////////////////////////////////
// declarations section


// parser name
%name myparser

// class definition
{
	// place any extra class members here
	
}

// constructor
{
	// place any extra initialisation code here
}

// destructor
{
	// place any extra cleanup code here
}

// attribute type
%include {
#ifndef YYSTYPE
//#define YYSTYPE string
#define YYSTYPE TreeNode*
#endif


}

// place any declarations here
%token ALGCADD ALGCMINUS ALGCMUL ALGCDIV ALGCMOD ALGCTADD ALGCTMINUS
%token NUMBERD DIGIT STRING ONECHAR FLOATD
%token LBRACESS RBRACESS
%token EQ
%token INT FLOAT CHAR VOID
%token IF ELSE WHILE FOR
%token MAIN
%token CONST COUT CIN ENDL
%token CLASS PUBLIC PRIVATE PROTECTED
%token INCLUDE USING NAMESPACE WELL
%token RETURN
%token LBRACE RBRACE LBRACEM RBRACEM LBRACES RBRACES LBRACESS RBRACESS
%token SEMI COMMA POINT QUES INVER COLON
%token LGCCEQ LGCCLESSEQ LGCCMOREEQ LGCCNEQ LGCCAND LGCCOR LGCCN
%token BTCYH BTCOR BTCAND BTCLEFT BTCRIGHT BTCN
%token ENDL ID
%token CLASSMC CLASSRST NEW DELETE ERRORCODE

%right EQ
%left LGCCOR
%left LGCCAND
%left BTCOR
%left BTCYH
%left BTCAND
%left LGCCEQ LGCCNEQ
%left LGCCMORE LGCCLESS LGCCMOREEQ LGCCLESSEQ LBRACES RBRACES
//注意LGCCMORE与LGCCLESS不是token
%left BTCLEFT BTCRIGHT
%left ALGCADD ALGCMINUS
%left ALGCMUL ALGCDIV ALGCMOD
%right UMINUS LGCCN BTCN GETADDR GETCONTENT
NEW DELETE
//注意UMINUS不是token
%right ALGCTADDP ALGCTMINUSP
%right ALGCTADDB ALGCTMINUSB  CLASSMC POINT
FUNCUSE ARRAYC LBRACESS RBRACESS LBRACEM RBRACEM
CLASSRST

%%

/////////////////////////////////////////////////////////////////////////////
// rules section

// place your YACC rules here (there must be at least one)


//如果我先要对符号有一个分开生存期与作用域的操作，我需要维护一个符号表的存储结构
//来更换符号表。

//声明语句:一个问题....在lex里面是只要遇到一个符号就会创建一个表项....emmm没毛病
//符号表的创建是在yacc中。这样保证有意义的作用域创建。
//将现在起作用的作用域压到栈顶，在lex只会对栈顶做操作。

//关于开始符号的问题。最后解决吧。

//startf: funcstmt;
//startf:cstmtlist	{$$=$1;startnode=$$;}
//;

start:	startinfo	{$$=$1;startnode=$$;cout<<"start1"<<endl;}
	|	start startinfo{$$=newStmtsNode(STARTK);
						$$->child[0]=$1;
						$$->child[1]=$2;
						//结合代码
						$$->midcode=Fcodes::combinecode($1->midcode,$2->midcode);
						//---
						startnode=$$;
						
						cout<<"start 2"<<endl;}
	;

startinfo:
//		funcstmt	{$$=$1;}//new StmtsNode(FUNCSK);}
//	|	expr	{$$=new St
//	|	comstmt		{$$=$1;}//new StmtsNode(COMSTMT);}
		classdef	{$$=$1;}//
//	|	stmt	{$$=$1;}
	|	basetypestmt	{$$=$1;}
	|	funcdef		{$$=$1;}
	|	funcdefmain	{$$=$1;}
//	|	basetypestmt
	;


basetype:	INT	{$$=newTypeNode(INTK);$$->exptype=new CType(CINT);nowattri=INTK;nowcode=CINT;}
	|	CHAR	{$$=newTypeNode(CHARK);$$->exptype=new CType(CCHAR);nowattri=CHARK;nowcode=CCHAR;}
	|	FLOAT	{$$=newTypeNode(FLOATK);$$->exptype=new CType(CFLOAT);nowattri=FLOATK;nowcode=CFLOAT;}
	|	VOID	{$$=newTypeNode(VOIDK);$$->exptype=new CType(CVOID);nowattri=VOIDK;nowcode=CVOID;}
	;
	

//list全在sibling
idlistwithvar:	idlistwithvar COMMA ID{
					//添加类型
					$3->exptype=new CType(nowcode);
					if(nowcode==CCLASS)$3->exptype->cname=nowclass;
					
					Node*addr=allsymbol.top()->findexist($3->attri.name);
					if(addr==NULL){
						Node*n=new Node("ID",$3->attri.name);
						n->setType($3->exptype);
						addr=allsymbol.top()->insert(n);
						cout<<$3->attri.name<<":my addr is:"<<allsymbol.top()<<" : "<<addr<<endl;
					}
					else rout<<"  redefine at line :"<<lineno<<" symbol:"<<$3->attri.name<<endl;
					addr->attri=nowattri;
					if(nowattri==NOTK)addr->classname=nowclass;
					$$=$3;
					$3->sibling=$1;
					//可能的中阿锦代码的设置
					$$->midcode=$1->midcode;
					
				}
	|	ID		{	//cout<<"hhh"<<endl;
					//添加类型
					$1->exptype=new CType(nowcode);
					if(nowcode==CCLASS)$1->exptype->cname=nowclass;
					
					Node*addr=allsymbol.top()->findexist($1->attri.name);
					if(addr==NULL){
						Node *n=new Node("ID",$1->attri.name);
						n->setType($1->exptype);
						addr=allsymbol.top()->insert(n);
						cout<<$1->attri.name<<":my addr is:"<<allsymbol.top()<<" : "<<addr<<endl;
					}
					else rout<<"  redefine at line :"<<lineno<<" symbol:"<<$1->attri.name<<endl;
					
					addr->attri=nowattri;
					if(nowattri==NOTK)addr->classname=nowclass;
					$$=$1;
					//不可能有中间代码
					
					}
	//
	|	idlistwithvar COMMA ID EQ expr	{
					//类型检查
					$3->exptype=new CType(nowcode);
					if(nowcode==CCLASS)$3->exptype->cname=nowclass;
					if(checkEqual($3,$5->exptype)==NULL)gtf=true;
					
					Node*addr=allsymbol.top()->findexist($3->attri.name);
					if(addr==NULL){
						Node*n=new Node("ID",$3->attri.name);
						n->setType($3->exptype);
						addr=allsymbol.top()->insert(n);
						cout<<$3->attri.name<<":my addr is:"<<allsymbol.top()<<" : "<<addr<<endl;
					}
					else rout<<"  redefine at line :"<<lineno<<" symbol:"<<$3->attri.name<<endl;
					addr->attri=nowattri;
					if(nowattri==NOTK)addr->classname=nowclass;
					TreeNode*tmp=newExpNode(OPK);
					tmp->attri.op=EQUEK;
					$$=tmp;
					tmp->child[0]=$3;
					tmp->child[1]=$5;
					$$->sibling=$1;	
					//设置中间代码：（赋值语句）
					//$$->
					
					}
	|	ID EQ expr	{
					//类型检查：这里的类型检查就不拖到语法树建立完成了
					$1->exptype=new CType(nowcode);
					if(nowcode==CCLASS)$1->exptype->cname=nowclass;
					if(!checkEqual($1,$3->exptype))gtf=true;
					
					Node*addr=(allsymbol.top())->findexist($1->attri.name);
					if(addr==NULL){
						Node*n=new Node("ID",$1->attri.name);
						n->setType($1->exptype);
						addr=allsymbol.top()->insert(n);
						cout<<$1->attri.name<<":my addr is:"<<allsymbol.top()<<" : "<<addr<<endl;
					}
					else rout<<"  redefine at line :"<<lineno<<" symbol:"<<$1->attri.name<<endl;
					addr->attri=nowattri;
					if(nowattri==NOTK)addr->classname=nowclass;
					TreeNode*tmp=newExpNode(OPK);
					tmp->attri.op=EQUEK;
					$$=tmp;
					tmp->child[0]=$1;
					tmp->child[1]=$3;
				
							
						}
	
	//扩展：数组与指针
	|	idlistwithvar COMMA ALGCMUL ID	{
						//添加类型
					$4->exptype=CType::pointer(new CType(nowcode));
					if(nowcode==CCLASS)$4->exptype->cname=nowclass;
					
					Node*addr=allsymbol.top()->findexist($4->attri.name);
					if(addr==NULL){
						Node*n=new Node("ID",$4->attri.name);
						n->setType($4->exptype);
						addr=allsymbol.top()->insert(n);
						cout<<$4->attri.name<<":my addr is:"<<allsymbol.top()<<" : "<<addr<<endl;
					}
					else rout<<"  redefine at line :"<<lineno<<" symbol:"<<$4->attri.name<<endl;
					addr->attri=((nowattri==INTK ? INTSK:(nowattri==CHARK ?CHARSK:(nowattri==FLOATK ? FLOATSK:NOTK))));
					if(nowattri==NOTK)addr->classname=nowclass;
					TreeNode*tmp=newExpNode(OPK);
					tmp->attri.op=GETCONTENTK;
					$$=tmp;
					tmp->child[0]=$4;
					$$->sibling=$1;
				//	cout<<"???"<<endl;
				
					
					}
	
	|	idlistwithvar COMMA ID LBRACEM NUMBERD RBRACEM	{
					//添加类型
					$3->exptype=CType::array0($5->attri.val,new CType(nowcode));
					if(nowcode==CCLASS)$3->exptype->cname=nowclass;
					$5->exptype=new CType(CINT);
					
					Node*addr=allsymbol.top()->findexist($3->attri.name);
					if(addr==NULL){
						Node*n=new Node("ID",$3->attri.name);
						n->setType($3->exptype);
						addr=allsymbol.top()->insert(n);
						cout<<$3->attri.name<<":my addr is:"<<allsymbol.top()<<" : "<<addr<<endl;
					}
					else rout<<"  redefine at line :"<<lineno<<" symbol:"<<$3->attri.name<<endl;
					TreeNode*tmp=newExpNode(OPK);
					addr->attri=((nowattri==INTK ? INTSK:(nowattri==CHARK ?CHARSK:(nowattri==FLOATK ? FLOATSK:NOTK))));
					if(nowattri==NOTK)addr->classname=nowclass;
					tmp->attri.op=ARRAYCK;
					$$=tmp;
					tmp->child[0]=$3;
					tmp->child[1]=$5;
					$$->sibling=$1;
					
						}
	|	ALGCMUL ID	{
					//添加类型
					$2->exptype=CType::pointer(new CType(nowcode));
					if(nowcode==CCLASS)$2->exptype->cname=nowclass;
					
					Node*addr=allsymbol.top()->findexist($2->attri.name);
					if(addr==NULL){
						Node*n=new Node("ID",$2->attri.name);
						n->setType($2->exptype);
						addr=allsymbol.top()->insert(n);
						cout<<$2->attri.name<<":my addr is:"<<allsymbol.top()<<" : "<<addr<<endl;
					}
					else rout<<"  redefine at line :"<<lineno<<" symbol:"<<$2->attri.name<<endl;
					TreeNode*tmp=newExpNode(OPK);
					addr->attri=((nowattri==INTK ? INTSK:(nowattri==CHARK ?CHARSK:(nowattri==FLOATK ? FLOATSK:NOTK))));
					if(nowattri==NOTK)addr->classname=nowclass;
					tmp->attri.op=GETCONTENTK;
					$$=tmp;
					tmp->child[0]=$2;//cout<<"???"<<endl;
					
					}
				
	|	ID LBRACEM NUMBERD RBRACEM	{
					//添加类型
					$1->exptype=CType::array0($3->attri.val,new CType(nowcode));
					if(nowcode==CCLASS)$1->exptype->cname=nowclass;
					$3->exptype=new CType(CINT);
					
					Node*addr=allsymbol.top()->findexist($1->attri.name);
					if(addr==NULL){
						Node*n=new Node("ID",$1->attri.name);
						n->setType($1->exptype);
						addr=allsymbol.top()->insert(n);
						cout<<$1->attri.name<<":my addr is:"<<allsymbol.top()<<" : "<<addr<<endl;
					}
					else rout<<"  redefine at line :"<<lineno<<" symbol:"<<$1->attri.name<<endl;
					TreeNode*tmp=newExpNode(OPK);
					addr->attri=((nowattri==INTK ? INTSK:(nowattri==CHARK ?CHARSK:(nowattri==FLOATK ? FLOATSK:NOTK))));
					if(nowattri==NOTK)addr->classname=nowclass;
					tmp->attri.op=ARRAYCK;
					$$=tmp;
					tmp->child[0]=$1;
					tmp->child[1]=$3;
					
						}
	;

//exprlist仅供函数访问。
//函数作为表达式被调用的时候的参数列表
//这些expr都应该是被检查过的合法的参数
//但是并不能保证一定可以调用，这还要对函数类型进行检查
exprlist:	exprlist COMMA expr	{lastt->sibling=$3;lastt=$3;$$=$1;$$->exptype=CType::dicar($1->exptype,$3->exptype);}
	|	expr	{lastt=$1;$$=$1;$$->exptype=new CType($1->exptype);}
	;

//基本类型（int char）的声明。在这里填上属性值（其实是在上面的idlistwithvar）

//这部分的检查集中于idlistwithvar。
basetypestmt:	basetype idlistwithvar SEMI	{
					$$=newStmtsNode(BASEK);
					$$->child[0]=$1;
					$$->child[1]=$2;
					//cout<<"basetype:"<<$1->type<<$2->nodekind<<endl;
					//类型
					
				}
	| among idlistwithvar SEMI{
		//ID可能是在类表里面，也可能不在
		//要求类在使用前必须定义，函数也是一样
					
					$$=newStmtsNode(BASEK);
					string name=$1->attri.name;
//					delete $1;
					//$1=newTypeNode(NOTK,name);
					$1->nodekind=TYPEK;
					$1->type=NOTK;
					$1->classname=name;
					$$->child[0]=$1;
					$$->child[1]=$2;
				}
	;
	//类对象的定义：要求此时类已经被声明，加入了classmap
	//（可能会出现类中类的情况
	//也许在汇编时无法实现
	//到时候会加一些约束条件
among	: ID {

	if(classmap.find($1->attri.name)==classmap.end()){
		gtf=true;
		rout<<"error:undefined symbol:"<<$1->attri.name<<" at line:"<<lineno<<endl;
	}
	nowattri=NOTK;nowcode=CCLASS;nowclass=$1->attri.name;$$=$1;}
	;
//由于shift-reduce conflit，导致非左值不报错
//没有区分
//能在expr出现的ID必须是已经在符号表中的了，否则就是未定义的标识符
expr	:	valueexpr
	|	calexpr
//	|	DELETE valueexpr LBRACEM RBRACEM 	{$$=makenodeS($2,DELETEK);}

;
valueexpr:	ID			{
			int count=0;
			Node*idnode;
			if((idnode=findfexist(allsymbol,$1->attri.name,count))==NULL){
			//	gtf=true;
			//	rout<<"error undefined symbol:"<<$1->attri.name<<" at line:"<<lineno<<endl;
				$1->exptype=new CType(CVOID);
			}else{
				$1->exptype=new CType(idnode->exptype);
			}
			$$=$1;
		}
			
	|	valueexpr CLASSMC valueexpr	{$$=makenodeT($1,$3,CLASSMCK);
					//类型检查与赋值
					$$->exptype=checkclass(CLASSMCK,$1->exptype,$3->attri.name,NULL);
					if(!($$->exptype)){
						gtf=1;
						rout<<"error:bad type '->' at line :"<<lineno<<endl;
						}
					}
	|	valueexpr POINT valueexpr	%prec CLASSMC {
					$$=makenodeT($1,$3,POINTK);
					$$->exptype=checkclass(POINTK,$1->exptype,$3->attri.name,NULL);
					if(!($$->exptype)){
						gtf=1;
						rout<<"error:bad type '.' at line :"<<lineno<<endl;
						}
					
					}
	|	ALGCMUL valueexpr %prec GETCONTENT	{
					$$=makenodeS($2,GETCONTENTK);
					$$->exptype=checkOp(GETCONTENTK,$2->exptype,NULL);
					if(!($$->exptype)){
						gtf=1;
						rout<<"error:bad type '*' at line :"<<lineno<<endl;
						}
					}
//	|	ALGCMUL LBRACESS valueexpr ALGCADD RBRACESS
	|	valueexpr LBRACEM expr RBRACEM %prec ARRAYC {
					$$=makenodeT($1,$3,ARRAYCK);
					$$->exptype=checkOp(ARRAYCK,$1->exptype,$3->exptype);
					if(!($$->exptype)){
						gtf=1;
						rout<<"error:bad type '[]' at line :"<<lineno<<endl;
						}
					
					}	
	|	ALGCTADD valueexpr %prec ALGCTADDP		{
					$$=makenodeS($2,ALGCTADDPK);
					$$->exptype=checkleft(ALGCTADDPK,$2);
					if(!($$->exptype)){
						gtf=1;
						rout<<"error:bad type '++' at line :"<<lineno<<endl;
						}

					}
	|	ALGCTMINUS valueexpr %prec ALGCTMINUSP	{
					$$=makenodeS($2,ALGCTMINUSPK);
					$$->exptype=checkleft(ALGCTMINUSPK,$2);
					if(!($$->exptype)){
						gtf=1;
						rout<<"error:bad type '--' at line :"<<lineno<<endl;
						}
					
					}
	|	LBRACESS valueexpr RBRACESS	{$$=$2;}
	
//	|	LBRACESS valueexpr RBRACESS {$$=$2;}
	;
calexpr	:	expr ALGCADD expr %prec ALGCADD	{
					$$=makenodeT($1,$3,ALGCADDK);
					$$->exptype=checkOp(ALGCADDK,$1->exptype,$3->exptype);
					if(!($$->exptype)){
						gtf=1;
						rout<<"error:bad type '+' at line :"<<lineno<<endl;
						}
					
					}
	|	expr ALGCMINUS expr	%prec ALGCMINUS{ 
					$$=makenodeT($1,$3,ALGCMINUSK);
					$$->exptype=checkOp(ALGCMINUSK,$1->exptype,$3->exptype);
					if(!($$->exptype)){
						gtf=1;
						rout<<"error:bad type '-' at line :"<<lineno<<endl;
						}
					
					 }
	|	expr ALGCMUL expr	%prec ALGCMUL{ 
					$$=makenodeT($1,$3,ALGCMULK); 
					$$->exptype=checkOp(ALGCMULK,$1->exptype,$3->exptype);
					if(!($$->exptype)){
						gtf=1;
						rout<<"error:bad type '*' at line :"<<lineno<<endl;
						}
					
					}
	|	expr ALGCDIV expr	{ $$=makenodeT($1,$3,ALGCDIVK); 
	
					$$->exptype=checkOp(ALGCDIVK,$1->exptype,$3->exptype);
					if(!($$->exptype)){
						gtf=1;
						rout<<"error:bad type '/' at line :"<<lineno<<endl;
						}
	}
	|	expr ALGCMOD expr	{$$=makenodeT($1,$3,ALGCMODK);
					$$->exptype=checkOp(ALGCMODK,$1->exptype,$3->exptype);
					if(!($$->exptype)){
						gtf=1;
						rout<<"error:bad type '%' at line :"<<lineno<<endl;
						}
	
		}						
							
	|	LBRACESS calexpr RBRACESS	{ $$=$2;}//这里的括号是不会产生的作用域的!!
	|	ALGCMINUS expr %prec UMINUS	{$$=makenodeS($2,UMINUSK);
					$$->exptype=checkOp(UMINUSK,$1->exptype,NULL);
					if(!($$->exptype)){
						gtf=1;
						rout<<"error:bad type 'uminus' at line :"<<lineno<<endl;
						}
	
	
	}
	
	|	NUMBERD		{$$=$1;$$->exptype=new CType(CINT);}
	|	DIGIT	{$$=$1;$$->exptype=new CType(CINT);}
	|	FLOATD		{$$=$1;$$->exptype=new CType(CFLOAT);}
	|	STRING		{$$=$1;$$->exptype=new CType(CSTRING);}
	|	ONECHAR		{$$=$1;$$->exptype=new CType(CCHAR);}
	//需要左值 ,由于类、数组、指针的加入，不能直接写ID
	//需要左值的运算将会检查是否左值
	
	|	valueexpr ALGCTADD %prec ALGCTADDB		{
					$$=makenodeS($1,ALGCTADDBK);
					$$->exptype=checkleft(ALGCTADDBK,$1);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '++' at line :"<<lineno<<endl;
					}
					
					
					}
	|	valueexpr ALGCTMINUS %prec ALGCTMINUSB		{
					$$=makenodeS($1,ALGCTMINUSBK);
					$$->exptype=checkleft(ALGCTMINUSBK,$1);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '--' at line :"<<lineno<<endl;
					}
					
					}


	|	BTCN expr	{$$=makenodeS($2,BTCNK);
					$$->exptype=checkOp(BTCNK,$2->exptype,NULL);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '~' at line :"<<lineno<<endl;
					}
	
	}
	
	|	expr BTCRIGHT expr	{$$=makenodeT($1,$3,BTCRIGHTK);
					$$->exptype=checkOp(BTCRIGHTK,$1->exptype,$3->exptype);
					//$$->exptype=checkOp(BTCNK,$2->exptype);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '>>' at line :"<<lineno<<endl;
					}
	
	}
	|	expr BTCLEFT expr	{$$=makenodeT($1,$3,BTCLEFTK);
					$$->exptype=checkOp(BTCLEFTK,$1->exptype,$3->exptype);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '<<' at line :"<<lineno<<endl;
					}
	
	}
	|	expr BTCAND expr{$$=makenodeT($1,$3,BTCANDK);
						$$->exptype=checkOp(BTCANDK,$1->exptype,$3->exptype);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '&' at line :"<<lineno<<endl;
					}
	}
	|	expr BTCOR expr{$$=makenodeT($1,$3,BTCORK);
						$$->exptype=checkOp(BTCORK,$1->exptype,$3->exptype);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '||' at line :"<<lineno<<endl;
					}
			}
	|	expr BTCYH expr{$$=makenodeT($1,$3,BTCYHK);
						$$->exptype=checkOp(BTCYHK,$1->exptype,$3->exptype);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '^' at line :"<<lineno<<endl;
					}
					}
	//函数使用
	|	ID LBRACESS exprlist RBRACESS %prec FUNCUSE	{$$=makenodeT($1,$3,FUNCK);
					$$->exptype=checkfunc($1->attri.name,$3->exptype);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type 'func' at line :"<<lineno<<endl;
					}
	
	}

	|	valueexpr CLASSMC ID LBRACESS exprlist RBRACESS %prec FUNCUSE	{
					TreeNode*t=makenodeT($3,$5,FUNCK);
					$$=makenodeT($1,t,CLASSMCK);
					$$->exptype=checkclass(CLASSMCK,$1->exptype,$3->attri.name,$5->exptype);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type 'func' at line :"<<lineno<<endl;
					}
					
					}
	|	valueexpr POINT ID LBRACESS exprlist RBRACESS %prec FUNCUSE	{
					TreeNode*t=makenodeT($3,$5,FUNCK);
					$$=makenodeT($1,t,POINTK);
					$$->exptype=checkclass(POINTK,$1->exptype,$3->attri.name,$5->exptype);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type 'func' at line :"<<lineno<<endl;
					}
		}
	|	ID LBRACESS  RBRACESS %prec FUNCUSE	{$$=makenodeS($1,FUNCK);
					$$->exptype=checkfunc($1->attri.name,new CType(CVOID));
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type 'func' at line :"<<lineno<<endl;
					}
	
	}
	
	|	valueexpr CLASSMC ID LBRACESS  RBRACESS %prec FUNCUSE	{
					TreeNode*t=makenodeS($3,FUNCK);
					$$=makenodeT($1,t,CLASSMCK);
					$$->exptype=checkclass(CLASSMCK,$1->exptype,$3->attri.name,new CType(CVOID));
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type 'func' at line :"<<lineno<<endl;
					}
					
					}
	|	valueexpr POINT ID LBRACESS  RBRACESS %prec FUNCUSE	{
					TreeNode*t=makenodeS($3,FUNCK);
					$$=makenodeT($1,t,POINTK);
					$$->exptype=checkclass(POINTK,$1->exptype,$3->attri.name,new CType(CVOID));
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type 'func' at line :"<<lineno<<endl;
					}
					}
					
	//逻辑运算
	|	LGCCN expr	{$$=makenodeS($2,LGCCNK);
					//$$->exptype=checkOp(
	}
	|	expr LGCCMOREEQ expr{$$=makenodeT($1,$3,LGCCMOREEQK);
					/*$$->exptype=checkOp(BTCLEFTK,$1->exptype,$3->exptype);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '<<' at line :"<<lineno<<endl;
					}*/
	
	}
	|	expr LGCCLESSEQ expr{$$=makenodeT($1,$3,LGCCLESSEQK);
				/*		$$->exptype=checkOp(BTCLEFTK,$1->exptype,$3->exptype);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '<<' at line :"<<lineno<<endl;
					}*/
	}
	|	expr LBRACES expr %prec LGCCMORE{$$=makenodeT($1,$3,LGCCLESSK);}
	|	expr RBRACES expr %prec LGCCLESS{$$=makenodeT($1,$3,LGCCMOREK);}
	|	expr LGCCEQ expr{$$=makenodeT($1,$3,LGCCEQK);}
	|	expr LGCCNEQ expr{$$=makenodeT($1,$3,LGCCNK);}
	


	|	expr LGCCAND expr{$$=makenodeT($1,$3,LGCCANDK);
				/*		$$->exptype=checkOp(BTCLEFTK,$1->exptype,$3->exptype);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '<<' at line :"<<lineno<<endl;
					}*/
	}
	|	expr LGCCOR expr{$$=makenodeT($1,$3,LGCCORK);}
	

	
	//左值
	|	expr EQ expr	%prec EQ	{$$=makenodeT($1,$3,EQUEK);
					$$->exptype=checkEqual($1,$3->exptype);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '=' at line :"<<lineno<<endl;
					}
	}
//	|	valueexpr EQ expr %prec EQ	{$$=makenodeT($1,$3,EQUEK);}//赋值表达式
	
	
	|	BTCAND expr %prec GETADDR	{$$=makenodeS($2,GETADDRK);
					$$->exptype=checkleft(GETADDRK,$2);
					if($$->exptype==NULL){
						gtf=1;
						rout<<"error:bad type '&' at line :"<<lineno<<endl;
					}
	
	}
//关于new 这应该属于运行时了吧...
//	|	NEW basetype LBRACEM expr RBRACEM 	{$$=makenodeT($2,$4,NEWK);$$->exptype=CType::pointer($2->exptype);}
/*	|	NEW ID LBRACEM expr RBRACEM		{
					string name=$2->attri.name;
//					delete $2;
					$2->nodekind=TYPEK;
					$2->type=NOTK;
					$2->classname=name;
//					$2=newTypeNode(NOTK,name);
					$$=makenodeT($2,$4,NEWK);
				}*/
	//是类型检查
	;
/*
comstmt:	LBRACE comstmt RBRACE comstmt	{
	|
	;*/
//在函数中用于函数的类型检查
returnstmt:	RETURN expr SEMI {
			$$=newStmtsNode(RETURNK);
			$$->child[0]=$2;
			$$->exptype=new CType($2->exptype);
		}
	;
	
	
stmt :	expr SEMI	{$$=newStmtsNode(EXPSK);$$->child[0]=$1;;}//去掉了equstmt
	|	LBRACESS error SEMI	{$$=newStmtsNode(EXPSK);$$->child[0]=NULL;rout<<"error at line:"<<lineno<<" missing rbracess"<<endl;}
	|	basetypestmt	{$$=$1;}
	|	ifstmt	
	|	whilestmt
	|	forstmt
	|	cinstmt
	|	coutstmt
	|	returnstmt
	|	SEMI	{$$=newStmtsNode(NULLK);}
	;

//stmt与comstmt的列表
//cstmtlist只能与comstmt内被使用。不可以在其他地方单独使用
//在第一个大括号开始之后，就一直在cstmlist中。期间可能会回到comstmt中，但是外面的大框架还是cstmtlist	
cstmtlist:	cstmtlist comstmt	{
			if(cstlastt.top()!=NULL){
				cstlastt.top()->sibling=$2;
				cstlastt.pop();
				cstlastt.push($2) ;
			}
//			else if(comlastt==NULL)comlastt=$2;
			else {
				cstlastt.top()->sibling=$2;
				cstlastt.pop();
				cstlastt.push($2);
			}
			$$=$1;
			}
	|	cstmtlist stmt	{
			cstlastt.top()->sibling=$2;cstlastt.pop();cstlastt.push($2);$$=$1;
			}
	|	comstmt		{cstlastt.pop();cstlastt.push($1);$$=$1;}
	|	stmt	{cstlastt.pop();cstlastt.push($1);$$=$1;}
	;
	//是一个像链表一样的树
//stmtlist: stmtlist stmt	{lastt->sibling=$2;lastt=$2;$$=$1;}
//	|	stmt	{lastt=$1;$$=$1;}
//	;
comstmt:	LBRACE midum cstmtlist RBRACE	{
				$$=newStmtsNode(COMSTMTK);
				$$->child[0]=$3;
				cstlastt.pop();
			}
//	|	LBRACE midum stmtlist RBRACE	{
//				$$=newStmtsNode(COMSTMTK);
//				$$->child[0]=$3;
//				cstlastt.pop();
//			}
	|	LBRACE midum RBRACE	{$$=newStmtsNode(COMSTMTK);cstlastt.pop();}
//	|	LBRACE cs
	//trytryrtryrtryrtryry
/*	|	LBRACE midum cstmtlist error	{
				$$=newStmtsNode(COMSTMTK);
				$$->child[0]=$3;
				cstlastt.pop();
				rout<<"error at line:"<<lineno<<" missing '}'"<<endl;
			}	
	|	LBRACE midum error	{$$=newStmtsNode(COMSTMTK);cstlastt.pop();
				rout<<"error at line:"<<lineno<<" missing '}'"<<endl;}*/
	;
	
midum :		{TreeNode*lat;cstlastt.push(lat);}
	;	
	
	
//if里面是expr，不可能有新的符号表帮他创建的。

stmtcomstmt:	stmt
	|	comstmt
	;


ifstmt:	IF LBRACESS expr RBRACESS stmtcomstmt ELSE stmtcomstmt	{
				$$=newStmtsNode(IFK);
				$$->child[0]=$3;
				$$->child[1]=$5;
				$$->child[2]=$7;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
			}
	
	|	IF LBRACESS expr RBRACESS stmtcomstmt	{
				$$=newStmtsNode(IFK);
				$$->child[0]=$3;
				$$->child[1]=$5;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
			}
	|	IF LBRACESS expr error stmtcomstmt ELSE stmtcomstmt	{
				$$=newStmtsNode(IFK);
				$$->child[0]=$3;
				$$->child[1]=$5;
				$$->child[2]=$7;
				rout<<"error at line:"<<lineno<<" missing ')'"<<endl;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
			}
	
	|	IF LBRACESS expr error stmtcomstmt	{
				$$=newStmtsNode(IFK);
				$$->child[0]=$3;
				$$->child[1]=$5;
				rout<<"error at line:"<<lineno<<" missing ')'"<<endl;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
	}
	;

//others:	.{cout<<"not match"};
whilestmt:	WHILE LBRACESS expr RBRACESS stmtcomstmt	{
				$$=newStmtsNode(WHILEK);
				$$->child[0]=$3;
				$$->child[1]=$5;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
			}
		|	WHILE LBRACESS expr error stmtcomstmt	{
				$$=newStmtsNode(WHILEK);
				$$->child[0]=$3;
				$$->child[1]=$5;
				rout<<"error at line:"<<lineno<<" missing ')'"<<endl;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
			}
	;

forstmt:	FOR LBRACESS expr SEMI expr SEMI expr RBRACESS stmtcomstmt	{

				TreeNode*t=newStmtsNode(FOREK);
				t->child[0]=$3;
				t->child[1]=$5;
				t->child[2]=$7;
				$$=newStmtsNode(FORK);
				$$->child[0]=t;
				$$->child[1]=$9;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
}
	|	FOR LBRACESS expr SEMI expr SEMI RBRACESS stmtcomstmt{
				TreeNode*t=newStmtsNode(FOREK);
				t->child[0]=$3;
				t->child[1]=$5;
				t->child[2]=NULL;
				$$=newStmtsNode(FORK);
				$$->child[0]=t;
				$$->child[1]=$8;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
}
	|	FOR LBRACESS expr SEMI SEMI expr RBRACESS stmtcomstmt{
				TreeNode*t=newStmtsNode(FOREK);
				t->child[0]=$3;
				t->child[1]=NULL;
				t->child[2]=$6;
				$$=newStmtsNode(FORK);
				$$->child[0]=t;
				$$->child[1]=$8;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
}
	|	FOR LBRACESS SEMI expr SEMI expr RBRACESS stmtcomstmt{
				TreeNode*t=newStmtsNode(FOREK);
				t->child[0]=NULL;
				t->child[1]=$4;
				t->child[2]=$6;
				
				$$=newStmtsNode(FORK);
				$$->child[0]=t;
				$$->child[1]=$8;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
}
	|	FOR LBRACESS expr SEMI SEMI RBRACESS stmtcomstmt{
				TreeNode*t=newStmtsNode(FOREK);
				t->child[0]=$3;
				
				$$=newStmtsNode(FORK);
				$$->child[0]=t;
				$$->child[1]=$7;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
}
	|	FOR LBRACESS SEMI expr SEMI RBRACESS stmtcomstmt{
				TreeNode*t=newStmtsNode(FOREK);
				//$$->child[0]=$1;
				t->child[1]=$4;
				
				$$=newStmtsNode(FORK);
				$$->child[0]=t;
				$$->child[1]=$7;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
}
	|	FOR LBRACESS SEMI SEMI expr RBRACESS stmtcomstmt{
				TreeNode*t=newStmtsNode(FOREK);
				//$$->child[0]=$1;
				//$$->child[1]=$3;
				t->child[2]=$5;
				
				$$=newStmtsNode(FORK);
				$$->child[0]=t;
				$$->child[1]=$7;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
}
	|	FOR LBRACESS SEMI SEMI RBRACESS stmtcomstmt{
				TreeNode*t=newStmtsNode(FOREK);
				
				$$=newStmtsNode(FORK);
				$$->child[0]=t;
				$$->child[1]=$6;
				storesymbol.push(allsymbol.top());
				allsymbol.pop();
}
	
	;


//cout

coutlist:	coutlist BTCLEFT expr{
			$$=$1;
			lastt->sibling=$3;
			lastt=$3;
}
	|	BTCLEFT  expr 	{
			$$=$2;
			lastt=$$;
		
	}
	;
coutstmt:	COUT coutlist SEMI	{
			$$=newStmtsNode(COUTK);
			$$->child[0]=$2;
}
	;
	
//cin
cinlist:	cinlist BTCRIGHT valueexpr	{
			$$=$1;
			lastt->sibling=$3;
			lastt=$3;
	
}
	|	BTCRIGHT valueexpr	{
			$$=$2;
			lastt=$$;	
	}
	;
cinstmt:	CIN cinlist SEMI{
			$$=newStmtsNode(CINK);
			$$->child[0]=$2;
}
	;


//目前函数不支持类类型作为参数以及类类型作为返回值
//因此进行类型检查时只需要code一样即可
typep:	basetype	
	|	basetype ALGCMUL	{
		ExpType type=$1->type;
		ExpType nt=(type==INTK ?INTSK:(type==CHARK ?CHARSK:FLOATSK));
		$1->type=nt;
		$$=$1;
		//类型
		$$->exptype=CType::pointer($1->exptype);
	}
	;
	
//应该是一群basek的list//
//将会直接进行类型检查，所以一定确保写东西的时候
//先定义后使用
//这里类型的标准是typep
typeidlist:	typeidlist COMMA typep ID	{
		TreeNode*t=newStmtsNode(BASEK);
		t->child[0]=$3;
		t->child[1]=$4;
		$$=$1;
		lastt->sibling=t;
		lastt=t;
		//类型：由于直接是给函数用的，于是直接定义成dicar
		$$->exptype=CType::dicar($1->exptype,$3->exptype);
		
}
	|	typeidlist COMMA typep ID LBRACEM NUMBERD RBRACEM {
			TreeNode*t=newStmtsNode(BASEK);
			TreeNode*te=newExpNode(OPK);
			te->attri.op=ARRAYCK;
			te->child[0]=$4;
			te->child[1]=$6;
			t->child[0]=$3;
			t->child[1]=te;
			lastt->sibling=t;
			$$=$1;
			lastt=t;
			//类型：由于直接是给函数用的，于是直接定义成dicar
			$$->exptype=CType::dicar($1->exptype,CType::array0($6->attri.val,$3->exptype));
	}
	
	|	typep ID	{
			TreeNode*t=newStmtsNode(BASEK);
			t->child[0]=$1;
			t->child[1]=$2;
			$$=t;
			lastt=t;
			//类型
			$$->exptype=$1->exptype;
	}
	|	typep ID LBRACEM NUMBERD RBRACEM	{
			TreeNode*t=newStmtsNode(BASEK);
			TreeNode*te=newExpNode(OPK);
			te->attri.op=ARRAYCK;
			te->child[0]=$2;
			te->child[1]=$4;
			t->child[0]=$1;
			t->child[1]=te;
			lastt=t;
			//类型
			$$->exptype=CType::array0($4->attri.val,$1->exptype);	
}
	;
/*
funcstmt:	basetype ID LBRACESS typeidlist RBRACESS SEMI	{cout<<"funcstmt"<<endl;}
	|	basetype ALGCMUL ID LBRACE typeidlist RBRACE SEMI
	|	basetype ID LBRACESS RBRACESS SEMI	{cout<<"funcstmt"<<endl;}
	|	basetype ALGCMUL ID LBRACE RBRACE SEMI
	;*///这里的问题是，如何处理函数的符号表。
	//因为引用机制的存在啊！所以才会不修改原参的值！
	//done
	//另一个问题是，如何保存函数的ID。因为函数ID和标识符是可以重复的。
	
	//这一点上类就很令人省心，因为类名不允许其他人使用了。
	//emmm其实也没有问题了。同一个作用域不允许同名嘻嘻嘻。
	//还有一个问题是函数声明的归属。在函数定义中，不允许函数存在。
	//个关于函数还应该了解更多。

//emm定义的话，如果已经有id了就加东西，没有就加一个id项
//终于要往符号表插其他东西了...
//函数的话，是不允许在函数中被定义的，全局区域也不允许出现comstmt
//所以插入ID一定是在最底层的符号表插入，
//关于类，其函数允许在全局也允许在类中。类有自己的作用域，类并不想和其他用同一个符号表
//因此这些普通函数，他们全部在自己的符号表。

//为了更加简洁地实现符号表的功能
//只能委屈语法部分变得繁杂了√

//关于return语句的问题：需要func中包含return语句，其type
//应该与表示的basetype一样
//怎么实现呢？
funcdef:	basetype ID LBRACESS typeidlist RBRACESS comstmt	{
					$$=newStmtsNode(FUNCDK);
					$$->child[0]=$1;
					$$->child[1]=$2;
					$$->child[2]=$4;
					$$->exptype=CType::func($1->exptype,$4->exptype);
					$$->sibling=$6;
					if(funcmap.find($2->attri.name)!=funcmap.end())rout<<"error at line :"<<lineno<<"redefined func:"<<$2->attri.name<<endl; 
					else{
						Node*n=new Node("FUNC",$2->attri.name);
						n->exptype=$$->exptype;//符号表中的exptype
					//	n->setType($1->exptype);
						funcmap[$2->attri.name]=n;//$$;
						cout<<$2->attri.name<<":my addr is:"<<funcmap[$2->attri.name]<<endl;
						
					}
					
}
	|	basetype ALGCMUL ID LBRACESS typeidlist RBRACESS comstmt	{
					$$=newStmtsNode(FUNCDK);
					ExpType type=(($1->type==INTK ? INTSK:($1->type==CHARK ? CHARSK:FLOATSK)));
					TreeNode*tmp=newTypeNode(type);
					//类型
					$$->exptype=CType::func(CType::pointer($1->exptype),$5->exptype);
					
					delete $1;
					$$->child[0]=tmp;
					$$->child[1]=$3;
					$$->child[2]=$5;
					$$->sibling=$7;
					if(funcmap.find($3->attri.name)!=funcmap.end())rout<<"error at line :"<<lineno<<"redefined func:"<<$3->attri.name<<endl; 
					else{
						Node*n=new Node("FUNC",$3->attri.name);
					//	n->setType($1->exptype);
						n->exptype=$$->exptype;//符号表中的exptype
						funcmap[$3->attri.name]=n;//$$;
						cout<<$3->attri.name<<":my addr is:"<<funcmap[$3->attri.name]<<endl;
					}
}
//无参数：需要加VOID
	|	basetype ID LBRACESS  RBRACESS comstmt	{
					$$=newStmtsNode(FUNCDK);
					$$->child[0]=$1;
					$$->child[1]=$2;
					$$->child[2]=NULL;
					$$->sibling=$5;
					//符号
					$$->exptype=CType::func($1->exptype,new CType(CVOID));
					
					//cout<<($$->sibling==NULL)<<"the func's sibling is null?"<<endl;
					if(funcmap.find($2->attri.name)!=funcmap.end())rout<<"error at line :"<<lineno<<" redefined func:"<<$2->attri.name<<endl; 
					else{
						Node*n=new Node("FUNC",$2->attri.name);
					//	n->setType($1->exptype);
						n->exptype=$$->exptype;//符号表中的exptype
						funcmap[$2->attri.name]=n;//$$;
						cout<<$2->attri.name<<":my addr is:"<<funcmap[$2->attri.name]<<endl;
					}
	
	}
	|	basetype ALGCMUL ID LBRACESS  RBRACESS comstmt	{
					$$=newStmtsNode(FUNCDK);
					ExpType type=(($1->type==INTK ? INTSK:($1->type==CHARK ? CHARSK:FLOATSK)));
					TreeNode*tmp=newTypeNode(type);
					//符号
					$$->exptype=CType::func(CType::pointer($1->exptype),new CType(CVOID));
					delete $1;
					$$->child[0]=tmp;
					$$->child[1]=$3;
					$$->child[2]=NULL;
					$$->sibling=$6;
					if(funcmap.find($3->attri.name)!=funcmap.end())rout<<"error at line :"<<lineno<<" redefined func:"<<$3->attri.name<<endl; 
					else{
						Node*n=new Node("FUNC",$3->attri.name);
					//	n->setType($1->exptype);
						n->exptype=$$->exptype;//符号
						funcmap[$3->attri.name]=n;//$$;
						cout<<$3->attri.name<<":my addr is:"<<funcmap[$3->attri.name]<<endl;
					}
}
	;

//emmmmain函数不接受传参...
//返回值....
//设置bool，一旦有发现的错误就设置为true，完成之后停止
//不会生成汇编代码
funcdefmain:	INT MAIN LBRACESS RBRACESS comstmt	{
		$$=newStmtsNode(MAINK);
		$$->type=INTK;
		$$->child[0]=newTypeNode(INTK);
		$$->child[1]=$5;
		mainnode=$$;//
	}
	
	|	INT MAIN LBRACESS error  comstmt{
		$$=newStmtsNode(MAINK);
		$$->type=INTK;
		$$->child[0]=newTypeNode(INTK);
		$$->child[1]=$5;
		rout<<"error at line :"<<lineno<<" missing ')'"<<endl;
		
		}
	
	;
	

//类
//有一次一直循环，是因为输入为空的时候还允许递归，所以就一直匹配
/*
protype:	PUBLIC
	|	PRIVATE
	|	PROTECTED
	;//我也不懂为啥要这个...有很大概率应该是不会实现了...*/
	

//
//
inclass:

	inclass basetypestmt	{$$=$1;lastt->sibling=$2;lastt=$2;}
//	|	inclass funcdef	{cout<<"2in"<<endl;}
//	在类的作用域中，函数会被加到类提供的相应字段
	|	inclass funcdef	{$$=$1;lastt->sibling=$2;lastt=$2;}
	|	basetypestmt	{$$=$1;lastt=$$;}
//	|	funcstmt	{cout<<"7in"<<endl;}
	|	funcdef	{$$=$1;lastt=$$;}
	;
//因为类的大括号将会创建一个新的作用域。
//inclass中的东西都在这个作用域
//这个top由于}的关系在storesymbol顶层。
classdef:	class ID LBRACE inclass RBRACE SEMI	{
		ClassNode*n=new ClassNode($2->attri.name);
		n->classv=storesymbol.top();
		cout<<"llll"<<(n->classv)->findexist("m");
//		allsymbol.pop();
		$$=newStmtsNode(CLASSK);
		if(classmap.find($2->attri.name)!=classmap.end()){
			gtf=1;
			rout<<"error at line:"<<lineno<<"   redefine of class:"<<$2->attri.name<<endl;
		}
		else{
		
			n->classf=&(funcmap);
			funcmap=*tofuncmap;
			classmap[$2->attri.name]=n;
			cout<<$2->attri.name<<":my addr :"<<classmap[$2->attri.name]<<endl;	
		}
		
		$$->child[0]=$2;
		$$->child[1]=$4;
		//类型
		$$->exptype=new CType($2->attri.name);
		
		cout<<"更换回来"<<endl;
		//$$->w
		//其他的都会在自己的basetypestmt里面有自己的类型的编码。
		//关于ID声明变量
	}
	//忘加分号：其实处理都一样，但是标识出有错误输出
	|	class ID LBRACE inclass RBRACE error{
		rout<<"missing ; ?  at line:"<<lineno<<endl;
		gtf=1;
		ClassNode*n=new ClassNode($2->attri.name);
//		n->classv=storesymbol.top();
		allsymbol.pop();
		$$=newStmtsNode(CLASSK);
		if(classmap.find($2->attri.name)!=classmap.end()){
			gtf=1;
			rout<<"error at line:"<<lineno<<"   redefine of class:"<<$2->attri.name<<endl;
		}
		else{
		
			n->classf=&(funcmap);
			funcmap=*tofuncmap;
			classmap[$2->attri.name]=n;
			cout<<$2->attri.name<<":my addr :"<<classmap[$2->attri.name]<<endl;	
		}
		
		$$->child[0]=$2;
		$$->child[1]=$4;
		//类型
		$$->exptype=new CType($2->attri.name);
		
		cout<<"更换回来"<<endl;
	
	
	
	}

	;	
	
class :	CLASS	{
	//	allsymbol.push(new CHash());
		tofuncmap=&funcmap;
		funcmap=*(new hash_map<string,Node*>());
		//进入类的作用域，将类中的变量信息存储
		//question类与变量
		cout<<"更换"<<endl;
};
	

%%

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

