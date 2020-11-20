#ifndef SRC_UTILS_HPP_
#define SRC_UTILS_HPP_

using namespace std;

const int MAX_IMAGEN_ENEMIGOS = 30,MAX_IMAGEN_BLOQUE = 30;
const int MAX_BLOQUES=200,MAX_ENEMIGOS=70,MAX_MONEDAS=70,MAX_IMAGEN_NIVELES_POSIBLES = 30;

const int MAX_JUGADORES = 4;

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
	int recorteImagen; // Si el recorte de la imagen viene en un valor (-1?) se indica que el jugador se desconecto y el recorte correspondiente es el gris
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


typedef struct usuario{
	string nombre;
	string contrasenia;
	bool usado;
}usuario_t;

typedef struct entrada_usuario{
	bool A;
	bool S;
	bool D;
	bool W;
}entrada_usuario_t;

#define INICIO 'I'
typedef struct info_inicio{
	unsigned short cantidadJugadores;
	unsigned short cantidadJugadoresActivos;
}info_inicio_t;

#define VERIFICACION 'V'
typedef bool verificacion_t;

typedef struct info_partida{
	jugador_t jugadores[MAX_JUGADORES];
	unsigned short cantidadJugadores;
	string direccionesFondoNiveles[MAX_IMAGEN_NIVELES_POSIBLES];

	bool iniciadoCorrectamente;

	string direccionesImagenEnemigos[MAX_IMAGEN_ENEMIGOS];
	string direccionesImagenBloques[MAX_IMAGEN_BLOQUE];

	unsigned short cantidadFondosNiveles;
	unsigned short anchoVentana;
	unsigned short altoVentana;
	unsigned short idPropio;
}info_partida_t;

typedef struct info_estado_actual_partida{
	unsigned short cantidadJugadoresActivos;
}info_estado_actual_partida_t;


typedef struct ronda{
	unsigned short posXCamara;
	unsigned short tiempoFaltante;
	unsigned short topeBloques;
	unsigned short topeEnemigos;
	unsigned short topeMonedas;
	bloque_t bloques[MAX_BLOQUES];
	enemigo_t enemigos[MAX_ENEMIGOS];
	moneda_t monedas[MAX_MONEDAS];
	jugador_t jugadores[MAX_JUGADORES];
}info_ronda_t;



#endif /* SRC_UTILS_HPP_ */
