#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MONEDATEST_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MONEDATEST_HPP

#include <iostream>
#include <string>
using namespace std;

#include "src/Server/Modelo/Juego/Nivel/Moneda.hpp"
#include "Assert.hpp"

class MonedaTest {
    public:
        static void ejecutar(Assert* testSuite );
        static void test01CuandoSeColisionaConMarioLaMonedaFueAgarrada(Assert* testSuite);

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MONEDATEST_HPP
