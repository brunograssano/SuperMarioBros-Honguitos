#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCONEXIONCLIENTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCONEXIONCLIENTE_HPP

#include <map>
#include "src/Utils/Thread.hpp"
#include "src/Utils/Socket.hpp"
#include "src/Server/Servidor/ConexionCliente.hpp"
#include "src/Server/Servidor/ConexionCliente.hpp"
#include "src/Utils/Escuchador.hpp"

class EscuchadorConexionCliente : public Thread{
    public:
        EscuchadorConexionCliente(Socket* socket,ConexionCliente* cliente);
        ~EscuchadorConexionCliente() override;
        void ejecutar()override;
        void agregarEscuchadorEntrada(int IDjugador,Servidor* servidor);
    private:
        ConexionCliente* cliente;
        std::map<char,Escuchador*> escuchadores;
        Socket* socket;
        int idJugador;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCONEXIONCLIENTE_HPP
