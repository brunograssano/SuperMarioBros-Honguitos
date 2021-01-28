#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_TUBERIATEST_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_TUBERIATEST_HPP


#include "src/Server/Modelo/Juego/Nivel/Bloques/Tuberia.hpp"
#include "Assert.hpp"

class TuberiaTest {
    public:
        static void ejecutar(Assert* testSuite );
        static void test01UnaTuberiaRespondeCorrectamenteSiColisionaContraOtra(Assert* testSuite);

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_TUBERIATEST_HPP
