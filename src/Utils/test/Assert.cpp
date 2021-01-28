#include "Assert.hpp"
using namespace std;
#define ROJO  "\x1b[31m"
#define VERDE "\x1b[32m"
#define RESET "\x1b[0m"

void Assert::assert(int obtenido, int esperado, const string &textoExplicativo) {
    cout << textoExplicativo << ": ";
    if(obtenido==esperado){
        cout << VERDE "OK" RESET<<endl;
        pruebasPasadas++;
    }
    else{
        cout <<ROJO "ERROR" RESET<<endl;
    }
    pruebasTotales++;
}

void Assert::assert(float obtenido, float esperado, float delta, const string &textoExplicativo) {
    cout << textoExplicativo << ": ";
    if(obtenido < esperado + delta && obtenido > esperado - delta){
        cout <<VERDE "OK" RESET<<endl;
        pruebasPasadas++;
    }
    else{
        cout <<ROJO "ERROR" RESET<<endl;
    }
    pruebasTotales++;
}

void Assert::assert(bool condicion, const string &textoExplicativo) {
    cout << textoExplicativo << ": ";
    if(condicion){
        cout <<VERDE "OK" RESET<<endl;
        pruebasPasadas++;
    }
    else{
        cout <<ROJO "ERROR" RESET<<endl;
    }
    pruebasTotales++;
}

void Assert::assert(const string &obtenido, const string &esperado, const string &textoExplicativo) {
    cout << textoExplicativo << ": ";
    if(obtenido == esperado){
        cout <<VERDE "OK" RESET<<endl;
        pruebasPasadas++;
    }
    else{
        cout <<ROJO "ERROR" RESET<<endl;
    }
    pruebasTotales++;
}

int Assert::getPruebasPasadas() const {
    return pruebasPasadas;
}

int Assert::getPruebasTotales() const {
    return pruebasTotales;
}

