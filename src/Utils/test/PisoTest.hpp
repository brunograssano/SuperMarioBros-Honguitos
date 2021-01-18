#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_PISOTEST_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_PISOTEST_HPP

#include "Assert.hpp"

class PisoTest{
    public:
        static void ejecutar(Assert* testSuite);
        static void test01CuandoSeLePideAlPisoLaPosicionDeRespawnYNoHayPozosEsteDevuelveLaMinima(Assert* testSuite);
        static void test02CuandoSeLePideAlPisoLaPosicionDeRespawnYAlPrincipioHayUnPozoEsteDevuelveElFinalDelPozo(Assert* testSuite);
        static void test03CuandoNoHayUnPozoAlComienzoLaPosicionDeRespawnCoincideConLaDeLaCamara(Assert* testSuite);
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_PISOTEST_HPP
