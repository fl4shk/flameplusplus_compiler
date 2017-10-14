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


#include "compiler_class.hpp"

namespace flame_plus_plus
{

Compiler::Compiler()
	: __we(&__line_num),
	__lexer(&__we, &__sym_tbl, &__line_num)
{
}


void Compiler::init(int s_argc, char** s_argv)
{
	__argc = s_argc;
	__argv = s_argv;

	handle_argv();


	fill_builtin_symbol_table();
}

int Compiler::operator () ()
{
	//while ((next_tok() != &Tok::Eof)
	//	&& (next_tok() != &Tok::Bad))
	//{
	//	lex();

	//	//printout(next_tok()->str(), "\n");
	//}

	lex();

	//// For user idents
	//make_scope();

	//// Parse
	//parse_program();



	// For testing
	parse_expr();

	print_code();

	return 0;
}


void Compiler::handle_argv()
{
	if (argc() != 1)
	{
		printerr("Usage:  ", argv()[0], "\n");
		exit(1);
	}
}

void Compiler::fill_builtin_symbol_table()
{
	#define TOKEN_STUFF(varname, value) \
		sym_tbl().insert_or_assign(Symbol(&Tok::varname, \
			SymType::Keyword));

	LIST_OF_KEYWORD_TOKENS(TOKEN_STUFF);
	
	#undef TOKEN_STUFF


	#define TOKEN_STUFF(varname, value) \
		sym_tbl().insert_or_assign(Symbol(&Tok::varname, \
			SymType::BuiltinTypename));

	LIST_OF_DEFAULT_INT_TYPENAME_TOKENS(TOKEN_STUFF);

	#undef TOKEN_STUFF

	//sym_tbl().debug_print();
}

void Compiler::parse_program()
{
	parse_statements();
}

void Compiler::parse_statements()
{
	if (parse_scope(true))
	{
		parse_scope();
	}
	else
	{
		while (parse_var_decl(true))
		{
			parse_var_decl();
		}
		while (parse_non_var_decl_statement(true))
		{
			parse_non_var_decl_statement();
		}
	}
}

bool Compiler::parse_scope(bool just_test)
{
	if (parse_one_statement(true))
	{
		if (!just_test)
		{
			make_scope();
			parse_one_statement();
			del_scope();
		}
		return true;
	}
	else if (next_tok() == &Tok::LBrace)
	{
		if (!just_test)
		{
			match(&Tok::LBrace);
			make_scope();

			parse_statements();

			del_scope();
			match(&Tok::RBrace);
		}
		return true;
	}
	else
	{
		if (!just_test)
		{
			we().err("parse_scope():  Unexpected token");
		}
		return false;
	}
}


bool Compiler::parse_one_statement(bool just_test)
{
	if (parse_var_decl(true))
	{
		if (!just_test)
		{
			parse_var_decl();
		}
		return true;
	}
	else if (parse_non_var_decl_statement(true))
	{
		if (!just_test)
		{
			parse_non_var_decl_statement();
		}
		return true;
	}
	else
	{
		if (!just_test)
		{
			we().err("parse_one_statement():  Unexpected token");
		}
		return false;
	}
}

bool Compiler::parse_var_decl(bool just_test)
{
	Symbol* type_sym = sym_tbl().find(next_sym_str());

	// Adjust this later for user-defined types
	if (type_sym->type() != SymType::BuiltinTypename)
	{
		if (just_test)
		{
			return false;
		}
		else
		{
			we().err("parse_var_decl():  Unexpected token");
		}
	}
	if (just_test)
	{
		return true;
	}

	lex();

	{
	if (next_tok() != &Tok::Ident)
	{
		we().expected_tokens(&Tok::Ident);
	}

	Symbol* sym = sym_tbl().find(next_sym_str());
	sym->set_type(SymType::VarName);

	// No arrays for now
	var_tbl().insert_or_assign(Var(type_sym, sym, scope_lev(), scope_num(),
		0));

	lex();
	}

	while (next_tok() == &Tok::Comma)
	{
		match(&Tok::Comma);

		if (next_tok() != &Tok::Ident)
		{
			we().expected_tokens(&Tok::Ident);
		}

		Symbol* sym = sym_tbl().find(next_sym_str());
		sym->set_type(SymType::VarName);

		// No arrays for now
		var_tbl().insert_or_assign(Var(type_sym, sym, scope_lev(),
			scope_num(), 0));

		lex();
	}

	match(&Tok::Semicolon);

	return true;
}


bool Compiler::parse_non_var_decl_statement(bool just_test)
{
	if (parse_while_loop_stmt(true))
	{
		if (!just_test)
		{
			parse_while_loop_stmt();
		}
		return true;
	}
	else if (parse_if_stmt(true))
	{
		if (!just_test)
		{
			parse_if_stmt();
		}
		return true;
	}
	else if (parse_assignment_stmt(true))
	{
		if (!just_test)
		{
			parse_assignment_stmt();
		}
		return true;
	}
	else
	{
		if (!just_test)
		{
			we().err("parse_non_var_decl_statement():  Unexpected token");
		}
		return false;
	}
}

bool Compiler::parse_while_loop_stmt(bool just_test)
{
	if (next_tok() != &Tok::While)
	{
		if (!just_test)
		{
			we().err("parse_while_loop_stmt():  Unexpected token");
		}
		return false;
	}
	if (just_test)
	{
		return true;
	}

}
bool Compiler::parse_if_stmt(bool just_test)
{
	return false;
}
bool Compiler::parse_if_stmt_head(bool just_test)
{
	return false;
}
bool Compiler::parse_else_stmt(bool just_test)
{
	return false;
}
bool Compiler::parse_break_stmt(bool just_test)
{
	return false;
}
bool Compiler::parse_continue_stmt(bool just_test)
{
	return false;
}
bool Compiler::parse_assignment_stmt(bool just_test)
{
	return false;
}



IrNode* Compiler::parse_expr()
{
	IrNode* ret = nullptr;

	ret = __parse_expr_regular();

	return ret;
}
IrNode* Compiler::__parse_expr_regular()
{
	IrNode* ret = nullptr;

	if (next_tok() == &Tok::Plus)
	{
		lex();
	}
	else if (next_tok() == &Tok::Minus)
	{
		lex();

		ret = code().mk_binop(IrnOp::Sub, code().mk_const(0), 
			__parse_term());
	}
	else
	{
		ret = __parse_term();
	}

	while (any_tok_matches(next_tok(), &Tok::Plus, &Tok::Minus))
	{
		const bool minus = (next_tok() == &Tok::Minus);

		lex();

		if (minus)
		{
			ret = code().mk_binop(IrnOp::Sub, ret, __parse_term());
		}
		else
		{
			ret = code().mk_binop(IrnOp::Add, ret, __parse_term());
		}
	}

	return ret;
}
IrNode* Compiler::__parse_term()
{
	IrNode* ret = nullptr;

	ret = __parse_factor();

	//const auto some_next_tok = some_parse_vec.at(index).next_tok;

	while (any_tok_matches(next_tok(), &Tok::Mul, &Tok::Div, &Tok::Mod,
		&Tok::BitAnd, &Tok::BitOr, &Tok::BitXor,
		&Tok::BitShL, &Tok::BitShR))
	{
		const auto old_next_tok = next_tok();

		lex();

		if (old_next_tok == &Tok::Mul)
		{
			//ret *= __handle_factor(some_parse_vec, index);
			ret = code().mk_binop(IrnOp::Mul, ret, __parse_factor());
		}
		else if (old_next_tok == &Tok::Div)
		{
			//ret /= __handle_factor(some_parse_vec, index);
			ret = code().mk_binop(IrnOp::SgnDiv, ret, __parse_factor());
		}
		else if (old_next_tok == &Tok::Mod)
		{
			ret = code().mk_binop(IrnOp::SgnMod, ret, __parse_factor());
		}
		else if (old_next_tok == &Tok::BitAnd)
		{
			//ret &= __handle_factor(some_parse_vec, index);
			ret = code().mk_binop(IrnOp::BitAnd, ret, __parse_factor());
		}
		else if (old_next_tok == &Tok::BitOr)
		{
			//ret |= __handle_factor(some_parse_vec, index);
			ret = code().mk_binop(IrnOp::BitOr, ret, __parse_factor());
		}
		else if (old_next_tok == &Tok::BitXor)
		{
			//ret ^= __handle_factor(some_parse_vec, index);
			ret = code().mk_binop(IrnOp::BitXor, ret, __parse_factor());
		}
		else if (old_next_tok == &Tok::BitShL)
		{
			//ret <<= __handle_factor(some_parse_vec, index);
			ret = code().mk_binop(IrnOp::Lsl, ret, __parse_factor());
		}
		else if (old_next_tok == &Tok::BitShR)
		{
			//ret >>= __handle_factor(some_parse_vec, index);
			ret = code().mk_binop(IrnOp::Asr, ret, __parse_factor());
		}
	}
	return ret;

}
IrNode* Compiler::__parse_factor()
{
	IrNode* ret = nullptr;

	if (next_tok() == &Tok::NatNum)
	{
		ret = code().mk_const(next_num());
		lex();
		return ret;
	}
	//else if (next_tok() == &Tok::Ident)
	//{
	//}

	else if (next_tok() == &Tok::LParen)
	{
		lex();

		ret = parse_expr();

		match(&Tok::RParen);
	}
	else
	{
		we().err("Invalid expression");
	}


	return ret;

}


void Compiler::print_code() const
{
	for (auto irn=code().head.next; irn!=&code().head; irn=irn->next)
	{
		code().osprint_irn(cout, irn);
		printout("\n");
	}
}

}
