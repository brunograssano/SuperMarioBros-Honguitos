#include "ManejadorSDL.hpp"
#include "../../Utils/log/Log.hpp"

void iniciarSDL(){
	Log* log = Log::getInstance();
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		log->huboUnErrorSDL("No se pudo inicializar SDL", SDL_GetError());
		exit(-1);
	}
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
		log->huboUnError("No se pudo activar el filtrado lineal de texturas");
		exit(-1);
	}
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ){
		log->huboUnErrorSDL("No se pudo inicializar SDL image", SDL_GetError());
		exit(-1);
	}
	if( TTF_Init() == -1 ){
		log->huboUnErrorSDL("No se pudo inicializar SDL ttf", SDL_GetError());
		exit(-1);
	}
}

void destructorDeTexturas(SDL_Texture* textura){
	SDL_DestroyTexture( textura );
	textura = nullptr;
}

void terminarSDL(){
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
