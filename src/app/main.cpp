#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include "App.h"

int main( int argc, char* args[] ){

	App* aplicacion = App::GetInstance();
	bool salir = false;
	SDL_Event evento;


	while(!salir){
		while( SDL_PollEvent( &evento ) != 0 ){
			if( evento.type == SDL_QUIT ){
				salir = true;
			}else{
				aplicacion->actualizar(evento);
			}
		}
		aplicacion->actualizar();
		aplicacion->dibujar();
	}

	delete aplicacion;
	return 0;

}
