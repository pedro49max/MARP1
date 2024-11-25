#include <iostream>
#include<fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


//Definicion del tipo de las baterias

struct bateria {
    //Definicion del tipo de las baterias
    int id; //identificador
    int carga; //carga de la bateria
    int max = 0;
    int i = 1;
    void recarga(int Z) {
        this->carga += max - Z * i;
        i++;
    }
};

typedef priority_queue<bateria, vector<bateria>, greater<bateria>> pq;

bool operator>(bateria p1, bateria p2) {
    return (p1.carga > p2.carga) || (p1.carga == p2.carga && p1.id > p2.id);
}

bool resuelveCaso() {
    int B;
    cin >> B;
    if (!cin)
        return false;
    pq baterias;
    //Lee las B baterias y almacenalas en una estructura llamada baterias
    int carga;
    for (int i = 0; i < B; i++) {
        cin >> carga;
        bateria b; b.carga = b.max = carga;      
        b.id = i + 1;
        baterias.push(b);
    }

     //Lee las R baterias de repuesto y almacenalas en una estructura llamada repuestos
    int R;
    cin >> R;
    vector<bateria> recarga(R);
    for (int i = 0; i < R; i++) {
        cin >> recarga[i].carga;
        recarga[i].max = recarga[i].carga;
        recarga[i].id = i + B + 1;
    }

    int Z, T;
    cin >> Z >> T;
    bool continuee = true;
    auto r = recarga.cbegin();
    while (continuee) {
        bateria lesser = baterias.top(); baterias.pop();
        if (lesser.carga > T) {
            continuee = false;
            baterias.push(lesser);
        }
        else {
            int prev = lesser.carga;
            lesser.recarga(Z);
            if (lesser.carga <= T && prev >= lesser.carga && r != recarga.cend()) {
                lesser.carga = prev + r->carga;
                lesser.i = 1;
                lesser.id = r->id;
                lesser.max = r->max;
                r.operator++();
                baterias.push(lesser);
            }
            else if (lesser.carga > T) {
                baterias.push(lesser);
            }
            else if (lesser.carga <= T && prev < lesser.carga) {
                baterias.push(lesser);
            }
        }
        if (baterias.empty())
            continuee = false;
    }
    if (baterias.empty())
        cout << "ABANDONEN INMEDIATAMENTE LA BASE\n";
    else {
        if (baterias.size() == B)
            cout << "CORRECTO\n";
        else
            cout << "FALLO EN EL SISTEMA\n";
    }
    for (int i = 0; i < B && !baterias.empty(); i++) {
        bateria b = baterias.top(); baterias.pop();
        if(b.carga > 0)
            cout << b.id << " " << b.carga<< endl;
    }

//Analiza el coste de forma justificada

cout << "---\n";
return true;
}



int main() {
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    while (resuelveCaso());
    return 0;
}