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


#include "ircode_class.hpp"

namespace flame_plus_plus
{
//const bool IrCode::optimize = false;
const bool IrCode::optimize = true;

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

//IrNode* IrCode::mkirn()
//{
//	IrNode* p = new IrNode();
//
//	p->next = &head;
//	p->prev = head.prev;
//	p->prev->next = p;
//	head.prev = p;
//
//	return p;
//}
void IrCode::rmirn(IrNode* irn)
{
	//printout("Removing this Irn:  ");
	//osprint_irn(cout, irn);
	//printout("\n");
	__delink_irn(irn);
	delete irn;
}

IrNode* IrCode::mk_binop(IrnBinOp op, IrNode* a, IrNode* b, bool unsgn)
{
	{
	IrBinOpNode temp(op, nullptr, nullptr);

	if (!temp.is_binop())
	{
		printerr("IrCode::mk_binop():  Eek!\n");
		exit(1);
	}

	if (optimize)
	{
		// Constant folding
		if (a->is_const() && b->is_const())
		{
			u64 temp_u;
			s64 temp_s;

			switch (op)
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


	return __append(new IrBinOpNode(op, a, b));
}
IrNode* IrCode::mk_unop(IrnUnOp op, IrNode* irn0)
{
	// Constant folding
	if (optimize)
	{
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
	}

	//p->op = op;
	//p->__irnarg[0] = irn0;

	return __append(new IrUnOpNode(op, irn0));
}



IrNode* IrCode::mk_noteq(IrNode* a, IrNode* b)
{
	IrNode* p = mk_binop(IrnBinOp::Eq, a, b, true);
	//p = mk_lognot(p);
	p = mk_unop(IrnUnOp::LogNot, p);
	return p;
}
IrNode* IrCode::mk_logand(IrNode* a, IrNode* b)
{
	IrNode* p = mk_noteq(a, mk_const(0));
	IrNode* q = mk_noteq(b, mk_const(0));

	return mk_binop(IrnBinOp::BitAnd, p, q, true);
}
IrNode* IrCode::mk_logor(IrNode* a, IrNode* b)
{
	IrNode* p = mk_noteq(a, mk_const(0));
	IrNode* q = mk_noteq(b, mk_const(0));

	return mk_binop(IrnBinOp::BitOr, p, q, true);
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
	if (optimize)
	{
		// Search until we hit the start of the basic block so that we
		// don't have duplicate constants within the basic block
		for (IrNode* p=head.prev; (!p->is_lab() && p!=&head); p=p->prev)
		{
			if (p->is_const() && p->get_const_arg() == val)
			{
				return p;
			}
		}
	}

	//// Make a new constant
	//p->__op = IrnOp::Const;
	//p->__const_arg = val;
	return __append(new IrConstNode(val));
}
IrNode* IrCode::mk_lab(s64 val)
{
	//p->__op = IrnOp::Lab;
	//p->__larg[0] = val;
	return __append(new IrLabNode(val));
}
IrNode* IrCode::mk_condjump(IrNode* dst, s64 lab0, s64 lab1)
{
	//p->__op = IrnOp::CondJump;
	//p->__irnarg[0] = dst;
	//p->__larg[0] = lab0;
	//p->__larg[1] = lab1;

	return __append(new IrCondJumpNode(dst, lab0, lab1));
}
IrNode* IrCode::mk_clean(Var* varg)
{
	//p->__op = IrnOp::Clean;
	//p->__varg = varg;

	return __append(new IrCleanNode(varg));
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
		switch (p->get_irn_bin_op())
		{
			case IrnBinOp::Add:
				print_binop("add");
				break;
			case IrnBinOp::Sub:
				print_binop("sub");
				break;
			case IrnBinOp::Mul:
				print_binop("mul");
				break;
			case IrnBinOp::UnsgnDiv:
				print_binop("udiv");
				break;
			case IrnBinOp::UnsgnMod:
				print_binop("umod");
				break;
			case IrnBinOp::SgnDiv:
				print_binop("sdiv");
				break;
			case IrnBinOp::SgnMod:
				print_binop("smod");
				break;

			// Save this for later
			//DivMod

			case IrnBinOp::BitAnd:
				print_binop("bitand");
				break;
			case IrnBinOp::BitOr:
				print_binop("bitor");
				break;
			case IrnBinOp::BitXor:
				print_binop("bitxor");
				break;


			// Logical shift left
			case IrnBinOp::Lsl:
				print_binop("lsl");
				break;

			// Logical shift right
			case IrnBinOp::Lsr:
				print_binop("lsr");
				break;

			// Arithmetic shift right
			case IrnBinOp::Asr:
				print_binop("asr");
				break;



			// ==
			case IrnBinOp::Eq:
				print_binop("eq");
				break;

			// Unsigned >
			case IrnBinOp::UnsgnGt:
				print_binop("ugt");
				break;

			// Unsigned >=
			case IrnBinOp::UnsgnGe:
				print_binop("uge");
				break;

			// Signed >
			case IrnBinOp::SgnGt:
				print_binop("sgt");
				break;

			// Signed >=
			case IrnBinOp::SgnGe:
				print_binop("sge");
				break;

			default:
				printerr("osprint_irn:  binop Eek!\n");
				exit(1);
		}
	}

	else if (p->is_unop())
	{
		switch (p->get_irn_un_op())
		{
			case IrnUnOp::Negate:
				osprintout(os, "neg(");
				osprintout(os, irn_to_index(p->__irnarg[0]));
				osprintout(os, ")");
				break;
			case IrnUnOp::BitNot:
				osprintout(os, "bitnot(");
				osprintout(os, irn_to_index(p->__irnarg[0]));
				osprintout(os, ")");
				break;

			case IrnUnOp::LogNot:
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
		switch (p->get_irn_ldst_op())
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
	else if (p->is_const())
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

	// clean
	else if (p->is_clean())
	{
		osprintout(os, "clean(");
		osprintout(os, p->__varg->name(), "{", p->__varg->scope_lev(),
			", ", p->__varg->scope_num(), "}");
		osprintout(os, ")");
	}

	else
	{
		osprintout(os, "Eek!  Bad IrNode!\n");
	}

	return os;
}


IrNode* IrCode::__mk_ldop(IrnLdStOp op, Var* varg)
{
	{
	IrLdStNode temp(op, varg, nullptr, nullptr);

	if (!temp.is_ldop())
	{
		printerr("IrCode::__mk_ldop():  Eek!\n");
		exit(1);
	}
	}

	//p->op = op;
	//p->varg = varg;

	return __append(new IrLdStNode(op, varg, nullptr, nullptr));
}
IrNode* IrCode::__mk_ldxop(IrnLdStOp op, Var* varg, IrNode* irn0)
{
	{
	IrLdStNode temp(op, varg, nullptr, nullptr);

	if (!temp.is_ldxop())
	{
		printerr("IrCode::__mk_ldxop():  Eek!\n");
		exit(1);
	}
	}

	//p->op = op;
	//p->varg = varg;
	//p->__irnarg[0] = irn0;

	return __append(new IrLdStNode(op, varg, irn0, nullptr));
}
IrNode* IrCode::__mk_stop(IrnLdStOp op, Var* varg, IrNode* irn1)
{
	{
	IrLdStNode temp(op, varg, nullptr, nullptr);

	if (!temp.is_stop())
	{
		printerr("IrCode::__mk_stop():  Eek!\n");
		exit(1);
	}
	}

	//p->op = op;
	//p->varg = varg;
	//p->__irnarg[1] = irn1;

	
	return __append(new IrLdStNode(op, varg, nullptr, irn1));
}
IrNode* IrCode::__mk_stxop(IrnLdStOp op, Var* varg, IrNode* irn0, 
	IrNode* irn1)
{
	{
	IrLdStNode temp(op, varg, nullptr, nullptr);

	if (!temp.is_stxop())
	{
		printerr("IrCode::__mk_stxop():  Eek!\n");
		exit(1);
	}
	}

	//p->op = op;
	//p->varg = varg;
	//p->__irnarg[0] = irn0;
	//p->__irnarg[1] = irn1;
	return __append(new IrLdStNode(op, varg, irn0, irn1));
}

}
