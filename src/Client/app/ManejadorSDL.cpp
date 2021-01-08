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

SDL_Renderer* crearRenderer(SDL_Window* ventana){
	Log* log = Log::getInstance();
	SDL_Renderer* renderer = SDL_CreateRenderer( ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( renderer == nullptr ){
		log->huboUnErrorSDL("No se pudo crear el renderer por error de SDL", SDL_GetError());
	}else{
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	}
	return renderer;
}

void cargarIcono(SDL_Window* ventana){
	Log* log = Log::getInstance();
	string direccionIcono = "resources/Imagenes/Personajes/IconoHongo.png";
	SDL_Surface* icono = IMG_Load(direccionIcono.c_str());
	if(icono == nullptr){
		log->huboUnErrorSDL("No se pudo cargar el icono en: " + direccionIcono, IMG_GetError());
	}else{
		SDL_SetWindowIcon(ventana, icono);
		SDL_FreeSurface(icono);
	}
}

SDL_Window* crearVentana(const char *titulo, int alto, int ancho){
    SDL_Window* ventanaAplicacion = SDL_CreateWindow( titulo, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ancho, alto, SDL_WINDOW_SHOWN );
    if( ventanaAplicacion == nullptr ){
        Log::getInstance()->huboUnErrorSDL("No se pudo crear una ventana de SDL", SDL_GetError());
    }
    return ventanaAplicacion;
}

SDL_Texture* cargoTextura(const string& texto, SDL_Color color,SDL_Renderer* renderer,TTF_Font* fuente){
	Log* log = Log::getInstance();
	SDL_Texture* texturaACargar;
	SDL_Surface* textSurface = TTF_RenderText_Solid( fuente, texto.c_str(), color );
	if( textSurface != nullptr ){
		texturaACargar = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( texturaACargar == nullptr ){
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

void renderizar(int coordenadaX,int coordenadaY,int alto,int ancho,SDL_Texture* textura,SDL_Renderer* renderer){
		SDL_Rect renderQuad = { coordenadaX, coordenadaY, ancho, alto };
		SDL_Rect* clip = nullptr;
		double angle = 0.0;
		SDL_Point* center = nullptr;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		SDL_RenderCopyEx( renderer, textura, clip, &renderQuad, angle, center, flip );
}

void destructorDeTexturas(SDL_Texture* textura){
	if(textura != nullptr){
		SDL_DestroyTexture( textura );
		textura = nullptr;
	}
}

void terminarSDL(){
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
