#ifndef SRC_SERVER_MODELO_NIVEL_HPP_
#define SRC_SERVER_MODELO_NIVEL_HPP_

#include <map>
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
#include "Piso.hpp"
#include "Podio.hpp"

using namespace std;

const int ALTO_NIVEL = 600;

class Nivel{
	public:
        Nivel(int mundo, string direccionFondo, int tiempo, int cantidadMonedas, int puntoBanderaFin, int altoPiso);
        ~Nivel();
		void inicializar();
        void agregarTuberia(int posicionXNuevaTuberia, int tipoTuberia, int colorTuberia);
        void agregarPozo(int posicionX, int tipoPozo, int fondo);
		void agregarPlataforma(list<Bloque *> unaPlataforma);
		void agregarEnemigo(Enemigo* unEnemigo);
		void agregarMoneda(Moneda* unaMoneda);
		int obtenerMundo() const;
		int tiempoRestante();
		void iniciar(map<int, Mario*> jugadores);

        /* Completará la información de los siguientes campos:
         * tiempoFaltante, mundo, bloques[], enemigos[], monedas[],tuberias[], y sus respectivos topes */
		void completarInformacionRonda(info_ronda_t* ptrInfoRonda, bool (* deboAgregarlo)(void*, rectangulo_t), void* contexto);
        void actualizarModelo(map<int, Mario*> jugadores, rectangulo_t rectanguloEscena);
        bool todosEnLaMeta(map<int, Mario*> jugadores);
		string obtenerDireccionFondoActual();
        void terminar(map<int, Mario*> jugadores);
        void completarInformacionNivel(nivel_t *nivel);
        void aparecerDisparo(ObjetoFugaz* disparo);
        Podio* obtenerPodio();

    private:
        void sacarEnemigosMuertos();
        void sacarMonedasAgarradas();
        void actualizarPosicionesEnemigos(rectangulo_t rectangulo);
        void actualizarMonedas();
        void actualizarObjetosFugaces();
        void resolverColisiones(map<int,Mario*> jugadores);
        bool esUnaPosicionXValidaEnemigo(int coordenadaX);
        bool esUnaPosicionValidaMoneda(int numeroPosicionX, int numeroPosicionY);
        void resolverGanadores(map<int, Mario *> map);
        void elevarObstaculos();
        void inicializarPosicionEnemigo();
        void inicializarPosicionMonedas();
        void inicializarPosicionOcupadasPorTuberias();
        void inicializarPosicionesOcupadasPorBloques();
        static void agregarObjeto_helper(void* ptr_jugador, void* ptr_bloque, void* ptr_nivel);
        void utilizarSorpresa(Mario* jugador, Bloque* bloque);

        map<int, bool> posicionesOcupadasXEnemigos;
        map<tuple<int, int>, bool> posicionesOcupadas;

        list<Bloque*> plataformas;
        list<Enemigo*> enemigos;
        list<Moneda*> monedas;
        list<Tuberia*> tuberias;
        list<ObjetoFugaz*> objetosFugaces;
        Piso piso = Piso(0);

        Meta meta = Meta(0);
        Contador contador = Contador(0, 0);
        Podio* podio;

        int mundo;
        string direccionFondo;
        int tiempo;
        int cantidadMonedas;
        float puntoBanderaFin;

        void sacarObjetosFugaces();
        void actualizarBloques();

        void imponerPosicionDeReaparicion(map<int, Mario*> jugadores, rectangulo_t rectanguloEscena);
        void buscarBloqueParaCaer(rectangulo_t rectanguloEscena, PosicionFija* pos);
};

#endif /* SRC_SERVER_MODELO_NIVEL_HPP_ */