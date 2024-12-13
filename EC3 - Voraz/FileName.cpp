//Jorge Polo y Pedro Tobalina
#include <iostream>
#include <fstream> 
#include <vector>
#include <algorithm>

using namespace std;

//Explica la estrategia voraz
//La estrategia consiste en emparejar al que m�s pese con el que menos pese, y asi tener mas posibilidades de hacer menos viajes.
//Si no pueden ir juntos, el que m�s pesa va solo y se intentar� emparejar al que pesa menos pesa con el siguiente del vector que pesa m�s en la siguiente iteraci�n del bucle.

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
Si v = {x0 .. xn-1} esta ordenado de menor a mayor, sabemos que xn-1 + x0 es la suma m�s peque�a que encuentra xn-1 porque x0 es el elemento m�s peque�o.
Asi que si no puede emparejarse con x0, no puede emparejarse con nadie m�s.

Sabemos que emparejar el m�ximo relativo con el m�nimo relativo cuando su peso no supere el permitido siempre va a llegar a la mejor soluci�n
porque la alternativa ser�a no emparejarlos, enviar al m�ximo solo, entonces tener un viaje mas y mantener el m�nimo, pero si lo dejamos pasar, podr�a encontrarse con la soluci�n directamente,
es decir, en menos viajes que si no los hubiesemos emparejado, o en el mejor de los casos para no emparejarlos, nos encotrar�amos un emparejamiento no posible, lo que nos llevar�a al mismo estado.
En otras palabras, emparejar al maximo con el minimo siempre nos lleva a la mejor soluci�n.
Nuestra soluci�n voraz simpre nos lleva a la soluci�n �ptima.

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