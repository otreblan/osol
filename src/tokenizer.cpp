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

#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>

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
		case '-':
		case '(':
			tokens.push_back(token{input[0]});
			[[fallthrough]];
		case ' ':
			input[0] = '\0';
			return state::before_operand;

		ARU_NUMERIC_CASES
			tokens.push_back(token{input});
			return state::in_literal;

		ARU_ALPHA_UNDERSCORE_CASES
			tokens.push_back(token{input});
			return state::in_variable;

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
		ARU_ALPHANUMERIC_UNDERSCORE_CASES
			return state::in_variable;

		case ')':
			tokens.push_back(token{input[0]});
			[[fallthrough]];
		case ' ':
			input[0] = '\0';
			return state::before_operator;

		ARU_OPERATOR_CASES
			tokens.push_back(token{input[0]});
			input[0] = '\0';
			return state::before_operand;

		default:
			return state::end;
	}
}


aru::tokenizer::state aru::tokenizer::in_literal(char* input)
{
	if(!input)
		raise(SIGSEGV);

	state next_state = state::end;
	char input_c = input[0];

	switch(input_c)
	{
		ARU_NUMERIC_CASES
			next_state = state::in_literal;
			break;

		case ')':
		case ' ':
			next_state = state::before_operator;
			break;

		ARU_OPERATOR_CASES
			next_state = state::before_operand;
			break;
	}

	if(next_state != state::in_literal)
	{
		input[0] = '\0';
		if(!parse_literal(tokens.back()))
			next_state = state::end;

		if(input_c != ' ')
			if(next_state != state::end)
				tokens.push_back(token{input_c});
	}

	return next_state;
}

aru::tokenizer::state aru::tokenizer::before_operator(char* input)
{
	if(!input)
		raise(SIGSEGV);

	switch(input[0])
	{
		case ')':
			tokens.push_back(token{input[0]});
			[[fallthrough]];
		case ' ':
			input[0] = '\0';
			return state::before_operator;

		ARU_OPERATOR_CASES
			tokens.push_back(token{input[0]});
			input[0] = '\0';
			return state::before_operand;

		default:
			return state::end;
	}
}

aru::tokenizer::state aru::tokenizer::next_state(char* input, state current_state)
{
	if(!input)
		raise(SIGSEGV);

	switch(current_state)
	{
		case state::before_operand:  return before_operand(input);
		case state::in_variable:     return in_variable(input);
		case state::in_literal:      return in_literal(input);
		case state::before_operator: return before_operator(input);

		default:
			return state::end;
	}
}

bool aru::tokenizer::parse_literal(token& literal_token)
{
	errno = 0;

	if(literal_token.type != token_type::STRING)
	{
		fprintf(stderr, "osol: Invalid literal.\n");
		return false;
	}

	char* endptr = nullptr;

	int literal = strtol(literal_token.value.str_ref, &endptr, 10);

	if(errno != 0)
	{
		perror("osol");
		return false;
	}

	if(strlen(endptr) != 0)
	{
		fprintf(stderr,
			"osol: Invalid variable name \"%s\".\n",
			literal_token.value.str_ref
		);
		return false;
	}

	literal_token = token{literal};

	return true;
}
