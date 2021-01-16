
#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORINFOFINJUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORINFOFINJUEGO_HPP


#include <src/Utils/Enviador.hpp>

class EnviadorInfoFinJuego : public Enviador{
public:
    explicit EnviadorInfoFinJuego(int socket);
    void enviar()override;
    void dejarInformacion(void* informacion)override;
private:
    info_fin_juego_t infoFinJuego;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORINFOFINJUEGO_HPP
