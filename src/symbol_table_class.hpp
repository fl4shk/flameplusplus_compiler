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



#ifndef symbol_table_class_hpp
#define symbol_table_class_hpp

#include "misc_includes.hpp"
#include "tokens_and_stuff.hpp"

#include "scoped_ident_table_class.hpp"

namespace flame_plus_plus
{

enum class SymType
{
	Keyword,
	BuiltinTypename,


	// Used by the lexer, fixed by the parser
	UnknownUserIdent,

	VarName,
	FuncName,
	StructName,
};


class Symbol
{
private:		// variables
	std::string __name;

	PTok __tok = nullptr;

	SymType __type;

public:		// functions
	inline Symbol()
	{
	}
	inline Symbol(PTok s_tok, SymType s_type)
		: __name(s_tok->str()), __tok(s_tok), __type(s_type)
	{
	}
	inline Symbol(const std::string& s_name, PTok s_tok, SymType s_type) 
		: __name(s_name), __tok(s_tok), __type(s_type)
	{
	}
	inline Symbol(std::string&& s_name, PTok s_tok, SymType s_type)
		: __name(std::move(s_name)), __tok(s_tok), __type(s_type)
	{
	}
	inline Symbol(const Symbol& to_copy) = default;
	inline Symbol(Symbol&& to_move) = default;

	inline Symbol& operator = (const Symbol& to_copy) = default;
	inline Symbol& operator = (Symbol&& to_move) = default;

	gen_getter_and_setter_by_con_ref(name);
	gen_setter_by_rval_ref(name);
	gen_getter_and_setter_by_val(tok);
	gen_getter_and_setter_by_val(type);
};

//typedef IdentTable<Symbol> SymbolTable;
//typedef ScopedIdentTable<Symbol> SymbolTable;


class SymbolTable : public ScopedIdentTable<Symbol>
{
public:		// functions
	void debug_print() __attribute__((noinline))
	{
		for (size_t i=0; i<table().size(); ++i)
		{
			auto& outer_iter = table().at(i);
			for (const auto& inner_iter : outer_iter.table())
			{
				printout("level ", i, ":  \"", inner_iter.first, "\":  ", 
					inner_iter.second.tok()->str(), ", ", 
					inner_iter.second.type(), "\n");
			}
		}
	}

	void debug_print_old() __attribute__((noinline))
	{
		for (size_t i=0; i<__old_table.size(); ++i)
		{
			auto& outer_iter = __old_table.at(i);
			for (const auto& inner_iter : outer_iter.table())
			{
				printout("level ", i, ":  \"", inner_iter.first, "\":  ", 
					inner_iter.second.tok()->str(), ", ", 
					inner_iter.second.type(), "\n");
			}
		}
	}
};

}


std::ostream& operator << (std::ostream& os, 
	const flame_plus_plus::SymType& to_print);

#endif		// symbol_table_class_hpp
