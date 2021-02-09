#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCONEXIONCLIENTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCONEXIONCLIENTE_HPP

#include <map>
#include <queue>
#include "src/Utils/Enviador.hpp"
#include "src/Server/Servidor/ConexionCliente.hpp"

class EnviadorConexionCliente : public Thread{

    public:
        EnviadorConexionCliente(Socket* socket,ConexionCliente* cliente);
        ~EnviadorConexionCliente() override;
        void ejecutar()override;
        void agregarMensajeAEnviar(char caracter,void* mensaje);

    private:
        ConexionCliente* cliente;
        std::queue<char> identificadoresMensajeAEnviar;
        std::map<char,Enviador*> enviadores;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCONEXIONCLIENTE_HPP
