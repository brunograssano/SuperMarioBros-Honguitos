#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCLIENTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCLIENTE_HPP

#include "../Cliente.hpp"
#include "src/Utils/Escuchador.hpp"
#include "src/Utils/Thread.hpp"

class EscuchadorCliente : public Thread{
    public:
        EscuchadorCliente(Socket* socket, Cliente* cliente);
        ~EscuchadorCliente() override;
        void ejecutar()override;
        bool terminoDeEscuchar() const;

    private:
        Cliente* cliente{};
        bool terminoEscuchar;
        Socket* socketCliente;
        std::map<char,Escuchador*> escuchadores;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCLIENTE_HPP
