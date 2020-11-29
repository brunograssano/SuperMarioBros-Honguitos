#include "../Client/mainClient.hpp"
#include "../Client/Cliente.hpp"

#include "app/AplicacionCliente.hpp"
#include "../Utils/Validaciones.hpp"

int mainClient(int argc, char* args[]){

	char nivelLogEntrada[LARGO_ENTRADA] = "";
	char ipEntrada[LARGO_IP] = "";
	char puertoEntrada [LARGO_IP]= "";

	//manejarEntrada(argc, args, ipEntrada, puertoEntrada, nivelLogEntrada);

	int puerto = 5004;
	char ip[LARGO_IP] = "127.0.0.1";

	//validarPuertoEIp(ipEntrada, puertoEntrada, ip, &puerto);

	TipoLog* nivelLog = determinarNivelLog(nivelLogEntrada);
	Log::getInstance(nivelLog);
	info_partida_t informacion; //nos lo mandan

	Cliente* cliente = new Cliente(ip, puerto);
	cliente->ejecutar();
	delete cliente;
	delete Log::getInstance();


	return 0;
}
