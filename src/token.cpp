// Operation Solver
// Copyright © 2020 otreblan
//
// osol is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// osol is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with osol.  If not, see <http://www.gnu.org/licenses/>.

#include <cstdio>

#include <token.hpp>
#include <tokenizer.hpp>

aru::token::token(char c):
	type(token_type::CHAR)
{
	value.c = c;
}

aru::token::token(int i):
	type(token_type::INT)
{
	value.i = i;
}

aru::token::token(char* str_ref):
	type(token_type::STRING)
{
	value.str_ref = str_ref;
}

void aru::token::print()
{
	switch(type)
	{
		case token_type::CHAR:
			printf("char:\t%c\n", value.c);
			break;

		case token_type::INT:
			printf("int:\t%d\n", value.i);
			break;

		case token_type::STRING:
			printf("string:\t%s\n", value.str_ref);
			break;
	}
}

bool aru::token::valid_ending()
{
	if(type == token_type::CHAR)
	{
		switch(value.c)
		{
			ARU_OPERATOR_CASES
			case '(':
				return false;
		}
	}
	return true;
}
