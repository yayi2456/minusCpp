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
* myparser.h
* C++ header file generated from myparser.y.
* 
* Date: 01/04/18
* Time: 02:52:38
* 
* AYACC Version: 2.07
****************************************************************************/

#ifndef _MYPARSER_H
#define _MYPARSER_H

#include <yycpars.h>

/////////////////////////////////////////////////////////////////////////////
// myparser

#ifndef YYEXPPARSER
#define YYEXPPARSER
#endif

class YYEXPPARSER YYFAR myparser : public _YL yyfparser {
public:
	myparser();
	virtual ~myparser();

protected:
	void yytables();
	virtual void yyaction(int action);
#ifdef YYDEBUG
	void YYFAR* yyattribute1(int index) const;
	void yyinitdebug(void YYFAR** p, int count) const;
#endif

	// attribute functions
	virtual void yystacktoval(int index);
	virtual void yyvaltostack(int index);
	virtual void yylvaltoval();
	virtual void yyvaltolval();
	virtual void yylvaltostack(int index);

	virtual void YYFAR* yynewattribute(int count);
	virtual void yydeleteattribute(void YYFAR* attribute);
	virtual void yycopyattribute(void YYFAR* dest, const void YYFAR* src, int count);

public:
#line 210 ".\\myparser.y"

	// place any extra class members here
	

#line 70 "myparser.h"
};

#ifndef YYPARSERNAME
#define YYPARSERNAME myparser
#endif

#line 226 ".\\myparser.y"

#ifndef YYSTYPE
//#define YYSTYPE string
#define YYSTYPE TreeNode*
#endif



#line 86 "myparser.h"
#define ALGCADD 257
#define ALGCMINUS 258
#define ALGCMUL 259
#define ALGCDIV 260
#define ALGCMOD 261
#define ALGCTADD 262
#define ALGCTMINUS 263
#define NUMBERD 264
#define DIGIT 265
#define STRING 266
#define ONECHAR 267
#define FLOATD 268
#define LBRACESS 269
#define RBRACESS 270
#define EQ 271
#define INT 272
#define FLOAT 273
#define CHAR 274
#define VOID 275
#define IF 276
#define ELSE 277
#define WHILE 278
#define FOR 279
#define MAIN 280
#define CONST 281
#define COUT 282
#define CIN 283
#define ENDL 284
#define CLASS 285
#define PUBLIC 286
#define PRIVATE 287
#define PROTECTED 288
#define INCLUDE 289
#define USING 290
#define NAMESPACE 291
#define WELL 292
#define RETURN 293
#define LBRACE 294
#define RBRACE 295
#define LBRACEM 296
#define RBRACEM 297
#define LBRACES 298
#define RBRACES 299
#define SEMI 300
#define COMMA 301
#define POINT 302
#define QUES 303
#define INVER 304
#define COLON 305
#define LGCCEQ 306
#define LGCCLESSEQ 307
#define LGCCMOREEQ 308
#define LGCCNEQ 309
#define LGCCAND 310
#define LGCCOR 311
#define LGCCN 312
#define BTCYH 313
#define BTCOR 314
#define BTCAND 315
#define BTCLEFT 316
#define BTCRIGHT 317
#define BTCN 318
#define ID 319
#define CLASSMC 320
#define CLASSRST 321
#define NEW 322
#define DELETE 323
#define ERRORCODE 324
#define LGCCMORE 325
#define LGCCLESS 326
#define UMINUS 327
#define GETADDR 328
#define GETCONTENT 329
#define ALGCTADDP 330
#define ALGCTMINUSP 331
#define ALGCTADDB 332
#define ALGCTMINUSB 333
#define FUNCUSE 334
#define ARRAYC 335
#endif
