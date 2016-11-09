/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SRC_BISON_HPP_INCLUDED
# define YY_YY_SRC_BISON_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/grammatic.bizon" /* yacc.c:1909  */

    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include <stdbool.h>
    #include "shared_ptrs_nodes/Expressions.h"
	#include "shared_ptrs_nodes/Statements.h"
	#include "shared_ptrs_nodes/Classes.h"

       
    #define YYERROR_VERBOSE 1        

#line 57 "src/bison.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NEW = 258,
    CLASS = 259,
    EXTENDS = 260,
    THIS = 261,
    RETURN = 262,
    PUBLIC = 263,
    PRIVATE = 264,
    STATIC = 265,
    PRINTLN = 266,
    INT = 267,
    BOOLEAN = 268,
    VOID = 269,
    INT_ARRAY = 270,
    LENGTH = 271,
    TRUE = 272,
    FALSE = 273,
    WHILE = 274,
    IF = 275,
    ELSE = 276,
    NUM = 277,
    ID = 278,
    LPAREN = 279,
    RPAREN = 280,
    LBRACKET = 281,
    RBRACKET = 282,
    LBRACE = 283,
    RBRACE = 284,
    COMMA = 285,
    DOT = 286,
    SEMI = 287,
    COMMENT = 288,
    AND = 289,
    OR = 290,
    PLUS = 291,
    MINUS = 292,
    TIMES = 293,
    MOD = 294,
    MAIN = 295,
    STRING = 296,
    LESS = 297,
    GREATER = 298,
    NOT = 299,
    ASSIGN = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 24 "src/grammatic.bizon" /* yacc.c:1909  */


	CProgram* Program; // Указатель на класс-программу
	CClass* Class; // Указатель класс
	IStatement* Statement;
	IExpression* Expression;
	CType* Type;
	CField* VarDeclaration;
	CFieldList* VarDeclaratitionList;
	CArgument* Argument;
	CArgumentList* ArgumentList;
	CMethod* MethodDeclaration;
	CMethodList* MethodDeclarationList;
	CMainMethod* MainMethod;
	CMainClass* MainClass;
	CExpList* ExpressionList;
	char *string;

#line 134 "src/bison.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (CProgram** program);

#endif /* !YY_YY_SRC_BISON_HPP_INCLUDED  */
