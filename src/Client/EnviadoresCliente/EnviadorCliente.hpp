#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCLIENTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCLIENTE_HPP

class Cliente;
#include "../Cliente.hpp"
#include "src/Utils/Enviador.hpp"
#include "src/Utils/Thread.hpp"
#include "src/Utils/ColaBloqueante.hpp"

class EnviadorCliente  : public Thread{
    public:
        EnviadorCliente(Socket* socketCliente,Cliente* cliente);
        ~EnviadorCliente() override;
        void ejecutar()override;
        void agregarMensajeAEnviar(char tipoMensaje, void *mensaje);
        bool terminoDeEnviar();

    private:
        Cliente* cliente;
        BlockingQueue<char> identificadoresMensajeAEnviar;
        std::map<char,Enviador*> enviadores;
        bool terminoEnviar;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCLIENTE_HPP
