#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MANEJADORDESONIDO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MANEJADORDESONIDO_HPP

#include <string>
#include <map>

class ManejadorDeSonido{
    public:
        void reproducirSonidoIzquierda(std::string id_colision);
        void reproducirSonidoDerecha(std::string id_colision);
        void reproducirSonidoArriba(std::string id_colision);
        void reproducirSonidoAbajo(std::string id_colision);

    protected:
        std::map<std::string, uint8_t> mapaSonidoColisionPorDerecha;
        std::map<std::string, uint8_t> mapaSonidoColisionPorIzquierda;
        std::map<std::string, uint8_t> mapaSonidoColisionPorArriba;
        std::map<std::string, uint8_t> mapaSonidoColisionPorAbajo;
        void agregarSonido(std::map<std::string, uint8_t> mapaSonido, std::string id_colision);
        int id = 0;
};
#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MANEJADORDESONIDO_HPP
