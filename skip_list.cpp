#include "skip_list.h"

skip_list::skip_list() : _level(1), _head(0), _size(0) {
	_head = new skip_list_node();
}

int skip_list::level() { return _level; }

int skip_list::size() { return _size; }

skip_list_node* skip_list::find(int _val) {
	skip_list_node* cur = _head;
	int t_level = _level;
	for (;;) {
		if (!cur->_next || _val < cur->_next->_val) {
			cur = cur->_down;
			if (!--t_level) return 0;
		}
		else {
			cur = cur->_next;
			if (cur->_val == _val) return cur;
		}
	}
	return 0;
}

skip_list_node* skip_list::insert_node(skip_list_node* node, int _val, skip_list_node* _down) {
	skip_list_node* new_node = new skip_list_node(_val);
	new_node->_next = node->_next;
	node->_next = new_node;
	new_node->_down = _down;

	if (new_node->_next) new_node->_next->_left = new_node;
	new_node->_left = node;
	return new_node;
}

void skip_list::insert(int _val) {
	skip_list_node* cur = _head;
	skip_list_node** _stack = new skip_list_node*[_level];
	int t_level = _level, p = 0;

	for (;;) {
		if (!cur->_next || _val < cur->_next->_val) {
			if (!--t_level) {
				break;
			}
			else {
				_stack[p++] = cur;
				cur = cur->_down;
			}
		}
		else {
			cur = cur->_next;
			if (_val == cur->_val) {
				delete [] _stack;
				return ;
			}
		}
	}
	
	skip_list_node* _down = insert_node(cur, _val);
	int max_loop = p + 1;
	while (max_loop--) {
		if (rand() % 2 == 0) break;
		if (max_loop) {
			_down = insert_node(_stack[--p], _val, _down);
		}
		else if (_size){
			_level++;
			skip_list_node* new_head = new skip_list_node();
			new_head->_down = _head;
			_head = new_head;
			insert_node(_head, _val, _down);
		}
	}
	_size++;
	delete [] _stack;
}

void skip_list::remove_node(skip_list_node* node) {
	skip_list_node* _next = node->_next;
	skip_list_node* _left = node->_left;
	_left->_next = _next;
	if (_next) _next->_left = _left;

	if (!_left->_left && !_next && _left->_down) {
		_head = _head->_down;
		_level--;
		delete _left;
	}

	delete node;
}

void skip_list::remove(int _val) {
	skip_list_node* cur = find(_val);
	if (cur == 0) return ;
	
	while (cur) {
		skip_list_node* tmp = cur->_down;
		remove_node(cur);
		cur = tmp;
	}
	_size--;
}

void skip_list::print() {
	skip_list_node* t_head = _head;
	int t_level = 1;
	while (t_head) {
		std::cout << "level = " << t_level++ << ' ';
		skip_list_node* tmp = t_head->_down;
		while (t_head->_next) {
			t_head = t_head->_next;
			t_head->print();
		}
		t_head = tmp;
		std::cout << std::endl;
	}
	std::cout << "level: " << _level << std::endl;
}

//int main() {
//	skip_list* list = new skip_list();
//	list->insert(5);
//	list->print();
//	list->insert(4);
//	list->print();
//	list->insert(10);
//	list->print();
//	list->insert(7);
//	list->print();
//	list->remove(7);
//	list->print();
//	list->remove(10);
//	list->print();
//	list->remove(4);
//	list->print();
//	list->remove(5);
//	list->print();
//	return 0;
//}
