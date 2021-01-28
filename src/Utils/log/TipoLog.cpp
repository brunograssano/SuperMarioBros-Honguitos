#include "TipoLog.hpp"

void TipoLog::mostrarPosicion(const std::string &registroPosicion, std::ofstream &archivo) {
    escribirEnLog(" [DEBUG] ",registroPosicion,archivo);
}

void TipoLog::mostrarAccion(const std::string &registroAccion, std::ofstream &archivo) {
    escribirEnLog(" [DEBUG] ",registroAccion,archivo);
}

void TipoLog::mostrarMensajeDeInfo(const std::string &registroInfo, std::ofstream &archivo) {
    escribirEnLog(" [INFO] ",registroInfo,archivo);
}

void TipoLog::mostrarMensajeDeCarga(const std::string &registroInfo, std::ofstream &archivo) {
    escribirEnLog(" [INFO] ",registroInfo,archivo);
}

void TipoLog::huboUnError(const std::string &registroError, std::ofstream &archivo) {
    escribirEnLog(" [ERROR] ",registroError,archivo);
}

void TipoLog::escribirEnLog(const std::string &tipo, const std::string &registroError, std::ofstream &archivo) {
    archivo << tipo + registroError << std::endl;
}

