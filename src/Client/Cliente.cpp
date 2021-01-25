#include "Cliente.hpp"
#include <thread>
#include "src/Client/ReproductorDeMusica/ReproductorMusica.hpp"
#include "App/ManejadorSDL.hpp"
#include "App/AplicacionCliente.hpp"
#include "UtilidadesCliente.hpp"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

Cliente::Cliente(char ip[LARGO_IP], int puerto){
	socketCliente = conectarAlServidor(ip, puerto);

	terminoJuego = false;
	empiezaElJuego = false;
	pasoVerificacion = false;
	seRecibioVerificacion = false;
	seRecibioInformacionInicio = false;
	cargoLaAplicacion = false;
	terminoEnviar = false;
	terminoEscuchar = false;
	cerroVentana = false;

    ReproductorMusica::getInstance();
	escuchador = new EscuchadorCliente(socketCliente,this,&terminoJuego,&terminoEscuchar);
    enviador = new EnviadorCliente(socketCliente,this,&terminoJuego,&terminoEnviar);
	ventanaInicio = nullptr;
	gameLoop = new GameLoop();
}

void Cliente::terminarProcesosDelCliente() {
	pthread_mutex_lock(&mutex);
	terminoJuego = true;
	//cerroVentana = true;
	gameLoop->seMurioElServer();
	if(ventanaInicio!=nullptr){
		ventanaInicio->seMurioElServer();
	}
	pthread_mutex_unlock(&mutex);
}

void Cliente::empezarJuego(info_partida_t info_partida){
	empiezaElJuego = true;
	infoPartida = info_partida;
}

void Cliente::recibirVerificacionCredenciales(verificacion_t verificacion){
	this->pasoVerificacion = verificacion;
	this->seRecibioVerificacion = true;
}

void Cliente::recibirInformacionActualizacion(actualizacion_cantidad_jugadores_t actualizacion){
	if(!seRecibioInformacionInicio){
		iniciarSDL();
		ventanaInicio = new VentanaInicio(actualizacion.cantidadJugadoresActivos, actualizacion.cantidadMaximaDeJugadores);
		pthread_mutex_lock(&mutex);
        ventanaInicio->actualizarJugadores(actualizacion);
		this->seRecibioInformacionInicio = true;
		pthread_mutex_unlock(&mutex);
	}else if(!empiezaElJuego){
        ventanaInicio->actualizarJugadores(actualizacion);
	}
}
void Cliente::recibirInformacionRonda(info_ronda_t info_ronda) const{
	if(!cargoLaAplicacion){
		return;
	}
	App* aplicacion = App::getInstance();
	if(aplicacion!= nullptr)
	    aplicacion->agregarRonda(info_ronda);
}

void Cliente::esperar(const bool* condicionAEsperar){
    while(!(*condicionAEsperar)){
    }
}

void Cliente::esperarAQueEmpieceElJuego() {
	while (!cerroVentana && !empiezaElJuego) {
		try {
			ventanaInicio->imprimirMensajeEspera();
		} catch (const std::exception &e) {
			cerroVentana = true;
		}
	}
}

void Cliente::intentarEntrarAlJuego() {
	while (!pasoVerificacion && !cerroVentana) {
		try {
			ventanaInicio->obtenerEntrada();
			credencial_t credenciales = ventanaInicio->obtenerCredenciales();
            agregarMensajeAEnviar(CREDENCIAL,&credenciales);
			esperar(&seRecibioVerificacion);
			if (!pasoVerificacion) {
				ventanaInicio->imprimirMensajeError();
				seRecibioVerificacion = false;
			}
		} catch (const std::exception &e) {
			cerroVentana = true;
		}
	}
}

void Cliente::ejecutar(){
    try{
        enviador->empezarHilo("Enviador");
        escuchador->empezarHilo("Escuchador");
    }catch(const std::exception& e){
        terminoJuego = true;
        return;
    }

	esperar(&seRecibioInformacionInicio);
	intentarEntrarAlJuego();
	if(cerroVentana){
		delete ventanaInicio;
		cerradoVentanaInicio();
		return;
	}

	esperarAQueEmpieceElJuego();
	delete ventanaInicio;
	ventanaInicio = nullptr;
	if(cerroVentana){
		cerradoVentanaInicio();
		return;
	}

	cargoLaAplicacion = gameLoop->inicializarAplicacion(infoPartida, this);
	if(!cargoLaAplicacion){
		Log::getInstance()->huboUnError("No se inicializo la aplicacion");
		cerrarSocketCliente(socketCliente);
		while(!terminoEnviar || !terminoEscuchar){}
		delete Log::getInstance();
		exit(-1);
	}

	gameLoop->gameLoop();

	terminoJuego = true;
}


void Cliente::agregarMensajeAEnviar(char tipoMensaje,void* mensaje){
    enviador->agregarMensajeAEnviar(tipoMensaje,mensaje);
}

void Cliente::cerradoVentanaInicio() const {
	Log::getInstance()->mostrarMensajeDeInfo("Se cerro la ventana de inicio");
	cerrarSocketCliente(socketCliente);
    while(!terminoEnviar || !terminoEscuchar){}
    delete Log::getInstance();
    exit(0);
}

Cliente::~Cliente(){
	cerrarSocketCliente(socketCliente);
	while(!terminoEnviar || !terminoEscuchar){}
    delete ReproductorMusica::getInstance();
    delete escuchador;
	delete enviador;
	delete gameLoop;
    terminarSDL();
    delete Log::getInstance();
}

void Cliente::recibirInformacionNivel(nivel_t nivel) {
    esperar(&cargoLaAplicacion);
    App* aplicacion = App::getInstance();
    aplicacion->agregarNivel(nivel);
}
