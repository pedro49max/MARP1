#include <iostream>
#include<fstream>
#include <vector>
#include <queue>
#include"Grafo.h"
using namespace std;

class OrdenTopologico {
public:
    // g es DAG
    OrdenTopologico(Digrafo const& g) : visit(g.V(), false) {
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v])
                dfs(g, v);
    }
    // devuelve la ordenaci�n topol�gica
    std::deque<int> const& orden() const {
        return _orden;
    }
private:
    std::vector<bool> visit;
    std::deque<int> _orden; // ordenaci�n topol�gica
    void dfs(Digrafo const& g, int v) {
        visit[v] = true;
        for (int w : g.ady(v))
            if (!visit[w])
                dfs(g, w);
        _orden.push_front(v);
    }
};


class CicloDirigido {
public:
    CicloDirigido(Digrafo const& g) : visit(g.V(), false), ant(g.V()),
        apilado(g.V(), false), hayciclo(false) {
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v])
                dfs(g, v);
    }
    bool hayCiclo() const { return hayciclo; }
    deque<int> const& ciclo() const { return _ciclo; }
private:
    

    std::vector<int> ant; // ant[v] = v�rtice anterior en el camino a v
    std::vector<bool> visit; // visit[v] = �se ha alcanzado a v en el dfs?
    std::vector<bool> apilado; // apilado[v] = �est� el v�rtice v en la pila?
    deque<int> _ciclo; // ciclo dirigido (vac�o si no existe)

    bool hayciclo;
    void dfs(Digrafo const& g, int v) {// dfs desde v
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (hayciclo) // si hemos encontrado un ciclo terminamos
                return;
            if (!visit[w]) { // encontrado un nuevo v�rtice, seguimos
                ant[w] = v; dfs(g, w);
            }
            else if (apilado[w]) { // hemos detectado un ciclo
         // se recupera retrocediendo
                hayciclo = true;
                for (int x = v; x != w; x = ant[x])
                    _ciclo.push_front(x);
                _ciclo.push_front(w); _ciclo.push_front(v);
            }
        }
        apilado[v] = false;
    }
};



int main() {
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int N, M;
    while (cin >> N >> M) {
        vector<int> in_degree(N, 0);
        deque<int> result;
        Digrafo grafo(N);
        bool posible = true;
        for(int i = 0; i < M; i ++){
            int a, b;
            cin >> a >> b;
            a--; b--;
            //cout << a << " " << b << endl;
            grafo.ponArista(a,b);
        }
        CicloDirigido dg(grafo);

        //si hay ciclo, imposible
        if (dg.hayCiclo()) {//O(V + A)
            cout << "Imposible" << endl;
        }//Otro caso, orden topologico
        else {
            OrdenTopologico oro (grafo);
            result = oro.orden();//O(V + A)
            cout << result.front() +1 ; result.pop_front();
            while (!result.empty()) {
                cout << " " << result.front() + 1; result.pop_front();
            }
            cout << endl;
        }
    }

    return 0;
}
