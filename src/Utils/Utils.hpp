#ifndef SRC_UTILS_HPP_
#define SRC_UTILS_HPP_

#include <string>
#include <cstdint>

using namespace std;
/* PALABRAS RESERVADAS */
/*
 * V: Verificacion
 * U: Actualizacion sobre la cantidad de jugadores.
 * L: Mensaje para el log.
 * E: Entrada del usuario
 * C: Credenciales que nos manda el usuario
 * P: Informacion necesaria para iniciar la partida
 * R: Información necesaria para renderizar
 * S: Sonido a reproducir
 * N: Informacion del nivel nuevo (bloques fijos)
 */


const int MAX_NOMBRE = 20,MAX_CONTRASENIA = 25;

const int MAX_CANT_NIVELES = 10,MAX_LARGO_NOMBRE_NIVEL= 30; // Solo el nombre, nosotros concatenamos la direccion
															// correspondiente a la carpeta en la que tiene que estar esta imagen

const int MAX_SORPRESAS=15,MAX_ENEMIGOS=25,MAX_MONEDAS=25,MAX_TUBERIAS = 30,MAX_POZOS = 30, MAX_LADRILLOS = 400,MAX_EFECTOS = 20;

const int MAX_JUGADORES = 4;
const int MAX_MENSAJE = 75;

const int TIPO_GOOMBA = 1;
const int TIPO_KOOPA = 2;

typedef struct rectangulo{
    int x1;
    int x2;
    int y1;
    int y2;
    int h;
    int w;
}rectangulo_t;

#define TIPO_ERROR 'E'
#define INFO 'I'
#define MENSAJE_LOG 'L'
typedef struct mensaje_log{
	char tipo;
	char mensajeParaElLog[MAX_MENSAJE];
}mensaje_log_t;

typedef struct enemigo{
    unsigned short posX;
    unsigned short posY;
	uint8_t numeroRecorteX;	// 1|2|3|4|5|6|...|
	uint8_t numeroRecorteY;	// 1: marrón, 2: azul, 3: blanco , 4: fuego
	uint8_t tipoEnemigo;	// 1 GOOMBA - 2 KOOPA
	bool espejar;
}enemigo_t;

typedef struct bloque{
    int posX;
    int posY;
	uint8_t numeroRecorteX;
	uint8_t numeroRecorteY;
}bloque_t;

typedef struct mario{
	uint8_t idImagen;    //1 ROJO - 2 VERDE - 3 VIOLETA - 4 CELESTE
	uint8_t modificador; // 0 Nada - 1 Fuego
	unsigned short posX;
	unsigned short posY;
	int8_t recorteImagen; // Si el recorte de la imagen viene en un valor (-1) se indica que el jugador se desconecto y
    uint8_t vidas;		  //el recorte correspondiente es el gris
}mario_t;

typedef struct moneda{
	unsigned short posX;
	unsigned short posY;
	uint8_t numeroRecorte;
}moneda_t;

typedef struct jugador{
	char nombreJugador[MAX_NOMBRE];
	unsigned short puntos;
	mario_t mario;
}jugador_t;

typedef struct tuberia {
    unsigned short posX;
    unsigned short posY;
    uint8_t color;
    uint8_t tipo;
}tuberia_t;

typedef struct pozo {
    unsigned short posX;
    uint8_t fondo;
    uint8_t tipo;
}pozo_t;

typedef struct podio {
    unsigned short puntosNivel[MAX_JUGADORES];
    unsigned short cantidadJugadores;
    int ids[MAX_JUGADORES];
}podio_t;

#define NADA 0
#define BOLA_DE_FUEGO 1
#define CHISPA 2
#define FLOR 3
#define MONEDA_FLOTANTE 4
typedef struct efecto{
    unsigned short posX;
    unsigned short posY;
    uint8_t numeroRecorte;
    uint8_t tipoDeEfecto;
}efecto_t;

#define CREDENCIAL 'C'
typedef struct credencial{
	char nombre[MAX_NOMBRE];
	char contrasenia[MAX_CONTRASENIA];
}credencial_t;

#define ENTRADA 'E'
typedef struct entrada_usuario{
	bool A;
	bool S;
	bool D;
	bool W;
	bool ESP;
	bool T;
}entrada_usuario_t;

#define VERIFICACION 'V'
typedef bool verificacion_t;

typedef struct entrada_usuario_id{
	entrada_usuario_t entradas;
	unsigned short id;
}entrada_usuario_id_t;

#define PARTIDA 'P'
typedef struct info_partida{
	jugador_t jugadores[MAX_JUGADORES];
	podio_t podios[MAX_CANT_NIVELES];
	podio_t podioPuntosAcumulados;
	unsigned short topePodios;
	unsigned short cantidadJugadores;
	char direccionesFondoNiveles[MAX_CANT_NIVELES][MAX_LARGO_NOMBRE_NIVEL];
	unsigned short cantidadFondosNiveles;
	unsigned short anchoVentana;
	unsigned short mundo;
	unsigned short altoVentana;
	unsigned short idPropio;
}info_partida_t;


typedef struct par_id_nombre{
	char nombre[MAX_NOMBRE];
	unsigned short id;
	bool conectado;
}par_id_nombre_t;

#define ACTUALIZACION_JUGADORES 'U'
typedef struct actualizacion_cantidad_jugadores{
	unsigned short cantidadMaximaDeJugadores;
	unsigned short cantidadJugadoresActivos;
	unsigned short tope;
	par_id_nombre_t pares_id_nombre[MAX_JUGADORES];
}actualizacion_cantidad_jugadores_t;

#define RONDA 'R'
typedef struct ronda{
	uint8_t topeBloques;
    uint8_t topeEnemigos;
	uint8_t topeMonedas;
    uint8_t topeEfectos;
	bool ganaron;
	bool perdieron;
	unsigned short posXCamara;
	unsigned short tiempoFaltante;
	bloque_t bloques[MAX_SORPRESAS];
	enemigo_t enemigos[MAX_ENEMIGOS];
	moneda_t monedas[MAX_MONEDAS];
	jugador_t jugadores[MAX_JUGADORES];
	efecto_t efectos[MAX_EFECTOS];
}info_ronda_t;

#define NIVEL 'N'
typedef struct nivel{
    uint8_t mundo;
    short topeBloques;
    uint8_t topePozos;
    uint8_t topeTuberias;
    bloque_t bloques[MAX_LADRILLOS];
    tuberia_t tuberias[MAX_TUBERIAS];
    pozo_t pozos[MAX_POZOS];
    podio_t podio;
    podio_t podioPuntosAcumulados;
}nivel_t;

typedef struct usuario{
	string nombre;
	string contrasenia;
	bool usado;
}usuario_t;

#define SONIDO 'S'
typedef struct sonido{
    uint8_t tipoSonido;
}sonido_t;

bool esUnSonidoValido(sonido_t sonido);

#endif /* SRC_UTILS_HPP_ */
