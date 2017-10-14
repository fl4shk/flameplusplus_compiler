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


#include "var_class.hpp"

namespace flame_plus_plus
{

s32 Var::builtin_type_size() const
{
	if (anything_matches(type_name(), "u64", "s64"))
	{
		return 64;
	}
	else if (anything_matches(type_name(), "u32", "s32"))
	{
		return 32;
	}
	else if (anything_matches(type_name(), "u16", "s16"))
	{
		return 16;
	}
	else if (anything_matches(type_name(), "u8", "s8"))
	{
		return 8;
	}
	else
	{
		return -1;
	}
}

bool Var::builtin_type_unsgn() const
{
	return (anything_matches(type_name(), "u64", "u32", "u16", "u8"))
}

}
