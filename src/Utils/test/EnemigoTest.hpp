#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ENEMIGOTEST_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ENEMIGOTEST_HPP

#include "Assert.hpp"

class EnemigoTest {
    public:
        static void ejecutar(Assert* testSuite);
        static void test01LosEnemigosSePuedenMover(Assert* testSuite);
        static void test02SeChocaMarioPorArribaConUnEnemigoYElEnemigoMuere(Assert *testSuite);
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ENEMIGOTEST_HPP
