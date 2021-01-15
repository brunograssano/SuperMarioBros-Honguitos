#ifndef SRC_SERVER_MODELO_NIVEL_HPP_
#define SRC_SERVER_MODELO_NIVEL_HPP_

#include <map>
#include <string>
#include <tuple>
#include <cstdlib>
#include <utility>
#include <src/Server/modelo/Bloques/Pozo.hpp>
#include "src/Server/modelo/Bloques/Tuberia.hpp"
#include "Bloques/Plataforma.hpp"
#include "src/Utils/Contador.hpp"
#include "Bloques/Bloque.hpp"
#include "Enemigos/Enemigo.hpp"
#include "Moneda.hpp"
#include "Meta.hpp"
#include "Podio.hpp"

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
		void agregarPlataforma(Plataforma* unaPlataforma);
		void agregarEnemigo(Enemigo* unEnemigo);
		void agregarMoneda(Moneda* unaMoneda);
		int obtenerMundo() const;
		int tiempoRestante();
		void iniciar(map<int, Mario*> jugadores);

        /* Completará la información de los siguientes campos:
         * tiempoFaltante, mundo, bloques[], enemigos[], monedas[],tuberias[], y sus respectivos topes */
		void completarInformacionRonda(info_ronda_t* ptrInfoRonda, bool (* deboAgregarlo)(void*, int), void* contexto);
        void actualizarModelo(map<int, Mario*> jugadores);
        bool todosEnLaMeta(map<int, Mario*> jugadores);
		string obtenerDireccionFondoActual();
        void terminar();
        void completarInformacionNivel(nivel_t *nivel);
        void aparecerDisparo(Disparo* disparo);
        Podio* obtenerPodio();

    private:
        void sacarEnemigosMuertos();
        void actualizarPosicionesEnemigos();
        void actualizarMonedas();
        void actualizarDisparos();
        bool esUnaPosicionXValidaEnemigo(int coordenadaX);
        bool esUnaPosicionValidaMoneda(int numeroPosicionX, int numeroPosicionY);
        void resolverGanadores(map<int, Mario *> map);
        void inicializarPosicionEnemigo();
        void inicializarPosicionMonedas();
        void inicializarPosicionesOcupadasPorBloques();

        map<int, bool> posicionesOcupadasXEnemigos;
        map<tuple<int, int>, bool> posicionesOcupadas;

        list<Plataforma*> plataformas;
        list<Enemigo*> enemigos;
        list<Moneda*> monedas;
        list<Pozo*> pozos;
        list<Tuberia*> tuberias;
        list<Enemigo*>enemigosMuertos;

        //todo ->
        list<Disparo*> disparos;               //Refactor: proximamente tendra objetosFugaces: flores, disparos, otros objetos(Moneda de bloque)
        //list<ObjetoFugaz*> objetosFugaces;   // y esta debería ser la lista. Estos objetos podrán desaparecer, para ello
                                               // habrá que preguntar si "debeDesaparecer()" y si es así quitarlo... :S
        Meta* meta;
        Contador* contador;
        Podio* podio;

        int mundo;
        string direccionFondo;
        int tiempo;
        int cantidadMonedas;
        float puntoBanderaFin;

};

#endif /* SRC_SERVER_MODELO_NIVEL_HPP_ */