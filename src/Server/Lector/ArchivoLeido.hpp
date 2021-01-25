#ifndef SRC_LECTOR_ARCHIVOLEIDO_H_
#define SRC_LECTOR_ARCHIVOLEIDO_H_

#include <string>
#include <list>
using namespace std;
#include "src/Server/Modelo/Juego/Nivel/Nivel.hpp"
#include "../../Utils/log/TipoLog.hpp"
#include "../../Utils/Utils.hpp"

class ArchivoLeido{
	public:

		ArchivoLeido(){
			tipoLog = nullptr;
			anchoVentana = 0;
			altoVentana = 0;
			leidoCorrectamente = true;
			cantidadConexiones = 1;
		}

		TipoLog* tipoLog;
		int anchoVentana;
		int altoVentana;
		list<Nivel*> niveles{};
		bool leidoCorrectamente;
		list<string> mensajeError{};
		list<usuario_t> usuariosValidos{};
		int cantidadConexiones;

		void verificarLectura();
		~ArchivoLeido();
};

#endif
