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


#ifndef ident_table_class_hpp
#define ident_table_class_hpp


#include "misc_includes.hpp"
#include "tokens_and_stuff.hpp"


namespace flame_plus_plus
{

template<typename Type>
class IdentTable
{
private:		// variables
	std::map<std::string, Type> __table;

public:		// functions
	inline IdentTable()
	{
	}

	// Type accessors
	inline Type& at(const std::string& some_name)
	{
		return __table[some_name];
	}

	inline const Type& at(const std::string& some_name) const
	{
		return __table.at(some_name);
	}

	inline bool contains(const std::string& some_name) const
	{
		return (__table.count(some_name) == 1);
	}

	inline void insert_or_assign(const Type& to_insert_or_assign)
	{
		at(to_insert_or_assign.name()) = to_insert_or_assign;
	}
	inline void insert_or_assign(Type&& to_insert_or_assign)
	{
		at(to_insert_or_assign.name()) = std::move(to_insert_or_assign);
	}

	gen_getter_by_con_ref(table);
};

}



#endif		// ident_table_class_hpp
