#include "ReproductorMusica.hpp"
#include "EstadoMusica.hpp"

#include <string>

ReproductorMusica* ReproductorMusica::reproductor = nullptr;

ReproductorMusica::ReproductorMusica(){
	if((Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)){
		Log::getInstance()->huboUnErrorSDL("Hubo un fallo al inicializar el reproductor de musica", Mix_GetError());
	}
	map<string,string> nombresSonidos;
	nombresSonidos.insert(std::pair<string,string>("EfectoSalto","resources/Musica/EfectosSonido/EfectoSalto.wav"));
	nombresSonidos.insert(std::pair<string,string>("AgarrarMoneda","resources/Musica/EfectosSonido/AgarrarMoneda.wav"));
	nombresSonidos.insert(std::pair<string,string>("InicioJuego","resources/Musica/EfectosSonido/InicioJuego.wav"));
	nombresSonidos.insert(std::pair<string,string>("SumarVida","resources/Musica/EfectosSonido/SumarVida.wav"));
	nombresSonidos.insert(std::pair<string,string>("RomperBloque","resources/Musica/EfectosSonido/RomperBloque.wav"));
	nombresSonidos.insert(std::pair<string,string>("MarioMataGoomba","resources/Musica/EfectosSonido/MarioMataGoomba.wav"));
	nombresSonidos.insert(std::pair<string,string>("MarioChicoGolpeaLadrillo","resources/Musica/EfectosSonido/MarioChicoGolpeaLadrillo.wav"));
	nombresSonidos.insert(std::pair<string,string>("MarioLanzaFuego","resources/Musica/EfectosSonido/MarioLanzaFuego.wav"));
	nombresSonidos.insert(std::pair<string,string>("SonidoBandera","resources/Musica/EfectosSonido/SonidoBandera.wav"));
	nombresSonidos.insert(std::pair<string,string>("AparecePlanta","resources/Musica/EfectosSonido/AparecePlanta.wav"));
	nombresSonidos.insert(std::pair<string,string>("MarioAgarraHongo","resources/Musica/EfectosSonido/MarioAgarraHongo.wav"));
	nombresSonidos.insert(std::pair<string,string>("ApareceHongo","resources/Musica/EfectosSonido/ApareceHongo.wav"));
	nombresSonidos.insert(std::pair<string,string>("MarioPisaKoopa","resources/Musica/EfectosSonido/MarioPisaKoopa.wav"));

	string nombreArchivo;
	Mix_Chunk* efecto =nullptr;

	for (const auto& elemento : nombresSonidos) {
		nombreArchivo = elemento.second;
		efecto = Mix_LoadWAV(nombreArchivo.c_str());
		if(efecto == NULL){
			Log::getInstance()->huboUnError("Hubo un error al intentar cargar el efecto especial en la direccion "+ nombreArchivo);
		}else{
			efectosDeSonido.insert(std::pair<string,Mix_Chunk*>(elemento.first ,efecto));
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
    estadoMusica->reproducir(nombreCancion);
}

void ReproductorMusica::ponerMusica(string nombreCancion){
    Mix_Music* cancion = NULL;

    if (cancionReproduciendose == nullptr){

        cancion = Mix_LoadMUS( nombreCancion.c_str());
        if( cancion == NULL ){
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

        if( cancion == NULL ){
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

void ReproductorMusica::ReproducirSonidoSalto(){
	estadoSonidos->reproducir("EfectoSalto");
}

void ReproductorMusica::ReproducirSonidoAgarrarMoneda(){
	estadoSonidos->reproducir("AgarrarMoneda");
}
void ReproductorMusica::ReproducirSonidoInicioJuego(){
	estadoSonidos->reproducir("InicioJuego");
}

void ReproductorMusica::ReproducirSonidoSumarVida(){
	estadoSonidos->reproducir("SumarVida");
}

void ReproductorMusica::ReproducirSonidoRomperBloque(){
	estadoSonidos->reproducir("RomperBloque");
}

void ReproductorMusica::ReproducirSonidoMarioMataGoomba(){
	estadoSonidos->reproducir("MarioMataGoomba");
}

void ReproductorMusica::ReproducirSonidoMarioChicoGolpeaLadrillo(){
	estadoSonidos->reproducir("MarioChicoGolpeaLadrillo");
}

void ReproductorMusica::ReproducirSonidoMarioLanzaFuego(){
    estadoSonidos->reproducir("MarioLanzaFuego");
}

void ReproductorMusica::ReproducirSonidoBandera(){
	estadoSonidos->reproducir("SonidoBandera");
}

void ReproductorMusica::ReproducirSonidoAparecePlanta(){
	estadoSonidos->reproducir("AparecePlanta");
}

void ReproductorMusica::ReproducirSonidoMarioAgarraHongo(){
    estadoSonidos->reproducir("MarioAgarraHongo");
}

void ReproductorMusica::ReproducirSonidoApareceHongo(){
	estadoSonidos->reproducir("ApareceHongo");
}

void ReproductorMusica::ReproducirSonidoMarioPisaKoopa(){
    estadoSonidos->reproducir("MarioPisaKoopa");
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

void ReproductorMusica::reproducirSonido(string tipoSonido) {
    Mix_Chunk* efecto = efectosDeSonido.at(tipoSonido);
    Mix_PlayChannel( -1, efecto, 0 );
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





