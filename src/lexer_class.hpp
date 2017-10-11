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


#ifndef lexer_class_hpp
#define lexer_class_hpp

#include "misc_includes.hpp"
#include "tokens_and_stuff.hpp"

#include "warn_error_class.hpp"
#include "symbol_table_class.hpp"


namespace flame_plus_plus
{

class Lexer
{
private:		// variables
	WarnError* __we = nullptr;

	SymbolTable* __sym_tbl = nullptr;
	size_t* __line_num = nullptr;




	int __next_char = ' ';
	PTok __next_tok = nullptr;
	std::string __next_sym_str;
	s64 __next_num = -1;



public:		// functions
	Lexer(WarnError* s_we, SymbolTable* s_sym_tbl, size_t* s_line_num);

	PTok advance();
	PTok lex();

	gen_getter_by_val(next_char);
	gen_getter_by_val(next_tok);
	gen_getter_by_con_ref(next_sym_str);
	gen_getter_by_val(next_num);


private:		// functions
	inline auto& we()
	{
		return *__we;
	}

	inline auto& sym_tbl()
	{
		return *__sym_tbl;
	}

	inline auto line_num()
	{
		return *__line_num;
	}

	inline void set_line_num(size_t n_line_num)
	{
		*__line_num = n_line_num;
	}

	gen_setter_by_val(next_char);
	gen_setter_by_val(next_tok);
	gen_setter_by_con_ref(next_sym_str);
	gen_setter_by_val(next_num);

};

}



#endif		// lexer_class_hpp
