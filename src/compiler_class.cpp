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

	parse_args();


	fill_builtin_symbol_table();
}

int Compiler::operator () ()
{
	__lexer.lex();

	printout(__lexer.next_tok()->str(), "\n");

	return 0;
}


void Compiler::parse_args()
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

}
