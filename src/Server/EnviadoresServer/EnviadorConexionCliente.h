#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCONEXIONCLIENTE_H
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCONEXIONCLIENTE_H

#include <map>
#include <queue>
#include "src/Utils/Enviador.hpp"

class EnviadorConexionCliente {

    public:
        EnviadorConexionCliente(int socket,bool* terminoElJuego);
        ~EnviadorConexionCliente();
        void enviar();
        void agregarMensajeAEnviar(char caracter,void* mensaje);

    private:
        bool* terminoJuego;
        queue<char> identificadoresMensajeAEnviar;
        map<char,Enviador*> enviadores;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORCONEXIONCLIENTE_H
