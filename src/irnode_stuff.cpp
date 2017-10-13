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
	return any_irnop_matches(op, IrnOp::Add, IrnOp::Sub, IrnOp::Mul,
		IrnOp::UnsgnDiv, IrnOp::UnsgnMod,
		IrnOp::SgnDiv, IrnOp::SgnMod,

		IrnOp::BitAnd, IrnOp::BitOr, IrnOp::BitXor,

		IrnOp::Lsl, IrnOp::Lsr, IrnOp::Asr,

		IrnOp::Eq, 
		IrnOp::UnsgnGt, IrnOp::UnsgnGe, 
		IrnOp::SgnGt, IrnOp::SgnGe);
}

bool IrNode::is_commutative_binop() const
{
	return any_irnop_matches(op, IrnOp::Add, IrnOp::Mul,

		IrnOp::BitAnd, IrnOp::BitOr, IrnOp::BitXor,

		IrnOp::Eq);
}

bool IrNode::is_compare() const
{
	return any_irnop_matches(op, IrnOp::Eq, 
		IrnOp::UnsgnGt, IrnOp::UnsgnGe,
		IrnOp::SgnGt, IrnOp::SgnGe);
}

bool IrNode::is_ldst_32() const
{
	return any_irnop_matches(op, IrnOp::Ldu32, IrnOp::Ldu32x,
		IrnOp::Lds32, IrnOp::Lds32x,
		IrnOp::St32);
}
bool IrNode::is_ldst_16() const
{
	return any_irnop_matches(op, IrnOp::Ldu16, IrnOp::Ldu16x,
		IrnOp::Lds16, IrnOp::Lds16x,
		IrnOp::St16);
}
bool IrNode::is_ldst_8() const
{
	return any_irnop_matches(op, IrnOp::Ldu8, IrnOp::Ldu8x,
		IrnOp::Lds8, IrnOp::Lds8x,
		IrnOp::St8);
}

bool IrNode::is_ldop() const
{
	return any_irnop_matches(op, IrnOp::Ldu32, IrnOp::Ldu16, IrnOp::Ldu8,
		IrnOp::Lds32, IrnOp::Lds16, IrnOp::Lds8);
}
bool IrNode::is_ldxop() const
{
	return any_irnop_matches(op, 
		IrnOp::Ldu32x, IrnOp::Ldu16x, IrnOp::Ldu8x,
		IrnOp::Lds32x, IrnOp::Lds16x, IrnOp::Lds8x);
}
bool IrNode::is_stop() const
{
	return any_irnop_matches(op, IrnOp::St32, IrnOp::St16, IrnOp::St8);
}
bool IrNode::is_stxop() const
{
	return any_irnop_matches(op, IrnOp::St32x, IrnOp::St16x, IrnOp::St8x);
}


bool IrNode::is_unsigned_ldop() const
{
	return any_irnop_matches(op, IrnOp::Ldu32, IrnOp::Ldu16, IrnOp::Ldu8);
}
bool IrNode::is_signed_ldop() const
{
	return any_irnop_matches(op, IrnOp::Lds32, IrnOp::Lds16, IrnOp::Lds8);
}
bool IrNode::is_unsigned_ldxop() const
{
	return any_irnop_matches(op, 
		IrnOp::Ldu32x, IrnOp::Ldu16x, IrnOp::Ldu8x);
}
bool IrNode::is_signed_ldxop() const
{
	return any_irnop_matches(op, 
		IrnOp::Lds32x, IrnOp::Lds16x, IrnOp::Lds8x);
}

IrCode::IrCode()
{
	head.next = &head;
	head.prev = &head;
	head.op = IrnOp::Unknown;
}

IrCode::~IrCode()
{
	while (head.next != &head)
	{
		rmirn(head.prev);
	}
}

int IrCode::ir_to_index(IrNode* irn) const
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
	printout("Removing this Irn:  ");
	osprint_irn(cout, irn);
	printout("\n");
	__delink_irn(irn);
	delete irn;
}

IrNode* IrCode::mk_binop(IrnOp op, IrNode* a, IrNode* b)
{
	{
	IrNode temp;
	temp.op = op;

	if (!temp.is_binop())
	{
		printerr("IrCode::mk_binop():  Eek!\n");
		exit(1);
	}
	}

	IrNode* p = mkirn();
	p->op = op;
	p->irnarg[0] = a;
	p->irnarg[1] = b;

	return p;
}

IrNode* IrCode::mk_ldop(IrnOp op, Var* varg)
{
	{
	IrNode temp;
	temp.op = op;

	if (!temp.is_ldop())
	{
		printerr("IrCode::mk_ldop():  Eek!\n");
		exit(1);
	}
	}

	IrNode* p = mkirn();
	p->op = op;
	p->varg = varg;

	return p;
}
IrNode* IrCode::mk_ldxop(IrnOp op, Var* varg, IrNode* irn0)
{
	{
	IrNode temp;
	temp.op = op;

	if (!temp.is_ldxop())
	{
		printerr("IrCode::mk_ldxop():  Eek!\n");
		exit(1);
	}
	}

	IrNode* p = mkirn();
	p->op = op;
	p->varg = varg;
	p->irnarg[0] = irn0;

	return p;
}
IrNode* IrCode::mk_stop(IrnOp op, Var* varg, IrNode* irn1)
{
	{
	IrNode temp;
	temp.op = op;

	if (!temp.is_stop())
	{
		printerr("IrCode::mk_stop():  Eek!\n");
		exit(1);
	}
	}

	IrNode* p = mkirn();
	p->op = op;
	p->varg = varg;
	p->irnarg[1] = irn1;

	return p;
}
IrNode* IrCode::mk_stxop(IrnOp op, Var* varg, IrNode* irn0, IrNode* irn1)
{
	{
	IrNode temp;
	temp.op = op;

	if (!temp.is_stxop())
	{
		printerr("IrCode::mk_stxop():  Eek!\n");
		exit(1);
	}
	}

	IrNode* p = mkirn();
	p->op = op;
	p->varg = varg;
	p->irnarg[0] = irn0;
	p->irnarg[1] = irn1;

	return p;
}

IrNode* IrCode::mk_const(s64 val)
{
	IrNode* p = mkirn();
	p->op = IrnOp::Const;
	p->carg = val;

	return p;
}
IrNode* IrCode::mk_lab(s64 val)
{
	IrNode* p = mkirn();
	p->op = IrnOp::Lab;
	p->larg[0] = val;

	return p;
}
IrNode* IrCode::mk_sel(IrNode* dst, s64 lab0, s64 lab1)
{
	IrNode* p = mkirn();
	p->op = IrnOp::Sel;
	p->irnarg[0] = dst;
	p->larg[0] = lab0;
	p->larg[1] = lab1;

	return p;
}
IrNode* IrCode::mk_kill(Var* varg)
{
	IrNode* p = mkirn();
	p->op = IrnOp::Kill;
	p->varg = varg;

	return p;
}

std::ostream& IrCode::osprint_irn(std::ostream& os, IrNode* p) const
{
	osprintout(os, ir_to_index(p), ":\t\t");

	auto print_binop = [&](const std::string& text) -> void
	{
		osprintout(os, text, "(");
		osprintout(os, ir_to_index(p->irnarg[0]), ", ", 
			ir_to_index(p->irnarg[1]));
		osprintout(os, ")");
	};


	auto print_ldop = [&](const std::string& text) -> void
	{
		osprintout(os, text, "(");
		osprintout(os, p->varg->name(), "{", p->varg->scope_lev(),
			", ", p->varg->scope_num(), "}");
		osprintout(os, ")");
	};

	auto print_ldxop = [&](const std::string& text) -> void
	{
		osprintout(os, text, "(");
		osprintout(os, p->varg->name(), "{", p->varg->scope_lev(),
			", ", p->varg->scope_num(), "}, ", ir_to_index(p->irnarg[0]));
		osprintout(os, ")");
	};

	auto print_stop = [&](const std::string& text) -> void
	{
		osprintout(os, text, "(");
		osprintout(os, p->varg->name(), "{", p->varg->scope_lev(),
			", ", p->varg->scope_num(), "}, ", ir_to_index(p->irnarg[1]));
		osprintout(os, ")");
	};

	auto print_stxop = [&](const std::string& text) -> void
	{
		osprintout(os, text, "(");
		osprintout(os, p->varg->name(), "{", p->varg->scope_lev(),
			", ", p->varg->scope_num(), "}, ", ir_to_index(p->irnarg[0]),
			", ", ir_to_index(p->irnarg[1]));
		osprintout(os, ")");
	};

	switch (p->op)
	{
		case IrnOp::Add:
			print_binop("add");
			break;
		case IrnOp::Sub:
			print_binop("sub");
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


		// ldu32op
		case IrnOp::Ldu32:
			print_ldop("ldu32");
			break;

		// ldu32xop
		case IrnOp::Ldu32x:
			print_ldxop("ldu32x");
			break;

		// ldu16op
		case IrnOp::Ldu16:
			print_ldop("ldu16");
			break;

		// ldu16xop
		case IrnOp::Ldu16x:
			print_ldxop("ldu16x");
			break;

		// ldu8op
		case IrnOp::Ldu8:
			print_ldop("ldu8");
			break;

		// ldu8xop
		case IrnOp::Ldu8x:
			print_ldxop("ldu8x");
			break;


		// lds32op
		case IrnOp::Lds32:
			print_ldop("lds32");
			break;

		// lds32xop
		case IrnOp::Lds32x:
			print_ldxop("lds32x");
			break;

		// lds16op
		case IrnOp::Lds16:
			print_ldop("lds16");
			break;

		// lds16xop
		case IrnOp::Lds16x:
			print_ldxop("lds16x");
			break;

		// lds8op
		case IrnOp::Lds8:
			print_ldop("lds8");
			break;

		// lds8xop
		case IrnOp::Lds8x:
			print_ldxop("lds8x");
			break;



		// st32op
		case IrnOp::St32:
			print_stop("st32");
			break;

		// st32xop
		case IrnOp::St32x:
			print_stxop("st32x");
			break;

		// st16op
		case IrnOp::St16:
			print_stop("st16");
			break;

		// st16xop
		case IrnOp::St16x:
			print_stxop("st16x");
			break;

		// st8op
		case IrnOp::St8:
			print_stop("st8");
			break;

		// st8xop
		case IrnOp::St8x:
			print_stxop("st8x");
			break;


		// const
		case IrnOp::Const:
			osprintout(os, "const(");
			osprintout(os, p->carg);
			osprintout(os, ")");
			break;

		// labop
		case IrnOp::Lab:
			osprintout(os, "lab(");
			osprintout(os, p->larg[0]);
			osprintout(os, ")");
			break;

		// selop
		case IrnOp::Sel:
			osprintout(os, "sel(");
			osprintout(os, ir_to_index(p->irnarg[0]), ", ", p->larg[0], 
				", ", p->larg[1]);
			osprintout(os, ")");
			break;

		// kill
		case IrnOp::Kill:
			osprintout(os, "kill(");
			osprintout(os, p->varg->name(), "{", p->varg->scope_lev(),
				", ", p->varg->scope_num(), "}");
			osprintout(os, ")");
			break;

		default:
			osprintout(os, "Eek!  Bad Opcode:  ");
			osprintout(os, static_cast<s64>(p->op));
			break;
	}

	return os;
}

}
