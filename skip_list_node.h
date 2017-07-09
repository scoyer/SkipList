class skip_list_node {
friend class skip_list;
public:
	skip_list_node();
	skip_list_node(int _val);
	int val();
	void print();
private:
	int _val;
	skip_list_node* _next;
	skip_list_node* _down;
	skip_list_node* _left;
};
