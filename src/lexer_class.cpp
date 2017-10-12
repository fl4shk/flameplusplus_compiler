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


#include "lexer_class.hpp"

namespace flame_plus_plus
{

Lexer::Lexer(WarnError* s_we, SymbolTable* s_sym_tbl, size_t* s_line_num)
	: __we(s_we), __sym_tbl(s_sym_tbl), __line_num(s_line_num)
{
}

void Lexer::advance()
{
	if (next_char() == EOF)
	{
		set_next_tok(&Tok::Eof);
		return;
	}

	set_next_char(getchar());

	if (next_char() == '\n')
	{
		set_line_num(line_num() + 1);
	}
}

void Lexer::lex()
{
	auto handle_multi_combo_2 = [&](int first, PTok first_tok, 
		int second, PTok second_tok) -> bool
	{
		if (next_char() == first)
		{
			advance();

			if (next_char() == second)
			{
				advance();
				set_next_tok(second_tok);
			}
			else
			{
				set_next_tok(first_tok);
			}

			return true;
		}

		return false;
	};

	auto handle_multi_combo_3 = [&](int first, PTok first_tok, 
		int second, PTok second_tok, int third, PTok third_tok) -> bool
	{
		if (next_char() == first)
		{
			advance();

			if (next_char() == second)
			{
				advance();
				set_next_tok(second_tok);
			}
			else if (next_char() == third)
			{
				advance();
				set_next_tok(third_tok);
			}
			else
			{
				set_next_tok(first_tok);
			}

			return true;
		}

		return false;
	};


	while (isspace(next_char()))
	{
		advance();
	}

	if (next_char() == EOF)
	{
		set_next_tok(&Tok::Eof);
	}


	std::string next_str;
	next_str += next_char();




	// Find an identifier
	if (isalpha(next_char()) || (next_char() == '_'))
	{
		next_str = "";
		next_str += next_char();
		advance();

		while (isalnum(next_char()) || (next_char() == '_'))
		{
			next_str += next_char();
			advance();
		}


		Symbol* search = sym_tbl().find(next_str);

		// If we haven't seen a user symbol like this before...
		if (search == nullptr)
		{
			// ...Then create a new symbol
			//printout("Creating a new symbol....\n");
			Symbol to_insert(next_str, &Tok::Ident,
				SymType::UnknownUserIdent);

			//printout((int)to_insert.type(), "\n");

			sym_tbl().insert_or_assign(to_insert);

			set_next_tok(&Tok::Ident);
		}

		else
		{
			set_next_tok(search->tok());
		}

		// Gain slightly more speed by using std::move
		set_next_sym_str(std::move(next_str));

		return;
	}

	// The constant 0... or a hexadecimal or binary number!
	if (next_char() == '0')
	{
		set_next_num(0);
		set_next_tok(&Tok::NatNum);

		advance();

		// Find a constant base 10 natural number
		if (isdigit(next_char()))
		{
			do
			{
				set_next_num((next_num() * 10) + (next_char() - '0'));
				advance();
			} while (isdigit(next_char()));

			return;
		}

		// Hexadecimal number
		if (next_char() == 'x')
		{
			advance();

			if (!isxdigit(next_char()))
			{
				we().expected("Hexadecimal number");
			}

			while (isxdigit(next_char()))
			{
				if ((next_char() >= 'a') && (next_char() <= 'f'))
				{
					set_next_num((next_num() * 16) 
						+ (next_char() - 'a' + 0xa));
				}
				else if ((next_char() >= 'A') && (next_char() <= 'F'))
				{
					set_next_num((next_num() * 16) 
						+ (next_char() - 'A' + 0xa));
				}
				else // if ((next_char() >= '0') && (next_char() <= '9'))
				{
					set_next_num((next_num() * 16) + (next_char() - '0'));
				}

				advance();
			}
		}

		// Binary number
		if (next_char() == 'b')
		{
			advance();

			if ((next_char() != '0') && (next_char() != '1'))
			{
				we().expected("Binary number");
			}

			while ((next_char() == '0') || (next_char() == '1'))
			{
				set_next_num((next_num() * 2) + (next_char() - '0'));

				advance();
			}
		}

		return;
	}

	// Find a constant base 10 natural number
	if (isdigit(next_char()))
	{
		set_next_num(0);

		do
		{
			set_next_num((next_num() * 10) + (next_char() - '0'));
			advance();
		} while (isdigit(next_char()));

		set_next_tok(&Tok::NatNum);

		return;
	}

	// CmpLt, CmpLe, BitShL
	if (handle_multi_combo_3('<', &Tok::CmpLt, 
		'=', &Tok::CmpLe,
		'<', &Tok::BitShL))
	{
		return;
	}

	// CmpGt, CmpGe, BitShR
	if (handle_multi_combo_3('>', &Tok::CmpGt, 
		'=', &Tok::CmpGe,
		'>', &Tok::BitShR))
	{
		return;
	}

	// Div, LineComment
	if (handle_multi_combo_2('/', &Tok::Div,
		'/', &Tok::LineComment))
	{
		return;
	}

	// LogNot, CmpNe
	if (handle_multi_combo_2('!', &Tok::LogNot,
		'=', &Tok::CmpNe))
	{
		return;
	}

	// Equals, CmpEq
	if (handle_multi_combo_2('=', &Tok::Equals, 
		'=', &Tok::CmpEq))
	{
		return;
	}

	// BitAnd, LogAnd
	if (handle_multi_combo_2('&', &Tok::BitAnd,
		'&', &Tok::LogAnd))
	{
		return;
	}

	// BitOr, LogOr
	if (handle_multi_combo_2('|', &Tok::BitOr,
		'|', &Tok::LogOr))
	{
		return;
	}



	// Do this last to permit handling multi-char operator tokens
	if (next_str == "")
	{
	}

	#define TOKEN_STUFF(varname, value) \
		else if (next_str == Tok::varname.str()) \
		{ \
			set_next_tok(&Tok::varname); \
			advance(); \
			return; \
		}

	LIST_OF_PUNCT_TOKENS(TOKEN_STUFF)
	LIST_OF_SINGLE_CHAR_OPERATOR_TOKENS(TOKEN_STUFF)

	#undef TOKEN_STUFF

	set_next_tok(&Tok::Bad);
}


}
