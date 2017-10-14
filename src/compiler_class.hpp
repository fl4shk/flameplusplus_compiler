// This file is part of Flame++ Compiler.
// 
// Copyright 2017 by Andrew Clark (FL4SHK).
// 
// Flame++ Compiler is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
// 
// Flame++ Compiler is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Flame++ Compiler.  If not, see <http://www.gnu.org/licenses/>.


#ifndef compiler_class_hpp
#define compiler_class_hpp


#include "lexer_class.hpp"
#include "var_class.hpp"
//#include "code_generator_class.hpp"
#include "irnode_stuff.hpp"

namespace flame_plus_plus
{


class Compiler
{
private:		// variables
	WarnError __we;
	Lexer __lexer;
	SymbolTable __sym_tbl;
	ScopedIdentTable<Var> __var_tbl;
	size_t __line_num = 0;


	int __argc;
	char** __argv;



	s64 __last_lab = -1;


	// Used for break and continue.
	IrNode * __loop_start = nullptr, * __loop_end = nullptr;


	// Generated intermediate representation of code
	IrCode __code;



public:		// functions
	Compiler();

	void init(int s_argc, char** s_argv);

	int operator () ();


private:		// functions
	gen_getter_by_ref(we);
	gen_getter_by_ref(lexer);
	gen_getter_by_ref(sym_tbl);
	gen_getter_by_ref(var_tbl);
	gen_getter_by_val(line_num);
	gen_getter_by_val(argc);
	gen_getter_by_val(argv);
	gen_getter_and_setter_by_val(last_lab);
	inline const auto& code() const
	{
		return __code;
	}
	inline auto& code()
	{
		return __code;
	}

	inline void lex()
	{
		__lexer.lex();
	}

	inline auto next_char() const
	{
		return __lexer.next_char();
	}
	inline auto next_tok() const
	{
		return __lexer.next_tok();
	}
	inline const std::string& next_sym_str() const
	{
		return __lexer.next_sym_str();
	}
	inline auto next_num() const
	{
		return __lexer.next_num();
	}

	inline void make_scope()
	{
		sym_tbl().make_scope();
		var_tbl().make_scope();
	}
	inline void del_scope()
	{
		sym_tbl().del_scope();
		var_tbl().del_scope();
	}

	inline auto scope_lev() const
	{
		return __sym_tbl.scope_lev();
	}
	inline auto scope_num() const
	{
		return __sym_tbl.scope_num();
	}


	void handle_argv();
	void fill_builtin_symbol_table();

	inline void match(PTok tok)
	{
		if (next_tok() == tok)
		{
			lex();
		}
		else
		{
			we().expected_tokens(tok);
		}
	}

	void parse_program();
	void parse_statements();


	bool parse_scope(bool just_test=false);

	bool parse_one_statement(bool just_test=false);
	bool parse_one_loop_statement(bool just_test=false);


	bool parse_var_decl(bool just_test=false);
	bool parse_non_var_decl_statement(bool just_test=false);
	bool parse_non_var_decl_loop_statement(bool just_test=false);

	bool parse_while_loop_stmt(bool just_test=false);
	bool parse_if_stmt(bool just_test=false);
	bool parse_if_stmt_head(bool just_test=false);
	bool parse_else_stmt(bool just_test=false);
	bool parse_break_stmt(bool just_test=false);
	bool parse_continue_stmt(bool just_test=false);

	bool parse_assignment_stmt(bool just_test=false);




	IrNode* parse_expr();
	IrNode* __parse_expr_regular();
	IrNode* __parse_term();
	IrNode* __parse_factor();



	//inline IrNode* mk_lab()
	//{
	//	return __code.mk_lab(++__last_lab);
	//}

	void print_code() const;



};

}

#endif		// compiler_class_hpp
