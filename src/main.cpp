#include <cstring>
using namespace std;
#include <csignal>
#include <src/Utils/Validaciones.hpp>

#include "Server/mainServer.hpp"
#include "Client/mainClient.hpp"
#include "Utils/test/mainTest.hpp"

bool revisarParametro(int cantidadArgumentos, char *argumentos[], const char parametroEntero[10]) {
	bool esParametro = false;
	char comandoLargo[12]="--";
    char comandoCorto[5]="-";
	strcat(comandoLargo,parametroEntero);
    comandoCorto[1] = parametroEntero[0];
	int i=0;
	while(i<cantidadArgumentos && !esParametro){
		if(strcmp(argumentos[i],comandoCorto)==0 ||  strcmp(argumentos[i],comandoLargo)==0){
            esParametro = true;
		}
		i++;
	}
	return esParametro;
}

void mostrarMensajeInicial(){
    cout<<"Super Mario Bros by Honguitos"<<endl;
    cout<<"Integrantes"<<endl;
    cout<<"* Adrian Romero"<<endl;
    cout<<"* Bruno Grassano"<<endl;
    cout<<"* Joaquin Gomez"<<endl;
    cout<<"* Lukas De Angelis Riva"<<endl;
    cout<<"Puede ver informacion sobre los comandos disponibles con -h o --help"<<endl;
    cout<<"Si quiere detalles sobre el comportamiento de la aplicacion puede ver los logs generados por la misma"<<endl;
    cout<<"El proyecto esta bajo licencia MIT"<<endl;
}

int main( int cantidadArgumentos, char* argumentos[]){

	signal(SIGPIPE, SIG_IGN);
    srand(time(nullptr));
	mostrarMensajeInicial();

	if(revisarParametro(cantidadArgumentos, argumentos, "server")){
		mainServer(cantidadArgumentos, argumentos);
	}
	else if(revisarParametro(cantidadArgumentos, argumentos, "test")){
	    mainTest();
	}
    else if(revisarParametro(cantidadArgumentos, argumentos, "help")){
        mostrarAyuda();
    }
	else{
		mainClient(cantidadArgumentos, argumentos);
	}
	return 0;
}
