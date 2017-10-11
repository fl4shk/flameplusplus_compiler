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

namespace flame_plus_plus
{

class Var
{
private:		// variables (inside the Var class... yay!)
	// Obvious
	std::string __name;

	// What typename was used for this variable?
	// This permits using both built-in type names and custom ones,
	// assuming custom ones exist at some point, by using the __typename
	// to find 
	std::string __typname;


	// Scope level of this variable's symbol (must be greater than 0 for
	// variables)
	s64 __scope_lev = 1;


	// Array dimensions (0 if not an array)
	size_t __dim = 0;

public:		// functions
	inline Var()
	{
	}

	inline Var(const std::string& s_name, const std::string& s_typname,
		s64 s_scope_lev, size_t s_dim)
		: __name(s_name), __typname(s_typname), __scope_lev(s_scope_lev),
		__dim(s_dim)
	{
	}

	inline Var(const Var& to_copy) = default;
	inline Var(Var&& to_move) = default;

	inline Var& operator = (const Var& to_copy) = default;
	inline Var& operator = (Var&& to_move) = default;


	gen_getter_and_setter_by_con_ref(name);
	gen_setter_by_rval_ref(name);
	gen_getter_and_setter_by_con_ref(typname);
	gen_setter_by_rval_ref(typname);
	gen_getter_and_setter_by_val(scope_lev);
	gen_getter_and_setter_by_val(dim);

};

}


#endif		// var_class_hpp
