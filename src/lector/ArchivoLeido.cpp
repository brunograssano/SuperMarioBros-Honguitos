#include "ArchivoLeido.hpp"

void ArchivoLeido::verificarLectura(){

	if(this->niveles.empty()){
		this->mensajeError.push_back("No se envio informacion de los niveles, se cargara la configuracion default");
		this->leidoCorrectamente = false;
	}

}

ArchivoLeido::~ArchivoLeido(){
	this->mensajeError.clear();
}
