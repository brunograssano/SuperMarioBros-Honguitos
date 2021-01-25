#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_PISO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_PISO_HPP

#include "Pozo.hpp"
#include "Plataforma.hpp"
#include "src/Server/Modelo/Juego/Posiciones/Posicion.hpp"
#include "src/Server/Modelo/Juego/Colisionable.hpp"

class Piso {

    public:
        explicit Piso(int altoPiso);
        void inicializar();
        ~Piso();
        void agregarPozo(int posicionPozo, int tipoPozo, int fondo);
        list<Colisionable*> obtenerPiso();
        list<pozo_t> serializar();
        int obtenerAltura() const;
        bool obtenerRespawn(rectangulo_t rectangulo, Posicion* posicion);

private:
        int alto;
        list<Pozo> pozos;
        list<Colisionable*> plataformas;
        bool obtenerXRespawn(rectangulo_t rectangulo, int* x);
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_PISO_HPP
