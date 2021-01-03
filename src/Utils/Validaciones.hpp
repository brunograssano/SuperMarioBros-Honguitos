#ifndef SRC_UTILS_VALIDACIONES_HPP_
#define SRC_UTILS_VALIDACIONES_HPP_

#include <getopt.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>

#include "../Utils/log/Debug.hpp"
#include "../Utils/log/Error.hpp"
#include "../Utils/log/Info.hpp"
#include "../Utils/log/Log.hpp"

#define LARGO_IP 20
#define LARGO_ENTRADA 150
#define VALOR_MAXIMO_PUERTO 65535
#define VALOR_MINIMO_PUERTO 1023
const int TERMINO = -1;

#define SERVER 's'
#define CONFIG 'c'
#define IP 'i'
#define PUERTO 'p'
#define LOG 'l'
#define TEST 't'
#define AYUDA 'h'

void manejarEntrada(int argc, char* args[], char ipEntrada[LARGO_IP], char puertoEntrada[LARGO_IP], char nivelLogEntrada[LARGO_ENTRADA]);

void manejarEntrada(int cantidadArgumentos, char* argumentos[],char direccionLecturaComando[LARGO_ENTRADA],char nivelLogEntrada[LARGO_ENTRADA],
					char ipEntrada[LARGO_IP],char puertoEntrada[LARGO_IP]);

TipoLog* determinarNivelLog(char nivelLogEntrada[LARGO_ENTRADA]);

void validarPuertoEIp(char ipEntrada[LARGO_IP], char puertoEntrada[LARGO_IP], char ip[LARGO_IP], int* puerto);

void mostrarAyuda();

#endif /* SRC_UTILS_VALIDACIONES_HPP_ */
