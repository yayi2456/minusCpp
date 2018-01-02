#############################################################################
#                     U N R E G I S T E R E D   C O P Y
# 
# You are on day 109 of your 30 day trial period.
# 
# This file was produced by an UNREGISTERED COPY of Parser Generator. It is
# for evaluation purposes only. If you continue to use Parser Generator 30
# days after installation then you are required to purchase a license. For
# more information see the online help or go to the Bumble-Bee Software
# homepage at:
# 
# http://www.bumblebeesoftware.com
# 
# This notice must remain present in the file. It cannot be removed.
#############################################################################

#############################################################################
# myparser.v
# YACC verbose file generated from myparser.y.
# 
# Date: 01/02/18
# Time: 14:41:22
# 
# AYACC Version: 2.07
#############################################################################


##############################################################################
# Rules
##############################################################################

    0  $accept : start $end

    1  start : startinfo
    2        | start startinfo

    3  startinfo : classdef
    4            | basetypestmt
    5            | funcdef
    6            | funcdefmain

    7  basetype : INT
    8           | CHAR
    9           | FLOAT
   10           | VOID

   11  idlistwithvar : idlistwithvar COMMA ID
   12                | ID
   13                | idlistwithvar COMMA ID EQ expr
   14                | ID EQ expr
   15                | idlistwithvar COMMA ALGCMUL ID
   16                | idlistwithvar COMMA ID LBRACEM NUMBERD RBRACEM
   17                | ALGCMUL ID
   18                | ID LBRACEM NUMBERD RBRACEM

   19  exprlist : exprlist COMMA expr
   20           | expr

   21  basetypestmt : basetype idlistwithvar SEMI
   22               | among idlistwithvar SEMI

   23  among : ID

   24  expr : valueexpr
   25       | calexpr
   26       | DELETE valueexpr LBRACEM RBRACEM

   27  valueexpr : ID
   28            | valueexpr CLASSMC valueexpr
   29            | ALGCMUL valueexpr
   30            | valueexpr LBRACEM expr RBRACEM
   31            | ALGCTADD valueexpr
   32            | ALGCTMINUS valueexpr
   33            | LBRACESS valueexpr RBRACESS
   34            | valueexpr POINT valueexpr

   35  calexpr : expr ALGCADD expr
   36          | expr ALGCMINUS expr
   37          | expr ALGCMUL expr
   38          | expr ALGCDIV expr
   39          | expr ALGCMOD expr
   40          | LBRACESS calexpr RBRACESS
   41          | ALGCMINUS expr
   42          | NUMBERD
   43          | DIGIT
   44          | FLOATD
   45          | STRING
   46          | ONECHAR
   47          | valueexpr ALGCTADD
   48          | valueexpr ALGCTMINUS
   49          | LGCCN expr
   50          | BTCN expr
   51          | expr BTCRIGHT expr
   52          | expr BTCLEFT expr
   53          | expr LGCCMOREEQ expr
   54          | expr LGCCLESSEQ expr
   55          | expr LBRACES expr
   56          | expr RBRACES expr
   57          | expr LGCCEQ expr
   58          | expr LGCCNEQ expr
   59          | expr BTCAND expr
   60          | expr BTCOR expr
   61          | expr BTCYH expr
   62          | expr LGCCAND expr
   63          | expr LGCCOR expr
   64          | ID LBRACESS exprlist RBRACESS
   65          | valueexpr CLASSMC ID LBRACESS exprlist RBRACESS
   66          | valueexpr POINT ID LBRACESS exprlist RBRACESS
   67          | ID LBRACESS RBRACESS
   68          | valueexpr CLASSMC ID LBRACESS RBRACESS
   69          | valueexpr POINT ID LBRACESS RBRACESS
   70          | expr EQ expr
   71          | BTCAND expr

   72  returnstmt : RETURN expr SEMI

   73  stmt : expr SEMI
   74       | LBRACESS error SEMI
   75       | basetypestmt
   76       | ifstmt
   77       | whilestmt
   78       | forstmt
   79       | cinstmt
   80       | coutstmt
   81       | returnstmt
   82       | SEMI

   83  cstmtlist : cstmtlist comstmt
   84            | cstmtlist stmt
   85            | comstmt
   86            | stmt

   87  comstmt : LBRACE midum cstmtlist RBRACE
   88          | LBRACE midum RBRACE

   89  midum :

   90  stmtcomstmt : stmt
   91              | comstmt

   92  ifstmt : IF LBRACESS expr RBRACESS stmtcomstmt ELSE stmtcomstmt
   93         | IF LBRACESS expr RBRACESS stmtcomstmt
   94         | IF LBRACESS expr error stmtcomstmt ELSE stmtcomstmt
   95         | IF LBRACESS expr error stmtcomstmt

   96  whilestmt : WHILE LBRACESS expr RBRACESS stmtcomstmt
   97            | WHILE LBRACESS expr error stmtcomstmt

   98  forstmt : FOR LBRACESS expr SEMI expr SEMI expr RBRACESS stmtcomstmt
   99          | FOR LBRACESS expr SEMI expr SEMI RBRACESS stmtcomstmt
  100          | FOR LBRACESS expr SEMI SEMI expr RBRACESS stmtcomstmt
  101          | FOR LBRACESS SEMI expr SEMI expr RBRACESS stmtcomstmt
  102          | FOR LBRACESS expr SEMI SEMI RBRACESS stmtcomstmt
  103          | FOR LBRACESS SEMI expr SEMI RBRACESS stmtcomstmt
  104          | FOR LBRACESS SEMI SEMI expr RBRACESS stmtcomstmt
  105          | FOR LBRACESS SEMI SEMI RBRACESS stmtcomstmt

  106  coutlist : coutlist BTCLEFT expr
  107           | BTCLEFT expr

  108  coutstmt : COUT coutlist SEMI

  109  cinlist : cinlist BTCRIGHT valueexpr
  110          | BTCRIGHT valueexpr

  111  cinstmt : CIN cinlist SEMI

  112  typep : basetype
  113        | basetype ALGCMUL

  114  typeidlist : typeidlist COMMA typep ID
  115             | typeidlist COMMA typep ID LBRACEM NUMBERD RBRACEM
  116             | typep ID
  117             | typep ID LBRACEM NUMBERD RBRACEM

  118  funcdef : basetype ID LBRACESS typeidlist RBRACESS comstmt
  119          | basetype ALGCMUL ID LBRACESS typeidlist RBRACESS comstmt
  120          | basetype ID LBRACESS RBRACESS comstmt
  121          | basetype ALGCMUL ID LBRACESS RBRACESS comstmt

  122  funcdefmain : INT MAIN LBRACESS RBRACESS comstmt
  123              | INT MAIN LBRACESS error comstmt

  124  inclass : inclass basetypestmt
  125          | inclass funcdef
  126          | basetypestmt
  127          | funcdef

  128  classdef : CLASS ID LBRACE inclass RBRACE SEMI


##############################################################################
# States
##############################################################################

state 0
	$accept : . start $end

	INT  shift 1
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	CLASS  shift 5
	ID  shift 6

	basetypestmt  goto 7
	classdef  goto 8
	funcdef  goto 9
	funcdefmain  goto 10
	basetype  goto 11
	startinfo  goto 12
	start  goto 13
	among  goto 14


state 1
	basetype : INT .  (7)
	funcdefmain : INT . MAIN LBRACESS RBRACESS comstmt
	funcdefmain : INT . MAIN LBRACESS error comstmt

	MAIN  shift 15
	.  reduce 7


state 2
	basetype : FLOAT .  (9)

	.  reduce 9


state 3
	basetype : CHAR .  (8)

	.  reduce 8


state 4
	basetype : VOID .  (10)

	.  reduce 10


state 5
	classdef : CLASS . ID LBRACE inclass RBRACE SEMI

	ID  shift 16


state 6
	among : ID .  (23)

	.  reduce 23


state 7
	startinfo : basetypestmt .  (4)

	.  reduce 4


state 8
	startinfo : classdef .  (3)

	.  reduce 3


state 9
	startinfo : funcdef .  (5)

	.  reduce 5


state 10
	startinfo : funcdefmain .  (6)

	.  reduce 6


state 11
	basetypestmt : basetype . idlistwithvar SEMI
	funcdef : basetype . ALGCMUL ID LBRACESS typeidlist RBRACESS comstmt
	funcdef : basetype . ID LBRACESS typeidlist RBRACESS comstmt
	funcdef : basetype . ID LBRACESS RBRACESS comstmt
	funcdef : basetype . ALGCMUL ID LBRACESS RBRACESS comstmt

	ALGCMUL  shift 17
	ID  shift 18

	idlistwithvar  goto 19


state 12
	start : startinfo .  (1)

	.  reduce 1


state 13
	$accept : start . $end  (0)
	start : start . startinfo

	$end  accept
	INT  shift 1
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	CLASS  shift 5
	ID  shift 6

	basetypestmt  goto 7
	classdef  goto 8
	funcdef  goto 9
	funcdefmain  goto 10
	basetype  goto 11
	startinfo  goto 20
	among  goto 14


state 14
	basetypestmt : among . idlistwithvar SEMI

	ALGCMUL  shift 21
	ID  shift 22

	idlistwithvar  goto 23


state 15
	funcdefmain : INT MAIN . LBRACESS RBRACESS comstmt
	funcdefmain : INT MAIN . LBRACESS error comstmt

	LBRACESS  shift 24


state 16
	classdef : CLASS ID . LBRACE inclass RBRACE SEMI

	LBRACE  shift 25


state 17
	idlistwithvar : ALGCMUL . ID
	funcdef : basetype ALGCMUL . ID LBRACESS typeidlist RBRACESS comstmt
	funcdef : basetype ALGCMUL . ID LBRACESS RBRACESS comstmt

	ID  shift 26


state 18
	idlistwithvar : ID .  (12)
	idlistwithvar : ID . EQ expr
	idlistwithvar : ID . LBRACEM NUMBERD RBRACEM
	funcdef : basetype ID . LBRACESS typeidlist RBRACESS comstmt
	funcdef : basetype ID . LBRACESS RBRACESS comstmt

	LBRACESS  shift 27
	EQ  shift 28
	LBRACEM  shift 29
	.  reduce 12


state 19
	idlistwithvar : idlistwithvar . COMMA ID
	idlistwithvar : idlistwithvar . COMMA ID EQ expr
	idlistwithvar : idlistwithvar . COMMA ALGCMUL ID
	idlistwithvar : idlistwithvar . COMMA ID LBRACEM NUMBERD RBRACEM
	basetypestmt : basetype idlistwithvar . SEMI

	SEMI  shift 30
	COMMA  shift 31


state 20
	start : start startinfo .  (2)

	.  reduce 2


state 21
	idlistwithvar : ALGCMUL . ID

	ID  shift 32


state 22
	idlistwithvar : ID .  (12)
	idlistwithvar : ID . EQ expr
	idlistwithvar : ID . LBRACEM NUMBERD RBRACEM

	EQ  shift 28
	LBRACEM  shift 29
	.  reduce 12


state 23
	idlistwithvar : idlistwithvar . COMMA ID
	idlistwithvar : idlistwithvar . COMMA ID EQ expr
	idlistwithvar : idlistwithvar . COMMA ALGCMUL ID
	idlistwithvar : idlistwithvar . COMMA ID LBRACEM NUMBERD RBRACEM
	basetypestmt : among idlistwithvar . SEMI

	SEMI  shift 33
	COMMA  shift 31


state 24
	funcdefmain : INT MAIN LBRACESS . RBRACESS comstmt
	funcdefmain : INT MAIN LBRACESS . error comstmt

	error  shift 34
	RBRACESS  shift 35


state 25
	classdef : CLASS ID LBRACE . inclass RBRACE SEMI

	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	ID  shift 6

	basetypestmt  goto 37
	funcdef  goto 38
	basetype  goto 11
	among  goto 14
	inclass  goto 39


state 26
	idlistwithvar : ALGCMUL ID .  (17)
	funcdef : basetype ALGCMUL ID . LBRACESS typeidlist RBRACESS comstmt
	funcdef : basetype ALGCMUL ID . LBRACESS RBRACESS comstmt

	LBRACESS  shift 40
	.  reduce 17


state 27
	funcdef : basetype ID LBRACESS . typeidlist RBRACESS comstmt
	funcdef : basetype ID LBRACESS . RBRACESS comstmt

	RBRACESS  shift 41
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4

	basetype  goto 42
	typeidlist  goto 43
	typep  goto 44


state 28
	idlistwithvar : ID EQ . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 60
	valueexpr  goto 61
	calexpr  goto 62


state 29
	idlistwithvar : ID LBRACEM . NUMBERD RBRACEM

	NUMBERD  shift 63


state 30
	basetypestmt : basetype idlistwithvar SEMI .  (21)

	.  reduce 21


state 31
	idlistwithvar : idlistwithvar COMMA . ID
	idlistwithvar : idlistwithvar COMMA . ID EQ expr
	idlistwithvar : idlistwithvar COMMA . ALGCMUL ID
	idlistwithvar : idlistwithvar COMMA . ID LBRACEM NUMBERD RBRACEM

	ALGCMUL  shift 64
	ID  shift 65


state 32
	idlistwithvar : ALGCMUL ID .  (17)

	.  reduce 17


state 33
	basetypestmt : among idlistwithvar SEMI .  (22)

	.  reduce 22


state 34
	funcdefmain : INT MAIN LBRACESS error . comstmt

	LBRACE  shift 66

	comstmt  goto 67


state 35
	funcdefmain : INT MAIN LBRACESS RBRACESS . comstmt

	LBRACE  shift 66

	comstmt  goto 68


state 36
	basetype : INT .  (7)

	.  reduce 7


state 37
	inclass : basetypestmt .  (126)

	.  reduce 126


state 38
	inclass : funcdef .  (127)

	.  reduce 127


state 39
	inclass : inclass . basetypestmt
	inclass : inclass . funcdef
	classdef : CLASS ID LBRACE inclass . RBRACE SEMI

	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	RBRACE  shift 69
	ID  shift 6

	basetypestmt  goto 70
	funcdef  goto 71
	basetype  goto 11
	among  goto 14


state 40
	funcdef : basetype ALGCMUL ID LBRACESS . typeidlist RBRACESS comstmt
	funcdef : basetype ALGCMUL ID LBRACESS . RBRACESS comstmt

	RBRACESS  shift 72
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4

	basetype  goto 42
	typeidlist  goto 73
	typep  goto 44


state 41
	funcdef : basetype ID LBRACESS RBRACESS . comstmt

	LBRACE  shift 66

	comstmt  goto 74


state 42
	typep : basetype . ALGCMUL
	typep : basetype .  (112)

	ALGCMUL  shift 75
	.  reduce 112


state 43
	typeidlist : typeidlist . COMMA typep ID
	funcdef : basetype ID LBRACESS typeidlist . RBRACESS comstmt
	typeidlist : typeidlist . COMMA typep ID LBRACEM NUMBERD RBRACEM

	RBRACESS  shift 76
	COMMA  shift 77


state 44
	typeidlist : typep . ID LBRACEM NUMBERD RBRACEM
	typeidlist : typep . ID

	ID  shift 78


state 45
	calexpr : ALGCMINUS . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 79
	valueexpr  goto 61
	calexpr  goto 62


state 46
	valueexpr : ALGCMUL . valueexpr

	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 82


state 47
	valueexpr : ALGCTADD . valueexpr

	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 83


state 48
	valueexpr : ALGCTMINUS . valueexpr

	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 84


state 49
	calexpr : NUMBERD .  (42)

	.  reduce 42


state 50
	calexpr : DIGIT .  (43)

	.  reduce 43


state 51
	calexpr : STRING .  (45)

	.  reduce 45


state 52
	calexpr : ONECHAR .  (46)

	.  reduce 46


state 53
	calexpr : FLOATD .  (44)

	.  reduce 44


state 54
	valueexpr : LBRACESS . valueexpr RBRACESS
	calexpr : LBRACESS . calexpr RBRACESS

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 85
	valueexpr  goto 86
	calexpr  goto 87


state 55
	calexpr : LGCCN . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 88
	valueexpr  goto 61
	calexpr  goto 62


state 56
	calexpr : BTCAND . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 89
	valueexpr  goto 61
	calexpr  goto 62


state 57
	calexpr : BTCN . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 90
	valueexpr  goto 61
	calexpr  goto 62


state 58
	valueexpr : ID .  (27)
	calexpr : ID . LBRACESS exprlist RBRACESS
	calexpr : ID . LBRACESS RBRACESS

	LBRACESS  shift 91
	.  reduce 27


state 59
	expr : DELETE . valueexpr LBRACEM RBRACEM

	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 92


state 60
	idlistwithvar : ID EQ expr .  (14)
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111
	.  reduce 14


state 61
	valueexpr : valueexpr . LBRACEM expr RBRACEM
	expr : valueexpr .  (24)
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr . POINT valueexpr
	calexpr : valueexpr . ALGCTMINUS
	calexpr : valueexpr . CLASSMC ID LBRACESS exprlist RBRACESS
	calexpr : valueexpr . ALGCTADD
	calexpr : valueexpr . POINT ID LBRACESS exprlist RBRACESS
	calexpr : valueexpr . CLASSMC ID LBRACESS RBRACESS
	calexpr : valueexpr . POINT ID LBRACESS RBRACESS

	ALGCTADD  shift 112
	ALGCTMINUS  shift 113
	LBRACEM  shift 114
	POINT  shift 115
	CLASSMC  shift 116
	.  reduce 24


state 62
	expr : calexpr .  (25)

	.  reduce 25


state 63
	idlistwithvar : ID LBRACEM NUMBERD . RBRACEM

	RBRACEM  shift 117


state 64
	idlistwithvar : idlistwithvar COMMA ALGCMUL . ID

	ID  shift 118


state 65
	idlistwithvar : idlistwithvar COMMA ID .  (11)
	idlistwithvar : idlistwithvar COMMA ID . EQ expr
	idlistwithvar : idlistwithvar COMMA ID . LBRACEM NUMBERD RBRACEM

	EQ  shift 119
	LBRACEM  shift 120
	.  reduce 11


state 66
	comstmt : LBRACE . midum cstmtlist RBRACE
	comstmt : LBRACE . midum RBRACE
	midum : .  (89)

	.  reduce 89

	midum  goto 121


state 67
	funcdefmain : INT MAIN LBRACESS error comstmt .  (123)

	.  reduce 123


state 68
	funcdefmain : INT MAIN LBRACESS RBRACESS comstmt .  (122)

	.  reduce 122


state 69
	classdef : CLASS ID LBRACE inclass RBRACE . SEMI

	SEMI  shift 122


state 70
	inclass : inclass basetypestmt .  (124)

	.  reduce 124


state 71
	inclass : inclass funcdef .  (125)

	.  reduce 125


state 72
	funcdef : basetype ALGCMUL ID LBRACESS RBRACESS . comstmt

	LBRACE  shift 66

	comstmt  goto 123


state 73
	typeidlist : typeidlist . COMMA typep ID
	funcdef : basetype ALGCMUL ID LBRACESS typeidlist . RBRACESS comstmt
	typeidlist : typeidlist . COMMA typep ID LBRACEM NUMBERD RBRACEM

	RBRACESS  shift 124
	COMMA  shift 77


state 74
	funcdef : basetype ID LBRACESS RBRACESS comstmt .  (120)

	.  reduce 120


state 75
	typep : basetype ALGCMUL .  (113)

	.  reduce 113


state 76
	funcdef : basetype ID LBRACESS typeidlist RBRACESS . comstmt

	LBRACE  shift 66

	comstmt  goto 125


state 77
	typeidlist : typeidlist COMMA . typep ID
	typeidlist : typeidlist COMMA . typep ID LBRACEM NUMBERD RBRACEM

	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4

	basetype  goto 42
	typep  goto 126


state 78
	typeidlist : typep ID . LBRACEM NUMBERD RBRACEM
	typeidlist : typep ID .  (116)

	LBRACEM  shift 127
	.  reduce 116


state 79
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : ALGCMINUS expr .  (41)
	calexpr : expr . EQ expr

	.  reduce 41


state 80
	valueexpr : LBRACESS . valueexpr RBRACESS

	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 128


state 81
	valueexpr : ID .  (27)

	.  reduce 27


state 82
	valueexpr : valueexpr . LBRACEM expr RBRACEM
	valueexpr : ALGCMUL valueexpr .  (29)
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr . POINT valueexpr

	LBRACEM  shift 114
	POINT  shift 129
	CLASSMC  shift 130
	.  reduce 29


state 83
	valueexpr : valueexpr . LBRACEM expr RBRACEM
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : ALGCTADD valueexpr .  (31)
	valueexpr : valueexpr . POINT valueexpr

	LBRACEM  shift 114
	POINT  shift 129
	CLASSMC  shift 130
	.  reduce 31


state 84
	valueexpr : valueexpr . LBRACEM expr RBRACEM
	valueexpr : ALGCTMINUS valueexpr .  (32)
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr . POINT valueexpr

	LBRACEM  shift 114
	POINT  shift 129
	CLASSMC  shift 130
	.  reduce 32


state 85
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111


state 86
	valueexpr : valueexpr . LBRACEM expr RBRACEM
	expr : valueexpr .  (24)
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : LBRACESS valueexpr . RBRACESS
	valueexpr : valueexpr . POINT valueexpr
	calexpr : valueexpr . ALGCTMINUS
	calexpr : valueexpr . CLASSMC ID LBRACESS exprlist RBRACESS
	calexpr : valueexpr . ALGCTADD
	calexpr : valueexpr . POINT ID LBRACESS exprlist RBRACESS
	calexpr : valueexpr . CLASSMC ID LBRACESS RBRACESS
	calexpr : valueexpr . POINT ID LBRACESS RBRACESS

	ALGCTADD  shift 112
	ALGCTMINUS  shift 113
	RBRACESS  shift 131
	LBRACEM  shift 114
	POINT  shift 115
	CLASSMC  shift 116
	.  reduce 24


state 87
	expr : calexpr .  (25)
	calexpr : LBRACESS calexpr . RBRACESS

	RBRACESS  shift 132
	.  reduce 25


state 88
	calexpr : LGCCN expr .  (49)
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	.  reduce 49


state 89
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr
	calexpr : BTCAND expr .  (71)

	.  reduce 71


state 90
	calexpr : BTCN expr .  (50)
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	.  reduce 50


state 91
	calexpr : ID LBRACESS . exprlist RBRACESS
	calexpr : ID LBRACESS . RBRACESS

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	RBRACESS  shift 133
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 134
	exprlist  goto 135
	valueexpr  goto 61
	calexpr  goto 62


state 92
	valueexpr : valueexpr . LBRACEM expr RBRACEM
	expr : DELETE valueexpr . LBRACEM RBRACEM
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr . POINT valueexpr

	LBRACEM  shift 136
	POINT  shift 129
	CLASSMC  shift 130


state 93
	calexpr : expr ALGCADD . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 137
	valueexpr  goto 61
	calexpr  goto 62


state 94
	calexpr : expr ALGCMINUS . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 138
	valueexpr  goto 61
	calexpr  goto 62


state 95
	calexpr : expr ALGCMUL . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 139
	valueexpr  goto 61
	calexpr  goto 62


state 96
	calexpr : expr ALGCDIV . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 140
	valueexpr  goto 61
	calexpr  goto 62


state 97
	calexpr : expr ALGCMOD . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 141
	valueexpr  goto 61
	calexpr  goto 62


state 98
	calexpr : expr EQ . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 142
	valueexpr  goto 61
	calexpr  goto 62


state 99
	calexpr : expr LBRACES . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 143
	valueexpr  goto 61
	calexpr  goto 62


state 100
	calexpr : expr RBRACES . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 144
	valueexpr  goto 61
	calexpr  goto 62


state 101
	calexpr : expr LGCCEQ . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 145
	valueexpr  goto 61
	calexpr  goto 62


state 102
	calexpr : expr LGCCLESSEQ . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 146
	valueexpr  goto 61
	calexpr  goto 62


state 103
	calexpr : expr LGCCMOREEQ . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 147
	valueexpr  goto 61
	calexpr  goto 62


state 104
	calexpr : expr LGCCNEQ . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 148
	valueexpr  goto 61
	calexpr  goto 62


state 105
	calexpr : expr LGCCAND . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 149
	valueexpr  goto 61
	calexpr  goto 62


state 106
	calexpr : expr LGCCOR . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 150
	valueexpr  goto 61
	calexpr  goto 62


state 107
	calexpr : expr BTCYH . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 151
	valueexpr  goto 61
	calexpr  goto 62


state 108
	calexpr : expr BTCOR . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 152
	valueexpr  goto 61
	calexpr  goto 62


state 109
	calexpr : expr BTCAND . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 153
	valueexpr  goto 61
	calexpr  goto 62


state 110
	calexpr : expr BTCLEFT . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 154
	valueexpr  goto 61
	calexpr  goto 62


state 111
	calexpr : expr BTCRIGHT . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 155
	valueexpr  goto 61
	calexpr  goto 62


state 112
	calexpr : valueexpr ALGCTADD .  (47)

	.  reduce 47


state 113
	calexpr : valueexpr ALGCTMINUS .  (48)

	.  reduce 48


state 114
	valueexpr : valueexpr LBRACEM . expr RBRACEM

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 156
	valueexpr  goto 61
	calexpr  goto 62


state 115
	valueexpr : valueexpr POINT . valueexpr
	calexpr : valueexpr POINT . ID LBRACESS exprlist RBRACESS
	calexpr : valueexpr POINT . ID LBRACESS RBRACESS

	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	LBRACESS  shift 80
	ID  shift 157

	valueexpr  goto 158


state 116
	valueexpr : valueexpr CLASSMC . valueexpr
	calexpr : valueexpr CLASSMC . ID LBRACESS exprlist RBRACESS
	calexpr : valueexpr CLASSMC . ID LBRACESS RBRACESS

	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	LBRACESS  shift 80
	ID  shift 159

	valueexpr  goto 160


state 117
	idlistwithvar : ID LBRACEM NUMBERD RBRACEM .  (18)

	.  reduce 18


state 118
	idlistwithvar : idlistwithvar COMMA ALGCMUL ID .  (15)

	.  reduce 15


state 119
	idlistwithvar : idlistwithvar COMMA ID EQ . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 161
	valueexpr  goto 61
	calexpr  goto 62


state 120
	idlistwithvar : idlistwithvar COMMA ID LBRACEM . NUMBERD RBRACEM

	NUMBERD  shift 162


state 121
	comstmt : LBRACE midum . cstmtlist RBRACE
	comstmt : LBRACE midum . RBRACE

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 163
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 164
	WHILE  shift 165
	FOR  shift 166
	COUT  shift 167
	CIN  shift 168
	RETURN  shift 169
	LBRACE  shift 66
	RBRACE  shift 170
	SEMI  shift 171
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 172
	DELETE  shift 59

	basetypestmt  goto 173
	basetype  goto 174
	expr  goto 175
	stmt  goto 176
	among  goto 14
	cinstmt  goto 177
	ifstmt  goto 178
	whilestmt  goto 179
	coutstmt  goto 180
	valueexpr  goto 61
	returnstmt  goto 181
	forstmt  goto 182
	calexpr  goto 62
	comstmt  goto 183
	cstmtlist  goto 184


state 122
	classdef : CLASS ID LBRACE inclass RBRACE SEMI .  (128)

	.  reduce 128


state 123
	funcdef : basetype ALGCMUL ID LBRACESS RBRACESS comstmt .  (121)

	.  reduce 121


state 124
	funcdef : basetype ALGCMUL ID LBRACESS typeidlist RBRACESS . comstmt

	LBRACE  shift 66

	comstmt  goto 185


state 125
	funcdef : basetype ID LBRACESS typeidlist RBRACESS comstmt .  (118)

	.  reduce 118


state 126
	typeidlist : typeidlist COMMA typep . ID
	typeidlist : typeidlist COMMA typep . ID LBRACEM NUMBERD RBRACEM

	ID  shift 186


state 127
	typeidlist : typep ID LBRACEM . NUMBERD RBRACEM

	NUMBERD  shift 187


state 128
	valueexpr : valueexpr . LBRACEM expr RBRACEM
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : LBRACESS valueexpr . RBRACESS
	valueexpr : valueexpr . POINT valueexpr

	RBRACESS  shift 131
	LBRACEM  shift 114
	POINT  shift 129
	CLASSMC  shift 130


state 129
	valueexpr : valueexpr POINT . valueexpr

	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 158


state 130
	valueexpr : valueexpr CLASSMC . valueexpr

	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 160


state 131
	valueexpr : LBRACESS valueexpr RBRACESS .  (33)

	.  reduce 33


state 132
	calexpr : LBRACESS calexpr RBRACESS .  (40)

	.  reduce 40


state 133
	calexpr : ID LBRACESS RBRACESS .  (67)

	.  reduce 67


state 134
	exprlist : expr .  (20)
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111
	.  reduce 20


state 135
	exprlist : exprlist . COMMA expr
	calexpr : ID LBRACESS exprlist . RBRACESS

	RBRACESS  shift 188
	COMMA  shift 189


state 136
	valueexpr : valueexpr LBRACEM . expr RBRACEM
	expr : DELETE valueexpr LBRACEM . RBRACEM

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	RBRACEM  shift 190
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 156
	valueexpr  goto 61
	calexpr  goto 62


state 137
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr ALGCADD expr .  (35)
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	.  reduce 35


state 138
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr ALGCMINUS expr .  (36)
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	.  reduce 36


state 139
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr ALGCMUL expr .  (37)
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	.  reduce 37


state 140
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr ALGCDIV expr .  (38)
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	.  reduce 38


state 141
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr ALGCMOD expr .  (39)
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	.  reduce 39


state 142
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr EQ expr .  (70)
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111
	.  reduce 70


state 143
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr LBRACES expr .  (55)
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	BTCLEFT  shift 110
	BTCRIGHT  shift 111
	.  reduce 55


state 144
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr RBRACES expr .  (56)
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	BTCLEFT  shift 110
	BTCRIGHT  shift 111
	.  reduce 56


state 145
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr LGCCEQ expr .  (57)
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	BTCLEFT  shift 110
	BTCRIGHT  shift 111
	.  reduce 57


state 146
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr LGCCLESSEQ expr .  (54)
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	BTCLEFT  shift 110
	BTCRIGHT  shift 111
	.  reduce 54


state 147
	calexpr : expr LGCCMOREEQ expr .  (53)
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	BTCLEFT  shift 110
	BTCRIGHT  shift 111
	.  reduce 53


state 148
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr LGCCNEQ expr .  (58)
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	BTCLEFT  shift 110
	BTCRIGHT  shift 111
	.  reduce 58


state 149
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr LGCCAND expr .  (62)
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111
	.  reduce 62


state 150
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr LGCCOR expr .  (63)
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111
	.  reduce 63


state 151
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr BTCYH expr .  (61)
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111
	.  reduce 61


state 152
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr BTCOR expr .  (60)
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	BTCYH  shift 107
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111
	.  reduce 60


state 153
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr BTCAND expr .  (59)
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	BTCLEFT  shift 110
	BTCRIGHT  shift 111
	.  reduce 59


state 154
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr BTCLEFT expr .  (52)
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	.  reduce 52


state 155
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr BTCRIGHT expr .  (51)
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	.  reduce 51


state 156
	valueexpr : valueexpr LBRACEM expr . RBRACEM
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	EQ  shift 98
	RBRACEM  shift 191
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111


state 157
	valueexpr : ID .  (27)
	calexpr : valueexpr POINT ID . LBRACESS exprlist RBRACESS
	calexpr : valueexpr POINT ID . LBRACESS RBRACESS

	LBRACESS  shift 192
	.  reduce 27


state 158
	valueexpr : valueexpr . LBRACEM expr RBRACEM
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr POINT valueexpr .  (34)
	valueexpr : valueexpr . POINT valueexpr

	LBRACEM  shift 114
	POINT  shift 129
	CLASSMC  shift 130
	.  reduce 34


state 159
	valueexpr : ID .  (27)
	calexpr : valueexpr CLASSMC ID . LBRACESS exprlist RBRACESS
	calexpr : valueexpr CLASSMC ID . LBRACESS RBRACESS

	LBRACESS  shift 193
	.  reduce 27


state 160
	valueexpr : valueexpr . LBRACEM expr RBRACEM
	valueexpr : valueexpr CLASSMC valueexpr .  (28)
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr . POINT valueexpr

	LBRACEM  shift 114
	POINT  shift 129
	CLASSMC  shift 130
	.  reduce 28


state 161
	idlistwithvar : idlistwithvar COMMA ID EQ expr .  (13)
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111
	.  reduce 13


state 162
	idlistwithvar : idlistwithvar COMMA ID LBRACEM NUMBERD . RBRACEM

	RBRACEM  shift 194


state 163
	valueexpr : LBRACESS . valueexpr RBRACESS
	calexpr : LBRACESS . calexpr RBRACESS
	stmt : LBRACESS . error SEMI

	error  shift 195
	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 85
	valueexpr  goto 86
	calexpr  goto 87


state 164
	ifstmt : IF . LBRACESS expr RBRACESS stmtcomstmt ELSE stmtcomstmt
	ifstmt : IF . LBRACESS expr RBRACESS stmtcomstmt
	ifstmt : IF . LBRACESS expr error stmtcomstmt ELSE stmtcomstmt
	ifstmt : IF . LBRACESS expr error stmtcomstmt

	LBRACESS  shift 196


state 165
	whilestmt : WHILE . LBRACESS expr RBRACESS stmtcomstmt
	whilestmt : WHILE . LBRACESS expr error stmtcomstmt

	LBRACESS  shift 197


state 166
	forstmt : FOR . LBRACESS expr SEMI expr SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR . LBRACESS expr SEMI expr SEMI RBRACESS stmtcomstmt
	forstmt : FOR . LBRACESS expr SEMI SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR . LBRACESS SEMI expr SEMI RBRACESS stmtcomstmt
	forstmt : FOR . LBRACESS expr SEMI SEMI RBRACESS stmtcomstmt
	forstmt : FOR . LBRACESS SEMI expr SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR . LBRACESS SEMI SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR . LBRACESS SEMI SEMI RBRACESS stmtcomstmt

	LBRACESS  shift 198


state 167
	coutstmt : COUT . coutlist SEMI

	BTCLEFT  shift 199

	coutlist  goto 200


state 168
	cinstmt : CIN . cinlist SEMI

	BTCRIGHT  shift 201

	cinlist  goto 202


state 169
	returnstmt : RETURN . expr SEMI

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 203
	valueexpr  goto 61
	calexpr  goto 62


state 170
	comstmt : LBRACE midum RBRACE .  (88)

	.  reduce 88


state 171
	stmt : SEMI .  (82)

	.  reduce 82


172: reduce-reduce conflict (reduce 23, reduce 27) on ALGCMUL
state 172
	valueexpr : ID .  (27)
	among : ID .  (23)
	calexpr : ID . LBRACESS exprlist RBRACESS
	calexpr : ID . LBRACESS RBRACESS

	LBRACESS  shift 91
	ALGCMUL  reduce 23
	ID  reduce 23
	.  reduce 27


state 173
	stmt : basetypestmt .  (75)

	.  reduce 75


state 174
	basetypestmt : basetype . idlistwithvar SEMI

	ALGCMUL  shift 21
	ID  shift 22

	idlistwithvar  goto 19


state 175
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr
	stmt : expr . SEMI

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	SEMI  shift 204
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111


state 176
	cstmtlist : stmt .  (86)

	.  reduce 86


state 177
	stmt : cinstmt .  (79)

	.  reduce 79


state 178
	stmt : ifstmt .  (76)

	.  reduce 76


state 179
	stmt : whilestmt .  (77)

	.  reduce 77


state 180
	stmt : coutstmt .  (80)

	.  reduce 80


state 181
	stmt : returnstmt .  (81)

	.  reduce 81


state 182
	stmt : forstmt .  (78)

	.  reduce 78


state 183
	cstmtlist : comstmt .  (85)

	.  reduce 85


state 184
	comstmt : LBRACE midum cstmtlist . RBRACE
	cstmtlist : cstmtlist . stmt
	cstmtlist : cstmtlist . comstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 163
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 164
	WHILE  shift 165
	FOR  shift 166
	COUT  shift 167
	CIN  shift 168
	RETURN  shift 169
	LBRACE  shift 66
	RBRACE  shift 205
	SEMI  shift 171
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 172
	DELETE  shift 59

	basetypestmt  goto 173
	basetype  goto 174
	expr  goto 175
	stmt  goto 206
	among  goto 14
	cinstmt  goto 177
	ifstmt  goto 178
	whilestmt  goto 179
	coutstmt  goto 180
	valueexpr  goto 61
	returnstmt  goto 181
	forstmt  goto 182
	calexpr  goto 62
	comstmt  goto 207


state 185
	funcdef : basetype ALGCMUL ID LBRACESS typeidlist RBRACESS comstmt .  (119)

	.  reduce 119


state 186
	typeidlist : typeidlist COMMA typep ID .  (114)
	typeidlist : typeidlist COMMA typep ID . LBRACEM NUMBERD RBRACEM

	LBRACEM  shift 208
	.  reduce 114


state 187
	typeidlist : typep ID LBRACEM NUMBERD . RBRACEM

	RBRACEM  shift 209


state 188
	calexpr : ID LBRACESS exprlist RBRACESS .  (64)

	.  reduce 64


state 189
	exprlist : exprlist COMMA . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 210
	valueexpr  goto 61
	calexpr  goto 62


state 190
	expr : DELETE valueexpr LBRACEM RBRACEM .  (26)

	.  reduce 26


state 191
	valueexpr : valueexpr LBRACEM expr RBRACEM .  (30)

	.  reduce 30


state 192
	calexpr : valueexpr POINT ID LBRACESS . exprlist RBRACESS
	calexpr : valueexpr POINT ID LBRACESS . RBRACESS

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	RBRACESS  shift 211
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 134
	exprlist  goto 212
	valueexpr  goto 61
	calexpr  goto 62


state 193
	calexpr : valueexpr CLASSMC ID LBRACESS . exprlist RBRACESS
	calexpr : valueexpr CLASSMC ID LBRACESS . RBRACESS

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	RBRACESS  shift 213
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 134
	exprlist  goto 214
	valueexpr  goto 61
	calexpr  goto 62


state 194
	idlistwithvar : idlistwithvar COMMA ID LBRACEM NUMBERD RBRACEM .  (16)

	.  reduce 16


state 195
	stmt : LBRACESS error . SEMI

	SEMI  shift 215


state 196
	ifstmt : IF LBRACESS . expr RBRACESS stmtcomstmt ELSE stmtcomstmt
	ifstmt : IF LBRACESS . expr RBRACESS stmtcomstmt
	ifstmt : IF LBRACESS . expr error stmtcomstmt ELSE stmtcomstmt
	ifstmt : IF LBRACESS . expr error stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 216
	valueexpr  goto 61
	calexpr  goto 62


state 197
	whilestmt : WHILE LBRACESS . expr RBRACESS stmtcomstmt
	whilestmt : WHILE LBRACESS . expr error stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 217
	valueexpr  goto 61
	calexpr  goto 62


state 198
	forstmt : FOR LBRACESS . expr SEMI expr SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS . expr SEMI expr SEMI RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS . expr SEMI SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS . SEMI expr SEMI RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS . expr SEMI SEMI RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS . SEMI expr SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS . SEMI SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS . SEMI SEMI RBRACESS stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	SEMI  shift 218
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 219
	valueexpr  goto 61
	calexpr  goto 62


state 199
	coutlist : BTCLEFT . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 220
	valueexpr  goto 61
	calexpr  goto 62


state 200
	coutlist : coutlist . BTCLEFT expr
	coutstmt : COUT coutlist . SEMI

	SEMI  shift 221
	BTCLEFT  shift 222


state 201
	cinlist : BTCRIGHT . valueexpr

	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 223


state 202
	cinlist : cinlist . BTCRIGHT valueexpr
	cinstmt : CIN cinlist . SEMI

	SEMI  shift 224
	BTCRIGHT  shift 225


state 203
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr
	returnstmt : RETURN expr . SEMI

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	SEMI  shift 226
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111


state 204
	stmt : expr SEMI .  (73)

	.  reduce 73


state 205
	comstmt : LBRACE midum cstmtlist RBRACE .  (87)

	.  reduce 87


state 206
	cstmtlist : cstmtlist stmt .  (84)

	.  reduce 84


state 207
	cstmtlist : cstmtlist comstmt .  (83)

	.  reduce 83


state 208
	typeidlist : typeidlist COMMA typep ID LBRACEM . NUMBERD RBRACEM

	NUMBERD  shift 227


state 209
	typeidlist : typep ID LBRACEM NUMBERD RBRACEM .  (117)

	.  reduce 117


state 210
	exprlist : exprlist COMMA expr .  (19)
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111
	.  reduce 19


state 211
	calexpr : valueexpr POINT ID LBRACESS RBRACESS .  (69)

	.  reduce 69


state 212
	exprlist : exprlist . COMMA expr
	calexpr : valueexpr POINT ID LBRACESS exprlist . RBRACESS

	RBRACESS  shift 228
	COMMA  shift 189


state 213
	calexpr : valueexpr CLASSMC ID LBRACESS RBRACESS .  (68)

	.  reduce 68


state 214
	exprlist : exprlist . COMMA expr
	calexpr : valueexpr CLASSMC ID LBRACESS exprlist . RBRACESS

	RBRACESS  shift 229
	COMMA  shift 189


state 215
	stmt : LBRACESS error SEMI .  (74)

	.  reduce 74


state 216
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	ifstmt : IF LBRACESS expr . RBRACESS stmtcomstmt ELSE stmtcomstmt
	calexpr : expr . EQ expr
	ifstmt : IF LBRACESS expr . RBRACESS stmtcomstmt
	ifstmt : IF LBRACESS expr . error stmtcomstmt ELSE stmtcomstmt
	ifstmt : IF LBRACESS expr . error stmtcomstmt

	error  shift 230
	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	RBRACESS  shift 231
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111


state 217
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	whilestmt : WHILE LBRACESS expr . RBRACESS stmtcomstmt
	calexpr : expr . EQ expr
	whilestmt : WHILE LBRACESS expr . error stmtcomstmt

	error  shift 232
	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	RBRACESS  shift 233
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111


state 218
	forstmt : FOR LBRACESS SEMI . expr SEMI RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS SEMI . expr SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS SEMI . SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS SEMI . SEMI RBRACESS stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	SEMI  shift 234
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 235
	valueexpr  goto 61
	calexpr  goto 62


state 219
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr
	forstmt : FOR LBRACESS expr . SEMI expr SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr . SEMI expr SEMI RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr . SEMI SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr . SEMI SEMI RBRACESS stmtcomstmt

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	SEMI  shift 236
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111


state 220
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr
	coutlist : BTCLEFT expr .  (107)

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCRIGHT  shift 111
	.  reduce 107


state 221
	coutstmt : COUT coutlist SEMI .  (108)

	.  reduce 108


state 222
	coutlist : coutlist BTCLEFT . expr

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 237
	valueexpr  goto 61
	calexpr  goto 62


state 223
	valueexpr : valueexpr . LBRACEM expr RBRACEM
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr . POINT valueexpr
	cinlist : BTCRIGHT valueexpr .  (110)

	LBRACEM  shift 114
	POINT  shift 129
	CLASSMC  shift 130
	.  reduce 110


state 224
	cinstmt : CIN cinlist SEMI .  (111)

	.  reduce 111


state 225
	cinlist : cinlist BTCRIGHT . valueexpr

	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 238


state 226
	returnstmt : RETURN expr SEMI .  (72)

	.  reduce 72


state 227
	typeidlist : typeidlist COMMA typep ID LBRACEM NUMBERD . RBRACEM

	RBRACEM  shift 239


state 228
	calexpr : valueexpr POINT ID LBRACESS exprlist RBRACESS .  (66)

	.  reduce 66


state 229
	calexpr : valueexpr CLASSMC ID LBRACESS exprlist RBRACESS .  (65)

	.  reduce 65


state 230
	ifstmt : IF LBRACESS expr error . stmtcomstmt ELSE stmtcomstmt
	ifstmt : IF LBRACESS expr error . stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 163
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 164
	WHILE  shift 165
	FOR  shift 166
	COUT  shift 167
	CIN  shift 168
	RETURN  shift 169
	LBRACE  shift 66
	SEMI  shift 171
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 172
	DELETE  shift 59

	basetypestmt  goto 173
	basetype  goto 174
	expr  goto 175
	stmt  goto 240
	among  goto 14
	cinstmt  goto 177
	ifstmt  goto 178
	whilestmt  goto 179
	coutstmt  goto 180
	valueexpr  goto 61
	returnstmt  goto 181
	forstmt  goto 182
	calexpr  goto 62
	comstmt  goto 241
	stmtcomstmt  goto 242


state 231
	ifstmt : IF LBRACESS expr RBRACESS . stmtcomstmt ELSE stmtcomstmt
	ifstmt : IF LBRACESS expr RBRACESS . stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 163
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 164
	WHILE  shift 165
	FOR  shift 166
	COUT  shift 167
	CIN  shift 168
	RETURN  shift 169
	LBRACE  shift 66
	SEMI  shift 171
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 172
	DELETE  shift 59

	basetypestmt  goto 173
	basetype  goto 174
	expr  goto 175
	stmt  goto 240
	among  goto 14
	cinstmt  goto 177
	ifstmt  goto 178
	whilestmt  goto 179
	coutstmt  goto 180
	valueexpr  goto 61
	returnstmt  goto 181
	forstmt  goto 182
	calexpr  goto 62
	comstmt  goto 241
	stmtcomstmt  goto 243


state 232
	whilestmt : WHILE LBRACESS expr error . stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 163
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 164
	WHILE  shift 165
	FOR  shift 166
	COUT  shift 167
	CIN  shift 168
	RETURN  shift 169
	LBRACE  shift 66
	SEMI  shift 171
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 172
	DELETE  shift 59

	basetypestmt  goto 173
	basetype  goto 174
	expr  goto 175
	stmt  goto 240
	among  goto 14
	cinstmt  goto 177
	ifstmt  goto 178
	whilestmt  goto 179
	coutstmt  goto 180
	valueexpr  goto 61
	returnstmt  goto 181
	forstmt  goto 182
	calexpr  goto 62
	comstmt  goto 241
	stmtcomstmt  goto 244


state 233
	whilestmt : WHILE LBRACESS expr RBRACESS . stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 163
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 164
	WHILE  shift 165
	FOR  shift 166
	COUT  shift 167
	CIN  shift 168
	RETURN  shift 169
	LBRACE  shift 66
	SEMI  shift 171
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 172
	DELETE  shift 59

	basetypestmt  goto 173
	basetype  goto 174
	expr  goto 175
	stmt  goto 240
	among  goto 14
	cinstmt  goto 177
	ifstmt  goto 178
	whilestmt  goto 179
	coutstmt  goto 180
	valueexpr  goto 61
	returnstmt  goto 181
	forstmt  goto 182
	calexpr  goto 62
	comstmt  goto 241
	stmtcomstmt  goto 245


state 234
	forstmt : FOR LBRACESS SEMI SEMI . expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS SEMI SEMI . RBRACESS stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	RBRACESS  shift 246
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 247
	valueexpr  goto 61
	calexpr  goto 62


state 235
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr
	forstmt : FOR LBRACESS SEMI expr . SEMI RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS SEMI expr . SEMI expr RBRACESS stmtcomstmt

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	SEMI  shift 248
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111


state 236
	forstmt : FOR LBRACESS expr SEMI . expr SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr SEMI . expr SEMI RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr SEMI . SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr SEMI . SEMI RBRACESS stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	SEMI  shift 249
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 250
	valueexpr  goto 61
	calexpr  goto 62


state 237
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr
	coutlist : coutlist BTCLEFT expr .  (106)

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCRIGHT  shift 111
	.  reduce 106


state 238
	valueexpr : valueexpr . LBRACEM expr RBRACEM
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr . POINT valueexpr
	cinlist : cinlist BTCRIGHT valueexpr .  (109)

	LBRACEM  shift 114
	POINT  shift 129
	CLASSMC  shift 130
	.  reduce 109


state 239
	typeidlist : typeidlist COMMA typep ID LBRACEM NUMBERD RBRACEM .  (115)

	.  reduce 115


state 240
	stmtcomstmt : stmt .  (90)

	.  reduce 90


state 241
	stmtcomstmt : comstmt .  (91)

	.  reduce 91


242: shift-reduce conflict (shift 251, reduce 95) on ELSE
state 242
	ifstmt : IF LBRACESS expr error stmtcomstmt . ELSE stmtcomstmt
	ifstmt : IF LBRACESS expr error stmtcomstmt .  (95)

	ELSE  shift 251
	.  reduce 95


243: shift-reduce conflict (shift 252, reduce 93) on ELSE
state 243
	ifstmt : IF LBRACESS expr RBRACESS stmtcomstmt . ELSE stmtcomstmt
	ifstmt : IF LBRACESS expr RBRACESS stmtcomstmt .  (93)

	ELSE  shift 252
	.  reduce 93


state 244
	whilestmt : WHILE LBRACESS expr error stmtcomstmt .  (97)

	.  reduce 97


state 245
	whilestmt : WHILE LBRACESS expr RBRACESS stmtcomstmt .  (96)

	.  reduce 96


state 246
	forstmt : FOR LBRACESS SEMI SEMI RBRACESS . stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 163
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 164
	WHILE  shift 165
	FOR  shift 166
	COUT  shift 167
	CIN  shift 168
	RETURN  shift 169
	LBRACE  shift 66
	SEMI  shift 171
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 172
	DELETE  shift 59

	basetypestmt  goto 173
	basetype  goto 174
	expr  goto 175
	stmt  goto 240
	among  goto 14
	cinstmt  goto 177
	ifstmt  goto 178
	whilestmt  goto 179
	coutstmt  goto 180
	valueexpr  goto 61
	returnstmt  goto 181
	forstmt  goto 182
	calexpr  goto 62
	comstmt  goto 241
	stmtcomstmt  goto 253


state 247
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr
	forstmt : FOR LBRACESS SEMI SEMI expr . RBRACESS stmtcomstmt

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	RBRACESS  shift 254
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111


state 248
	forstmt : FOR LBRACESS SEMI expr SEMI . RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS SEMI expr SEMI . expr RBRACESS stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	RBRACESS  shift 255
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 256
	valueexpr  goto 61
	calexpr  goto 62


state 249
	forstmt : FOR LBRACESS expr SEMI SEMI . expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr SEMI SEMI . RBRACESS stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	RBRACESS  shift 257
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 258
	valueexpr  goto 61
	calexpr  goto 62


state 250
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr
	forstmt : FOR LBRACESS expr SEMI expr . SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr SEMI expr . SEMI RBRACESS stmtcomstmt

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	SEMI  shift 259
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111


state 251
	ifstmt : IF LBRACESS expr error stmtcomstmt ELSE . stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 163
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 164
	WHILE  shift 165
	FOR  shift 166
	COUT  shift 167
	CIN  shift 168
	RETURN  shift 169
	LBRACE  shift 66
	SEMI  shift 171
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 172
	DELETE  shift 59

	basetypestmt  goto 173
	basetype  goto 174
	expr  goto 175
	stmt  goto 240
	among  goto 14
	cinstmt  goto 177
	ifstmt  goto 178
	whilestmt  goto 179
	coutstmt  goto 180
	valueexpr  goto 61
	returnstmt  goto 181
	forstmt  goto 182
	calexpr  goto 62
	comstmt  goto 241
	stmtcomstmt  goto 260


state 252
	ifstmt : IF LBRACESS expr RBRACESS stmtcomstmt ELSE . stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 163
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 164
	WHILE  shift 165
	FOR  shift 166
	COUT  shift 167
	CIN  shift 168
	RETURN  shift 169
	LBRACE  shift 66
	SEMI  shift 171
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 172
	DELETE  shift 59

	basetypestmt  goto 173
	basetype  goto 174
	expr  goto 175
	stmt  goto 240
	among  goto 14
	cinstmt  goto 177
	ifstmt  goto 178
	whilestmt  goto 179
	coutstmt  goto 180
	valueexpr  goto 61
	returnstmt  goto 181
	forstmt  goto 182
	calexpr  goto 62
	comstmt  goto 241
	stmtcomstmt  goto 261


state 253
	forstmt : FOR LBRACESS SEMI SEMI RBRACESS stmtcomstmt .  (105)

	.  reduce 105


state 254
	forstmt : FOR LBRACESS SEMI SEMI expr RBRACESS . stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 163
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 164
	WHILE  shift 165
	FOR  shift 166
	COUT  shift 167
	CIN  shift 168
	RETURN  shift 169
	LBRACE  shift 66
	SEMI  shift 171
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 172
	DELETE  shift 59

	basetypestmt  goto 173
	basetype  goto 174
	expr  goto 175
	stmt  goto 240
	among  goto 14
	cinstmt  goto 177
	ifstmt  goto 178
	whilestmt  goto 179
	coutstmt  goto 180
	valueexpr  goto 61
	returnstmt  goto 181
	forstmt  goto 182
	calexpr  goto 62
	comstmt  goto 241
	stmtcomstmt  goto 262


state 255
	forstmt : FOR LBRACESS SEMI expr SEMI RBRACESS . stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 163
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 164
	WHILE  shift 165
	FOR  shift 166
	COUT  shift 167
	CIN  shift 168
	RETURN  shift 169
	LBRACE  shift 66
	SEMI  shift 171
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 172
	DELETE  shift 59

	basetypestmt  goto 173
	basetype  goto 174
	expr  goto 175
	stmt  goto 240
	among  goto 14
	cinstmt  goto 177
	ifstmt  goto 178
	whilestmt  goto 179
	coutstmt  goto 180
	valueexpr  goto 61
	returnstmt  goto 181
	forstmt  goto 182
	calexpr  goto 62
	comstmt  goto 241
	stmtcomstmt  goto 263


state 256
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr
	forstmt : FOR LBRACESS SEMI expr SEMI expr . RBRACESS stmtcomstmt

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	RBRACESS  shift 264
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111


state 257
	forstmt : FOR LBRACESS expr SEMI SEMI RBRACESS . stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 163
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 164
	WHILE  shift 165
	FOR  shift 166
	COUT  shift 167
	CIN  shift 168
	RETURN  shift 169
	LBRACE  shift 66
	SEMI  shift 171
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 172
	DELETE  shift 59

	basetypestmt  goto 173
	basetype  goto 174
	expr  goto 175
	stmt  goto 240
	among  goto 14
	cinstmt  goto 177
	ifstmt  goto 178
	whilestmt  goto 179
	coutstmt  goto 180
	valueexpr  goto 61
	returnstmt  goto 181
	forstmt  goto 182
	calexpr  goto 62
	comstmt  goto 241
	stmtcomstmt  goto 265


state 258
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr
	forstmt : FOR LBRACESS expr SEMI SEMI expr . RBRACESS stmtcomstmt

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	RBRACESS  shift 266
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111


state 259
	forstmt : FOR LBRACESS expr SEMI expr SEMI . expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr SEMI expr SEMI . RBRACESS stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 54
	RBRACESS  shift 267
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 58
	DELETE  shift 59

	expr  goto 268
	valueexpr  goto 61
	calexpr  goto 62


state 260
	ifstmt : IF LBRACESS expr error stmtcomstmt ELSE stmtcomstmt .  (94)

	.  reduce 94


state 261
	ifstmt : IF LBRACESS expr RBRACESS stmtcomstmt ELSE stmtcomstmt .  (92)

	.  reduce 92


state 262
	forstmt : FOR LBRACESS SEMI SEMI expr RBRACESS stmtcomstmt .  (104)

	.  reduce 104


state 263
	forstmt : FOR LBRACESS SEMI expr SEMI RBRACESS stmtcomstmt .  (103)

	.  reduce 103


state 264
	forstmt : FOR LBRACESS SEMI expr SEMI expr RBRACESS . stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 163
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 164
	WHILE  shift 165
	FOR  shift 166
	COUT  shift 167
	CIN  shift 168
	RETURN  shift 169
	LBRACE  shift 66
	SEMI  shift 171
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 172
	DELETE  shift 59

	basetypestmt  goto 173
	basetype  goto 174
	expr  goto 175
	stmt  goto 240
	among  goto 14
	cinstmt  goto 177
	ifstmt  goto 178
	whilestmt  goto 179
	coutstmt  goto 180
	valueexpr  goto 61
	returnstmt  goto 181
	forstmt  goto 182
	calexpr  goto 62
	comstmt  goto 241
	stmtcomstmt  goto 269


state 265
	forstmt : FOR LBRACESS expr SEMI SEMI RBRACESS stmtcomstmt .  (102)

	.  reduce 102


state 266
	forstmt : FOR LBRACESS expr SEMI SEMI expr RBRACESS . stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 163
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 164
	WHILE  shift 165
	FOR  shift 166
	COUT  shift 167
	CIN  shift 168
	RETURN  shift 169
	LBRACE  shift 66
	SEMI  shift 171
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 172
	DELETE  shift 59

	basetypestmt  goto 173
	basetype  goto 174
	expr  goto 175
	stmt  goto 240
	among  goto 14
	cinstmt  goto 177
	ifstmt  goto 178
	whilestmt  goto 179
	coutstmt  goto 180
	valueexpr  goto 61
	returnstmt  goto 181
	forstmt  goto 182
	calexpr  goto 62
	comstmt  goto 241
	stmtcomstmt  goto 270


state 267
	forstmt : FOR LBRACESS expr SEMI expr SEMI RBRACESS . stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 163
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 164
	WHILE  shift 165
	FOR  shift 166
	COUT  shift 167
	CIN  shift 168
	RETURN  shift 169
	LBRACE  shift 66
	SEMI  shift 171
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 172
	DELETE  shift 59

	basetypestmt  goto 173
	basetype  goto 174
	expr  goto 175
	stmt  goto 240
	among  goto 14
	cinstmt  goto 177
	ifstmt  goto 178
	whilestmt  goto 179
	coutstmt  goto 180
	valueexpr  goto 61
	returnstmt  goto 181
	forstmt  goto 182
	calexpr  goto 62
	comstmt  goto 241
	stmtcomstmt  goto 271


state 268
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . BTCAND expr
	calexpr : expr . BTCOR expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . LBRACES expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . EQ expr
	forstmt : FOR LBRACESS expr SEMI expr SEMI expr . RBRACESS stmtcomstmt

	ALGCADD  shift 93
	ALGCMINUS  shift 94
	ALGCMUL  shift 95
	ALGCDIV  shift 96
	ALGCMOD  shift 97
	RBRACESS  shift 272
	EQ  shift 98
	LBRACES  shift 99
	RBRACES  shift 100
	LGCCEQ  shift 101
	LGCCLESSEQ  shift 102
	LGCCMOREEQ  shift 103
	LGCCNEQ  shift 104
	LGCCAND  shift 105
	LGCCOR  shift 106
	BTCYH  shift 107
	BTCOR  shift 108
	BTCAND  shift 109
	BTCLEFT  shift 110
	BTCRIGHT  shift 111


state 269
	forstmt : FOR LBRACESS SEMI expr SEMI expr RBRACESS stmtcomstmt .  (101)

	.  reduce 101


state 270
	forstmt : FOR LBRACESS expr SEMI SEMI expr RBRACESS stmtcomstmt .  (100)

	.  reduce 100


state 271
	forstmt : FOR LBRACESS expr SEMI expr SEMI RBRACESS stmtcomstmt .  (99)

	.  reduce 99


state 272
	forstmt : FOR LBRACESS expr SEMI expr SEMI expr RBRACESS . stmtcomstmt

	ALGCMINUS  shift 45
	ALGCMUL  shift 46
	ALGCTADD  shift 47
	ALGCTMINUS  shift 48
	NUMBERD  shift 49
	DIGIT  shift 50
	STRING  shift 51
	ONECHAR  shift 52
	FLOATD  shift 53
	LBRACESS  shift 163
	INT  shift 36
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 164
	WHILE  shift 165
	FOR  shift 166
	COUT  shift 167
	CIN  shift 168
	RETURN  shift 169
	LBRACE  shift 66
	SEMI  shift 171
	LGCCN  shift 55
	BTCAND  shift 56
	BTCN  shift 57
	ID  shift 172
	DELETE  shift 59

	basetypestmt  goto 173
	basetype  goto 174
	expr  goto 175
	stmt  goto 240
	among  goto 14
	cinstmt  goto 177
	ifstmt  goto 178
	whilestmt  goto 179
	coutstmt  goto 180
	valueexpr  goto 61
	returnstmt  goto 181
	forstmt  goto 182
	calexpr  goto 62
	comstmt  goto 241
	stmtcomstmt  goto 273


state 273
	forstmt : FOR LBRACESS expr SEMI expr SEMI expr RBRACESS stmtcomstmt .  (98)

	.  reduce 98


##############################################################################
# Summary
##############################################################################

State 172 contains 1 reduce-reduce conflict(s)
State 242 contains 1 shift-reduce conflict(s)
State 243 contains 1 shift-reduce conflict(s)


66 token(s), 30 nonterminal(s)
129 grammar rule(s), 274 state(s)


##############################################################################
# End of File
##############################################################################
