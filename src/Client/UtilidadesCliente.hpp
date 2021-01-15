#ifndef SRC_CLIENT_UTILIDADESCLIENTE_HPP_
#define SRC_CLIENT_UTILIDADESCLIENTE_HPP_

#include "../Utils/Constantes.hpp"


int conectarAlServidor(char ip[LARGO_IP], int puerto);

void cerrarSocketCliente(int socketCliente);

#endif /* SRC_CLIENT_UTILIDADESCLIENTE_HPP_ */
