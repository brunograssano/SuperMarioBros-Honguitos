#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCLIENTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORCLIENTE_HPP

#include <map>
#include "src/Utils/Thread.hpp"
#include "src/Utils/Socket.hpp"
#include "src/Utils/Escuchador.hpp"
#include "src/Client/Cliente.hpp"

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
