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

#include <csignal>

#include <tokenizer.hpp>

void aru::tokenizer::split(char* operation)
{
	state current_state = state::before_operand;

	while(current_state != state::end)
	{
		current_state = next_state(operation++, current_state);
	}
}

aru::tokenizer::state aru::tokenizer::before_operand(char* input)
{
	if(!input)
		raise(SIGSEGV);

	switch(input[0])
	{
		default:
			return state::end;
	}
}

aru::tokenizer::state aru::tokenizer::begin_variable(char* input)
{
	if(!input)
		raise(SIGSEGV);

	switch(input[0])
	{
		default:
			return state::end;
	}
}

aru::tokenizer::state aru::tokenizer::in_variable(char* input)
{
	if(!input)
		raise(SIGSEGV);

	switch(input[0])
	{
		default:
			return state::end;
	}
}

aru::tokenizer::state aru::tokenizer::begin_literal(char* input)
{
	if(!input)
		raise(SIGSEGV);

	switch(input[0])
	{
		default:
			return state::end;
	}
}

aru::tokenizer::state aru::tokenizer::in_literal(char* input)
{
	if(!input)
		raise(SIGSEGV);

	switch(input[0])
	{
		default:
			return state::end;
	}
}

aru::tokenizer::state aru::tokenizer::before_operator(char* input)
{
	if(!input)
		raise(SIGSEGV);

	switch(input[0])
	{
		default:
			return state::end;
	}
}

aru::tokenizer::state aru::tokenizer::next_state(char* input, state current_state)
{
	switch(current_state)
	{
		case state::before_operand:  return before_operand(input);
		case state::begin_variable:  return begin_variable(input);
		case state::in_variable:     return in_variable(input);
		case state::begin_literal:   return begin_literal(input);
		case state::in_literal:      return in_literal(input);
		case state::before_operator: return before_operator(input);

		default:
			return state::end;
	}
}
