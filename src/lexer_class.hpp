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

	void advance();
	void lex();

	inline auto next_char() const
	{
		return __next_char;
	}

	inline auto next_tok() const
	{
		return __next_tok;
	}
	inline const std::string& next_sym_str() const
	{
		return __next_sym_str;
	}
	inline s64 next_num() const
	{
		return __next_num;
	}


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

	inline auto set_next_char(int n_next_char)
	{
		__next_char = n_next_char;
		return next_char();
	}

	inline auto set_next_tok(PTok n_next_tok)
	{
		__next_tok = n_next_tok;
		return next_tok();
	}

	inline const std::string& set_next_sym_str
		(const std::string& n_next_sym_str)
	{
		__next_sym_str = n_next_sym_str;
		return next_sym_str();
	}
	inline const std::string& set_next_sym_str
		(std::string&& n_next_sym_str)
	{
		__next_sym_str = std::move(n_next_sym_str);
		return next_sym_str();
	}

	inline auto set_next_num(s64 n_next_num)
	{
		__next_num = n_next_num;
		return next_num();
	}

};

}



#endif		// lexer_class_hpp
