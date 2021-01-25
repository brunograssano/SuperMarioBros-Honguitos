#include "MarioTest.hpp"
#define CYAN "\u001b[36m"
#define AZUL_CLARO "\e[1;34m"
#define RESET "\x1b[0m"

#include "src/Server/Modelo/Juego/Mario/Mario.hpp"
#include "src/Server/Modelo/Juego/Nivel/Enemigos/Koopa.hpp"

void MarioTest::ejecutar(Assert* testSuite){

	cout << CYAN"========== Comenzando con las pruebas de Mario ==========" RESET << endl;
    cout << AZUL_CLARO"----------TEST 01----------" RESET<< endl;
	test01CuandoPedisAMarioQueSeMuevaADerechaSeMueve(testSuite);
    cout << AZUL_CLARO"----------TEST 02----------" RESET<< endl;
	test02CuandoPedisAMarioQueSeMuevaAIzquierdaSeMueve(testSuite);
    cout << AZUL_CLARO"----------TEST 03----------" RESET<< endl;
    test03AgregarMonedasAMarioSumaCincuentaPuntos(testSuite);
    cout << AZUL_CLARO"----------TEST 04----------" RESET<< endl;
	test04MarioEmpiezaConCeroPuntos(testSuite);
    cout << AZUL_CLARO"----------TEST 05----------" RESET<< endl;
	test05MarioGanaDiezPuntosYDevuelveEsoDeTotal(testSuite);
    cout << AZUL_CLARO"----------TEST 06----------" RESET<< endl;
	test06MarioEmpiezaCon3VidasYLasPierdedependiendoElCaso(testSuite);
    cout << AZUL_CLARO"----------TEST 07----------" RESET<< endl;
    test07MarioPierdeUnaVidaCuandoChocaConPorDerechaConUnKoopa(testSuite);
	cout << CYAN"========== Finalizando con las pruebas de Mario ==========" RESET<< endl;


}

void MarioTest::test01CuandoPedisAMarioQueSeMuevaADerechaSeMueve(Assert* testSuite){
	Mario mario = Mario(0);
	int posicion = mario.obtenerPosicionX();

    mario.actualizarDerechaMario();
	mario.actualizarPosicion();
    mario.actualizarPosicion();

	testSuite->assert(mario.obtenerPosicionX() > posicion,"Mario se mueve a derecha");
}

void MarioTest::test02CuandoPedisAMarioQueSeMuevaAIzquierdaSeMueve(Assert* testSuite){
	Mario mario = Mario(0);
	int posicion = mario.obtenerPosicionX();

    mario.actualizarIzquierdaMario();
	mario.actualizarPosicion();
    mario.actualizarPosicion();

	testSuite->assert(mario.obtenerPosicionX() < posicion,"Mario se mueve a izquierda");
}

void MarioTest::test03AgregarMonedasAMarioSumaCincuentaPuntos(Assert* testSuite){
	Mario mario = Mario(0);

	mario.agregarMoneda();
	testSuite->assert(mario.obtenerPuntos(),50,"Mario tiene 50 puntos");
    mario.agregarMoneda();
    testSuite->assert(mario.obtenerPuntos(),100,"Mario tiene 100 puntos");
    mario.agregarMoneda();
    mario.agregarMoneda();
    testSuite->assert(mario.obtenerPuntos(),200,"Mario tiene 200 puntos");
}

void MarioTest::test04MarioEmpiezaConCeroPuntos(Assert* testSuite){
	Mario mario = Mario(0);
	testSuite->assert(mario.obtenerPuntos(),0,"Mario empieza con 0 puntos");
}

void MarioTest::test05MarioGanaDiezPuntosYDevuelveEsoDeTotal(Assert* testSuite){
	Mario mario = Mario(0);
	mario.agregarPuntos(10);
	testSuite->assert(mario.obtenerPuntos(),10,"Mario tiene 10 puntos");
}

void MarioTest::test06MarioEmpiezaCon3VidasYLasPierdedependiendoElCaso(Assert *testSuite) {
    Mario mario = Mario(0);
    testSuite->assert(mario.obtenerVida(),3,"Mario empieza con 3 vidas");
    mario.perderVida();
    testSuite->assert(mario.obtenerVida(),2,"Mario pierde una vida, le quedan 2");
    mario.hacerseDeFuego();
    testSuite->assert(mario.obtenerVida(),2,"Mario se hace de fuego y tiene 2 vidas");
    mario.perderVida();
    testSuite->assert(mario.obtenerVida(),2,"Mario de fuego pierde una vida, pero sigue teniendo 2");
    mario.perderVida();
    testSuite->assert(mario.obtenerVida(),1,"Mario es normal, pierde vida, le queda 1");
}

void MarioTest::test07MarioPierdeUnaVidaCuandoChocaConPorDerechaConUnKoopa(Assert *testSuite){
    Mario mario = Mario(0);
    Koopa koopa = Koopa(1);
    mario.chocarPorDerechaCon(&koopa);
    testSuite->assert(mario.obtenerVida(), 2, "Mario pierde una vida al chocar con koopa.");
}
