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


#include "irnode_classes.hpp"

namespace flame_plus_plus
{

bool IrNode::is_binop() const
{
	return false;
}
bool IrNode::is_commutative_binop() const
{
	return false;
}
bool IrNode::is_non_commutative_binop() const
{
	return false;
}
bool IrNode::is_unsigned_compare_binop() const
{
	return false;
}
bool IrNode::is_signed_compare_binop() const
{
	return false;
}

bool IrNode::is_unop() const
{
	return false;
}

bool IrNode::is_ldst_32() const
{
	return false;
}
bool IrNode::is_ldst_16() const
{
	return false;
}
bool IrNode::is_ldst_8() const
{
	return false;
}


bool IrNode::is_ldop() const
{
	return false;
}
bool IrNode::is_ldxop() const
{
	return false;
}
bool IrNode::is_stop() const
{
	return false;
}
bool IrNode::is_stxop() const
{
	return false;
}


bool IrNode::is_unsigned_ldop() const
{
	return false;
}
bool IrNode::is_signed_ldop() const
{
	return false;
}
bool IrNode::is_unsigned_ldxop() const
{
	return false;
}
bool IrNode::is_signed_ldxop() const
{
	return false;
}

bool IrNode::is_const() const
{
	return false;
}
bool IrNode::is_lab() const
{
	return false;
}
bool IrNode::is_condjump() const
{
	return false;
}
bool IrNode::is_call() const
{
	return false;
}
bool IrNode::is_clean() const
{
	return false;
}


bool IrBinOpNode::is_binop() const
{
	//return anything_matches(__op, IrnBinOp::Add, IrnBinOp::Sub, 
	//	IrnBinOp::Mul,

	//	IrnBinOp::UnsgnDiv, IrnBinOp::UnsgnMod,
	//	IrnBinOp::SgnDiv, IrnBinOp::SgnMod,

	//	IrnBinOp::BitAnd, IrnBinOp::BitOr, IrnBinOp::BitXor,

	//	IrnBinOp::Lsl, IrnBinOp::Lsr, IrnBinOp::Asr,

	//	IrnBinOp::Eq, 
	//	IrnBinOp::UnsgnGt, IrnBinOp::UnsgnGe, 
	//	IrnBinOp::SgnGt, IrnBinOp::SgnGe);


	// Error checking to make sure I've done this right
	if (!(is_commutative_binop() || is_non_commutative_binop()))
	{
		printerr("IrBinOpNode::is_binop():  Eek 1!\n");
		exit(1);
	}
	else if (is_commutative_binop() && is_non_commutative_binop())
	{
		printerr("IrBinOpNode::is_binop():  Eek 2!\n");
		exit(1);
	}

	return true;
}

bool IrBinOpNode::is_commutative_binop() const
{
	return anything_matches(get_irn_bin_op(), 
		IrnBinOp::Add, IrnBinOp::Mul,

		IrnBinOp::BitAnd, IrnBinOp::BitOr, IrnBinOp::BitXor,

		IrnBinOp::Eq);
}

bool IrBinOpNode::is_non_commutative_binop() const
{
	return anything_matches(get_irn_bin_op(), IrnBinOp::Sub, 
		IrnBinOp::UnsgnDiv, IrnBinOp::UnsgnMod,
		IrnBinOp::SgnDiv, IrnBinOp::SgnMod,

		IrnBinOp::Lsl, IrnBinOp::Lsr, IrnBinOp::Asr,
		
		IrnBinOp::UnsgnGt, IrnBinOp::UnsgnGe, 
		IrnBinOp::SgnGt, IrnBinOp::SgnGe);
}
bool IrBinOpNode::is_unsigned_compare_binop() const
{
	return anything_matches(get_irn_bin_op(), 
		IrnBinOp::UnsgnGt, IrnBinOp::UnsgnGe);
}
bool IrBinOpNode::is_signed_compare_binop() const
{
	return anything_matches(get_irn_bin_op(), 
		IrnBinOp::SgnGt, IrnBinOp::SgnGe);
}

bool IrUnOpNode::is_unop() const
{
	return anything_matches(get_irn_un_op(), 
		IrnUnOp::Negate, IrnUnOp::BitNot, IrnUnOp::LogNot);
}


bool IrLdStNode::is_ldst_32() const
{
	return anything_matches(get_irn_ldst_op(), 
		IrnLdStOp::Ldu32, IrnLdStOp::Ldu32x,
		IrnLdStOp::Lds32, IrnLdStOp::Lds32x,
		IrnLdStOp::St32);
}
bool IrLdStNode::is_ldst_16() const
{
	return anything_matches(get_irn_ldst_op(), 
		IrnLdStOp::Ldu16, IrnLdStOp::Ldu16x,
		IrnLdStOp::Lds16, IrnLdStOp::Lds16x,
		IrnLdStOp::St16);
}
bool IrLdStNode::is_ldst_8() const
{
	return anything_matches(get_irn_ldst_op(), 
		IrnLdStOp::Ldu8, IrnLdStOp::Ldu8x,
		IrnLdStOp::Lds8, IrnLdStOp::Lds8x,
		IrnLdStOp::St8);
}

bool IrLdStNode::is_ldop() const
{
	return anything_matches(get_irn_ldst_op(), 
		IrnLdStOp::Ldu64, IrnLdStOp::Ldu32, 
		IrnLdStOp::Ldu16, IrnLdStOp::Ldu8,

		IrnLdStOp::Lds64, IrnLdStOp::Lds32, 
		IrnLdStOp::Lds16, IrnLdStOp::Lds8);
}
bool IrLdStNode::is_ldxop() const
{
	return anything_matches(get_irn_ldst_op(), 
		IrnLdStOp::Ldu64x, IrnLdStOp::Ldu32x, 
		IrnLdStOp::Ldu16x, IrnLdStOp::Ldu8x,

		IrnLdStOp::Lds64x, IrnLdStOp::Lds32x, 
		IrnLdStOp::Lds16x, IrnLdStOp::Lds8x);
}
bool IrLdStNode::is_stop() const
{
	return anything_matches(get_irn_ldst_op(), 
		IrnLdStOp::St64, IrnLdStOp::St32, 
		IrnLdStOp::St16, IrnLdStOp::St8);
}
bool IrLdStNode::is_stxop() const
{
	return anything_matches(get_irn_ldst_op(), 
		IrnLdStOp::St64x, IrnLdStOp::St32x, 
		IrnLdStOp::St16x, IrnLdStOp::St8x);
}


bool IrLdStNode::is_unsigned_ldop() const
{
	return anything_matches(get_irn_ldst_op(), 
		IrnLdStOp::Ldu64, IrnLdStOp::Ldu32, 
		IrnLdStOp::Ldu16, IrnLdStOp::Ldu8);
}
bool IrLdStNode::is_signed_ldop() const
{
	return anything_matches(get_irn_ldst_op(), 
		IrnLdStOp::Lds64, IrnLdStOp::Lds32, 
		IrnLdStOp::Lds16, IrnLdStOp::Lds8);
}
bool IrLdStNode::is_unsigned_ldxop() const
{
	return anything_matches(get_irn_ldst_op(), 
		IrnLdStOp::Ldu64x, IrnLdStOp::Ldu32x, 
		IrnLdStOp::Ldu16x, IrnLdStOp::Ldu8x);
}
bool IrLdStNode::is_signed_ldxop() const
{
	return anything_matches(get_irn_ldst_op(), 
		IrnLdStOp::Lds64x, IrnLdStOp::Lds32x, 
		IrnLdStOp::Lds16x, IrnLdStOp::Lds8x);
}
bool IrConstNode::is_const() const
{
	return true;
}

bool IrLabNode::is_lab() const
{
	return true;
}

bool IrCondJumpNode::is_condjump() const
{
	return true;
}

//bool IrCallNode::is_call() const
//{
//	return true;
//}

bool IrCleanNode::is_clean() const
{
	return true;
}

}
