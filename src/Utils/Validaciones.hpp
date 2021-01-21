#ifndef SRC_UTILS_VALIDACIONES_HPP_
#define SRC_UTILS_VALIDACIONES_HPP_

#include "../Utils/log/TipoLog.hpp"
#define LARGO_IP 20
#define LARGO_ENTRADA 150

void manejarEntrada(int argc, char* args[], char ipEntrada[LARGO_IP], char puertoEntrada[LARGO_IP], char nivelLogEntrada[LARGO_ENTRADA]);

void manejarEntrada(int cantidadArgumentos, char* argumentos[],char direccionLecturaComando[LARGO_ENTRADA],char nivelLogEntrada[LARGO_ENTRADA],
					char ipEntrada[LARGO_IP],char puertoEntrada[LARGO_IP]);

TipoLog* determinarNivelLog(char nivelLogEntrada[LARGO_ENTRADA]);

void validarPuertoEIp(char ipEntrada[LARGO_IP], char puertoEntrada[LARGO_IP], char ip[LARGO_IP], int* puerto);

void mostrarAyuda();

#endif /* SRC_UTILS_VALIDACIONES_HPP_ */
