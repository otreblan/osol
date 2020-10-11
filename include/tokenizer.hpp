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

#pragma once

#include <vector>

#include <token.hpp>

#define ARU_NUMERIC_CASES \
	case '0':\
	case '1':\
	case '2':\
	case '3':\
	case '4':\
	case '5':\
	case '6':\
	case '7':\
	case '8':\
	case '9':

#define ARU_ALPHA_CASES \
	case 'a':\
	case 'b':\
	case 'c':\
	case 'd':\
	case 'e':\
	case 'f':\
	case 'g':\
	case 'h':\
	case 'i':\
	case 'j':\
	case 'k':\
	case 'l':\
	case 'm':\
	case 'n':\
	case 'o':\
	case 'p':\
	case 'q':\
	case 'r':\
	case 's':\
	case 't':\
	case 'u':\
	case 'v':\
	case 'w':\
	case 'x':\
	case 'y':\
	case 'z':\
	case 'A':\
	case 'B':\
	case 'C':\
	case 'D':\
	case 'E':\
	case 'F':\
	case 'G':\
	case 'H':\
	case 'I':\
	case 'J':\
	case 'K':\
	case 'L':\
	case 'M':\
	case 'N':\
	case 'O':\
	case 'P':\
	case 'Q':\
	case 'R':\
	case 'S':\
	case 'T':\
	case 'U':\
	case 'V':\
	case 'W':\
	case 'X':\
	case 'Y':\
	case 'Z':

#define ARU_ALPHA_UNDERSCORE_CASES \
	ARU_ALPHA_CASES \
	case '_':

#define ARU_ALPHANUMERIC_UNDERSCORE_CASES \
	ARU_ALPHA_UNDERSCORE_CASES \
	ARU_NUMERIC_CASES

#define ARU_OPERATOR_CASES \
	case '-':\
	case '+':\
	case '*':\
	case '/':

namespace aru
{

struct tokenizer
{
	std::vector<token> tokens;

	/// Splits the operation into tokens and puts them into the tokens vector.
	/// The operation string will be modified, and it must still exist after
	/// split() returns.
	bool split(char* operation);

private:
	enum class state
	{
		before_operand,
		in_variable,
		in_literal,
		before_operator,
		end
	};

	state before_operand(char* input);
	state in_variable(char* input);
	state in_literal(char* input);
	state before_operator(char* input);

	state next_state(char* input, state current_state);

	bool parse_literal(token& literal_token);
};

};
