//Jorge Polo y Pedro Tobalina
#include <iostream>
#include <fstream> 
#include <vector>
#include <algorithm>

using namespace std;

//Explica la estrategia voraz
//La estrategia consiste en emparejar al que más pese con el que menos pese, y asi tener mas posibilidades de hacer menos viajes.
//Si no pueden ir juntos, el que más pesa va solo y se intentará emparejar al que pesa menos pesa con el siguiente del vector que pesa más en la siguiente iteración del bucle.

int telesilla(int pesoMaximo, vector<int>& pesos) {
    int numeroViajes = 0;
    int beg = 0, end = pesos.size() - 1;
    while (beg <= end) {
        if (pesos[end] + pesos[beg] <= pesoMaximo) {
            ++beg;
            --end;
            ++numeroViajes;
        }
        else {
            --end;
            ++numeroViajes;
        }
    }
    //Implementa la estrategia voraz
    //Coste del algoritmo
    // El coste es O(n) en el peor caso.

    return numeroViajes;
}

/*
Demostracion de correccion de la estrategia voraz
Si v = {x0 .. xn-1} esta ordenado de menor a mayor, sabemos que xn-1 + x0 es la suma más pequeña que encuentra xn-1 porque x0 es el elemento más pequeño.
Asi que si no puede emparejarse con x0, no puede emparejarse con nadie más.

Sabemos que emparejar el máximo relativo con el mánimo relativo cuando su peso no supere el permitido siempre va a llegar a la mejor solución
porque la alternativa sería no emparejarlos, enviar al máximo solo, entonces tener un viaje mas y mantener el mínimo, pero si lo dejamos pasar, podría encontrarse con la solución directamente,
es decir, en menos viajes que si no los hubiesemos emparejado, o en el mejor de los casos para no emparejarlos, nos encotraríamos un emparejamiento no posible, lo que nos llevaría al mismo estado.
En otras palabras, emparejar al maximo con el minimo siempre nos lleva a la mejor solución.
Nuestra solución voraz simpre nos lleva a la solución óptima.

*/

bool resuelveCaso() {
    int a, b, j;
    cin >> a >> b;
    if (!cin) return false;

    vector<int> v(b);
    for (int i = 0; i < b; i++) {
        cin >> j;
        v[i] = j;
    }
    sort(v.begin(), v.end());//O(n(log(n)))
    int sol = telesilla(a, v);
    cout << sol << '\n';
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}