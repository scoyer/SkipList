#include "skip_list_node.h"
#include <iostream>

skip_list_node::skip_list_node() : _val(0), _next(0), _down(0), _left(0) {}

skip_list_node::skip_list_node(int _val) : _val(_val), _next(0), _down(0), _left(0) {}

int skip_list_node::val() { return _val; }

void skip_list_node::print() {
	std::cout << "(_val = " << _val << ' ';
	if (_next) std::cout << "_next = " << (_next->_val) << ' ';
	if (_down) std::cout << "_down = " << (_down->_val) << ' ';
	if (_left) std::cout << "_left = " << (_left->_val) << ' ';
	std::cout << ")";
}

//int main() {
//	skip_list_node* node = new skip_list_node(5);
//	node->print();
//	return 0;
//}
