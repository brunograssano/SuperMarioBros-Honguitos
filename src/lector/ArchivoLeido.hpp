#ifndef SRC_LECTOR_ARCHIVOLEIDO_H_
#define SRC_LECTOR_ARCHIVOLEIDO_H_

using namespace std;
#include <string>
#include <list>
#include "../modelo/Nivel.h"
#include "../log/TipoLog.h"

class ArchivoLeido{
	public:
			TipoLog* tipoLog;
			int anchoVentana;
			int altoVentana;
			list<Nivel*> niveles;
			bool leidoCorrectamente;
			list<string> mensajeError;

			void verificarLectura();
			~ArchivoLeido();
};

#endif
