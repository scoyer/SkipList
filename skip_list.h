#include "skip_list_node.h"
#include <iostream>
#include <stack>
#include <cstdlib>

class skip_list {
public:
	skip_list();
	skip_list_node* find(int);
	void insert(int);
	void remove(int);
	void print();
	int level();
	int size();
private:
	skip_list_node* insert_node(skip_list_node*, int, skip_list_node* _down = 0);
	void remove_node(skip_list_node*);
	int _level;
	int _size;
	skip_list_node* _head;
};
