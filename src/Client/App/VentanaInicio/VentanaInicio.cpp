#include "VentanaInicio.hpp"

#include <string>
#include <iostream>

#include "../ManejadorSDL.hpp"
#include "src/Utils/log/Log.hpp"
#include "ManejadorEntrada.hpp"
#include "EstadoConectado.hpp"
#include "EstadoEspera.hpp"
#include "EstadoDesconectado.hpp"

#define ANCHO_PANTALLA 650
#define ALTO_PANTALLA 450

const SDL_Color COLOR_BLANCO = {255, 255, 255, 0xFF };
const SDL_Color COLOR_NEGRO = { 0, 0, 0, 0xFF };
const SDL_Color COLOR_ROJO = { 214, 40, 57, 0xFF };


VentanaInicio::VentanaInicio(unsigned short jugadoresConectados, unsigned short jugadoresTotales){
	this->ingresoIncorrectoCredenciales = false;
    this->murioElServer = false;
	this->jugadoresTotales = jugadoresTotales;
	this->jugadoresConectados = jugadoresConectados;

	this->ventana = crearVentana( "Inicio Mario Bros", ALTO_PANTALLA,ANCHO_PANTALLA);
	this->renderer = crearRenderer(ventana);
	this->fuente = cargarFuente( "resources/Fuentes/fuenteSuperMarioBros.ttf", 12 );
	cargarIcono(ventana);
    std::string direccionFondo = "resources/Imagenes/Niveles/fondoPantallaInicio.png";
    this->fondoPantalla = cargarTexturaImagen( direccionFondo,this->renderer );

    this->botonEnviar = new BotonConTexto(460, 190, 80 , 40 , "Enviar",this->renderer,this->fuente);
    this->cajaTextoUsuario = new BotonConTexto(400,60,200,20,"...",this->renderer,this->fuente);
    this->cajaTextoContrasenia = new BotonConTexto(400,140,200,20,"...",this->renderer,this->fuente);
    cajaTextoContrasenia->ocultaTexto();

	texturasMarios = intentarCarga("Textura de colores mario", "resources/Imagenes/Personajes/ColoresMarios.png", renderer);
    estadoVentana = new EstadoConectado (renderer,fondoPantalla,fuente,botonEnviar,cajaTextoUsuario,cajaTextoContrasenia);
}

void VentanaInicio::actualizarJugadores(actualizacion_cantidad_jugadores_t actualizacion){
	jugadoresConectados = actualizacion.cantidadJugadoresActivos;
	informacionJugadoresConectados = actualizacion;
}

void VentanaInicio::seMurioElServer(){
	murioElServer = true;
}

void VentanaInicio::imprimirErrorIngreso() {
    SDL_Rect rectangulo = {370, 265, 260, 30};
    SDL_SetRenderDrawColor(this->renderer, 162, 177, 205, 0xFF);
    SDL_RenderFillRect(this->renderer, &rectangulo);
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 0xFF);
    SDL_RenderDrawRect(this->renderer, &rectangulo);
    SDL_Texture *texturaMensaje = cargarTexturaTexto(this->errorDeIngreso, COLOR_ROJO, this->renderer,
                                                     this->fuente);
    if (texturaMensaje == nullptr) {
        Log::getInstance()->huboUnError("No se pudo crear la textura para el mensaje: '" + errorDeIngreso + "'");

    }
    renderizar(375, 270, 18, 250, texturaMensaje, this->renderer);
    destructorDeTexturas(texturaMensaje);
}

void VentanaInicio::obtenerEntrada(){

    bool terminar = false;
	SDL_Event evento;
	SDL_StartTextInput();
    std::string textoIngresadoUsuario;
    std::string textoIngresadoContrasenia;
    std::string* entradaUsuario = &textoIngresadoUsuario;
	bool terminoEntrada = false;

	while( !terminar && !terminoEntrada){
		terminoEntrada = ManejadorEntrada::manejarEntrada(evento, &terminar, &textoIngresadoUsuario, &textoIngresadoContrasenia,
                                                  &entradaUsuario, cajaTextoUsuario, cajaTextoContrasenia, botonEnviar);

		cajaTextoUsuario->cambiarTexto(textoIngresadoUsuario);
		cajaTextoContrasenia->cambiarTexto(textoIngresadoContrasenia);

		estadoVentana->mostrarse(jugadoresConectados, jugadoresTotales);

		this->ponerLosMarios();

		if(ingresoIncorrectoCredenciales || murioElServer){
			if(murioElServer){
                estadoVentana = new EstadoDesconectado(renderer,fuente);
                estadoVentana->mostrarse(jugadoresConectados, jugadoresTotales);
			}else{
                imprimirErrorIngreso();
			}
		}

		SDL_RenderPresent( this->renderer );
	}
	SDL_StopTextInput();
	const char* punteroTextoIngresadoUsuario = textoIngresadoUsuario.c_str();
	const char* punteroTextoIngresadoContrasenia = textoIngresadoContrasenia.c_str();

	strcpy(credenciales.nombre,punteroTextoIngresadoUsuario);
	strcpy(credenciales.contrasenia,punteroTextoIngresadoContrasenia);
}


bool VentanaInicio::estaConectado(const std::string& nombre){
	for(int i = 0; i < informacionJugadoresConectados.tope; i++){
		if(nombre == informacionJugadoresConectados.pares_id_nombre[i].nombre &&
				informacionJugadoresConectados.pares_id_nombre[i].conectado){
			return true;
		}
	}
	return false;
}

void VentanaInicio::imprimirMensajeError(){
	ingresoIncorrectoCredenciales = true;
	if (informacionJugadoresConectados.tope >= jugadoresTotales){
		errorDeIngreso = std::string("La sala esta llena, no puede ingresar");
	}else if(estaConectado(credenciales.nombre)){
		errorDeIngreso = std::string("Este jugador ya ingreso a la sala.");
	}else{
		errorDeIngreso = std::string("Las credenciales ingresadas son erroneas");
	}
}

void VentanaInicio::imprimirMensajeEspera(){
    delete(this->estadoVentana);
    estadoVentana = new EstadoEspera(renderer,fondoPantalla,fuente);

	SDL_Event evento;
	while( SDL_PollEvent( &evento ) != 0 ){
		if( evento.type == SDL_QUIT ){
			throw std::runtime_error("Cerro Ventana De Inicio");
		}
	}

	estadoVentana->mostrarse(jugadoresConectados, jugadoresTotales);

	ponerLosMarios();

	SDL_RenderPresent( this->renderer );
}

credencial_t VentanaInicio::obtenerCredenciales(){
	return credenciales;
}

void VentanaInicio::ponerLosMarios(){
	for(int i = 0; i < informacionJugadoresConectados.tope; i++){

		int x = 60+70*i;
		int y = ALTO_PANTALLA -102;
		int w = 32;
		int h = 64;

		SDL_Rect rectanguloMario = {x, y, w, h};
		SDL_Rect recorte = {0, 0, 0, 0};
		if(informacionJugadoresConectados.pares_id_nombre[i].conectado)
			recorte = {i*16, 0, 16, 32};
		else
			recorte = {64, 0, 16, 32};

        std::string strNombre = informacionJugadoresConectados.pares_id_nombre[i].nombre;
		SDL_Texture* texturaNombre = cargarTexturaTexto(strNombre, COLOR_BLANCO, this->renderer, this->fuente);
		SDL_Rect rectanguloNombre = {x-5, y-15, 40, 10};
		SDL_SetRenderDrawColor(renderer, 75, 89, 129, 0x0F );
		SDL_RenderFillRect(renderer, &rectanguloNombre);
		SDL_RenderDrawRect(renderer, &rectanguloNombre);

		if( texturaNombre != nullptr ){
			renderizar(rectanguloNombre.x,rectanguloNombre.y,rectanguloNombre.h,rectanguloNombre.w,texturaNombre,renderer);
		}
		destructorDeTexturas(texturaNombre);

		SDL_RenderCopy(renderer, texturasMarios, &recorte, &rectanguloMario);
	}
}

VentanaInicio::~VentanaInicio(){
	destructorDeTexturas(fondoPantalla);
	destructorDeTexturas(texturasMarios);
	delete(this->botonEnviar);
	delete(this->cajaTextoUsuario);
	delete(this->cajaTextoContrasenia);
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( ventana );
}