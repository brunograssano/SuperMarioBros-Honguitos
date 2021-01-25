#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MANEJADORENTRADA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MANEJADORENTRADA_HPP

#include <SDL.h>
#include <string>
#include "BotonConTexto.hpp"

using namespace std;

class ManejadorEntrada{
    public:
        bool manejarEntrada(SDL_Event evento, bool* terminar, string* textoIngresadoUsuario, string* textoIngresadoContrasenia, string** entradaUsuario, BotonConTexto* cajaTextoUsuario, BotonConTexto* cajaTextoContrasenia, BotonConTexto* botonEnviar);
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MANEJADORENTRADA_HPP
