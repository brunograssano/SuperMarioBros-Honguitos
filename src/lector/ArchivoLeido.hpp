#ifndef SRC_LECTOR_ARCHIVOLEIDO_H_
#define SRC_LECTOR_ARCHIVOLEIDO_H_

using namespace std;
#include <string>
#include <list>
#include "../modelo/Nivel.hpp"
#include "../log/TipoLog.hpp"

typedef struct usuario{
	string nombre;
	string contrasenia;
}usuario_t;

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
		list<Nivel*> niveles;
		bool leidoCorrectamente;
		list<string> mensajeError;
		list<usuario_t> usuariosValidos;
		int cantidadConexiones;

		void verificarLectura();
		~ArchivoLeido();
};

#endif
