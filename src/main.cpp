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

#include <args.hpp>

/**
 * Solo consideras respuestas enteras. Quizás el efecto en las respuestas es porque no consideras decimales
 * 
 * 7/4*((3+1)*3)+5 La respuesta correcta es 26
 * 7/3*((2+-8)*6)+3 La respuesta correcta es 81
 * ((14-45/16*130-(182^2-15*12))) La respuesta correcta es -33295.625
 * 1231-92*2*(5^2)+(412/5*3) La respuesta correcta es -3121.8 
*/

int main(int argc, char *argv[])
{
	aru::args args;

	return args.parse(argc, argv);
}
