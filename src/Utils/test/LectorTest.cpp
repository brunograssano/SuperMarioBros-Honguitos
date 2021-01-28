#include "LectorTest.hpp"
#include <iostream>
using namespace std;
#define CYAN "\u001b[36m"
#define AZUL_CLARO "\e[1;34m"
#define RESET "\x1b[0m"

void LectorTest::ejecutar(Assert* testSuite){

	cout << CYAN"========== Comenzando con las pruebas del Lector ==========" RESET << endl;
    cout << AZUL_CLARO"----------TEST 01----------" RESET << endl;
	test01CuandoLePedisAlLectorQueLeaTraeElAncho(testSuite);
    cout << AZUL_CLARO"----------TEST 02----------" RESET << endl;
	test02CuandoLePedisAlLectorQueLeaTraeElAlto(testSuite);
    cout << AZUL_CLARO"----------TEST 03----------" RESET << endl;
	test03CuandoLePedisAlLectorElArchivoSeLeeCorrectamente(testSuite);
    cout << AZUL_CLARO"----------TEST 04----------" RESET << endl;
	test04CuandoLePedisAlLectorElArchivoSeLeeCorrectamenteNoTraeMensajesDeError(testSuite);
    cout << AZUL_CLARO"----------TEST 05----------" RESET << endl;
	test05CuandoLeEnviasUnArchivoQueNoExisteSeLanzaUnError(testSuite);
    cout << AZUL_CLARO"----------TEST 06----------" RESET << endl;
	test06CuandoLeEnviasUnArchivoMalFormateadoSeLanzaUnError(testSuite);
    cout << AZUL_CLARO"----------TEST 07----------" RESET << endl;
	test07CuandoLeEnviasUnArchivoMalElAnchoSeCargaElDefaultYSeLanzaUnError(testSuite);
    cout << AZUL_CLARO"----------TEST 08----------" RESET << endl;
	test08CuandoLeEnviasUnArchivoMalElAltooSeCargaElDefaultYSeLanzaUnError(testSuite);
	cout << CYAN"========== Finalizando con las pruebas del Lector ==========" RESET << endl;

}

void LectorTest::test01CuandoLePedisAlLectorQueLeaTraeElAncho(Assert* testSuite){
    auto lector = Lector();

	string archivoALeer = "resources/ArchivosXML/configuracionDefault.xml";

	ArchivoLeido archivoLeido = lector.leerArchivo(archivoALeer);

	int anchoEsperado = archivoLeido.anchoVentana;

	testSuite->assert(anchoEsperado,800,"El ancho es de 800 px en conf default");
}

void LectorTest::test02CuandoLePedisAlLectorQueLeaTraeElAlto(Assert* testSuite){
    auto lector = Lector();

	string archivoALeer = "resources/ArchivosXML/configuracionDefault.xml";

	ArchivoLeido archivoLeido = lector.leerArchivo(archivoALeer);

	int anchoEsperado = archivoLeido.altoVentana;

	testSuite->assert(anchoEsperado,600,"El alto es de 600 px en config default");
}
void LectorTest::test03CuandoLePedisAlLectorElArchivoSeLeeCorrectamente(Assert* testSuite){
    auto lector = Lector();

	string archivoALeer = "resources/ArchivosXML/configuracionDefault.xml";

	ArchivoLeido archivoLeido = lector.leerArchivo(archivoALeer);

	bool leidoCorrectamente = archivoLeido.leidoCorrectamente;

	testSuite->assert(leidoCorrectamente,"El archivo de configuracion default se lee correctamente");
}
void LectorTest::test04CuandoLePedisAlLectorElArchivoSeLeeCorrectamenteNoTraeMensajesDeError(Assert* testSuite){
    auto lector = Lector();

	string archivoALeer = "resources/ArchivosXML/configuracionDefault.xml";

	ArchivoLeido archivoLeido = lector.leerArchivo(archivoALeer);

	bool noHayMensajesDeError = archivoLeido.mensajeError.empty();

	testSuite->assert(noHayMensajesDeError,"No hay mensajes de error en la config default");
}

void LectorTest::test05CuandoLeEnviasUnArchivoQueNoExisteSeLanzaUnError(Assert* testSuite){
    auto lector = Lector();

	string archivoALeer = "NoExisto.xml";

	ArchivoLeido archivoLeido = lector.leerArchivo(archivoALeer);

	bool leidoCorrectamente = archivoLeido.leidoCorrectamente;

	string mensajeError;

	for(const string& error: archivoLeido.mensajeError){
		mensajeError = error;
	}

	testSuite->assert(!leidoCorrectamente,"El archivo no se lee correctamente");
	testSuite->assert(mensajeError,"El archivo pedido en la direccion: NoExisto.xml no existe,se carga el archivo por defecto","El mensaje de error es el correcto");
}

void LectorTest::test06CuandoLeEnviasUnArchivoMalFormateadoSeLanzaUnError(Assert* testSuite){
	auto lector = Lector();

	string archivoALeer = "resources/ArchivosXML/archivoMalFormato.xml";

	ArchivoLeido archivoLeido = lector.leerArchivo(archivoALeer);

	bool leidoCorrectamente = archivoLeido.leidoCorrectamente;

	string mensajeError;

	for(const string& error: archivoLeido.mensajeError){
		mensajeError = error;
	}


	testSuite->assert(!leidoCorrectamente,"El archivo no se lee correctamente");
	testSuite->assert(mensajeError,"Hay un error en la linea 57 del archivo resources/ArchivosXML/archivoMalFormato.xml,se carga el archivo por defecto","El mensaje de error es el correcto");
}
void LectorTest::test07CuandoLeEnviasUnArchivoMalElAnchoSeCargaElDefaultYSeLanzaUnError(Assert* testSuite){
	auto lector = Lector();

	string archivoALeer = "resources/ArchivosXML/archivoAnchoMalEnviado.xml";

	ArchivoLeido archivoLeido = lector.leerArchivo(archivoALeer);

	int anchoEsperado = archivoLeido.anchoVentana;

	bool leidoCorrectamente = archivoLeido.leidoCorrectamente;

	string mensajeError;

	for(const string& error: archivoLeido.mensajeError){
		mensajeError = error;
	}

	testSuite->assert(anchoEsperado,800,"El ancho es de 800 px");
	testSuite->assert(!leidoCorrectamente,"El archivo no se lee correctamente");
}
void LectorTest::test08CuandoLeEnviasUnArchivoMalElAltooSeCargaElDefaultYSeLanzaUnError(Assert* testSuite){
	auto lector = Lector();

	string archivoALeer = "resources/ArchivosXML/archivoAltoMalEnviado.xml";

	ArchivoLeido archivoLeido = lector.leerArchivo(archivoALeer);

	int altoEsperado = archivoLeido.altoVentana;

	bool leidoCorrectamente = archivoLeido.leidoCorrectamente;

	string mensajeError;

	for(const string& error: archivoLeido.mensajeError){
		mensajeError = error;
	}

	testSuite->assert(altoEsperado,600,"El alto es de 600 px");
	testSuite->assert(!leidoCorrectamente,"El archivo no se lee correctamente");
}


