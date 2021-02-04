#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCLIENTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCLIENTE_HPP

class Cliente;
#include "../Cliente.hpp"
#include "src/Utils/Enviador.hpp"
#include "src/Utils/Thread.hpp"

class EnviadorCliente  : public Thread{
    public:
        EnviadorCliente(int socketCliente,Cliente* cliente,bool* terminoJuego,bool* terminoEnviar);
        ~EnviadorCliente() override;
        void ejecutar()override;
        void agregarMensajeAEnviar(char tipoMensaje, void *mensaje);

    private:
        Cliente* cliente;
        std::queue<char> identificadoresMensajeAEnviar;
        std::map<char,Enviador*> enviadores;

        bool* terminoJuego;
        bool* terminoEnviar;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCLIENTE_HPP
