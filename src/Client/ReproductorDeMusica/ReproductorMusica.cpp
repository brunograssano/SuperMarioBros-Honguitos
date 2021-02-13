#include "ReproductorMusica.hpp"
#include "EstadoMusica.hpp"
#include "src/Utils/Constantes.hpp"
#include <string>
#include <utility>
#include "src/Utils/log/Log.hpp"

ReproductorMusica* ReproductorMusica::reproductor = nullptr;

ReproductorMusica::ReproductorMusica(){
	if((Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)){
		Log::getInstance()->huboUnErrorSDL("Hubo un fallo al inicializar el reproductor de musica", Mix_GetError());
	}
    std::map<uint8_t,std::string> nombresSonidos;
	nombresSonidos.insert(std::pair<uint8_t,std::string>(SONIDO_SALTO,DIRECCION_SONIDO_SALTO));
	nombresSonidos.insert(std::pair<uint8_t,std::string>(SONIDO_AGARRAR_MONEDA,DIRECCION_SONIDO_AGARRAR_MONEDA));
	nombresSonidos.insert(std::pair<uint8_t,std::string>(SONIDO_MATAR_GOOMBA,DIRECCION_SONIDO_MUERTE_GOOMBA));
    nombresSonidos.insert(std::pair<uint8_t,std::string>(SONIDO_MATAR_KOOPA,DIRECCION_SONIDO_MUERTE_KOOPA));
    nombresSonidos.insert(std::pair<uint8_t,std::string>(SONIDO_APARECE_FLOR,DIRECCION_SONIDO_APARECE_PLANTA));
    nombresSonidos.insert(std::pair<uint8_t,std::string>(SONIDO_AGARRA_POWERUP,DIRECCION_SONIDO_MARIO_AGARRA_HONGO));
    nombresSonidos.insert(std::pair<uint8_t,std::string>(SONIDO_MORIR,DIRECCION_SONIDO_MARIO_MUERE));
    nombresSonidos.insert(std::pair<uint8_t,std::string>(SONIDO_LANZAR_BOLA_DE_FUEGO,DIRECCION_SONIDO_MARIO_LANZA_FUEGO));
    nombresSonidos.insert(std::pair<uint8_t,std::string>(SONIDO_LANZAR_CHISPA,DIRECCION_SONIDO_CHISPA));
    nombresSonidos.insert(std::pair<uint8_t,std::string>(SONIDO_REBOTE_BOLA_DE_FUEGO,DIRECCION_SONIDO_REBOTE));
	nombresSonidos.insert(std::pair<uint8_t,std::string>(SONIDO_EXPLOSION_BOLA_DE_FUEGO,DIRECCION_SONIDO_EXPLOSION));
	nombresSonidos.insert(std::pair<uint8_t,std::string>(SONIDO_LLEGAR_A_LA_META,DIRECCION_SONIDO_PASAR_NIVEL));

    std::string nombreArchivo;
	Mix_Chunk* efecto = nullptr;

	for (const auto& elemento : nombresSonidos) {
		nombreArchivo = elemento.second;
		efecto = Mix_LoadWAV(nombreArchivo.c_str());
		if(efecto == nullptr){
			Log::getInstance()->huboUnError("Hubo un error al intentar cargar el efecto especial en la direccion "+ nombreArchivo);
		}else{
			efectosDeSonido.insert(std::pair<uint8_t, Mix_Chunk*>(elemento.first, efecto));
		}
	}

    estadoMusica = new Suena();
    estadoSonidos = new SuenanSonidos();
}

ReproductorMusica* ReproductorMusica::getInstance(){
	if(reproductor==nullptr){
		reproductor= new ReproductorMusica();
	}
	return reproductor;
}

void ReproductorMusica::ReproducirMusicaNivel(std::string nombreCancion){
    estadoMusica->reproducir(std::move(nombreCancion));
}

void ReproductorMusica::ponerMusica(const std::string& nombreCancion){
    Mix_Music* cancion = nullptr;

    if (cancionReproduciendose == nullptr){

        cancion = Mix_LoadMUS( nombreCancion.c_str());
        if( cancion == nullptr ){
            Log::getInstance()->huboUnErrorSDL("Hubo un fallo al intentar cargar la musica en la direccion "+ nombreCancion, Mix_GetError());
        }else{
            cancionReproduciendose = cancion;
            if(Mix_PlayMusic( cancion, -1 ) == 0){
                Log::getInstance()->mostrarMensajeDeInfo("Se reproduce la cancion de la direccion: "+nombreCancion);
            }else{
                Log::getInstance()->huboUnErrorSDL("Hubo un fallo al intentar reproducir la musica en la direccion "+ nombreCancion, Mix_GetError());
            }

        }

    }else{

        Mix_Music* cancionABorrar = cancionReproduciendose;
        cancion = Mix_LoadMUS( nombreCancion.c_str());

        if( cancion == nullptr ){
            Log::getInstance()->huboUnErrorSDL("Hubo un fallo al intentar cargar la musica en la direccion "+ nombreCancion, Mix_GetError());
        }else{
            cancionReproduciendose = cancion;
            if(Mix_PlayMusic( cancion, -1 ) == 0){
                Log::getInstance()->mostrarMensajeDeInfo("Se reproduce la cancion de la direccion: "+nombreCancion);
                Mix_FreeMusic(cancionABorrar);
            }else{
                Log::getInstance()->huboUnErrorSDL("Hubo un fallo al intentar reproducir la musica en la direccion "+ nombreCancion, Mix_GetError());
                Mix_FreeMusic(cancionABorrar);
            }
        }
    }
}

void ReproductorMusica::pausarMusica(){
    Mix_PauseMusic();
}

void ReproductorMusica::reanudarMusica(){
    Mix_ResumeMusic();
}

void ReproductorMusica::cambiarMusica(){
    EstadoMusica* nuevoEstadoMusica = estadoMusica->cambiar();
    delete estadoMusica;
    estadoMusica = nuevoEstadoMusica;
}

void ReproductorMusica::cambiarSonidos(){
    EstadoSonidos* nuevoEstadoSonidos = estadoSonidos->cambiar();
    delete estadoSonidos;
    estadoSonidos = nuevoEstadoSonidos;
}

void ReproductorMusica::reproducirSonido(const uint8_t& tipoSonido) {
    Mix_Chunk* efecto = efectosDeSonido.at(tipoSonido);
    estadoSonidos->reproducir(efecto);
}

ReproductorMusica::~ReproductorMusica(){
	Mix_FreeMusic(cancionReproduciendose);
	for (const auto& elemento : efectosDeSonido) {
		Mix_FreeChunk(elemento.second);
	}
	Mix_Quit();
	delete estadoSonidos;
	delete estadoMusica;
}