%{
	// Includes - libraries or files
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <assert.h>
	#include <stdbool.h>
	#include "symbol_table.h"
	#include "my_structs.h"

	// Global variables
	symbol_table* SymbolTable;
	char current_type;
	int current_reg = 0; // Current register index
	bool is_prog_valid = true;

	// External variables (from lex file)
	extern int line;
	extern int col;
	extern int yylex(void);
	extern FILE* yyin;

	// Functions declarations
	void yyerror(const char* msg);
	int next_reg();
	void reset_reg();
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
		printf("\n--------------------------\nResult: ");
		printf("Success\n");
		print(SymbolTable);
		free_symbol_table(SymbolTable);
	}
	else {
		printf("\n--------------------------\nResult: ");
		printf("Not Valid\n");
		free_symbol_table(SymbolTable);
	}
}
| error ID START declarations stmtlist END {
	is_prog_valid = false;
	yyerror("program keyword is missing");
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

cdecl: FINAL type ID ASSIGN NUM ';' cdecl {
	symbol_table_entry* tempID = lookup(SymbolTable, $3.sval);
	if (tempID) {
		is_prog_valid = false;
		yyerror("ID is already defined.");
	}
	else {
		if (current_type == 's') {
			is_prog_valid = false;
			yyerror("Cannot define const string variable.");
		}
		else if (current_type == 'i' && $5.type == 'r') {
			is_prog_valid = false;
			yyerror("Cannot assign real value to int.");
		}
		else
			add_attribute(SymbolTable, $3.sval, current_type, true, true);
	}
}
|
;

type: INT { current_type = 'i'; }
| REAL { current_type = 'r'; }
| STRING { current_type = 's'; }
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

control_stmt: IF '(' bool_expr ')' THEN stmt ELSE stmt
| WHILE '(' bool_expr ')' stmt_block
| FOREACH ID ASSIGN NUM TILL NUM WITH step stmt {
	symbol_table_entry* tempID = lookup(SymbolTable, $2.sval);
	if (tempID == NULL) {
		is_prog_valid = false;
		yyerror("Loop ID is not declared!");
	}
	else {
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
| FOREACH ID ASSIGN NUM TILL ID WITH step stmt {
	symbol_table_entry* tempID1 = lookup(SymbolTable, $2.sval);
	symbol_table_entry* tempID2 = lookup(SymbolTable, $6.sval);
	if (tempID1 == NULL) {
		is_prog_valid = false;
		yyerror("Loop ID is not declared!");
	}
	else if (tempID2 == NULL) {
		is_prog_valid = false;
		yyerror("Up barrier ID is not declared!");
	}
	else {
		if (tempID1->is_const) {
			is_prog_valid = false;
			yyerror("Cannot assign value to const (final) variable.");
		}
		else {
			if ($2.type == 'i' && $4.type == 'r') {
				is_prog_valid = false;
				yyerror("Cannot assign real value to int.");
			}
			else if (tempID2->is_init == false) {
				is_prog_valid = false;
				yyerror("Up barrier loop ID is not initialized.");
			}
			else
				tempID1->is_init = true;
		}
	}
}
| _switch
;

stmt_block: '{' stmtlist '}'
;

_switch: SWITCH '(' ID ')' '{' cases '}' {
	symbol_table_entry* tempID = lookup(SymbolTable, $3.sval);
	if (tempID == NULL) {
		is_prog_valid = false;
		yyerror("ID is not declared!");
	}
	else {
		if (tempID->is_init == false) {
			is_prog_valid = false;
			yyerror("Switch ID is not initialized.");
		}
		else if (tempID->type != current_type) {
			is_prog_valid = false;
			yyerror("Type of case ID is not the same as NUM.");
		}
	}
}
;

cases: CASE NUM ':' stmtlist BREAK ';' cases {
	current_type = $2.type;
}
| DEFAULT ':' stmtlist
| {
	is_prog_valid = false;
	yyerror("default keyword is missing.");
}
;

step: ID ASSIGN ID PLUS NUM {
	symbol_table_entry* tempID1 = lookup(SymbolTable, $1.sval);
	symbol_table_entry* tempID2 = lookup(SymbolTable, $3.sval);
	if (tempID1 == NULL || tempID2 == NULL) {
		is_prog_valid = false;
		yyerror("ID is not declared!");
	}
	else {
		if (strcmp(tempID1->name, tempID2->name) != 0) { // not the same ID
			is_prog_valid = false;
			yyerror("Step ID must match the loop variable ID.");
		}
		else { // same type
			// wrong assign op - assign real to int
			if (tempID1->type == 'i' && (tempID2->type == 'r' || $5.type == 'r')) {
				is_prog_valid = false;
				yyerror("Cannot assign real value into integer.");
			}
			else
				tempID1->is_init = true;
		}
	}
}
| ID ASSIGN ID MINUS NUM {
	symbol_table_entry* tempID1 = lookup(SymbolTable, $1.sval);
	symbol_table_entry* tempID2 = lookup(SymbolTable, $3.sval);
	if (tempID1 == NULL || tempID2 == NULL) {
		is_prog_valid = false;
		yyerror("ID is not declared!");
	}
	else {
		if (strcmp(tempID1->name, tempID2->name) != 0) { // not the same ID
			is_prog_valid = false;
			yyerror("Step ID must match the loop variable ID.");
		}
		else { // same type
			// wrong assign op - assign real to int
			if (tempID1->type == 'i' && (tempID2->type == 'r' || $5.type == 'r')) {
				is_prog_valid = false;
				yyerror("Cannot assign real value into integer.");
			}
			else
				tempID1->is_init = true;
		}
	}
}
| ID ASSIGN ID MUL NUM {
	symbol_table_entry* tempID1 = lookup(SymbolTable, $1.sval);
	symbol_table_entry* tempID2 = lookup(SymbolTable, $3.sval);
	if (tempID1 == NULL || tempID2 == NULL) {
		is_prog_valid = false;
		yyerror("ID is not declared!");
	}
	else {
		if (strcmp(tempID1->name, tempID2->name) != 0) { // not the same ID
			is_prog_valid = false;
			yyerror("Step ID must match the loop variable ID.");
		}
		else { // same type
			// wrong assign op - assign real to int
			if (tempID1->type == 'i' && (tempID2->type == 'r' || $5.type == 'r')) {
				is_prog_valid = false;
				yyerror("Cannot assign real value into integer.");
			}
			else
				tempID1->is_init = true;
		}
	}
}
| ID ASSIGN ID DIV NUM {
	symbol_table_entry* tempID1 = lookup(SymbolTable, $1.sval);
	symbol_table_entry* tempID2 = lookup(SymbolTable, $3.sval);
	if (tempID1 == NULL || tempID2 == NULL) {
		is_prog_valid = false;
		yyerror("ID is not declared!");
	}
	else {
		if (strcmp(tempID1->name, tempID2->name) != 0) { // not the same ID
			is_prog_valid = false;
			yyerror("Step ID must match the loop variable ID.");
		}
		else { // same type
			// wrong assign op - assign real to int
			if (tempID1->type == 'i' && (tempID2->type == 'r' || $5.type == 'r')) {
				is_prog_valid = false;
				yyerror("Cannot assign real value into integer.");
			}
			else
				tempID1->is_init = true;
		}
	}
}
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

/* Functions Implementations */
void yyerror(const char* msg) 
{ // Function to print the error
	fprintf(stderr, "\nError (line %d, col %d): %s\n", line-1, col, msg);
}

int next_reg()
{ // Function to get the next available register index
	current_reg++;
	return current_reg - 1;
}

void reset_reg()
{ // Function to reset the register index
	current_reg = 0;
}