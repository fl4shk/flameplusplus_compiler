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
TOKEN_STUFF(At, "@") \
TOKEN_STUFF(Semicolon, ";") \



#define LIST_OF_SINGLE_CHAR_OPERATOR_TOKENS(TOKEN_STUFF) \
/* "+", "-", etc */ \
TOKEN_STUFF(Plus, "+") \
TOKEN_STUFF(Minus, "-") \
TOKEN_STUFF(Mult, "*") \
TOKEN_STUFF(Div, "/") \
\
/* "&", "|", "^" */ \
TOKEN_STUFF(BitAnd, "&") \
TOKEN_STUFF(BitOr, "|") \
TOKEN_STUFF(BitXor, "^") \
TOKEN_STUFF(BitNot, "~") \

#define LIST_OF_MULTI_CHAR_OPERATOR_TOKESN(TOKEN_STUFF) \
/* Shift left, shift right */ \
TOKEN_STUFF(BitShL, "<<") \
TOKEN_STUFF(BitShR, ">>")

#define LIST_OF_OPERATOR_TOKENS(TOKEN_STUFF) \
LIST_OF_SINGLE_CHAR_OPERATOR_TOKENS(TOKEN_STUFF) \
LIST_OF_MULTI_CHAR_OPERATOR_TOKESN(TOKEN_STUFF)




#define LIST_OF_IDENT_ISH_TOKENS(TOKEN_STUFF) \
TOKEN_STUFF(Ident, "Identifier")

#define LIST_OF_EXTRA_TOKENS(TOKEN_STUFF) \
/* "Number" */ \
TOKEN_STUFF(NatNum, "NaturalNumber") \
\
LIST_OF_IDENT_ISH_TOKENS(TOKEN_STUFF) \
\
/* "Newline", "EOF", "Bad" */ \
TOKEN_STUFF(Newline, "newline") \
TOKEN_STUFF(Eof, "EOF") \
TOKEN_STUFF(Bad, "Bad")


#define LIST_OF_TOKENS(TOKEN_STUFF) \
LIST_OF_EXTRA_TOKENS(TOKEN_STUFF) \
LIST_OF_OPERATOR_TOKENS(TOKEN_STUFF) \
LIST_OF_PUNCT_TOKENS(TOKEN_STUFF)



#endif		// tokens_and_stuff_hpp
