using namespace std;
#include "LectorTest.h"
#include "../lector/Lector.hpp"
#include <iostream>

void LectorTest::ejecutar(Assert* testSuite){

	cout << "========== Comenzando con las pruebas del Lector ==========" << endl;
	test01CuandoLePedisAlLectorQueLeaTraeElAncho(testSuite);
	test02CuandoLePedisAlLectorQueLeaTraeElAlto(testSuite);
	test03CuandoLePedisAlLectorElArchivoSeLeeCorrectamente(testSuite);
	test04CuandoLePedisAlLectorElArchivoSeLeeCorrectamenteNoTraeMensajesDeError(testSuite);
	test05CuandoLeEnviasUnArchivoQueNoExisteSeLanzaUnError(testSuite);
	test06CuandoLeEnviasUnArchivoMalFormateadoSeLanzaUnError(testSuite);
	cout << "========== Finalizando con las pruebas del Lector ==========" << endl;

}

void LectorTest::test01CuandoLePedisAlLectorQueLeaTraeElAncho(Assert* testSuite){

	Lector* lector = new Lector();

	string archivoALeer = "resources/modeloXML.xml";

	ArchivoLeido* archivoLeido = lector->leerArchivo(archivoALeer);

	int anchoEsperado = archivoLeido->anchoVentana;

	testSuite->assert(anchoEsperado,800,"El ancho es de 800 px");

	delete lector;
	delete archivoLeido;
}

void LectorTest::test02CuandoLePedisAlLectorQueLeaTraeElAlto(Assert* testSuite){

	Lector* lector = new Lector();

	string archivoALeer = "resources/modeloXML.xml";

	ArchivoLeido* archivoLeido = lector->leerArchivo(archivoALeer);

	int anchoEsperado = archivoLeido->altoVentana;

	testSuite->assert(anchoEsperado,600,"El alto es de 600 px");

	delete lector;
	delete archivoLeido;
}
void LectorTest::test03CuandoLePedisAlLectorElArchivoSeLeeCorrectamente(Assert* testSuite){

	Lector* lector = new Lector();

	string archivoALeer = "resources/modeloXML.xml";

	ArchivoLeido* archivoLeido = lector->leerArchivo(archivoALeer);

	bool leidoCorrectamente = archivoLeido->leidoCorrectamente;

	testSuite->assert(leidoCorrectamente,"El archivo se lee correctamente");

	delete lector;
	delete archivoLeido;
}
void LectorTest::test04CuandoLePedisAlLectorElArchivoSeLeeCorrectamenteNoTraeMensajesDeError(Assert* testSuite){

	Lector* lector = new Lector();

	string archivoALeer = "resources/modeloXML.xml";

	ArchivoLeido* archivoLeido = lector->leerArchivo(archivoALeer);

	bool noHayMensajesDeError = archivoLeido->mensajeError.empty();

	testSuite->assert(noHayMensajesDeError,"No hay mensajes de error");

	delete lector;
	delete archivoLeido;
}

void LectorTest::test05CuandoLeEnviasUnArchivoQueNoExisteSeLanzaUnError(Assert* testSuite){

	Lector* lector = new Lector();

	string archivoALeer = "NoExisto.xml";

	ArchivoLeido* archivoLeido = lector->leerArchivo(archivoALeer);

	bool leidoCorrectamente = archivoLeido->leidoCorrectamente;

	string mensajeError;

	for(string error: archivoLeido->mensajeError){
		mensajeError = error;
	}

	testSuite->assert(!leidoCorrectamente,"El archivo no se lee correctamente");
	testSuite->assert(mensajeError,"El archivo pedido no existe","El mensaje de error es el correcto");

	delete lector;
	delete archivoLeido;
}

void LectorTest::test06CuandoLeEnviasUnArchivoMalFormateadoSeLanzaUnError(Assert* testSuite){

	Lector* lector = new Lector();

	string archivoALeer = "resources/archivoMalFormato.xml";

	ArchivoLeido* archivoLeido = lector->leerArchivo(archivoALeer);

	bool leidoCorrectamente = archivoLeido->leidoCorrectamente;

	string mensajeError;

	for(string error: archivoLeido->mensajeError){
		mensajeError = error;
	}


	testSuite->assert(!leidoCorrectamente,"El archivo no se lee correctamente");
	testSuite->assert(mensajeError,"Hay un error en la linea 56","El mensaje de error es el correcto");

	delete lector;
	delete archivoLeido;
}



