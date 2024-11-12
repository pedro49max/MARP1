#include<iostream>
#include<vector>
#include"TreeSet_AVL.h"
using namespace std;

void resolve(Set<int> &avltree) {
	int cost = 0, result;
	if (avltree.size() > 1) {
		//working with the first two operands
		while (avltree.size() > 1) {
			auto it = avltree.begin();
			int a = *it;
			avltree.erase(a);
			it = avltree.begin();
			int b = *it;
			avltree.erase(b);
			result = a + b;
			cout << a << " " << b << endl;
			avltree.insert(result);
			cost +=result;
		}

	}
	// Output the total effort aech case
	cout << cost << endl;
}

int main() {
	int n;
	cin >> n;
	while (n != 0) {
		Set<int> avltree;
		int x;
		for (int i = 0; i < n; i++) {//reading the operands
			cin >> x;
			avltree.insert(x);
		}
		resolve(avltree);
		cin >> n;
	}

	return 0;
}