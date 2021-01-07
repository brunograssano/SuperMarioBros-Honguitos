#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCLIENTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCLIENTE_HPP

class Cliente;
#include "../Cliente.hpp"
#include "../../Utils/Enviador.hpp"

class EnviadorCliente {
    public:
        EnviadorCliente(int socketCliente,Cliente* cliente,bool* terminoJuego,bool* terminoEnviar);
        ~EnviadorCliente();
        void enviar();
        void agregarMensajeAEnviar(char tipoMensaje, void *mensaje);

    private:
        Cliente* cliente;
        queue<char> identificadoresMensajeAEnviar;
        map<char,Enviador*> enviadores;

        bool* terminoJuego;
        bool* terminoEnviar;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCLIENTE_HPP
