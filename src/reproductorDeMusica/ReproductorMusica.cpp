#include "ReproductorMusica.hpp"

ReproductorMusica* ReproductorMusica::reproductor = nullptr;

ReproductorMusica* ReproductorMusica::getInstance(){
	if(reproductor==nullptr){
		reproductor= new ReproductorMusica();
	}
	return reproductor;
}

void ReproductorMusica::ReproducirMusicaNivel(string nombreCancion){
	//The music that will be played
	Mix_Music *gMusic = NULL;

	gMusic = Mix_LoadMUS( nombreCancion.c_str());
	if( gMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );

	}
	//If there is no music playing
	if( Mix_PlayingMusic() == 0 )
	{
		//Play the music
		Mix_PlayMusic( gMusic, -1 );
	}
	//If music is being played
	else
	{
		//If the music is paused
		if( Mix_PausedMusic() == 1 )
		{
			//Resume the music
			Mix_ResumeMusic();
		}
		//If the music is playing
		else
		{
			//Pause the music
			Mix_PauseMusic();
		}
	}
}

void ReproductorMusica::ReproducirSonidoSalto(){
	Mix_Chunk* gScratch = NULL;
	string nombreArchivo ="resources/Musica/EfectoSalto.wav";
	gScratch = Mix_LoadWAV(nombreArchivo.c_str());
	Mix_PlayChannel( -1, gScratch, 0 );
}




