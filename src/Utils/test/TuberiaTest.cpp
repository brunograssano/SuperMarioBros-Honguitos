#include "TuberiaTest.hpp"
#include "src/Server/Modelo/Juego/Nivel/Bloques/Tuberia.hpp"
using namespace std;
#define CYAN "\u001b[36m"
#define AZUL_CLARO "\e[1;34m"
#define RESET "\x1b[0m"


void TuberiaTest::ejecutar(Assert *testSuite) {
    cout << CYAN"========== Comenzando con las pruebas de tuberia ==========" RESET << endl;
    cout << AZUL_CLARO"----------TEST 01----------" RESET << endl;
    test01UnaTuberiaRespondeCorrectamenteSiColisionaContraOtra(testSuite);
}

void TuberiaTest::test01UnaTuberiaRespondeCorrectamenteSiColisionaContraOtra(Assert *testSuite) {
    Tuberia tuberiaChica(100, 0, 0);
    Tuberia tuberiaGrande(100, 0, 0);
    Tuberia tuberiaChicaColisiona(110, 0, 0);
    Tuberia tuberiaGrandeColisiona(110, 1, 0);
    Tuberia tuberiaChicaNoColisiona(1000, 0, 0);
    Tuberia tuberiaGrandeNoColisiona(1000,1, 0);

    testSuite->assert(tuberiaChica.colisionaCon(&tuberiaChicaColisiona) && tuberiaChica.colisionaCon(&tuberiaGrandeColisiona), "La tuberia chica informa correctamente colision.");
    testSuite->assert(tuberiaGrande.colisionaCon(&tuberiaChicaColisiona) && tuberiaGrande.colisionaCon(&tuberiaGrandeColisiona), "La tuberia grande informa correctamente colision.");
    testSuite->assert(!tuberiaChica.colisionaCon(&tuberiaChicaNoColisiona) && !tuberiaChica.colisionaCon(&tuberiaGrandeNoColisiona), "La tuberia chica informa correctamente la no colision");
    testSuite->assert(!tuberiaGrande.colisionaCon(&tuberiaChicaNoColisiona) && !tuberiaGrande.colisionaCon(&tuberiaGrandeNoColisiona), "La tuberia grande informa correctamente la no colision");
}
