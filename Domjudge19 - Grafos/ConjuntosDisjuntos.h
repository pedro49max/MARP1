//
//  ConjuntosDisjuntos.h
//
//  Implementación de estructuras de partición o conjuntos disjuntos
//  con unión por tamaño y compresión de caminos
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2015-2019  Alberto Verdejo
//

#ifndef CONJUNTOSDISJUNTOS_H_
#define CONJUNTOSDISJUNTOS_H_

#include <vector>
#include <iostream>

class ConjuntosDisjuntos {
public:

    // crea una estructura de partición con los elementos 0..N-1, cada uno en un conjunto
    ConjuntosDisjuntos(int N) : nelems(N), ncjtos(nelems), id(nelems, -1) {}

    // devuelve el número de conjuntos disjuntos
    int num_cjtos() const { return ncjtos; }

    //  devuelve el identificador del conjunto que contiene a p
    int buscar(int p) const {
        if (id.at(p) < 0) // es una raíz
            return p;
        else
            return id[p] = buscar(id[p]);
    }

    // unir los conjuntos que contengan a p y q
    void unir(int p, int q) {
        auto i = buscar(p);
        auto j = buscar(q);
        if (i == j) return;
        //std::cout << "Uniendo " << p << " y " << q << "\n";
        if (id[i] < id[j]) { // i es la raíz del mayor árbol
            id[i] += id[j]; id[j] = int(i);
            //std::cout << " El conjunto " << i << " ahora tiene un peso de " << -id[i] << "\n";
        }
        else {
            id[j] += id[i]; id[i] = int(j);
            //std::cout << " El conjunto " << j << " ahora tiene un peso de " << -id[j] << "\n";
        }
        --ncjtos;
    }

    int tam(int p) const {
        //std::cout << " El conjunto " << buscar(p) << " ahora tiene un peso de " << -id[buscar(p)] << "\n";
        return -id[buscar(p)];
    }

    bool unidos(int p, int q) const {
        return buscar(p) == buscar(q);
    }

protected:
    int nelems;           // los elementos son 0 .. nelems-1
    int ncjtos;           // número de conjuntos disjuntos
    mutable std::vector<int> id;  // si id[i]>=0 es el padre de i, si no es el tamaño del conjunto de i

};


#endif
