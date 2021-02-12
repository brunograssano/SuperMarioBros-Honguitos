#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_CAMARA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_CAMARA_HPP

#include "src/Server/Modelo/Juego/Mario/Mario.hpp"

class Camara {

    public:
        Camara(int alto_pantalla, int ancho_pantalla);
        ~Camara() = default;
        void reiniciar();
        void moverCamara(const std::map<int,Mario*>& jugadores);
        static bool estaEnRangoHelper(void* ptr, rectangulo_t rect);
        bool estaEnRangoVisible(rectangulo_t rect) const;
        rectangulo_t obtenerRectanguloCamara();
    private:
        rectangulo_t rectanguloCamara{};
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_CAMARA_HPP
