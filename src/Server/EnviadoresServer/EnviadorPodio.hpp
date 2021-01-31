

#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORPODIO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORPODIO_HPP


#include "../../Utils/Enviador.hpp"

class EnviadorPodio: public Enviador{

public:
    explicit EnviadorPodio(int socket);
    void enviar()override;
    void dejarInformacion(void* informacionPodio)override;
private:
    ultimos_podios_t ultimos_podios{};
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORPODIO_HPP
