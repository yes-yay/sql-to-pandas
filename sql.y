%{
#include "sql_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int yyparse();
extern FILE *yyin;
void yyerror(const char *s);
%}

%union {
    char *strval;
    char *comparison;
    char *value;
}

%token <strval> IDENTIFIER INTEGER STRING
%token SELECT INSERT UPDATE DELETE FROM WHERE
%token JOIN ON INTO VALUES SET GROUP BY
%token ORDER ASC DESC AND OR
%token EQUAL LESS GREATER LESS_EQUAL GREATER_EQUAL NOT_EQUAL
%token COMMA SEMICOLON LPAREN RPAREN STAR

/* Define types for non-terminals */
%type <strval> value
%type <comparison> comparison_op
%type <strval> opt_direction
%type <strval> condition

%%

query_list:
    query SEMICOLON {
        generate_pandas_code(&current_query);
        init_query_info();
    }
    ;

query:
    select_query
    | insert_query
    | update_query
    | delete_query
    ;

select_query:
    SELECT select_list FROM table_reference opt_where opt_group opt_order {
        strcpy(current_query.query_type, "SELECT");
    }
    ;

select_list:
    STAR {
        strcpy(current_query.columns[0], "*");
        current_query.column_count = 1;
    }
    | column_list
    ;

column_list:
    IDENTIFIER {
        strcpy(current_query.columns[current_query.column_count++], $1);
    }
    | column_list COMMA IDENTIFIER {
        strcpy(current_query.columns[current_query.column_count++], $3);
    }
    ;

table_reference:
    IDENTIFIER {
        strcpy(current_query.table_name, $1);
    }
    | IDENTIFIER JOIN IDENTIFIER ON join_condition {
        strcpy(current_query.table_name, $1);
        strcpy(current_query.join_table, $3);
    }
    ;

join_condition:
    IDENTIFIER EQUAL IDENTIFIER {
        sprintf(current_query.join_condition, "%s = %s", $1, $3);
    }
    ;

opt_where:
    /* empty */
    | WHERE condition
    ;

opt_group:
    /* empty */
    | GROUP BY IDENTIFIER {
        strcpy(current_query.group_by, $3);
    }
    ;

opt_order:
    /* empty */
    | ORDER BY IDENTIFIER opt_direction {
        strcpy(current_query.order_by, $3);
        strcpy(current_query.order_direction, $4);
    }
    ;

opt_direction:
    /* empty */ { $$ = strdup("ASC"); }
    | ASC { $$ = strdup("ASC"); }
    | DESC { $$ = strdup("DESC"); }
    ;

condition:
    IDENTIFIER comparison_op value {
        char temp[256];
        sprintf(temp, "%s %s %s", $1, $2, $3);
        $$ = strdup(temp);
        strcat(current_query.conditions, $$);
    }
    | condition AND condition {
        char temp[512];
        sprintf(temp, "(%s) & (%s)", $1, $3);
        $$ = strdup(temp);
    }
    | condition OR condition {
        char temp[512];
        sprintf(temp, "(%s) | (%s)", $1, $3);
        $$ = strdup(temp);
    }
    ;

comparison_op:
    EQUAL { $$ = strdup("=="); }
    | LESS { $$ = strdup("<"); }
    | GREATER { $$ = strdup(">"); }
    | LESS_EQUAL { $$ = strdup("<="); }
    | GREATER_EQUAL { $$ = strdup(">="); }
    | NOT_EQUAL { $$ = strdup("!="); }
    ;

value:
    INTEGER { $$ = strdup($1); }
    | STRING {
        char temp[256];
        sprintf(temp, "'%s'", $1);
        $$ = strdup(temp);
    }
    ;

insert_query:
    INSERT INTO IDENTIFIER LPAREN column_list RPAREN VALUES LPAREN value_list RPAREN {
        strcpy(current_query.query_type, "INSERT");
        strcpy(current_query.table_name, $3);
    }
    ;

value_list:
    value {
        strcpy(current_query.values[current_query.value_count++], $1);
    }
    | value_list COMMA value {
        strcpy(current_query.values[current_query.value_count++], $3);
    }
    ;

update_query:
    UPDATE IDENTIFIER SET IDENTIFIER EQUAL value opt_where {
        strcpy(current_query.query_type, "UPDATE");
        strcpy(current_query.table_name, $2);
        strcpy(current_query.columns[0], $4);
        strcpy(current_query.values[0], $6);
    }
    ;

delete_query:
    DELETE FROM IDENTIFIER opt_where {
        strcpy(current_query.query_type, "DELETE");
        strcpy(current_query.table_name, $3);
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}