#include <stdexcept>
#include "ManejadorEntrada.hpp"

bool ManejadorEntrada::manejarEntrada(SDL_Event evento, bool* terminar, string* textoIngresadoUsuario, string* textoIngresadoContrasenia, string** entradaUsuario, BotonConTexto* cajaTextoUsuario, BotonConTexto* cajaTextoContrasenia, BotonConTexto* botonEnviar){
    while( SDL_PollEvent( &evento ) != 0 ){
        if( evento.type == SDL_QUIT ){
            (*terminar) = true;
            throw runtime_error("CerroVentanaDeInicio");
        }
        else if(( evento.type == SDL_KEYDOWN )||(evento.type == SDL_MOUSEBUTTONDOWN)){
            if( evento.key.keysym.sym == SDLK_BACKSPACE && (**entradaUsuario).length() > 0 ){
                (**entradaUsuario).pop_back();
            }
            else if(cajaTextoContrasenia->botonClickeado(evento) || evento.key.keysym.sym == SDLK_DOWN){
                (*entradaUsuario) = textoIngresadoContrasenia;
                cajaTextoContrasenia->seleccionarCajaTexto();
                cajaTextoUsuario->deseleccionarCajaTexto();
            }
            else if(cajaTextoUsuario->botonClickeado(evento) || evento.key.keysym.sym == SDLK_UP){
                (*entradaUsuario) = textoIngresadoUsuario;
                cajaTextoUsuario->seleccionarCajaTexto();
                cajaTextoContrasenia->deseleccionarCajaTexto();
            }
            else if(botonEnviar->botonClickeado(evento) || evento.key.keysym.sym == SDLK_RETURN){
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