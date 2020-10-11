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

#include <getopt.h>
#include <unistd.h>

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <tokenizer.hpp>

namespace aru
{

struct args
{
	/// Parses the command line arguments.
	/// argv must exist after parsing, otherwise expresions wont work.
	int parse(int argc, char** argv) noexcept;

	tokenizer tkn;

	std::unordered_map<std::string, int> variables;

private:
	int argc;
	char** argv;

	int usage(int exit_code) const noexcept;

	void parse_key_value(const char* key_value) noexcept;

	static constexpr option options[] =
	{
		{"define",    required_argument, nullptr, 'D'},
		{"help",      no_argument,       nullptr, 'h'},
		{"operation", required_argument, nullptr, 'o'},
		{nullptr,     0,                 nullptr, 0}
	};
};

};
