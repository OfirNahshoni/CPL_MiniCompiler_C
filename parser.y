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
	symbol_table_entry* currentID;
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
}

%token <val> NUM SENTENCE ID
%token <myop> RELOP PLUS MINUS MUL DIV ASSIGN OR AND
%token BREAK CASE DECL DEFAULT ELSE END FINAL FOREACH IF IN INT
%token OUT PROGRAM REAL START STRING SWITCH THEN TILL WHILE WITH

%type <val> list declarlist decl cdecl declarations
%type <val> type expression factor term bool_expr bool_factor bool_term


%left FOREACH
%left OR
%left AND
%left PLUS
%left MINUS
%left MUL
%left DIV
%right ASSIGN


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
| error declarlist cdecl {
	is_prog_valid = false;
	yyerror("decl keyword is missing");
	yyerrok;
}
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

cdecl: FINAL type ID ASSIGN NUM ';' cdecl { // crule
	// final int x = 2;
	symbol_table_entry* tempID = lookup(SymbolTable, $3.sval);
	if (tempID) {
		is_prog_valid = false;
		yyerror("ID is already defined from crule");
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
| ID ASSIGN SENTENCE ';' {
	symbol_table_entry* tempID = lookup(SymbolTable, $1.sval);
	if (tempID == NULL){
		is_prog_valid = false;
		yyerror("ID is not declared!");
	}
	else {
		if (tempID->type != 's') {
			is_prog_valid = false;
			yyerror("String must be assigned to string type only.");
		}
		tempID->is_init = true;
	}
}
| control_stmt
| in_stmt
| out_stmt
| stmt_block
;

in_stmt: IN '(' ID ')' ';' {
	symbol_table_entry* tempID = lookup(SymbolTable, $3.sval);
	if (tempID == NULL) {
		is_prog_valid = false;
		yyerror("You must declar the type of ID to get input to it.");
	}
	else {
		if (tempID->is_const) {
			is_prog_valid = false;
			yyerror("You cannot change value of const (final) variable.");
		}
		else
			tempID->is_init = true;
	}
}
;

out_stmt: OUT '(' expression ')' ';'
| OUT '(' SENTENCE ')' ';'
;

assign_stmt: ID ASSIGN expression ';' { // 1
	symbol_table_entry* tempID = lookup(SymbolTable, $1.sval);
	if (tempID == NULL) {
		is_prog_valid = false;
		yyerror("ID is not declared!");
	}
	else {
		if (tempID->is_const) {
			is_prog_valid = false;
			yyerror("Cannot assign value to const (final) variable.");
		}
		if (tempID->type != $3.type) { // 'i' = 'r' // 'r' == 'i' // 'r' = 's'
			if (tempID->type == 'i' || tempID->type == 's') {
				is_prog_valid = false;
				yyerror("Assign operation is not valid.");
			}
		}
		tempID->is_init = true;
	}
}
;

control_stmt: IF '(' bool_expr ')' THEN stmt ELSE stmt {
	// bool_expr true -> jump ?
}
| WHILE '(' bool_expr ')' stmt_block {
	// j loop
	// bne 
}
| FOREACH ID ASSIGN NUM TILL NUM WITH step stmt {
	symbol_table_entry* tempID = lookup(SymbolTable, $2.sval);
	if (tempID == NULL) {
		is_prog_valid = false;
		yyerror("Loop ID is not declared!");
	}
	else {
		currentID = tempID;
		if (tempID->is_const) {
			is_prog_valid = false;
			yyerror("Cannot assign value to const (final) variable.");
		}
		else {
			if ($2.type == 'i' && $4.type == 'r') {
				is_prog_valid = false;
				yyerror("Cannot assign real value to int.");
			}
			else
				tempID->is_init = true;
		}
	}
} 
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

step: ID ASSIGN ID PLUS NUM {
	symbol_table_entry* tempID1 = lookup(SymbolTable, $1.sval);
	symbol_table_entry* tempID2 = lookup(SymbolTable, $3.sval);
	if (tempID1 == NULL || tempID2 == NULL) {
		is_prog_valid = false;
		yyerror("ID is not declared!");
	}
	else {
		if (strcmp(tempID1->name, tempID2->name)) { // not the same ID
			is_prog_valid = false;
			yyerror("Step ID must match the loop variable ID.");
		}
		else {
			if (tempID1->type == 'i' && (tempID2->type == 'r' || $5.type == 'r')) {
				is_prog_valid = false;
				yyerror("Cannot assign real value into integer.");
			}
			// else {
				// Write mips here
			// }
		}
	}

}
| ID ASSIGN ID MINUS NUM
| ID ASSIGN ID MUL NUM
| ID ASSIGN ID DIV NUM
;

bool_expr: bool_expr OR bool_term
| bool_term
;

bool_term: bool_term AND bool_factor
| bool_factor {
	
}
;

bool_factor: '!' '(' bool_factor ')' /* -> NOT bool_factore */ {
	$$.res_bool_exp = !($3.res_bool_exp);
	// bne - mips
}
| expression RELOP expression
;

expression: expression PLUS term {
	if ($1.type == 'r' || $3.type == 'r')
		$$.type = 'r';
	else
		$$.type = 'i';
}
| expression MINUS term {
	if ($1.type == 'r' || $3.type == 'r')
		$$.type = 'r';
	else
		$$.type = 'i';
}
| term { $$.type = $1.type; }
;

term: term MUL factor {
	if ($1.type == 'r' || $3.type == 'r')
		$$.type = 'r';
	else
		if ($1.type == 's' || $3.type == 's') {
			is_prog_valid = false;
			yyerror("Cannot do arithmetic operations on strings");
		}
		else
			$$.type = $1.type;
}
| term DIV factor {
	if ($1.type == 'r' || $3.type == 'r')
		$$.type = 'r';
	else
		if ($1.type == 's' || $3.type == 's') {
			is_prog_valid = false;
			yyerror("Cannot do arithmetic operations on strings");
		}
		else
			$$.type = $1.type;
}
| factor {
	$$.type = $1.type;
}
;

factor: '(' expression ')' {
	$$.type = $2.type;
}
| ID {
	symbol_table_entry* tempID = lookup(SymbolTable, $1.sval);
	if (tempID == NULL) { // ERROR
		is_prog_valid = false;
		yyerror("ID is not declared!");
	}
	else {
		if (tempID->type == 's') { // ERROR
			is_prog_valid = false;
			yyerror("String should not used in arithmetic operations!");
		}
		else if (tempID->is_init == false) { // ERROR
			is_prog_valid = false;
			yyerror("ID is not initialized.");
		}
		else { // OK
			current_type = tempID->type;
			$$.type = current_type;
		}
	}
}
| NUM {
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