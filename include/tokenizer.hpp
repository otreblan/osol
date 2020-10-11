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

namespace aru
{

struct tokenizer
{
	std::vector<token> tokens;

	/// Splits the operation into tokens and puts them into the tokens vector.
	/// The operation string will be modified, and it must still exist after
	/// split() returns.
	void split(char* operation);

private:
	enum class state
	{
		before_operand,
		begin_variable,
		in_variable,
		begin_literal,
		in_literal,
		before_operator,
		end
	};

	state before_operand(char* input);
	state begin_variable(char* input);
	state in_variable(char* input);
	state begin_literal(char* input);
	state in_literal(char* input);
	state before_operator(char* input);

	state next_state(char* input, state current_state);
};

};
