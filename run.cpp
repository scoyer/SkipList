#include <stack>
#include <cstdlib>
#include <vector>
#include <iostream>

class skip_list_node {
public:
	skip_list_node();
	skip_list_node(int value);
	void print();
	skip_list_node *next;
	skip_list_node *left;
	skip_list_node *down;
	int value;
};

skip_list_node::skip_list_node() : next(0), down(0), left(0), value(-1) {}

skip_list_node::skip_list_node(int value) : next(0), down(0), left(0), value(value) {}

void skip_list_node::print() {
	std::cout << "(value=" << value << ' ';
	if (next) std::cout << "next=" << next->value << ' ';
	if (down) std::cout << "down=" << down->value << ' ';
	if (left) std::cout << "left=" << left->value << ' ';
	std::cout << ")";
}

class skip_list {
public:
	skip_list();
	skip_list(std::vector<int>);
	void insert(int);
	bool find(int);
	void remove(int);
	void print();
	int level();
	int size();
	skip_list_node* insert_after(skip_list_node*, int, skip_list_node* down = 0);
	void remove_node(skip_list_node*);
private:
	skip_list_node* head;
	int _level;
	int _size;
};

skip_list::skip_list() : _level(1) {
	head = new skip_list_node();
}

int skip_list::size() { return _size; }

int skip_list::level() { return _level; }

bool skip_list::find(int value) {
	skip_list_node* cur = head;
	int t_level = _level;
	for (;;) {
		if (!cur->next || value < cur->next->value) {
			cur = cur->down;
			if (--t_level) ;
			else return false;
		}
		else {
			if (value == cur->next->value) return true;
			else cur = cur->next;
		}
	}
	return false;
}

int get_rand() {
	return rand() % 2;
}

skip_list_node* skip_list::insert_after(skip_list_node* node, int value, skip_list_node* down) {
	skip_list_node* new_node = new skip_list_node(value);
	new_node->next = node->next;
	if (down) new_node->down = down;
	node->next = new_node;

	if (new_node->next) new_node->next->left = new_node;
	new_node->left = node;

	return new_node;
}

void skip_list::insert(int value) {
	skip_list_node* cur = head;
	std::stack<skip_list_node*> _stack;
	int t_level = _level;

	for (;;) {
		if (!cur->next || value < cur->next->value) {
			if (!--t_level) {
				skip_list_node* down = insert_after(cur, value);
				int max_loop = _stack.size() + 1;
				while (max_loop--) {
					if (!get_rand()) return;
					if (max_loop) {
						down = insert_after(_stack.top(), value, down);
						_stack.pop();
					}
					else {
						_level++;
						skip_list_node* newhead = new skip_list_node();
						newhead->down = head;
						head = newhead;
						insert_after(head, value, down);
					}
				}
				break;
			}
			else {
				_stack.push(cur);
				cur = cur->down;
			}
		}
		else {
			if (value == cur->next->value) return ;
			else cur = cur->next;
		}
	}
}

void skip_list::print() {
	int t_level = 0;
	skip_list_node* cur_head = head;
	while (cur_head) {
		std::cout << "level " << ++t_level << ": ";
		skip_list_node* tmp = cur_head;
		cur_head = cur_head->down;

		while (tmp->next) {
			//std::cout << (tmp->next->value) << " ";
			tmp->next->print();
			tmp = tmp->next;
		}
		std::cout << std::endl;
	}
}

void skip_list::remove_node(skip_list_node* node) {
	skip_list_node* left = node->left;
	skip_list_node* next = node->next;
	left->next = node->next;
	if (next) next->left = node->left;
	if (!left->left && !next) {
		head = left->down;
		delete left;
	}
	delete node;
}

void skip_list::remove(int _value) {
	skip_list_node* cur = head;
	int t_level = _level;
	for (;;) {
		if (!cur->next || _value < cur->next->value) {
			cur = cur->down;
			if (--t_level) ;
			else return ;
		}
		else {
			if (_value == cur->next->value) {
				cur = cur->next;
				while (cur) {
					skip_list_node* tmp = cur->down;
					remove_node(cur);
					cur = tmp;
				}
				return ;
			}
			else cur = cur->next;
		}
	}
}

int main() {
	skip_list* list = new skip_list();
	list->insert(5);
	list->print();
	list->insert(4);
	list->print();
	list->insert(10);
	list->print();
	list->insert(7);
	list->print();
	std::cout << "===============================================" << std::endl;
	list->remove(7);
	list->print();
	list->remove(10);
	list->print();
	list->remove(4);
	list->print();
	list->remove(5);
	list->print();
	return 0;
}
