#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCONEXIONCLIENTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCONEXIONCLIENTE_HPP

#include <map>
#include <queue>
#include "src/Utils/Enviador.hpp"
#include "../ConexionCliente.hpp"

class EnviadorConexionCliente {

    public:
        EnviadorConexionCliente(int socket,ConexionCliente* cliente);
        ~EnviadorConexionCliente();
        void enviar();
        void agregarMensajeAEnviar(char caracter,void* mensaje);

    private:
        ConexionCliente* cliente;
        queue<char> identificadoresMensajeAEnviar;
        map<char,Enviador*> enviadores;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCONEXIONCLIENTE_HPP
