#ifndef TREESET_AVL_H_
#define TREESET_AVL_H_

#include <algorithm>
#include <functional>
#include <stack>
#include <stdexcept>
#include <utility>
#include<iostream>

template <class T, class Comparator = std::less<T>>
class Set {
protected:
    struct TreeNode;
    using Link = TreeNode*;
    struct TreeNode {
        T elem;
        Link iz, dr;
        long long altura;
        long long tam_i;
        long long peso;

        TreeNode(T const& e, Link i = nullptr, Link d = nullptr, long long alt = 1, long long ti = 1, long long td = 1)
            : elem(e), iz(i), dr(d), altura(alt), tam_i(ti), peso(td) {}
    };

    Link raiz;
    long long nelems;
    Comparator menor;

public:
    Set(Comparator c = Comparator()) : raiz(nullptr), nelems(0), menor(c) {}

    Set(Set const& other) { copia(other); }

    Set& operator=(Set const& that) {
        if (this != &that) {
            libera(raiz);
            copia(that);
        }
        return *this;
    }

    ~Set() { libera(raiz); }

    bool insert(T const& e) { return inserta(e, raiz); }

    bool empty() const { return raiz == nullptr; }

    int size() const { return nelems; }

    bool contains(T const& e) const { return pertenece(e, raiz); }

    T const kesimo(int k) const {
        if (k < 1 || k > size()) {
            return -1;
        }
        T n = kesimoRec(raiz, k);
        if(n == -1)
            return -1;
        return n;
    }
    void printTree(){
        printTree(raiz);
        std::cout << "\n";
    }

protected:
    void copia(Set const& other) {
        raiz = copia(other.raiz);
        nelems = other.nelems;
        menor = other.menor;
    }

    static Link copia(Link a) {
        if (a == nullptr) return nullptr;
        else return new TreeNode(a->elem, copia(a->iz), copia(a->dr), a->altura, a->tam_i, a->peso);
    }

    static void libera(Link a) {
        if (a != nullptr) {
            libera(a->iz);
            libera(a->dr);
            delete a;
        }
    }

    bool pertenece(T const& e, Link a) const {
        if (a == nullptr) return false;
        else if (menor(e, a->elem)) return pertenece(e, a->iz);
        else if (menor(a->elem, e)) return pertenece(e, a->dr);
        else return true;
    }

    bool inserta(T const& e, Link& a) {
        bool crece;
        if (a == nullptr) {
            a = new TreeNode(e);
            ++nelems;
            crece = true;
        }
        else if (menor(e, a->elem)) {
            crece = inserta(e, a->iz);
            if (crece) reequilibraDer(a);
        }
        else if (menor(a->elem, e)) {
            crece = inserta(e, a->dr);
            if (crece) reequilibraIzq(a);
        }
        else {
            crece = false; // El elemento ya existe
        }
        if (crece) actualizaTam(a);
        return crece;
    }

    void actualizaTam(Link a) {//falla
        if (a != nullptr) {
            int pesoIzq = a->iz ? a->iz->peso : 0;
            int pesoDer = a->dr ? a->dr->peso : 0;
            a->peso = pesoIzq + pesoDer + 1;
            if (a->iz) {
                a->tam_i = a->iz->peso +1;
            }
            else
                a->tam_i = 1;
        }
    }
    void printTree(Link a) {
        if (a->iz) {
            std::cout << "dIz";
            printTree(a->iz);
        }
        std::cout << "(" << a->elem << "," << a->tam_i<<")";
        if (a->dr) {
            std::cout << "dDr";
            printTree(a->dr);
        }
        std::cout << "u";
    }

    T const& kesimoRec(Link a, int k) const {
        long long tam = a->tam_i;
        if (k == tam) 
            return a->elem;
        else if (k <= tam) {
            if (a->iz) {
                return kesimoRec(a->iz, k);
            }
            else
                return -1;
        }       
        else {
            if (a->dr)
                return kesimoRec(a->dr, k - tam);
            else
                return -1;
        }       
    }

    int altura(Link a) const { return a == nullptr ? 0 : a->altura; }

    void rotaDer(Link& k2) {
        Link k1 = k2->iz;
        k2->iz = k1->dr;
        k1->dr = k2;
        k2->altura = std::max(altura(k2->iz), altura(k2->dr)) + 1;
        k1->altura = std::max(altura(k1->iz), altura(k1->dr)) + 1;
        k2 = k1;
        actualizaTam(k2->dr);
        actualizaTam(k2);
    }

    void rotaIzq(Link& k1) {
        Link k2 = k1->dr;
        k1->dr = k2->iz;
        k2->iz = k1;
        k1->altura = std::max(altura(k1->iz), altura(k1->dr)) + 1;
        k2->altura = std::max(altura(k2->iz), altura(k2->dr)) + 1;
        k1 = k2;
        actualizaTam(k1->iz);
        actualizaTam(k1);
    }

    void reequilibraIzq(Link& a) {
        if (altura(a->dr) - altura(a->iz) > 1) {
            if (altura(a->dr->iz) > altura(a->dr->dr)) rotaDerIzq(a);
            else rotaIzq(a);
        }
        else a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
    }

    void reequilibraDer(Link& a) {
        if (altura(a->iz) - altura(a->dr) > 1) {
            if (altura(a->iz->dr) > altura(a->iz->iz)) rotaIzqDer(a);
            else rotaDer(a);
        }
        else a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
    }

    void rotaIzqDer(Link& k3) {
        rotaIzq(k3->iz);
        rotaDer(k3);
    }

    void rotaDerIzq(Link& k1) {
        rotaDer(k1->dr);
        rotaIzq(k1);
    }

public:
    class const_iterator {
    public:
        T const& operator*() const {
            if (act == nullptr) throw std::out_of_range("No hay elemento a consultar");
            return act->elem;
        }

        T const* operator->() const { return &operator*(); }

        const_iterator& operator++() {
            next();
            return *this;
        }

        bool operator==(const_iterator const& that) const { return act == that.act; }

        bool operator!=(const_iterator const& that) const { return !(this->operator==(that)); }

    protected:
        friend class Set;
        Link act;
        std::stack<Link> ancestros;

        const_iterator(Link raiz) { act = first(raiz); }

        const_iterator() : act(nullptr) {}

        Link first(Link ptr) {
            while (ptr && ptr->iz) {
                ancestros.push(ptr);
                ptr = ptr->iz;
            }
            return ptr;
        }

        void next() {
            if (act == nullptr) throw std::out_of_range("El iterador no puede avanzar");
            if (act->dr) act = first(act->dr);
            else if (!ancestros.empty()) {
                act = ancestros.top();
                ancestros.pop();
            }
            else act = nullptr;
        }
    };

    const_iterator begin() const { return const_iterator(raiz); }

    const_iterator end() const { return const_iterator(); }
};

#endif
