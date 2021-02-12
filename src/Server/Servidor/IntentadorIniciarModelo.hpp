#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_INTENTADORINICIARMODELO_H
#define TP_TALLER_DE_PROGRAMACION_FIUBA_INTENTADORINICIARMODELO_H

#include "src/Server/Modelo/AplicacionServidor.hpp"
#include "src/Utils/Thread.hpp"
#include "ConexionCliente.hpp"


class IntentadorIniciarModelo : public Thread{

    public:
        IntentadorIniciarModelo(unsigned int cantidadConexiones, AplicacionServidor* aplicacionServidor,
                                std::map<int,ConexionCliente*>* mapaClientesJugando,
                                std::map<int,std::string> *mapaIDNombre);
        void ejecutar() override;

    private:
        AplicacionServidor* aplicacionServidor{};
        std::map<int,ConexionCliente*>* mapaClientesJugando;
        std::map<int,std::string> *mapaIDNombre;
        const unsigned int cantidadConexiones;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_INTENTADORINICIARMODELO_H
