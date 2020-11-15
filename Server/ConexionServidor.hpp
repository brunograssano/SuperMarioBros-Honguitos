#ifndef SERVER_CONEXIONSERVIDOR_HPP_
#define SERVER_CONEXIONSERVIDOR_HPP_

using namespace std;
#include <thread>
#include <string>

class ConexionServidor{


	public:
		ConexionServidor(int socket,string nombre);
		~ConexionServidor();


	private:
		int socketCliente;
		string nombreUsuario;



};



#endif /* SERVER_CONEXIONSERVIDOR_HPP_ */
