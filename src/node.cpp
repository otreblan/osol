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
#include <stack>

#include <node.hpp>
#include <tokenizer.hpp>

aru::node* aru::node::make_node(std::vector<token>& postfix)
{
	node* new_node = nullptr;
	std::stack<node*> node_s;
	for(token t: postfix)
	{
		t.print();
		new_node = new (std::nothrow) node(t);

		if(new_node == nullptr)
		{
			while(!node_s.empty())
			{
				delete node_s.top();
				node_s.pop();
			}
			return nullptr;
		}

		switch(t.type)
		{
			case token_type::CHAR:
				switch(t.value.c)
				{
					ARU_OPERATOR_CASES
						new_node->right = node_s.top();
						node_s.pop();
						[[fallthrough]];
					case '~':
						new_node->left = node_s.top();
						node_s.pop();
						break;
				}
				[[fallthrough]];
			case token_type::INT:
			case token_type::STRING:
				node_s.push(new_node);
				break;
		}
	}

	if(node_s.size() != 1)
		return nullptr;

	return node_s.top();
}

int aru::node::solve()
{
	return 0;
}

aru::node::node(token value):
	value(value),
	left(nullptr),
	right(nullptr)
{};
