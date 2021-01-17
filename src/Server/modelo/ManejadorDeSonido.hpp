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
        std::map<std::string, std::string> mapaSonidoColisionPorDerecha;
        std::map<std::string, std::string> mapaSonidoColisionPorIzquierda;
        std::map<std::string, std::string> mapaSonidoColisionPorArriba;
        std::map<std::string, std::string> mapaSonidoColisionPorAbajo;
        void agregarSonido(std::map<std::string, std::string> mapaSonido, std::string id_colision);
        int id = 0;
};
#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MANEJADORDESONIDO_HPP
