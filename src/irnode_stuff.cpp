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


#include "irnode_stuff.hpp"

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
	return anything_matches(__op, IrnBinOp::Add, IrnBinOp::Mul,

		IrnBinOp::BitAnd, IrnBinOp::BitOr, IrnBinOp::BitXor,

		IrnBinOp::Eq);
}

bool IrBinOpNode::is_non_commutative_binop() const
{
	return anything_matches(__op, IrnBinOp::Sub, 
		IrnBinOp::UnsgnDiv, IrnBinOp::UnsgnMod,
		IrnBinOp::SgnDiv, IrnBinOp::SgnMod,

		IrnBinOp::Lsl, IrnBinOp::Lsr, IrnBinOp::Asr,
		
		IrnBinOp::UnsgnGt, IrnBinOp::UnsgnGe, 
		IrnBinOp::SgnGt, IrnBinOp::SgnGe);
}
bool IrBinOpNode::is_unsigned_compare_binop() const
{
	return any_irnop_matches(op, IrnBinOp::UnsgnGt, IrnOp::UnsgnGe);
}
bool IrBinOpNode::is_signed_compare_binop() const
{
	return any_irnop_matches(op, IrnBinOp::SgnGt, IrnOp::SgnGe);
}

bool IrUnOpNode::is_unop() const
{
	return anything_matches(__op, IrnUnOp::Negate, IrnUnOp::BitNot,
		IrnUnOp::LogNot);
}


bool IrLdStNode::is_ldst_32() const
{
	return anything_matches(__op, IrnLdStOp::Ldu32, IrnLdStOp::Ldu32x,
		IrnLdStOp::Lds32, IrnLdStOp::Lds32x,
		IrnLdStOp::St32);
}
bool IrLdStNode::is_ldst_16() const
{
	return anything_matches(__op, IrnLdStOp::Ldu16, IrnLdStOp::Ldu16x,
		IrnLdStOp::Lds16, IrnLdStOp::Lds16x,
		IrnLdStOp::St16);
}
bool IrLdStNode::is_ldst_8() const
{
	return anything_matches(__op, IrnLdStOp::Ldu8, IrnLdStOp::Ldu8x,
		IrnLdStOp::Lds8, IrnLdStOp::Lds8x,
		IrnLdStOp::St8);
}

bool IrLdStNode::is_ldop() const
{
	return anything_matches(__op, 
		IrnLdStOp::Ldu64, IrnLdStOp::Ldu32, 
		IrnLdStOp::Ldu16, IrnLdStOp::Ldu8,

		IrnLdStOp::Lds64, IrnLdStOp::Lds32, 
		IrnLdStOp::Lds16, IrnLdStOp::Lds8);
}
bool IrLdStNode::is_ldxop() const
{
	return anything_matches(__op, 
		IrnLdStOp::Ldu64x, IrnLdStOp::Ldu32x, 
		IrnLdStOp::Ldu16x, IrnLdStOp::Ldu8x,

		IrnLdStOp::Lds64x, IrnLdStOp::Lds32x, 
		IrnLdStOp::Lds16x, IrnLdStOp::Lds8x);
}
bool IrLdStNode::is_stop() const
{
	return anything_matches(__op, IrnLdStOp::St64, IrnLdStOp::St32, 
		IrnLdStOp::St16, IrnLdStOp::St8);
}
bool IrLdStNode::is_stxop() const
{
	return anything_matches(__op, IrnLdStOp::St64x, IrnLdStOp::St32x, 
		IrnLdStOp::St16x, IrnLdStOp::St8x);
}


bool IrLdStNode::is_unsigned_ldop() const
{
	return anything_matches(__op, IrnLdStOp::Ldu64, IrnLdStOp::Ldu32, 
		IrnLdStOp::Ldu16, IrnLdStOp::Ldu8);
}
bool IrLdStNode::is_signed_ldop() const
{
	return anything_matches(__op, IrnLdStOp::Lds64, IrnLdStOp::Lds32, 
		IrnLdStOp::Lds16, IrnLdStOp::Lds8);
}
bool IrLdStNode::is_unsigned_ldxop() const
{
	return anything_matches(__op, IrnLdStOp::Ldu64x, IrnLdStOp::Ldu32x, 
		IrnLdStOp::Ldu16x, IrnLdStOp::Ldu8x);
}
bool IrLdStNode::is_signed_ldxop() const
{
	return anything_matches(__op, IrnLdStOp::Lds64x, IrnLdStOp::Lds32x, 
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

IrCode::IrCode()
{
	head.next = &head;
	head.prev = &head;
}

IrCode::~IrCode()
{
	while (head.next != &head)
	{
		rmirn(head.prev);
	}
}

int IrCode::irn_to_index(IrNode* irn) const
{
	int ret = 0;

	for (IrNode* p=head.next; p!=&head; p=p->next)
	{
		if (p == irn)
		{
			return ret;
		}
		++ret;
	}

	return -1;
}

IrNode* IrCode::mkirn()
{
	IrNode* p = new IrNode();

	p->next = &head;
	p->prev = head.prev;
	p->prev->next = p;
	head.prev = p;

	return p;
}
void IrCode::rmirn(IrNode* irn)
{
	//printout("Removing this Irn:  ");
	//osprint_irn(cout, irn);
	//printout("\n");
	__delink_irn(irn);
	delete irn;
}

IrNode* IrCode::mk_binop(IrnBinOp __op, IrNode* a, IrNode* b, bool unsgn)
{
	{
	//IrNode temp;
	//temp.get_op() = __op;

	//if (!temp.is_binop())
	//{
	//	printerr("IrCode::mk_binop():  Eek!\n");
	//	exit(1);
	//}

	// Constant folding
	if (a->is_const() && b->is_const())
	{
		u64 temp_u;
		s64 temp_s;

		switch (__op)
		{
			case IrnBinOp::Add:
				temp_u = (static_cast<u64>(a->get_const_arg()))
					+ (static_cast<u64>(b->get_const_arg()));
				temp_s = a->get_const_arg() + b->get_const_arg();
				break;

			case IrnBinOp::Sub:
				temp_u = (static_cast<u64>(a->get_const_arg()))
					- (static_cast<u64>(b->get_const_arg()));
				temp_s = a->get_const_arg() - b->get_const_arg();
				break;

			case IrnBinOp::Mul:
				temp_u = (static_cast<u64>(a->get_const_arg()))
					* (static_cast<u64>(b->get_const_arg()));
				temp_s = a->get_const_arg() * b->get_const_arg();
				break;

			case IrnBinOp::UnsgnDiv:
				temp_u = (static_cast<u64>(a->get_const_arg()))
					/ (static_cast<u64>(b->get_const_arg()));
				temp_s = -9000;
				break;

			case IrnBinOp::UnsgnMod:
				temp_u = (static_cast<u64>(a->get_const_arg()))
					% (static_cast<u64>(b->get_const_arg()));
				temp_s = -9000;
				break;

			case IrnBinOp::SgnDiv:
				temp_u = 9000;
				temp_s = a->get_const_arg() / b->get_const_arg();
				break;

			case IrnBinOp::SgnMod:
				temp_u = 9000;
				temp_s = a->get_const_arg() % b->get_const_arg();
				break;


			case IrnBinOp::BitAnd:
				temp_u = (static_cast<u64>(a->get_const_arg()))
					& (static_cast<u64>(b->get_const_arg()));
				temp_s = a->get_const_arg() & b->get_const_arg();
				break;
			case IrnBinOp::BitOr:
				temp_u = (static_cast<u64>(a->get_const_arg()))
					| (static_cast<u64>(b->get_const_arg()));
				temp_s = a->get_const_arg() | b->get_const_arg();
				break;
			case IrnBinOp::BitXor:
				temp_u = (static_cast<u64>(a->get_const_arg()))
					^ (static_cast<u64>(b->get_const_arg()));
				temp_s = a->get_const_arg() ^ b->get_const_arg();
				break;

			case IrnBinOp::Lsl:
				temp_u = (static_cast<u64>(a->get_const_arg()))
					<< (static_cast<u64>(b->get_const_arg()));
				temp_s = a->get_const_arg() << b->get_const_arg();
				break;
			case IrnBinOp::Lsr:
				temp_u = (static_cast<u64>(a->get_const_arg()))
					>> (static_cast<u64>(b->get_const_arg()));
				temp_s = -9000;
				break;

			case IrnBinOp::Asr:
				temp_u = 9000;
				temp_s = a->get_const_arg() >> b->get_const_arg();
				break;

			case IrnBinOp::Eq:
				temp_u = (static_cast<u64>(a->get_const_arg()))
					== (static_cast<u64>(b->get_const_arg()));
				temp_s = a->get_const_arg() == b->get_const_arg();
				break;


			case IrnBinOp::UnsgnGt:
				temp_u = ((static_cast<u64>(a->get_const_arg()))
					> (static_cast<u64>(b->get_const_arg())));
				temp_s = -9000;
				break;

			case IrnBinOp::UnsgnGe:
				temp_u = ((static_cast<u64>(a->get_const_arg()))
					>= (static_cast<u64>(b->get_const_arg())));
				temp_s = -9000;
				break;
			case IrnBinOp::SgnGt:
				temp_u = 9000;
				temp_s = ((a->get_const_arg()) > (b->get_const_arg()));
				break;

			case IrnBinOp::SgnGe:
				temp_u = 9000;
				temp_s = ((a->get_const_arg()) >= (b->get_const_arg()));
				break;

			default:
				printerr("mk_binop():  constant folding Eek!\n");
				exit(1);
				break;
		}

		if (!unsgn)
		{
			return mk_const(temp_s);
		}
		else
		{
			return mk_const(temp_u);
		}
	}

	if (temp.is_commutative_binop())
	{
		// Normalize operand order for commutative ops
		if (irn_to_index(b) < irn_to_index(a))
		{
			IrNode* irn = a;
			a = b;
			b = irn;
		}
	}
	}


	//IrNode* p = mkirn();
	IrNode* p = new IrBinOpNode(__op, a, b);
	__append(p);

	return p;
}
IrNode* IrCode::mk_unop(IrnUnOp op, IrNode* irn0)
{
	// Constant folding
	if (irn0->is_const())
	{
		s64 temp_s;
		
		switch (op)
		{
			case IrnUnOp::Negate:
				temp_s = -irn0->get_const_arg();
				break;

			case IrnUnOp::BitNot:
				temp_s = ~irn0->get_const_arg();
				break;

			case IrnUnOp::LogNot:
				temp_s = !irn0->get_const_arg();
				break;

			default:
				printerr("mk_unop():  constant folding Eek!\n");
				exit(1);
				break;
		}

		return mk_const(temp_s);
	}

	//IrNode* p = mkirn();
	//p->op = op;
	//p->__irnarg[0] = irn0;

	IrNode* p = new IrUnOpNode(op, irn0);
	__append(p);

	return p;
}



IrNode* IrCode::mk_noteq(IrNode* a, IrNode* b)
{
	IrNode* p = mk_binop(IrnOp::Eq, a, b, true);
	//p = mk_lognot(p);
	p = mk_unop(IrnOp::LogNot, p);
	return p;
}
IrNode* IrCode::mk_logand(IrNode* a, IrNode* b)
{
	IrNode* p = mk_noteq(a, mk_const(0));
	IrNode* q = mk_noteq(b, mk_const(0));

	return mk_binop(IrnOp::BitAnd, p, q, true);
}
IrNode* IrCode::mk_logor(IrNode* a, IrNode* b)
{
	IrNode* p = mk_noteq(a, mk_const(0));
	IrNode* q = mk_noteq(b, mk_const(0));

	return mk_binop(IrnOp::BitOr, p, q, true);
}

IrNode* IrCode::mk_ldop(IrnLoadType ldtyp, Var* __varg)
{
	switch (ldtyp)
	{
		case IrnLoadType::LdUnsgn8:
			return __mk_ldop(IrnLdStOp::Ldu8, __varg);
			break;

		case IrnLoadType::LdUnsgn16:
			return __mk_ldop(IrnLdStOp::Ldu16, __varg);
			break;

		case IrnLoadType::LdUnsgn32:
			return __mk_ldop(IrnLdStOp::Ldu32, __varg);
			break;

		case IrnLoadType::LdSgn8:
			return __mk_ldop(IrnLdStOp::Lds8, __varg);
			break;

		case IrnLoadType::LdSgn16:
			return __mk_ldop(IrnLdStOp::Lds16, __varg);
			break;

		case IrnLoadType::LdSgn32:
			return __mk_ldop(IrnLdStOp::Lds32, __varg);
			break;

		default:
			printerr("IrCode::mk_ldop():  Eek!\n");
			exit(1);
			break;
	}
}
IrNode* IrCode::mk_ldxop(IrnLoadType ldtyp, Var* __varg, IrNode* irn0)
{
	switch (ldtyp)
	{
		case IrnLoadType::LdUnsgn8:
			return __mk_ldxop(IrnLdStOp::Ldu8x, __varg, irn0);
			break;

		case IrnLoadType::LdUnsgn16:
			return __mk_ldxop(IrnLdStOp::Ldu16x, __varg, irn0);
			break;

		case IrnLoadType::LdUnsgn32:
			return __mk_ldxop(IrnLdStOp::Ldu32x, __varg, irn0);
			break;

		case IrnLoadType::LdSgn8:
			return __mk_ldxop(IrnLdStOp::Lds8x, __varg, irn0);
			break;

		case IrnLoadType::LdSgn16:
			return __mk_ldxop(IrnLdStOp::Lds16x, __varg, irn0);
			break;

		case IrnLoadType::LdSgn32:
			return __mk_ldxop(IrnLdStOp::Lds32x, __varg, irn0);
			break;

		default:
			printerr("IrCode::mk_ldxop():  Eek!\n");
			exit(1);
			break;
	}
}
IrNode* IrCode::mk_stop(IrnStoreType sttyp, Var* __varg, IrNode* irn1)
{
	switch (sttyp)
	{
		case IrnStoreType::St8:
			return __mk_stop(IrnLdStOp::St8, __varg, irn1);
			break;

		case IrnStoreType::St16:
			return __mk_stop(IrnLdStOp::St16, __varg, irn1);
			break;

		case IrnStoreType::St32:
			return __mk_stop(IrnLdStOp::St32, __varg, irn1);
			break;

		default:
			printerr("IrCode::mk_stop():  Eek!\n");
			exit(1);
			break;
	}
}
IrNode* IrCode::mk_stxop(IrnStoreType sttyp, Var* __varg, IrNode* irn0, 
	IrNode* irn1)
{
	switch (sttyp)
	{
		case IrnStoreType::St8:
			return __mk_stxop(IrnLdStOp::St8x, __varg, irn0, irn1);
			break;

		case IrnStoreType::St16:
			return __mk_stxop(IrnLdStOp::St16x, __varg, irn0, irn1);
			break;

		case IrnStoreType::St32:
			return __mk_stxop(IrnLdStOp::St32x, __varg, irn0, irn1);
			break;

		default:
			printerr("IrCode::mk_stxop():  Eek!\n");
			exit(1);
			break;
	}
}

IrNode* IrCode::mk_const(s64 val)
{
	// Search until we hit the start of the basic block so that we don't
	// have duplicate constants within the basic block
	for (IrNode* p=head.prev; (!p->is_lab() && p!=&head); p=p->prev)
	{
		if (p->is_const() && p->get_const_arg() == val)
		{
			return p;
		}
	}

	//// Make a new constant
	//IrNode* p = mkirn();
	//p->__op = IrnOp::Const;
	//p->__const_arg = val;
	IrNode* p = new IrConstNode(val);
	__append(p);

	return p;
}
IrNode* IrCode::mk_lab(s64 val)
{
	//IrNode* p = mkirn();
	//p->__op = IrnOp::Lab;
	//p->__larg[0] = val;
	IrNode* p = new IrLabNode(val);
	__append(p);

	return p;
}
IrNode* IrCode::mk_condjump(IrNode* dst, s64 lab0, s64 lab1)
{
	//IrNode* p = mkirn();
	//p->__op = IrnOp::CondJump;
	//p->__irnarg[0] = dst;
	//p->__larg[0] = lab0;
	//p->__larg[1] = lab1;

	IrNode* p = new IrCondJumpNode(dst, lab0, lab1);
	__append(p);

	return p;
}
IrNode* IrCode::mk_clean(Var* varg)
{
	//IrNode* p = mkirn();
	//p->__op = IrnOp::Clean;
	//p->__varg = varg;

	IrNode* p = new IrCleanNode(varg);
	__append(p);

	return p;
}

std::ostream& IrCode::osprint_irn(std::ostream& os, IrNode* p) const
{
	osprintout(os, irn_to_index(p), ":\t\t");

	auto print_binop = [&](const std::string& text) -> void
	{
		osprintout(os, text, "(");
		osprintout(os, irn_to_index(p->__irnarg[0]), ", ", 
			irn_to_index(p->__irnarg[1]));
		osprintout(os, ")");
	};


	auto print_ldop = [&](const std::string& text) -> void
	{
		osprintout(os, text, "(");
		osprintout(os, p->__varg->name(), "{", 
			p->__varg->scope_lev(), ", ", p->__varg->scope_num(), "}");
		osprintout(os, ")");
	};

	auto print_ldxop = [&](const std::string& text) -> void
	{
		osprintout(os, text, "(");
		osprintout(os, p->__varg->name(), "{", 
			p->__varg->scope_lev(), ", ", p->__varg->scope_num(), "}, ", 
			irn_to_index(p->__irnarg[0]));
		osprintout(os, ")");
	};

	auto print_stop = [&](const std::string& text) -> void
	{
		osprintout(os, text, "(");
		osprintout(os, p->__varg->name(), "{", 
			p->__varg->scope_lev(), ", ", p->__varg->scope_num(), "}, ", 
			irn_to_index(p->__irnarg[1]));
		osprintout(os, ")");
	};

	auto print_stxop = [&](const std::string& text) -> void
	{
		osprintout(os, text, "(");
		osprintout(os, p->__varg->name(), "{", 
			p->__varg->scope_lev(), ", ", p->__varg->scope_num(), "}, ", 
			irn_to_index(p->__irnarg[0]), ", ", 
			irn_to_index(p->__irnarg[1]));
		osprintout(os, ")");
	};

	if (p->is_binop())
	{
		switch (p->__op)
		{
			case IrnOp::Add:
				print_binop("add");
				break;
			case IrnOp::Sub:
				print_binop("sub");
				break;
			case IrnOp::Negate:
				osprintout(os, "neg(");
				osprintout(os, irn_to_index(p->__irnarg[0]));
				osprintout(os, ")");
				break;
			case IrnOp::Mul:
				print_binop("mul");
				break;
			case IrnOp::UnsgnDiv:
				print_binop("udiv");
				break;
			case IrnOp::UnsgnMod:
				print_binop("umod");
				break;
			case IrnOp::SgnDiv:
				print_binop("sdiv");
				break;
			case IrnOp::SgnMod:
				print_binop("smod");
				break;

			// Save this for later
			//DivMod

			case IrnOp::BitAnd:
				print_binop("bitand");
				break;
			case IrnOp::BitOr:
				print_binop("bitor");
				break;
			case IrnOp::BitXor:
				print_binop("bitxor");
				break;


			// Logical shift left
			case IrnOp::Lsl:
				print_binop("lsl");
				break;

			// Logical shift right
			case IrnOp::Lsr:
				print_binop("lsr");
				break;

			// Arithmetic shift right
			case IrnOp::Asr:
				print_binop("asr");
				break;



			// ==
			case IrnOp::Eq:
				print_binop("eq");
				break;

			// Unsigned >
			case IrnOp::UnsgnGt:
				print_binop("ugt");
				break;

			// Unsigned >=
			case IrnOp::UnsgnGe:
				print_binop("uge");
				break;

			// Signed >
			case IrnOp::SgnGt:
				print_binop("sgt");
				break;

			// Signed >=
			case IrnOp::SgnGe:
				print_binop("sge");
				break;

			default:
				printerr("osprint_irn:  binop Eek!\n");
				exit(1);
		}
	}

	else if (p->is_unop())
	{
		switch (p->__op)
		{
			case IrnOp::BitNot:
				osprintout(os, "bitnot(");
				osprintout(os, irn_to_index(p->__irnarg[0]));
				osprintout(os, ")");
				break;

			case IrnOp::LogNot:
				osprintout(os, "lognot(");
				osprintout(os, irn_to_index(p->__irnarg[0]));
				osprintout(os, ")");
				break;

			default:
				printerr("osprint_irn:  unop Eek!\n");
				exit(1);
		}
	}

	else if (p->is_ldst())
	{
		switch (p->__op)
		{
			// ldu64op
			case IrnLdStOp::Ldu64:
				print_ldop("ldu64");
				break;
			// ldu32op
			case IrnLdStOp::Ldu32:
				print_ldop("ldu32");
				break;
			// ldu16op
			case IrnLdStOp::Ldu16:
				print_ldop("ldu16");
				break;
			// ldu8op
			case IrnLdStOp::Ldu8:
				print_ldop("ldu8");
				break;


			// ldu64xop
			case IrnLdStOp::Ldu64x:
				print_ldxop("ldu64x");
				break;
			// ldu32xop
			case IrnLdStOp::Ldu32x:
				print_ldxop("ldu32x");
				break;
			// ldu16xop
			case IrnLdStOp::Ldu16x:
				print_ldxop("ldu16x");
				break;
			// ldu8xop
			case IrnLdStOp::Ldu8x:
				print_ldxop("ldu8x");
				break;


			// lds64op
			case IrnLdStOp::Lds64:
				print_ldop("lds64");
				break;
			// lds32op
			case IrnLdStOp::Lds32:
				print_ldop("lds32");
				break;
			// lds16op
			case IrnLdStOp::Lds16:
				print_ldop("lds16");
				break;
			// lds8op
			case IrnLdStOp::Lds8:
				print_ldop("lds8");
				break;


			// lds64xop
			case IrnLdStOp::Lds64x:
				print_ldxop("lds64x");
				break;
			// lds32xop
			case IrnLdStOp::Lds32x:
				print_ldxop("lds32x");
				break;
			// lds16xop
			case IrnLdStOp::Lds16x:
				print_ldxop("lds16x");
				break;
			// lds8xop
			case IrnLdStOp::Lds8x:
				print_ldxop("lds8x");
				break;



			// st64op
			case IrnLdStOp::St64:
				print_stop("st64");
				break;
			// st32op
			case IrnLdStOp::St32:
				print_stop("st32");
				break;
			// st16op
			case IrnLdStOp::St16:
				print_stop("st16");
				break;
			// st8op
			case IrnLdStOp::St8:
				print_stop("st8");
				break;


			// st64xop
			case IrnLdStOp::St64x:
				print_stxop("st64x");
				break;
			// st32xop
			case IrnLdStOp::St32x:
				print_stxop("st32x");
				break;
			// st16xop
			case IrnLdStOp::St16x:
				print_stxop("st16x");
				break;
			// st8xop
			case IrnLdStOp::St8x:
				print_stxop("st8x");
				break;

			default:
				printerr("osprint_irn:  ldst Eek!\n");
				exit(1);
		}
	}


		// const
		else if (p->is_const)
		{
			osprintout(os, "const(");
			osprintout(os, p->__const_arg);
			osprintout(os, ")");
		}

		// lab
		else if (p->is_lab())
		{
			osprintout(os, "lab(");
			osprintout(os, p->__larg[0]);
			osprintout(os, ")");
		}

		// condjump
		else if (p->is_condjump())
		{
			osprintout(os, "condjump(");
			osprintout(os, irn_to_index(p->__irnarg[0]), ", ", 
				p->__larg[0], ", ", p->__larg[1]);
			osprintout(os, ")");
		}

		// kill
		else if (p->is_clean())
		{
			osprintout(os, "kill(");
			osprintout(os, p->__varg->name(), "{", p->__varg->scope_lev(),
				", ", p->__varg->scope_num(), "}");
			osprintout(os, ")");
		}

		else
		{
			osprintout(os, "Eek!  Bad IrNode!\n");
		}
	}

	return os;
}


IrNode* IrCode::__mk_ldop(IrnLdStOp op, Var* varg)
{
	{
	IrNode temp;
	temp.get_op() = op;

	if (!temp.is_ldop())
	{
		printerr("IrCode::__mk_ldop():  Eek!\n");
		exit(1);
	}
	}

	//IrNode* p = mkirn();
	//p->op = op;
	//p->varg = varg;

	IrNode* p = new IrLdStNode(op, varg, nullptr, nullptr);
	__append(p);

	return p;
}
IrNode* IrCode::__mk_ldxop(IrnLdStOp op, Var* varg, IrNode* irn0)
{
	{
	IrNode temp;
	temp.get_op() = op;

	if (!temp.is_ldxop())
	{
		printerr("IrCode::__mk_ldxop():  Eek!\n");
		exit(1);
	}
	}

	//IrNode* p = mkirn();
	//p->op = op;
	//p->varg = varg;
	//p->__irnarg[0] = irn0;

	IrNode* p = new IrLdStNode(op, varg, irn0, nullptr);
	__append(p);

	return p;
}
IrNode* IrCode::__mk_stop(IrnLdStOp op, Var* varg, IrNode* irn1)
{
	{
	IrNode temp;
	temp.get_op() = op;

	if (!temp.is_stop())
	{
		printerr("IrCode::__mk_stop():  Eek!\n");
		exit(1);
	}
	}

	//IrNode* p = mkirn();
	//p->op = op;
	//p->varg = varg;
	//p->__irnarg[1] = irn1;

	IrNode* p = new IrLdStNode(op, varg, nullptr, irn1);
	__append(p);

	return p;
}
IrNode* IrCode::__mk_stxop(IrnLdStOp op, Var* varg, IrNode* irn0, 
	IrNode* irn1)
{
	{
	IrNode temp;
	temp.get_op() = op;

	if (!temp.is_stxop())
	{
		printerr("IrCode::__mk_stxop():  Eek!\n");
		exit(1);
	}
	}

	//IrNode* p = mkirn();
	//p->op = op;
	//p->varg = varg;
	//p->__irnarg[0] = irn0;
	//p->__irnarg[1] = irn1;
	IrNode* p = new IrLdStNode(op, varg, irn0, irn1);
	__append(p);

	return p;
}

}
