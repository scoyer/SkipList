run: main.cpp skip_list.o skip_list_node.o
	g++ -o run main.cpp skip_list.o skip_list_node.o
skip_list.o:
	g++ -o skip_list.o -c skip_list.cpp
skip_list_node.o:
	g++ -o skip_list_node.o -c skip_list_node.cpp
run2 : skip_list.o skip_list_node.o
	g++ -o run skip_list.cpp skip_list_node.cpp
#skip_list_node.o :
#	g++ -o skip_list_node.o -c skip_list_node.cpp
#skip_list.o :
#	g++ -o skip_list.o -c skip_list.cpp skip_list_node.cpp
clean:
	rm skip_list.o skip_list_node.o	
rung : skip_list.o skip_list_node.o
	g++ -o run skip_list.cpp skip_list_node.cpp -g
