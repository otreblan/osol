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
#include <iostream>

#include <args.hpp>

int aru::args::parse(int argc, char** argv) noexcept
{
	if(argc < 2)
		return usage(EXIT_FAILURE);

	int c;
	bool has_operation = false;
	bool no_errors = true;

	while((c = getopt_long(argc, argv, "-D:ho:", options, nullptr)) != -1)
	{
		switch(c)
		{
			case 'D':
				o_solver.parse_key_value(optarg);
				break;

			case 'h':
				return usage(EXIT_SUCCESS);
				break;

			case 'o':
			case 1:
				no_errors &= o_solver.solve(optarg);
				has_operation = true;
				break;

			default:
				return EXIT_FAILURE;
				break;
		}
	}

	while(optind < argc)
	{
		no_errors &= o_solver.solve(argv[optind++]);
		has_operation = true;
	}

	if(!has_operation)
		return usage(EXIT_FAILURE);

	if(!no_errors)
	{
		fprintf(stderr, "%s: Error while solving.\n", argv[0]);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int aru::args::usage(int exit_code) const noexcept
{
	printf(
		"Usage: %s [ [-Dkey=value] | [-o\"operation\"] ]... [--] operation...\n"
		"Expands the keys and solves the operations.\n"
		"\n"
		"Arguments:\n"
		"\t-h, --help                  Display help.\n"
		"\t-D, --define key=value      Set value to a key.\n"
		"\t-o, --operation \"operation\" Operation to solve.\n",
		program_invocation_name
	);

	return exit_code;
}
