#include "src/Server/modelo/Enemigos/Goomba.hpp"
#include "src/Server/modelo/Enemigos/Koopa.hpp"
#include "src/Server/modelo/Mario/Mario.hpp"
#include "EnemigoTest.hpp"

#define CYAN "\u001b[36m"
#define AZUL_CLARO "\e[1;34m"
#define RESET "\x1b[0m"

void EnemigoTest::ejecutar(Assert *testSuite) {
    cout << CYAN"========== Comenzando con las pruebas de los enemigos ==========" RESET << endl;
    cout << AZUL_CLARO"----------TEST 01----------" RESET<< endl;
    test01LosEnemigosSePuedenMover(testSuite);
    cout << AZUL_CLARO"----------TEST 02----------" RESET<< endl;
    test02SeChocaMarioPorArribaConUnEnemigoYElEnemigoMuere(testSuite);
    cout << CYAN"========== Finalizando con las pruebas de los enemigos ==========" RESET << endl;
}

void EnemigoTest::test01LosEnemigosSePuedenMover(Assert *testSuite) {
    auto goomba =  Goomba(0);
    goomba.agregarPosicion(5,5);
    int posInicialGoomba = goomba.obtenerPosicionX();
    auto koopa = Koopa(0);
    koopa.agregarPosicion(10,10);
    int posInicialKoopa = koopa.obtenerPosicionX();

    for (int i = 0; i < 10; ++i) {
        goomba.actualizarPosicion();
        koopa.actualizarPosicion();
    }

    testSuite->assert(goomba.obtenerPosicionX()!=posInicialGoomba,"El Goomba se puede mover");
    testSuite->assert(koopa.obtenerPosicionX()!=posInicialKoopa,"El Koopa se puede mover");
}

void EnemigoTest::test02SeChocaMarioPorArribaConUnEnemigoYElEnemigoMuere(Assert* testSuite){
    Goomba goomba(0);
    goomba.agregarPosicion(5,5);
    Mario mario(0);

    goomba.chocarPorArribaCon(&mario);

    testSuite->assert(goomba.estaMuerto(), "Se murio el Goomba");

}
