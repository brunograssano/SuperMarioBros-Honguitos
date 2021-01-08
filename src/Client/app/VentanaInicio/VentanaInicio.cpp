#include "VentanaInicio.hpp"

#include <stdio.h>
using namespace std;
#include<string>
#include<iostream>
#include "../ManejadorSDL.hpp"
#include "../../../Utils/log/Log.hpp"
#define ANCHO_PANTALLA 650
#define ALTO_PANTALLA 450

VentanaInicio::VentanaInicio(unsigned short jugadoresConectados, unsigned short jugadoresTotales){
	this->ingresoIncorrectoCredenciales = false;
	this->salaLlena = false;
	this->murioElServer = false;
	this->jugadoresTotales = jugadoresTotales;
	this->jugadoresConectados = jugadoresConectados;
	Log* log = Log::getInstance();

	this->ventana = SDL_CreateWindow( "Inicio Mario Bros", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_PANTALLA, ALTO_PANTALLA, SDL_WINDOW_SHOWN );
	if( ventana == NULL ){
		log->huboUnErrorSDL("No se pudo crear una ventana de inicio por error de SDL", SDL_GetError());
	}
	this->renderer = crearRenderer(ventana);
	this->fuente = TTF_OpenFont( "resources/Fuentes/fuenteSuperMarioBros.ttf", 12 );
	if( this->fuente == NULL ){
		log->huboUnErrorSDL("No se pudo cargar la fuente", SDL_GetError());
	}else{
		cargarIcono(ventana);
		string direccionFondo = "resources/Imagenes/Niveles/fondoPantallaInicio.png";
		SDL_Surface* superficieImagen = IMG_Load(direccionFondo.c_str());
		if(superficieImagen == NULL){
			Log::getInstance()->huboUnErrorSDL("No se pudo cargar una imagen en " + direccionFondo, IMG_GetError());
		}else{
			this->fondoPantalla = SDL_CreateTextureFromSurface( this->renderer, superficieImagen );
			if( this->fondoPantalla == NULL ){
				Log::getInstance()->huboUnErrorSDL("No se pudo crear una textura a partir de la imagen en " + direccionFondo, SDL_GetError());
			}
			SDL_FreeSurface( superficieImagen );
		}

		SDL_Color colorBlanco = { 255, 255, 255, 0xFF };
		this->texturaTextoUsuario = cargoTextura("Ingrese usuario:", colorBlanco,this->renderer,this->fuente );
		this->texturaTextoContrasenia = cargoTextura("Ingrese contrasenia:", colorBlanco,this->renderer,this->fuente );
		if( this->texturaTextoUsuario == nullptr ){
			log->huboUnError("No se pudo crear la textura para el comando del usuario");
		}
		if( this->texturaTextoContrasenia == nullptr ){
			log->huboUnError("No se pudo crear la textura para el comando de la contraseña");
		}
		this->botonEnviar = new BotonConTexto(460, 190, 80 , 40 , "Enviar",this->renderer,this->fuente);
		this->cajaTextoUsuario = new BotonConTexto(400,60,200,20,"...",this->renderer,this->fuente);
		this->cajaTextoContrasenia = new BotonConTexto(400,140,200,20,"...",this->renderer,this->fuente);
		cajaTextoContrasenia->ocultaTexto();
	}
	texturasMarios = intentarCarga("Textura de colores mario", "resources/Imagenes/Personajes/ColoresMarios.png", renderer);
}

void VentanaInicio::actualizarJugadores(actualizacion_cantidad_jugadores_t actualizacion){
	jugadoresConectados = actualizacion.cantidadJugadoresActivos;
	informacionJugadoresConectados = actualizacion;
}

bool VentanaInicio::manejarEntradaUsuario(SDL_Event evento, bool* terminar,string* textoIngresadoUsuario, string* textoIngresadoContrasenia, string** entradaUsuario){
	while( SDL_PollEvent( &evento ) != 0 ){
		if( evento.type == SDL_QUIT ){
			(*terminar) = true;
			throw runtime_error("CerroVentanaDeInicio");
		}
		else if(( evento.type == SDL_KEYDOWN )||(evento.type == SDL_MOUSEBUTTONDOWN)){
			if( evento.key.keysym.sym == SDLK_BACKSPACE && (**entradaUsuario).length() > 0 ){
				(**entradaUsuario).pop_back();
			}
			else if(this->cajaTextoContrasenia->botonClickeado(evento) || evento.key.keysym.sym == SDLK_DOWN){
				(*entradaUsuario) = textoIngresadoContrasenia;
				cajaTextoContrasenia->seleccionarCajaTexto();
				cajaTextoUsuario->deseleccionarCajaTexto();
			}
			else if(this->cajaTextoUsuario->botonClickeado(evento) || evento.key.keysym.sym == SDLK_UP){
				(*entradaUsuario) = textoIngresadoUsuario;
				cajaTextoUsuario->seleccionarCajaTexto();
				cajaTextoContrasenia->deseleccionarCajaTexto();
			}
			else if(this->botonEnviar->botonClickeado(evento) || evento.key.keysym.sym == SDLK_RETURN){
				return true;
			}else if(evento.key.keysym.sym == SDLK_TAB){
				 if((*entradaUsuario) == textoIngresadoUsuario){
					 (*entradaUsuario) = textoIngresadoContrasenia;
					 cajaTextoContrasenia->seleccionarCajaTexto();
					 cajaTextoUsuario->deseleccionarCajaTexto();
				 }else{
					 (*entradaUsuario) = textoIngresadoUsuario;
					 cajaTextoUsuario->seleccionarCajaTexto();
					 cajaTextoContrasenia->deseleccionarCajaTexto();
				 }
			}else if( evento.key.keysym.sym == SDLK_c && (SDL_GetModState() & KMOD_CTRL) ){
				SDL_SetClipboardText( (**entradaUsuario).c_str() );
				(**entradaUsuario) += evento.text.text;
			}
			else if( evento.key.keysym.sym == SDLK_v && (SDL_GetModState() & KMOD_CTRL)){
				(**entradaUsuario) = SDL_GetClipboardText();
			}
		}
		else if( evento.type == SDL_TEXTINPUT ){
			if( !( (SDL_GetModState() & KMOD_CTRL) && ( evento.text.text[ 0 ] == 'c' || evento.text.text[ 0 ] == 'C' || evento.text.text[ 0 ] == 'v' || evento.text.text[ 0 ] == 'V' ) ) ){
				(**entradaUsuario) += evento.text.text;
			}
		}
	}
	return false;
}

void VentanaInicio::seMurioElServer(){
	murioElServer = true;
}

void VentanaInicio::imprimirMensajeDesconexion(){
	SDL_RenderClear( this->renderer );
	SDL_Color colorNegro = { 0, 0, 0, 0xFF };
	SDL_Texture* texturaMensaje = cargoTextura("Ocurrio un error en la conexion con el Servidor.", colorNegro, this->renderer, this->fuente);
	SDL_Texture* texturaMensajeInfo = cargoTextura("Revise su archivo log en la carpeta \"/logs/\".", colorNegro, this->renderer, this->fuente);

	renderizar(20,ALTO_PANTALLA/2-80,40,ANCHO_PANTALLA-50, texturaMensaje, renderer);
	renderizar(20,ALTO_PANTALLA/2,40,ANCHO_PANTALLA-50, texturaMensajeInfo, renderer);
	destructorDeTexturas(texturaMensaje);
	destructorDeTexturas(texturaMensajeInfo);
}

void VentanaInicio::obtenerEntrada(){

	Log* log = Log::getInstance();

	bool terminar = false;

	SDL_Event evento;

	SDL_Color colorBlanco = { 255, 255, 255, 0xFF };

	SDL_StartTextInput();
	string textoIngresadoUsuario = "";
	string textoIngresadoContrasenia = "";
	string* entradaUsuario = &textoIngresadoUsuario;

	bool terminoEntrada = false;

	int anchoTextoUsuario;
	int anchoTextoContrasenia;
	while( !terminar && !terminoEntrada){
		terminoEntrada = manejarEntradaUsuario(evento,&terminar,&textoIngresadoUsuario,&textoIngresadoContrasenia,&entradaUsuario);

		SDL_Texture* texturaCantidadJugadores = cargoTextura("Conectados "+ to_string(jugadoresConectados)+"/"+to_string(jugadoresTotales)+" jugadores", colorBlanco,this->renderer,this->fuente);
		cajaTextoUsuario->cambiarTexto(textoIngresadoUsuario);
		cajaTextoContrasenia->cambiarTexto(textoIngresadoContrasenia);

		anchoTextoUsuario = textoIngresadoUsuario.length()*10;
		if(textoIngresadoUsuario.empty()){
			anchoTextoUsuario = 30;
		}

		if(anchoTextoUsuario>270){
			anchoTextoUsuario = 270;
		}

		anchoTextoContrasenia = textoIngresadoContrasenia.length()*10;
		if(textoIngresadoContrasenia.empty()){
			anchoTextoContrasenia = 30;
		}
		if(anchoTextoContrasenia>270){
			anchoTextoContrasenia = 270;
		}

		SDL_SetRenderDrawColor( this->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( this->renderer );

		SDL_Rect rectanguloCamara = {0, 0, ALTO_PANTALLA, ANCHO_PANTALLA};
		SDL_RenderCopy( this->renderer, this->fondoPantalla, &rectanguloCamara, NULL);

		this->botonEnviar->mostrarse();

		renderizar(380,40,14,200,this->texturaTextoUsuario,renderer);

		this->cajaTextoUsuario->mostrarseCambiandoAncho(anchoTextoUsuario);

		renderizar(380,120,14,250,this->texturaTextoContrasenia,renderer);

		this->cajaTextoContrasenia->mostrarseCambiandoAncho(anchoTextoContrasenia);

		if(texturaCantidadJugadores != nullptr ){
			renderizar(380,320,14,250,texturaCantidadJugadores,renderer);
		}
		destructorDeTexturas(texturaCantidadJugadores);

		this->ponerLosMarios();

		if(ingresoIncorrectoCredenciales || murioElServer){
			if(murioElServer){
				imprimirMensajeDesconexion();
			}else{
				SDL_Color colorRojo = { 214, 40, 57, 0xFF };
				SDL_Rect rectangulo = {370, 265, 260, 30 };
				SDL_SetRenderDrawColor(renderer, 162, 177, 205, 0xFF );
				SDL_RenderFillRect(renderer, &rectangulo);
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF );
				SDL_RenderDrawRect(renderer, &rectangulo);
				SDL_Texture* texturaMensaje = cargoTextura(errorDeIngreso, colorRojo, this->renderer, this->fuente);
				if(texturaMensaje == nullptr){
					log->huboUnError("No se pudo crear la textura para el mensaje: '" + errorDeIngreso +"'");

				}
				renderizar(375, 270, 18, 250, texturaMensaje, renderer);
				destructorDeTexturas(texturaMensaje);
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

bool VentanaInicio::estaConectado(string nombre){
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
		errorDeIngreso = string("La sala esta llena, no puede ingresar");
	}else if(murioElServer){
		errorDeIngreso = string("Se perdio la conexion con el servidor."); //ACA NO NOS SIRVE
	}else if(estaConectado(credenciales.nombre)){
		errorDeIngreso = string("Este jugador ya ingreso a la sala.");
	}else{
		errorDeIngreso = string("Las credenciales ingresadas son erroneas");
	}
}

void VentanaInicio::imprimirMensajeEspera(){
	SDL_Event evento;
	while( SDL_PollEvent( &evento ) != 0 ){
		if( evento.type == SDL_QUIT ){
			throw runtime_error("CerroVentanaDeInicio");
		}
	}

	Log* log = Log::getInstance();

	SDL_RenderClear( this->renderer );

	SDL_Rect rectanguloCamara = {0, 0, ALTO_PANTALLA, ANCHO_PANTALLA};
	SDL_RenderCopy( this->renderer, this->fondoPantalla, &rectanguloCamara, NULL);

	SDL_Color colorVerde = { 1, 152, 117, 0xFF };

	SDL_Texture* texturaMensajeCredencialesCorrectas = cargoTextura("Credenciales correctas", colorVerde,this->renderer,this->fuente);
	if(texturaMensajeCredencialesCorrectas == nullptr ){
		log->huboUnError("No se pudo crear la textura para el mensaje de credenciales correctas");
	}else{
		renderizar(375,150,14,250,texturaMensajeCredencialesCorrectas,renderer);
	}
	destructorDeTexturas(texturaMensajeCredencialesCorrectas);

	SDL_Texture* texturaMensajeEspera = cargoTextura("Esperando al resto de jugadores", colorVerde,this->renderer,this->fuente);
	if(texturaMensajeEspera == nullptr ){
		log->huboUnError("No se pudo crear la textura para el mensaje de credenciales correctas");
	}else{
		renderizar(375,180,14,250,texturaMensajeEspera,renderer);
	}
	destructorDeTexturas(texturaMensajeEspera);

	SDL_Color colorBlanco = { 255, 255, 255, 0xFF };

	SDL_Texture* texturaCantidadJugadores = cargoTextura("Conectados "+ to_string(jugadoresConectados)+"/"+to_string(jugadoresTotales)+" jugadores", colorBlanco,this->renderer,this->fuente);
	if(texturaCantidadJugadores != nullptr ){
		renderizar(380,320,14,250,texturaCantidadJugadores,renderer);
	}
	destructorDeTexturas(texturaCantidadJugadores);

	ponerLosMarios();

	SDL_RenderPresent( this->renderer );
}

credencial_t VentanaInicio::obtenerCredenciales(){
	return credenciales;
}

void VentanaInicio::ponerLosMarios(){
	SDL_Color colorBlanco = { 255, 255, 255, 0xFF };
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

		string strNombre = informacionJugadoresConectados.pares_id_nombre[i].nombre;
		SDL_Texture* texturaNombre = cargoTextura(strNombre, colorBlanco,this->renderer,this->fuente);
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
	//aca se elimina cada textura de la pantalla de espera

	destructorDeTexturas(texturaTextoUsuario);
	destructorDeTexturas(texturaTextoContrasenia);
	destructorDeTexturas(fondoPantalla);
	destructorDeTexturas(texturasMarios);

	delete(this->botonEnviar);
	delete(this->cajaTextoUsuario);
	delete(this->cajaTextoContrasenia);

	SDL_DestroyRenderer( renderer );

	SDL_DestroyWindow( ventana );

}


/* Código repetido del cargador de texturas, no debería ir acá. Pero no peudo utilizar al cargador de texturas hasta tener toda la información del servidor, cosa que no tengo */
SDL_Texture* VentanaInicio::cargarTextura(std::string direccion, SDL_Renderer* renderizador){
	SDL_Texture*  texturaCargada= NULL;
	SDL_Surface* superficieImagen = IMG_Load(direccion.c_str());
	if(superficieImagen == NULL){
		Log::getInstance()->huboUnErrorSDL("No se pudo cargar una imagen en " + direccion, IMG_GetError());
	}
	else{
		texturaCargada = SDL_CreateTextureFromSurface( renderizador, superficieImagen );
		if( texturaCargada == NULL ){
			Log::getInstance()->huboUnErrorSDL("No se pudo crear una textura a partir de la imagen en " + direccion, SDL_GetError());
		}
		SDL_FreeSurface( superficieImagen );
	}
	return texturaCargada;
}

SDL_Texture* VentanaInicio::intentarCarga(std::string descripcion, std::string direccion, SDL_Renderer* renderizador){
	SDL_Texture* texturaCargada =  cargarTextura(direccion, renderizador);
	if(texturaCargada == NULL){
		//texturaCargada = texturaDefecto; TODO: Fijarse si es necesario.
		Log::getInstance()->huboUnError("No se pudo cargar " + descripcion +" en: "+ direccion + ". Se cargo la textura por defecto.");
	}else{
		Log::getInstance()->mostrarMensajeDeCarga(descripcion, direccion);
	}
	return texturaCargada;
}
