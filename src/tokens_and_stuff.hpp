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


#ifndef tokens_and_stuff_hpp
#define tokens_and_stuff_hpp

#include "misc_includes.hpp"



#define LIST_OF_COMMENT_TOKENS(TOKEN_STUFF) \
TOKEN_STUFF(LineComment, "//")

#define LIST_OF_PUNCT_TOKENS(TOKEN_STUFF) \
/* "." */ \
TOKEN_STUFF(Period, ".") \
\
/* "(", ")" */ \
TOKEN_STUFF(LParen, "(") \
TOKEN_STUFF(RParen, ")") \
\
/* "[", "]" */ \
TOKEN_STUFF(LBracket, "[") \
TOKEN_STUFF(RBracket, "]") \
\
/* "{", "}" */ \
TOKEN_STUFF(LBrace, "{") \
TOKEN_STUFF(RBrace, "}") \
\
/* "=", ";", ",", etc. */ \
TOKEN_STUFF(Equals, "=") \
LIST_OF_COMMENT_TOKENS(TOKEN_STUFF) \
TOKEN_STUFF(Comma, ",") \
TOKEN_STUFF(Colon, ":") \
/* TOKEN_STUFF(At, "@") */ \
TOKEN_STUFF(Semicolon, ";") \


#define LIST_OF_SINGLE_CHAR_COMPARISON_OPERATOR_TOKENS(TOKEN_STUFF) \
/* "<", ">" */ \
TOKEN_STUFF(CmpLt, "<") \
TOKEN_STUFF(CmpGt, ">") \

#define LIST_OF_MULTI_CHAR_COMPARISON_OPERATOR_TOKENS(TOKEN_STUFF) \
/* "==", "!=", "&&", "||", etc. */ \
TOKEN_STUFF(CmpEq, "==") \
TOKEN_STUFF(CmpNe, "!=") \
TOKEN_STUFF(CmpLe, "<=") \
TOKEN_STUFF(CmpGe, ">=") \
TOKEN_STUFF(LogAnd, "&&") \
TOKEN_STUFF(LogOr, "||" )

#define LIST_OF_COMPARISON_OPERATOR_TOKENS(TOKEN_STUFF) \
LIST_OF_SINGLE_CHAR_COMPARISON_OPERATOR_TOKENS(TOKEN_STUFF) \
LIST_OF_MULTI_CHAR_COMPARISON_OPERATOR_TOKENS(TOKEN_STUFF) 

#define LIST_OF_SINGLE_CHAR_OPERATOR_TOKENS(TOKEN_STUFF) \
/* "+", "-", etc */ \
TOKEN_STUFF(Plus, "+") \
TOKEN_STUFF(Minus, "-") \
TOKEN_STUFF(Mult, "*") \
TOKEN_STUFF(Div, "/") \
TOKEN_STUFF(Mod, "%") \
\
/* "&", "|", "^" */ \
TOKEN_STUFF(BitAnd, "&") \
TOKEN_STUFF(BitOr, "|") \
TOKEN_STUFF(BitXor, "^") \
TOKEN_STUFF(BitNot, "~") \
\
/* "!" */ \
TOKEN_STUFF(LogNot, "!") 

#define LIST_OF_MULTI_CHAR_OPERATOR_TOKENS(TOKEN_STUFF) \
/* Shift left, shift right */ \
TOKEN_STUFF(BitShL, "<<") \
TOKEN_STUFF(BitShR, ">>") \

#define LIST_OF_OPERATOR_TOKENS(TOKEN_STUFF) \
LIST_OF_SINGLE_CHAR_OPERATOR_TOKENS(TOKEN_STUFF) \
LIST_OF_MULTI_CHAR_OPERATOR_TOKENS(TOKEN_STUFF)




#define LIST_OF_IDENT_ISH_TOKENS(TOKEN_STUFF) \
TOKEN_STUFF(Ident, "Identifier")

#define LIST_OF_EXTRA_TOKENS(TOKEN_STUFF) \
/* "Number" */ \
TOKEN_STUFF(NatNum, "NaturalNumber") \
\
LIST_OF_IDENT_ISH_TOKENS(TOKEN_STUFF) \
\
/* "EOF", "Bad" */ \
/* TOKEN_STUFF(Newline, "newline") */ \
TOKEN_STUFF(Eof, "EOF") \
TOKEN_STUFF(Bad, "Bad")


#define LIST_OF_KEYWORD_TOKENS(TOKEN_STUFF) \
/* "if", "else", "while", etc. */ \
TOKEN_STUFF(If, "if") \
TOKEN_STUFF(Else, "else") \
TOKEN_STUFF(While, "while") \


#define LIST_OF_UNSGN_INT_TYPENAMES(TOKEN_STUFF) \
/* "u8", "u16", "u32", "u64" */ \
TOKEN_STUFF(U8, "u8") \
TOKEN_STUFF(U16, "u16") \
TOKEN_STUFF(U32, "u32") \
TOKEN_STUFF(U64, "u64") \

#define LIST_OF_SGN_INT_TYPENAMES(TOKEN_STUFF) \
/* "u8", "u16", "u32", "u64" */ \
TOKEN_STUFF(S8, "s8") \
TOKEN_STUFF(S16, "s16") \
TOKEN_STUFF(S32, "s32") \
TOKEN_STUFF(S64, "s64") \

#define LIST_OF_DEFAULT_INT_TYPENAME_TOKENS(TOKEN_STUFF) \
LIST_OF_UNSGN_INT_TYPENAMES(TOKEN_STUFF) \
LIST_OF_SGN_INT_TYPENAMES(TOKEN_STUFF)


#define LIST_OF_BUILTIN_SYM_TOKENS(TOKEN_STUFF) \
LIST_OF_KEYWORD_TOKENS(TOKEN_STUFF) \
LIST_OF_DEFAULT_INT_TYPENAME_TOKENS(TOKEN_STUFF) \


#define LIST_OF_TOKENS(TOKEN_STUFF) \
LIST_OF_EXTRA_TOKENS(TOKEN_STUFF) \
LIST_OF_OPERATOR_TOKENS(TOKEN_STUFF) \
LIST_OF_PUNCT_TOKENS(TOKEN_STUFF) \
LIST_OF_COMPARISON_OPERATOR_TOKENS(TOKEN_STUFF) \
LIST_OF_BUILTIN_SYM_TOKENS(TOKEN_STUFF) 


namespace flame_plus_plus
{


class Tok;
typedef const Tok* PTok;

// Why is this class holding all the instances of itself?  Jeez.  It works
// fine; don't get me wrong.  It's just a little weird.
class Tok
{
private:		// variables
	std::string __str;

public:		// constants
	#define TOKEN_STUFF(varname, value) varname, 

	static const Tok LIST_OF_TOKENS(TOKEN_STUFF) Dummy;

	#undef TOKEN_STUFF

	static const std::vector<PTok> tok_vec;

public:		// functions
	inline Tok()
	{
	}
	inline Tok(const std::string& s_str) : __str(s_str)
	{
	}
	inline Tok(std::string&& s_str) : __str(std::move(s_str))
	{
	}

	inline Tok(const Tok& to_copy) = default;
	inline Tok(Tok&& to_move) = default;
	inline Tok& operator = (const Tok& to_copy) = default;
	inline Tok& operator = (Tok&& to_move) = default;


	inline bool operator == (const Tok& to_cmp) const
	{
		return (str() == to_cmp.str());
	}
	inline bool operator != (const Tok& to_cmp) const
	{
		return (str() != to_cmp.str());
	}

	inline bool operator < (const Tok& to_cmp) const
	{
		return (str() < to_cmp.str());
	}

	gen_getter_by_con_ref(str)

	gen_setter_by_con_ref(str)
	gen_setter_by_rval_ref(str)

};

}


#endif		// tokens_and_stuff_hpp
