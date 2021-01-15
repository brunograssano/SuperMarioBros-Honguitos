#ifndef SRC_SERVER_SERVIDOR_HPP_
#define SRC_SERVER_SERVIDOR_HPP_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>

#include <thread>
#include <map>

#include "../Utils/log/Log.hpp"
#include "modelo/Juego.hpp"

class AplicacionServidor;
#include "../Server/AplicacionServidor.hpp"
#include "../Utils/Utils.hpp"
#include "UtilidadesServer.hpp"
#include "lector/ArchivoLeido.hpp"

class ConexionCliente;
#include "ConexionCliente.hpp"

#include "ManejadorIdentificadores.hpp"

#include "src/Utils/Constantes.hpp"

class AceptadorDeConexiones;
#include "AceptadorDeConexiones.hpp"

class ReconectadorDeConexiones;
#include "ReconectadorDeConexiones.hpp"

class Servidor : public Thread{

	public:
		Servidor(ArchivoLeido archivoLeido,const list<string>& mensajesErrorOtroArchivo, int puerto, char* ip);
		~Servidor();

		bool esUsuarioValido(const usuario_t& posibleUsuario,ConexionCliente* conexionClienteConPosibleUsuario);
		void intentarIniciarModelo();
		void encolarEntradaUsuario(entrada_usuario_id_t entradaUsuario);
		void agregarUsuarioDesconectado(ConexionCliente* conexionPerdida,int idJugador,string nombre,const string& contrasenia);
		void ejecutar() override;
		void guardarRondaParaEnvio(info_ronda_t ronda);
		void terminarElJuego();

		map<int,string> obtenerMapaJugadores();

		actualizacion_cantidad_jugadores_t crearActualizacionJugadores();
        void mandarNivelAClientes(nivel_t nivel);
        bool terminoElJuego() const;
        void guardarConexion(ConexionCliente *conexionCliente);

        int cantidadUsuariosLogueados() const;
        bool empezoElJuego();
        void mandarActualizacionAClientes();
        void reconectarJugador(mensaje_log_t mensaje, const int idJugador);

private:
        ReconectadorDeConexiones* reconectador;
        AceptadorDeConexiones* aceptadorDeConexiones;
		map<int,string> mapaIDNombre;
		Log* log;
		AplicacionServidor* aplicacionServidor;
		ManejadorIdentificadores* manejadorIDs;

		int socketServer;
		int cantidadConexiones;
		int cantUsuariosLogueados = 0;

		list<usuario_t> usuariosValidos;

		bool esUsuarioDesconectado(const usuario_t& posibleUsuario,ConexionCliente* conexionClienteConPosibleUsuario);
		bool esUsuarioSinConectarse(const usuario_t& posibleUsuario,ConexionCliente* conexionClienteConPosibleUsuario);

		bool terminoJuego;
		list<ConexionCliente*> clientes;
		list<ConexionCliente*> conexionesPerdidas;
		map<int,ConexionCliente*> clientesJugando;
};

#endif /* SRC_SERVER_SERVIDOR_HPP_ */