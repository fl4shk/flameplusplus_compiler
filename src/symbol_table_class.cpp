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


#include "symbol_table_class.hpp"


std::ostream& operator << (std::ostream& os, 
	const flame_plus_plus::SymType& to_print)
{
	using flame_plus_plus::SymType;

	switch (to_print)
	{
		case SymType::Keyword:
			os << "Keyword";
			break;

		case SymType::BuiltinTypename:
			os << "BuiltinTypename";
			break;

		case SymType::VarName:
			os << "VarName";
			break;

		case SymType::FuncName:
			os << "FuncName";
			break;

		case SymType::StructName:
			os << "StructName";
			break;

		default:
			os << "Unknown";
			break;
	}

	return os;
}
