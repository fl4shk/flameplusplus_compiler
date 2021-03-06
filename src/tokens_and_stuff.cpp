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


#include "tokens_and_stuff.hpp"


namespace flame_plus_plus
{

#define TOKEN_STUFF(varname, value) Tok::varname(value),

const Tok LIST_OF_TOKENS(TOKEN_STUFF) Tok::Dummy;

#undef TOKEN_STUFF



#define TOKEN_STUFF(varname, value) &Tok::varname,

const std::vector<PTok> Tok::tok_vec
({
	LIST_OF_TOKENS(TOKEN_STUFF)
});


#undef TOKEN_STUFF




}
