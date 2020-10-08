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
	int c;

	while((c = getopt_long(argc, argv, "D:h", options, nullptr)) != -1)
	{
		switch(c)
		{
			case 'D':
				parse_key_value(optarg);
				break;

			case 'h':
				usage();
				exit(EXIT_SUCCESS);
				break;

			default:
				std::cerr << "osol: " << c << '\n';
				exit(EXIT_FAILURE);
				break;
		}
	}

	if(optind < argc)
	{
		expresions.reserve(argc - optind);

		while(optind < argc)
		{
			expresions.push_back(argv[optind++]);
		}
	}
}

void aru::args::usage() const noexcept
{
	std::cout << "help\n";
}

void aru::args::parse_key_value(const char* key_value) noexcept
{

	char* name = nullptr;
	int value;

	if(isdigit(key_value[0]) ||
		sscanf(key_value, "%m[^= ]%*[ =]%d", &name, &value) < 2)
	{
		std::cerr << "osol: Bad key=value " << key_value << '\n';
		exit(EXIT_FAILURE);
	}

	if(errno != 0)
		perror("osol");

	variables[name] = value;

	free(name);
}
