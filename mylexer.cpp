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
* mylexer.cpp
* C++ source file generated from mylexer.l.
* 
* Date: 01/04/18
* Time: 02:52:38
* 
* ALex Version: 2.07
****************************************************************************/

#include <yyclex.h>

// namespaces
#ifdef YYSTDCPPLIB
using namespace std;
#endif
#ifdef YYNAMESPACE
using namespace yl;
#endif

#line 1 ".\\mylexer.l"

/****************************************************************************
mylexer.l
ParserWizard generated Lex file.

Date: 2017年12月2日
****************************************************************************/

#include <fstream>
#include<string>
#include<iomanip>
#include<stack>
#include<sstream>
#include"myhashtable.h"
#include "mytreenode.h"
#include "myparser.h"

extern TreeNode* yylval;

void coutf(string token,string lexeme,string attri);//notice
float getfloat(const string &s);

ofstream mout("lexstream.txt");
CHash*symbtb=new CHash();//全局符号表
//使用栈来管理所有的符号表。
stack<CHash*> allsymbol;
stack<CHash*> storesymbol;
void coutf(string token,string lexeme,Node* attri);
int lineno = 0;


int getint(string s);
TreeNode * newExpNode(ExpKind kind);


#line 74 "mylexer.cpp"
// repeated because of possible precompiled header
#include <yyclex.h>

// namespaces
#ifdef YYSTDCPPLIB
using namespace std;
#endif
#ifdef YYNAMESPACE
using namespace yl;
#endif

#include ".\mylexer.h"

/////////////////////////////////////////////////////////////////////////////
// constructor

YYLEXERNAME::YYLEXERNAME()
{
	yytables();
#line 160 ".\\mylexer.l"

	// place any extra initialisation code here
	allsymbol.push(symbtb);
	cout<<"EXE"<<endl;

#line 100 "mylexer.cpp"
}

/////////////////////////////////////////////////////////////////////////////
// destructor

YYLEXERNAME::~YYLEXERNAME()
{
#line 167 ".\\mylexer.l"

	// place any extra cleanup code here

#line 112 "mylexer.cpp"
}

#ifndef YYTEXT_SIZE
#define YYTEXT_SIZE 100
#endif
#ifndef YYUNPUT_SIZE
#define YYUNPUT_SIZE YYTEXT_SIZE
#endif
#ifndef YYTEXT_MAX
#define YYTEXT_MAX 0
#endif
#ifndef YYUNPUT_MAX
#define YYUNPUT_MAX YYTEXT_MAX
#endif

/****************************************************************************
* N O T E
* 
* If the compiler generates a YYLEXERNAME error then you have not declared
* the name of the lexical analyser. The easiest way to do this is to use a
* name declaration. This is placed in the declarations section of your Lex
* source file and is introduced with the %name keyword. For instance, the
* following name declaration declares the lexer mylexer:
* 
* %name mylexer
* 
* For more information see help.
****************************************************************************/

// backwards compatability with lex
#ifdef input
int YYLEXERNAME::yyinput()
{
	return input();
}
#else
#define input yyinput
#endif

#ifdef output
void YYLEXERNAME::yyoutput(int ch)
{
	output(ch);
}
#else
#define output yyoutput
#endif

#ifdef unput
void YYLEXERNAME::yyunput(int ch)
{
	unput(ch);
}
#else
#define unput yyunput
#endif

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn -rch		// <warning: unreachable code> off
#endif
#endif

int YYLEXERNAME::yyaction(int action)
{
#line 181 ".\\mylexer.l"

	// extract yylval for use later on in actions
	YYSTYPE YYFAR& yylval = *(YYSTYPE YYFAR*)yyparserptr->yylvalptr;

#line 183 "mylexer.cpp"
	yyreturnflg = yytrue;
	switch (action) {
	case 1:
		{
#line 187 ".\\mylexer.l"
;
#line 190 "mylexer.cpp"
		}
		break;
	case 2:
		{
#line 190 ".\\mylexer.l"
coutf("INT","int","");return INT;
#line 197 "mylexer.cpp"
		}
		break;
	case 3:
		{
#line 191 ".\\mylexer.l"
coutf("FLOAT","float","");return FLOAT;
#line 204 "mylexer.cpp"
		}
		break;
	case 4:
		{
#line 192 ".\\mylexer.l"
coutf("CHAR","char","");return CHAR;
#line 211 "mylexer.cpp"
		}
		break;
	case 5:
		{
#line 193 ".\\mylexer.l"
coutf("VOID","void","");return VOID;
#line 218 "mylexer.cpp"
		}
		break;
	case 6:
		{
#line 195 ".\\mylexer.l"
CHash*newtb=new CHash();
				allsymbol.push(newtb);coutf("IF","if","");return IF;
#line 226 "mylexer.cpp"
		}
		break;
	case 7:
		{
#line 197 ".\\mylexer.l"
coutf("ELSE","else","");return ELSE;
#line 233 "mylexer.cpp"
		}
		break;
	case 8:
		{
#line 198 ".\\mylexer.l"
CHash*newtb=new CHash();
				allsymbol.push(newtb);coutf("WHILE","while","");return WHILE;
#line 241 "mylexer.cpp"
		}
		break;
	case 9:
		{
#line 200 ".\\mylexer.l"
CHash*newtb=new CHash();
				allsymbol.push(newtb);coutf("FOR","for","");return FOR;
#line 249 "mylexer.cpp"
		}
		break;
	case 10:
		{
#line 202 ".\\mylexer.l"
coutf("MAIN","main","");return MAIN;
#line 256 "mylexer.cpp"
		}
		break;
	case 11:
		{
#line 203 ".\\mylexer.l"
coutf("CONST","const","");return CONST;
#line 263 "mylexer.cpp"
		}
		break;
	case 12:
		{
#line 204 ".\\mylexer.l"
coutf("COUT","cout","");return COUT;
#line 270 "mylexer.cpp"
		}
		break;
	case 13:
		{
#line 205 ".\\mylexer.l"
coutf("CIN","cin","");return CIN;
#line 277 "mylexer.cpp"
		}
		break;
	case 14:
		{
#line 207 ".\\mylexer.l"
coutf("CLASS","class","");return CLASS;
#line 284 "mylexer.cpp"
		}
		break;
	case 15:
		{
#line 209 ".\\mylexer.l"
coutf("PUBLIC","public","");return PUBLIC;
#line 291 "mylexer.cpp"
		}
		break;
	case 16:
		{
#line 210 ".\\mylexer.l"
coutf("PRIVATE","private","");return PRIVATE;
#line 298 "mylexer.cpp"
		}
		break;
	case 17:
		{
#line 211 ".\\mylexer.l"
coutf("PROTECTED","protected","");return PROTECTED;
#line 305 "mylexer.cpp"
		}
		break;
	case 18:
		{
#line 213 ".\\mylexer.l"
coutf("INCLUDE","include","");return INCLUDE;
#line 312 "mylexer.cpp"
		}
		break;
	case 19:
		{
#line 214 ".\\mylexer.l"
coutf("USING","using","");return USING;
#line 319 "mylexer.cpp"
		}
		break;
	case 20:
		{
#line 215 ".\\mylexer.l"
coutf("NAMESPACE","namespace","");return NAMESPACE;
#line 326 "mylexer.cpp"
		}
		break;
	case 21:
		{
#line 216 ".\\mylexer.l"
coutf("RETURN","return","");return RETURN;
#line 333 "mylexer.cpp"
		}
		break;
	case 22:
		{
#line 218 ".\\mylexer.l"
coutf("WELL","#","");return WELL;
#line 340 "mylexer.cpp"
		}
		break;
	case 23:
		{
#line 220 ".\\mylexer.l"
yylval=newExpNode(CONSTK);yylval->type=FLOATK;yylval->attri.val=getfloat(yytext);coutf("FLOATD",yytext,yytext);return FLOATD;
#line 347 "mylexer.cpp"
		}
		break;
	case 24:
		{
#line 221 ".\\mylexer.l"
yylval=newExpNode(CONSTK);yylval->type=INTK;yylval->attri.val=getint(yytext);coutf("NUMBERD",yytext,yytext);return NUMBERD;
#line 354 "mylexer.cpp"
		}
		break;
	case 25:
		{
#line 222 ".\\mylexer.l"
yylval=newExpNode(CONSTK);yylval->type=INTK;yylval->attri.val=getint(yytext);coutf("DIGIT",yytext,yytext);return DIGIT;
#line 361 "mylexer.cpp"
		}
		break;
	case 26:
		{
#line 226 ".\\mylexer.l"
return CLASSMC;
#line 368 "mylexer.cpp"
		}
		break;
	case 27:
		{
#line 227 ".\\mylexer.l"
return CLASSRST;
#line 375 "mylexer.cpp"
		}
		break;
	case 28:
		{
#line 228 ".\\mylexer.l"
return NEW;
#line 382 "mylexer.cpp"
		}
		break;
	case 29:
		{
#line 229 ".\\mylexer.l"
return DELETE;
#line 389 "mylexer.cpp"
		}
		break;
	case 30:
		{
#line 232 ".\\mylexer.l"
coutf("COMMENT",yytext,yytext);coutf("COMMENT",yytext,yytext);
			


#line 399 "mylexer.cpp"
		}
		break;
	case 31:
		{
#line 237 ".\\mylexer.l"
coutf("LBRACE","{","");CHash*newtb=new CHash();
				allsymbol.push(newtb);return LBRACE;
#line 407 "mylexer.cpp"
		}
		break;
#line 239 ".\\mylexer.l"
				//关于函数特殊的处理在yacc中完成
				//但是外面的符号也需要可用
				//如果是这样....可能需要一直往下找。新函数：findfirtexist。
				//在lex中只是创建表项，不填。填表只会在base生命哪里创建
				//只要不是在第0层发现，都会创建。
				//新的符号表必须在lex中push
#line 417 "mylexer.cpp"
	case 32:
		{
#line 245 ".\\mylexer.l"
cout<<"hh";coutf("RBRACE","}","");cout<<"RBRACETEST:"<<allsymbol.empty()<<endl;storesymbol.push(allsymbol.top());allsymbol.pop();return RBRACE;
#line 422 "mylexer.cpp"
		}
		break;
	case 33:
		{
#line 246 ".\\mylexer.l"
coutf("LBRACEM","[","");return LBRACEM;
#line 429 "mylexer.cpp"
		}
		break;
	case 34:
		{
#line 247 ".\\mylexer.l"
coutf("RBRACEM","]","");return RBRACEM;
#line 436 "mylexer.cpp"
		}
		break;
	case 35:
		{
#line 248 ".\\mylexer.l"
coutf("LBRACES","<","");return LBRACES;
#line 443 "mylexer.cpp"
		}
		break;
	case 36:
		{
#line 249 ".\\mylexer.l"
coutf("RBRACES",">","");return RBRACES;
#line 450 "mylexer.cpp"
		}
		break;
	case 37:
		{
#line 250 ".\\mylexer.l"
coutf("LBRACESS","(","");return LBRACESS;
#line 457 "mylexer.cpp"
		}
		break;
	case 38:
		{
#line 251 ".\\mylexer.l"
coutf("RBRACESS",")","");return RBRACESS;
#line 464 "mylexer.cpp"
		}
		break;
	case 39:
		{
#line 252 ".\\mylexer.l"
coutf("SEMI",";","");return SEMI;
#line 471 "mylexer.cpp"
		}
		break;
	case 40:
		{
#line 253 ".\\mylexer.l"
coutf("COMMA",",","");return COMMA;
#line 478 "mylexer.cpp"
		}
		break;
	case 41:
		{
#line 254 ".\\mylexer.l"
coutf("POINT",".","");return POINT;
#line 485 "mylexer.cpp"
		}
		break;
	case 42:
		{
#line 258 ".\\mylexer.l"
yylval=newExpNode(CONSTK);yylval->type=STRINGK;string chars=yytext;yylval->attri.conststring=chars.substr(1,chars.length()-2);coutf("STRING",yytext,yytext);return STRING;
#line 492 "mylexer.cpp"
		}
		break;
	case 43:
		{
#line 259 ".\\mylexer.l"
yylval=newExpNode(CONSTK);yylval->type=CHARK;yylval->attri.val=yytext[1];coutf("ONECHAR",yytext,yytext);return ONECHAR;
#line 499 "mylexer.cpp"
		}
		break;
	case 44:
		{
#line 261 ".\\mylexer.l"
coutf("QUES","?","");return QUES;
#line 506 "mylexer.cpp"
		}
		break;
	case 45:
		{
#line 262 ".\\mylexer.l"
coutf("INVER","\\","");return INVER;
#line 513 "mylexer.cpp"
		}
		break;
	case 46:
		{
#line 263 ".\\mylexer.l"
coutf("EQ","=","");return EQ;
#line 520 "mylexer.cpp"
		}
		break;
	case 47:
		{
#line 264 ".\\mylexer.l"
coutf("COLON",":","");return COLON;
#line 527 "mylexer.cpp"
		}
		break;
	case 48:
		{
#line 265 ".\\mylexer.l"
coutf("ENDL","endl","");return ENDL;
#line 534 "mylexer.cpp"
		}
		break;
	case 49:
		{
#line 270 ".\\mylexer.l"
cout<<"test:top is:"<<allsymbol.top()<<endl;yylval=newExpNode(IDK);
			yylval->attri.name=yytext;
			//cout<<"pptrt"<<endl;
			//每次都会创建一个新的TreeNode返回，添加ID的事情是Yacc的事情
			return ID;
#line 545 "mylexer.cpp"
		}
		break;
	case 50:
		{
#line 276 ".\\mylexer.l"
coutf("LGCCEQ","==","");return LGCCEQ;
#line 552 "mylexer.cpp"
		}
		break;
	case 51:
		{
#line 277 ".\\mylexer.l"
coutf("LGCCLESSEQ","<=","");return LGCCLESSEQ;
#line 559 "mylexer.cpp"
		}
		break;
	case 52:
		{
#line 279 ".\\mylexer.l"
coutf("LGCCMOREEQ",">=","");return LGCCMOREEQ;
#line 566 "mylexer.cpp"
		}
		break;
	case 53:
		{
#line 281 ".\\mylexer.l"
coutf("LGCCNEQ","!=","");return LGCCNEQ;
#line 573 "mylexer.cpp"
		}
		break;
	case 54:
		{
#line 282 ".\\mylexer.l"
coutf("LGCCAND","&&","");return LGCCAND;
#line 580 "mylexer.cpp"
		}
		break;
	case 55:
		{
#line 283 ".\\mylexer.l"
coutf("LGCCOR","||","");return LGCCOR;
#line 587 "mylexer.cpp"
		}
		break;
	case 56:
		{
#line 284 ".\\mylexer.l"
coutf("LGCCN","!","");return LGCCN;
#line 594 "mylexer.cpp"
		}
		break;
	case 57:
		{
#line 286 ".\\mylexer.l"
coutf("BTCYH","^","");return BTCYH;
#line 601 "mylexer.cpp"
		}
		break;
	case 58:
		{
#line 287 ".\\mylexer.l"
coutf("BTCOR","|","");return BTCOR;
#line 608 "mylexer.cpp"
		}
		break;
	case 59:
		{
#line 288 ".\\mylexer.l"
coutf("BTCAND","&","");return BTCAND;
#line 615 "mylexer.cpp"
		}
		break;
	case 60:
		{
#line 289 ".\\mylexer.l"
coutf("BTCLEFT","<<","");return BTCLEFT;
#line 622 "mylexer.cpp"
		}
		break;
	case 61:
		{
#line 290 ".\\mylexer.l"
coutf("BTCRIGHT",">>","");return BTCRIGHT;
#line 629 "mylexer.cpp"
		}
		break;
	case 62:
		{
#line 291 ".\\mylexer.l"
coutf("BTCN","~","");return BTCN;
#line 636 "mylexer.cpp"
		}
		break;
	case 63:
		{
#line 293 ".\\mylexer.l"
coutf("ALGCADD","+","");return ALGCADD;
#line 643 "mylexer.cpp"
		}
		break;
	case 64:
		{
#line 294 ".\\mylexer.l"
coutf("ALGCMINUS","-","");return ALGCMINUS;
#line 650 "mylexer.cpp"
		}
		break;
	case 65:
		{
#line 295 ".\\mylexer.l"
coutf("ALGCMUL","*","");return ALGCMUL;
#line 657 "mylexer.cpp"
		}
		break;
	case 66:
		{
#line 296 ".\\mylexer.l"
coutf("ALGCDIV","/","");return ALGCDIV;
#line 664 "mylexer.cpp"
		}
		break;
	case 67:
		{
#line 297 ".\\mylexer.l"
coutf("ALGCMOD","%","");return ALGCMOD;
#line 671 "mylexer.cpp"
		}
		break;
	case 68:
		{
#line 298 ".\\mylexer.l"
coutf("ALGCTADD","++","");return ALGCTADD;
#line 678 "mylexer.cpp"
		}
		break;
	case 69:
		{
#line 299 ".\\mylexer.l"
coutf("ALGCTMINUS","--","");return ALGCTMINUS;
#line 685 "mylexer.cpp"
		}
		break;
	case 70:
		{
#line 301 ".\\mylexer.l"
lineno++;
#line 692 "mylexer.cpp"
		}
		break;
	case 71:
		{
#line 303 ".\\mylexer.l"
return ERRORCODE;
#line 699 "mylexer.cpp"
		}
		break;
	default:
		yyassert(0);
		break;
	}
	yyreturnflg = yyfalse;
	return 0;
}

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn .rch		// <warning: unreachable code> to the old state
#endif
#endif

void YYLEXERNAME::yytables()
{
	yystext_size = YYTEXT_SIZE;
	yysunput_size = YYUNPUT_SIZE;
	yytext_max = YYTEXT_MAX;
	yyunput_max = YYUNPUT_MAX;

	static const yymatch_t YYNEARFAR YYBASED_CODE match[] = {
		0
	};
	yymatch = match;

	yytransitionmax = 308;
	static const yytransition_t YYNEARFAR YYBASED_CODE transition[] = {
		{ 0, 0 },
		{ 4, 1 },
		{ 5, 1 },
		{ 102, 78 },
		{ 0, 51 },
		{ 0, 51 },
		{ 56, 17 },
		{ 60, 61 },
		{ 0, 7 },
		{ 61, 61 },
		{ 61, 61 },
		{ 61, 61 },
		{ 61, 61 },
		{ 61, 61 },
		{ 61, 61 },
		{ 61, 61 },
		{ 61, 61 },
		{ 61, 61 },
		{ 61, 61 },
		{ 82, 40 },
		{ 103, 78 },
		{ 95, 71 },
		{ 83, 40 },
		{ 57, 17 },
		{ 4, 1 },
		{ 6, 1 },
		{ 7, 1 },
		{ 8, 1 },
		{ 96, 71 },
		{ 9, 1 },
		{ 10, 1 },
		{ 11, 1 },
		{ 12, 1 },
		{ 13, 1 },
		{ 14, 1 },
		{ 15, 1 },
		{ 16, 1 },
		{ 17, 1 },
		{ 18, 1 },
		{ 19, 1 },
		{ 20, 1 },
		{ 21, 1 },
		{ 21, 1 },
		{ 21, 1 },
		{ 21, 1 },
		{ 21, 1 },
		{ 21, 1 },
		{ 21, 1 },
		{ 21, 1 },
		{ 21, 1 },
		{ 22, 1 },
		{ 23, 1 },
		{ 24, 1 },
		{ 25, 1 },
		{ 26, 1 },
		{ 27, 1 },
		{ 51, 51 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 29, 1 },
		{ 30, 1 },
		{ 31, 1 },
		{ 32, 1 },
		{ 28, 1 },
		{ 84, 41 },
		{ 28, 1 },
		{ 28, 1 },
		{ 33, 1 },
		{ 34, 1 },
		{ 35, 1 },
		{ 36, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 37, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 38, 1 },
		{ 39, 1 },
		{ 28, 1 },
		{ 40, 1 },
		{ 28, 1 },
		{ 41, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 42, 1 },
		{ 43, 1 },
		{ 44, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 28, 1 },
		{ 45, 1 },
		{ 46, 1 },
		{ 47, 1 },
		{ 48, 1 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 107, 82 },
		{ 80, 39 },
		{ 73, 35 },
		{ 85, 42 },
		{ 74, 35 },
		{ 81, 39 },
		{ 108, 82 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 58, 19 },
		{ 66, 26 },
		{ 67, 26 },
		{ 86, 43 },
		{ 28, 159 },
		{ 59, 19 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 28, 159 },
		{ 0, 11 },
		{ 77, 37 },
		{ 87, 44 },
		{ 75, 36 },
		{ 68, 33 },
		{ 69, 33 },
		{ 76, 36 },
		{ 88, 46 },
		{ 70, 33 },
		{ 78, 37 },
		{ 0, 11 },
		{ 71, 33 },
		{ 0, 11 },
		{ 63, 24 },
		{ 64, 24 },
		{ 0, 11 },
		{ 0, 11 },
		{ 89, 50 },
		{ 52, 10 },
		{ 90, 53 },
		{ 53, 54 },
		{ 0, 59 },
		{ 72, 34 },
		{ 54, 11 },
		{ 60, 60 },
		{ 60, 60 },
		{ 60, 60 },
		{ 60, 60 },
		{ 60, 60 },
		{ 60, 60 },
		{ 60, 60 },
		{ 60, 60 },
		{ 60, 60 },
		{ 60, 60 },
		{ 21, 21 },
		{ 21, 21 },
		{ 21, 21 },
		{ 21, 21 },
		{ 21, 21 },
		{ 21, 21 },
		{ 21, 21 },
		{ 21, 21 },
		{ 21, 21 },
		{ 21, 21 },
		{ 49, 6 },
		{ 92, 68 },
		{ 93, 69 },
		{ 94, 70 },
		{ 62, 22 },
		{ 97, 72 },
		{ 98, 73 },
		{ 99, 74 },
		{ 100, 75 },
		{ 101, 76 },
		{ 0, 11 },
		{ 55, 15 },
		{ 0, 11 },
		{ 104, 79 },
		{ 105, 80 },
		{ 106, 81 },
		{ 79, 38 },
		{ 109, 83 },
		{ 110, 84 },
		{ 111, 85 },
		{ 112, 86 },
		{ 113, 87 },
		{ 114, 91 },
		{ 115, 92 },
		{ 116, 94 },
		{ 117, 95 },
		{ 118, 96 },
		{ 119, 97 },
		{ 120, 98 },
		{ 121, 99 },
		{ 122, 100 },
		{ 123, 102 },
		{ 124, 104 },
		{ 125, 105 },
		{ 126, 107 },
		{ 127, 108 },
		{ 128, 109 },
		{ 129, 110 },
		{ 130, 111 },
		{ 131, 112 },
		{ 132, 113 },
		{ 91, 114 },
		{ 133, 116 },
		{ 134, 117 },
		{ 135, 119 },
		{ 136, 122 },
		{ 137, 123 },
		{ 138, 125 },
		{ 139, 126 },
		{ 140, 127 },
		{ 141, 128 },
		{ 142, 129 },
		{ 143, 130 },
		{ 144, 132 },
		{ 145, 135 },
		{ 146, 137 },
		{ 147, 138 },
		{ 148, 139 },
		{ 149, 140 },
		{ 150, 141 },
		{ 151, 142 },
		{ 152, 146 },
		{ 153, 147 },
		{ 154, 148 },
		{ 155, 149 },
		{ 156, 153 },
		{ 157, 155 },
		{ 158, 156 },
		{ 159, 157 },
		{ 65, 25 }
	};
	yytransition = transition;

	static const yystate_t YYNEARFAR YYBASED_CODE state[] = {
		{ 0, 0, 0 },
		{ -3, -8, 0 },
		{ 1, 0, 0 },
		{ 0, 0, 71 },
		{ 0, 0, 1 },
		{ 0, 0, 70 },
		{ 0, 177, 56 },
		{ 51, -26, 71 },
		{ 0, 0, 22 },
		{ 0, 0, 67 },
		{ 0, 174, 59 },
		{ -53, 125, 71 },
		{ 0, 0, 37 },
		{ 0, 0, 38 },
		{ 0, 0, 65 },
		{ 0, 206, 63 },
		{ 0, 0, 40 },
		{ 0, -39, 64 },
		{ 0, 0, 41 },
		{ 0, 120, 66 },
		{ 61, 0, 25 },
		{ 61, 180, 24 },
		{ 0, 184, 47 },
		{ 0, 0, 39 },
		{ 0, 147, 35 },
		{ 0, 246, 46 },
		{ 0, 102, 36 },
		{ 0, 0, 44 },
		{ 159, 0, 49 },
		{ 0, 0, 33 },
		{ 0, 0, 45 },
		{ 0, 0, 34 },
		{ 0, 0, 57 },
		{ 159, 94, 49 },
		{ 159, 115, 49 },
		{ 159, 23, 49 },
		{ 159, 89, 49 },
		{ 159, 93, 49 },
		{ 159, 157, 49 },
		{ 159, 33, 49 },
		{ 159, -95, 49 },
		{ 159, -13, 49 },
		{ 159, 17, 49 },
		{ 159, 54, 49 },
		{ 159, 92, 49 },
		{ 0, 0, 31 },
		{ 0, 77, 58 },
		{ 0, 0, 32 },
		{ 0, 0, 62 },
		{ 0, 0, 53 },
		{ 51, 177, 0 },
		{ -50, -36, 0 },
		{ 0, 0, 54 },
		{ 0, 174, 0 },
		{ 0, 175, 0 },
		{ 0, 0, 68 },
		{ 0, 0, 69 },
		{ 0, 0, 26 },
		{ 114, 0, 0 },
		{ -59, 205, 30 },
		{ 0, 170, 23 },
		{ 0, -39, 0 },
		{ 0, 0, 27 },
		{ 0, 0, 60 },
		{ 0, 0, 51 },
		{ 0, 0, 50 },
		{ 0, 0, 52 },
		{ 0, 0, 61 },
		{ 159, 142, 49 },
		{ 159, 130, 49 },
		{ 159, 144, 49 },
		{ 159, -89, 49 },
		{ 159, 135, 49 },
		{ 159, 129, 49 },
		{ 159, 145, 49 },
		{ 159, 135, 49 },
		{ 159, 133, 49 },
		{ 159, 0, 6 },
		{ 159, -96, 49 },
		{ 159, 146, 49 },
		{ 159, 143, 49 },
		{ 159, 134, 49 },
		{ 159, 24, 49 },
		{ 159, 157, 49 },
		{ 159, 140, 49 },
		{ 159, 152, 49 },
		{ 159, 153, 49 },
		{ 159, 154, 49 },
		{ 0, 0, 55 },
		{ 0, 0, 42 },
		{ 0, 0, 43 },
		{ 114, 213, 0 },
		{ 159, 147, 49 },
		{ 159, 0, 13 },
		{ 159, 147, 49 },
		{ 159, 148, 49 },
		{ 159, 148, 49 },
		{ 159, 164, 49 },
		{ 159, 165, 49 },
		{ 159, 159, 49 },
		{ 159, 171, 49 },
		{ 159, 0, 9 },
		{ 159, 161, 49 },
		{ 159, 0, 2 },
		{ 159, 160, 49 },
		{ 159, 170, 49 },
		{ 159, 0, 28 },
		{ 159, 154, 49 },
		{ 159, 157, 49 },
		{ 159, 166, 49 },
		{ 159, 158, 49 },
		{ 159, 166, 49 },
		{ 159, 177, 49 },
		{ 159, 170, 49 },
		{ -58, 237, 30 },
		{ 159, 0, 4 },
		{ 159, 165, 49 },
		{ 159, 165, 49 },
		{ 159, 0, 12 },
		{ 159, 166, 49 },
		{ 159, 0, 7 },
		{ 159, 0, 48 },
		{ 159, 167, 49 },
		{ 159, 167, 49 },
		{ 159, 0, 10 },
		{ 159, 170, 49 },
		{ 159, 189, 49 },
		{ 159, 186, 49 },
		{ 159, 183, 49 },
		{ 159, 175, 49 },
		{ 159, 187, 49 },
		{ 159, 0, 5 },
		{ 159, 190, 49 },
		{ 159, 0, 14 },
		{ 159, 0, 11 },
		{ 159, 191, 49 },
		{ 159, 0, 3 },
		{ 159, 193, 49 },
		{ 159, 182, 49 },
		{ 159, 179, 49 },
		{ 159, 197, 49 },
		{ 159, 198, 49 },
		{ 159, 188, 49 },
		{ 159, 0, 19 },
		{ 159, 0, 8 },
		{ 159, 0, 29 },
		{ 159, 198, 49 },
		{ 159, 203, 49 },
		{ 159, 200, 49 },
		{ 159, 186, 49 },
		{ 159, 0, 15 },
		{ 159, 0, 21 },
		{ 159, 0, 18 },
		{ 159, 204, 49 },
		{ 159, 0, 16 },
		{ 159, 203, 49 },
		{ 159, 204, 49 },
		{ 159, 206, 49 },
		{ 159, 0, 20 },
		{ 0, 71, 17 }
	};
	yystate = state;

	static const yybackup_t YYNEARFAR YYBASED_CODE backup[] = {
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	};
	yybackup = backup;
}
#line 305 ".\\mylexer.l"


/////////////////////////////////////////////////////////////////////////////
// programs section
TreeNode * newExpNode(ExpKind kind)
{
  	TreeNode*t = new TreeNode();
  int i;
  if (t==NULL)
    cout<<"Out of memory error at line "<<lineno<<endl;
  else {
    for (i=0;i<MAXCHILD;i++){ 
		t->child[i] = NULL;
	}
    t->sibling = NULL;
    t->nodekind = EXPK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = INTK;
  }
  return t;
}
void coutf(string token,string lexeme,string attri){
	mout.setf(ios::left);
	mout<<setw(10)<<token<<setw(10)<<lexeme<<setw(10)<<attri<<endl;
}
void coutf(string token,string lexeme,Node* attri){
	mout.setf(ios::left);
	mout<<setw(10)<<token<<setw(10)<<lexeme<<setw(10)<<attri<<endl;
}
int getint(string s){
    return atoi(s.c_str());
}
float getfloat(const string &s){
	istringstream iss(s);
	float num;
	iss>>num;
	return num;
}

