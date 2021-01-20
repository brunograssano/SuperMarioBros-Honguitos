#ifndef SRC_TIPOLOG_H_
#define SRC_TIPOLOG_H_
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
using namespace std;

class TipoLog{

	public:

		virtual ~TipoLog()= default;

		//DEBUG//
		virtual void mostrarPosicion(const string& registroPosicion,ofstream& archivo){
			escribirEnLog(" [DEBUG] ",registroPosicion,archivo);
		}

		virtual void mostrarAccion(const string& registroAccion,ofstream& archivo){
			escribirEnLog(" [DEBUG] ",registroAccion,archivo);
		}

		//INFO//
		virtual void mostrarMensajeDeInfo(const string& registroInfo,ofstream& archivo){
			escribirEnLog(" [INFO] ",registroInfo,archivo);
		}
		virtual void mostrarMensajeDeCarga(const string& registroInfo,ofstream& archivo){
			escribirEnLog(" [INFO] ",registroInfo,archivo);
		}

		//ERRORES//
		virtual void huboUnError(const string& registroError,ofstream& archivo){
			escribirEnLog(" [ERROR] ",registroError,archivo);
		}


	private:

		static void escribirEnLog(const string& tipo,const string& registroError,ofstream& archivo){
			archivo << tipo + registroError << endl;
		}

};

#endif /* SRC_TIPOLOG_H_ */