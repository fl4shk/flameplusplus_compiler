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


#ifndef var_class_hpp
#define var_class_hpp

#include "misc_includes.hpp"
#include "tokens_and_stuff.hpp"

#include "scoped_ident_table_class.hpp"
#include "symbol_table_class.hpp"

namespace flame_plus_plus
{

class Var
{
private:		// variables (inside the Var class... yay!)
	// What typename was used for this variable?
	// This permits using both built-in type names and custom ones
	Symbol* __type_sym = nullptr;


	// What symbol does this variable belong to?
	Symbol* __sym = nullptr;


	// Scope level of this variable's symbol (must be greater than 0 for
	// variables), as in, how deep we are
	s64 __scope_lev = 1;

	// Which scope number?
	s64 __scope_num = 1;


	// Array dimensions (0 if not an array)
	size_t __dim = 0;

public:		// functions
	inline Var()
	{
	}

	inline Var(Symbol* s_type_sym, Symbol* s_sym, s64 s_scope_lev,
		s64 s_scope_num, size_t s_dim) 
		: __type_sym(s_type_sym), __sym(s_sym),
		__scope_lev(s_scope_lev), __dim(s_dim)
	{
	}

	inline Var(const Var& to_copy) = default;
	inline Var(Var&& to_move) = default;

	inline Var& operator = (const Var& to_copy) = default;
	inline Var& operator = (Var&& to_move) = default;


	inline const std::string& type_name() const
	{
		return type_sym()->name();
	}
	inline const std::string& name() const
	{
		return sym()->name();
	}

	gen_getter_and_setter_by_val(type_sym);
	gen_getter_and_setter_by_val(sym);
	gen_getter_and_setter_by_val(scope_lev);
	gen_getter_and_setter_by_val(scope_num);
	gen_getter_and_setter_by_val(dim);

};

}


#endif		// var_class_hpp
