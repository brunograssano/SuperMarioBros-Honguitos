#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MANEJADORENTRADA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MANEJADORENTRADA_HPP

#include <SDL.h>
#include <string>
#include "BotonConTexto.hpp"

class ManejadorEntrada{
    public:
        static bool manejarEntrada(SDL_Event evento, bool* terminar, std::string* textoIngresadoUsuario, std::string* textoIngresadoContrasenia, std::string** entradaUsuario, BotonConTexto* cajaTextoUsuario, BotonConTexto* cajaTextoContrasenia, BotonConTexto* botonEnviar);
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MANEJADORENTRADA_HPP
