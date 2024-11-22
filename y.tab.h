/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    INTEGER = 259,                 /* INTEGER  */
    STRING = 260,                  /* STRING  */
    SELECT = 261,                  /* SELECT  */
    INSERT = 262,                  /* INSERT  */
    UPDATE = 263,                  /* UPDATE  */
    DELETE = 264,                  /* DELETE  */
    FROM = 265,                    /* FROM  */
    WHERE = 266,                   /* WHERE  */
    JOIN = 267,                    /* JOIN  */
    ON = 268,                      /* ON  */
    INTO = 269,                    /* INTO  */
    VALUES = 270,                  /* VALUES  */
    SET = 271,                     /* SET  */
    GROUP = 272,                   /* GROUP  */
    BY = 273,                      /* BY  */
    ORDER = 274,                   /* ORDER  */
    ASC = 275,                     /* ASC  */
    DESC = 276,                    /* DESC  */
    AND = 277,                     /* AND  */
    OR = 278,                      /* OR  */
    EQUAL = 279,                   /* EQUAL  */
    LESS = 280,                    /* LESS  */
    GREATER = 281,                 /* GREATER  */
    LESS_EQUAL = 282,              /* LESS_EQUAL  */
    GREATER_EQUAL = 283,           /* GREATER_EQUAL  */
    NOT_EQUAL = 284,               /* NOT_EQUAL  */
    COMMA = 285,                   /* COMMA  */
    SEMICOLON = 286,               /* SEMICOLON  */
    LPAREN = 287,                  /* LPAREN  */
    RPAREN = 288,                  /* RPAREN  */
    STAR = 289                     /* STAR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IDENTIFIER 258
#define INTEGER 259
#define STRING 260
#define SELECT 261
#define INSERT 262
#define UPDATE 263
#define DELETE 264
#define FROM 265
#define WHERE 266
#define JOIN 267
#define ON 268
#define INTO 269
#define VALUES 270
#define SET 271
#define GROUP 272
#define BY 273
#define ORDER 274
#define ASC 275
#define DESC 276
#define AND 277
#define OR 278
#define EQUAL 279
#define LESS 280
#define GREATER 281
#define LESS_EQUAL 282
#define GREATER_EQUAL 283
#define NOT_EQUAL 284
#define COMMA 285
#define SEMICOLON 286
#define LPAREN 287
#define RPAREN 288
#define STAR 289

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 13 "sql.y"

    char *strval;
    char *comparison;
    char *value;

#line 141 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
