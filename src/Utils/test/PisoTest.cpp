#include "src/Server/modelo/Piso.hpp"
#include "PisoTest.hpp"

#define CYAN "\u001b[36m"
#define AZUL_CLARO "\e[1;34m"
#define RESET "\x1b[0m"

void PisoTest::ejecutar(Assert *testSuite) {
    cout << CYAN"========== Comenzando con las pruebas del piso ==========" RESET << endl;
    cout << AZUL_CLARO"----------TEST 01----------" RESET << endl;
    test01CuandoSeLePideAlPisoLaPosicionDeRespawnYNoHayPozosEsteDevuelveLaMinima(testSuite);
    cout << AZUL_CLARO"----------TEST 02----------" RESET << endl;
    test02CuandoSeLePideAlPisoLaPosicionDeRespawnYAlPrincipioHayUnPozoEsteDevuelveElFinalDelPozo(testSuite);
    cout << AZUL_CLARO"----------TEST 03----------" RESET << endl;
    test03CuandoNoHayUnPozoAlComienzoLaPosicionDeRespawnCoincideConLaDeLaCamara(testSuite);
    cout << AZUL_CLARO"----------TEST 04----------" RESET << endl;
    test04AlInicializarElPisoSeObtienenLasCantidadesCorrectas(testSuite);
    cout << CYAN"========== Finalizando con las pruebas del piso ==========" RESET << endl;

}

void PisoTest::test01CuandoSeLePideAlPisoLaPosicionDeRespawnYNoHayPozosEsteDevuelveLaMinima(Assert* testSuite) {
    int alto = 400;
    int xEsperado = 100;
    Piso piso(alto);
    piso.inicializar();
    rectangulo_t rectanguloCamara = {xEsperado, 1000, 0, 800, 800, 1000 - xEsperado};
    PosicionFija respawn(0,0);
    bool hayPiso = piso.obtenerRespawn(rectanguloCamara, &respawn);
    testSuite->assert(hayPiso, "Se encontró una posición para reaparecer.");
    testSuite->assert(respawn.obtenerPosX(),xEsperado, "El piso devuelve correctamente la posición de resaparición si no hay pozos.");
}

void PisoTest::test02CuandoSeLePideAlPisoLaPosicionDeRespawnYAlPrincipioHayUnPozoEsteDevuelveElFinalDelPozo(
        Assert *testSuite) {
    int alto = 400;
    int xPozo = 1300;
    int xCamara = 1400;
    int xEsperado = 1500;
    int anchoCamara = 1000;

    Piso piso(alto);
    piso.agregarPozo(xPozo, 0, 0);
    piso.inicializar();
    rectangulo_t rectanguloCamara = {xCamara, xCamara+anchoCamara, 0, 800, 800, anchoCamara};
    PosicionFija respawn(0,0);
    bool hayPiso = piso.obtenerRespawn(rectanguloCamara, &respawn);
    testSuite->assert(hayPiso, "Se encontró una posición para reaparecer.");
    testSuite->assert(respawn.obtenerPosX(), xEsperado, "El piso devuelve correctamente la posición de resaparición con un pozo al comienzo.");
}

void PisoTest::test03CuandoNoHayUnPozoAlComienzoLaPosicionDeRespawnCoincideConLaDeLaCamara(Assert* testSuite){
    int alto = 400;
    int xPozo = 1600;
    int xCamara = 1400;
    int xEsperado = xCamara;
    int anchoCamara = 1000;

    Piso piso(alto);
    piso.agregarPozo(xPozo, 0, 0);
    piso.inicializar();
    rectangulo_t rectanguloCamara = {xCamara, xCamara+anchoCamara, 0, 800, 800, anchoCamara};
    PosicionFija respawn(0,0);
    bool hayPiso = piso.obtenerRespawn(rectanguloCamara, &respawn);
    testSuite->assert(hayPiso, "Se encontró una posición para reaparecer.");
    testSuite->assert(respawn.obtenerPosX(), xEsperado, "El piso devuelve correctamente la posición de resaparición con un pozo al comienzo.");
}
void PisoTest::test04AlInicializarElPisoSeObtienenLasCantidadesCorrectas(Assert* testSuite) {
    int alto = 400;

    Piso piso(alto);
    piso.inicializar();
    testSuite->assert(piso.obtenerPiso().size(), 1, "Si no se tienen pozos, se obtiene un solo piso");

    piso = Piso(alto);
    piso.agregarPozo(10, 0, 0);
    piso.inicializar();
    testSuite->assert(piso.obtenerPiso().size(), 2, "Con un solo pozo se obtienen 2 pisos");

    piso = Piso(alto);
    piso.agregarPozo(10, 0, 0);
    piso.agregarPozo(20, 0, 0);
    piso.agregarPozo(30, 0, 0);
    piso.inicializar();
    testSuite->assert(piso.obtenerPiso().size(), 2, "No se pueden superponer pozos");

    piso = Piso(alto);
    piso.agregarPozo(100, 0, 0);
    piso.agregarPozo(400, 0, 0);
    piso.agregarPozo(700, 0, 0);
    piso.inicializar();
    testSuite->assert(piso.obtenerPiso().size(), 4, "Con 3 pozos se tienen 4 pisos");

    piso = Piso(alto);
    piso.agregarPozo(-1, 0, 0);
    piso.inicializar();
    testSuite->assert(piso.obtenerPiso().size(), 1, "No se puede poner un pozo antes del comienzo del piso");
}