#include <iostream>
#include <list>
#include <algorithm>

using namespace std;



struct ciudad {
    int barrio;
    list<int> ady;
};

void llenaBarrios(ciudad barrios[]) {

    barrios[0].barrio = 1;
    barrios[0].ady.push_front(1);
    barrios[0].ady.push_front(2);
    barrios[0].ady.push_front(3);
    barrios[0].ady.push_front(5);

    barrios[1].barrio = 2;
    barrios[1].ady.push_front(1);
    barrios[1].ady.push_front(2);
    barrios[1].ady.push_front(5);

    barrios[2].barrio = 3;
    barrios[2].ady.push_front(1);
    barrios[2].ady.push_front(3);
    barrios[2].ady.push_front(4);
    barrios[2].ady.push_front(5);
    barrios[2].ady.push_front(6);
    barrios[2].ady.push_front(7);
    barrios[2].ady.push_front(8);

    barrios[3].barrio = 4;
    barrios[3].ady.push_front(3);
    barrios[3].ady.push_front(4);
    barrios[3].ady.push_front(5);
    barrios[3].ady.push_front(6);
    barrios[3].ady.push_front(11);

    barrios[4].barrio = 5;
    barrios[4].ady.push_front(1);
    barrios[4].ady.push_front(2);
    barrios[4].ady.push_front(3);
    barrios[4].ady.push_front(4);
    barrios[4].ady.push_front(5);
    barrios[4].ady.push_front(10);
    barrios[4].ady.push_front(11);

    barrios[5].barrio = 6;
    barrios[5].ady.push_front(3);
    barrios[5].ady.push_front(4);
    barrios[5].ady.push_front(6);
    barrios[5].ady.push_front(8);
    barrios[5].ady.push_front(11);

    barrios[6].barrio = 7;
    barrios[6].ady.push_front(3);
    barrios[6].ady.push_front(7);
    barrios[6].ady.push_front(8);
    barrios[6].ady.push_front(12);

    barrios[7].barrio = 8;
    barrios[7].ady.push_front(3);
    barrios[7].ady.push_front(6);
    barrios[7].ady.push_front(7);
    barrios[7].ady.push_front(8);
    barrios[7].ady.push_front(9);
    barrios[7].ady.push_front(11);
    barrios[7].ady.push_front(12);

    barrios[8].barrio = 9;
    barrios[8].ady.push_front(8);
    barrios[8].ady.push_front(9);
    barrios[8].ady.push_front(10);
    barrios[8].ady.push_front(11);
    barrios[8].ady.push_front(12);

    barrios[9].barrio = 10;
    barrios[9].ady.push_front(5);
    barrios[9].ady.push_front(9);
    barrios[9].ady.push_front(10);
    barrios[9].ady.push_front(11);

    barrios[10].barrio = 11;
    barrios[10].ady.push_front(4);
    barrios[10].ady.push_front(5);
    barrios[10].ady.push_front(6);
    barrios[10].ady.push_front(8);
    barrios[10].ady.push_front(9);
    barrios[10].ady.push_front(10);
    barrios[10].ady.push_front(11);

    barrios[11].barrio = 12;
    barrios[11].ady.push_front(7);
    barrios[11].ady.push_front(8);
    barrios[11].ady.push_front(9);
    barrios[11].ady.push_front(12);
}


void imprimeSol (list<int> sol) {
    list<int>::iterator it;
    cout << "Hay que poner estaciones en los siguientes barrios: " << endl;;
    for (it = sol.begin() ; it != sol.end() ; it++)
        cout << (*it) << endl;
}


void copiarUniverso(list<int> &u, int universo[], int n) { //Copia mi universo a una lista u
    for (int i = 0; i < n; i++)
        u.push_back(universo[i]);
}

void eliminarB(list<int> & u, ciudad b) { //Me elimina los barrios que ya les construí estación de mi lista u.
    list<int>::iterator it;
    for (it = b.ady.begin() ; it != b.ady.end() ; it++)
        u.remove((*it));

}

bool contiene(list<int>  u, int b) { //Me dice si un barrio está en mi lista u.
    list<int>::iterator it;
    it = find(u.begin(), u.end(), b);
    return it != u.end();
}

int BarriosAdyacentes(list<int> u, ciudad barrios, int m) { //Me devuelve el número de adyacentes al barrio que no tienen estacion de bomberos.
    int suma=0;
    list<int>::iterator it = barrios.ady.begin();
    while ( it != barrios.ady.end() ) {
        if ( contiene(u, (*it)) ) {
            suma++;
        }
        it++;
    }
    return suma;
}

void Solucion (int universo[], ciudad barrios[], int n) { //El algoritmo está basado en la técnica greedy
    list<int> sol;
    list<int> u;
    copiarUniverso(u, universo, n); //Copio mi universo a una lista u para así modificarlo a mi gusto.
    int S=-1;
    while ( !u.empty() ) { //Mientras que tenga elementos en u
        for (int i = 0; i < n; i++) { //Voy a iterar la cantidad de elementos que tenga en mi universo, en éste caso 12.
            if ( S < 0 || BarriosAdyacentes(u,barrios[S],n) < BarriosAdyacentes(u,barrios[i],n) ) // S guarda el indice del set que voy a guardar. Como está basado en greedy, va a tomar el barrio que más adyacentes sin estacion de bombero tenga.
                S = i; //Guardo el indice
        }

        sol.push_back(barrios[S].barrio); //Una vez termina el for guardo en sol el barrio que más adyacentes tiene sin estaciones de bombero.
        eliminarB(u,barrios[S]); //Y elimino todos los barrios a los que ya les construí una estacion de mi lista u.
    }
    imprimeSol(sol);
}


int main()
{
    int n = 12; //Tamaño de mi universo, y en éste caso tambien es mi número de sets.
    int universo[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    list<int> sol;
    ciudad barrios[12];
    llenaBarrios(barrios); //Cargo mis sets (en este caso barrios)
    Solucion(universo,barrios,n);

    return 0;
}
