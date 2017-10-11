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

void test_symbol_table();



int main(int argc, char** argv)
{
	test_symbol_table();

	return 0;
}


void test_symbol_table()
{
	using namespace flame_plus_plus;


	SymbolTable test;
	test.insert_or_assign(Symbol(&Tok::While, SymType::Keyword));
	test.insert_or_assign(Symbol(&Tok::If, SymType::Keyword));


	test.insert_or_assign(Symbol(&Tok::S8, SymType::BuiltinTypename));
	//test.insert_or_assign(Symbol(&Tok::S16, SymType::BuiltinTypename));
	//test.insert_or_assign(Symbol(&Tok::S32, SymType::BuiltinTypename));
	//test.insert_or_assign(Symbol(&Tok::S64, SymType::BuiltinTypename));

	test.insert_or_assign(Symbol(&Tok::U8, SymType::BuiltinTypename));
	//test.insert_or_assign(Symbol(&Tok::U16, SymType::BuiltinTypename));
	//test.insert_or_assign(Symbol(&Tok::U32, SymType::BuiltinTypename));
	//test.insert_or_assign(Symbol(&Tok::U64, SymType::BuiltinTypename));

	test.debug_print();
}
