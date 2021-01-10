#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCLIENTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCLIENTE_HPP

#include "../Cliente.hpp"
#include "src/Utils/Escuchador.hpp"
#include "src/Utils/Thread.hpp"

class EscuchadorCliente : public Thread{
    public:
        EscuchadorCliente(int socketCliente,Cliente* cliente,bool* terminoJuego,bool* terminoEscuchar);
        ~EscuchadorCliente();
        void ejecutar()override;

    private:
        Cliente* cliente{};
        bool* terminoEscuchar;
        bool* terminoJuego;
        int socketCliente;
        map<char,Escuchador*> escuchadores;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCLIENTE_HPP
