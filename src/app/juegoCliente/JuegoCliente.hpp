#ifndef SRC_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_
#define SRC_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_


using namespace std;
#include <map>
#include <string>
#include <list>

typedef struct enemigo{
	int posX;
	unsigned short numeroRecorte;
	unsigned short tipoEnemigo; // 1 GOOMBA - 2 KOOPA
	string direccionImagen;
}enemigo_t;

typedef struct bloque{
	int posX;
	int posY;
	string dirImagen;
}bloque_t;

typedef struct mario{
	unsigned short idImagen; //1 ROJO - 2 VERDE - 3 VIOLETA - 4 CELESTE
	int posX;
	int posY;
	int recorteImagen;
}mario_t;

typedef struct moneda{
	int posX;
	int posY;
	unsigned short numeroRecorte;
}moneda_t;

typedef struct jugador{
	string nombreJugador;
	int puntos;
	mario_t mario;
}jugador_t;



const int MAX_JUGADORES = 4;

class JuegoCliente{

	public:
		JuegoCliente(int cantidadJugadores,jugador_t jugadores[MAX_JUGADORES],int idPropio);
		~JuegoCliente();

		map<int,jugador_t> obtenerJugadores();
		list<enemigo_t> obtenerEnemigos();
		list<bloque_t> obtenerBloques();
		list<moneda_t> obtenerMonedas();
		int obtenerTiempoFaltante();
		int obtenerMundoActual();
		int obtenerIDPropio();

	private:
		map<int,jugador_t> jugadores;
		list<bloque_t> bloques;
		list<enemigo_t> enemigos;
		list<moneda_t> monedas;
		int cantidadJugadores;
		int idPropio;

		int numeroMundo;
		int tiempoFaltante;
		int tiempoDeInicio;
};



#endif /* SRC_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_ */
