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

#include <new>

#include <node.hpp>

aru::node* aru::node::make_node(std::vector<token>& postfix)
{
	for(token t: postfix)
	{
		t.print();
	}
	return nullptr;
}

aru::node::node(token value):
	value(value),
	left(nullptr),
	right(nullptr)
{};