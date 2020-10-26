#include "ArchivoLeido.hpp"

void ArchivoLeido::verificarLectura(){
	if(this->altoVentana == 0){
		this->mensajeError.push_back("No se envio el parametro alto de la ventana");
		this->leidoCorrectamente = false;
	}
	if(this->anchoVentana == 0){
		this->mensajeError.push_back("No se envio el parametro ancho de la ventana");
		this->leidoCorrectamente = false;
	}
	if(this->tipoLog == NULL){
		this->mensajeError.push_back("No se envio el parametro tipo de log");
		this->leidoCorrectamente = false;
	}
	if(this->niveles.empty()){
		this->mensajeError.push_back("No se envio informacion de los niveles");
		this->leidoCorrectamente = false;
	}
	for(auto const& unNivel: niveles){
		if(unNivel == NULL){
			this->mensajeError.push_back("Hubo un error al crear un nivel");
			this->leidoCorrectamente = false;
		}else{
			if(unNivel->obtenerEnemigos().empty()){
				this->mensajeError.push_back("Hubo un error al crear enemigos");
				this->leidoCorrectamente = false;
			}
			if(unNivel->obtenerPlataformas().empty()){
				this->mensajeError.push_back("Hubo un error al crear plataformas");
				this->leidoCorrectamente = false;
			}

		}
	}

}

ArchivoLeido::~ArchivoLeido(){
	this->mensajeError.clear();
}
