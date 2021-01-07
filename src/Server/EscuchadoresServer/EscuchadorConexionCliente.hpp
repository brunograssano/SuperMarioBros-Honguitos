#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCONEXIONCLIENTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCONEXIONCLIENTE_HPP

#include "../ConexionCliente.hpp"
#include "../../Utils/Escuchador.hpp"

class EscuchadorConexionCliente {
    public:
        EscuchadorConexionCliente(int socket,bool* terminoJuego,ConexionCliente* cliente,Servidor* servidor);
        ~EscuchadorConexionCliente();
        void escuchar();
        void agregarEscuchadorEntrada(int IDjugador);
    private:
        Servidor* servidor;
        ConexionCliente* cliente;
        map<char,Escuchador*> escuchadores;
        int socket;
        bool* terminoJuego;
        int idJugador;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCONEXIONCLIENTE_HPP
