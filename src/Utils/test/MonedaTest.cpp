#include "MonedaTest.hpp"
#define CYAN "\u001b[36m"
#define AZUL_CLARO "\e[1;34m"
#define RESET "\x1b[0m"

#include "src/Server/Modelo/Juego/Mario/Mario.hpp"

void MonedaTest::ejecutar(Assert *testSuite) {
    cout << CYAN"========== Comenzando con las pruebas de moneda ==========" RESET << endl;
    cout << AZUL_CLARO"----------TEST 01----------" RESET << endl;
    test01CuandoSeColisionaConMarioLaMonedaFueAgarrada(testSuite);
    cout << CYAN"========== Finalizando con las pruebas de moneda ==========" RESET << endl;
}

void MonedaTest::test01CuandoSeColisionaConMarioLaMonedaFueAgarrada(Assert *testSuite) {
    Moneda moneda1(0, 0);
    Moneda moneda2(0, 0);
    Moneda moneda3(0, 0);
    Moneda moneda4(0, 0);
    Mario mario(0);
    moneda1.chocarPorDerechaCon(&mario);
    moneda2.chocarPorIzquierdaCon(&mario);
    moneda3.chocarPorArribaCon(&mario);
    moneda4.chocarPorAbajoCon(&mario);
    testSuite->assert(moneda1.fueAgarrada(), "La moneda fue agarrada al colisionar por derecha.");
    testSuite->assert(moneda2.fueAgarrada(), "La moneda fue agarrada al colisionar por izquierda.");
    testSuite->assert(moneda3.fueAgarrada(), "La moneda fue agarrada al colisionar por arriba.");
    testSuite->assert(moneda4.fueAgarrada(), "La moneda fue agarrada al colisionar por abajo.");
}
