//Pedro Tobalina and Jorge polo
#include<iostream>
#include"bintree_eda.h"
using namespace std;

bintree<int> readTree();
bool isAVLTree(const bintree<int>& tree, int& height, int& minimum, int& maximum);

int main(){
    int n;
    cin >> n;
    for(int i  =0 ; i < n; i++){
        bintree<int> tree = leerArbol(-1);
        int j = 0, min = -1, max = -1;
        if(isAVLTree(tree, j, min, max)){
            cout << "SI" << endl;
        }
        else
            cout << "NO" << endl;
    }

    return 0;
}

bintree<int> readTree(){
    int raiz;
   std::cin >> raiz;
   if (raiz == -1) { // es un árbol vacío
      return {};
   } else { // leer recursivamente los hijos
      auto iz = readTree();
      auto dr = readTree();
      return {iz, raiz, dr};
   }
}
bool isAVLTree(const bintree<int>&tree, int& height, int &minimum, int &maximum) {//hay que chequear que todo el lado izq sea menor, y que todo el lado der sea mayor
    if (tree.empty()) {
        height = 0;
        return true;
    }

    int leftHeight = 0, rightHeight = 0, minLeft = -1, minRight = -1, maxLeft = -1, maxRight = -1;
    //chequeo si los hijos son avl
    bool isLeftAVL = isAVLTree(tree.left(), leftHeight, minLeft, maxLeft);
    bool isRightAVL = isAVLTree(tree.right(), rightHeight,  minRight, maxRight);
    if (tree.left().empty()) {
        minLeft = tree.root();
        maxLeft = tree.root();
    }
    if (tree.right().empty()) {
        minRight = tree.root();
        minLeft = tree.root();
    }

    // Verificar propiedad de búsqueda
    if (!isLeftAVL || !isRightAVL) {//Si uno de los lados no es avl, el arbol no es avl
        return false;
    }

    if (!tree.left().empty() && maxLeft >= tree.root()) {
        return false;
    }

    if (!tree.right().empty() && minRight <= tree.root()) {
        return false;
    }

    // Comprobar equilibrio
    if (abs(leftHeight - rightHeight) > 1) {
        return false;
    }

    height = max(leftHeight, rightHeight) + 1;

    maximum = max(tree.root(), maxLeft);
    maximum = max(maximum, maxRight);
    
    minimum = min(tree.root(), minLeft);
    minimum = min(minimum, minRight);
    
    return true;
}