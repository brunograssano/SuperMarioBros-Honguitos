#include "VentanaInicio.hpp"
#include "VentanaInicio.hpp"
#include <stdio.h>
using namespace std;

#include "../../log/Log.hpp"
#define ANCHO_PANTALLA 300
#define ALTO_PANTALLA 300
VentanaInicio::VentanaInicio(){
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
	//Open the font
	this->fuente = TTF_OpenFont( "resources/Fuentes/fuenteSuperMarioBros.ttf", 14 );
	if( this->fuente == NULL )
	{
		log->huboUnErrorSDL("No se pudo cargar la fuente", SDL_GetError());
	}
	else
	{
		//Render the prompt
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
		if( textSurface != NULL )
		{
			//Create texture from surface pixels
			texturaACargar = SDL_CreateTextureFromSurface( this->renderer, textSurface );
			if( texturaACargar == NULL )
			{
				log->huboUnErrorSDL("No se pudo crear la textura", SDL_GetError());
			}

			SDL_FreeSurface( textSurface );
		}
		else
		{
			log->huboUnErrorSDL("No se pudo renderizar la superficie", SDL_GetError());
		}
	return texturaACargar;
}
void VentanaInicio::ObtenerEntrada(){

	bool terminar = false;

	SDL_Event evento;

	SDL_Color textColor = { 0, 0, 0, 0xFF };

	SDL_StartTextInput();

	while( !terminar ){
		bool renderText = false;
		string input;
		while( SDL_PollEvent( &evento ) != 0 ){
			if( evento.type == SDL_QUIT ){
				terminar = true;
			}
			else if( evento.type == SDL_KEYDOWN ){
				if( evento.key.keysym.sym == SDLK_BACKSPACE && input.length() > 0 ){
					input.pop_back();
					renderText = true;
				}
				else if( evento.key.keysym.sym == SDLK_c && (SDL_GetModState() & KMOD_CTRL) ){
					SDL_SetClipboardText( input.c_str() );
				}
				else if( evento.key.keysym.sym == SDLK_v && (SDL_GetModState() & KMOD_CTRL)){
					input = SDL_GetClipboardText();
					renderText = true;
				}
			}
			else if( evento.type == SDL_TEXTINPUT ){
				if( !( (SDL_GetModState() & KMOD_CTRL) && ( evento.text.text[ 0 ] == 'c' || evento.text.text[ 0 ] == 'C' || evento.text.text[ 0 ] == 'v' || evento.text.text[ 0 ] == 'V' ) ) ){
					input += evento.text.text;
					renderText = true;
				}
			}
		}
		if( renderText ){
			if( input != "" ){
				this->usuarioIngresado = cargoTextura( input.c_str(), textColor );
			}
			else{
				this->usuarioIngresado = cargoTextura( "", textColor );
			}
		}

		SDL_SetRenderDrawColor( this->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( this->renderer );

		Renderizar(10,20,14,200,this->texturaTextoUsuario);
		Renderizar(10,40,14,200,this->texturaTextoContrasenia);
		Renderizar(10,70,14,100,this->usuarioIngresado);
		Renderizar(10,90,14,100,this->contraseniaIngresada);

		SDL_RenderPresent( this->renderer );
	}

	SDL_StopTextInput();
}

void VentanaInicio::Renderizar(int coordenadaX,int coordenadaY,int alto,int ancho,SDL_Texture* textura){
		SDL_Rect renderQuad = { coordenadaX, coordenadaY, ancho, alto };
		SDL_Rect* clip = NULL;
		double angle = 0.0;
		SDL_Point* center = NULL;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		SDL_RenderCopyEx( this->renderer, textura, clip, &renderQuad, angle, center, flip );
}

VentanaInicio::~VentanaInicio(){


	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( ventana );

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
