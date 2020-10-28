#include "ReproductorMusica.hpp"
#include <string>

ReproductorMusica* ReproductorMusica::reproductor = nullptr;

ReproductorMusica::ReproductorMusica(){
	if((Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)){
		Log::getInstance()->huboUnErrorSDL("Hubo un fallo al inicializar el reproductor de musica", Mix_GetError());
	}
	map<string,string> nombresSonidos;
	nombresSonidos.insert(std::pair<string,string>("EfectoSalto","resources/Musica/EfectosSonido/EfectoSalto.wav"));
	nombresSonidos.insert(std::pair<string,string>("AgarrarMoneda","resources/Musica/EfectosSonido/AgarrarMoneda.wav"));

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
}

ReproductorMusica* ReproductorMusica::getInstance(){
	if(reproductor==nullptr){
		reproductor= new ReproductorMusica();
	}
	return reproductor;
}

void ReproductorMusica::ReproducirMusicaNivel(string nombreCancion){
	Mix_Music* cancion = NULL;

	if (cancionReproduciendose == nullptr){

		cancion = Mix_LoadMUS( nombreCancion.c_str());
		if( cancion == NULL ){
			Log::getInstance()->huboUnErrorSDL("Hubo un fallo al intentar cargar la musica en la direccion "+ nombreCancion, Mix_GetError());
		}else{
			cancionReproduciendose = cancion;
			Mix_PlayMusic( cancion, -1 );
			Log::getInstance()->mostrarMensajeDeInfo("Se reproduce la cancion de la direccion: "+nombreCancion);
		}

	}else{

		Mix_Music* cancionABorrar = cancionReproduciendose;
		cancion = Mix_LoadMUS( nombreCancion.c_str());

		if( cancion == NULL ){
			Log::getInstance()->huboUnErrorSDL("Hubo un fallo al intentar cargar la musica en la direccion "+ nombreCancion, Mix_GetError());
		}else{
			cancionReproduciendose = cancion;
			Mix_PlayMusic( cancion, -1 );
			Log::getInstance()->mostrarMensajeDeInfo("Se reproduce la cancion de la direccion: "+nombreCancion);
			Mix_FreeMusic(cancionABorrar);
		}
	}
}

void ReproductorMusica::ReproducirSonidoSalto(){
	Mix_Chunk* efecto = efectosDeSonido.at("EfectoSalto");
	Mix_PlayChannel( -1, efecto, 0 );
}

void ReproductorMusica::ReproducirSonidoAgarrarMoneda(){
	Mix_Chunk* efecto = efectosDeSonido.at("AgarrarMoneda");
	Mix_PlayChannel( -1, efecto, 0 );
}

ReproductorMusica::~ReproductorMusica(){
	Log::getInstance()->mostrarMensajeDeInfo("Se cierra el reproductor de musica");
	Mix_FreeMusic(cancionReproduciendose);
	for (const auto& elemento : efectosDeSonido) {
		Mix_FreeChunk(elemento.second);
	}
	Mix_Quit();

}




