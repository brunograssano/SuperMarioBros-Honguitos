#include <src/Server/modelo/Podio.hpp>
#include "PodioTest.hpp"
#include <vector>
#define CYAN "\u001b[36m"
#define AZUL_CLARO "\e[1;34m"
#define RESET "\x1b[0m"

void PodioTest::ejecutar(Assert *testSuite) {
    cout << CYAN"========== Comenzando con las pruebas del Lector ==========" RESET << endl;
    cout << AZUL_CLARO"----------TEST 01----------" RESET << endl;
    test01CuandoLePedisAlPodioQueTeDeElPodioParcialElPrimeroEsElDeMayorPuntaje(testSuite);
    cout << AZUL_CLARO"----------TEST 01----------" RESET << endl;
    test02CuandoLePedisAlPodioQueTeDeElPodioParcialElPrimeroEsElDeMayorPuntaje(testSuite);
    cout << CYAN"========== Finalizando con las pruebas del Lector ==========" RESET << endl;
}

void PodioTest::test01CuandoLePedisAlPodioQueTeDeElPodioParcialElPrimeroEsElDeMayorPuntaje(Assert *testSuite) {
    Podio* podio = new Podio();
    Mario* unMario = new Mario(0);
    Mario* otroMario = new Mario(1);
    unMario->agregar((Observador*)podio);
    otroMario->agregar((Observador*)podio);
    map<int,Mario*> jugadores;
    jugadores[0] = unMario;
    jugadores[1] = otroMario;
    podio->recibirJugadores(jugadores);
    otroMario->agregarPuntos(50);
    otroMario->agregarPuntos(50);
    unMario->agregarPuntos(50);
    vector<pair<Mario*, int>> resultados = podio->getPodioNivel();
    int puntosEsperados = resultados.begin()->second;
    testSuite->assert(puntosEsperados,100,"El jugador que tiene mas puntos tiene 100");
}

void PodioTest::test02CuandoLePedisAlPodioQueTeDeElPodioParcialElPrimeroEsElDeMayorPuntaje(Assert *testSuite) {
    Podio* podio = new Podio();
    Mario* unMario = new Mario(0);
    Mario* otroMario = new Mario(1);
    Mario* algunMario = new Mario(2);
    unMario->agregar((Observador*)podio);
    otroMario->agregar((Observador*)podio);
    algunMario->agregar((Observador*)podio);
    map<int,Mario*> jugadores;
    jugadores[0] = unMario;
    jugadores[1] = otroMario;
    jugadores[2] = algunMario;
    podio->recibirJugadores(jugadores);
    otroMario->agregarPuntos(50);
    otroMario->agregarPuntos(50);
    unMario->agregarPuntos(50);
    algunMario->agregarPuntos(500);
    vector<pair<Mario*, int>> resultados = podio->getPodioNivel();
    int puntosEsperados = resultados.at(0).second;
    vector<pair<Mario*, int>> resultadosTotales = podio->getPodioTotal();
    int puntosTotales = resultadosTotales.at(0).second;
    testSuite->assert(puntosEsperados,500,"El jugador que tiene mas puntos tiene 500");
    puntosEsperados = resultados.at(2).second;
    testSuite->assert(puntosEsperados,50,"El jugador que tiene menos puntos tiene 50");
    testSuite->assert(puntosTotales,500,"El  jugador que tiene mas puntos totales tiene 500");
}
