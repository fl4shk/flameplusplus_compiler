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


#ifndef irnode_stuff_hpp
#define irnode_stuff_hpp


#include "var_class.hpp"



namespace flame_plus_plus
{

enum class IrnOp
{
	Add,
	Sub,
	Mul,
	Div,
	Mod,

	// Save this for later
	//DivMod,

	BitAnd,
	BitOr,
	BitXor,
	BitNot,


	// Logical shift left
	Lsl,

	// Logical shift right
	Lsr,

	// Arithmetic shift right
	Asr,



	// ==
	Eq,

	// >
	Gt,

	// >=
	Ge,



	// ldu32op
	Ldu32,

	// ldu32xop
	Ldu32x,

	// ldu16op
	Ldu16,

	// ldu16xop
	Ldu16x,

	// ldu8op
	Ldu8,

	// ldu8xop
	Ldu8x,



	// lds32op
	Lds32,

	// lds32xop
	Lds32x,

	// lds16op
	Lds16,

	// lds16xop
	Lds16x,

	// lds8op
	Lds8,

	// lds8xop
	Lds8x,



	// st32op
	St32,

	// st32xop
	St32x,

	// st16op
	St16,

	// st16xop
	St16x,

	// st8op
	St8,

	// st8xop
	St8x,



	// const
	Const,

	// labop
	Lab,

	// selop
	Sel,

	// kill
	Kill,

	Unknown
};

class IrNode
{
public:		// constants
	static constexpr size_t max_num_args = 2;
	static constexpr s64 blank_int_val = -1;

public:		// variables
	// Linked list stuff
	IrNode * next, * prev;

	IrnOp op = IrnOp::Unknown;

	// A link to the variable table
	Var* varg = nullptr;

	// For const()
	s64 carg = blank_int_val;

	IrNode* irnarg[max_num_args];

	// For lab() and sel()
	s64 larg[max_num_args];

public:		// functions
	inline IrNode()
	{
		init_array(irnarg, nullptr, nullptr);
		init_array(larg, blank_int_val, blank_int_val);
	}
};


// IrNode List, and also an optimizer
class IrCode
{
public:		// variables
	IrNode head;

public:		// functions
	IrCode();
	~IrCode();



	int ir_to_index(IrNode* irn) const;


	IrNode* mkirn();
	void rmirn(IrNode* irn);




	std::ostream& osprint_irn(std::ostream& os, IrNode* p) const;


private:		// functions
	inline void __delink_irn(IrNode* irn)
	{
		irn->prev->next = irn->next;
		irn->next->prev = irn->prev;
	}

	inline void __relink_irn(IrNode* irn, IrNode* to_link_after)
	{
		IrNode* old_next = to_link_after->next;

		to_link_after->next = irn;
		irn->prev = to_link_after;
		irn->next = old_next;
		old_next->prev = irn;
	}

};

}



#endif		// irnode_stuff_hpp
