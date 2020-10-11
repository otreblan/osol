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

#include <cstring>
#include <iostream>
#include <stack>
#include <vector>
#include <cerrno>

#include <solver.hpp>
#include <tokenizer.hpp>

void aru::solver::parse_key_value(const char* key_value) noexcept
{
	char* name = nullptr;
	int value;

	if(isdigit(key_value[0]) ||
		sscanf(key_value, "%m[^= ]%*[ =]%d", &name, &value) < 2)
	{
		fprintf(stderr, "%s: Bad key=value \"%s\"\n", program_invocation_name, key_value);
		exit(EXIT_FAILURE);
	}

	if(errno != 0)
	{
		perror(program_invocation_name);
		exit(EXIT_FAILURE);
	}

	variables[name] = value;

	free(name);
}

bool aru::solver::solve(char* operation)
{
	tokenizer tkn;
	tkn.split(operation);

	for(auto i: tkn.tokens)
	{
		switch(i.type)
		{
			case token_type::CHAR:
				std::cout << "char: " << i.value.c << '\n';
				break;
			case token_type::INT:
				std::cout << "int: " << i.value.i << '\n';
				break;
			case token_type::STRING:
				std::cout << "string: " << i.value.str_ref << '\n';
				break;
		}
	}

	std::stack<char> t_stack;
	std::vector<token> postfix;

	for(auto t: tkn.tokens)
	{
		switch(t.type)
		{
			case token_type::CHAR:
				switch(t.value.c)
				{
					ARU_OPERATOR_CASES
						break;

					case '(':
						t_stack.push(t.value.c);
						break;

					case ')':
						break;

					case '~':
						break;
				}
				break;

			case token_type::STRING:
			{
				auto v_it = variables.find(t.value.str_ref);

				if(v_it == variables.end())
					return false;

				postfix.push_back(token{v_it->second});
				break;
			}

			case token_type::INT:
				postfix.push_back(t);
				break;
		}
	}

	return true;
}

int aru::solver::precedence(char op)
{
	switch(op)
	{
		case '*':
		case '/':
			return 2;

		case '+':
		case '-':
			return 1;

		default:
			return 0;
	}
}
