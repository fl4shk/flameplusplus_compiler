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


#ifndef irnode_classes_hpp
#define irnode_classes_hpp


#include "var_class.hpp"

namespace flame_plus_plus
{

enum class IrnBinOp : s64
{
	Add,
	Sub,
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
};

// Unary operator ("~", "-", "!")
enum class IrnUnOp : s64
{
	Negate,
	BitNot,
	LogNot,
};

enum class IrnLdStOp
{
	// ldu64op
	Ldu64,
	// ldu32op
	Ldu32,
	// ldu16op
	Ldu16,
	// ldu8op
	Ldu8,

	// ldu64xop
	Ldu64x,
	// ldu32xop
	Ldu32x,
	// ldu16xop
	Ldu16x,
	// ldu8xop
	Ldu8x,




	// lds64op
	Lds64,
	// lds32op
	Lds32,
	// lds16op
	Lds16,
	// lds8op
	Lds8,

	// lds64xop
	Lds64x,
	// lds32xop
	Lds32x,
	// lds16xop
	Lds16x,
	// lds8xop
	Lds8x,



	// st64op
	St64,
	// st32op
	St32,
	// st16op
	St16,
	// st8op
	St8,


	// st64xop
	St64x,
	// st32xop
	St32x,
	// st16xop
	St16x,
	// st8xop
	St8x,
};


enum class IrnLoadType : s64
{
	LdUnsgn64,
	LdUnsgn32,
	LdUnsgn16,
	LdUnsgn8,

	LdSgn64,
	LdSgn32,
	LdSgn16,
	LdSgn8,
};

enum class IrnStoreType : s64
{
	St64,
	St32,
	St16,
	St8,
};

//inline operator s64 (IrnBinOp op)
//{
//	return (s64)op;
//}
//inline operator s64 (IrnUnOp op)
//{
//	return (s64)op;
//}
//inline operator s64 (IrnLdStOp op)
//{
//	return (s64) op;
//}
//inline operator s64 (IrnLoadType ldtyp)
//{
//	return (s64)ldtyp;
//}
//
//inline operator s64 (IrnStoreType sttyp)
//{
//	return (s64)sttyp;
//}

class IrCode;

// Base class for a node in the internal representation
class IrNode
{
friend class IrCode;

public:		// static constexpr variables
	static constexpr size_t num_args = 2;

protected:		// variables
//public:		// variables
	s64 __op;
	s64 __const_arg;

	IrNode* __irnarg[num_args];
	s64 __larg[num_args];
	Var* __varg;



	//std::vector<CallArg> __call_args;


public:		// variables
	IrNode * next, * prev;


public:		// functions
	inline IrNode()
	{
		__op = -1;
	}
	virtual ~IrNode()
	{
	}

	inline s64& get_op()
	{
		return __op;
	}
	inline IrnBinOp get_irn_bin_op() const
	{
		return static_cast<IrnBinOp>(__op);
	}
	inline IrnUnOp get_irn_un_op() const
	{
		return static_cast<IrnUnOp>(__op);
	}
	inline IrnLdStOp get_irn_ldst_op() const
	{
		return static_cast<IrnLdStOp>(__op);
	}

	inline void set_irn_bin_op(IrnBinOp op)
	{
		__op = static_cast<s64>(op);
	}
	inline void set_irn_un_op(IrnUnOp op)
	{
		__op = static_cast<s64>(op);
	}
	inline void set_irn_ldst_op(IrnLdStOp op)
	{
		__op = static_cast<s64>(op);
	}


	inline s64& get_const_arg()
	{
		return __const_arg;
	}
	inline IrNode* get_store_src()
	{
		return __irnarg[0];
	}
	inline IrNode* get_ldxstx_index()
	{
		return __irnarg[1];
	}

	inline IrNode* get_condjump_cmp()
	{
		return __irnarg[0];
	}
	inline s64& get_condjump_nonzero_dst()
	{
		return __larg[0];
	}
	inline s64& get_condjump_zero_dst()
	{
		return __larg[1];
	}


	// IrBinOpNode
	virtual bool is_binop() const;
	virtual bool is_commutative_binop() const;
	virtual bool is_non_commutative_binop() const;
	inline bool is_compare_binop() const
	{
		return (is_unsigned_compare_binop() || is_signed_compare_binop());
	}
	virtual bool is_unsigned_compare_binop() const;
	virtual bool is_signed_compare_binop() const;

	// IrUnOpNode
	virtual bool is_unop() const;


	// IrLdStNode
	inline bool is_ldst() const
	{
		return (is_ldop() || is_ldxop() || is_stop() || is_stxop());
	}
	virtual bool is_ldst_32() const;
	virtual bool is_ldst_16() const;
	virtual bool is_ldst_8() const;


	virtual bool is_ldop() const;
	virtual bool is_ldxop() const;
	virtual bool is_stop() const;
	virtual bool is_stxop() const;


	virtual bool is_unsigned_ldop() const;
	virtual bool is_signed_ldop() const;
	virtual bool is_unsigned_ldxop() const;
	virtual bool is_signed_ldxop() const;

	inline bool is_unsigned_load() const
	{
		return (is_unsigned_ldop() || is_unsigned_ldxop());
	}
	inline bool is_signed_load() const
	{
		return (is_signed_ldop() || is_signed_ldxop());
	}


	virtual bool is_const() const;
	virtual bool is_lab() const;
	virtual bool is_condjump() const;
	virtual bool is_call() const;
	virtual bool is_clean() const;
};

class IrBinOpNode : public IrNode
{
public:		// functions
	inline IrBinOpNode(IrnBinOp s_op, IrNode* s_irnarg0, IrNode* s_irnarg1)
	{
		__op = (s64)s_op;
		init_array(__irnarg, s_irnarg0, s_irnarg1);
	}
	bool is_binop() const;
	bool is_commutative_binop() const;
	bool is_non_commutative_binop() const;
	bool is_compare_binop() const;
	bool is_unsigned_compare_binop() const;
	bool is_signed_compare_binop() const;
};

class IrUnOpNode : public IrNode
{
public:		// functions
	inline IrUnOpNode(IrnUnOp s_op, IrNode* s_irnarg0)
	{
		__op = (s64)s_op;
		__irnarg[0] = s_irnarg0;
	}
	bool is_unop() const;
};

class IrLdStNode : public IrNode
{
public:		// functions
	inline IrLdStNode(IrnLdStOp s_op, Var* s_varg, IrNode* s_irnarg0,
		IrNode* s_irnarg1)
	{
		__op = (s64)s_op;
		__varg = s_varg;

		init_array(__irnarg, s_irnarg0, s_irnarg1);
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
};

class IrConstNode : public IrNode
{
public:		// functions
	inline IrConstNode(s64 val)
	{
		__const_arg = val;
	}

	virtual bool is_const() const;
};

class IrLabNode : public IrNode
{
public:		// functions
	inline IrLabNode(s64 val)
	{
		__larg[0] = val;
	}
	virtual bool is_lab() const;
};

class IrCondJumpNode : public IrNode
{
public:		// functions
	inline IrCondJumpNode(IrNode* s_dst, s64 s_lab0, s64 s_lab1)
	{
		__irnarg[0] = s_dst;
		init_array(__larg, s_lab0, s_lab1);
	}
	virtual bool is_condjump() const;
};

//class IrCallNode : public IrNode
//{
//public:		// functions
//	inline IrCallNode(std::vector<CallArg>&& s_call_args)
//	{
//		__call_args = std::move(s_call_args);
//	}
//	virtual bool is_call() const;
//};

class IrCleanNode : public IrNode
{
public:		// functions
	inline IrCleanNode(Var* s_varg)
	{
		__varg = s_varg;
	}
	virtual bool is_clean() const;
};

}


#endif		// irnode_classes_hpp
