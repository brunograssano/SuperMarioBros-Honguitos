
#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_COLISIONADORTEST_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_COLISIONADORTEST_HPP


#include "Assert.hpp"
#include "src/Utils/colisiones/Colisionador.hpp"

class ColisionadorTest {

public:
    static void ejecutar(Assert* testSuite );
    static void test01Colisionamos2CuadradosYLaInterseccionEsCorrecta(Assert* testSuite);
    static void test02Colisionamos2CuadradosYLaInterseccionEsCorrecta(Assert *testSuite);
    static void test03Colisionamos2CuadradosSinInterseccionYNoHayInterseccion(Assert *testSuite);
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_COLISIONADORTEST_HPP
