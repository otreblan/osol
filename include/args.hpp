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

#include <getopt.h>
#include <unistd.h>

#include <vector>
#include <string_view>
#include <unordered_map>

namespace aru
{

struct args
{
	/// Parses the command line arguments.
	/// argv must exist after parsing, otherwise expresions wont work.
	void parse(int argc, char** argv) noexcept;

	std::vector<std::string_view> expresions;

	std::unordered_map<std::string, int> variables;

private:
	void usage() const noexcept;

	void parse_key_value(const char* key_value) noexcept;

	static constexpr option options[] =
	{
		{"define", required_argument, nullptr, 'D'},
		{"help",   no_argument,       nullptr, 'h'},
		{nullptr,  0,                 nullptr, 0}
	};
};

};
