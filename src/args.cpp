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

#include <iostream>
#include <string.h>

#include <args.hpp>

void aru::args::parse(int argc, char** argv) noexcept
{
	this->argc = argc;
	this->argv = argv;

	if(argc < 2)
		usage(EXIT_FAILURE);

	int c;

	while((c = getopt_long(argc, argv, "-D:h", options, nullptr)) != -1)
	{
		switch(c)
		{
			case 'D':
				parse_key_value(optarg);
				break;

			case 'h':
				usage(EXIT_SUCCESS);
				break;

			case 1:
				operations.push_back(optarg);
				break;

			default:
				exit(EXIT_FAILURE);
				break;
		}
	}

	if(operations.empty())
	{
		usage(EXIT_FAILURE);
	}
}

void aru::args::usage(int exit_code) const noexcept
{
	printf(
		"Usage: %s [-Dkey=value]... -- operation...\n"
		"Expands the keys and solves the operations.\n"
		"\n"
		"Arguments:\n"
		"\t-h, --help             Display help.\n"
		"\t-D, --define key=value Set value to a key.\n",
		argv[0]
	);

	exit(exit_code);
}

void aru::args::parse_key_value(const char* key_value) noexcept
{
	char* name = nullptr;
	int value;

	if(isdigit(key_value[0]) ||
		sscanf(key_value, "%m[^= ]%*[ =]%d", &name, &value) < 2)
	{
		fprintf(stderr, "%s: Bad key=value \"%s\"\n", argv[0], key_value);
		exit(EXIT_FAILURE);
	}

	if(errno != 0)
	{
		perror(argv[0]);
		exit(EXIT_FAILURE);
	}

	variables[name] = value;

	free(name);
}
