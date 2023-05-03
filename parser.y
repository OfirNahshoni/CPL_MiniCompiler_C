%{
	// Libraries to include
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <assert.h>
	#include <stdbool.h>

	// Files to include
	#include "symbol_table.h"
	#include "my_structs.h"

	// Global variables
	symbol_table* SymbolTable;
	bool is_prog_valid = true;
	char current_type;

	// External variables (from lex file)
	extern int line;
	extern int col;
	extern int yylex(void);
	extern FILE* yyin;

	void yyerror(const char* msg);
%}
%union {
	Op myop;
	Val val;
	char mytype;
}

%token <val> NUM SENTENCE ID
%token <myop> RELOP PLUS MINUS MUL DIV ASSIGN OR AND
%token BREAK CASE DECL DEFAULT ELSE END FINAL FOREACH IF IN INT
%token OUT PROGRAM REAL START STRING SWITCH THEN TILL WHILE WITH

%type <val> list declarlist decl cdecl declarations
%type <val> type expression factor term


%%
program: PROGRAM ID {	
	// Create the symbol table
	SymbolTable = create_symbol_table(2);
}
START declarations stmtlist END { 
	if (is_prog_valid) {
		printf("\nSuccess\n");
		print(SymbolTable);
		free_symbol_table(SymbolTable);
	}
	else {
		printf("\nNot Valid\n");
		free_symbol_table(SymbolTable);
	}
}
;

declarations: DECL declarlist cdecl
|
;

declarlist: declarlist decl
| decl
;

decl: type ':' list ';' { $3.type = current_type; }
;

list: ID ',' list { // 2.1
	symbol_table_entry* tempSymID = lookup(SymbolTable, $1.sval);
	if (tempSymID) {
		is_prog_valid = false;
		yyerror("ID is already defined");
	}
	else
		add_attribute(SymbolTable, $1.sval, current_type, false, false);
}
| ID { // 2.2
	symbol_table_entry* tempID = lookup(SymbolTable, $1.sval);
	if (tempID) {
		is_prog_valid = false;
		yyerror("ID already defined");
	}
	else
		add_attribute(SymbolTable, $1.sval, current_type, false, false);
}
;

type: INT { current_type = 'i'; }
| REAL { current_type = 'r'; }
| STRING { current_type = 's'; }
;

cdecl: FINAL type ID ASSIGN NUM ';' cdecl {
	// final int x = 2;
	symbol_table_entry* tempID = lookup(SymbolTable, $3.sval);
	if (tempID) {
		is_prog_valid = false;
		yyerror("ID is already defined");
	}
	else {
		if (current_type != $5.type) {
			is_prog_valid = false;
			yyerror("Wrong value assigned");
		}
		else
			add_attribute(SymbolTable, $3.sval, current_type, true, true);
	}
}
|
;

stmtlist: stmtlist stmt  
|
;

stmt: assign_stmt
| ID ASSIGN SENTENCE ';'
| control_stmt 
| in_stmt 
| out_stmt
| stmt_block
;

out_stmt: OUT '(' expression ')' ';'
| OUT '(' SENTENCE ')' ';'
;

in_stmt: IN '(' ID ')' ';'
;

// x = y+5.1;
assign_stmt: ID ASSIGN expression ';' {
	symbol_table_entry* tempID = lookup(SymbolTable, $1.sval);
	if (tempID == NULL) {
		is_prog_valid = false;
		yyerror("ID is not declared!");
	}
	else {
		printf("\nleft.type=%c , right.type = %c\n", tempID->type, $3.type);
		if (tempID->type != $3.type) {
			if (tempID->type == 'i') {
				is_prog_valid = false;
				yyerror("Assign operation is not valid!");
			}
		}
	}
}
;

control_stmt: IF '(' bool_expr ')' THEN stmt ELSE stmt 
| WHILE '(' bool_expr ')' stmt_block
| FOREACH ID ASSIGN NUM TILL NUM WITH step stmt 
| FOREACH ID ASSIGN NUM TILL ID WITH step stmt
| _switch
;

stmt_block: '{' stmtlist '}'
;

_switch: SWITCH '(' ID ')' '{' cases '}'
;

cases: CASE NUM ':' stmtlist BREAK ';' cases
| DEFAULT ':' stmtlist
;

step: ID ASSIGN ID PLUS NUM
| ID ASSIGN ID MINUS NUM
| ID ASSIGN ID MUL NUM
;

bool_expr: bool_expr OR bool_term
| bool_term
;

bool_term: bool_term AND bool_factor
| bool_factor
;

bool_factor: '!' '(' bool_factor ')' /* -> NOT bool_factore */
| expression RELOP expression
;  

expression: expression PLUS term {
	if ($1.type == 'r' || $3.type == 'r')
		$$.type = 'r';
	else
		$$.type = 'i';
}
| term {
	$$.type = $1.type;
}
;

term: term MUL factor
| factor { // 3
	$$.type = $1.type;
	// printf("\n3) %c\n", $$.type);
}
;

factor: '(' expression ')'
| ID { // 1
	symbol_table_entry* tempID = lookup(SymbolTable, $1.sval);
	if (tempID == NULL) {
		is_prog_valid = false;
		yyerror("ID is not declared!");
	}
	else {
		if (tempID->type == 's') {
			is_prog_valid = false;
			yyerror("String should not used in arithmetic operations!");
		}
		else {
			current_type = tempID->type;
			$$.type = current_type;
		}
	}
}
| NUM { // 1
	current_type = $1.type; // 'r' or 'i'
	$$.type = current_type;
}
;

%%
// Main function
int main(int argc, char* argv[])
{
	yyin = fopen(argv[1], "r");
	assert(yyin);

	printf("%d) ", line++);

	do {
		yyparse();
	} while(!feof(yyin));
	fclose(yyin);

	return 0;
}

// Function to add error to the errors files
void yyerror(const char* msg)
{
	// Print errors to the screen
	fprintf(stderr, "\nError (line %d, col %d): %s\n", line-1, col, msg);
}