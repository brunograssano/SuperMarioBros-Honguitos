#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOSONIDOS_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOSONIDOS_HPP

#include <string>
#include <SDL_mixer.h>

using namespace std;

class EstadoSonidos {
    public:
        virtual ~EstadoSonidos()= default;
        virtual EstadoSonidos* cambiar() = 0;
        virtual void reproducir(Mix_Chunk* efecto) = 0;
};

class SuenanSonidos : public EstadoSonidos{
    public:
        EstadoSonidos* cambiar() override;
        void reproducir(Mix_Chunk* efecto) override;
};

class SonidosMuteados : public EstadoSonidos{
    public:
        EstadoSonidos* cambiar() override;
        void reproducir(Mix_Chunk* efecto) override;
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOSONIDOS_HPP
