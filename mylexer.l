%{
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

%}

/////////////////////////////////////////////////////////////////////////////
// declarations section
IF if
ELSE else
WHILE while
FOR for

MAIN main
CONST const 
//后面有空格
INT int 
CHAR char 
FLOAT float 
VOID void

TYPE {INT}|{CHAR}|{FLOAT}
PUBLIC public
PRIVATE private
PROTECTED protected



CLASS class 
INCLUDE include
USING using 
NAMESPACE namespace 

WELL #
//return后面没有空格
RETURN return
COUT cout
CIN cin

LBRACE \{
RBEACE \}
LBRACEM \[
RBRACEM \]
LBRACES \<
RBRACES \>
LBRACESS \(
RBRACESS \)
INVER \\
SEMI ;
COMMA ,
POINT \.

DQUOTE \"
QUOTE '

STRING \"([^(\")]|(\\\"))*([^(\"\\)]|(\\\"))+\"

ONECHAR {QUOTE}([^{QUOTE}\\]|(\\{QUOTE})){QUOTE}

QUES \?
EQ =
COLON :
ENDL endl

BLANK \t|" "
ENTER \n

COMMENT \/\/.*|\/\*([^\/\*]|{ENTER})*\*\/

ID [a-zA-Z_][a-zA-Z_0-9]*

/*多行注释扰乱了line
LGCC2 ==|\<=|\>=|\<|\>|!=|&&|\|\|
LGCC1 !
BTC2 \^|\||&|\<\<|\>\>
BTC1 ~
ALGC2 \+|\/|%
MINUS -
STAR \*
*/
LGCCEQ ==
LGCCLESSEQ \<=
//LGCCLESS \<
LGCCMOREEQ \>=
//LGCCMORE \>
LGCCNEQ !=
LGCCAND &&
LGCCOR \|\|
LGCCN !

BTCYH \^
BTCOR \|
BTCAND &
BTCLEFT \<\<
BTCRIGHT \>\>
BTCN ~

ALGCADD \+
ALGCMINUS -
ALGCMUL \*
ALGCDIV \/
ALGCMOD \%

ALGCTADD \+\+
ALGCTMINUS --

CLASSMC -\>
CLASSRST ::
NEW new
DELETE delete

DIGIT [0-9]
NUMBERD [1-9]{DIGIT}*
FLOATD [0-9]{DIGIT}*\.{DIGIT}*




// lexical analyser name
%name mylexer

// class definition
{
	// place any extra class members here
}

// constructor
{
	// place any extra initialisation code here
	allsymbol.push(symbtb);
	cout<<"EXE"<<endl;
}

// destructor
{
	// place any extra cleanup code here
}

// place any declarations here

%%

/////////////////////////////////////////////////////////////////////////////
// rules section


//.	{}

%{
	// extract yylval for use later on in actions
	YYSTYPE YYFAR& yylval = *(YYSTYPE YYFAR*)yyparserptr->yylvalptr;
%}

// place your Lex rules here
{BLANK}	{;}


{INT}	{coutf("INT","int","");return INT;}
{FLOAT}	{coutf("FLOAT","float","");return FLOAT;}
{CHAR}	{coutf("CHAR","char","");return CHAR;}
{VOID}	{coutf("VOID","void","");return VOID;}

{IF}	{CHash*newtb=new CHash();
				allsymbol.push(newtb);coutf("IF","if","");return IF;}
{ELSE}	{coutf("ELSE","else","");return ELSE;}
{WHILE}	{CHash*newtb=new CHash();
				allsymbol.push(newtb);coutf("WHILE","while","");return WHILE;}
{FOR}	{CHash*newtb=new CHash();
				allsymbol.push(newtb);coutf("FOR","for","");return FOR;}
{MAIN}	{coutf("MAIN","main","");return MAIN;}
{CONST}	{coutf("CONST","const","");return CONST;}
{COUT}	{coutf("COUT","cout","");return COUT;}
{CIN}	{coutf("CIN","cin","");return CIN;}

{CLASS}	{coutf("CLASS","class","");return CLASS;}

{PUBLIC}	{coutf("PUBLIC","public","");return PUBLIC;}
{PRIVATE}	{coutf("PRIVATE","private","");return PRIVATE;}
{PROTECTED}	{coutf("PROTECTED","protected","");return PROTECTED;}

{INCLUDE}	{coutf("INCLUDE","include","");return INCLUDE;}
{USING}		{coutf("USING","using","");return USING;}
{NAMESPACE}	{coutf("NAMESPACE","namespace","");return NAMESPACE;}
{RETURN}	{coutf("RETURN","return","");return RETURN;}

{WELL}		{coutf("WELL","#","");return WELL;}

{FLOATD}	{yylval=newExpNode(CONSTK);yylval->type=FLOATK;yylval->attri.val=getfloat(yytext);coutf("FLOATD",yytext,yytext);return FLOATD;}
{NUMBERD}	{yylval=newExpNode(CONSTK);yylval->type=INTK;yylval->attri.val=getint(yytext);coutf("NUMBERD",yytext,yytext);return NUMBERD;}
{DIGIT}		{yylval=newExpNode(CONSTK);yylval->type=INTK;yylval->attri.val=getint(yytext);coutf("DIGIT",yytext,yytext);return DIGIT;}

//

{CLASSMC}	{return CLASSMC;}
{CLASSRST}	{return CLASSRST;}
{NEW}	 {return NEW;}
{DELETE}	{return DELETE;}


{COMMENT}	{coutf("COMMENT",yytext,yytext);coutf("COMMENT",yytext,yytext);
			

}

{LBRACE}	{coutf("LBRACE","{","");CHash*newtb=new CHash();
				allsymbol.push(newtb);return LBRACE;}//每碰到一个就新压入一个符号表。
				//关于函数特殊的处理在yacc中完成
				//但是外面的符号也需要可用
				//如果是这样....可能需要一直往下找。新函数：findfirtexist。
				//在lex中只是创建表项，不填。填表只会在base生命哪里创建
				//只要不是在第0层发现，都会创建。
				//新的符号表必须在lex中push
{RBEACE}	{cout<<"hh";coutf("RBRACE","}","");cout<<"RBRACETEST:"<<allsymbol.empty()<<endl;storesymbol.push(allsymbol.top());allsymbol.pop();return RBRACE;}
{LBRACEM}	{coutf("LBRACEM","[","");return LBRACEM;}
{RBRACEM}	{coutf("RBRACEM","]","");return RBRACEM;}
{LBRACES}	{coutf("LBRACES","<","");return LBRACES;}
{RBRACES}	{coutf("RBRACES",">","");return RBRACES;}
{LBRACESS}	{coutf("LBRACESS","(","");return LBRACESS;}
{RBRACESS}	{coutf("RBRACESS",")","");return RBRACESS;}
{SEMI}		{coutf("SEMI",";","");return SEMI;}
{COMMA}		{coutf("COMMA",",","");return COMMA;}
{POINT}		{coutf("POINT",".","");return POINT;}

//{DQUOTE}	{coutf("DQUOTE","\"","");}
//{QUOTE}		{coutf("QUOTE","'","");}
{STRING}	{yylval=newExpNode(CONSTK);yylval->type=STRINGK;string chars=yytext;yylval->attri.conststring=chars.substr(1,chars.length()-2);coutf("STRING",yytext,yytext);return STRING;}
{ONECHAR}	{yylval=newExpNode(CONSTK);yylval->type=CHARK;yylval->attri.val=yytext[1];coutf("ONECHAR",yytext,yytext);return ONECHAR;}

{QUES}		{coutf("QUES","?","");return QUES;}
{INVER}		{coutf("INVER","\\","");return INVER;}//
{EQ}		{coutf("EQ","=","");return EQ;}
{COLON}		{coutf("COLON",":","");return COLON;}
{ENDL}		{coutf("ENDL","endl","");return ENDL;}



//
{ID}	{cout<<"test:top is:"<<allsymbol.top()<<endl;yylval=newExpNode(IDK);
			yylval->attri.name=yytext;
			//cout<<"pptrt"<<endl;
			//每次都会创建一个新的TreeNode返回，添加ID的事情是Yacc的事情
			return ID;}//ID的type最初是不知道的。
//
{LGCCEQ}	{coutf("LGCCEQ","==","");return LGCCEQ;}
{LGCCLESSEQ}	{coutf("LGCCLESSEQ","<=","");return LGCCLESSEQ;}
//{LGCCLESS}		//{coutf("LGCCLESS","<","");}//never matched
{LGCCMOREEQ}	{coutf("LGCCMOREEQ",">=","");return LGCCMOREEQ;}
//{LGCCMORE}		//{coutf("LGCCMORE",">","");}
{LGCCNEQ}		{coutf("LGCCNEQ","!=","");return LGCCNEQ;}
{LGCCAND}		{coutf("LGCCAND","&&","");return LGCCAND;}
{LGCCOR}		{coutf("LGCCOR","||","");return LGCCOR;}
{LGCCN}		{coutf("LGCCN","!","");return LGCCN;}

{BTCYH}		{coutf("BTCYH","^","");return BTCYH;}
{BTCOR}		{coutf("BTCOR","|","");return BTCOR;}
{BTCAND}	{coutf("BTCAND","&","");return BTCAND;}
{BTCLEFT}	{coutf("BTCLEFT","<<","");return BTCLEFT;}
{BTCRIGHT}	{coutf("BTCRIGHT",">>","");return BTCRIGHT;}
{BTCN}		{coutf("BTCN","~","");return BTCN;}

{ALGCADD}	{coutf("ALGCADD","+","");return ALGCADD;}
{ALGCMINUS}	{coutf("ALGCMINUS","-","");return ALGCMINUS;}
{ALGCMUL}	{coutf("ALGCMUL","*","");return ALGCMUL;}
{ALGCDIV}	{coutf("ALGCDIV","/","");return ALGCDIV;}
{ALGCMOD}	{coutf("ALGCMOD","%","");return ALGCMOD;}
{ALGCTADD}	{coutf("ALGCTADD","++","");return ALGCTADD;}
{ALGCTMINUS}	{coutf("ALGCTMINUS","--","");return ALGCTMINUS;}

{ENTER}	{lineno++;}

. {return ERRORCODE;}

%%

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
