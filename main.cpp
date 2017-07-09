#include <iostream>
#include <fstream>
#include <set>
#include <time.h>
#include <stdlib.h>
#include "skip_list.h"
using namespace std;

typedef pair<int,int> pii;
#define xx first
#define yy second

const int N = 5e6 + 10;

pii p[N], res[N];

clock_t c1, c2;

void start() {
	c1 = clock();
}

void stop() {
	c2 = clock();
}

double pass() {
	return (double) (c2 - c1) / CLOCKS_PER_SEC;
}

int main() {
	srand(time(0));
	for (int i = 0; i < N; i++) {
		p[i].xx = rand() % 3;
		p[i].yy = rand() % N;
	}

	set<int> s;
	skip_list* sl = new skip_list();
	
	int t = 0;
	start();
	for (int i = 0; i < N; i++) {
		switch(p[i].xx) {
			case 1: res[t++].xx = (s.find(p[i].yy) == s.end()); break;
			case 2: s.insert(p[i].yy);							break;
			case 3: s.erase(p[i].yy);							break;
			default: break;
		}
	}
	stop();
	cout << pass() << endl;
	
	start();
	t = 0;
	for (int i = 0; i < N; i++) {
		switch(p[i].xx) {
			case 1: res[t++].yy = (sl->find(p[i].yy) == 0); break;
			case 2: sl->insert(p[i].yy);					break;
			case 3: sl->remove(p[i].yy);					break;
			default: break;
		}
	}
	stop();
	cout << pass() << endl;
	
	for (int i = 0; i < t; i++) {
		if (res[i].xx != res[i].yy) {
			puts("wrong");
		}
	}

	return 0;
}
