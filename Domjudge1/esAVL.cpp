#include <iostream>
#include <fstream>
#include "bintree_eda.h"

using namespace std;

const int INF = 10e8;

struct AVL {
    bool sol;
    int height;
    int max;
    int min;
};

AVL checkAVL(const bintree<int>& tree) {
    if (tree.empty()) {
        return { true, 0, 0, INF};
    }

    // Check left and right
    AVL leftResult = checkAVL(tree.left());
    AVL rightResult = checkAVL(tree.right());

    bool left = leftResult.max < tree.root();
    bool right = rightResult.min > tree.root();

    bool isBalanced = abs(leftResult.height - rightResult.height) <= 1;
    bool equilibred = left && right;
    bool isAVL = leftResult.sol && rightResult.sol && isBalanced && equilibred;

    // The height of the current tree is the maximum height of its subtrees plus one
    int height = max(leftResult.height, rightResult.height) + 1;

    return { isAVL, height, max(rightResult.max, tree.root()), min(leftResult.min, tree.root())};
}

void solve_avl() {
	bintree<int> tree = leerArbol(-1);
    int minVal = 10000, maxVal = 0;
    if (checkAVL(tree).sol) {
        cout << "SI" << endl;
    }
    else {
        cout << "NO" << endl;
    }
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("avl.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	int C;
	cin >> C;
	for (int i = 0; i < C; ++i) solve_avl();
	return 0;
}