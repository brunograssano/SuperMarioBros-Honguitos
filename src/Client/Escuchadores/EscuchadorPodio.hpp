
#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORPODIO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORPODIO_HPP



#include "../Cliente.hpp"
#include "src/Utils/Escuchador.hpp"

class EscuchadorPodio : public Escuchador{

public:
    EscuchadorPodio(int socketCliente, Cliente* cliente);
    void casoError(int resultado)override;
    void casoSocketCerrado()override;
    void casoExitoso()override;
private:
    std::string error;
    ultimos_podios_t ultimos_podios{};
    Cliente* cliente;
};



#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORPODIO_HPP
