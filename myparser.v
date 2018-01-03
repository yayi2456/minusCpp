#############################################################################
#                     U N R E G I S T E R E D   C O P Y
# 
# You are on day 110 of your 30 day trial period.
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
# Date: 01/04/18
# Time: 02:52:38
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

   26  valueexpr : ID
   27            | valueexpr CLASSMC valueexpr
   28            | valueexpr POINT valueexpr
   29            | ALGCMUL valueexpr
   30            | valueexpr LBRACEM expr RBRACEM
   31            | ALGCTADD valueexpr
   32            | ALGCTMINUS valueexpr
   33            | LBRACESS valueexpr RBRACESS

   34  calexpr : expr ALGCADD expr
   35          | expr ALGCMINUS expr
   36          | expr ALGCMUL expr
   37          | expr ALGCDIV expr
   38          | expr ALGCMOD expr
   39          | LBRACESS calexpr RBRACESS
   40          | ALGCMINUS expr
   41          | NUMBERD
   42          | DIGIT
   43          | FLOATD
   44          | STRING
   45          | ONECHAR
   46          | valueexpr ALGCTADD
   47          | valueexpr ALGCTMINUS
   48          | BTCN expr
   49          | expr BTCRIGHT expr
   50          | expr BTCLEFT expr
   51          | expr BTCAND expr
   52          | expr BTCOR expr
   53          | expr BTCYH expr
   54          | ID LBRACESS exprlist RBRACESS
   55          | valueexpr CLASSMC ID LBRACESS exprlist RBRACESS
   56          | valueexpr POINT ID LBRACESS exprlist RBRACESS
   57          | ID LBRACESS RBRACESS
   58          | valueexpr CLASSMC ID LBRACESS RBRACESS
   59          | valueexpr POINT ID LBRACESS RBRACESS
   60          | LGCCN expr
   61          | expr LGCCMOREEQ expr
   62          | expr LGCCLESSEQ expr
   63          | expr LBRACES expr
   64          | expr RBRACES expr
   65          | expr LGCCEQ expr
   66          | expr LGCCNEQ expr
   67          | expr LGCCAND expr
   68          | expr LGCCOR expr
   69          | expr EQ expr
   70          | BTCAND expr

   71  returnstmt : RETURN expr SEMI

   72  stmt : expr SEMI
   73       | LBRACESS error SEMI
   74       | basetypestmt
   75       | ifstmt
   76       | whilestmt
   77       | forstmt
   78       | cinstmt
   79       | coutstmt
   80       | returnstmt
   81       | SEMI

   82  cstmtlist : cstmtlist comstmt
   83            | cstmtlist stmt
   84            | comstmt
   85            | stmt

   86  comstmt : LBRACE midum cstmtlist RBRACE
   87          | LBRACE midum RBRACE

   88  midum :

   89  stmtcomstmt : stmt
   90              | comstmt

   91  ifstmt : IF LBRACESS expr RBRACESS stmtcomstmt ELSE stmtcomstmt
   92         | IF LBRACESS expr RBRACESS stmtcomstmt
   93         | IF LBRACESS expr error stmtcomstmt ELSE stmtcomstmt
   94         | IF LBRACESS expr error stmtcomstmt

   95  whilestmt : WHILE LBRACESS expr RBRACESS stmtcomstmt
   96            | WHILE LBRACESS expr error stmtcomstmt

   97  forstmt : FOR LBRACESS expr SEMI expr SEMI expr RBRACESS stmtcomstmt
   98          | FOR LBRACESS expr SEMI expr SEMI RBRACESS stmtcomstmt
   99          | FOR LBRACESS expr SEMI SEMI expr RBRACESS stmtcomstmt
  100          | FOR LBRACESS SEMI expr SEMI expr RBRACESS stmtcomstmt
  101          | FOR LBRACESS expr SEMI SEMI RBRACESS stmtcomstmt
  102          | FOR LBRACESS SEMI expr SEMI RBRACESS stmtcomstmt
  103          | FOR LBRACESS SEMI SEMI expr RBRACESS stmtcomstmt
  104          | FOR LBRACESS SEMI SEMI RBRACESS stmtcomstmt

  105  coutlist : coutlist BTCLEFT expr
  106           | BTCLEFT expr

  107  coutstmt : COUT coutlist SEMI

  108  cinlist : cinlist BTCRIGHT valueexpr
  109          | BTCRIGHT valueexpr

  110  cinstmt : CIN cinlist SEMI

  111  typep : basetype
  112        | basetype ALGCMUL

  113  typeidlist : typeidlist COMMA typep ID
  114             | typeidlist COMMA typep ID LBRACEM NUMBERD RBRACEM
  115             | typep ID
  116             | typep ID LBRACEM NUMBERD RBRACEM

  117  funcdef : basetype ID LBRACESS typeidlist RBRACESS comstmt
  118          | basetype ALGCMUL ID LBRACESS typeidlist RBRACESS comstmt
  119          | basetype ID LBRACESS RBRACESS comstmt
  120          | basetype ALGCMUL ID LBRACESS RBRACESS comstmt

  121  funcdefmain : INT MAIN LBRACESS RBRACESS comstmt
  122              | INT MAIN LBRACESS error comstmt

  123  inclass : inclass basetypestmt
  124          | inclass funcdef
  125          | basetypestmt
  126          | funcdef

  127  classdef : class ID LBRACE inclass RBRACE SEMI
  128           | class ID LBRACE inclass RBRACE error

  129  class : CLASS


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

	class  goto 7
	basetype  goto 8
	funcdef  goto 9
	start  goto 10
	startinfo  goto 11
	funcdefmain  goto 12
	classdef  goto 13
	basetypestmt  goto 14
	among  goto 15


state 1
	basetype : INT .  (7)
	funcdefmain : INT . MAIN LBRACESS RBRACESS comstmt
	funcdefmain : INT . MAIN LBRACESS error comstmt

	MAIN  shift 16
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
	class : CLASS .  (129)

	.  reduce 129


state 6
	among : ID .  (23)

	.  reduce 23


state 7
	classdef : class . ID LBRACE inclass RBRACE SEMI
	classdef : class . ID LBRACE inclass RBRACE error

	ID  shift 17


state 8
	basetypestmt : basetype . idlistwithvar SEMI
	funcdef : basetype . ID LBRACESS RBRACESS comstmt
	funcdef : basetype . ID LBRACESS typeidlist RBRACESS comstmt
	funcdef : basetype . ALGCMUL ID LBRACESS RBRACESS comstmt
	funcdef : basetype . ALGCMUL ID LBRACESS typeidlist RBRACESS comstmt

	ALGCMUL  shift 18
	ID  shift 19

	idlistwithvar  goto 20


state 9
	startinfo : funcdef .  (5)

	.  reduce 5


state 10
	$accept : start . $end  (0)
	start : start . startinfo

	$end  accept
	INT  shift 1
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	CLASS  shift 5
	ID  shift 6

	class  goto 7
	basetype  goto 8
	funcdef  goto 9
	startinfo  goto 21
	funcdefmain  goto 12
	classdef  goto 13
	basetypestmt  goto 14
	among  goto 15


state 11
	start : startinfo .  (1)

	.  reduce 1


state 12
	startinfo : funcdefmain .  (6)

	.  reduce 6


state 13
	startinfo : classdef .  (3)

	.  reduce 3


state 14
	startinfo : basetypestmt .  (4)

	.  reduce 4


state 15
	basetypestmt : among . idlistwithvar SEMI

	ALGCMUL  shift 22
	ID  shift 23

	idlistwithvar  goto 24


state 16
	funcdefmain : INT MAIN . LBRACESS RBRACESS comstmt
	funcdefmain : INT MAIN . LBRACESS error comstmt

	LBRACESS  shift 25


state 17
	classdef : class ID . LBRACE inclass RBRACE SEMI
	classdef : class ID . LBRACE inclass RBRACE error

	LBRACE  shift 26


state 18
	idlistwithvar : ALGCMUL . ID
	funcdef : basetype ALGCMUL . ID LBRACESS RBRACESS comstmt
	funcdef : basetype ALGCMUL . ID LBRACESS typeidlist RBRACESS comstmt

	ID  shift 27


state 19
	idlistwithvar : ID .  (12)
	idlistwithvar : ID . EQ expr
	idlistwithvar : ID . LBRACEM NUMBERD RBRACEM
	funcdef : basetype ID . LBRACESS RBRACESS comstmt
	funcdef : basetype ID . LBRACESS typeidlist RBRACESS comstmt

	LBRACESS  shift 28
	EQ  shift 29
	LBRACEM  shift 30
	.  reduce 12


state 20
	idlistwithvar : idlistwithvar . COMMA ID
	idlistwithvar : idlistwithvar . COMMA ID EQ expr
	idlistwithvar : idlistwithvar . COMMA ALGCMUL ID
	idlistwithvar : idlistwithvar . COMMA ID LBRACEM NUMBERD RBRACEM
	basetypestmt : basetype idlistwithvar . SEMI

	SEMI  shift 31
	COMMA  shift 32


state 21
	start : start startinfo .  (2)

	.  reduce 2


state 22
	idlistwithvar : ALGCMUL . ID

	ID  shift 33


state 23
	idlistwithvar : ID .  (12)
	idlistwithvar : ID . EQ expr
	idlistwithvar : ID . LBRACEM NUMBERD RBRACEM

	EQ  shift 29
	LBRACEM  shift 30
	.  reduce 12


state 24
	idlistwithvar : idlistwithvar . COMMA ID
	idlistwithvar : idlistwithvar . COMMA ID EQ expr
	idlistwithvar : idlistwithvar . COMMA ALGCMUL ID
	idlistwithvar : idlistwithvar . COMMA ID LBRACEM NUMBERD RBRACEM
	basetypestmt : among idlistwithvar . SEMI

	SEMI  shift 34
	COMMA  shift 32


state 25
	funcdefmain : INT MAIN LBRACESS . RBRACESS comstmt
	funcdefmain : INT MAIN LBRACESS . error comstmt

	error  shift 35
	RBRACESS  shift 36


state 26
	classdef : class ID LBRACE . inclass RBRACE SEMI
	classdef : class ID LBRACE . inclass RBRACE error

	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	ID  shift 6

	inclass  goto 38
	basetype  goto 8
	funcdef  goto 39
	basetypestmt  goto 40
	among  goto 15


state 27
	idlistwithvar : ALGCMUL ID .  (17)
	funcdef : basetype ALGCMUL ID . LBRACESS RBRACESS comstmt
	funcdef : basetype ALGCMUL ID . LBRACESS typeidlist RBRACESS comstmt

	LBRACESS  shift 41
	.  reduce 17


state 28
	funcdef : basetype ID LBRACESS . RBRACESS comstmt
	funcdef : basetype ID LBRACESS . typeidlist RBRACESS comstmt

	RBRACESS  shift 42
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4

	typeidlist  goto 43
	typep  goto 44
	basetype  goto 45


state 29
	idlistwithvar : ID EQ . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 60
	valueexpr  goto 61
	calexpr  goto 62


state 30
	idlistwithvar : ID LBRACEM . NUMBERD RBRACEM

	NUMBERD  shift 63


state 31
	basetypestmt : basetype idlistwithvar SEMI .  (21)

	.  reduce 21


state 32
	idlistwithvar : idlistwithvar COMMA . ID
	idlistwithvar : idlistwithvar COMMA . ID EQ expr
	idlistwithvar : idlistwithvar COMMA . ALGCMUL ID
	idlistwithvar : idlistwithvar COMMA . ID LBRACEM NUMBERD RBRACEM

	ALGCMUL  shift 64
	ID  shift 65


state 33
	idlistwithvar : ALGCMUL ID .  (17)

	.  reduce 17


state 34
	basetypestmt : among idlistwithvar SEMI .  (22)

	.  reduce 22


state 35
	funcdefmain : INT MAIN LBRACESS error . comstmt

	LBRACE  shift 66

	comstmt  goto 67


state 36
	funcdefmain : INT MAIN LBRACESS RBRACESS . comstmt

	LBRACE  shift 66

	comstmt  goto 68


state 37
	basetype : INT .  (7)

	.  reduce 7


state 38
	classdef : class ID LBRACE inclass . RBRACE SEMI
	inclass : inclass . basetypestmt
	inclass : inclass . funcdef
	classdef : class ID LBRACE inclass . RBRACE error

	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	RBRACE  shift 69
	ID  shift 6

	basetype  goto 8
	funcdef  goto 70
	basetypestmt  goto 71
	among  goto 15


state 39
	inclass : funcdef .  (126)

	.  reduce 126


state 40
	inclass : basetypestmt .  (125)

	.  reduce 125


state 41
	funcdef : basetype ALGCMUL ID LBRACESS . RBRACESS comstmt
	funcdef : basetype ALGCMUL ID LBRACESS . typeidlist RBRACESS comstmt

	RBRACESS  shift 72
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4

	typeidlist  goto 73
	typep  goto 44
	basetype  goto 45


state 42
	funcdef : basetype ID LBRACESS RBRACESS . comstmt

	LBRACE  shift 66

	comstmt  goto 74


state 43
	typeidlist : typeidlist . COMMA typep ID
	funcdef : basetype ID LBRACESS typeidlist . RBRACESS comstmt
	typeidlist : typeidlist . COMMA typep ID LBRACEM NUMBERD RBRACEM

	RBRACESS  shift 75
	COMMA  shift 76


state 44
	typeidlist : typep . ID LBRACEM NUMBERD RBRACEM
	typeidlist : typep . ID

	ID  shift 77


state 45
	typep : basetype . ALGCMUL
	typep : basetype .  (111)

	ALGCMUL  shift 78
	.  reduce 111


state 46
	calexpr : ALGCMINUS . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 79
	valueexpr  goto 61
	calexpr  goto 62


state 47
	valueexpr : ALGCMUL . valueexpr

	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 82


state 48
	valueexpr : ALGCTADD . valueexpr

	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 83


state 49
	valueexpr : ALGCTMINUS . valueexpr

	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 84


state 50
	calexpr : NUMBERD .  (41)

	.  reduce 41


state 51
	calexpr : DIGIT .  (42)

	.  reduce 42


state 52
	calexpr : STRING .  (44)

	.  reduce 44


state 53
	calexpr : ONECHAR .  (45)

	.  reduce 45


state 54
	calexpr : FLOATD .  (43)

	.  reduce 43


state 55
	valueexpr : LBRACESS . valueexpr RBRACESS
	calexpr : LBRACESS . calexpr RBRACESS

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 85
	valueexpr  goto 86
	calexpr  goto 87


state 56
	calexpr : LGCCN . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 88
	valueexpr  goto 61
	calexpr  goto 62


state 57
	calexpr : BTCAND . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 89
	valueexpr  goto 61
	calexpr  goto 62


state 58
	calexpr : BTCN . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 90
	valueexpr  goto 61
	calexpr  goto 62


state 59
	valueexpr : ID .  (26)
	calexpr : ID . LBRACESS RBRACESS
	calexpr : ID . LBRACESS exprlist RBRACESS

	LBRACESS  shift 91
	.  reduce 26


state 60
	idlistwithvar : ID EQ expr .  (14)
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110
	.  reduce 14


state 61
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr . POINT valueexpr
	expr : valueexpr .  (24)
	valueexpr : valueexpr . LBRACEM expr RBRACEM
	calexpr : valueexpr . CLASSMC ID LBRACESS exprlist RBRACESS
	calexpr : valueexpr . CLASSMC ID LBRACESS RBRACESS
	calexpr : valueexpr . ALGCTADD
	calexpr : valueexpr . POINT ID LBRACESS RBRACESS
	calexpr : valueexpr . POINT ID LBRACESS exprlist RBRACESS
	calexpr : valueexpr . ALGCTMINUS

	ALGCTADD  shift 111
	ALGCTMINUS  shift 112
	LBRACEM  shift 113
	POINT  shift 114
	CLASSMC  shift 115
	.  reduce 24


state 62
	expr : calexpr .  (25)

	.  reduce 25


state 63
	idlistwithvar : ID LBRACEM NUMBERD . RBRACEM

	RBRACEM  shift 116


state 64
	idlistwithvar : idlistwithvar COMMA ALGCMUL . ID

	ID  shift 117


state 65
	idlistwithvar : idlistwithvar COMMA ID .  (11)
	idlistwithvar : idlistwithvar COMMA ID . EQ expr
	idlistwithvar : idlistwithvar COMMA ID . LBRACEM NUMBERD RBRACEM

	EQ  shift 118
	LBRACEM  shift 119
	.  reduce 11


state 66
	comstmt : LBRACE . midum cstmtlist RBRACE
	comstmt : LBRACE . midum RBRACE
	midum : .  (88)

	.  reduce 88

	midum  goto 120


state 67
	funcdefmain : INT MAIN LBRACESS error comstmt .  (122)

	.  reduce 122


state 68
	funcdefmain : INT MAIN LBRACESS RBRACESS comstmt .  (121)

	.  reduce 121


state 69
	classdef : class ID LBRACE inclass RBRACE . SEMI
	classdef : class ID LBRACE inclass RBRACE . error

	error  shift 121
	SEMI  shift 122


state 70
	inclass : inclass funcdef .  (124)

	.  reduce 124


state 71
	inclass : inclass basetypestmt .  (123)

	.  reduce 123


state 72
	funcdef : basetype ALGCMUL ID LBRACESS RBRACESS . comstmt

	LBRACE  shift 66

	comstmt  goto 123


state 73
	typeidlist : typeidlist . COMMA typep ID
	funcdef : basetype ALGCMUL ID LBRACESS typeidlist . RBRACESS comstmt
	typeidlist : typeidlist . COMMA typep ID LBRACEM NUMBERD RBRACEM

	RBRACESS  shift 124
	COMMA  shift 76


state 74
	funcdef : basetype ID LBRACESS RBRACESS comstmt .  (119)

	.  reduce 119


state 75
	funcdef : basetype ID LBRACESS typeidlist RBRACESS . comstmt

	LBRACE  shift 66

	comstmt  goto 125


state 76
	typeidlist : typeidlist COMMA . typep ID
	typeidlist : typeidlist COMMA . typep ID LBRACEM NUMBERD RBRACEM

	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4

	typep  goto 126
	basetype  goto 45


state 77
	typeidlist : typep ID . LBRACEM NUMBERD RBRACEM
	typeidlist : typep ID .  (115)

	LBRACEM  shift 127
	.  reduce 115


state 78
	typep : basetype ALGCMUL .  (112)

	.  reduce 112


state 79
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : ALGCMINUS expr .  (40)
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	.  reduce 40


state 80
	valueexpr : LBRACESS . valueexpr RBRACESS

	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 128


state 81
	valueexpr : ID .  (26)

	.  reduce 26


state 82
	valueexpr : ALGCMUL valueexpr .  (29)
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr . POINT valueexpr
	valueexpr : valueexpr . LBRACEM expr RBRACEM

	LBRACEM  shift 113
	POINT  shift 129
	CLASSMC  shift 130
	.  reduce 29


state 83
	valueexpr : ALGCTADD valueexpr .  (31)
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr . POINT valueexpr
	valueexpr : valueexpr . LBRACEM expr RBRACEM

	LBRACEM  shift 113
	POINT  shift 129
	CLASSMC  shift 130
	.  reduce 31


state 84
	valueexpr : ALGCTMINUS valueexpr .  (32)
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr . POINT valueexpr
	valueexpr : valueexpr . LBRACEM expr RBRACEM

	LBRACEM  shift 113
	POINT  shift 129
	CLASSMC  shift 130
	.  reduce 32


state 85
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110


state 86
	valueexpr : LBRACESS valueexpr . RBRACESS
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr . POINT valueexpr
	expr : valueexpr .  (24)
	valueexpr : valueexpr . LBRACEM expr RBRACEM
	calexpr : valueexpr . CLASSMC ID LBRACESS exprlist RBRACESS
	calexpr : valueexpr . CLASSMC ID LBRACESS RBRACESS
	calexpr : valueexpr . ALGCTADD
	calexpr : valueexpr . POINT ID LBRACESS RBRACESS
	calexpr : valueexpr . POINT ID LBRACESS exprlist RBRACESS
	calexpr : valueexpr . ALGCTMINUS

	ALGCTADD  shift 111
	ALGCTMINUS  shift 112
	RBRACESS  shift 131
	LBRACEM  shift 113
	POINT  shift 114
	CLASSMC  shift 115
	.  reduce 24


state 87
	expr : calexpr .  (25)
	calexpr : LBRACESS calexpr . RBRACESS

	RBRACESS  shift 132
	.  reduce 25


state 88
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : LGCCN expr .  (60)
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	.  reduce 60


state 89
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : BTCAND expr .  (70)
	calexpr : expr . EQ expr

	.  reduce 70


state 90
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : BTCN expr .  (48)
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	.  reduce 48


state 91
	calexpr : ID LBRACESS . RBRACESS
	calexpr : ID LBRACESS . exprlist RBRACESS

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	RBRACESS  shift 133
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	exprlist  goto 134
	expr  goto 135
	valueexpr  goto 61
	calexpr  goto 62


state 92
	calexpr : expr ALGCADD . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 136
	valueexpr  goto 61
	calexpr  goto 62


state 93
	calexpr : expr ALGCMINUS . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 137
	valueexpr  goto 61
	calexpr  goto 62


state 94
	calexpr : expr ALGCMUL . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 138
	valueexpr  goto 61
	calexpr  goto 62


state 95
	calexpr : expr ALGCDIV . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 139
	valueexpr  goto 61
	calexpr  goto 62


state 96
	calexpr : expr ALGCMOD . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 140
	valueexpr  goto 61
	calexpr  goto 62


state 97
	calexpr : expr EQ . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 141
	valueexpr  goto 61
	calexpr  goto 62


state 98
	calexpr : expr LBRACES . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 142
	valueexpr  goto 61
	calexpr  goto 62


state 99
	calexpr : expr RBRACES . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 143
	valueexpr  goto 61
	calexpr  goto 62


state 100
	calexpr : expr LGCCEQ . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 144
	valueexpr  goto 61
	calexpr  goto 62


state 101
	calexpr : expr LGCCLESSEQ . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 145
	valueexpr  goto 61
	calexpr  goto 62


state 102
	calexpr : expr LGCCMOREEQ . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 146
	valueexpr  goto 61
	calexpr  goto 62


state 103
	calexpr : expr LGCCNEQ . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 147
	valueexpr  goto 61
	calexpr  goto 62


state 104
	calexpr : expr LGCCAND . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 148
	valueexpr  goto 61
	calexpr  goto 62


state 105
	calexpr : expr LGCCOR . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 149
	valueexpr  goto 61
	calexpr  goto 62


state 106
	calexpr : expr BTCYH . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 150
	valueexpr  goto 61
	calexpr  goto 62


state 107
	calexpr : expr BTCOR . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 151
	valueexpr  goto 61
	calexpr  goto 62


state 108
	calexpr : expr BTCAND . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 152
	valueexpr  goto 61
	calexpr  goto 62


state 109
	calexpr : expr BTCLEFT . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 153
	valueexpr  goto 61
	calexpr  goto 62


state 110
	calexpr : expr BTCRIGHT . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 154
	valueexpr  goto 61
	calexpr  goto 62


state 111
	calexpr : valueexpr ALGCTADD .  (46)

	.  reduce 46


state 112
	calexpr : valueexpr ALGCTMINUS .  (47)

	.  reduce 47


state 113
	valueexpr : valueexpr LBRACEM . expr RBRACEM

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 155
	valueexpr  goto 61
	calexpr  goto 62


state 114
	valueexpr : valueexpr POINT . valueexpr
	calexpr : valueexpr POINT . ID LBRACESS RBRACESS
	calexpr : valueexpr POINT . ID LBRACESS exprlist RBRACESS

	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	LBRACESS  shift 80
	ID  shift 156

	valueexpr  goto 157


state 115
	valueexpr : valueexpr CLASSMC . valueexpr
	calexpr : valueexpr CLASSMC . ID LBRACESS exprlist RBRACESS
	calexpr : valueexpr CLASSMC . ID LBRACESS RBRACESS

	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	LBRACESS  shift 80
	ID  shift 158

	valueexpr  goto 159


state 116
	idlistwithvar : ID LBRACEM NUMBERD RBRACEM .  (18)

	.  reduce 18


state 117
	idlistwithvar : idlistwithvar COMMA ALGCMUL ID .  (15)

	.  reduce 15


state 118
	idlistwithvar : idlistwithvar COMMA ID EQ . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 160
	valueexpr  goto 61
	calexpr  goto 62


state 119
	idlistwithvar : idlistwithvar COMMA ID LBRACEM . NUMBERD RBRACEM

	NUMBERD  shift 161


state 120
	comstmt : LBRACE midum . cstmtlist RBRACE
	comstmt : LBRACE midum . RBRACE

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 162
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 163
	WHILE  shift 164
	FOR  shift 165
	COUT  shift 166
	CIN  shift 167
	RETURN  shift 168
	LBRACE  shift 66
	RBRACE  shift 169
	SEMI  shift 170
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 171

	cstmtlist  goto 172
	comstmt  goto 173
	basetype  goto 174
	expr  goto 175
	basetypestmt  goto 176
	valueexpr  goto 61
	whilestmt  goto 177
	stmt  goto 178
	among  goto 15
	calexpr  goto 62
	returnstmt  goto 179
	ifstmt  goto 180
	cinstmt  goto 181
	coutstmt  goto 182
	forstmt  goto 183


state 121
	classdef : class ID LBRACE inclass RBRACE error .  (128)

	.  reduce 128


state 122
	classdef : class ID LBRACE inclass RBRACE SEMI .  (127)

	.  reduce 127


state 123
	funcdef : basetype ALGCMUL ID LBRACESS RBRACESS comstmt .  (120)

	.  reduce 120


state 124
	funcdef : basetype ALGCMUL ID LBRACESS typeidlist RBRACESS . comstmt

	LBRACE  shift 66

	comstmt  goto 184


state 125
	funcdef : basetype ID LBRACESS typeidlist RBRACESS comstmt .  (117)

	.  reduce 117


state 126
	typeidlist : typeidlist COMMA typep . ID
	typeidlist : typeidlist COMMA typep . ID LBRACEM NUMBERD RBRACEM

	ID  shift 185


state 127
	typeidlist : typep ID LBRACEM . NUMBERD RBRACEM

	NUMBERD  shift 186


state 128
	valueexpr : LBRACESS valueexpr . RBRACESS
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr . POINT valueexpr
	valueexpr : valueexpr . LBRACEM expr RBRACEM

	RBRACESS  shift 131
	LBRACEM  shift 113
	POINT  shift 129
	CLASSMC  shift 130


state 129
	valueexpr : valueexpr POINT . valueexpr

	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 157


state 130
	valueexpr : valueexpr CLASSMC . valueexpr

	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 159


state 131
	valueexpr : LBRACESS valueexpr RBRACESS .  (33)

	.  reduce 33


state 132
	calexpr : LBRACESS calexpr RBRACESS .  (39)

	.  reduce 39


state 133
	calexpr : ID LBRACESS RBRACESS .  (57)

	.  reduce 57


state 134
	exprlist : exprlist . COMMA expr
	calexpr : ID LBRACESS exprlist . RBRACESS

	RBRACESS  shift 187
	COMMA  shift 188


state 135
	exprlist : expr .  (20)
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110
	.  reduce 20


state 136
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr ALGCADD expr .  (34)
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	.  reduce 34


state 137
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr ALGCMINUS expr .  (35)
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	.  reduce 35


state 138
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr ALGCMUL expr .  (36)
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	.  reduce 36


state 139
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr ALGCDIV expr .  (37)
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	.  reduce 37


state 140
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr ALGCMOD expr .  (38)
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	.  reduce 38


state 141
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr EQ expr .  (69)
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110
	.  reduce 69


state 142
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr LBRACES expr .  (63)
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	BTCLEFT  shift 109
	BTCRIGHT  shift 110
	.  reduce 63


state 143
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr RBRACES expr .  (64)
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	BTCLEFT  shift 109
	BTCRIGHT  shift 110
	.  reduce 64


state 144
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr LGCCEQ expr .  (65)
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	BTCLEFT  shift 109
	BTCRIGHT  shift 110
	.  reduce 65


state 145
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr LGCCLESSEQ expr .  (62)
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	BTCLEFT  shift 109
	BTCRIGHT  shift 110
	.  reduce 62


state 146
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr LGCCMOREEQ expr .  (61)
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	BTCLEFT  shift 109
	BTCRIGHT  shift 110
	.  reduce 61


state 147
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr LGCCNEQ expr .  (66)
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	BTCLEFT  shift 109
	BTCRIGHT  shift 110
	.  reduce 66


state 148
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr LGCCAND expr .  (67)
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110
	.  reduce 67


state 149
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr LGCCOR expr .  (68)
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110
	.  reduce 68


state 150
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr BTCYH expr .  (53)
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110
	.  reduce 53


state 151
	calexpr : expr BTCOR expr .  (52)
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	BTCYH  shift 106
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110
	.  reduce 52


state 152
	calexpr : expr . BTCOR expr
	calexpr : expr BTCAND expr .  (51)
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	BTCLEFT  shift 109
	BTCRIGHT  shift 110
	.  reduce 51


state 153
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr BTCLEFT expr .  (50)
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	.  reduce 50


state 154
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr BTCRIGHT expr .  (49)
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	.  reduce 49


state 155
	valueexpr : valueexpr LBRACEM expr . RBRACEM
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	EQ  shift 97
	RBRACEM  shift 189
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110


state 156
	valueexpr : ID .  (26)
	calexpr : valueexpr POINT ID . LBRACESS RBRACESS
	calexpr : valueexpr POINT ID . LBRACESS exprlist RBRACESS

	LBRACESS  shift 190
	.  reduce 26


state 157
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr POINT valueexpr .  (28)
	valueexpr : valueexpr . POINT valueexpr
	valueexpr : valueexpr . LBRACEM expr RBRACEM

	LBRACEM  shift 113
	POINT  shift 129
	CLASSMC  shift 130
	.  reduce 28


state 158
	valueexpr : ID .  (26)
	calexpr : valueexpr CLASSMC ID . LBRACESS exprlist RBRACESS
	calexpr : valueexpr CLASSMC ID . LBRACESS RBRACESS

	LBRACESS  shift 191
	.  reduce 26


state 159
	valueexpr : valueexpr CLASSMC valueexpr .  (27)
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr . POINT valueexpr
	valueexpr : valueexpr . LBRACEM expr RBRACEM

	LBRACEM  shift 113
	POINT  shift 129
	CLASSMC  shift 130
	.  reduce 27


state 160
	idlistwithvar : idlistwithvar COMMA ID EQ expr .  (13)
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110
	.  reduce 13


state 161
	idlistwithvar : idlistwithvar COMMA ID LBRACEM NUMBERD . RBRACEM

	RBRACEM  shift 192


state 162
	valueexpr : LBRACESS . valueexpr RBRACESS
	calexpr : LBRACESS . calexpr RBRACESS
	stmt : LBRACESS . error SEMI

	error  shift 193
	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 85
	valueexpr  goto 86
	calexpr  goto 87


state 163
	ifstmt : IF . LBRACESS expr RBRACESS stmtcomstmt ELSE stmtcomstmt
	ifstmt : IF . LBRACESS expr error stmtcomstmt ELSE stmtcomstmt
	ifstmt : IF . LBRACESS expr error stmtcomstmt
	ifstmt : IF . LBRACESS expr RBRACESS stmtcomstmt

	LBRACESS  shift 194


state 164
	whilestmt : WHILE . LBRACESS expr RBRACESS stmtcomstmt
	whilestmt : WHILE . LBRACESS expr error stmtcomstmt

	LBRACESS  shift 195


state 165
	forstmt : FOR . LBRACESS expr SEMI expr SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR . LBRACESS expr SEMI expr SEMI RBRACESS stmtcomstmt
	forstmt : FOR . LBRACESS expr SEMI SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR . LBRACESS SEMI expr SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR . LBRACESS SEMI expr SEMI RBRACESS stmtcomstmt
	forstmt : FOR . LBRACESS SEMI SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR . LBRACESS expr SEMI SEMI RBRACESS stmtcomstmt
	forstmt : FOR . LBRACESS SEMI SEMI RBRACESS stmtcomstmt

	LBRACESS  shift 196


state 166
	coutstmt : COUT . coutlist SEMI

	BTCLEFT  shift 197

	coutlist  goto 198


state 167
	cinstmt : CIN . cinlist SEMI

	BTCRIGHT  shift 199

	cinlist  goto 200


state 168
	returnstmt : RETURN . expr SEMI

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 201
	valueexpr  goto 61
	calexpr  goto 62


state 169
	comstmt : LBRACE midum RBRACE .  (87)

	.  reduce 87


state 170
	stmt : SEMI .  (81)

	.  reduce 81


171: reduce-reduce conflict (reduce 23, reduce 26) on ALGCMUL
state 171
	among : ID .  (23)
	valueexpr : ID .  (26)
	calexpr : ID . LBRACESS RBRACESS
	calexpr : ID . LBRACESS exprlist RBRACESS

	LBRACESS  shift 91
	ALGCMUL  reduce 23
	ID  reduce 23
	.  reduce 26


state 172
	comstmt : LBRACE midum cstmtlist . RBRACE
	cstmtlist : cstmtlist . comstmt
	cstmtlist : cstmtlist . stmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 162
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 163
	WHILE  shift 164
	FOR  shift 165
	COUT  shift 166
	CIN  shift 167
	RETURN  shift 168
	LBRACE  shift 66
	RBRACE  shift 202
	SEMI  shift 170
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 171

	comstmt  goto 203
	basetype  goto 174
	expr  goto 175
	basetypestmt  goto 176
	valueexpr  goto 61
	whilestmt  goto 177
	stmt  goto 204
	among  goto 15
	calexpr  goto 62
	returnstmt  goto 179
	ifstmt  goto 180
	cinstmt  goto 181
	coutstmt  goto 182
	forstmt  goto 183


state 173
	cstmtlist : comstmt .  (84)

	.  reduce 84


state 174
	basetypestmt : basetype . idlistwithvar SEMI

	ALGCMUL  shift 22
	ID  shift 23

	idlistwithvar  goto 20


state 175
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	stmt : expr . SEMI
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	SEMI  shift 205
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110


state 176
	stmt : basetypestmt .  (74)

	.  reduce 74


state 177
	stmt : whilestmt .  (76)

	.  reduce 76


state 178
	cstmtlist : stmt .  (85)

	.  reduce 85


state 179
	stmt : returnstmt .  (80)

	.  reduce 80


state 180
	stmt : ifstmt .  (75)

	.  reduce 75


state 181
	stmt : cinstmt .  (78)

	.  reduce 78


state 182
	stmt : coutstmt .  (79)

	.  reduce 79


state 183
	stmt : forstmt .  (77)

	.  reduce 77


state 184
	funcdef : basetype ALGCMUL ID LBRACESS typeidlist RBRACESS comstmt .  (118)

	.  reduce 118


state 185
	typeidlist : typeidlist COMMA typep ID .  (113)
	typeidlist : typeidlist COMMA typep ID . LBRACEM NUMBERD RBRACEM

	LBRACEM  shift 206
	.  reduce 113


state 186
	typeidlist : typep ID LBRACEM NUMBERD . RBRACEM

	RBRACEM  shift 207


state 187
	calexpr : ID LBRACESS exprlist RBRACESS .  (54)

	.  reduce 54


state 188
	exprlist : exprlist COMMA . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 208
	valueexpr  goto 61
	calexpr  goto 62


state 189
	valueexpr : valueexpr LBRACEM expr RBRACEM .  (30)

	.  reduce 30


state 190
	calexpr : valueexpr POINT ID LBRACESS . RBRACESS
	calexpr : valueexpr POINT ID LBRACESS . exprlist RBRACESS

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	RBRACESS  shift 209
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	exprlist  goto 210
	expr  goto 135
	valueexpr  goto 61
	calexpr  goto 62


state 191
	calexpr : valueexpr CLASSMC ID LBRACESS . exprlist RBRACESS
	calexpr : valueexpr CLASSMC ID LBRACESS . RBRACESS

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	RBRACESS  shift 211
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	exprlist  goto 212
	expr  goto 135
	valueexpr  goto 61
	calexpr  goto 62


state 192
	idlistwithvar : idlistwithvar COMMA ID LBRACEM NUMBERD RBRACEM .  (16)

	.  reduce 16


state 193
	stmt : LBRACESS error . SEMI

	SEMI  shift 213


state 194
	ifstmt : IF LBRACESS . expr RBRACESS stmtcomstmt ELSE stmtcomstmt
	ifstmt : IF LBRACESS . expr error stmtcomstmt ELSE stmtcomstmt
	ifstmt : IF LBRACESS . expr error stmtcomstmt
	ifstmt : IF LBRACESS . expr RBRACESS stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 214
	valueexpr  goto 61
	calexpr  goto 62


state 195
	whilestmt : WHILE LBRACESS . expr RBRACESS stmtcomstmt
	whilestmt : WHILE LBRACESS . expr error stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 215
	valueexpr  goto 61
	calexpr  goto 62


state 196
	forstmt : FOR LBRACESS . expr SEMI expr SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS . expr SEMI expr SEMI RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS . expr SEMI SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS . SEMI expr SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS . SEMI expr SEMI RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS . SEMI SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS . expr SEMI SEMI RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS . SEMI SEMI RBRACESS stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	SEMI  shift 216
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 217
	valueexpr  goto 61
	calexpr  goto 62


state 197
	coutlist : BTCLEFT . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 218
	valueexpr  goto 61
	calexpr  goto 62


state 198
	coutlist : coutlist . BTCLEFT expr
	coutstmt : COUT coutlist . SEMI

	SEMI  shift 219
	BTCLEFT  shift 220


state 199
	cinlist : BTCRIGHT . valueexpr

	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 221


state 200
	cinstmt : CIN cinlist . SEMI
	cinlist : cinlist . BTCRIGHT valueexpr

	SEMI  shift 222
	BTCRIGHT  shift 223


state 201
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	returnstmt : RETURN expr . SEMI
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	SEMI  shift 224
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110


state 202
	comstmt : LBRACE midum cstmtlist RBRACE .  (86)

	.  reduce 86


state 203
	cstmtlist : cstmtlist comstmt .  (82)

	.  reduce 82


state 204
	cstmtlist : cstmtlist stmt .  (83)

	.  reduce 83


state 205
	stmt : expr SEMI .  (72)

	.  reduce 72


state 206
	typeidlist : typeidlist COMMA typep ID LBRACEM . NUMBERD RBRACEM

	NUMBERD  shift 225


state 207
	typeidlist : typep ID LBRACEM NUMBERD RBRACEM .  (116)

	.  reduce 116


state 208
	exprlist : exprlist COMMA expr .  (19)
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110
	.  reduce 19


state 209
	calexpr : valueexpr POINT ID LBRACESS RBRACESS .  (59)

	.  reduce 59


state 210
	exprlist : exprlist . COMMA expr
	calexpr : valueexpr POINT ID LBRACESS exprlist . RBRACESS

	RBRACESS  shift 226
	COMMA  shift 188


state 211
	calexpr : valueexpr CLASSMC ID LBRACESS RBRACESS .  (58)

	.  reduce 58


state 212
	exprlist : exprlist . COMMA expr
	calexpr : valueexpr CLASSMC ID LBRACESS exprlist . RBRACESS

	RBRACESS  shift 227
	COMMA  shift 188


state 213
	stmt : LBRACESS error SEMI .  (73)

	.  reduce 73


state 214
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	ifstmt : IF LBRACESS expr . RBRACESS stmtcomstmt ELSE stmtcomstmt
	ifstmt : IF LBRACESS expr . error stmtcomstmt ELSE stmtcomstmt
	ifstmt : IF LBRACESS expr . error stmtcomstmt
	calexpr : expr . EQ expr
	ifstmt : IF LBRACESS expr . RBRACESS stmtcomstmt

	error  shift 228
	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	RBRACESS  shift 229
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110


state 215
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	whilestmt : WHILE LBRACESS expr . RBRACESS stmtcomstmt
	whilestmt : WHILE LBRACESS expr . error stmtcomstmt
	calexpr : expr . EQ expr

	error  shift 230
	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	RBRACESS  shift 231
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110


state 216
	forstmt : FOR LBRACESS SEMI . expr SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS SEMI . expr SEMI RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS SEMI . SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS SEMI . SEMI RBRACESS stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	SEMI  shift 232
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 233
	valueexpr  goto 61
	calexpr  goto 62


state 217
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	forstmt : FOR LBRACESS expr . SEMI expr SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr . SEMI expr SEMI RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr . SEMI SEMI expr RBRACESS stmtcomstmt
	calexpr : expr . EQ expr
	forstmt : FOR LBRACESS expr . SEMI SEMI RBRACESS stmtcomstmt

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	SEMI  shift 234
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110


state 218
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr
	coutlist : BTCLEFT expr .  (106)

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCRIGHT  shift 110
	.  reduce 106


state 219
	coutstmt : COUT coutlist SEMI .  (107)

	.  reduce 107


state 220
	coutlist : coutlist BTCLEFT . expr

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 235
	valueexpr  goto 61
	calexpr  goto 62


state 221
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr . POINT valueexpr
	valueexpr : valueexpr . LBRACEM expr RBRACEM
	cinlist : BTCRIGHT valueexpr .  (109)

	LBRACEM  shift 113
	POINT  shift 129
	CLASSMC  shift 130
	.  reduce 109


state 222
	cinstmt : CIN cinlist SEMI .  (110)

	.  reduce 110


state 223
	cinlist : cinlist BTCRIGHT . valueexpr

	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	LBRACESS  shift 80
	ID  shift 81

	valueexpr  goto 236


state 224
	returnstmt : RETURN expr SEMI .  (71)

	.  reduce 71


state 225
	typeidlist : typeidlist COMMA typep ID LBRACEM NUMBERD . RBRACEM

	RBRACEM  shift 237


state 226
	calexpr : valueexpr POINT ID LBRACESS exprlist RBRACESS .  (56)

	.  reduce 56


state 227
	calexpr : valueexpr CLASSMC ID LBRACESS exprlist RBRACESS .  (55)

	.  reduce 55


state 228
	ifstmt : IF LBRACESS expr error . stmtcomstmt ELSE stmtcomstmt
	ifstmt : IF LBRACESS expr error . stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 162
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 163
	WHILE  shift 164
	FOR  shift 165
	COUT  shift 166
	CIN  shift 167
	RETURN  shift 168
	LBRACE  shift 66
	SEMI  shift 170
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 171

	comstmt  goto 238
	stmtcomstmt  goto 239
	basetype  goto 174
	expr  goto 175
	basetypestmt  goto 176
	valueexpr  goto 61
	whilestmt  goto 177
	stmt  goto 240
	among  goto 15
	calexpr  goto 62
	returnstmt  goto 179
	ifstmt  goto 180
	cinstmt  goto 181
	coutstmt  goto 182
	forstmt  goto 183


state 229
	ifstmt : IF LBRACESS expr RBRACESS . stmtcomstmt ELSE stmtcomstmt
	ifstmt : IF LBRACESS expr RBRACESS . stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 162
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 163
	WHILE  shift 164
	FOR  shift 165
	COUT  shift 166
	CIN  shift 167
	RETURN  shift 168
	LBRACE  shift 66
	SEMI  shift 170
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 171

	comstmt  goto 238
	stmtcomstmt  goto 241
	basetype  goto 174
	expr  goto 175
	basetypestmt  goto 176
	valueexpr  goto 61
	whilestmt  goto 177
	stmt  goto 240
	among  goto 15
	calexpr  goto 62
	returnstmt  goto 179
	ifstmt  goto 180
	cinstmt  goto 181
	coutstmt  goto 182
	forstmt  goto 183


state 230
	whilestmt : WHILE LBRACESS expr error . stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 162
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 163
	WHILE  shift 164
	FOR  shift 165
	COUT  shift 166
	CIN  shift 167
	RETURN  shift 168
	LBRACE  shift 66
	SEMI  shift 170
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 171

	comstmt  goto 238
	stmtcomstmt  goto 242
	basetype  goto 174
	expr  goto 175
	basetypestmt  goto 176
	valueexpr  goto 61
	whilestmt  goto 177
	stmt  goto 240
	among  goto 15
	calexpr  goto 62
	returnstmt  goto 179
	ifstmt  goto 180
	cinstmt  goto 181
	coutstmt  goto 182
	forstmt  goto 183


state 231
	whilestmt : WHILE LBRACESS expr RBRACESS . stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 162
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 163
	WHILE  shift 164
	FOR  shift 165
	COUT  shift 166
	CIN  shift 167
	RETURN  shift 168
	LBRACE  shift 66
	SEMI  shift 170
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 171

	comstmt  goto 238
	stmtcomstmt  goto 243
	basetype  goto 174
	expr  goto 175
	basetypestmt  goto 176
	valueexpr  goto 61
	whilestmt  goto 177
	stmt  goto 240
	among  goto 15
	calexpr  goto 62
	returnstmt  goto 179
	ifstmt  goto 180
	cinstmt  goto 181
	coutstmt  goto 182
	forstmt  goto 183


state 232
	forstmt : FOR LBRACESS SEMI SEMI . expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS SEMI SEMI . RBRACESS stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	RBRACESS  shift 244
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 245
	valueexpr  goto 61
	calexpr  goto 62


state 233
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	forstmt : FOR LBRACESS SEMI expr . SEMI expr RBRACESS stmtcomstmt
	calexpr : expr . EQ expr
	forstmt : FOR LBRACESS SEMI expr . SEMI RBRACESS stmtcomstmt

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	SEMI  shift 246
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110


state 234
	forstmt : FOR LBRACESS expr SEMI . expr SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr SEMI . expr SEMI RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr SEMI . SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr SEMI . SEMI RBRACESS stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	SEMI  shift 247
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 248
	valueexpr  goto 61
	calexpr  goto 62


state 235
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr
	coutlist : coutlist BTCLEFT expr .  (105)

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCRIGHT  shift 110
	.  reduce 105


state 236
	valueexpr : valueexpr . CLASSMC valueexpr
	valueexpr : valueexpr . POINT valueexpr
	valueexpr : valueexpr . LBRACEM expr RBRACEM
	cinlist : cinlist BTCRIGHT valueexpr .  (108)

	LBRACEM  shift 113
	POINT  shift 129
	CLASSMC  shift 130
	.  reduce 108


state 237
	typeidlist : typeidlist COMMA typep ID LBRACEM NUMBERD RBRACEM .  (114)

	.  reduce 114


state 238
	stmtcomstmt : comstmt .  (90)

	.  reduce 90


239: shift-reduce conflict (shift 249, reduce 94) on ELSE
state 239
	ifstmt : IF LBRACESS expr error stmtcomstmt . ELSE stmtcomstmt
	ifstmt : IF LBRACESS expr error stmtcomstmt .  (94)

	ELSE  shift 249
	.  reduce 94


state 240
	stmtcomstmt : stmt .  (89)

	.  reduce 89


241: shift-reduce conflict (shift 250, reduce 92) on ELSE
state 241
	ifstmt : IF LBRACESS expr RBRACESS stmtcomstmt . ELSE stmtcomstmt
	ifstmt : IF LBRACESS expr RBRACESS stmtcomstmt .  (92)

	ELSE  shift 250
	.  reduce 92


state 242
	whilestmt : WHILE LBRACESS expr error stmtcomstmt .  (96)

	.  reduce 96


state 243
	whilestmt : WHILE LBRACESS expr RBRACESS stmtcomstmt .  (95)

	.  reduce 95


state 244
	forstmt : FOR LBRACESS SEMI SEMI RBRACESS . stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 162
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 163
	WHILE  shift 164
	FOR  shift 165
	COUT  shift 166
	CIN  shift 167
	RETURN  shift 168
	LBRACE  shift 66
	SEMI  shift 170
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 171

	comstmt  goto 238
	stmtcomstmt  goto 251
	basetype  goto 174
	expr  goto 175
	basetypestmt  goto 176
	valueexpr  goto 61
	whilestmt  goto 177
	stmt  goto 240
	among  goto 15
	calexpr  goto 62
	returnstmt  goto 179
	ifstmt  goto 180
	cinstmt  goto 181
	coutstmt  goto 182
	forstmt  goto 183


state 245
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	calexpr : expr . EQ expr
	forstmt : FOR LBRACESS SEMI SEMI expr . RBRACESS stmtcomstmt

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	RBRACESS  shift 252
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110


state 246
	forstmt : FOR LBRACESS SEMI expr SEMI . expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS SEMI expr SEMI . RBRACESS stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	RBRACESS  shift 253
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 254
	valueexpr  goto 61
	calexpr  goto 62


state 247
	forstmt : FOR LBRACESS expr SEMI SEMI . expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr SEMI SEMI . RBRACESS stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	RBRACESS  shift 255
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 256
	valueexpr  goto 61
	calexpr  goto 62


state 248
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	forstmt : FOR LBRACESS expr SEMI expr . SEMI expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr SEMI expr . SEMI RBRACESS stmtcomstmt
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	SEMI  shift 257
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110


state 249
	ifstmt : IF LBRACESS expr error stmtcomstmt ELSE . stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 162
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 163
	WHILE  shift 164
	FOR  shift 165
	COUT  shift 166
	CIN  shift 167
	RETURN  shift 168
	LBRACE  shift 66
	SEMI  shift 170
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 171

	comstmt  goto 238
	stmtcomstmt  goto 258
	basetype  goto 174
	expr  goto 175
	basetypestmt  goto 176
	valueexpr  goto 61
	whilestmt  goto 177
	stmt  goto 240
	among  goto 15
	calexpr  goto 62
	returnstmt  goto 179
	ifstmt  goto 180
	cinstmt  goto 181
	coutstmt  goto 182
	forstmt  goto 183


state 250
	ifstmt : IF LBRACESS expr RBRACESS stmtcomstmt ELSE . stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 162
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 163
	WHILE  shift 164
	FOR  shift 165
	COUT  shift 166
	CIN  shift 167
	RETURN  shift 168
	LBRACE  shift 66
	SEMI  shift 170
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 171

	comstmt  goto 238
	stmtcomstmt  goto 259
	basetype  goto 174
	expr  goto 175
	basetypestmt  goto 176
	valueexpr  goto 61
	whilestmt  goto 177
	stmt  goto 240
	among  goto 15
	calexpr  goto 62
	returnstmt  goto 179
	ifstmt  goto 180
	cinstmt  goto 181
	coutstmt  goto 182
	forstmt  goto 183


state 251
	forstmt : FOR LBRACESS SEMI SEMI RBRACESS stmtcomstmt .  (104)

	.  reduce 104


state 252
	forstmt : FOR LBRACESS SEMI SEMI expr RBRACESS . stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 162
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 163
	WHILE  shift 164
	FOR  shift 165
	COUT  shift 166
	CIN  shift 167
	RETURN  shift 168
	LBRACE  shift 66
	SEMI  shift 170
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 171

	comstmt  goto 238
	stmtcomstmt  goto 260
	basetype  goto 174
	expr  goto 175
	basetypestmt  goto 176
	valueexpr  goto 61
	whilestmt  goto 177
	stmt  goto 240
	among  goto 15
	calexpr  goto 62
	returnstmt  goto 179
	ifstmt  goto 180
	cinstmt  goto 181
	coutstmt  goto 182
	forstmt  goto 183


state 253
	forstmt : FOR LBRACESS SEMI expr SEMI RBRACESS . stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 162
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 163
	WHILE  shift 164
	FOR  shift 165
	COUT  shift 166
	CIN  shift 167
	RETURN  shift 168
	LBRACE  shift 66
	SEMI  shift 170
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 171

	comstmt  goto 238
	stmtcomstmt  goto 261
	basetype  goto 174
	expr  goto 175
	basetypestmt  goto 176
	valueexpr  goto 61
	whilestmt  goto 177
	stmt  goto 240
	among  goto 15
	calexpr  goto 62
	returnstmt  goto 179
	ifstmt  goto 180
	cinstmt  goto 181
	coutstmt  goto 182
	forstmt  goto 183


state 254
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	forstmt : FOR LBRACESS SEMI expr SEMI expr . RBRACESS stmtcomstmt
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	RBRACESS  shift 262
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110


state 255
	forstmt : FOR LBRACESS expr SEMI SEMI RBRACESS . stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 162
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 163
	WHILE  shift 164
	FOR  shift 165
	COUT  shift 166
	CIN  shift 167
	RETURN  shift 168
	LBRACE  shift 66
	SEMI  shift 170
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 171

	comstmt  goto 238
	stmtcomstmt  goto 263
	basetype  goto 174
	expr  goto 175
	basetypestmt  goto 176
	valueexpr  goto 61
	whilestmt  goto 177
	stmt  goto 240
	among  goto 15
	calexpr  goto 62
	returnstmt  goto 179
	ifstmt  goto 180
	cinstmt  goto 181
	coutstmt  goto 182
	forstmt  goto 183


state 256
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	forstmt : FOR LBRACESS expr SEMI SEMI expr . RBRACESS stmtcomstmt
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	RBRACESS  shift 264
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110


state 257
	forstmt : FOR LBRACESS expr SEMI expr SEMI . expr RBRACESS stmtcomstmt
	forstmt : FOR LBRACESS expr SEMI expr SEMI . RBRACESS stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 55
	RBRACESS  shift 265
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 59

	expr  goto 266
	valueexpr  goto 61
	calexpr  goto 62


state 258
	ifstmt : IF LBRACESS expr error stmtcomstmt ELSE stmtcomstmt .  (93)

	.  reduce 93


state 259
	ifstmt : IF LBRACESS expr RBRACESS stmtcomstmt ELSE stmtcomstmt .  (91)

	.  reduce 91


state 260
	forstmt : FOR LBRACESS SEMI SEMI expr RBRACESS stmtcomstmt .  (103)

	.  reduce 103


state 261
	forstmt : FOR LBRACESS SEMI expr SEMI RBRACESS stmtcomstmt .  (102)

	.  reduce 102


state 262
	forstmt : FOR LBRACESS SEMI expr SEMI expr RBRACESS . stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 162
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 163
	WHILE  shift 164
	FOR  shift 165
	COUT  shift 166
	CIN  shift 167
	RETURN  shift 168
	LBRACE  shift 66
	SEMI  shift 170
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 171

	comstmt  goto 238
	stmtcomstmt  goto 267
	basetype  goto 174
	expr  goto 175
	basetypestmt  goto 176
	valueexpr  goto 61
	whilestmt  goto 177
	stmt  goto 240
	among  goto 15
	calexpr  goto 62
	returnstmt  goto 179
	ifstmt  goto 180
	cinstmt  goto 181
	coutstmt  goto 182
	forstmt  goto 183


state 263
	forstmt : FOR LBRACESS expr SEMI SEMI RBRACESS stmtcomstmt .  (101)

	.  reduce 101


state 264
	forstmt : FOR LBRACESS expr SEMI SEMI expr RBRACESS . stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 162
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 163
	WHILE  shift 164
	FOR  shift 165
	COUT  shift 166
	CIN  shift 167
	RETURN  shift 168
	LBRACE  shift 66
	SEMI  shift 170
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 171

	comstmt  goto 238
	stmtcomstmt  goto 268
	basetype  goto 174
	expr  goto 175
	basetypestmt  goto 176
	valueexpr  goto 61
	whilestmt  goto 177
	stmt  goto 240
	among  goto 15
	calexpr  goto 62
	returnstmt  goto 179
	ifstmt  goto 180
	cinstmt  goto 181
	coutstmt  goto 182
	forstmt  goto 183


state 265
	forstmt : FOR LBRACESS expr SEMI expr SEMI RBRACESS . stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 162
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 163
	WHILE  shift 164
	FOR  shift 165
	COUT  shift 166
	CIN  shift 167
	RETURN  shift 168
	LBRACE  shift 66
	SEMI  shift 170
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 171

	comstmt  goto 238
	stmtcomstmt  goto 269
	basetype  goto 174
	expr  goto 175
	basetypestmt  goto 176
	valueexpr  goto 61
	whilestmt  goto 177
	stmt  goto 240
	among  goto 15
	calexpr  goto 62
	returnstmt  goto 179
	ifstmt  goto 180
	cinstmt  goto 181
	coutstmt  goto 182
	forstmt  goto 183


state 266
	calexpr : expr . BTCOR expr
	calexpr : expr . BTCAND expr
	calexpr : expr . ALGCADD expr
	calexpr : expr . ALGCMUL expr
	calexpr : expr . ALGCDIV expr
	calexpr : expr . BTCRIGHT expr
	calexpr : expr . ALGCMINUS expr
	calexpr : expr . LGCCMOREEQ expr
	calexpr : expr . LBRACES expr
	calexpr : expr . LGCCLESSEQ expr
	calexpr : expr . RBRACES expr
	calexpr : expr . LGCCEQ expr
	calexpr : expr . ALGCMOD expr
	calexpr : expr . BTCYH expr
	calexpr : expr . BTCLEFT expr
	calexpr : expr . LGCCNEQ expr
	calexpr : expr . LGCCAND expr
	calexpr : expr . LGCCOR expr
	forstmt : FOR LBRACESS expr SEMI expr SEMI expr . RBRACESS stmtcomstmt
	calexpr : expr . EQ expr

	ALGCADD  shift 92
	ALGCMINUS  shift 93
	ALGCMUL  shift 94
	ALGCDIV  shift 95
	ALGCMOD  shift 96
	RBRACESS  shift 270
	EQ  shift 97
	LBRACES  shift 98
	RBRACES  shift 99
	LGCCEQ  shift 100
	LGCCLESSEQ  shift 101
	LGCCMOREEQ  shift 102
	LGCCNEQ  shift 103
	LGCCAND  shift 104
	LGCCOR  shift 105
	BTCYH  shift 106
	BTCOR  shift 107
	BTCAND  shift 108
	BTCLEFT  shift 109
	BTCRIGHT  shift 110


state 267
	forstmt : FOR LBRACESS SEMI expr SEMI expr RBRACESS stmtcomstmt .  (100)

	.  reduce 100


state 268
	forstmt : FOR LBRACESS expr SEMI SEMI expr RBRACESS stmtcomstmt .  (99)

	.  reduce 99


state 269
	forstmt : FOR LBRACESS expr SEMI expr SEMI RBRACESS stmtcomstmt .  (98)

	.  reduce 98


state 270
	forstmt : FOR LBRACESS expr SEMI expr SEMI expr RBRACESS . stmtcomstmt

	ALGCMINUS  shift 46
	ALGCMUL  shift 47
	ALGCTADD  shift 48
	ALGCTMINUS  shift 49
	NUMBERD  shift 50
	DIGIT  shift 51
	STRING  shift 52
	ONECHAR  shift 53
	FLOATD  shift 54
	LBRACESS  shift 162
	INT  shift 37
	FLOAT  shift 2
	CHAR  shift 3
	VOID  shift 4
	IF  shift 163
	WHILE  shift 164
	FOR  shift 165
	COUT  shift 166
	CIN  shift 167
	RETURN  shift 168
	LBRACE  shift 66
	SEMI  shift 170
	LGCCN  shift 56
	BTCAND  shift 57
	BTCN  shift 58
	ID  shift 171

	comstmt  goto 238
	stmtcomstmt  goto 271
	basetype  goto 174
	expr  goto 175
	basetypestmt  goto 176
	valueexpr  goto 61
	whilestmt  goto 177
	stmt  goto 240
	among  goto 15
	calexpr  goto 62
	returnstmt  goto 179
	ifstmt  goto 180
	cinstmt  goto 181
	coutstmt  goto 182
	forstmt  goto 183


state 271
	forstmt : FOR LBRACESS expr SEMI expr SEMI expr RBRACESS stmtcomstmt .  (97)

	.  reduce 97


##############################################################################
# Summary
##############################################################################

State 171 contains 1 reduce-reduce conflict(s)
State 239 contains 1 shift-reduce conflict(s)
State 241 contains 1 shift-reduce conflict(s)


65 token(s), 31 nonterminal(s)
130 grammar rule(s), 272 state(s)


##############################################################################
# End of File
##############################################################################
