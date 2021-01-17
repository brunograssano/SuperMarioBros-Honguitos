#include "ReproductorMusica.hpp"
#include "EstadoMusica.hpp"
#include "src/Utils/Constantes.hpp"
#include <string>
#include <utility>

ReproductorMusica* ReproductorMusica::reproductor = nullptr;

ReproductorMusica::ReproductorMusica(){
	if((Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)){
		Log::getInstance()->huboUnErrorSDL("Hubo un fallo al inicializar el reproductor de musica", Mix_GetError());
	}
	map<uint8_t,string> nombresSonidos;
	nombresSonidos.insert(std::pair<uint8_t,string>(SONIDO_SALTO,"resources/Musica/EfectosSonido/EfectoSalto.wav"));
	nombresSonidos.insert(std::pair<uint8_t,string>(SONIDO_AGARRAR_MONEDA,"resources/Musica/EfectosSonido/AgarrarMoneda.wav"));
	nombresSonidos.insert(std::pair<uint8_t,string>(SONIDO_MATAR_GOOMBA,"resources/Musica/EfectosSonido/MarioMataGoomba.wav"));
    nombresSonidos.insert(std::pair<uint8_t,string>(SONIDO_MATAR_KOOPA,"resources/Musica/EfectosSonido/MarioPisaKoopa.wav"));
    nombresSonidos.insert(std::pair<uint8_t,string>(SONIDO_APARECE_FLOR,"resources/Musica/EfectosSonido/AparecePlanta.wav"));
    nombresSonidos.insert(std::pair<uint8_t,string>(SONIDO_AGARRA_POWERUP,"resources/Musica/EfectosSonido/MarioAgarraHongo.wav"));
    nombresSonidos.insert(std::pair<uint8_t,string>(SONIDO_MORIR,"resources/Musica/EfectosSonido/MarioMorir.wav"));
    nombresSonidos.insert(std::pair<uint8_t,string>(SONIDO_LANZAR_BOLA_DE_FUEGO,"resources/Musica/EfectosSonido/MarioLanzaFuego.wav"));
    nombresSonidos.insert(std::pair<uint8_t,string>(SONIDO_LANZAR_CHISPA,"resources/Musica/EfectosSonido/Chispazo.wav"));
    nombresSonidos.insert(std::pair<uint8_t,string>(SONIDO_REBOTE_BOLA_DE_FUEGO,"resources/Musica/EfectosSonido/ReboteBolaDeFuego.wav"));
	nombresSonidos.insert(std::pair<uint8_t,string>(SONIDO_EXPLOSION_BOLA_DE_FUEGO,"resources/Musica/EfectosSonido/ExplosionBolaDeFuego.wav"));
	nombresSonidos.insert(std::pair<uint8_t,string>(SONIDO_LLEGAR_A_LA_META,"resources/Musica/EfectosSonido/PasarDeNivel.wav"));

	string nombreArchivo;
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

void ReproductorMusica::ReproducirMusicaNivel(string nombreCancion){
    estadoMusica->reproducir(std::move(nombreCancion));
}

void ReproductorMusica::ponerMusica(const string& nombreCancion){
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