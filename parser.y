%{
	// Includes
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <assert.h>
	#include <stdbool.h>
	#include "symbol_table.h"
	#include "my_structs.h"
	#include "mips_trans.h"

	// Global variables
	symbol_table* SymbolTable;
	char current_type;
	bool is_prog_valid = true;

	// External variables (from lex file)
	extern int line;
	extern int col;
	extern int yylex(void);
	extern FILE* yyin;
	FILE* mips_file;

	// Functions declarations
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

%type <val> list
%type <val> declarlist
%type <val> decl
%type <val> cdecl
%type <val> declarations
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
	// Header of mips_file
	generate_mips_header(mips_file);
}
START declarations stmtlist END { 
	if (is_prog_valid) {
		// CMD
		printf("\n--------------------------\nResult: ");
		printf("Success\n");
		print(SymbolTable);
		free_symbol_table(SymbolTable);

		// Terminate program - mips
		generate_mips_footer(mips_file);
	}
	else {
		// CMD
		printf("\n--------------------------\nResult: ");
		printf("Not Valid\n");
		free_symbol_table(SymbolTable);
	}
}
;
	
declarations: DECL { 
		generate_mips_data_section(mips_file); // .data
	} declarlist cdecl { 
			generate_mips_text_section(mips_file); // .text
		}
|
;

declarlist: declarlist decl
| decl
;

decl: type { current_type = $1.type; } ':' list ';' { // r1 
	// printf("\nr1\n");
}

list: ID ',' list { // r2.1
	symbol_table_entry* tempID = lookup(SymbolTable, $1.sval);
	if (tempID) {
		is_prog_valid = false;
		yyerror("ID is already defined");
	}
	else {
		// printf("\nr2.1\n");
		add_attribute(SymbolTable, $1.sval, current_type, false, false);
		translate_declar(mips_file, current_type, $1.sval, "0");
	}
}
| ID { // r2.2
	symbol_table_entry* tempID = lookup(SymbolTable, $1.sval);
	if (tempID) {
		is_prog_valid = false;
		yyerror("ID already defined");
	}
	else {
		// printf("\nr2.2\n");
		add_attribute(SymbolTable, $1.sval, current_type, false, false);
		translate_declar(mips_file, current_type, $1.sval, "0");
	}
}
;

cdecl: FINAL type ID ASSIGN NUM ';' cdecl {
	current_type = $2.type;
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
		else if ($2.type == 'i' && $5.type == 'r') {
			is_prog_valid = false;
			yyerror("Cannot assign real value to int.");
		}
		else {
			add_attribute(SymbolTable, $3.sval, $2.type, true, true);
			translate_declar(mips_file, current_type, $3.sval, $5.sval);
		}
	}
}
|
;

type: INT { $$.type = 'i'; }
| REAL { $$.type = 'r'; }
| STRING { $$.type = 's'; }
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
		else {
			tempID->is_init = true;
			// Generate reg_name
			char* reg_name = generate_reg_name('s');
			// mips
			translate_assignment(mips_file, tempID->name, $3.sval, 's', reg_name);
			// free register name
			free(reg_name);
		}

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
		yyerror("Cannot execute input method, ID is not declared.");
	}
	else {
		if (tempID->is_const) {
			is_prog_valid = false;
			yyerror("You cannot change value of const (final) variable.");
		}
		else {
			tempID->is_init = true;
			// mips - input
			translate_input(mips_file, tempID->name, tempID->type);
		}
	}
}
;

out_stmt: OUT '(' expression ')' ';' { // int or real
	translate_output(mips_file, $3.sval, $3.type);
}
| OUT '(' SENTENCE ')' ';' { // string
	translate_output(mips_file, $3.sval, $3.type);
}
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
		else {
			tempID->is_init = true;
			// Generate reg_name
			char* reg_name = generate_reg_name(tempID->type);
			// mips
			translate_assignment(mips_file, tempID->name, $3.sval, tempID->type, reg_name);
			// free register name
			free(reg_name);
		}
	}
}
;

control_stmt: IF '(' bool_expr ')' THEN stmt ELSE stmt
| WHILE '(' bool_expr ')' stmt_block
| FOREACH ID ASSIGN NUM TILL NUM WITH step {
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
} stmt
| FOREACH ID ASSIGN NUM TILL ID WITH step {
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
} stmt
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

// foreach i = 0 till 7 with i = i + 1
step: ID ASSIGN ID PLUS NUM {
	if (strcmp($1.sval, $3.sval) != 0) { // Infinite loop
		is_prog_valid = false;
		yyerror("Danger to Infinite loop !! Step ID must match the loop variable ID.");
	}
	else {
		symbol_table_entry* tempID1 = lookup(SymbolTable, $1.sval);
		if (tempID1 == NULL) {
			is_prog_valid = false;
			yyerror("ID is not declared!");
		}
		else
			tempID1->is_init = true;
	}
}
| ID ASSIGN ID MINUS NUM {
	if (strcmp($1.sval, $3.sval) != 0) { // Infinite loop
		is_prog_valid = false;
		yyerror("Danger to Infinite loop !! Step ID must match the loop variable ID.");
	}
	else {
		symbol_table_entry* tempID1 = lookup(SymbolTable, $1.sval);
		if (tempID1 == NULL) {
			is_prog_valid = false;
			yyerror("ID is not declared!");
		}
		else
			tempID1->is_init = true;
	}
}
| ID ASSIGN ID MUL NUM {
	if (strcmp($1.sval, $3.sval) != 0) { // Infinite loop
		is_prog_valid = false;
		yyerror("Danger to Infinite loop !! Step ID must match the loop variable ID.");
	}
	else {
		symbol_table_entry* tempID1 = lookup(SymbolTable, $1.sval);
		if (tempID1 == NULL) {
			is_prog_valid = false;
			yyerror("ID is not declared!");
		}
		else
			tempID1->is_init = true;
	}
}
| ID ASSIGN ID DIV NUM { // i = i / 4
	if (strcmp($1.sval, $3.sval) != 0) { // Infinite loop
		is_prog_valid = false;
		yyerror("Danger to Infinite loop !! Step ID must match the loop variable ID.");
	}
	else {
		symbol_table_entry* tempID1 = lookup(SymbolTable, $1.sval);
		if (tempID1 == NULL) {
			is_prog_valid = false;
			yyerror("ID is not declared!");
		}
		else
			tempID1->is_init = true;
	}
}
;

bool_expr: bool_expr OR bool_term
| bool_term
;

bool_term: bool_term AND bool_factor
| bool_factor
;

bool_factor: '!' '(' bool_factor ')' /* -> NOT bool_factor */
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
| term { $$.type = $1.type; $$.sval = $1.sval; }
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
| factor {$$.type = $1.type; $$.sval = $1.sval;}
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
			$$.sval = $1.sval;
		}
	}
}
| NUM {
	current_type = $1.type; // 'r' or 'i'
	$$.type = current_type;
	$$.sval = $1.sval;
}
;

%%
// Main function
int main(int argc, char* argv[])
{
	yyin = fopen(argv[1], "r");
	assert(yyin);

	// Open mips file for write mode
    mips_file = fopen("mips_res.asm", "w");
    assert(mips_file);

	printf("%d) ", line++);

	do {
		yyparse();
	} while(!feof(yyin));

	fclose(yyin);
	fclose(mips_file);

	return 0;
}

/* Functions Implementations */
void yyerror(const char* msg) 
{ // Function to print the error
	fprintf(stderr, "\nError (line %d, col %d): %s\n", line-1, col, msg);
}