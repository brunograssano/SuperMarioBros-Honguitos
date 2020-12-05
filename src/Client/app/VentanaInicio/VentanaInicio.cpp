#include "VentanaInicio.hpp"

#include <stdio.h>
using namespace std;

#include "../../../Utils/log/Log.hpp"
#define ANCHO_PANTALLA 650
#define ALTO_PANTALLA 450

VentanaInicio::VentanaInicio(unsigned short jugadoresConectados, unsigned short jugadoresTotales){
	this->ingresoIncorrectoCredenciales = false;
	this->salaLlena = false;
	this->jugadoresTotales = jugadoresTotales;
	this->jugadoresConectados = jugadoresConectados;
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

		string direccionIcono = "resources/Imagenes/Personajes/IconoHongo.png";
		SDL_Surface* icono = IMG_Load(direccionIcono.c_str());
		if(icono == NULL){
			log->huboUnErrorSDL("No se pudo cargar el icono en: " + direccionIcono, IMG_GetError());
		}
		else{
			SDL_SetWindowIcon(this->ventana, icono);
			SDL_FreeSurface(icono);
		}

		string direccionFondo = "resources/Imagenes/Niveles/fondoPantallaInicio.png";
		SDL_Surface* superficieImagen = IMG_Load(direccionFondo.c_str());
		if(superficieImagen == NULL){
			Log::getInstance()->huboUnErrorSDL("No se pudo cargar una imagen en " + direccionFondo, IMG_GetError());
		}
		else{
			this->fondoPantalla = SDL_CreateTextureFromSurface( this->renderer, superficieImagen );
			if( this->fondoPantalla == NULL ){
				Log::getInstance()->huboUnErrorSDL("No se pudo crear una textura a partir de la imagen en " + direccionFondo, SDL_GetError());
			}
			SDL_FreeSurface( superficieImagen );
		}

		SDL_Color colorBlanco = { 255, 255, 255, 0xFF };
		this->texturaTextoUsuario = cargoTextura("Ingrese usuario:", colorBlanco );
		this->texturaTextoContrasenia = cargoTextura("Ingrese contrasenia:", colorBlanco );
		if( this->texturaTextoUsuario == nullptr ){
			log->huboUnError("No se pudo crear la textura para el comando del usuario");
		}
		if( this->texturaTextoContrasenia == nullptr ){
			log->huboUnError("No se pudo crear la textura para el comando de la contraseña");
		}
		this->botonEnviar = new BotonConTexto(470, 200, 80 , 40 , "Enviar",this->renderer,this->fuente);
		this->cajaTextoUsuario = new BotonConTexto(400,60,200,20,"...",this->renderer,this->fuente);
		this->cajaTextoContrasenia = new BotonConTexto(400,140,200,20,"...",this->renderer,this->fuente);
	}
	texturasMarios = intentarCarga("Textura de colores mario", "resources/Imagenes/Personajes/ColoresMarios.png", renderer);
}

void VentanaInicio::actualizarJugadores(actualizacion_cantidad_jugadores_t actualizacion){
	jugadoresConectados = actualizacion.cantidadJugadoresActivos;
	informacionJugadoresConectados = actualizacion;
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

		this->texturaCantidadJugadores = cargoTextura("Conectados "+ to_string(jugadoresConectados)+"/"+to_string(jugadoresTotales)+" jugadores", colorBlanco);
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

		renderizar(380,40,14,200,this->texturaTextoUsuario);

		this->cajaTextoUsuario->mostrarseCambiandoAncho(anchoTextoUsuario);

		renderizar(380,120,14,250,this->texturaTextoContrasenia);

		this->cajaTextoContrasenia->mostrarseCambiandoAncho(anchoTextoContrasenia);

		if(ingresoIncorrectoCredenciales){
			SDL_Color colorRojo = { 207, 0, 15, 0xFF };

			if (jugadoresConectados >= jugadoresTotales){
				salaLlena = true;
				this->texturaMensajeSalaLlena = cargoTextura("La sala esta llena, no puede ingresar", colorRojo);
				if( this->texturaMensajeSalaLlena == nullptr ){
					log->huboUnError("No se pudo crear la textura para el mensaje de error de sala llena");
				}
				renderizar(380,250,14,250,texturaMensajeSalaLlena);

			}else{

				this->texturaMensajeCredencialesIncorrectas = cargoTextura("Las credenciales ingresadas son erroneas", colorRojo);
				if( this->texturaMensajeCredencialesIncorrectas == nullptr ){
					log->huboUnError("No se pudo crear la textura para el mensaje de error de credenciales");
				}else{
					renderizar(380,250,14,250,texturaMensajeCredencialesIncorrectas);

				}
			}

		}

		if( this->texturaCantidadJugadores != nullptr ){
			renderizar(380,280,14,250,texturaCantidadJugadores);
		}

		this->ponerLosMarios();

		SDL_RenderPresent( this->renderer );


		SDL_DestroyTexture( usuarioIngresado );
		SDL_DestroyTexture( contraseniaIngresada );
	}

	SDL_StopTextInput();
	if (!salaLlena){
		const char* punteroTextoIngresadoUsuario = textoIngresadoUsuario.c_str();
		const char* punteroTextoIngresadoContrasenia = textoIngresadoContrasenia.c_str();

		strcpy(credenciales.nombre,punteroTextoIngresadoUsuario);
		strcpy(credenciales.contrasenia,punteroTextoIngresadoContrasenia);
	}
}

void VentanaInicio::imprimirMensajeError(){
	ingresoIncorrectoCredenciales = true;
}

void VentanaInicio::imprimirMensajeEspera(){
	SDL_Event evento;
	while( SDL_PollEvent( &evento ) != 0 ){
		if( evento.type == SDL_QUIT ){
			throw runtime_error("CerroVentanaDeInicio");
		}
	}

	Log* log = Log::getInstance();
	/*
	delete(this->botonEnviar);
	delete(this->cajaTextoUsuario);
	delete(this->cajaTextoContrasenia);
	*/
	SDL_RenderClear( this->renderer );
	SDL_DestroyTexture( texturaTextoUsuario );
	SDL_DestroyTexture( texturaMensajeCredencialesIncorrectas );
	SDL_DestroyTexture( texturaTextoContrasenia );
	SDL_DestroyTexture(	texturaCantidadJugadores);

	SDL_Rect rectanguloCamara = {0, 0, ALTO_PANTALLA, ANCHO_PANTALLA};
	SDL_RenderCopy( this->renderer, this->fondoPantalla, &rectanguloCamara, NULL);

	SDL_Color colorVerde = { 1, 152, 117, 0xFF };
	this->texturaMensajeCredencialesCorrectas = cargoTextura("Credenciales correctas, esperando al resto de jugadores", colorVerde);
	if( this->texturaMensajeCredencialesCorrectas == nullptr ){
		log->huboUnError("No se pudo crear la textura para el mensaje de credenciales correctas");
	}else{
		renderizar(380,240,14,250,texturaMensajeCredencialesCorrectas);
	}
	//aca se crearia cada textura del string del server y se pone por pantalla

	SDL_Color colorBlanco = { 255, 255, 255, 0xFF };
	this->texturaCantidadJugadores = cargoTextura("Conectados "+ to_string(jugadoresConectados)+"/"+to_string(jugadoresTotales)+" jugadores", colorBlanco);

	if( this->texturaCantidadJugadores != nullptr ){
		renderizar(380,280,14,250,texturaCantidadJugadores);
	}

	ponerLosMarios();

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


void VentanaInicio::ponerLosMarios(){
	for(int i = 0; i < informacionJugadoresConectados.tope; i++){
		SDL_Rect rectanguloMario = {100 + 50*i, ALTO_PANTALLA - 100, 32, 64};
		SDL_Rect recorte = {0, 0, 0, 0};
		if(informacionJugadoresConectados.pares_id_nombre[i].conectado)
			recorte = {i*16, 0, 16, 32};
		else
			recorte = {64, 0, 16, 32};
		SDL_RenderCopy(renderer, texturasMarios, &recorte, &rectanguloMario);
	}
}


VentanaInicio::~VentanaInicio(){
	//aca se elimina cada textura de la pantalla de espera
	if (texturaMensajeSalaLlena != nullptr){
		SDL_DestroyTexture( texturaMensajeSalaLlena );
	}
	SDL_DestroyTexture( fondoPantalla );
	SDL_DestroyTexture( texturaCantidadJugadores );
	SDL_DestroyTexture( texturaMensajeCredencialesCorrectas );
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
