#ifndef SRC_SERVER_MODELO_NIVEL_HPP_
#define SRC_SERVER_MODELO_NIVEL_HPP_

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <cstdlib>
#include <utility>
#include "src/Server/modelo/Bloques/Pozo.hpp"
#include "src/Server/modelo/Bloques/Tuberia.hpp"
#include "src/Utils/Contador.hpp"
#include "Bloques/Bloque.hpp"
#include "Bloques/ObjetosSorpresa/ObjetoSorpresa.hpp"
#include "Enemigos/Enemigo.hpp"
#include "Moneda.hpp"
#include "Meta.hpp"

using namespace std;

const int ANCHO_FONDO2 = 8177;
const int ALTO_NIVEL = 600;

class Nivel{
	public:
        Nivel(int mundo, string direccionFondo, int tiempo, int cantidadMonedas, int puntoBanderaFin);
        ~Nivel();
		void inicializar();
        void agregarTuberia(int posicionXNuevaTuberia, int tipoTuberia, int colorTuberia);
        void agregarPozo(int posicionX,int tipoPozo);
		void agregarPlataforma(list<Bloque *> unaPlataforma);
		void agregarEnemigo(Enemigo* unEnemigo);
		void agregarMoneda(Moneda* unaMoneda);
		int obtenerMundo() const;
		int tiempoRestante();
		void iniciar();

        /* Completará la información de los siguientes campos:
         * tiempoFaltante, mundo, bloques[], enemigos[], monedas[],tuberias[], y sus respectivos topes */
		void completarInformacionRonda(info_ronda_t* ptrInfoRonda, bool (* deboAgregarlo)(void*, int), void* contexto);
        void actualizarModelo(map<int, Mario*> jugadores);
        bool todosEnLaMeta(map<int, Mario*> jugadores);
		string obtenerDireccionFondoActual();
        void terminar();
        void completarInformacionNivel(nivel_t *nivel);
        void aparecerDisparo(ObjetoFugaz* disparo);

    private:
        void sacarEnemigosMuertos();
        void sacarMonedasAgarradas();
        void actualizarPosicionesEnemigos();
        void actualizarMonedas();
        void actualizarObjetosFugaces();
        void resolverColisiones(map<int,Mario*> jugadores);
        bool esUnaPosicionXValidaEnemigo(int coordenadaX);
        bool esUnaPosicionValidaMoneda(int numeroPosicionX, int numeroPosicionY);
        void resolverGanadores(map<int, Mario *> map);
        void inicializarPosicionEnemigo();
        void inicializarPosicionMonedas();
        void inicializarPosicionesOcupadasPorBloques();
        static void agregarObjeto_helper(void* ptr_jugador, void* ptr_bloque, void* ptr_nivel);
        void utilizarSorpresa(Mario* jugador, Bloque* bloque);

        map<int, bool> posicionesOcupadasXEnemigos;
        map<tuple<int, int>, bool> posicionesOcupadas;

        list<Bloque*> plataformas;
        list<Enemigo*> enemigos;
        list<Moneda*> monedas;
        list<Pozo*> pozos;
        list<Tuberia*> tuberias;

        list<ObjetoFugaz*> objetosFugaces;

        Meta* meta;
        Contador* contador;

        int mundo;
        string direccionFondo;
        int tiempo;
        int cantidadMonedas;
        float puntoBanderaFin;

        void sacarObjetosFugaces();
        void actualizarBloques();
};

#endif /* SRC_SERVER_MODELO_NIVEL_HPP_ */