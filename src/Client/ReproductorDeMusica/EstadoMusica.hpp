#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOMUSICA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOMUSICA_HPP

#include <string>
using namespace std;

class EstadoMusica {
    public:
        virtual ~EstadoMusica()= default;
        virtual EstadoMusica* cambiar() = 0;
        virtual void reproducir(string nombreCancion) = 0;

    protected:
        string cancionAReproducir;
        string cancionQueSeReproduce;
};

class Suena : public EstadoMusica{
    public:
        Suena()= default;
        Suena(string cancionAReproducir,string cancionQueSeReproduce);
        EstadoMusica* cambiar() override;
        void reproducir(string nombreCancion) override;
};

class Muteada : public EstadoMusica{
    public:
        Muteada(string cancionAReproducir,string cancionQueSeReproduce);
        EstadoMusica* cambiar() override;
        void reproducir(string nombreCancion) override;
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOMUSICA_HPP
