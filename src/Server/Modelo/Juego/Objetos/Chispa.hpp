#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_CHISPA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_CHISPA_HPP


#include "src/Server/Modelo/Juego/Posiciones/PosicionFija.hpp"
#include "src/Server/Modelo/Juego/Sprites/SpriteChispa.hpp"
#include "src/Utils/Utils.hpp"
#include "ObjetoFugaz.hpp"

class Chispa : public ObjetoFugaz{
    const int CICLOS_PARA_DESAPARECER = 20;
    public:
        explicit Chispa(const Posicion& posicionInicial, int direccion);
        void actualizar() override;
        entidad_t serializar() override;
        int obtenerPosicionX() override;
        bool debeDesaparecer() override;
        int tipoDeEfecto() override;
        ~Chispa() override;

        std::string obtenerColisionID() override;
        rectangulo_t obtenerRectangulo() override;
        bool debeColisionar() override;

    private:
        void inicializarMapasDeColision() override;
        int ciclos = 0;
        PosicionFija* posicion;
        SpriteChispa* sprite;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_CHISPA_HPP
