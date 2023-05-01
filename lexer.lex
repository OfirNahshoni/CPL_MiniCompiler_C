%option noyywrap
%{
	// Libraries to include
	#include <stdio.h>
	#include <stdlib.h>
	#include <assert.h>
	#include <string.h>
	
	// Files to include
	#include "my_structs.h"
	#include "parser.tab.h"
	
	// Global variables
	int line = 1;
	int col = 1;
	
	// // Extern files from Bison
	// extern FILE* err_fp;
	// extern FILE* mips_fp;
%}
DIGIT [0-9]
LETTER [a-zA-Z]
SEP " "|\t
SYMBOL "("|")"|"{"|"}"|","|":"|";"|"!"
%%
"/*".*"*/" { /* Do nothing for comments */ }
{SEP} { col++; fprintf(yyout, "%s", yytext); }
"break" { col += yyleng; fprintf(yyout, "%s", yytext); return BREAK; }
"case" { col += yyleng; fprintf(yyout, "%s", yytext); return CASE; }
"decl" { col += yyleng; fprintf(yyout, "%s", yytext); return DECL; }
"default" { col += yyleng; fprintf(yyout, "%s", yytext); return DEFAULT; }
"else" { col += yyleng; fprintf(yyout, "%s", yytext); return ELSE; }
"end" { col += yyleng; fprintf(yyout, "%s", yytext); return END; }
"final" { col += yyleng; fprintf(yyout, "%s", yytext); return FINAL; }
"foreach" { col += yyleng; fprintf(yyout, "%s", yytext); return FOREACH; }
"if" { col += yyleng; fprintf(yyout, "%s", yytext); return IF; }
"in" { col += yyleng; fprintf(yyout, "%s", yytext); return IN; }
"int" { col += yyleng; fprintf(yyout, "%s", yytext); return INT; }
"out" { col += yyleng; fprintf(yyout, "%s", yytext); return OUT; }
"program" { col += yyleng; fprintf(yyout, "%s", yytext); return PROGRAM; }
"real" { col += yyleng; fprintf(yyout, "%s", yytext); return REAL; }
"start" { col += yyleng; fprintf(yyout, "%s", yytext); return START; }
"string" { col += yyleng; fprintf(yyout, "%s", yytext); return STRING; }
"switch" { col += yyleng; fprintf(yyout, "%s", yytext); return SWITCH; }
"then" { col += yyleng; fprintf(yyout, "%s", yytext); return THEN; }
"till" { col += yyleng; fprintf(yyout, "%s", yytext); return TILL; }
"while" { col += yyleng; fprintf(yyout, "%s", yytext); return WHILE; }
"with" { col += yyleng; fprintf(yyout, "%s", yytext); return WITH; }
{SYMBOL} { col++; fprintf(yyout, "%s", yytext); return yytext[0]; }
{LETTER}[[a-zA-Z]*|[0-9]*] { 
								col += yyleng;
								fprintf(yyout, "%s", yytext);
								yylval.val.sval = strdup(yytext);
								return ID;
							}
{DIGIT}+ {
			col += yyleng;
			fprintf(yyout, "%s", yytext);
			yylval.val.sval = strdup(yytext);
			yylval.val.type = 'i'; // int type
			return NUM;
		}
{DIGIT}+"."{DIGIT}* {
				col += yyleng;
				fprintf(yyout, "%s", yytext);
				yylval.val.sval = strdup(yytext);
				yylval.val.type = 'r'; // real type
				return NUM;
		    }
"=="|"<>"|"<"|">"|">="|"<=" { 
		col += yyleng;
		fprintf(yyout, "%s", yytext);
		yylval.myop = 0; // RELOP (enum op {RELOP, PLUS, MINUS, MUL, DIV, ASSIGN, OR, AND})
		return RELOP;
	}
"+" { 
		col++; 
		fprintf(yyout, "%s", yytext);
		yylval.myop = 1; // PLUS (enum op {RELOP, PLUS, MINUS, MUL, DIV, ASSIGN, OR, AND})
		return	PLUS;
	}
"-" { 
		col++;
		fprintf(yyout, "%s", yytext);
		yylval.myop = 2; // MINUS (enum op {RELOP, PLUS, MINUS, MUL, DIV, ASSIGN, OR, AND})
		return MINUS;
	}
"*" { 
		col++;
		fprintf(yyout, "%s", yytext);
		yylval.myop = 3; // MUL (enum op {RELOP, PLUS, MINUS, MUL, DIV, ASSIGN, OR, AND})
		return MUL;
	}
"/" { 
		col++;
		fprintf(yyout, "%s", yytext);
		yylval.myop = 4; // DIV (enum op {RELOP, PLUS, MINUS, MUL, DIV, ASSIGN, OR, AND})
		return DIV;
	}
"=" { 
		col++;
		fprintf(yyout, "%s", yytext);
		yylval.myop = 5; // ASSIGN (enum op {RELOP, PLUS, MINUS, MUL, DIV, ASSIGN, OR, AND})
		return ASSIGN; 
	}
"||" { 
		col += 2;
		fprintf(yyout, "%s", yytext);
		yylval.myop = 6; // OR (enum op {RELOP, PLUS, MINUS, MUL, DIV, ASSIGN, OR, AND})
		return OR;
	}
"&&" {
		col += 2;
		fprintf(yyout, "%s", yytext);
		yylval.myop = 7; // AND (enum op {RELOP, PLUS, MINUS, MUL, DIV, ASSIGN, OR, AND})
		return AND;
	}
\".*\" { 
			col += yyleng;
			fprintf(yyout, "%s", yytext);
			yylval.val.sval = strdup(yytext);
			yylval.val.type = 's'; // String type
			return SENTENCE;
		}
\n { col = 1; fprintf(yyout, "\n%d) ", line++); }
%%
