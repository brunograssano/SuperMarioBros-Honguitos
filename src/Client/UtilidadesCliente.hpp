#ifndef SRC_CLIENT_UTILIDADESCLIENTE_HPP_
#define SRC_CLIENT_UTILIDADESCLIENTE_HPP_

#include "src/Utils/Constantes.hpp"
#include "src/Utils/Socket.hpp"

Socket conectarAlServidor(char ip[LARGO_IP], int puerto);

#endif /* SRC_CLIENT_UTILIDADESCLIENTE_HPP_ */
