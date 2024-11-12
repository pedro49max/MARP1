#include<iostream>
#include "TreeSet_AVL.h"
using namespace std;

int main() {
	int n, m; 
	cin >> n;
	while (n != 0) {
		Set<long long> tree;
		for (long long i = 0; i < n; i++) {
			long long x;
			cin >> x;
			//cout << x << endl;
			tree.insert(x);
			//tree.printTree();
		}
		cin >> m;
		for (long long i = 0; i < m; i++) {
			long long x;
			cin >> x;
			if (x < 1 || x > n) {
				cout << "??" << "\n";
			}
			else {
				const long long num = tree.kesimo(x);
				if (num == -1)
					cout << "??" << "\n";
				else
					cout << num << "\n";
			}		
		}
		cout << "---" << "\n";
		cin >> n;
	}
	return 0;
}