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

	// File pointers
	FILE* err_fp;
	FILE* mips_fp;

	// Global variables
	symbol_table* SymbolTable;
	bool is_prog_valid = true;
	char current_type;


	// External variables (from lex file)
	extern int line;
	extern int col;

	void yyerror(const char* msg);
	extern int yylex();
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

%type <val> factor list declarlist decl declarations
%type <mytype> type

%%
program: PROGRAM ID {
	// Write to the mips file - headline and the title to define the variables
	fprintf(mips_fp, "#Ofir Nahshoni, 204616718\n#Eldar Garret, 312434293\n.data");
	
	// Create the symbol table
	SymbolTable = create_symbol_table(2);
}
START declarations stmtlist END { 
	if (is_prog_valid) {
		printf("\nsuccess\n");
		print(SymbolTable);
		free_symbol_table(SymbolTable);
	}
	
	else {
		// Delete the mips file
		printf("\nThere are errors\n");
		free_symbol_table(SymbolTable);
	}
}
| error ID START declarations stmtlist END {
	is_prog_valid = false; // Set Validation flag
	printf("program keywork is missing");
	free_symbol_table(SymbolTable);
}
| PROGRAM errmsg START declarations stmtlist END
| PROGRAM ID error declarations stmtlist END {
	is_prog_valid = false; // Set Validation flag
	printf("start keywork is missing");
	free_symbol_table(SymbolTable);
}
// | PROGRAM ID START declarations stmtlist error {
// 	is_prog_valid = false; // Set Validation flag
// 	yyerror("end keywork is missing");
// 	free_symbol_table(SymbolTable);
// }
;

errmsg: {
		printf("program ID (name of the program) is missing");
		is_prog_valid = false;
		free_symbol_table(SymbolTable);
	}
;

declarations: DECL declarlist cdecl
| error declarlist cdecl {
	is_prog_valid = false;
	printf("decl keyword is missing");
}
|
;

declarlist: declarlist decl
| decl
;

// rule1
decl: type ':' list ';' { $3.type = current_type; }
;

// rule2.1
list: ID ',' list {
	// Search ID in symbol table
	symbol_table_entry* tempSymID = lookup(SymbolTable, $1.sval);
	
	if (tempSymID) { // Error - ID is already in Symbol Table
		is_prog_valid = false;
		yyerror("ID is already defined");
	}
	else { // ID not found - Need to add to Symbol Table
		add_attribute(SymbolTable, $1.sval, current_type, false, false);
		$$.type = $3.type;
	}
}
// rule2.2
| ID {
	// Search ID in symbol table
	symbol_table_entry* tempID = lookup(SymbolTable, $1.sval);

	if (tempID) { // Error - ID is already in Symbol Table
		is_prog_valid = false;
		yyerror("ID already defined");
	}

	else { // Not found - Add to Symbol Table
		add_attribute(SymbolTable, $1.sval, current_type, false, false);
	}
}
;

// rule3.1
type: INT { 
	current_type = 'i';
	$$ = 'i';
}
| REAL { 
	current_type = 'r';
	$$ = 'r';
}
| STRING { 
	current_type = 's';
	$$ = 's';
}
;

cdecl: FINAL type ID ASSIGN NUM ';' cdecl {
	// Set to const
	symbol_table_entry* tempID = lookup(SymbolTable, $3.sval);

	if (tempID) { // Error already defined
		is_prog_valid = false;
		yyerror("ID already defined");
	}
	else {
		// Check if assigned value is from the same type
		if (current_type == $5.type)
			add_attribute(SymbolTable, $3.sval, current_type, true, true);
		else
			printf("Error in assignment of different type from the ID\n");
	}
}
| error type ID ASSIGN NUM ';' cdecl {
	is_prog_valid = false;
	yyerror("final keyword is missing");
}
| FINAL type error ASSIGN NUM ';' cdecl {
	is_prog_valid = false;
	yyerror("id is missing");
}
| FINAL type ID error NUM ';' cdecl {
	is_prog_valid = false;
	yyerror("assign symbol (=) is missing");
}
| FINAL type ID ASSIGN error ';' cdecl {
	is_prog_valid = false;
	yyerror("No value assigned to the ID");
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

assign_stmt: ID ASSIGN expression ';'
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

expression: expression PLUS term 
| term
;

term: term MUL factor
| factor
;

factor: '(' expression ')'
| ID
| NUM
;

%%
// Main function
int main(int argc, char* argv[])
{
	extern FILE* yyin;
	yyin = fopen(argv[1], "r");
	assert(yyin);

	// MIPS file - open to append
	mips_fp = fopen("mips_result.asm", "a");
	assert(mips_fp);

	// ErrorList file - open to append
	err_fp = fopen("errors_list.txt", "a");
	assert(err_fp);

	// Parsing by Bison
	do {
		printf("%d) ", line++);
		yyparse();
	} while(!feof(yyin));

	// Close the files - after parsing
	fclose(yyin);
	fclose(err_fp);
	fclose(mips_fp);

	if (!is_prog_valid)
		remove("mips_result.asm");
	else
		remove("errors_list.txt");


	return 0;
}

// Function to add error to the errors files
void yyerror(const char* msg)
{
	// Print errors to the screen
	fprintf(stderr, "Error (line %d, col %d): %s\n", line, col, msg);
	// Add error to the errors list file
	fprintf(err_fp, "Error (line %d, col %d): %s\n", line, col, msg);
}