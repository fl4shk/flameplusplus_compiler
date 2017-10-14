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


#ifndef ircode_class_hpp
#define ircode_class_hpp

#include "irnode_classes.hpp"

namespace flame_plus_plus
{


// IrNode List, and also part of the optimizer
class IrCode
{
public:		// variables
	static const bool optimize;
	IrNode head;


public:		// functions
	IrCode();
	~IrCode();



	int irn_to_index(IrNode* irn) const;


	//IrNode* mkirn();
	void rmirn(IrNode* irn);

	IrNode* mk_binop(IrnBinOp op, IrNode* a, IrNode* b, bool unsgn);
	IrNode* mk_unop(IrnUnOp op, IrNode* irn0);


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
	IrNode* mk_condjump(IrNode* dst, s64 lab0, s64 lab1);


	// Yes, this is a "make clean" joke....
	// Okay, it wasn't originally intended as one.  Eh.
	IrNode* mk_clean(Var* varg);




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

	inline IrNode* __append(IrNode* irn)
	{
		__relink_irn(irn, head.prev);
		return irn;
	}


	IrNode* __mk_ldop(IrnLdStOp op, Var* varg);
	IrNode* __mk_ldxop(IrnLdStOp op, Var* varg, IrNode* irn0);
	IrNode* __mk_stop(IrnLdStOp op, Var* varg, IrNode* irn1);
	IrNode* __mk_stxop(IrnLdStOp op, Var* varg, IrNode* irn0, IrNode* irn1);
};


}

#endif		// ircode_class_hpp
