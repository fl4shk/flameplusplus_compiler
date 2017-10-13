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


	// The number of scopes that have been made - 1
	s64 __scope_num = -1;

	

public:		// functions
	inline ScopedIdentTable()
	{
		make_scope();
	}

	void make_scope() __attribute__((noinline))
	{
		table().push_back(OneLevelTable());
		++__scope_num;

		if (scope_num() < 0)
		{
			printerr("ScopedIdentTable::make_scope():  ",
				"Far, FAR too many scopes!\n");
			exit(1);
		}
	}

	void del_scope() __attribute__((noinline))
	{
		if (scope_lev() > builtin_scope_level)
		{
			table().pop_back();
		}
		else
		{
			printerr("ScopedIdentTable::del_scope():  Eek!\n");
			exit(1);
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
		at(scope_lev()).insert_or_assign(to_insert_or_assign);
	}
	inline void insert_or_assign(Type&& to_insert_or_assign)
	{
		at(scope_lev()).insert_or_assign(std::move(to_insert_or_assign));
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

	Type* find(const std::string& some_name) __attribute__((noinline))
	{
		// Check builtins first.
		if (table().at(builtin_scope_level).contains(some_name))
		{
			//return builtin_scope_level;
			return &table().at(builtin_scope_level).at(some_name);
		}

		for (s64 i=scope_lev(); i>=builtin_scope_level; --i)
		{
			if (table().at(i).contains(some_name))
			{
				return &table().at(i).at(some_name);
			}
		}

		return nullptr;
	}

	//inline bool contains(const std::string& some_name) const
	//{
	//	return (find(some_name) != nullptr);
	//}

	bool name_is_builtin(const std::string& some_name) const
	{
		return table().at(builtin_scope_level).contains(some_name);
	}

	gen_getter_by_con_ref(table);
	gen_getter_by_ref(table);
	inline s64 scope_lev() const
	{
		return (table().size() - 1);
	}

	gen_getter_by_val(scope_num);
};

}


#endif		// scoped_ident_table_class_hpp
