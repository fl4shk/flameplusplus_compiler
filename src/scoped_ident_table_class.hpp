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


#ifndef scoped_ident_table_class_hpp
#define scoped_ident_table_class_hpp


#include "misc_includes.hpp"
#include "tokens_and_stuff.hpp"
#include "ident_table_class.hpp"

namespace flame_plus_plus
{

// This is kind of like a stack
template<typename Type>
class ScopedIdentTable
{
public:		// typedefs and constants
	typedef IdentTable<Type> OneLevelTable;

	static constexpr s64 builtin_scope_level = 0;
	static constexpr s64 not_found_level = builtin_scope_level - 1;

private:		// variables
	std::vector<OneLevelTable> __table;

	

public:		// functions
	inline ScopedIdentTable()
	{
		make_scope();
	}

	void make_scope() __attribute__((noinline))
	{
		table().push_back(OneLevelTable());
	}

	void del_scope() __attribute__((noinline))
	{
		if (cur_lev() > builtin_scope_level)
		{
			table().pop_back();
		}
	}

	inline auto& at(size_t table_index)
	{
		return __table.at(table_index);
	}
	inline const auto& at(size_t table_index) const
	{
		return __table.at(table_index);
	}

	inline void insert_or_assign(const Type& to_insert_or_assign)
	{
		at(cur_lev()).insert_or_assign(to_insert_or_assign);
	}
	inline void insert_or_assign(Type&& to_insert_or_assign)
	{
		at(cur_lev()).insert_or_assign(std::move(to_insert_or_assign));
	}

	inline void insert_or_assign(size_t level, 
		const Type& to_insert_or_assign)
	{
		at(level).insert_or_assign(to_insert_or_assign);
	}
	inline void insert_or_assign(size_t level, 
		Type&& to_insert_or_assign)
	{
		at(level).insert_or_assign(std::move(to_insert_or_assign));
	}

	s64 find(const std::string& name) __attribute__((noinline))
	{
		// Check builtins first.
		if (table().at(builtin_scope_level).contains(name))
		{
			return builtin_scope_level;
		}

		for (s64 i=cur_lev(); i>=builtin_scope_level; --i)
		{
			if (table().at(i).contains(name))
			{
				return i;
			}
		}

		return not_found_level;
	}

	gen_getter_by_con_ref(table);
	gen_getter_by_ref(table);
	inline s64 cur_lev() const
	{
		return (table().size() - 1);
	}

	void debug_print() __attribute__((noinline))
	{
		for (size_t i=0; i<table().size(); ++i)
		{
			auto& outer_iter = table().at(i);
			for (const auto& inner_iter : outer_iter.table())
			{
				printout("level ", i, ":  \"", inner_iter.first, "\":  ", 
					inner_iter.second.tok()->str(), "\n");
			}
		}
	}
};

}


#endif		// scoped_ident_table_class_hpp
