#include "ColisionadorTest.hpp"
#include "src/Utils/colisiones/Colisionador.hpp"
#include "src/Utils/Utils.hpp"
using namespace std;
#define CYAN "\u001b[36m"
#define AZUL_CLARO "\e[1;34m"
#define RESET "\x1b[0m"


void ColisionadorTest::test01Colisionamos2CuadradosYLaInterseccionEsCorrecta(Assert *testSuite) {

    rectangulo_t rectangulo1 = {0,5,0,5, 5,5};
    rectangulo_t rectangulo2 = {3,7,-1,4,5,4};

    testSuite->assert(tipoDeChoque(rectangulo1, rectangulo2), PRIMERO_DERECHA_SEGUNDO_IZQUIERDA,
                      "Colisiona el primer rectangulo a derecha y el segundo a izquierda");
    testSuite->assert(tipoDeChoque(rectangulo2, rectangulo1), PRIMERO_IZQUIERDA_SEGUNDO_DERECHA,
                      "Colisiona el primer rectangulo a izquierda y el segundo a derecha");
}

void ColisionadorTest::test02Colisionamos2CuadradosYLaInterseccionEsCorrecta(Assert *testSuite) {

    rectangulo_t rectangulo1 = {0,5,3,8, 5,5};
    rectangulo_t rectangulo2 = {3,7,-1,4,5,4};

    testSuite->assert(tipoDeChoque(rectangulo1, rectangulo2), PRIMERO_ABAJO_SEGUNDO_ARRIBA,
                      "Colisiona el primer rectangulo abajo y el segundo arriba");
    testSuite->assert(tipoDeChoque(rectangulo2, rectangulo1), PRIMERO_ARRIBA_SEGUNDO_ABAJO,
                      "Colisiona el primer rectangulo arriba y el segundo abajo");
}

void ColisionadorTest::test03Colisionamos2CuadradosSinInterseccionYNoHayInterseccion(Assert *testSuite) {

    rectangulo_t rectangulo1 = {0,1,0,1, 1,1};
    rectangulo_t rectangulo2 = {2,3,2,3,1,1};

    testSuite->assert(tipoDeChoque(rectangulo1, rectangulo2), SIN_CHOQUE,
                      "NO hay choque entre los rectangulos");
    testSuite->assert(tipoDeChoque(rectangulo2, rectangulo1), SIN_CHOQUE,
                      "No hay choque entre los rectangulos");
}


void ColisionadorTest::ejecutar(Assert *testSuite) {

    cout << CYAN"========== Comenzando con las pruebas de bloque ==========" RESET << endl;
    cout << AZUL_CLARO"----------TEST 01----------" RESET << endl;
    test01Colisionamos2CuadradosYLaInterseccionEsCorrecta(testSuite);
    cout << AZUL_CLARO"----------TEST 02----------" RESET << endl;
    test02Colisionamos2CuadradosYLaInterseccionEsCorrecta(testSuite);
    cout << AZUL_CLARO"----------TEST 03----------" RESET << endl;
    test03Colisionamos2CuadradosSinInterseccionYNoHayInterseccion(testSuite);
    cout << CYAN"========== Finalizando con las pruebas de colisionador ==========" RESET << endl;
}