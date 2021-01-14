#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_PISO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_PISO_HPP

#include "src/Server/modelo/Bloques/Pozo.hpp"
#include "Colisionable.hpp"

class Piso {

    public:
        Piso(int altoPiso);
        void inicializar();
        ~Piso();
        void agregarPozo(int posicionPozo,int tipoPozo);
        list<Colisionable*> obtenerPiso();
        list<pozo_t> serializar();

    private:
        int alto;
        list<Pozo> pozos;
        list<Colisionable*> plataformas;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_PISO_HPP
