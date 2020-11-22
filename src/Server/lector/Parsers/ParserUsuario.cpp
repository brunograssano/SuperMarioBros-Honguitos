#include "ParserUsuario.hpp"

void ParserUsuario::parsearUsuario(pugi::xml_node usuario,ArchivoLeido* archivoLeido){
	string nombreUsuario = usuario.child_value("username");
	string contraseniaUsuario = usuario.child_value("password");

	if(nombreUsuario.empty() || contraseniaUsuario.empty()){
		archivoLeido->mensajeError.push_front("No puede cargar un usuario sin contrasenia o nombre de usuario");
		return;
	}

	usuario_t usuarioJuego = {nombreUsuario,contraseniaUsuario,false} ;
	archivoLeido->usuariosValidos.push_back(usuarioJuego);
}
