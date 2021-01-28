#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCONEXIONCLIENTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCONEXIONCLIENTE_HPP

#include <map>
#include "src/Server/Servidor/ConexionCliente.hpp"
#include "src/Utils/Thread.hpp"
#include "../../Utils/Escuchador.hpp"

class EscuchadorConexionCliente : public Thread{
    public:
        EscuchadorConexionCliente(int socket,ConexionCliente* cliente);
        ~EscuchadorConexionCliente() override;
        void ejecutar()override;
        void agregarEscuchadorEntrada(int IDjugador,Servidor* servidor);
    private:
        ConexionCliente* cliente;
        std::map<char,Escuchador*> escuchadores;
        int socket;
        int idJugador;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCONEXIONCLIENTE_HPP
