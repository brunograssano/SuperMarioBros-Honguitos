#include "../Client/mainClient.hpp"
#include "../Client/Cliente.hpp"
#include "src/Utils/log/Log.hpp"
#include "../Utils/Validaciones.hpp"

int mainClient(int argc, char* args[]){

	char nivelLogEntrada[LARGO_ENTRADA] = "";
	char ipEntrada[LARGO_IP] = "";
	char puertoEntrada [LARGO_IP]= "";

	manejarEntrada(argc, args, ipEntrada, puertoEntrada, nivelLogEntrada);

	int puerto;
	char ip[LARGO_IP] = "";

	validarPuertoEIp(ipEntrada, puertoEntrada, ip, &puerto);

	TipoLog* nivelLog = determinarNivelLog(nivelLogEntrada);
	Log::getInstance(nivelLog);

	Cliente cliente(ip, puerto);
	cliente.ejecutar();

	return 0;
}
