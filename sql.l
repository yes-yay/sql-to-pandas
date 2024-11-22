%{
#include "sql_parser.h"
#include "y.tab.h"
#include <string.h>
#include <stdlib.h>

extern char *strdup(const char *s);
%}

%%
SELECT      { return SELECT; }
INSERT      { return INSERT; }
UPDATE      { return UPDATE; }
DELETE      { return DELETE; }
FROM        { return FROM; }
WHERE       { return WHERE; }
JOIN        { return JOIN; }
ON          { return ON; }
INTO        { return INTO; }
VALUES      { return VALUES; }
SET         { return SET; }
GROUP       { return GROUP; }
BY          { return BY; }
ORDER       { return ORDER; }
ASC         { return ASC; }
DESC        { return DESC; }
AND         { return AND; }
OR          { return OR; }

[A-Za-z][A-Za-z0-9_]*  { 
    yylval.strval = strdup(yytext); 
    return IDENTIFIER; 
}
[0-9]+      { 
    yylval.strval = strdup(yytext); 
    return INTEGER; 
}
'[^']*'     {
    yylval.strval = strdup(yytext+1);
    yylval.strval[strlen(yylval.strval)-1] = '\0';
    return STRING;
}
"="         { return EQUAL; }
"<"         { return LESS; }
">"         { return GREATER; }
"<="        { return LESS_EQUAL; }
">="        { return GREATER_EQUAL; }
"!="        { return NOT_EQUAL; }
";"         { return SEMICOLON; }
","         { return COMMA; }
"("         { return LPAREN; }
")"         { return RPAREN; }
"*"         { return STAR; }

[ \t\n]     ; /* Skip whitespace */
.           { printf("Unknown character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
