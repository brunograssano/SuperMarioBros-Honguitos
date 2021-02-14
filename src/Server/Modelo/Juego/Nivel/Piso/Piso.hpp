#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_PISO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_PISO_HPP

#include <list>
#include "Pozo.hpp"
#include "src/Server/Modelo/Juego/Posiciones/Posicion.hpp"
#include "src/Server/Modelo/Juego/Colisionable.hpp"
#include "src/Utils/Utils.hpp"

class Piso {

    public:
        explicit Piso(int altoPiso);
        void inicializar();
        ~Piso();
        void agregarPozo(int posicionPozo, int tipoPozo, int fondo);
        std::list<Colisionable*> obtenerPiso();
        std::list<entidad_t> serializar();
        int obtenerAltura() const;
        bool obtenerRespawn(rectangulo_t rectangulo, Posicion* posicion);

    private:
        int alto;
        std::list<Pozo> pozos;
        std::list<Colisionable*> plataformas;
        bool obtenerXRespawn(rectangulo_t rectangulo, int* x);
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_PISO_HPP
