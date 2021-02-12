
#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_DIBUJADORCREDITOS_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_DIBUJADORCREDITOS_HPP

#include "src/Client/App/CargadorTexturas.hpp"
#include "src/Client/App/JuegoCliente/JuegoCliente.hpp"
#include "src/Client/App/Dibujadores/Dibujador.hpp"

class DibujadorCreditos : public Dibujador{
    public:
        DibujadorCreditos(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla);
        void dibujar() override;
        ~DibujadorCreditos()= default;;
    private:
        int alto_pantalla;
        int ancho_pantalla;
        CargadorTexturas* cargadorTexturas;
        SDL_Renderer* renderizador;
        void dibujarRectanguloCreditos();
        void dibujarTexto();
        int ciclosDibujado = 0;
        int xRectanguloTransparente;
        int yRectanguloTransparente;
        int anchoRectanguloTransparente;
        int altoRectanguloTransparente;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_DIBUJADORCREDITOS_HPP
