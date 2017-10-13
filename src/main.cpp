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

flame_plus_plus::Compiler compiler;

void test_ir_code();


int main(int argc, char** argv)
{
	//compiler.init(argc, argv);
	//return compiler();

	test_ir_code();

	return 0;
}


//void test_symbol_table()
//{
//	using namespace flame_plus_plus;
//
//
//	SymbolTable test;
//	test.insert_or_assign(Symbol(&Tok::While, SymType::Keyword));
//
//
//	test.insert_or_assign(Symbol(&Tok::U8, SymType::BuiltinTypename));
//
//
//	test.make_scope();
//	test.make_scope();
//	test.insert_or_assign(Symbol("aaaaa", &Tok::Ident, SymType::VarName));
//
//	test.debug_print();
//
//	printout("\n");
//
//	test.del_scope();
//	test.insert_or_assign(Symbol("aaaaa", &Tok::Ident, SymType::VarName));
//
//
//	test.debug_print();
//}


void test_ir_code()
{
	using namespace flame_plus_plus;

	IrCode code;

	auto node0 = code.mkirn();
	auto node1 = code.mkirn();
	auto node2 = code.mkirn();

	node0->op = IrnOp::Const;
	node0->carg = 9000;

	node1->op = IrnOp::Const;
	node1->carg = 74;

	node2->op = IrnOp::Add;
	node2->irnarg[0] = node0;
	node2->irnarg[1] = node1;

	for (auto irn=code.head.next; irn!=&code.head; irn=irn->next)
	{
		code.osprint_irn(cout, irn);
		printout("\n");
	}
}
