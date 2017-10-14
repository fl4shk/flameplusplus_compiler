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
	Negate,
	Mul,
	UnsgnDiv,
	UnsgnMod,

	SgnDiv,
	SgnMod,

	// Save this for later
	//DivMod,

	BitAnd,
	BitOr,
	BitXor,


	BitNot,
	LogNot,


	// Logical shift left
	Lsl,

	// Logical shift right
	Lsr,

	// Arithmetic shift right
	Asr,



	// ==
	Eq,

	// Unsigned >
	UnsgnGt,

	// Unsigned >=
	UnsgnGe,

	// Signed >
	SgnGt,

	// Signed >=
	SgnGe,



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


	// Function call (not yet implemented)
	// Call,

	// kill (clean up the variable)
	Kill,

	Unknown
};

enum class IrnLoadType
{
	LdUnsgn8,
	LdUnsgn16,
	LdUnsgn32,

	LdSgn8,
	LdSgn16,
	LdSgn32,
};

enum class IrnStoreType
{
	St8,
	St16,
	St32,
};



inline bool any_irnop_matches(IrnOp op)
{
	return false;
}

template<typename... RemArgTypes>
bool any_irnop_matches(IrnOp op, IrnOp next, 
	RemArgTypes&&... rem_args)
{
	if (sizeof...(rem_args) == 0)
	{
		return (op == next);
	}
	else if (op == next)
	{
		return true;
	}
	else
	{
		return any_irnop_matches(op, rem_args...);
	}
}

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


	inline s64& get_const_arg()
	{
		return carg;
	}
	inline IrNode* get_store_src()
	{
		return irnarg[0];
	}
	inline IrNode* get_ldxstx_index()
	{
		return irnarg[1];
	}

	inline IrNode* get_sel_cmp()
	{
		return irnarg[0];
	}
	inline s64& get_sel_nonzero_dst()
	{
		return larg[0];
	}
	inline s64& get_sel_zero_dst()
	{
		return larg[1];
	}

	bool is_binop() const;
	bool is_commutative_binop() const;
	bool is_compare() const;
	inline bool is_unsigned_compare() const
	{
		return any_irnop_matches(op, IrnOp::UnsgnGt, IrnOp::UnsgnGe);
	}
	inline bool is_signed_compare() const
	{
		return any_irnop_matches(op, IrnOp::SgnGt, IrnOp::SgnGe);
	}
	inline bool is_ldst() const
	{
		return (is_ldop() || is_ldxop() || is_stop() || is_stxop());
	}
	bool is_ldst_32() const;
	bool is_ldst_16() const;
	bool is_ldst_8() const;


	bool is_ldop() const;
	bool is_ldxop() const;
	bool is_stop() const;
	bool is_stxop() const;


	bool is_unsigned_ldop() const;
	bool is_signed_ldop() const;
	bool is_unsigned_ldxop() const;
	bool is_signed_ldxop() const;

	inline bool is_unsigned_load() const
	{
		return (is_unsigned_ldop() || is_unsigned_ldxop());
	}
	inline bool is_signed_load() const
	{
		return (is_signed_ldop() || is_signed_ldxop());
	}


	inline bool is_const() const
	{
		return (op == IrnOp::Const);
	}
	inline bool is_lab() const
	{
		return (op == IrnOp::Lab);
	}
	inline bool is_sel() const
	{
		return (op == IrnOp::Sel);
	}
	inline bool is_kill() const
	{
		return (op == IrnOp::Kill);
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



	int irn_to_index(IrNode* irn) const;


	IrNode* mkirn();
	void rmirn(IrNode* irn);

	IrNode* mk_binop(IrnOp op, IrNode* a, IrNode* b);
	IrNode* mk_negate(IrNode* irn0);
	IrNode* mk_bitnot(IrNode* irn0);
	IrNode* mk_lognot(IrNode* irn0);

	// Helpers
	IrNode* mk_noteq(IrNode* a, IrNode* b);
	IrNode* mk_logand(IrNode* a, IrNode* b);
	IrNode* mk_logor(IrNode* a, IrNode* b);

	// Load/Store
	IrNode* mk_ldop(IrnLoadType ldtyp, Var* varg);
	IrNode* mk_ldxop(IrnLoadType ldtyp, Var* varg, IrNode* irn0);
	IrNode* mk_stop(IrnStoreType sttyp, Var* varg, IrNode* irn1);
	IrNode* mk_stxop(IrnStoreType sttyp, Var* varg, IrNode* irn0, 
		IrNode* irn1);


	// 
	IrNode* mk_const(s64 val);
	IrNode* mk_lab(s64 val);
	IrNode* mk_sel(IrNode* dst, s64 lab0, s64 lab1);

	IrNode* mk_kill(Var* varg);




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


	IrNode* __mk_ldop(IrnOp op, Var* varg);
	IrNode* __mk_ldxop(IrnOp op, Var* varg, IrNode* irn0);
	IrNode* __mk_stop(IrnOp op, Var* varg, IrNode* irn1);
	IrNode* __mk_stxop(IrnOp op, Var* varg, IrNode* irn0, IrNode* irn1);
};

}



#endif		// irnode_stuff_hpp
