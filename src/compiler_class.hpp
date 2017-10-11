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
//#include "code_generator_class.hpp"

namespace flame_plus_plus
{

class Compiler
{
private:		// variables
	WarnError __we;
	Lexer __lexer;
	SymbolTable __sym_tbl;
	size_t __line_num = 0;



public:		// functions
	Compiler();





private:		// functions
	gen_getter_by_ref(we);
	gen_getter_by_ref(lexer);
	gen_getter_by_ref(sym_tbl);
	gen_getter_by_val(line_num);


};

}

#endif		// compiler_class_hpp
