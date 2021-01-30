#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SOCKET_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SOCKET_HPP

#include <netdb.h>
#include <string>

class Socket {

    private:

        int socket{};
        sockaddr_in address{};
        /**
         * Crea una instancia de socket que se usa en el Servidor para comunicarse con el cliente
         */
        explicit Socket(int socket,sockaddr_in addressDelCliente);

        /**
         * Obtiene el socket que se va a usar.
         */
        void obtenerSocket();
        void setSockopt() const;
        void bind() const;
        void listen(int maximaCantidadDeClientesEnCola) const;
        void cerrarSocket();

    public:
        /**
         * Para el constructor por movimiento.
         */
        Socket();

        /**
         * El constructor del socket del cliente.
         */
        Socket(const char* ip, int puerto);

        /**
         * El constructor del socket del servidor.
         */
        Socket(const char* ip, int puerto, int maximaCantidadDeClientesEnCola);

        /**
         * Elimina el constructor por copia
         */
        Socket(const Socket&) = delete;
        Socket& operator=(const Socket&) = delete;

        /**
         * Se usa el constructor por movimiento
         */
        Socket(Socket&& otroSocket) noexcept ;
        Socket& operator=(Socket&& otroSocket) noexcept ;

        /**
         * Acepta la conexión de un cliente, en caso de fallo lanza excepcion
         */
        Socket accept() const;
        std::string obtenerIP() const;
        int enviar(void* buffer, unsigned int bytes) const;
        int escuchar(void* buffer, unsigned int bytes) const;
        void shutdown(int canalACerrar = SHUT_RDWR) const;
        void cerrar();
        ~Socket();

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SOCKET_HPP
