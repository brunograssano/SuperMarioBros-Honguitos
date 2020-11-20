#include "VentanaInicio.hpp"
#include "VentanaInicio.hpp"
#include <stdio.h>
using namespace std;

#include "../../log/Log.hpp"
#define ANCHO_PANTALLA 300
#define ALTO_PANTALLA 300
VentanaInicio::VentanaInicio(){
	this->ingresoIncorrectoCredenciales = false;
	Log* log = Log::getInstance();
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		log->huboUnErrorSDL("No se pudo inicializar SDL", SDL_GetError());
	}
	else{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
			log->huboUnError("No se pudo activar el filtrado lineal de texturas");
		}
		this->ventana = SDL_CreateWindow( "Inicio Mario Bros", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_PANTALLA, ALTO_PANTALLA, SDL_WINDOW_SHOWN );
		if( ventana == NULL ){
			log->huboUnErrorSDL("No se pudo crear una ventana de inicio por error de SDL", SDL_GetError());

		}
		else{
			this->renderer = SDL_CreateRenderer( ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderer == NULL ){
				log->huboUnErrorSDL("No se pudo crear el renderer por error de SDL", SDL_GetError());
			}
			else{
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ){
					log->huboUnErrorSDL("No se pudo inicializar SDL image", SDL_GetError());
				}
				if( TTF_Init() == -1 ){
					log->huboUnErrorSDL("No se pudo inicializar SDL ttf", SDL_GetError());
				}
			}
		}
	}

	this->fuente = TTF_OpenFont( "resources/Fuentes/fuenteSuperMarioBros.ttf", 12 );
	if( this->fuente == NULL ){
		log->huboUnErrorSDL("No se pudo cargar la fuente", SDL_GetError());
	}
	else{

		SDL_Color textColor = { 0, 0, 0, 0xFF };
		this->texturaTextoUsuario = cargoTextura("Ingrese usuario:", textColor );
		this->texturaTextoContrasenia = cargoTextura("Ingrese contrasenia:", textColor );
		this->usuarioIngresado = cargoTextura("...", textColor );
		this->contraseniaIngresada = cargoTextura("...", textColor );
		if( this->texturaTextoUsuario == nullptr ){
			log->huboUnError("No se pudo crear la textura para el comando del usuario");
		}
		if( this->texturaTextoContrasenia == nullptr ){
			log->huboUnError("No se pudo crear la textura para el comando de la contraseña");
		}
		if( this->usuarioIngresado == nullptr ){
			log->huboUnError("No se pudo crear la textura para ingresar el usuario");
		}
		if( this->contraseniaIngresada == nullptr ){
			log->huboUnError("No se pudo crear la textura para ingresar la contraseña");
		}
	}
}

SDL_Texture* VentanaInicio::cargoTextura(string texto, SDL_Color color){
	Log* log = Log::getInstance();
	SDL_Texture* texturaACargar;
	SDL_Surface* textSurface = TTF_RenderText_Solid( this->fuente, texto.c_str(), color );
	if( textSurface != NULL ){
		texturaACargar = SDL_CreateTextureFromSurface( this->renderer, textSurface );
		if( texturaACargar == NULL ){
			log->huboUnErrorSDL("No se pudo crear la textura", SDL_GetError());
		}

		SDL_FreeSurface( textSurface );
	}
	else{
		log->huboUnErrorSDL("No se pudo renderizar la superficie", SDL_GetError());
		log->huboUnErrorSDL(texto, SDL_GetError());
	}
	return texturaACargar;
}

bool VentanaInicio::manejarEntradaUsuario(SDL_Event evento, bool* terminar,string* textoIngresadoUsuario, string* textoIngresadoConstrasenia, string** entradaUsuario){
	while( SDL_PollEvent( &evento ) != 0 ){
		if( evento.type == SDL_QUIT ){
			(*terminar) = true;
			throw runtime_error("CerroVentanaDeInicio");
		}
		else if( evento.type == SDL_KEYDOWN ){
			if( evento.key.keysym.sym == SDLK_BACKSPACE && (**entradaUsuario).length() > 0 ){
				(**entradaUsuario).pop_back();
			}
			else if(evento.key.keysym.sym == SDLK_DOWN){
				(*entradaUsuario) = textoIngresadoConstrasenia;
			}
			else if(evento.key.keysym.sym == SDLK_UP){
				(*entradaUsuario) = textoIngresadoUsuario;
			}
			else if(evento.key.keysym.sym == SDLK_RETURN){
				return true;
			}
			else if( evento.key.keysym.sym == SDLK_c && (SDL_GetModState() & KMOD_CTRL) ){
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

void VentanaInicio::obtenerEntrada(unsigned short jugadoresConectados, unsigned short jugadoresTotales){

	bool terminar = false;

	SDL_Event evento;

	SDL_Color textColor = { 0, 0, 0, 0xFF };

	this->texturaCantidadJugadores = cargoTextura("Conectados "+ to_string(jugadoresConectados)+"/"+to_string(jugadoresTotales)+" jugadores", textColor);

	SDL_StartTextInput();
	string textoIngresadoUsuario = "...";
	string textoIngresadoContrasenia = "...";
	string* entradaUsuario = &textoIngresadoUsuario;

	bool terminoEntrada = false;
	Log* log = Log::getInstance();

	while( !terminar && !terminoEntrada){

		terminoEntrada = manejarEntradaUsuario(evento,&terminar,&textoIngresadoUsuario,&textoIngresadoContrasenia,&entradaUsuario);

		if(textoIngresadoUsuario.length() != 0){
			this->usuarioIngresado = cargoTextura( textoIngresadoUsuario.c_str(), textColor );
		}
		if(textoIngresadoContrasenia.length() != 0){
			this->contraseniaIngresada = cargoTextura( textoIngresadoContrasenia.c_str(), textColor );
		}

		SDL_SetRenderDrawColor( this->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( this->renderer );

		int anchoTextoUsuario = textoIngresadoUsuario.length()*10;
		if(anchoTextoUsuario>270){
			anchoTextoUsuario = 270;
		}

		int anchoTextoContrasenia = textoIngresadoContrasenia.length()*10;
		if(anchoTextoContrasenia>270){
			anchoTextoContrasenia = 270;
		}

		renderizar(10,20,14,200,this->texturaTextoUsuario);
		if(textoIngresadoUsuario.length() != 0){
			renderizar(20,40,14,anchoTextoUsuario,this->usuarioIngresado);
		}

		renderizar(10,70,14,250,this->texturaTextoContrasenia);
		if(textoIngresadoContrasenia.length() != 0){
			renderizar(20,90,14,anchoTextoContrasenia,this->contraseniaIngresada);
		}
		if(ingresoIncorrectoCredenciales){
			SDL_Color colorRojo = { 207, 0, 15, 0xFF };
			this->texturaMensajeCredencialesIncorrectas = cargoTextura("Las credenciales ingresadas son erroneas", colorRojo);
			if( this->texturaMensajeCredencialesIncorrectas == nullptr ){
				log->huboUnError("No se pudo crear la textura para el mensaje de error de credenciales");
			}else{
				renderizar(10,170,14,250,texturaMensajeCredencialesIncorrectas);
			}
		}

		if( this->texturaCantidadJugadores != nullptr ){
			renderizar(10,140,14,250,texturaCantidadJugadores);
		}

		SDL_RenderPresent( this->renderer );


		SDL_DestroyTexture( usuarioIngresado );
		SDL_DestroyTexture( contraseniaIngresada );
	}

	SDL_StopTextInput();

	credenciales.nombre = textoIngresadoUsuario;
	credenciales.contrasenia = textoIngresadoContrasenia;



	// enviar entrada al server
}

void VentanaInicio::imprimirMensajeError(){
	ingresoIncorrectoCredenciales = true;
}

void VentanaInicio::imprimirMensajeEspera(unsigned short cantJugadoresConectados, unsigned short cantJugadoresTotales){
	SDL_Event evento;
	while( SDL_PollEvent( &evento ) != 0 ){
		if( evento.type == SDL_QUIT ){
			throw runtime_error("CerroVentanaDeInicio");
		}
	}

	Log* log = Log::getInstance();
	SDL_RenderClear( this->renderer );
	SDL_DestroyTexture( texturaTextoUsuario );
	SDL_DestroyTexture( texturaMensajeCredencialesIncorrectas );
	SDL_DestroyTexture( texturaTextoContrasenia );
	SDL_DestroyTexture(	texturaCantidadJugadores);

	SDL_Color colorVerde = { 1, 152, 117, 0xFF };
	this->texturaMensajeCredencialesCorrectas = cargoTextura("Credenciales correctas, esperando al resto de jugadores", colorVerde);
	if( this->texturaMensajeCredencialesCorrectas == nullptr ){
		log->huboUnError("No se pudo crear la textura para el mensaje de credenciales correctas");
	}else{
		renderizar(10,20,14,250,texturaMensajeCredencialesCorrectas);
	}
	//aca se crearia cada textura del string del server y se pone por pantalla

	SDL_Color textColor = { 0, 0, 0, 0xFF };
	this->texturaCantidadJugadores = cargoTextura("Conectados "+ to_string(cantJugadoresConectados)+"/"+to_string(cantJugadoresTotales)+" jugadores", textColor);

	if( this->texturaCantidadJugadores != nullptr ){
		renderizar(10,180,14,250,texturaCantidadJugadores);
	}

	SDL_RenderPresent( this->renderer );
}

void VentanaInicio::renderizar(int coordenadaX,int coordenadaY,int alto,int ancho,SDL_Texture* textura){
		SDL_Rect renderQuad = { coordenadaX, coordenadaY, ancho, alto };
		SDL_Rect* clip = NULL;
		double angle = 0.0;
		SDL_Point* center = NULL;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		SDL_RenderCopyEx( this->renderer, textura, clip, &renderQuad, angle, center, flip );
}

credencial_t VentanaInicio::obtenerCredenciales(){
	return credenciales;
}



VentanaInicio::~VentanaInicio(){
	//aca se elimina cada textura de la pantalla de espera
	SDL_DestroyTexture( texturaCantidadJugadores );
	SDL_DestroyTexture( texturaMensajeCredencialesCorrectas );
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( ventana );

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
