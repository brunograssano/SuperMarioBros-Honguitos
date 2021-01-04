#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOMUSICA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOMUSICA_HPP

#include <string>
using namespace std;

class EstadoMusica {
    public:
        virtual ~EstadoMusica(){};
        virtual EstadoMusica* cambiar();
        virtual void reproducir(string nombreCancion){};
};

class Suena : public EstadoMusica{
    public:
        EstadoMusica* cambiar();
        void reproducir(string nombreCancion) override;

};

class Muteada : public EstadoMusica{
    public:
        EstadoMusica* cambiar();
        void reproducir(string nombreCancion) override;
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOMUSICA_HPP
