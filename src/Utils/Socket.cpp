#include "Socket.hpp"
#include "log/Log.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>
#include <unistd.h>

Socket::Socket(const int socket,sockaddr_in addressDelCliente) {
    this->socket = socket;
    this->address = addressDelCliente;
}

void Socket::obtenerSocket() {
    socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socket <= 0){
        throw std::runtime_error("No se pudo crear el socket");
    }
}

void Socket::setSockopt() const {
    int opt = 1;
    if(::setsockopt(socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))<0){
        throw std::runtime_error("Ocurrio un error al hacer el setsockopt");
    }
}

void Socket::bind() const {
    if (::bind(socket,(struct sockaddr*)&address,sizeof(address))<0) {
        throw std::runtime_error("No se pudo realizar el bind del socket");
    }
}

void Socket::listen(const int maximaCantidadDeClientesEnCola) const {
    if (::listen(socket, maximaCantidadDeClientesEnCola)) {
        throw std::runtime_error("No se pudo realizar el listen del socket");
    }
}

void Socket::convertirFormatoANetwok(const char *ip, const int puerto) {
    address.sin_port = ::htons(puerto);
    if(::inet_pton(address.sin_family, ip,(void*) &address.sin_addr) <= 0){
        throw std::runtime_error("Dirección inválida / Dirección no soportada: Abortamos.");
    }
}

Socket::Socket() {
    socket = -1;
}

Socket::Socket(const char *ip, const int puerto) {
    obtenerSocket();
    memset(&address,0,sizeof(sockaddr_in));
    address.sin_family = AF_INET;

    convertirFormatoANetwok(ip, puerto);

    if (connect(socket, (struct sockaddr *)&address, sizeof(address)) < 0){
        throw std::runtime_error("Falló la conexión al servidor. Abortamos.-------"+std::to_string(errno));
    }

    std::cout<<"Se establecio la conexion con el servidor"<<std::endl;
}

Socket::Socket(const char *ip, const int puerto, const int maximaCantidadDeClientesEnCola) {
    obtenerSocket();
    setSockopt();

    memset(&address,0,sizeof(sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;

    /*Seteamos la ip y el puerto donde estara alojado el servidor*/
    convertirFormatoANetwok(ip, puerto);

    /* Enlazamos el socket acpetador del servidor a la dirección puerto */
    bind();

    /* Hacemos que el socket sea para escuchar */
    listen(maximaCantidadDeClientesEnCola);

    std::cout<< "Se inicio el servidor"<<std::endl;
}

Socket::Socket(Socket &&otroSocket) noexcept {
    this->socket = otroSocket.socket;
    this->address = otroSocket.address;
    otroSocket.socket = -1;
}

Socket &Socket::operator=(Socket &&otroSocket) noexcept {
    this->socket = otroSocket.socket;
    this->address = otroSocket.address;
    otroSocket.socket = -1;
    return *this;
}

Socket Socket::accept() const {
    if (socket<0) {
        throw std::runtime_error("El socket del servidor no es valido, no se pueden aceptar conexiones");
    }
    socklen_t addressStructure = 0;
    struct sockaddr_in addressCliente{};
    int socketCliente = ::accept(socket, (struct sockaddr *) &addressCliente, &addressStructure);
    if (socketCliente < 0) {
        throw std::runtime_error("Error al aceptar la conexion de un cliente");
    }
    return Socket(socketCliente,addressCliente);
}

int Socket::enviar(void* buffer, const unsigned int bytes) const {
    return ::send(socket, buffer, bytes, 0);
}

int Socket::escuchar(void* buffer, const unsigned int bytes) const {
    return ::recv(socket, buffer, bytes, MSG_WAITALL);
}

void Socket::cerrarSocket() {
    if (socket>=0) {
        ::close(socket);
        socket = -1;
    }
}

void Socket::shutdown(const int canalACerrar) const {
    if (socket>=0) {
        int resultado = ::shutdown(socket, canalACerrar);
        if(resultado<0) {
            Log::getInstance()->huboUnErrorSDL("No se cerro correctamente el socket del servidor",std::to_string(errno));
        }
    }
}

std::string Socket::obtenerIP() const {
    return (std::string) (inet_ntoa(address.sin_addr));
}

void Socket::cerrar() {
    shutdown();
    cerrarSocket();
}

Socket::~Socket() {
    shutdown();
    cerrarSocket();
}