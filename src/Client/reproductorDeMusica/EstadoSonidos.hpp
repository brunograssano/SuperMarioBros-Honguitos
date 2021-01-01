#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOSONIDOS_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOSONIDOS_HPP

#include <string>
using namespace std;

class EstadoSonidos {
    public:
        virtual ~EstadoSonidos(){};
        virtual EstadoSonidos* cambiar(){};
        virtual void reproducir(string sonidoAReproducir){ };
};

class SuenanSonidos : public EstadoSonidos{
    public:
        EstadoSonidos* cambiar();
        void reproducir(string sonidoAReproducir) override;
};

class SonidosMuteados : public EstadoSonidos{
    public:
        EstadoSonidos* cambiar();
        void reproducir(string sonidoAReproducir) override;
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOSONIDOS_HPP
