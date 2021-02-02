#include "OcultadorDeTexto.hpp"

std::string OcultadorDeTextoAstericos::ocultar(std::string texto) {
    return std::string(texto.length(), '*');
}

std::string OcultadorDeTextoNulo::ocultar(std::string texto) {
    return texto;
}
