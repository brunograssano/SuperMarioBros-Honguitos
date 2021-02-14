#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOMUSICA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOMUSICA_HPP

#include <string>

class EstadoMusica {
    public:
        virtual ~EstadoMusica()= default;
        virtual EstadoMusica* cambiar() = 0;
        virtual void reproducir(std::string nombreCancion) = 0;

    protected:
        std::string cancionAReproducir;
        std::string cancionQueSeReproduce;
};

class Suena : public EstadoMusica{
    public:
        Suena()= default;
        Suena(std::string cancionAReproducir,std::string cancionQueSeReproduce);
        EstadoMusica* cambiar() override;
        void reproducir(std::string nombreCancion) override;
};

class Muteada : public EstadoMusica{
    public:
        Muteada(std::string cancionAReproducir,std::string cancionQueSeReproduce);
        EstadoMusica* cambiar() override;
        void reproducir(std::string nombreCancion) override;
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOMUSICA_HPP
